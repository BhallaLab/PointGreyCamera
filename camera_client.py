#!/usr/bin/env python

from __future__ import print_function
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2016, Dilawar Singh"
__credits__          = ["NCBS Bangalore"]
__license__          = "GNU GPL"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = ""
__status__           = "Development"

import sys
import socket 
import random
import time
import fcntl, os
import errno
import cStringIO as StringIO
import numpy as np
import cv2
import threading
import datetime
import re

script_dir = os.path.dirname( os.path.realpath( __file__ ) )
config_file = os.path.join( script_dir, 'config.h' ) 
if not os.path.isfile( config_file ):
    print( "I can't find %s. Make sure it is available" % config_file )
    print( " Did you run cmake? " )
    quit( )

with open( config_file, "r" ) as cf:
    configText = cf.read( )
    h = re.search( r'#define\s+FRAME_HEIGHT\s+(\d+)', configText ).group(1)
    w = re.search( r'#define\s+FRAME_WIDTH\s+(\d+)', configText ).group(1) 
    sock = re.search( r'#define\s+SOCK_PATH\s+\"(.+?)\"', configText ).group(1) 
    h, w = int(h), int(w)
    assert sock, "Can't read socket path from configuration file"

sock_name_ = sock

img_shape_ = ( h, w )
frame_size_ = img_shape_[0] * img_shape_[1]

max_frames_in_trial = 1200
image_stack_ = None

args_ = None
metadata_ = { 'acquisition_datetime' : [ ] }

# When True, put a small text on each frame.
write_timestamp_ = True

def initialize( args ):
    global args_
    args_ = args
    if not os.path.exists( args_.data_dir ):
        print( '[INFO] Creating %s' % args_.data_dir )
        os.makedirs( args_.data_dir )

def save_img_stack( index ):
    import tifffile
    global metadata_ 
    global image_stack_ 
    global args_
    filename = os.path.join( args.data_dir, 'stack_%03d.tif' % index )
    tifffile.imsave( filename, image_stack_, metadata = metadata_ )
    print( '[INFO] Saved to %s' % filename )

def init_stack( ):
    global image_stack_
    global img_shape_, max_frames_in_trial 
    global metadata_ 
    metadata_[ 'acquisition_datetime' ] = []
    image_stack_ = np.zeros( 
            shape=( max_frames_in_trial, img_shape_[0], img_shape_[1] )
            , dtype = np.uint8
            )


def poll_socket( ):
    return os.path.exists( sock_name_ )

def main( args ):
    global img_, buf_
    global image_stack_

    initialize( args )

    s = socket.socket( socket.AF_UNIX, socket.SOCK_STREAM )
    while True:
        if os.path.exists( sock_name_ ):
            try:
                s.connect( sock_name_ )
                break
            except Exception as e:
                print( 'Error connecting %s' % e )
                time.sleep( 1 )
        else:
            print( 'Could not find %s' % sock_name_ )
            time.sleep( 1 )

    # print( s.getsockopt( socket.SOL_SOCKET, socket.SO_SNDBUF ) )
    # Make it non-blocking.
    # fcntl.fcntl( s, fcntl.F_SETFL, os.O_NONBLOCK )
    totalBytesRead = 0
    totalFrames = 0
    buf = ''
    init_stack( )
    framesInStack = 0
    trial_count = 0
    while True:
        try:
            data = s.recv( frame_size_ )
            buf += data
            if len( buf) >= frame_size_:
                img = np.frombuffer( buf[:frame_size_], dtype = np.uint8 )
                img = np.reshape( img, img_shape_ )
                now = datetime.datetime.now().isoformat( ) 
                if write_timestamp_:
                    cv2.putText( img, now, (0, 10)
                            , cv2.FONT_HERSHEY_SIMPLEX, 0.4, 0, 1
                            )
                print( 'f', end='')
                sys.stdout.flush( )
                # print( img.shape, img.max(), img.min(), len(img) )
                if args_.show_frames:
                    try:
                        cv2.imshow( 'img', img )
                        cv2.waitKey( 1 )
                    except Exception as e:
                        pass
                image_stack_[ framesInStack ] = img
                metadata_[ 'acquisition_datetime' ].append( now )
                framesInStack += 1
                buf = buf[frame_size_:]
            else:
                pass

        except Exception as e:
            err = e.args[0]
            if err == errno.EAGAIN or err == errno.EWOULDBLOCK:
                time.sleep( 0.1 )
                print( 'No data available' )
                continue
            else:
                print('No data : %s' % e )
                break

        if framesInStack == max_frames_in_trial :
            framesInStack = 0
            tiff = image_stack_
            print( "\nSize of image stack ", tiff.shape )
            save_img_stack( trial_count )
            trial_count += 1
            init_stack( )

if __name__ == '__main__':
    import argparse
    # Argument parser.
    description = '''Camera client for PointGrey camera'''
    parser = argparse.ArgumentParser(description=description)
    parser.add_argument('--data-dir', '-d'
        , required = True
        , type = str
        , help = 'Where to store data?'
        )
    parser.add_argument('--show-frames', '-s'
        , required = False
        , default = True
        , action = 'store_true'
        , help = 'Whether to show frames while acquiring frames.'
        )
    class Args: pass 
    args = Args()
    parser.parse_args(namespace=args)

    try:
        main( args )
    except KeyboardInterrupt:
        print( "User terminated" )
        quit( 1 )
