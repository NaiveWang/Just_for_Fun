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
            c.execute("insert into list1(url)values(?)", (domain+el.split("',", 1)[0].replace('\n1ff8\n', ''), ))
        c.execute("update list0 set tag=1, num=? where id=?", (len(l), e[0], ))
        db.commit()
    db.close()
grab_list()
