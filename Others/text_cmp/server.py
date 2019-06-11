#python3
from flask import Flask, render_template, request
import sqlite3
import os

app = Flask(__name__)


def get_cmp_result(src,dst):
    r=os.popen("java -jar post_cmp.jar %s %s"%(src,dst)).read().split('\n')[0:-1]
    rtn = []
    print(r)
    try:
        for er in r:
            er=er.split(' ',4)
            er[0]=int(er[0])
            er[1]=int(er[1])
            er[2]=int(er[2])
            er[3]=int(er[3])
            er[4]=len(er[4])
            rtn.append(er)
    except Exception as e:
        return False
    print(rtn)
    return rtn
def find_match(match, raw, ds):
    i=0
    if match == False:
        return False, i
    for m in match:
        if m[ds] == raw:
            return m, i
        i+=1
    else:
        return False, i
@app.route('/')
def root_get():
    db = sqlite3.connect("base")
    c = db.cursor()
    c.execute("select id,title,company from post")
    tri=c.fetchall()
    c.close()
    db.close()
    return render_template('hub.html', tri=tri)

@app.route("/cmp", methods=['POST'])

def cmp_post():
    
    src = request.form['src']
    dst = request.form['dst']
    print(src,dst)
    db = sqlite3.connect("base")
    c = db.cursor()
    
    #print(len(block_src))
    
    
    
    match = get_cmp_result(dst,src)
    # penta : src(id,pos) dst(id,pos) length
    
    
    
    c.execute("select id,content from content where pid=%s"%src)
    r=c.fetchall()
    
    blocks_src = []
    
    for _r in r:
        # r : seq : id content
        elm=[]
       
        # seq : pos len text
       
        result, i = find_match(match,_r[0],0)
        if result!=False :
            elm.append(result[1])
            elm.append(result[4])
            print(result[4], i)
            elm.append(_r[1])
            elm.append(i)
        else:
            elm.append(-1)
            elm.append(-1)
            elm.append(_r[1])
            elm.append(i)
            
        blocks_src.append(elm)
        
    
    
    c.execute("select id,content from content where pid=%s"%dst)
    r=c.fetchall()
    
    blocks_dst = []
    
    for _r in r:
        # r : seq : id content
        elm=[]
       
        # seq : pos len text
        result, i = find_match(match,_r[0],2)
        if result!=False :
            elm.append(result[3])
            elm.append(result[4])
            elm.append(_r[1])
            #print(elm)
            elm.append(i)
        else:
            elm.append(-1)
            elm.append(-1)
            elm.append(_r[1])
            elm.append(i)
            
        blocks_dst.append(elm)
    
    c.close()
    db.close()
    return render_template('cmp.html',blocks_src=blocks_src,blocks_dst=blocks_dst)
    

if __name__ == "__main__":
    app.run(debug=False)
