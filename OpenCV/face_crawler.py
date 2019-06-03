 
import numpy as np
import cv2
import face_recognition
import random
# import subprocess as sp

cctv1='rtsp://60.214.109.103:1554/iptv/Tvod/iptv/001/001/ch12122514263996485740.rsc/47543_Uni.sdp'
cctv3='rtsp://60.214.109.103:1554/iptv/Tvod/iptv/001/001/ch12101814165876183439.rsc/34309_Uni.sdp'
cctv13='rtsp://60.214.109.103:1554/iptv/Tvod/iptv/001/001/ch15050914361303395989.rsc/34350_Uni.sdp'
hunan_weishi='rtsp://60.214.109.103:1554/iptv/Tvod/iptv/001/001/ch12051116352384581471.rsc/34379_Uni.sdp'
dongfang_weishi='rtsp://60.214.109.103:1554/iptv/Tvod/iptv/001/001/ch15050917541568689826.rsc/34393_Uni.sdp'
zhejiang_weishi='rtsp://60.214.109.103:1554/iptv/Tvod/iptv/001/001/ch15050917541521964962.rsc/34319_Uni.sdp'


cap = cv2.VideoCapture('1.mkv')

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

p_image=[]
p_name=[]
count=0
skips=0
while True:
    
    #buf = np.fromstring(vpipe.stdout.read(720*576*3), dtype='uint8').reshape((576,720,3))
    #frame = buf
    ret, frame = cap.read()
    skips+=1
    if skips % 20 == 0:
        frame = cv2.resize(frame, (0,0),fx=0.75,fy=0.75)
        
        face_locations = face_recognition.face_locations(frame)
        face_encodings = face_recognition.face_encodings(frame, face_locations)
        
        for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
            # See if the face is a match for the known face(s)
            matches = face_recognition.compare_faces(p_image, face_encoding)

            name = "NaN"

            # If a match was found in known_face_encodings, just use the first one.
            if True in matches:
                first_match_index = matches.index(True)
                name = p_name[first_match_index]
                
                cv2.imwrite("./pic/"+name+"__"+random.randint(1000000,9999999).__str__()+".jpg",frame[top:bottom,left:right]);
                
            else:
                p_image.append(face_encoding)
                p_name.append(count.__str__())
                count+=1

            # Or instead, use the known face with the smallest distance to the new face
            #face_distances = face_recognition.face_distance(known_face_encodings, face_encoding)
            #best_match_index = np.argmin(face_distances)
            #if matches[best_match_index]:
                #name = known_face_names[best_match_index]

            # Draw a box around the face
            
            cv2.rectangle(frame, (left, top), (right, bottom), (0, 0, 255), 2)

            # Draw a label with a name below the face
            #cv2.rectangle(frame, (left, bottom - 35), (right, bottom), (0, 0, 255), cv2.FILLED)
            cv2.putText(frame, name, (left + 6, bottom - 6), cv2.FONT_HERSHEY_DUPLEX, 1.0, (0, 255, 0), 1)
            cv2.imshow('matalizer',frame)
            cv2.waitKey(1)
    
