import requests
import os.path
import sqlite3
import time
#import re
#reg='https://[.-z]*.jpg'
#text=open('merged.json').read()

#m=re.findall(reg, text)
db=sqlite3.connect('20191031-1446.db')
c=db.cursor()
c.execute('select url from img order by random()')
m=c.fetchall()
sess=requests.Session()
for em in m:
    local = em[0].replace('/', '_').replace('https:__', 'img/')
    if os.path.isfile(local):
        continue
        #print('skipping', em)
    else:
        try:
            ctime=time.time()*1000
            print('grabbing', em[0], end=' > ')
            req = sess.get(em[0])
            if req.status_code == 200:
                with open(local, 'wb') as f: f.write(req.content)
                print('finished', time.time()*1000-ctime)
            else:
                print('failed, response code :', req.status_code)
        except Exception as e:
            print(e)
