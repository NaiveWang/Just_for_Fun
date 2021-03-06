 
import numpy as np
import cv2
import imageio
#from PIL import Image, GifImagePlugin

fourcc = cv2.VideoWriter_fourcc(*'MJPG')

lm = imageio.mimread('lm_low.gif')

out = cv2.VideoWriter('output', fourcc, 20, (640, 480))

cap = cv2.VideoCapture(0)

face_csc = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
f_cnt=0
while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()
    f_cnt+=1
    f_cnt%=len(lm)
    
    faces = face_csc.detectMultiScale(frame, 1.1, 4)
    for (x, y, w, h) in faces:
        buff = cv2.resize(cv2.cvtColor(lm[f_cnt],cv2.COLOR_BGRA2RGB),(0,0),fx=w/252,fy=h/252)
        #print("Captured new face rendering with laughing man:",x,y,x+w,y+h)
        frame[y:y+h, x:x+w] = buff
        
        
    cv2.imshow('stand alone complex',frame)
    out.write(frame)
    if cv2.waitKey(1) & 0xff == ord('q'):
        break
    
cap.release()
out.release()
cv2.destroyAllWindows()
