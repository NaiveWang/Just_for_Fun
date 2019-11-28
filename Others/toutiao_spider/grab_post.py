import sqlite3
from urllib import request
import gzip
headerz={
"Host": "www.toutiao.com",
"User-Agent": "Mozilla/5.0 (X11; Linux x86_64; rv:69.0) Gecko/20100101 Firefox/69.0",
"Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
"Accept-Language": "en-US,en;q=0.5",
"Accept-Encoding": "gzip, deflate, br",
"Connection": "keep-alive",
"Cookie": "tt_webid=6730777189916984835; WEATHER_CITY=%E5%8C%97%E4%BA%AC; tt_webid=6730777189916984835; csrftoken=1203577a586351ec44ccc51b100ed58c; __tasessionId=3mqo7cpex1567581302234",
"Upgrade-Insecure-Requests": "1",
"Cache-Control": "max-age=0"
}
domain='https://www.toutiao.com/a'
db=sqlite3.connect('toutiao.db')
c=db.cursor()
c.execute('select id from news where raw is null')
r=c.fetchall()
for re in r:
    try:
        req = request.Request(domain+str(re[0]), headers=headerz)
        rep = request.urlopen(req)

        text = gzip.decompress(rep.read()).decode().split('articleInfo:', 1)[-1].split('groupId:', 1)[0]+'}'#.replace(',', '}', -1)
        print(rep)
        c.execute('update news set raw=? where id=?', (text, re[0]))
        db.commit()
    except Exception as E:
        print(E)
