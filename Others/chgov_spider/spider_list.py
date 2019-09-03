from urllib import request
import sqlite3
from lxml import html

headers={
    'Host': 'sousuo.gov.cn',
    'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0',
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
    'Accept-Language': 'en-US,en;q=0.5',
    'Accept-Encoding': 'gzip',
    'Referer': 'http://www.gov.cn/xinwen/gundong.htm',
    'Connection': 'keep-alive',
    'Cookie': '_gscu_603879440=67415523pc5k5815; _gscbrs_603879440=1; acw_tc=2760822c15674155247961023ec217986bbf92d138730c7b591137ee2042ff; _gscs_603879440=t67480437fxu59l16|pv:1',
    'Upgrade-Insecure-Requests': '1',
    'Cache-Control': 'max-age=0'}



def jsfree_single(url, xpath):
    tree = html.parse(request.urlopen(url))
    #tree = html.parse(request.urlopen(request.Request(url, headers=headers)))
    return tree.xpath(xpath)

db=sqlite3.connect('_gov.db')
c=db.cursor()
c.execute('select id, url, xpath from source where tag=0 order by random()')

l = c.fetchall()
for e in l:
    try:
        table = jsfree_single(e[1], e[2])
        print(table)
        for col in table:
            c.execute('insert into posts(url)values(?)', (col.attrib['href'], ))

        c.execute('update source set tag=? where id=?', (len(table), e[0]))
        db.commit()
    except Exception as err:
        print(err)
