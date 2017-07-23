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

SCAN()
