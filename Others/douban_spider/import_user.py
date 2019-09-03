import json
import sqlite3
'''
this script import user and loc to local database
'''
db=sqlite3.connect('_douban.db')
c=db.cursor()
js=open('merged.json')
def add_user(val):
    try:
        if val[-1] is None:
            c.execute('insert into user(id, uid, name, url_avatar)values(?, ?, ?, ?)',val[:-1])
        else:
            c.execute('insert into user(id, uid, name, url_avatar, loc)values(?, ?, ?, ?, ?)',[val[0], val[1], val[2], val[3], val[-1]['id']])
    except Exception as e:
        print('user:', e)
def add_loc(val):
    try:
        val=val['loc']
        c.execute('insert into loc(id, name, uid)values(?, ?, ?)', (int(val['id']), val['name'], val['uid']))
    except Exception as e:
        print('loc:', e)

for j in js:
    j=json.loads(j)
    #print('\n\n\n',j)
    #id=0
    #uid=''
    #name=''
    #avatar=''
    #loc=0
    if 'status' in j:
        #print(j['status']['author'])
        add_user([int(j['status']['author']['id']),j['status']['author']['uid'],
        j['status']['author']['name'],j['status']['author']['avatar'],
        j['status']['author']['loc']])

        add_loc(j['status']['author'])
        comments=j['comments']
        for comment in comments:
            #print(comment['author'])
            add_user([
                int(comment['author']['id']),
                comment['author']['uid'],
                comment['author']['name'],
                comment['author']['avatar'],
                comment['author']['loc']])
            add_loc(comment['author'])
    else:
        #print(j['author'])
        add_user([
            int(j['author']['id']),
            j['author']['uid'],
            j['author']['name'],
            j['author']['avatar'],
            j['author']['loc']])

        add_loc(j['author'])


db.commit()
