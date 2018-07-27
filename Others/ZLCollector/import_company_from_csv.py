# python3.5
import sqlite3
fname = input("Input file name>>>")
f=open(fname,"r")
ldb=sqlite3.connect("company.db3")
c=ldb.cursor()
while 1:
    line = f.readline()
    if line:
        line = line.split('\n')[0].split("$")
        if len(line[0])>3:
            try:
                c.execute("insert into company_info(company_name,company_address,batch) values('%s','%s',1)"%(line[0],line[1]))
            except sqlite3.IntegrityError:
                continue
    else:
        break
ldb.commit()
ldb.close()
f.close()
