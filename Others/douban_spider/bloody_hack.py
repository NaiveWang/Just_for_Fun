from urllib import request
from io import StringIO
import gzip
import json
import sys
header={
'Host': 'm.douban.com',
'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0',
'Accept': 'application/json, text/javascript, */*; q=0.01',
'Accept-Language': 'en-US,en;q=0.5',
'Accept-Encoding': 'gzip',
'Referer': 'https://www.douban.com/gallery/topic/51644/?=undefined&sort=new',
'Content-Type': 'application/x-www-form-urlencoded',
'Origin': 'https://www.douban.com',
'Connection': 'keep-alive',
'Cookie': 'bid=Md0QpnoUKsM; __utma=30149280.660344315.1566440889.1567406979.1567408852.5; __utmz=30149280.1566867171.3.2.utmcsr=baidu|utmccn=(organic)|utmcmd=organic; ll="108288"; douban-fav-remind=1; __utmc=30149280; ap_v=0,6.0; __utmb=30149280.1.10.1567408852; __utmt=1',
'Pragma': 'no-cache',
'Cache-Control': 'no-cache',
'Upgrade-Insecure-Requests': '1'}

url='https://m.douban.com/rexxar/api/v2/gallery/topic/'+sys.argv[1]+'/items?sort=new&count=50&status_full_text=1&guest_only=0&ck=null&start='

total=int(sys.argv[2])
start=0
while start < total:
    req = request.Request(url+str(start), headers=header)

    response = request.urlopen(req)
    print(start, response.getcode())

    text = gzip.decompress(response.read())
    f=open('raw/'+str(start)+'.json', 'w')
    j=json.loads(text.decode("utf-8", "ignore"))
    json.dump(j, f, ensure_ascii=False)
    start+=50
