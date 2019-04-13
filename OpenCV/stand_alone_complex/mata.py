import numpy as np
import cv2
import imageio

cap = cv2.VideoCapture(0)

face_csc = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")


mata = cv2.imread("mata.jpeg")
#mata:w153,h198

while(True):
    ret, frame = cap.read()
    
    faces = face_csc.detectMultiScale(frame, 1.1, 4)
    for (x, y, w, h) in faces:
        #slice = np.zeros((lm.height, lm.width))
        buff = cv2.resize(mata,(0,0),fx=w/153,fy=h/198)
        #cv2.rectangle(frame, (x,y), (x+h, y+h), (0,0,0), 5)
        print("Captured new face rendering with laughing man:",x,y,x+w,y+h)
        frame[y:y+h, x:x+w] = buff
        
        
    cv2.imshow('frame',frame)
    cv2.waitKey(10)
