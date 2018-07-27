import pymysql
import sqlite3
# connect the remote database
remotedb = pymysql.connect(host='10.6.12.3', user='cd_back', password='123456', database='gjkj',charset='utf8')
rmc = remotedb.cursor()
# open the local database
localdb = sqlite3.connect('company.db3')
loc = localdb.cursor()
# get remote data
rmc.execute("SELECT id,company_name,ht_class_1st,company_type FROM gjkj.t_merged_company")
# clear all of the data from local database
# Note:if you do not want to remove data you already have, comment the following code

loc.execute("delete from company_info")
localdb.commit()

# insert to local database
data = rmc.fetchall()
for a in data:
    try:
        loc.execute("INSERT INTO company_info(\
                        company_serial,\
                        company_name,\
                        ht_class_1st,\
                        company_type\
                        ) VALUES(\"%s\",\"%s\",\"%s\",\"%s\"\
                        )"%(a[0],a[1],a[2],a[3]))
    except Exception as e:
        print(a[1],e)
# commit data and close connection
remotedb.close()
localdb.commit()
localdb.close()
