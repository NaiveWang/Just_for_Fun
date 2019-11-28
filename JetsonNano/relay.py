 
import Jetson.GPIO as GPIO
import time

relay=13

GPIO.setmode(GPIO.BOARD)
GPIO.setup(relay,GPIO.OUT,initial=GPIO.LOW)

def r(t):
    time.sleep(t)
    GPIO.output(relay,GPIO.LOW)
    time.sleep(t)
    GPIO.output(relay,GPIO.HIGH)
while True:
    r(1)
    
