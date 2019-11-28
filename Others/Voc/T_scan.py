f = open('CET4.txt', encoding='GBK')
print(f)
for r in f.readlines():
    #print(r.find(' '))
    #r[r.find(' ')]='#'
    t=r.split(' ',1)
    print(t)
f.close()
