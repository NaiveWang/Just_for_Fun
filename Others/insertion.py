# coding=UTF-8
import mysql.connector
from mysql.connector import errorcode
try:
    cnx = mysql.connector.connect(user='root',password='123123',host=None,database='coursesenrolling')
except mysql.connector.Error as err:
    if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
        print("Something is wrong with your user name or password")
    elif err.errno == errorcode.ER_BAD_DB_ERROR:
        print("Database does not exist")
    else:
        print('Unknown Fetal Error,code='+err)
    exit(1)
c1=cnx.cursor()
c1.execute('select id,num,nam from admin')
for(id,num,nam) in c1:
    print(id.__str__()+'  '+num+'  '+nam)
c1.close()
cnx.close()