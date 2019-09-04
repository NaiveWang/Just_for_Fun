from urllib import request
import sqlite3
import json
import gzip
headerz={
"Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
"Accept-Encoding": "gzip, deflate, br",
"Accept-Language": "en-US,en;q=0.5",
"Cache-Control": "max-age=0",
"Connection": "keep-alive",
"Host": "www.toutiao.com",
"TE": "Trailers",
"Upgrade-Insecure-Requests": "1",
"User-Agent": "Mozilla/5.0 (X11; Linux x86_64; rv:69.0) Gecko/20100101 Firefox/69.0"}
db=sqlite3.connect('toutiao.db')
c=db.cursor()
c.execute('select seed from seeds')
colz=c.fetchall()

for col in colz:
    while True:
        hotkey='0'
        hotkey_stale='0'
        is_closure=True
        req = request.Request(col[0].replace(hotkey_stale, hotkey), headers=headerz)
        rep = request.urlopen(req)
        print(rep.getcode())
        jraw = gzip.decompress(rep.read())
        j = json.loads(jraw.decode('utf-8', 'ignore'))
        # get id list
        for newz in j['data']:
            print(newz['item_id'], newz['tag'])
            try:
                c.execute('insert into news(id, tag, title, source)values(?, ?, ?, ?)', (
                    newz['item_id'], newz['tag'], newz['title'], newz['source']
                ))
                db.commit()
                is_closure=False
            except Exception as E:
                print(E)
        if is_closure is True:
            break
        hotkey_stale = hotkey
        hotkey = j['next']['max_behot_time']
