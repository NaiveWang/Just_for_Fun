# Creative Comments
# Time Stamp 2017.10.20
from urllib import request
from urllib import parse

#site 1 http://www.mmxyz.net/rosi-1000/
#site 2 https://www.rosmms.com/rosimm/2014/09/02/1056_6.htm
#site 3 https://wvw.rosmms.com/pic/upload/2014/09/02/rosimm-1000-26.jpg
# I will obtain the date at site 1
# Then I will produce website and download image at site 3
# So here you can see, site 2 is a intermediate page, which is used to obtain the original site 3.
site1="http://www.mmxyz.net/rosi-"
site3="https://wvw.rosmms.com/pic/upload/"
picname0="rosimm-"#<1015
picname1="rosmm-"
mon={'一':'01','二':'02','三':'03','四':'04','五':'05','六':'06','七':'07','八':'08','九':'09','十':'10','十一':'11','十二':'12'}
# at first, i got to parse site 1 first.
def GetDate(number):
    site = site1+number.__str__()+'/'
    tr=3
    while 1 :
        try:
            rsp = request.urlopen(site)
            text = rsp.read()
            text = bytes.decode(text)
        except Exception:
            print("Err0 : Page Cannot Access Correctly, Trying Again")
            continue
        else:
            break
        tr=tr-1
        if tr==0:
            print("Skip")
            return -1
    #here parsing the page
    text=text.split("post-msg")
    text=text[1]
    text=text.split(";")
    text=text[3]
    text=text.split("&")
    text=text[0]
    text=text.split(", ")
    year=text[1]
    text=text[0]
    text=text.split(" ")
    day=text[1]
    month=text[0]
    month=mon[month]
    print(year,month,day)
    return year+'/'+month+'/'+day+'/'
def GetDLurl(number):
    temp0=GetDate(number)
    if temp0 == -1:
        return -1
    url0=site3+temp0
    if(int(number)<1015):
        url0+=picname0
    else:
        url0+=picname1
    url0+=number
    url0+='-'
    return url0

def DownloadASet(number):
    cnt=1
    url=GetDLurl(number)
    if(url==-1):
        return
    while 1 :
        tmpurl=url+cnt.__str__()+".jpg"
        print("Downloading",tmpurl)
        try:
            request.urlretrieve(tmpurl,number+"-"+cnt.__str__()+".jpg")
        except Exception:
            break
        cnt+=1
ia=input()
ib=input()
for x in range(int(ia),int(ib)):
    DownloadASet(x.__str__())
