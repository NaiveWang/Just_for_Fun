'''
 this script upload patents to a online database.
'''
import pymysql
import sqlite3
# connect to local database
ldb = sqlite3.connect("company.db3")
lc = ldb.cursor()
# connect to remote database
## get pawd for security
pswd = input("Input password>>>")
## connect
try:
    rdb = pymysql.connect(host='10.6.12.3', user='cd_back', password=pswd, database='gjkj',charset='utf8')
except Exception as e:
    print(e)
    exit()
## get cursor
rc = rdb.cursor()
# fetching data
lc.execute("select * from patent")
rows = lc.fetchall()
for row in rows:
    print(row[0])
    rc.execute('insert into t_patent_201807(company_id,company_name,company_type,ht_class,p_url,p_name,p_sq_no,p_sq_date,p_gk_no,p_gk_date,p_sq_person,p_inventor,type_main,type,address,gs,priority,agent_org,agent,abstract)\
    values(%s,"%s",%s,"%s","%s","%s","%s","%s","%s","%s","%s","%s","%s","%s","%s","%s","%s","%s","%s","%s")'%(
    row[3],row[1],row[2],row[4],row[5],
    row[6],row[7],row[8],row[10],row[11],row[9],
    row[12],row[13],row[14],row[15],row[16],row[17],row[18],row[19],row[20].replace("'","\\\'").replace('"','\\\"')
    ))
# close local database
ldb.close()
# close remote database
rdb.commit()
rdb.close()
