 
import Jetson.GPIO as GPIO
import time
#import random


d_map=[
[0x60,0x90,0x90,0x90,0x90,0x90,0x60,0x00],
[0x20,0x60,0x20,0x20,0x20,0x20,0x20,0x00],
[0x60,0x90,0x10,0x20,0x40,0x80,0xF0,0x00],
[0x60,0x90,0x10,0x20,0x10,0x90,0x60,0x00],
[0x80,0xA0,0xA0,0xF0,0x20,0x20,0x20,0x00],
[0xF0,0x80,0x80,0x60,0x10,0x90,0x60,0x00],
[0x60,0x90,0x80,0xE0,0x90,0x90,0x60,0x00],
[0xF0,0x10,0x20,0x40,0x40,0x40,0x40,0x00],
[0x60,0x90,0x90,0x60,0x90,0x90,0x60,0x00],
[0x60,0x90,0x90,0x70,0x10,0x90,0x60,0x00],
[0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00],
[0x00,0x10,0x20,0x70,0x10,0x10,0x10,0x10],
[0x80,0x40,0x20,0x70,0x40,0x40,0x40,0xc0],
[0x00,0x10,0x30,0x70,0x10,0x10,0x10,0x10],
[0x80,0xc0,0xe0,0xf0,0xc0,0xc0,0xc0,0xc0],
[0x10,0x10,0x10,0x10,0x70,0x20,0x10,0x00],
[0xc0,0x40,0x40,0x40,0x70,0x20,0x40,0x80],
[0x10,0x10,0x10,0x10,0x70,0x30,0x10,0x00],
[0xc0,0xc0,0xc0,0xc0,0xf0,0xe0,0xc0,0x80]]


din=13
cs=12
clk=11




def WriteB(byte):
    for i in range(0,8):
        GPIO.output(clk,GPIO.LOW)
        
        if byte & 0x80 == 0x80:
            GPIO.output(din,GPIO.HIGH)
        else:
            GPIO.output(din,GPIO.LOW)
        
        byte=byte<<1
        GPIO.output(clk,GPIO.HIGH)
def WritehB(byte):
    for i in range(0,4):
        GPIO.output(clk,GPIO.LOW)
        
        if byte & 0x80 == 0x80:
            GPIO.output(din,GPIO.HIGH)
        else:
            GPIO.output(din,GPIO.LOW)
        
        byte=byte<<1
        GPIO.output(clk,GPIO.HIGH)
def init():
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(din,GPIO.OUT,initial=GPIO.LOW)
    GPIO.setup(cs,GPIO.OUT,initial=GPIO.LOW)
    GPIO.setup(clk,GPIO.OUT,initial=GPIO.LOW)
    
    GPIO.output(cs,GPIO.LOW)

    WriteB(0x09)
    WriteB(0x00)
    WriteB(0x09)
    WriteB(0x00)
    WriteB(0x09)
    WriteB(0x00)
    WriteB(0x09)
    WriteB(0x00)
    GPIO.output(cs,GPIO.HIGH)

    GPIO.output(cs,GPIO.LOW)

    WriteB(0x0a)
    WriteB(0x03)
    WriteB(0x0a)
    WriteB(0x03)
    WriteB(0x0a)
    WriteB(0x03)
    WriteB(0x0a)
    WriteB(0x03)
    GPIO.output(cs,GPIO.HIGH)

    GPIO.output(cs,GPIO.LOW)

    WriteB(0x0b)
    WriteB(0x07)
    WriteB(0x0b)
    WriteB(0x07)
    WriteB(0x0b)
    WriteB(0x07)
    WriteB(0x0b)
    WriteB(0x07)
    GPIO.output(cs,GPIO.HIGH)

    GPIO.output(cs,GPIO.LOW)

    WriteB(0x0c)
    WriteB(0x01)
    WriteB(0x0c)
    WriteB(0x01)
    WriteB(0x0c)
    WriteB(0x01)
    WriteB(0x0c)
    WriteB(0x01)
    GPIO.output(cs,GPIO.HIGH)

    GPIO.output(cs,GPIO.LOW)

    WriteB(0x0f)
    WriteB(0x00)
    WriteB(0x0f)
    WriteB(0x00)
    WriteB(0x0f)
    WriteB(0x00)
    WriteB(0x0f)
    WriteB(0x00)
    GPIO.output(cs,GPIO.HIGH)

#GPIO.output(cs,GPIO.LOW)
#WriteB(1)
#WriteB(0xff)
#GPIO.output(cs,GPIO.HIGH)
#input()
def show(p, trend):
    d3=int(p//100)
    d2=int(p//10)%10
    d1=int(p//1)%10
    d_1=int(p//.1)%10
    d_2=int(p//.01)%10
    for i in range(0,8):
        GPIO.output(cs,GPIO.LOW)
        
        WriteB(i+1)
        #WriteB(0xff);
        if d3==0:
            WritehB(0)
        else:
            WritehB(d_map[d3][i])    
        

        WritehB(d_map[d2][i])

        WriteB(i+1)
        #WriteB(0xff);
        WritehB(d_map[d1][i])
        WritehB(d_map[10][i])
        WriteB(i+1)
        #WriteB(0xff);
        WritehB(d_map[d_1][i])
        WritehB(d_map[d_2][i])
        WriteB(i+1)
        #WriteB(0xff);
        if trend >= 0.1:
            WritehB(d_map[13][i])
            WritehB(d_map[14][i])
        elif trend > 0:
            WritehB(d_map[11][i])
            WritehB(d_map[12][i])
        elif trend <= -0.1:
            WritehB(d_map[17][i])
            WritehB(d_map[18][i])
        else:
            WritehB(d_map[15][i])
            WritehB(d_map[16][i])
        GPIO.output(cs,GPIO.HIGH)

#show(23.11,True)

#print('done')

#GPIO.cleanup()
