import sqlite3
con=sqlite3.connect('CET4.db3')
def CREATE():
    conn=sqlite3.connect('CET4.db3')

    conn.execute('create table CET4(id integer primary key AUTOINCREMENT,dat varchar(120) unique,meaning varchar(200),state int)')

    conn.close()
def DROP():
    conn = sqlite3.connect('CET4.db3')

    conn.execute('drop table voc')

    conn.close()

def INSERT(s1,s2):
    try:
        con.execute('insert into CET4(dat,meaning,state)values(\''+s1+'\',\''+s2+'\',0)')
        con.commit()
    except Exception:
        print("already have one")
def VIEW():
    conn = sqlite3.connect('CET4.db3')

    c=conn.cursor()
    for row in c.execute("SELECT * FROM CET4"):
        print(row)


    conn.close()
def getQ():
    conn = sqlite3.connect('CET4.db3')

    c=conn.cursor()
    c.execute("SELECT count(id) from voc")
    f=c.fetchone()
    #print(f)

    conn.close()
    return f[0]
#INSERT('a')
'''
while 1:
    v=input()
    if v=='q':
        break
    try:
        INSERT(v)
    except Exception:
        print("Already Existed")
        continue
    con.commit()
getQ()
VIEW()

f = open('CET4.txt', encoding='GBK')
print(f)
for r in f.readlines():
    #print(r.find(' '))
    #r[r.find(' ')]='#'
    t=r.split(' ',1)
    INSERT(t[0],t[1])
    print(t)

f.close()
'''
con.close()
VIEW()