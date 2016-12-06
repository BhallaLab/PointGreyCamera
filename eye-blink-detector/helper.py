import cv2
import numpy as np

def process_frame(frame):
    # Find edge in frame
    s = np.mean(frame)
    edges = cv2.Canny(frame, 50, 250)
    cnts = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_TC89_KCOS)
    cntImg = np.ones(frame.shape)
    merge_contours(cnts[0], cntImg)

    # cool, find the contour again and convert again. Sum up their area.
    im = np.array((1-cntImg) * 255, dtype = np.uint8)
    cnts = cv2.findContours(im, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

    hullImg = np.ones(frame.shape)
    res = []
    for c in cnts[0]:
        c = cv2.convexHull(c)
        if accept_contour_as_possible_eye( c ):
            cv2.fillConvexPoly(hullImg, c, 0, 8)
            res.append(cv2.contourArea(c))
    hullImg = np.array((1-hullImg) * 255, dtype = np.uint8)
    return frame, hullImg, sum(res), s
