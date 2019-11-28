#!/usr/bin/python3
import pymysql
import random
import string
def randomword(length):
   letters = string.ascii_letters
   return ''.join(random.choice(letters) for i in range(length))
def randomchar(length):
   letters = string.ascii_letters+string.digits
   return ''.join(random.choice(letters) for i in range(length))
i=int(input())
u = open("yonghu.sql",'w')
u2 = open("pinglun.sql",'w')
'''
for c in range(0,i):
    u.write("insert into t_user(user_name,user_pw,user_realname,user_address,user_sex,user_tel,user_email,user_qq)\n")
    u.write("values(\"")
    u.write(randomchar(random.randint(5, 15)))
    u.write("\",\"")
    u.write(randomchar(6))
    u.write("\",\"")
    u.write(randomword(random.randint(5, 10)))
    u.write("\",\"")
    u.write(randomchar(random.randint(10, 20)))
    u.write("\",\"")
    u.write(randomword(1))
    u.write("\",\"")
    u.write(random.randint(10000000000, 99999999999).__str__())
    u.write("\",\"")
    u.write(randomchar(random.randint(2, 12))+"@163.com")
    u.write("\",\"")
    u.write(random.randint(100000, 9999999999).__str__())
    u.write("\");\n")
u.close()
'''
i=int(input())
for c in range(0,i):
    u2.write("insert into t_liuyan(liuyan_title,liuyan_content,liuyan_date,liuyan_user)\nvalues(\"")
    u2.write(randomword(random.randint(2,10)))
    u2.write("\",\"")
    u2.write(randomword(random.randint(20, 200)))
    u2.write("\",CURRENT_TIMESTAMP(),\"")
    u2.write(randomchar(random.randint(5,15))+"\");\n")

u2.close()
#db = pymysql.connect("", "root", "", "")
