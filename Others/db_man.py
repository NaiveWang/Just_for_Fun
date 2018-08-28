import pymysql
import math
def update_0():
    pswd = input("Input password>>>")
    rdb = pymysql.connect(host='10.6.12.3', user='cd_back', password=pswd, database='gqcxnl',charset='utf8')
    rc = rdb.cursor()
    rc.execute('select id,record_id,name,rank from cxnl_data_new')
    rz = rc.fetchall()
    for r in rz:
        print(r[2])
        if r[3] is None:
            rc.execute('insert into cxnl_log_100(id,record_id,name)VALUES(%s,%s,"%s")'%(
            r[0],r[1],r[2]
            ))
        else:
            rc.execute('insert into cxnl_log_100(id,record_id,name,rank)VALUES(%s,%s,"%s",%s)'%(
            r[0],r[1],r[2],r[3]
            ))
    rdb.commit()
def update_1():
    pswd = input("Input password>>>")
    rdb = pymysql.connect(host='10.6.12.3', user='cd_back', password=pswd, database='gqcxnl',charset='utf8')
    rc = rdb.cursor()
    rc.execute('select id,rank from cxnl_data_new where not isnull(rank)')
    rz = rc.fetchall()
    for r in rz:
        #print(r[2])
        rc.execute('update cxnl_standard_100_0 set rank=%s where id=%s'%(
        r[1],r[0]
        ))
    rdb.commit()
def update_2():
    pswd = input("Input password>>>")
    rdb = pymysql.connect(host='10.6.12.3', user='cd_back', password=pswd, database='gqcxnl',charset='utf8')
    rc = rdb.cursor()

    t = open('combo.csv','r').read().split('\n')
    del(t[-1])
    for r in t:

        r=r.split('$')
        print(r)
        rc.execute('insert into cxnl_rc(name,project,project_rank,company,region)\
        VALUES("%s","%s","%s","%s","%s")'%(
        r[0],r[1],r[2],r[3],r[4]
        ))

    rdb.commit()
def update_3():
    pswd = input("Input password>>>")
    rdb = pymysql.connect(host='10.6.12.3', user='cd_back', password=pswd, database='gqcxnl',charset='utf8')
    rc = rdb.cursor()
    rc.execute('SELECT count(*),company,project_rank FROM gqcxnl.cxnl_rc group by project_rank,company;')
    rz = rc.fetchall()
    for r in rz:
        print(r)
        if r[2] == '国':
            print("GGG")
            rc.execute('update cxnl_data_new set rc_gj=%s where name="%s"'%(r[0],r[1]))
        elif r[2] == '省':
            print("SSS")
            rc.execute('update cxnl_data_new set rc_sheng=%s where name="%s"'%(r[0],r[1]))
        elif r[2] == '市':
            print("CCC")
            rc.execute('update cxnl_data_new set rc_shi=%s where name="%s"'%(r[0],r[1]))
    rdb.commit()
def update_standard(col):
    pswd = input("Input password>>>")
    rdb = pymysql.connect(host='10.6.12.3', user='cd_back', password=pswd, database='gqcxnl',charset='utf8')
    rc = rdb.cursor()
    rc.execute('select id,%s from cxnl_data_new'%col)
    rz = rc.fetchall()
    rc.execute('select max(%s),min(%s) from cxnl_data_new'%(col,col))
    temp = rc.fetchone()
    max = float(temp[0])
    min = float(temp[1])
    for r in rz:
        print(r[0],100*(float(r[1])-min)/(max-min))
        rc.execute('update cxnl_standard_100_0 set %s=%lf where id=%s'%(
        col,
        100*(float(r[1])-min)/(max-min),r[0]
        ))
    rdb.commit()
def update_standard_0(col,val):
    pswd = input("Input password>>>")
    rdb = pymysql.connect(host='10.6.12.3', user='cd_back', password=pswd, database='gqcxnl',charset='utf8')
    rc = rdb.cursor()
    rc.execute('select id,%s from cxnl_data_new'%col)
    rz = rc.fetchall()
    rc.execute('select max(%s),min(%s) from cxnl_data_new'%(col,col))
    temp = rc.fetchone()
    max = 1.0
    min = -1.0
    for r in rz:
        print(r[0],100*(float(r[1])-min)/(max-min))
        if float(r[1])<-1:
            rc.execute('update cxnl_standard_100_0 set %s=%lf where id=%s'%(
            col,0.0,r[0]
            ))
        elif float(r[1])>1:
            rc.execute('update cxnl_standard_100_0 set %s=%lf where id=%s'%(
            col,100.0,r[0]
            ))
        else:
            rc.execute('update cxnl_standard_100_0 set %s=%lf where id=%s'%(
            col,
            100*(float(r[1])-min)/(max-min),r[0]
            ))
    rdb.commit()
def update_log_0(col,index):
    pswd = input("Input password>>>")
    rdb = pymysql.connect(host='10.6.12.3', user='cd_back', password=pswd, database='gqcxnl',charset='utf8')
    rc = rdb.cursor()
    rc.execute('select id,%s from cxnl_data_new'%(col))
    rz = rc.fetchall()
    rc.execute('select max(%s),min(%s) from cxnl_data_new'%(col,col))
    temp = rc.fetchone()
    max = float(temp[0])
    min = float(temp[1])
    val=[]
    for r in rz:
        if float(r[1])<-1:
            val.append(math.log(1,index))
        elif float(r[1])>1:
            val.append(math.log(3,index))
        else:
            val.append(math.log(float(r[1])+2,index))
    print(val)

    val_s=sorted(val)

    print(val_s)
    for i in range(len(val)):
        print(100*(val[i]-val_s[0])/(val_s[-1]-val_s[0]))
        rc.execute('update cxnl_log_100 set %s=%lf where id=%s'%(
        col,100*(val[i]-val_s[0])/(val_s[-1]-val_s[0]),rz[i][0]
        ))
    rdb.commit()
def update_log(col,index):
    pswd = input("Input password>>>")
    rdb = pymysql.connect(host='10.6.12.3', user='cd_back', password=pswd, database='gqcxnl',charset='utf8')
    rc = rdb.cursor()
    rc.execute('select id,%s from cxnl_data_new'%(col))
    rz = rc.fetchall()
    rc.execute('select max(%s),min(%s) from cxnl_data_new'%(col,col))
    temp = rc.fetchone()
    max = float(temp[0])
    min = float(temp[1])
    val=[]
    for r in rz:
        val.append(math.log((float(r[1])-min)/(max-min)+1,index))
    print(val)
    val_s=sorted(val)

    print(val_s)
    for i in range(len(val)):
        print(100*(val[i]-val_s[0])/(val_s[-1]-val_s[0]))
        rc.execute('update cxnl_log_100 set %s=%lf where id=%s'%(
        col,100*(val[i]-val_s[0])/(val_s[-1]-val_s[0]),rz[i][0]
        ))
    rdb.commit()
def update_percentile(col):
    pswd = input("Input password>>>")
    rdb = pymysql.connect(host='10.6.12.3', user='cd_back', password=pswd, database='gqcxnl',charset='utf8')
    rc = rdb.cursor()
    rc.execute('select id,%s from cxnl_data_new'%col)
    rz = rc.fetchall()
    rc.execute('select max(%s),min(%s) from cxnl_data_new'%(col,col))
    temp = rc.fetchone()
    max = float(temp[0])
    min = float(temp[1])
    for r in rz:
        print(r[0],100*(float(r[1])-min)/(max-min))
        rc.execute('update cxnl_standard_100_0 set %s=%lf where id=%s'%(
        col,
        100*(float(r[1])-min)/(max-min),r[0]
        ))
    rdb.commit()
