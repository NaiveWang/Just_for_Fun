 
from urllib import request
import sqlite3
source=[#source, limit, xpath
    ['http://sousuo.gov.cn/column/30613/#.htm', 1314, '/html/body/div[2]/div/div[2]/div[2]/ul/li/h4/a'],
    ['http://sousuo.gov.cn/column/30902/#.htm', 1787, '/html/body/div[2]/div/div[2]/div[2]/ul/li/h4/a'],
    ['http://sousuo.gov.cn/column/30618/#.htm', 95, '/html/body/div[2]/div/div[2]/div[2]/ul/li/h4/a'],
    ['http://sousuo.gov.cn/column/31421/#.htm', 1122, '/html/body/div[2]/div/div[2]/div[2]/ul/li/h4/a'],
    ['http://sousuo.gov.cn/column/30611/#.htm', 5181, '/html/body/div[2]/div/div[2]/div[2]/ul/li/h4/a'],
    ['http://sousuo.gov.cn/column/30619/#.htm', 6, '/html/body/div[2]/div/div[2]/div[2]/ul/li/h4/a']
    ]
db=sqlite3.connect('gov.db')
c=db.cursor()
for channel in source:
    for i in range(channel[1]):
        c.execute('insert into source(url, xpath)values(?, ?)', (channel[0].replace('#', str(i)), channel[2]))
        print(channel[0].replace('#', str(i)))
