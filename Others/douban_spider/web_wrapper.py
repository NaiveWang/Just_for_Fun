'''
    a small single user post rating system
    specifically, this web server is dedicated to apply rating tags to douban posts.
'''
from flask import Flask, render_template, make_response, request
import json
import sqlite3
import tf_idf
app = Flask(__name__)
global a
a=tf_idf.algo('douban.model', 'db.txt.npy')
dbn='20191030-1634.db'
#op : type, name, value
operations = [
    ['submit', '0', '这篇不要了, 再来一篇'], 
    ['submit', '1', '不傻逼'], 
    ['submit', '2', '真傻逼'], 
    ['submit', '3', '真他妈傻逼'],
    ['submit', '4', '操你妈']]
id=-1
post=''

rand_grab='select post.id, post.text, topic.title, user.name, loc.name, user.url_avatar from post, user, topic, loc where post.topic=topic.id and post.author=user.id and user.loc=loc.id order by random()'


@app.route('/', methods=['GET'])
def hub():
    global id, post
    db=sqlite3.connect(dbn)
    c=db.cursor()
    c.execute(rand_grab)
    chosen = c.fetchone()
    c.close()
    db.close()
    id=chosen[0]
    post = chosen[1]

    return render_template('hub.html', operations = operations, content = post, hotkeys = a.i2t(a.key_miner(post.split('\n'))),
                           topic=chosen[2], u=chosen[3:])
@app.route('/', methods=['POST'])
def hub_act():
    global id, post
    db=sqlite3.connect(dbn)
    c=db.cursor()
    if '0' in request.form:
        c.execute('update post set tag=-1 where id=%d'%id)
        #db.commit()
        print(id)
    elif '1' in request.form:
        c.execute('update post set tag=1 where id=%d'%id)
        print(id)
        #db.commit()
    elif '2' in request.form:
        c.execute('update post set tag=2 where id=%d'%id)
        print(id)
        #db.commit()
    elif '3' in request.form:
        c.execute('update post set tag=3 where id=%d'%id)
        print(id)
    elif '4' in request.form:
        c.execute('update post set tag=3 where id=%d'%id)
        of = open('master_dickhead.json', 'a')
        json.dump({
            'id': id,
            'text': post
            }, of, ensure_ascii=False)
        of.write('\n')
    db.commit()
    c.execute(rand_grab)
    chosen = c.fetchone()
    c.close()
    db.close()
    id=chosen[0]
    post = chosen[1]
    return render_template('hub.html', operations = operations, content = post, hotkeys = a.i2t(a.key_miner(post.split('\n'))),
                           topic=chosen[2], u=chosen[3:])
if __name__ == "__main__":
    app.run(debug=False)
    
