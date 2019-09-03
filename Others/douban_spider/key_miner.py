import pysqlite3

db = pysqlite3.connect('douban')

c=db.cursor()

c.execute('select text from zhengyoudahui')

rz = c.fetchall()

blocker=['，','；','。','.','…',',',':','-','：','、',' ']





for l in range(2,8):
    v={}
    for i in range(0,len(rz)):
        print("Processing",i,"of",len(rz))
        blockz = rz[i][0].split('\n')
        for block in blockz:
            if len(block) >= l:
                for j in range(0,len(block)-l+1):
                    elm=block[j:j+l]
                    if elm in v:
                        # already have one, change value
                        v[elm]+=1
                    else:
                        for bb in blocker:
                            if bb in elm:
                                break
                        else:
                            v[elm]=1
    print('writing result into database...')

    for key, feq in v.items():
        c.execute('insert into key(key,feq)values("%s",%d)'%(key,feq))
db.commit()
