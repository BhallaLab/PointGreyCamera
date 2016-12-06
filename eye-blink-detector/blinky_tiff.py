#!/usr/bin/env python

"""
Extract blink data and visualize it using matplotlib.

"""
    
__author__           = "Dilawar Singh"
__copyright__        = "Copyright 2015, Dilawar Singh and NCBS Bangalore"
__credits__          = ["NCBS Bangalore"]
__license__          = "GNU GPL"
__version__          = "1.0.0"
__maintainer__       = "Dilawar Singh"
__email__            = "dilawars@ncbs.res.in"
__status__           = "Development"

import numpy as np
import gnuplotlib as gplt
import extract
import sys
import cv2
import helper
import os
import sys
import tifffile

data_ = np.zeros(shape=(1,3))
cap_ = None
fps_ = 0.0
box_ = None

axes_ = {}
lines_ = {}

tvec_ = []
y1_ = []
y2_ = []
args_ = None
fps_ = 100

def update_axis_limits(ax, x, y):
    xlim = ax.get_xlim()
    if x >= xlim[1]:
        ax.set_xlim(xlim[0], x+10)

    ylims = ax.get_ylim()
    if y >= ylims[1]:
        ax.set_ylim(ylims[0], y+1)

def bounding_box( img, box ):
    c0, r0, w, h = box 
    return img[r0:r0+h, c0:c0+w]

def animate( i, img ):
    global data_
    # global time_text_
    global box_
    global tvec_, y1_, y2_
    t = float(i) / fps_
    c0, r0, w, h = box_
    if h < 0 or w < 0:
        w, h = img.shape 
        w, h = w-c0, h-r0
        box_[2], box_[3]  = w, h
    
    frame = bounding_box( img, box_ )
    inI, outI, edge, pixal = helper.process_frame(frame)
    cv2.imshow('Eye', np.concatenate((frame, outI)))
    cv2.waitKey( 1 )

    tvec_.append(t); y1_.append(edge); y2_.append(pixal)

    tA, bA = [0], [0]
    if i % int(fps_*0.1) == 0:
        data_ = np.array((tvec_, y1_)).T
        try:
            tA, bA = extract.find_blinks_using_edge(data_[:,:])
        except Exception as e:
            print('[WARN] Failed to detect blink data using egdes in frame %s' % i)
            tA, bA = [0], [0]

    try:
        gplt.plot(
                (np.array(tvec_[-1000:]), np.array( y1_[-1000:] ))
                , title = 'Blink detection. Running window 1000 frames'
                , terminal = 'x11'
                )
    except Exception as e:
        pass

def get_blinks( ):
    global args_
    global box_
    box_ = [ int(x) for x in args_.box.split( ) ]
    i = 0
    frames = tifffile.imread( args_.tiff_file )
    for i, frame in enumerate( frames ):
        animate( i, frame )

def close_all( ):
    pass

def main():
    get_blinks()

if __name__ == '__main__':
    import argparse
    # Argument parser.
    description = '''Detect eyeblink in live camera feed'''
    parser = argparse.ArgumentParser(description=description)
    parser.add_argument('--tiff-file', '-f'
        , required = True
        , type = str
        , help = 'Tiff file of recording.'
        )
    parser.add_argument('--box', '-b'
        , required = False
        , default = '0 0 -1 -1'
        , help = 'bounding box: x0 y0 widht height'
        )
    class Args: pass 
    args = Args()
    parser.parse_args(namespace=args)
    args_ = args
    try:
        main( )
    except KeyboardInterrupt as e:
        print('[INFO] Keyboard interrupt.Quitting')
        close_all()
        quit()

