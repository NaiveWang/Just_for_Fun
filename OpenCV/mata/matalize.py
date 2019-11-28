import numpy as np
import cv2
import glob


face_csc = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
mata = cv2.imread("mata.jpeg")

list = glob.glob('豆瓣话题 - 豆瓣征友大会_files/*.jpg')
#print(list)
for image_file in list:
    douche = cv2.imread(image_file)
    faces = face_csc.detectMultiScale(douche, 1.1, 4)
    for (x, y, w, h) in faces:
        #slice = np.zeros((lm.height, lm.width))
        buff = cv2.resize(mata,(0,0),fx=w/153,fy=h/198)
        #cv2.rectangle(frame, (x,y), (x+h, y+h), (0,0,0), 5)
        douche[y:y+h, x:x+w] = buff
    # cv2.imshow('傻逼们',douche)
    print(image_file)
    cv2.imwrite(image_file, douche)
    # cv2.waitKey(10)
