import sqlite3
import json
'''
    This file imports posts, commits and image links
'''


db=sqlite3.connect('_douban.db')
c=db.cursor()
js=open('merged.json')

def add_post(val):
    try:
        c.execute('insert into post(uri, id, topic, text, comments_count, create_time, like_count)values(?, ?, ?, ?, ?, ?, ?)', val)
    except Exception as e:
        print(e)
def add_comment(val):
    if val[-1] is None:
        # update without parent
        try:
            c.execute('insert into comments(id, pid, uid, text, create_time)values(?, ?, ?, ?, ?)', val[:-1])
        except Exception as e:
            print(e)
    else:
        # udpate with parent id
        try:
            c.execute('insert into comments(id, pid, uid, text, create_time, parent_comment_id)values(?, ?, ?, ?, ?, ?)', val)
        except Exception as e:
            print(e)
def add_image(val):
    try:
        c.execute('insert into img(pid, url)values(?, ?)', val)
    except Exception as e:
        print(e)
for j in js:
    j=json.loads(j)
    if 'status' in j:
        #print(j['status']['text'])
        add_post([j['status']['uri'], int(j['status']['id']), 51644,
                j['status']['text'], j['status']['comments_count'],
                j['status']['create_time'], j['status']['like_count']])
        for comment in j['comments']:
            add_comment([comment['id'], int(j['status']['id']), comment['author']['id'],
                comment['text'], comment['create_time'], comment['parent_comment_id']])

        #print(j['status']['images'])
        for group in j['status']['images']:
            add_image([int(j['status']['id']), group['large']['url']])
            #print()
            #print(group['normal']['url'])

    else:
        #print(j)
        #print(j['title']+'.'+j['abstract'])
        add_post([j['uri'], int(j['id']), 51644,
            j['title']+'.'+j['abstract'], j['comments_count'],
            j['update_time'], j['likers_count']])
        #print(j['comments'])
        #print(j['photos'])
        for group in j['photos']:
            #print(group['src'])
            add_image([int(j['id']), group['src']])
db.commit()
