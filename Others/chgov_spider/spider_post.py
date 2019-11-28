from urllib import request
import sqlite3
db=sqlite3.connect('_gov.db')
c=db.cursor()
c.execute('select id, url from posts where tag=0 order by random()')
l=c.fetchall()

for el in l:
    try:
        req = request.Request(el[1])
        #req.set_proxy('0.0.0.0:8964', 'http')
        text=request.urlopen(req).read().decode()
        c.execute('update posts set raw=?, tag=? where id=?',(
            text,
            len(text),
            el[0]
        ))
        db.commit()
        print(len(text))
    except Exception as E:
        print(E)
