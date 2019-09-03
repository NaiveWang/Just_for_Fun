from urllib import request
import os.path
import re
reg='https://[.-z]*.jpg'
text=open('merged.json').read()
m=re.findall(reg, text)
for em in m:
    local = em.replace('/', '_-').replace('https:_-_-', 'img/')
    if os.path.isfile(local):
        print('skipping', em)
    else:
        try:
            print('grabbing', em)
            request.urlretrieve(em, local)
            print('finished', em)
        except Exception as e:
            print(e)
