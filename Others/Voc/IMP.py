import sqlite3

file="TOEFL.csv"
con = sqlite3.connect("voc.db3")
con1 = sqlite3.connect("CET4.db3")
csr1 = con1.cursor()
try:
    con.execute("drop table voc")
    con.execute("create table voc(id integer primary key AUTOINCREMENT, v varchar(45) unique, m varchar(200),state int, genre int)")
except Exception:
    print('??')


for r in csr1.execute("select * from CET4"):
    con.execute("insert into voc(v,m,state,genre) values('%s','%s',%d,0)"%(r[1],r[2],r[3]))
con.commit()
file=open(file)
for r in file.readlines():
    if r=='\n':
        continue
    r=r.split('#')
    r[1]=r[1]+r[2]
    print(r[0]+'$$$'+r[1])
    try:
        con.execute("insert into voc(v,m,state,genre) values('%s','%s',0,1)"%(r[0],r[1]))
    except Exception:
        continue


con.commit()
con1.close()
con.close()
file.close()