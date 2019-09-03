from urllib import request
import sqlite3
from lxml import html

def jsfree_single(url, xpath, session):
    tree = html.parse(request.urlopen(url))
    return tree.xpath(xpath)

db=sqlite3.connect('gov.db')
c=db.cursor()
c.execute('select id, url, xpath from source where tag=0 order by random()')

l = c.fetchall()
s = requests.Session()
for e in l:
    table = jsfree_single(e[1], e[2])
    print(table)
    for col in table:
        try:
            c.execute('insert into posts(url)values(?)', (col.attrib['href'], ))
        except Exception as e:
            print(e)
    c.execute('update source set tag=? where id=?', (len(table), e[0]))
    db.commit()
