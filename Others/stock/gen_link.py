import sqlite3

def gen_company_link():
    db=sqlite3.connect("k.db3")
    c=db.cursor()
    c.execute('select id, market, serial from company')
    lst=c.fetchall()
    for e in lst:
        c.execute('update company set company_link="http://webf10.gw.com.cn/%s/B7/%s%s_B7.html" where id=%d'%(e[1], e[1], e[2], e[0]))
    db.commit()
def gen_admin_link():
    db=sqlite3.connect("k.db3")
    c=db.cursor()
    c.execute('select id, market, serial from company')
    lst=c.fetchall()
    for e in lst:
        c.execute('update company set admin_link="http://webf10.gw.com.cn/%s/B8/%s%s_B8.html" where id=%d'%(e[1], e[1], e[2], e[0]))
    db.commit()
def gen_shareholder_link():
    db=sqlite3.connect("k.db3")
    c=db.cursor()
    c.execute('select id, market, serial from company where market="HK"')
    lst=c.fetchall()
    for e in lst:
        c.execute('update company set shareholder_link="http://webf10.gw.com.cn/%s/B3/%s%s_B3.html" where id=%d'%(e[1], e[1], e[2], e[0]))
    c.execute('select id, market, serial from company where market<>"HK"')
    lst=c.fetchall()
    for e in lst:
        c.execute('update company set shareholder_link="http://webf10.gw.com.cn/%s/B10/%s%s_B10.html" where id=%d'%(e[1], e[1], e[2], e[0]))
    db.commit()
