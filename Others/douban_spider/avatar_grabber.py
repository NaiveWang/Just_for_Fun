from urllib import request
import os.path
import sqlite3
import time
#import re
#reg='https://[.-z]*.jpg'
#text=open('merged.json').read()

#m=re.findall(reg, text)
db=sqlite3.connect('202002091351.db')
c=db.cursor()
c.execute('select url_avatar from user order by random()')
m=c.fetchall()
for em in m:
    local = em[0].replace('/', '_').replace('https:__', 'img/avatar/')
    if os.path.isfile(local):
        continue
        #print('skipping', em)
    else:
        try:
            ctime=time.time()*1000
            print('grabbing', em[0], end=' > ')
            request.urlretrieve(em[0], local)
            print('finished', time.time()*1000-ctime)
        except Exception as e:
            print(e)
