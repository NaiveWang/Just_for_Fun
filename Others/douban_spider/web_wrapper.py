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
a=tf_idf.algo('tokenlizer/400000/douban_01.model', 'tokenlizer/400000/db.txt.npy')
dbn='20191031-1446.db'
#op : type, name, value
operations = [
    
    ['/static/Neutral.jpg', '0', '一般'], 
    ['/static/Disappointed.jpg', '1', '不强啊'], 
    ['/static/Unhappy.jpg', '2', '垃圾'],
    ['/static/Veryunhappy.jpg', '3', '傻逼'],
    ['/static/Angry.jpg', '4', '真他妈傻逼'],
    ['/static/Satisfied.jpg', '5', '妈了个逼的'],
    ['/static/Happy.jpg', '6', '我日你爹'],
    ['/static/Veryhappy.jpg', '7', '操你妈'],]
id=-1
post=''

rand_grab='select post.id, post.text, topic.title, user.name, loc.name, user.url_avatar from post, user, topic, loc where post.topic=topic.id and post.author=user.id and user.loc=loc.id order by random()'
get_comm='select text,uid,parent_comment_id where pid=?'


@app.route('/', methods=['GET'])
def hub():
    global id, post
    db=sqlite3.connect(dbn)
    c=db.cursor()
    c.execute(rand_grab)
    chosen = c.fetchone()
    id=chosen[0]
    post = chosen[1]
    
    c.execute('select url from img where pid=?', (id,))
    img=c.fetchall()
    #local = em[0].replace('/', '_').replace('https:__', 'static/img/')
    
    c.close()
    db.close()
    return render_template('hub.html', operations = operations, content = post, hotkeys = a.i2t(a.key_miner(post.split('\n'))),
                           topic=chosen[2], u=chosen[3:], imgs=img)
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
    c.execute('select url from img where pid=?', (id,))
    img=c.fetchall()
    c.close()
    db.close()
    return render_template('hub.html', operations = operations, content = post, hotkeys = a.i2t(a.key_miner(post.split('\n'))),
                           topic=chosen[2], u=chosen[3:], imgs=img)
if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000, debug=False)
    
