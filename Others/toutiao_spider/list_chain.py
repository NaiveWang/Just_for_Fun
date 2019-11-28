from urllib import request
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
for col in colz:
    #req = request.Request(col[0].replace(hotkey_stale, hotkey), headers=headerz)
    for i in range(100):
        is_closure=True
        
        req = request.Request(col[0].replace('0', str(time.time()-random.randint(0, 100000))), headers=headerz)
        rep = request.urlopen(req)
        kookie=rep.getheader('set-cookie')
        
        #headerz['Cookie'] = kookie
        
        print(rep.getcode(), col[1], kookie), 
        jraw = gzip.decompress(rep.read())
        j = json.loads(jraw.decode('utf-8', 'ignore'))
        # get id list
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
        
        #time.sleep(1.2)
        if is_closure is True:
            break
