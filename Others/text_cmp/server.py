#python3
from flask import Flask, render_template, request
import sqlite3
import jar_wrapper as jw

app = Flask(__name__)

ins=''

def get_cmp_result(src,dst):
    return jw.cmp_post(src, dst)

    #print(rtn)
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
@app.route('/', methods=['GET'])
def root_get():
    global ins
    db = sqlite3.connect("base")
    c = db.cursor()
    c.execute("select id,title,company from post")
    tri=c.fetchall()
    c.close()
    db.close()
    return render_template('hub.html', tri=tri)

@app.route("/", methods=['POST'])
def root_post():
    global ins
    db = sqlite3.connect("base")
    cr = db.cursor()
    if 'getall' in request.form:
        # generate excuusive form
        src = request.form['src0']
        # print(src)
        cr.execute("select id,title,company from post where id!=%s"%src)
        _tri=cr.fetchall()
        rst = []
        tri=[]
        for e in _tri:
            rst.append(e[0])
        srcl, rst = jw.cmp_post_batch(src, rst)
        
        for etri, erst in zip(_tri,rst):
            e = []
            e.append(etri[0])
            e.append((100*erst/srcl).__str__()+"% "+etri[1])
            e.append(etri[2])
            tri.append(e)
        
        
        
        
    elif 'getfiltered' in request.form:
        
        t = request.form['t']
        c = request.form['c']
        src = request.form['src1']
        
        
        # print("select id,title,company from post where title like '%%%s%%' and company like '%%%s%%'"%(t, c))
        cr.execute("select id,title,company from post where title like '%%%s%%' and company like '%%%s%%'"%(t, c))
        _tri=cr.fetchall()
        tri = []
        rst = []
        for e in _tri:
            rst.append(e[0])
        srcl, rst = jw.cmp_post_batch(src, rst)
        
        for etri, erst in zip(_tri,rst):
            e = []
            e.append(etri[0])
            e.append((100*erst/srcl).__str__()+"% "+etri[1])
            e.append(etri[2])
            tri.append(e)
    elif 'instance' in request.form:
        t = request.form['t']
        c = request.form['c']
        csize = request.form['cksz']
        ins = request.form['ists']
        
        cr.execute("select id,title,company from post where title like '%%%s%%' and company like '%%%s%%'"%(t, c))
        _tri=cr.fetchall()
        rst = []
        tri = []
        src='$'+csize+'$'+ins
        for e in _tri:
            rst.append(e[0])
        lil, li, dstv, dstc = jw.cmp_instance_batch(ins, csize, rst)
        
        for etri, erst in zip(_tri,dstc):
            e = []
            e.append(etri[0])
            e.append((100*erst/lil).__str__()+"% "+etri[1])
            e.append(etri[2])
            tri.append(e)
        
    cr.close()
    
    db.close()
    return render_template('hub.html', tri=tri, src=src, ins=ins)
@app.route("/cmp", methods=['GET'])
def cmp_get():
    dst = request.args.get('src')
    src = request.args.get('dst')
    db = sqlite3.connect("base")
    c = db.cursor()
    print(src)
    if '$' in src:
        
        csize=src.split('$',2)[1]
        src=src.split('$',2)[-1]
        # print(">>>"+csize, src)
        lil, li, match, matchc = jw.cmp_instance(src, csize, dst)
        print(match)
        # we assume auto increament starts from 1
        if match != False:
            match=sorted(match, key=lambda tup: tup[4], reverse=True)
        
        blocks_src = []
        
        c_total=0
        c_overlap=0
        _c_total=0
        _c_overlap=0
        cnt=1
        for _r in li:
            # r : seq : id content
            elm=[]
        
            # seq : pos len text
        
            result, i = find_match(match,cnt,0)
            if result!=False :
                elm.append(result[1]) # position
                elm.append(result[4]) # length
                c_overlap+=result[4]
                #print(result[4], i)
                elm.append(_r) # string
                elm.append(i) # overlap id
            else:
                elm.append(-1)
                elm.append(-1)
                elm.append(_r)
                elm.append(i)
            c_total+=len(_r)
                
            blocks_src.append(elm)
            cnt+=1
            
    else:
        match = get_cmp_result(dst,src)
        # penta : src(id,pos) dst(id,pos) length
        if match != False:
            match=sorted(match, key=lambda tup: tup[4], reverse=True)
        
        
        c.execute("select id,content from content where pid=%s"%src)
        r=c.fetchall()
        
        blocks_src = []
        
        c_total=0
        c_overlap=0
        _c_total=0
        _c_overlap=0
        
        for _r in r:
            # r : seq : id content
            elm=[]
        
            # seq : pos len text
        
            result, i = find_match(match,_r[0],0)
            if result!=False :
                elm.append(result[1]) # position
                elm.append(result[4]) # length
                c_overlap+=result[4]
                #print(result[4], i)
                elm.append(_r[1]) # string
                elm.append(i) # overlap id
            else:
                elm.append(-1)
                elm.append(-1)
                elm.append(_r[1])
                elm.append(i)
            c_total+=len(_r[1])
                
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
            _c_overlap+=result[4]
            #print('>',result[4])
        else:
            elm.append(-1)
            elm.append(-1)
            elm.append(_r[1])
            elm.append(i)
        #print(">>>",_c_overlap, _c_total, len(_r[1]),_r[1])
        _c_total+=len(_r[1])
        #print(_c_overlap, _c_total, len(_r[1]),_r[1])
        #print(_c_total,_c_overlap)
        blocks_dst.append(elm)
        
    c.close()
    db.close()
    return render_template('cmp.html',blocks_src=blocks_src,blocks_dst=blocks_dst,
                            c_t=c_total,c_o=c_overlap,_c_t=_c_total,_c_o=_c_overlap)
        
@app.route("/cmp", methods=['POST'])

def cmp_post():
    
    src = request.form['src']
    dst = request.form['dst']
    #print(src,dst)
    db = sqlite3.connect("base")
    c = db.cursor()
    
    #print(len(block_src))
    
    
    
    match = get_cmp_result(dst,src)
    # penta : src(id,pos) dst(id,pos) length
    if match != False:
        match=sorted(match, key=lambda tup: tup[4], reverse=True)
    
    
    c.execute("select id,content from content where pid=%s"%src)
    r=c.fetchall()
    
    blocks_src = []
    
    c_total=0
    c_overlap=0
    _c_total=0
    _c_overlap=0
    
    for _r in r:
        # r : seq : id content
        elm=[]
       
        # seq : pos len text
       
        result, i = find_match(match,_r[0],0)
        if result!=False :
            elm.append(result[1]) # position
            elm.append(result[4]) # length
            c_overlap+=result[4]
            #print(result[4], i)
            elm.append(_r[1]) # string
            elm.append(i) # overlap id
        else:
            elm.append(-1)
            elm.append(-1)
            elm.append(_r[1])
            elm.append(i)
        c_total+=len(_r[1])
            
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
            _c_overlap+=result[4]
            #print('>',result[4])
        else:
            elm.append(-1)
            elm.append(-1)
            elm.append(_r[1])
            elm.append(i)
        #print(">>>",_c_overlap, _c_total, len(_r[1]),_r[1])
        _c_total+=len(_r[1])
        #print(_c_overlap, _c_total, len(_r[1]),_r[1])
        #print(_c_total,_c_overlap)
        blocks_dst.append(elm)
    
    c.close()
    db.close()
    return render_template('cmp.html',blocks_src=blocks_src,blocks_dst=blocks_dst,
                           c_t=c_total,c_o=c_overlap,_c_t=_c_total,_c_o=_c_overlap)
    
@app.route("/conf", methods=['GET'])
def conf_get():
    db = sqlite3.connect("base")
    c = db.cursor()
    c.execute("select id,title,company,is_split from post")
    quad=c.fetchall()
    c.close()
    db.close()
    return render_template('conf.html', quad=quad)
@app.route("/conf", methods=['POST'])
def conf_post():
    db = sqlite3.connect("base")
    c = db.cursor()
    #do the job here
    
    if 'genB' in request.form:
        #print('genB')
        jw.gen_block()
    elif 'genC' in request.form:
        #print('genC')
        csize = request.form['csize']
        jw.gen_chunk(csize)
        
    elif 'delC' in request.form:
        #print('delC')
        c.execute("delete from chunks")
        c.execute("update content set is_chunk_ready=0")
        db.commit()
    elif 'delP' in request.form:
        #print('delP')
        pid = request.form['pid']
        c.execute("delete from post where id=%s"%pid)
        c.execute("delete from content where pid=%s"%pid)
        db.commit()
    elif 'newP' in request.form:
        #print('newP')
        title = request.form['a_t']
        comp = request.form['a_c']
        blah = request.form['blah']
        c.execute("insert into post(title, company, blah)values('%s','%s','%s')"%(
            title, comp, blah))
        db.commit()
    
    c.execute("select id,title,company,is_split from post")
    quad=c.fetchall()
    c.close()
    db.close()
    return render_template('conf.html', quad=quad)
    
if __name__ == "__main__":
    app.run(debug=False)
