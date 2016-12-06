""" The blinky socket.

Communicate with socket.

We read in non-blocking mode. If there is not data available on the socket, it
does not mean the connection is terminated.

"""
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

img_shape_ = ( 1024/2, 1280/2 )
frame_size_ = img_shape_[0] * img_shape_[1]

max_frames_in_trial = 1200
image_stack_ = None

now = datetime.datetime.now().isoformat( )
data_dir_ = 'videos_/%s' % now 

metadata_ = { 'acquisition_datetime' : [ ] }

# When True, put a small text on each frame.
write_timestamp_ = True

if not os.path.isdir( data_dir_ ):
    os.makedirs( data_dir_ )

def save_img_stack( index ):
    import tifffile
    global metadata_ 
    global image_stack_ 
    filename = os.path.join( data_dir_, 'stack_%03d.tif' % index )
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

sock_name_ = '/tmp/socket_blinky'

def poll_socket( ):
    return os.path.exists( sock_name_ )

def main( ):
    global img_, buf_
    global image_stack_
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
            time.sleep( 1 )
            print( '.', end='')
            sys.stdout.flush( )

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
    main()
