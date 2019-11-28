import sqlite3
db = sqlite3.connect("fc.db3")
c= db.cursor()
c.execute('select count (*) from `3k_punk_list`where status=0')
A=c.fetchone()
print('>>>>>>',A[0])
c.execute('select id,front,back from `3k_punk_list`where status=0 order  by random()')

l=c.fetchall()
i=0
j=0
for r in l:
    print(">>>"+r[1])
    input()
    print(r[2])
    key=input()
    if key == 'y':
        c.execute('update `3k_punk_list` set status=1 where id=%s'%r[0])
        i+=1
        db.commit()
    j+=1
    if j%100==0:
        print('short break at',j)
