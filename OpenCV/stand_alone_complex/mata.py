import numpy as np
import cv2
import imageio
#from PIL import Image, GifImagePlugin

lm = imageio.mimread('lm_low.gif')


cap = cv2.VideoCapture(0)

face_csc = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")


#mata = cv2.imread("mata.jpeg")
#mata:w153,h198
f_cnt=0
while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()
    f_cnt+=1
    f_cnt%=len(lm)
    # Our operations on the frame come here
    # Display the resulting frame
    
    faces = face_csc.detectMultiScale(frame, 1.1, 4)
    for (x, y, w, h) in faces:
        #slice = np.zeros((lm.height, lm.width))
        buff = cv2.resize(cv2.cvtColor(lm[f_cnt],cv2.COLOR_BGRA2RGB),(0,0),fx=w/252,fy=h/252)
        #cv2.rectangle(frame, (x,y), (x+h, y+h), (0,0,0), 5)
        print("Captured new face rendering with laughing man:",x,y,x+w,y+h)
        frame[y:y+h, x:x+w] = buff
        
        
    cv2.imshow('frame',frame)
    cv2.waitKey(10)
