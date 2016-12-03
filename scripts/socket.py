"""socket.py: 

Communicate with socket.

"""
    
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

def main( ):
    s = socket.socket( socket.AF_UNIX , socket.SOCK_STREAM )
    s.connect( '/tmp/echo_socket' )
    while True:
        s.send( random.random( ) )

if __name__ == '__main__':
    main()
