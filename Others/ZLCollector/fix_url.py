import sqlite3

# using python3
# connect db
db = sqlite3.connect("company.db3")
# working section
# get cursor
cursor = db.cursor()
# query
cursor.execute("select id,zl_url from patent")
# get id list
p_list = cursor.fetchall()
for p in p_list:
    new_url = p[1].split('&')[0]
    print(new_url,p[0])
    cursor.execute("update patent set zl_url='%s' where id=%d"%(new_url,p[0]))
# close db
db.commit()
db.close()
