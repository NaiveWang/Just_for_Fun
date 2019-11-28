 
import numpy as np
import cv2
# import subprocess as sp

cctv1='rtsp://60.214.109.103:1554/iptv/Tvod/iptv/001/001/ch12122514263996485740.rsc/47543_Uni.sdp'
cctv3='rtsp://60.214.109.103:1554/iptv/Tvod/iptv/001/001/ch12101814165876183439.rsc/34309_Uni.sdp'
cctv13='rtsp://60.214.109.103:1554/iptv/Tvod/iptv/001/001/ch15050914361303395989.rsc/34350_Uni.sdp'
hunan_weishi='rtsp://60.214.109.103:1554/iptv/Tvod/iptv/001/001/ch12051116352384581471.rsc/34379_Uni.sdp'
dongfang_weishi='rtsp://60.214.109.103:1554/iptv/Tvod/iptv/001/001/ch15050917541568689826.rsc/34393_Uni.sdp'
zhejiang_weishi='rtsp://60.214.109.103:1554/iptv/Tvod/iptv/001/001/ch15050917541521964962.rsc/34319_Uni.sdp'


cap = cv2.VideoCapture(zhejiang_weishi)

face_csc = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
mata = cv2.imread("mata.jpeg")

'''

vpipe = sp.Popen([ "ffmpeg", "-i", cctv3,
           "-loglevel", "quiet", # no text output
           "-an",   # disable audio
           "-f", "image2pipe",
           "-pix_fmt", "bgr24",
           "-vcodec", "rawvideo", "-"],
           stdin = sp.PIPE, stdout = sp.PIPE)

'''

while True:
    
    #buf = np.fromstring(vpipe.stdout.read(720*576*3), dtype='uint8').reshape((576,720,3))
    #frame = buf
    ret, frame = cap.read()
    frame = cv2.resize(frame, (0,0),fx=0.75,fy=0.75)
    faces = face_csc.detectMultiScale(frame, 1.1, 4)
    for (x, y, w, h) in faces:
        #slice = np.zeros((lm.height, lm.width))
        buff = cv2.resize(mata,(0,0),fx=w/153,fy=h/198)
        #cv2.rectangle(frame, (x,y), (x+h, y+h), (0,0,0), 5)
        print("Captured new face rendering with laughing man:",x,y,x+w,y+h)
        frame[y:y+h, x:x+w] = buff
    
    
    cv2.imshow('matalizer',frame)
    cv2.waitKey(10)
    
