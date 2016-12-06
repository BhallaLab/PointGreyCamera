"""blink_detection.py: 

Run blink detection on given directory. One tiff file at time.

"""
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2016, Dilawar Singh"
__credits__          = ["NCBS Bangalore"]
__license__          = "GNU GPL"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import sys
import os
sys.path.append( 'eye-blink-detector' )
import blinky

# get the current directory
tifffiles = []
with open( './__datadir__', 'r' ) as f:
    dataDir = f.read( ).strip( )
    print( 'Processing %s' % dataDir )
    for d, sd, fs in os.walk( dataDir ):
        for f in fs:
            if 'tif' in f[-4:].lower( ):
                tifffiles.append( os.path.join( d, f ) )

for f in sorted(tifffiles):
    print( '[INFO] Processing %s'  % f)
    blinky.main( { 'tiff_file' : f } )
