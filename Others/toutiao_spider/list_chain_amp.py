import requests
import sqlite3
import json
import gzip
import key
import time
import math
import random
headerz={
"Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
"Accept-Encoding": "gzip, deflate, br",
"Accept-Language": "en-US,en;q=0.5",
"Cache-Control": "max-age=0",
"Connection": "keep-alive",
"Host": "www.toutiao.com",
"Cookie": "tt_webid=6730777189916984835; WEATHER_CITY=%E5%8C%97%E4%BA%AC; tt_webid=6730777189916984835; csrftoken=1203577a586351ec44ccc51b100ed58c; s_v_web_id=3d26f78744e5c7d5f2136679b95cfb07; __tasessionId=d23el1ind1568007368379",
"TE": "Trailers",
"Upgrade-Insecure-Requests": "1",
"User-Agent": "Mozilla/5.0 (X11; Linux x86_64; rv:69.0) Gecko/20100101 Firefox/69.0"}
db=sqlite3.connect('toutiao.db')
c=db.cursor()
c.execute('select seed, category from seeds')
colz=c.fetchall()
sess=requests.Session()
kookiez=None
for col in colz:

    for i in range(100):
        is_closure=True
        
        req = sess.get(col[0], headers=headerz, cookies=kookiez)

        kookiez=req.cookies
        
        #headerz['Cookie'] = kookie
        
        print(req.status_code, col[1], kookiez)
        #jraw = req.text
        j = json.loads(req.text)
        # get id list
        #print(j)
        try:
            
            for newz in j['data']:
                try:
                    #print()
                    c.execute('insert into news(id, tag, title, source)values(?, ?, ?, ?)', (
                        newz['item_id'], newz['tag'], newz['title'], newz['source']
                    ))
                    db.commit()
                    is_closure=False
                    print('success :',newz['item_id'], newz['tag'])
                except Exception as E:
                    print('failed :', E)
        except Exception as E:
            print(E, j)
        #time.sleep(1.2)
        if is_closure is True:
            break
