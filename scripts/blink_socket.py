""" The blinky socket.

Communicate with socket.

We read in non-blocking mode. If there is not data available on the socket, it
does not mean the connection is terminated.

"""
from __future__ import print_function
    
__author__           = "Me"
__copyright__        = "Copyright 2016, Me"
__credits__          = ["NCBS Bangalore"]
__license__          = "GNU GPL"
__version__          = "1.0.0"
__maintainer__       = "Me"
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

img_ = np.zeros( shape=(1280, 1024), dtype=float )
buf_ = img_.data

sock_name_ = '/tmp/socket_blinky'

def poll_socket( ):
    return os.path.exists( sock_name_ )

def main( ):
    global img_, buf_
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
    while True:
        try:
            data = s.recv( 10 * 4096 )
            buf += data
            if len( buf) == 1024 * 1280:
                img = np.frombuffer( buf, dtype=np.uint8 )
                print( img )
                buf = ''

        except Exception as e:
            err = e.args[0]
            if err == errno.EAGAIN or err == errno.EWOULDBLOCK:
                time.sleep( 0.1 )
                print( 'No data available' )
                continue
            else:
                print('No data : %s' % e )
                break

if __name__ == '__main__':
    main()
