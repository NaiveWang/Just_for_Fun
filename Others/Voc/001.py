import sqlite3
con=sqlite3.connect('001.db3')
def CREATE():
    conn=sqlite3.connect('001.db3')

    conn.execute('create table voc(id integer primary key AUTOINCREMENT,dat varchar(120) unique,state char(1))')

    conn.close()
def DROP():
    conn = sqlite3.connect('001.db3')

    conn.execute('drop table voc')

    conn.close()

def INSERT(s):
    con.execute('insert into voc(dat,state)values(\''+s+'\',0)')
    con.commit()
def VIEW():
    conn = sqlite3.connect('001.db3')

    c=conn.cursor()
    for row in c.execute("SELECT * FROM voc"):
        print(row[1]+" ")
        if row[2]=='0':
            print("\tNAIVE\n")
        else:
            print("\tGOT IT\n")


    conn.close()
def getQ():
    conn = sqlite3.connect('001.db3')

    c=conn.cursor()
    c.execute("SELECT count(id) from voc")
    f=c.fetchone()
    #print(f)

    conn.close()
    return f[0]
#INSERT('a')
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


con.close()