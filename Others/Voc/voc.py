import sqlite3
con=sqlite3.connect("voc.db3")
c=con.cursor()
for r in c.execute("select * from voc"):
    print(r)
con.close()