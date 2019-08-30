from urllib import request as req
import sqlite3

urlz ="http://dy.chinasarft.gov.cn/shanty.deploy/catalog.nsp?id=0129dffcccb1015d402881cd29de91ec&pageIndex="
dbn=("base.db")
def init_source():
    db=sqlite3.connect(dbn)
    c=db.cursor()
    for i in range 
    db.close()
