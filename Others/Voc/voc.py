import sqlite3
database="voc.db3"
table="voc"
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
'''
def SCAN():
    conn = sqlite3.connect(database)
    #cconn = sqlite3.connect('CET4.db3')
    c = conn.cursor()
    for row in c.execute("SELECT * FROM %s"%table):
        if (row[3] != 0):
            continue
        print('\n\n\n'+row[0].__str__()+'---'+row[1])
        print('Press ENTER to get meaning.')
        input()
        print(row[2])
        print('\tDid U get it? y to confirm/q to quit/others to mark.')
        i=input()
        if(i=='y'):
            conn.execute("UPDATE %s SET STATE=-1 WHERE id="%table+row[0].__str__())
        elif(i=='q'):
            break
        else:
            conn.execute("UPDATE %s SET STATE=1 WHERE id="%table + row[0].__str__())

    conn.commit()
    conn.close()
def SCAN1():
    conn = sqlite3.connect(database)
    #cconn = sqlite3.connect('CET4.db3')
    c = conn.cursor()
    for row in c.execute("SELECT * FROM %s"%table+' where state <> -1'):
        print('\n\n\n'+row[0].__str__()+'---'+row[1])
        print('Press ENTER to get meaning.')
        input()
        print(row[2])
        print('\tDid U get it? y to confirm/q to quit/others to mark.')
        i=input()
        if(i=='y'):
            conn.execute("UPDATE %s SET STATE=-1 WHERE id="%table+row[0].__str__())
        elif(i=='q'):
            break
        else:
            conn.execute("UPDATE %s SET STATE=1 WHERE id="%table + row[0].__str__())

    conn.commit()
    conn.close()
def EXPO():
    conn=sqlite3.connect(database)
    o=open('n_voc.txt', 'w')
    c=conn.cursor()
    i=1
    for row in c.execute('SELECT * FROM %s'%table+' where state <> -1'):
        o.writelines(i.__str__()+'\t\t'+row[3].__str__()+'\t\t'+row[4].__str__()+'\t\t'+row[1]+'\n')
        i+=1
    o.close()
    conn.close()

SCAN1()
EXPO()