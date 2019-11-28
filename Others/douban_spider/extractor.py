import json
import glob
import sys
f=open(sys.argv[1]+'.json', 'a')
jsonz=glob.glob('raw/*.json')
for jfile in jsonz:
    j=json.load(open(jfile))
    #print(j['items'][0])
    for i in j['items']:
        json.dump(i['target'], f, ensure_ascii=False)
        f.write('\n')
    #exit()
