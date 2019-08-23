import pymysql
import sqlite3


rdb = pymysql.connect(host='10.6.12.3', user='cd_back', password=pswd, database='caspatent',charset='utf8')
rc=rdb.cursor()

ldb=sqlite3.connect('k.db3')
lc=ldb.cursor()

lc.execute('select * from news_detail')
rz = lc.fetchall()
for r in rc:
    print(r)
