import sqlite3
import json
import re
#import matplotlib.pyplot as plt

z='[0-9a-zA-Z]{6,}'
ze='C[0-9a-zA-Z]{2,}'
f=open('o.txt', 'a')
'''
    This scripts will extract the raw page/json file into columns,
    with title and contents.
'''
x=[]
y=[]

db=sqlite3.connect('toutiao.db')
c=db.cursor()
c.execute('select id, raw, tag from news where raw like " {%" and tag <> "forum_post" and tag in (select b from (select count(*) as a, tag as b from news where raw like " {%" group by tag) where a > 500) order by random()')
rs=c.fetchall()
for r in rs:
    co=r[1].split('\'.slice(6, -6),')[1].split('content: \'', 1)[-1]
    co=co.replace('&quot;', '').replace(' ', '').replace('\n', '').replace('\t', '').replace('strong', '').replace('div', '')
    #co=co.encode().decode('utf-8', 'ignore')
    tmps=co.split('\\u')
    co=tmps[0]
    for tmp in tmps[1:]:
        co+=tmp[3:]
    co=co.replace('&#x3D;' ,'').replace('\\inline', '').replace('\\', '').replace(':', '').replace('.','').replace('-','').replace('_','')
    co=re.sub(z, '', co)
    co=re.sub(ze, '', co)
    json.dump({
            'doc_label': [r[2]],
            'doc_token': list(co),
            'doc_keyword': [],
            'doc_topic': []
            }, f, ensure_ascii=False)
    
    #l=len(co)
    print(len(co))
    '''
    if l in x:
        y[x.index(l)]+=1
    else:
        x.append(l)
        y.append(1)
    '''
    f.write('\n')
    
    #exit(0)
#plt.scatter(x, y, s=.1)
#plt.show()
