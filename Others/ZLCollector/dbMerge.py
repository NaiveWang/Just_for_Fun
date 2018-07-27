'''
 python version : 3.6
 pip ： PyMySQL, sqlite3
 system : linux
 this script will merge two table into one.
'''
import sqlite3
import pymysql
import chardet
import sys

# clear the local database

localdb = sqlite3.connect('company.db3')
localdbc = localdb.cursor();
localdbc.execute('delete from company_info')
localdb.commit()
print('local database cleared.')

# connect the remote database (source)

db = pymysql.connect(host='10.6.12.3', user='cd_back_block', password='123456', database='gjkj',charset='utf8')
cursor = db.cursor()
cnt0=0
# add data from db 1
cnt=0
cursor.execute("SELECT company_name,address,contacts,contacts_phone,contacts_cellphone,contacts_email,\
                        base_id,\
                        license_id,\
                        first_high_technology_class,\
                        company_type,\
                        high_technology_class_name,\
                        industry_class_name \
                        FROM gjkj.tmse_application_company_info")

data = cursor.fetchall()
for a in data:
    try:
        localdbc.execute('INSERT INTO company_info(company_name,company_address,contact_name,contact_tel,contact_phone,contact_email,\
            company_id,\
            company_license,\
            ht_class_1st,\
            company_type,\
            ht_class_name,\
            industry_class_name)\
            VALUES(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")'
                    % (a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11]))

    except sqlite3.IntegrityError as e:
        cnt+=1
        continue
    cnt0+=1
## save
localdb.commit()
print("Company name exist : "+cnt.__str__())
# add data from db 2
cursor.execute("SELECT sName,sAddress,QA11,QA17,QA17_1,QA13,\
                company_id,\
                QB16V,\
                company_type,\
                QB15A,\
                QB03Two,\
                QB03One\
                FROM gjkj.t_high_tech_company_info")
data = cursor.fetchall()
cnt=0
for a in data:
    try:
        localdbc.execute("INSERT INTO company_info(company_name,company_address,contact_name,contact_tel,contact_phone,contact_email,\
            company_id,\
            ht_class_1st,\
            company_type,\
            QB15A,\
            QB03_2,\
            QB03_1)\
            VALUES(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")"
                    % (a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11]))
    except sqlite3.IntegrityError as e:
        # print(e)
        cnt+=1
        continue
    cnt0+=1
## save
localdb.commit()
print("Company name exist : "+cnt.__str__())
print("we have %d company"%cnt0)
# close all the database connection
