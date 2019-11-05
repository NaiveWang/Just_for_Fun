'''
    This scripts will export raw text from local sqlite database to a raw corpus text
    specially, this is for google's sentensepiece unsupervised tokenlizer
'''
# connect to local db file
import sqlite3

db = sqlite3.connect('20191031-1446.db')
c=db.cursor()
# initial corpus file
o=open('douban.corpus', 'w')
# export post raw
c.execute('select text from post')
rs = c.fetchall()
def text_process(raw):
    raw = raw.replace('。', '\n')
    raw = raw.replace(' ', '')
    raw = raw.replace('\t', '')
    raw = raw.replace(' ', '')
    raw = raw.replace('\r', '')
    x=0
    while x < len(raw):
        x=len(raw)
        raw = raw.replace('\n\n', '\n')
    return raw

for r in rs:
    if len(r[0]) > 0 and r[0] != '\n':
        raw = text_process(r[0])
        o.write(raw)
        if raw[-1] != '\n':
            o.write('\n')
# export commit raw
c.execute('select text from comments')
rs = c.fetchall()
for r in rs:
    if len(r[0]) > 0 and r[0] != '\n':
        raw = text_process(r[0])
        
        o.write(raw)
        if raw[-1] != '\n':
            o.write('\n')
o.close()
# save file
