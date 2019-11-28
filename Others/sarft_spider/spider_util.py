from urllib import request as req
import sqlite3
from lxml import html

urlz ="http://dy.chinasarft.gov.cn/shanty.deploy/catalog.nsp?id=0129dffcccb1015d402881cd29de91ec&pageIndex="
dbn=("base.db")

xpath_ll='/html/body/div[1]/div[2]/div[2]/div/div[2]/div/div/div[2]/div[2]/ul/li[1]/a'
xpath_l=[
    '/html/body/div[1]/div[2]/div[2]/div/div/div[2]/div[6]/table/tbody/tr/td[2]/a',
    '/html/body/div[1]/div[2]/div[2]/div/div/div[2]/div[7]/table/tbody/tr/td[2]/a',
    '/html/body/div[1]/div[2]/div[2]/div/div/div[2]/div/table/tbody/tr/td[2]/a'
    ]

domain='http://dy.chinasarft.gov.cn'


def jsfree_single(url, xpath, attr):
    tree = html.parse(req.urlopen(url))
    list = tree.xpath(xpath)
    dic={}
    #print(tree)
    for e in list:
        dic[e.text]=e.attrib[attr]
        #print(e.text, e.attrib['href'])
    return dic

def init_source():
    db=sqlite3.connect(dbn)
    c=db.cursor()
    for i in range(0, 26):
        c.execute("insert into source(url)values(?)", (urlz+i.__str__(),))

    db.commit()
    db.close()

def grab_llist():
    db=sqlite3.connect(dbn)
    c=db.cursor()
    c.execute('select id, url from source where tag=0')

    r=c.fetchall()
    for e in r:
        ll=jsfree_single(e[1], xpath_ll, "href")
        for k, v in ll.items():
            c.execute("insert into list0(url)values(?)", (domain+v, ))
        c.execute("update source set tag=1, num=? where id=?", (len(ll), e[0], ))
        db.commit()
    db.close()
def grab_list():
    db=sqlite3.connect(dbn)
    c=db.cursor()
    c.execute('select id, url from list0 where tag=0')

    r=c.fetchall()
    for e in r:
        print(e)
        l = req.urlopen(e[1]).read().decode("ISO-8859-1").split("javascript:window.open('")[1:]
        for el in l:

        #print(jsfree_single(e[1], xpath_l[0], "onclick"))
        #for k, v in ll.items():
            c.execute("insert into list1(url)values(?)", (domain+el.split("',", 1)[0].replace('\r\n915\n\r', ''), ))
        c.execute("update list0 set tag=1, num=? where id=?", (len(l), e[0], ))
        db.commit()
    db.close()
def grab_blah():
    db=sqlite3.connect(dbn)
    c=db.cursor()
    c.execute('select id, url from list1 where tag=0 order by random()')
    r=c.fetchall()
    for e in r:
        print(e)
        #print()
        #for a in tree.xpath('/html/body/div/div/table/tbody/tr/td/table[3]/tbody/tr[2]/td'):
        #    print('>>>', a.text)
        #print(tree.xpath('/html/body/div/div/table/tbody/tr/td/table[3]/tbody/tr[2]/td').text)
        #for a in tree.xpath('/html/body/div/div/table/tbody/tr/td/table[3]/tbody/tr[3]/td/span'):
        #    print(a.text)
        #print(tree.xpath('').text)
        #print(tree.xpath('').text)
        #print(tree.xpath('').text)
        #print(tree.xpath('').text)
        #print(tree.xpath('').text)
        try:
            c.execute('update list1 set tag=1, raw=? where id=?', (req.urlopen(e[1]).read().decode(), e[0]))
            db.commit()
        except Exception as e:
            print(e)
def debug0():
    db=sqlite3.connect(dbn)
    c=db.cursor()
    c.execute('select id, url from list1 where tag=0')
    r=c.fetchall()
    for e in r:
        print(e)
        c.execute('update list1 set url=? where id=?', (e[1].replace('\r\n8f0\r\n', ''), e[0]))
        db.commit()
    c.close()
    db.close()
def truncate():
    db=sqlite3.connect(dbn)
    c=db.cursor()
    c.execute('select id, raw from list1')
    r=c.fetchall()
    for e in r:
        print(e)
        c.execute('update list1 set raw=? where id=?', (e[1].split('<tr align="center">')[-1].split('</table>', 1)[0], e[0]))
        
    db.commit()
    c.close()
    db.close()
def prune(keyword, nkeyword):
    db=sqlite3.connect(dbn)
    c=db.cursor()
    c.execute('select id, raw from list1')
    r=c.fetchall()
    for e in r:
        print(e)
        c.execute('update list1 set raw=? where id=?', (e[1].replace(keyword, nkeyword), e[0]))
        
    db.commit()
    c.close()
    db.close()
def prune_post(keyword, nkeyword):
    db=sqlite3.connect(dbn)
    c=db.cursor()
    c.execute('select id, blah from blah')
    r=c.fetchall()
    for e in r:
        print(e)
        c.execute('update blah set blah=? where id=?', (e[1].replace(keyword, nkeyword), e[0]))
        
    db.commit()
    c.close()
    db.close()
def extract():
    db=sqlite3.connect(dbn)
    c=db.cursor()
    c.execute('select id, raw from list1')
    r=c.fetchall()
    for e in r:
        ee = e[1].split('#$#')[1:]
        col = [
            e[0],
            ee[0].split('</td>', 1)[0],
            ee[1].split('</td>', 1)[0],
            ee[2].split('</td>', 1)[0],
            ee[3].split('</td>', 1)[0],
            ee[4].split('</td>', 1)[0],
            ee[5].split('</td>', 1)[0],
            ee[7].split('</td>', 1)[0]]
        c.execute('insert into blah(id, title, name, company, asshole, result, region, blah)values(?,?,?,?,?,?,?,?)', col)
        #print(col)
    db.commit()
#debug0()
#grab_blah()
## grab_list()
#prune('\n', '')
prune_post('\u3000', '')
