# python3
from urllib import request
import json
import key
import sqlite3

word=input()
print('searching '+word)
temp=json.loads(bytes.decode(request.urlopen(key.u_mwdl+word+'?key='+key.k_mwdl).read()))
print(temp)

for a in temp:
    if a['hwi']['hw'].split(':',1)[0] == word:
        print('疯狂大宇宙',a['fl'])##voc
        for e in a['def']:
            for ee in e['sseq']:
                # print(ee,'\n\n')
                for eee in ee:
                    if eee[0]=='sense':
                        #print(eee[1]['dt'][1])
                        print('\t',eee[1]['dt'][0][1]) ###df
                        for eeee in eee[1]['dt']:
                            #print(eeee)
                            if eeee[0]=='vis':
                                #print(eeee[1])
                                for eeeee in eeee[1]:
                                    print(eeeee['t']) ###ex
                        print('二次元二次元二次元二次元二次元二次元')
                        #break
        #print(a['app-shortdef'])
