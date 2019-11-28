import sqlite3



db = sqlite3.connect("fc.db3")
c= db.cursor()


list = open("3k.csv").read().split("\n")[:-1]

for word in list:
    word = word.split("$")
    c.execute('INSERT INTO `3k_punk_list`(front,back)values("%s","%s")'%(
    word[1],word[2]+'\n'+word[3]
    ))
db.commit()
