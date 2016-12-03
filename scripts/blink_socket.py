""" The blinky socket.

Communicate with socket.

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
import os
import socket 
import random
import time

sock_name_ = '/tmp/socket_blinky'

def poll_socket( ):
    return os.path.exists( sock_name_ )

def main( ):
    s = socket.socket( socket.AF_UNIX, socket.SOCK_STREAM )
    while True:
        if os.path.exists( sock_name_ ):
            try:
                s.connect( sock_name_ )
                break
            except Exception as e:
                pass
        else:
            time.sleep( 1 )
            print( '.', end='')
            sys.stdout.flush( )
    while True:
        # Read data here.
        data = s.recv( 10 * 1024 )
        if not data:
            print('no data' )
            break
        print( len(data ))


if __name__ == '__main__':
    main()
