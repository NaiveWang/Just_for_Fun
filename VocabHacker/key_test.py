# python3
from urllib import request
import json
import key

temp=json.loads(bytes.decode(request.urlopen(key.u_mwdl+'contract'+'?key='+key.k_mwdl).read()))
print(json.dumps(temp, indent=4, sort_keys=True))
