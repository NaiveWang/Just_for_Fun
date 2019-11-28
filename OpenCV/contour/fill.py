import glob
import cv2
import numpy as np
import os
imgl = glob.glob('data_raw/*/*')
print(os.popen('rm data/*/*').read())
for imgn in imgl:
    img = cv2.imread(imgn)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    imgc = np.copy(img)
    #liquidate curves
    '''
    for y in range(1, img.shape[0]-1):
        for x in range(1, img.shape[1]-1):
            if 1024-(int(img[y, x+1])+int(img[y, x-1])+int(img[y+1, x])+int(img[y-1, x])) >= 768-int(img[y, x])*3:
                    imgc[y, x] = 255

    
    #drop 2-pixel eliminate algo
    for y in range(1, img.shape[0]-2):
        for x in range(0, img.shape[1]):
            if img[y-1, x]>220 and img[y+2, x]>220 and img[y, x]==img[y+1, x]:
                imgc[y+1, x] = imgc[y, x] = 255
    #drop 3-pixel eliminate algo
    for y in range(1, img.shape[0]-3):
        for x in range(0, img.shape[1]):
            if img[y-1, x]>220 and img[y+3, x]>220 and img[y, x]==img[y+1, x]==img[y+2, x]:
                imgc[y+1, x] = imgc[y, x] = 255
    #drop 4-pixel eliminate algo
    for y in range(1, img.shape[0]-4):
        for x in range(0, img.shape[1]):
            if img[y-1, x]>220 and img[y+4, x]>220 and img[y, x]==img[y+1, x]==img[y+2, x]=img[y+3, x]:
                imgc[y+1, x] = imgc[y, x] = 255
                
    '''
    # merged pixel dropping algo
    edge = 225
    core = 180
    for y in range(1, img.shape[0]-4):
        for x in range(0, img.shape[1]):
            if img[y, x] < 200:
                if img[y-1, x]>edge and img[y+4, x]>edge and img[y, x]==img[y+1, x]==img[y+2, x]==img[y+3, x]:
                    imgc[y+1, x] = imgc[y, x] = 255
                if img[y-1, x]>edge and img[y+3, x]>edge and img[y, x]==img[y+1, x]==img[y+2, x]:
                    imgc[y+1, x] = imgc[y, x] = 255
                if img[y-1, x]>edge and img[y+2, x]>edge and img[y, x]==img[y+1, x]:
                    imgc[y+1, x] = imgc[y, x] = 255
    for x in range(0, img.shape[1]):
        if img[y, x] < 200:
            if img[img.shape[0]-2, x]>edge and img[y+3, x]>edge and img[y, x]==img[y+1, x]==img[y+2, x]:
                        imgc[y+1, x] = imgc[y, x] = 255
            if img[img.shape[0]-2, x]>edge and img[y+2, x]>edge and img[y, x]==img[y+1, x]:
                        imgc[y+1, x] = imgc[y, x] = 255
            if img[img.shape[0]-1, x]>edge and img[y+2, x]>edge and img[y, x]==img[y+1, x]:
                        imgc[y+1, x] = imgc[y, x] = 255
    #eliminate stand alone pixel
    img = np.copy(imgc)
    for y in range(1, img.shape[0]-1):
        for x in range(1, img.shape[1]-1):
            if int(img[y, x+1])+int(img[y, x-1])+int(img[y+1, x])+int(img[y-1, x]) == 1020:
                    imgc[y, x] = 255
    # contour contrast increasing
    img = np.copy(imgc)
    '''
    blur = 192
    for y in range(1, img.shape[0]-1):
        for x in range(1, img.shape[1]-1):
            if img[y, x] < 180:
                #imgc[y, x]=0
                
                if img[y-1, x] == 255:
                    imgc[y-1, x] = blur
                    
                if img[y+1, x] == 255:
                    imgc[y+1, x] = blur
                if img[y, x-1] == 255:
                    imgc[y, x-1] = blur
                if img[y, x+1] == 255:
                    imgc[y, x+1] = blur
    '''
    # fill contour
    
    '''
    ret, thresh = cv2.threshold(imgc, 127, 255, 0)
    contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    cv2.drawContours(imgc, contours, 0, (0,255,0), 3)
    '''
    # blur pixel, bind with contrast stapep to improve performance
    print(imgn)
    cv2.imwrite(imgn.replace('_raw', ''), imgc)
