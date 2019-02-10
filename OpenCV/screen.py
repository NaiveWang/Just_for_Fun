import pyscreenshot as ImageGrab
import time
import numpy as np
import cv2
from PyQt5.QtWidgets import QApplication
import sys


#import matplotlab.pyplot as plt
#import gi
#gi.require_version('Gtk', '3.0')
#from gi.repository import Gtk as gtk

#gtk.g_idle_add()

#import wx
#wx.App()

face_csc = cv2.CascadeClassifier('haarcascade_upperbody.xml')

app = QApplication(sys.argv)
screen = QApplication.primaryScreen()
while True:


    raw = screen.grabWindow(0, 0, 0, 100, 100).toImage()
    #print(type(raw))
    #raw = ImageGrab.grab()
    #print(type(raw))
    print('@')
    img = np.array(raw)
    print('@@')
    frame = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    print('@@@')
    faces = face_csc.detectMultiScale(frame, 1.1, 4)
    print('@@@')
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x,y), (x+w, y+h), (0,0,0), 5)
    print('@@@@')
    cv2.imshow("frame", frame)
    print('@@@@@')
    cv2.waitKey(50)
    print('@@@@@@')


    #time.sleep(1)
