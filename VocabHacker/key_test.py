# python3
from urllib import request
import json
import key
import sqlite3



temp=json.loads(bytes.decode(request.urlopen(key.u_mwdl+'contract'+'?key='+key.k_mwdl).read()))
for a in temp:
    print(a["meta"])
