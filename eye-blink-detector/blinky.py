#!/usr/bin/env python

"""blinky.py: 

Starting point of blinky

"""
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2015, Dilawar Singh and NCBS Bangalore"
__credits__          = ["NCBS Bangalore"]
__license__          = "GNU GPL"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import extract
import pylab
import tifffile
import numpy as np
import helper
import cv2

def main( args ):
    # Extract video first
    frames = tifffile.imread( args['tiff_file'] )
    tvec, vec, rawvec, data = [], [], [], []
    fps = 100.0
    for i, f in enumerate( frames ):
        tvec.append( i * 1 / fps )
        infile, outfile, res, s = helper.process_frame( f ) 
        vec.append( res )
        rawvec.append( s )
        # This is to show what's going on
        result = np.concatenate((infile, outfile), axis=1)
        cv2.imshow( 'result', result )
        cv2.waitKey( 1 )

    data = np.array((tvec, vec, rawVec)).T
    edgyBlinks = extract.find_blinks_using_edge(data)
    outfile = "%s_blinks_using_edges.csv" % args['tiff_file']
    print("[INFO] Writing to outfile %s" % outfile)
    np.savetxt(outfile, np.array(edgyBlinks).T, delimiter=","
            , header = "time,blinks")

    pixalBlinks = extract.find_blinks_using_pixals(data)
    outfile = "%s_blinks_using_pixals.csv" % args['tiff_file']
    print("[INFO] Writing to outfile %s" % outfile)
    np.savetxt(outfile, np.array(pixalBlinks).T, delimiter=","
            , header = "time,blinks")

if __name__ == '__main__':
    import argparse
    # Argument parser.
    description = '''description'''
    parser = argparse.ArgumentParser(description=description)
    class Args: pass 
    args = Args()
    parser.add_argument('--tiff-file', '-f'
        , required = False
        , help = 'Path of the tiff file'
        )
    parser.add_argument('--bbox', '-b'
        , required = False
        , nargs = '+'
        , type = int
        , help = 'Bounding box : topx topy width height'
        )
    parser.parse_args(namespace=args)
    main(vars(args))

