'''
    a small single user post rating system
    specifically, this web server is dedicated to apply rating tags to douban posts.
'''
from flask import Flask, render_template, make_response, request
import json
import sqlite3
app = Flask(__name__)

dbn='douban'
#op : type, name, value
operations = [
    ['submit', '0', '这篇不要了, 再来一篇'], 
    ['submit', '1', '不傻逼'], 
    ['submit', '2', '真傻逼'], 
    ['submit', '3', '真他妈傻逼'],
    ['submit', '4', '操你妈']]
id=-1
post=''
@app.route('/', methods=['GET'])
def hub():
    global id, post
    db=sqlite3.connect(dbn)
    c=db.cursor()
    c.execute('select id, text from zhengyoudahui where tag=0 order by random()')
    chosen = c.fetchone()
    c.close()
    db.close()
    id=chosen[0]
    post = chosen[1]
    return render_template('hub.html', operations = operations, content = post)
@app.route('/', methods=['POST'])
def hub_act():
    global id, post
    db=sqlite3.connect(dbn)
    c=db.cursor()
    if '0' in request.form:
        c.execute('update zhengyoudahui set tag=-1 where id=%d'%id)
        #db.commit()
        print(id)
    elif '1' in request.form:
        c.execute('update zhengyoudahui set tag=1 where id=%d'%id)
        print(id)
        #db.commit()
    elif '2' in request.form:
        c.execute('update zhengyoudahui set tag=2 where id=%d'%id)
        print(id)
        #db.commit()
    elif '3' in request.form:
        c.execute('update zhengyoudahui set tag=3 where id=%d'%id)
        print(id)
    elif '4' in request.form:
        c.execute('update zhengyoudahui set tag=3 where id=%d'%id)
        of = open('master_dickhead.json', 'a')
        json.dump({
            'id': id,
            'text': post
            }, of, ensure_ascii=False)
        of.write('\n')
    db.commit()
    c.execute('select id, text from zhengyoudahui where tag=0 order by random()')
    chosen = c.fetchone()
    c.close()
    db.close()
    id=chosen[0]
    post = chosen[1]
    return render_template('hub.html', operations = operations, content = post)
if __name__ == "__main__":
    app.run(debug=False)
