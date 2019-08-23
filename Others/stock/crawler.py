from urllib import request
import urllib
import sqlite3
import glob, os
from selenium import webdriver
import json
from pprint import pprint
import random
import _thread
color_header = ["\x1B[31m",
"\x1B[32m",
"\x1B[33m",
"\x1B[34m",
"\x1B[35m",
"\x1B[36m",
"\x1B[37m"]



url_base_a = [  'http://webf10.gw.com.cn/SH/B8/SH',
                'http://webf10.gw.com.cn/SZ/B8/SZ',
                'http://webf10.gw.com.cn/SH/B7/SH',
                'http://webf10.gw.com.cn/SZ/B7/SZ',

                'http://webf10.gw.com.cn/SH/B10/SH',
                'http://webf10.gw.com.cn/SZ/B10/SZ',
                'http://webf10.gw.com.cn/SH/B15/SH',
                'http://webf10.gw.com.cn/SZ/B15/SZ']
url_base_b = ['_B8.html','_B7.html','_B10.html','_B15.html']
url_free_proxy = 'http://www.xiongmaodaili.com/xiongmao-web/api/glip?secret=66311ee5ec03163c4722632eddf168f7&orderNo=GL20180416164758V2LW1eYs&count=1&isTxt=1'

headers = { 'User-Agent' : 'Mozilla/4.0 (compatible; MSIE 5.5; Windows NT)' }

def get_stock_name(lst):
    bw = webdriver.Chrome()
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    url='http://stockpage.10jqka.com.cn/'
    for l in lst:
        print(url+l[1])
        bw.get(url+l[1])
        text=bw.page_source.split('<strong>',1)[-1].split('<')[0]
        print('$'+text+'$')

        c.execute('update company set name_stock="%s",is_crawled=1 where serial="%s"'%(
            text,l[1]
        ))
        db.commit()

def import_company_id(f, mkt):
    lz=open(f,'r').read().split('\n')[:-1]
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    for l in lz:
        try:
            c.execute('insert into company(serial, market)values("%s","%s")'%(l, mkt))
            print('>',end='')
        except sqlite3.IntegrityError:
            print("#",end='')
    db.commit()
    c.close()
    db.close()
def set_proxy():
    res=request.urlopen(url_free_proxy).read().decode('utf-8')
    proxy_support = urllib.request.ProxyHandler({'http': res})
    opener = urllib.request.build_opener(proxy_support)
    urllib.request.install_opener(opener)
def get_list_cond(val):
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    c.execute('select id,serial from company where is_crawled=%d'%val)
    rtn = c.fetchall()
    db.commit()
    c.close()
    db.close()
    return rtn
def get_list_full():
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    c.execute('select id,serial from company')
    rtn = c.fetchall()
    db.commit()
    c.close()
    db.close()
    return rtn
def crawl_i(lst):
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    for l in lst:
        print(l)
        text = request.urlopen(url_base_a[1]+l+url_base_b[0]).read().decode('utf-8')
        f=open('pagez/'+l+'_indiv.html','w')

        f.write(text)
        f.close()
        c.execute('update company set is_crawled=1 where serial="%s"'%l)
        db.commit()
def crawl_c(lst):
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    for l in lst:
        print(l)
        text = request.urlopen(url_base_a[3]+l+url_base_b[1]).read().decode('utf-8')
        f=open('pagez/'+l+'_comp.html','w')

        f.write(text)
        f.close()
        c.execute('update company set is_crawled=1 where serial="%s"'%l)
        db.commit()
def crawl_both(lst):
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    for l in lst:
        print('>',end='')
        try:
            text = request.urlopen(url_base_a[0]+l[1]+url_base_b[0]).read().decode('utf-8')
            f=open('pagez/'+l[1]+'_indiv.html','w')
            f.write(text)
            f.close()

            text = request.urlopen(url_base_a[2]+l[1]+url_base_b[1]).read().decode('utf-8')
            f=open('pagez/'+l[1]+'_comp.html','w')
            f.write(text)
            f.close()
            c.execute('update company set is_crawled=1 where serial="%s"'%l[1])
            db.commit()
        except urllib.error.HTTPError:
            try:
                text = request.urlopen(url_base_a[1]+l[1]+url_base_b[0]).read().decode('utf-8')
                f=open('pagez/'+l[1]+'_indiv.html','w')
                f.write(text)
                f.close()

                text = request.urlopen(url_base_a[3]+l[1]+url_base_b[1]).read().decode('utf-8')
                f=open('pagez/'+l[1]+'_comp.html','w')
                f.write(text)
                f.close()
                c.execute('update company set is_crawled=1 where serial="%s"'%l[1])
                db.commit()
            except Exception as e:
                print(e)
def crawl_both_new(lst):
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    for l in lst:
        print(l[1])
        try:
            text = request.urlopen(url_base_a[4]+l[1]+url_base_b[2]).read().decode('utf-8')
            f=open('pagez/'+l[1]+'_holder.html','w')
            f.write(text)
            f.close()

            text = request.urlopen(url_base_a[6]+l[1]+url_base_b[3]).read().decode('utf-8')
            f=open('pagez/'+l[1]+'_news.html','w')
            f.write(text)
            f.close()
            c.execute('update company set is_crawled=1 where serial="%s"'%l[1])
            db.commit()
        except urllib.error.HTTPError:
            try:
                text = request.urlopen(url_base_a[5]+l[1]+url_base_b[2]).read().decode('utf-8')
                f=open('pagez/'+l[1]+'_holder.html','w')
                f.write(text)
                f.close()

                text = request.urlopen(url_base_a[7]+l[1]+url_base_b[3]).read().decode('utf-8')
                f=open('pagez/'+l[1]+'_news.html','w')
                f.write(text)
                f.close()
                c.execute('update company set is_crawled=1 where serial="%s"'%l[1])
                db.commit()
            except Exception as e:
                print(e)
def parse_comp(lst):
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    for l in lst:
        print('>>>>>>>>>>>>>>>>>>>'+l[1])
        text=open('pagez/'+l[1]+'_comp.html','r').read().split('◆公司详情◆',1)[-1].split('◆参控公司◆',1)[0].replace('w3','w1').replace('w4','w2').split('<td class="w1">')[1:27]
        colz=[]
        for t in text:
            #print(t.split('<',1)[0],end='#')
            colz.append(t.split('w2">',1)[-1].split('<')[0].replace(' ','').replace('"','""'))
        print(colz)
        try:
            c.execute('update company set\
            	name_company="%s",date_onstock="%s",\
        	name_company_en="%s",date_offer="%s",website="%s",region="%s",industry="%s",num_tcss="%s",\
        	email="%s",num_sold="%s",\
        	recommendation="%s",price_sold="%s",\
        	dealer="%s",price_first="%s",represent="%s",\
        	director="%s",manager="%s",\
        	secretary="%s",tel="%s",fax="%s",count_org="%s",\
        	zipcode="%s",regist_address="%s",address="%s",field="%s",brief_history="%s"\
            where serial="%s"'%(colz[0],colz[1],colz[2],colz[3],colz[4],
            colz[5],colz[6],colz[7],colz[8],colz[9],
            colz[10],colz[11],colz[12],colz[13],colz[14],
            colz[15],colz[16],colz[17],colz[18],colz[19],
            colz[20],colz[21],colz[22],colz[23],colz[24],colz[25],l[1]))
        except Exception as e:
            print(e)
    db.commit()
def parse_comp2(lst):
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    for l in lst:
        print('>>>>>>>>>>>>>>>>>>>'+l[1])
        text=open('pagez/'+l[1]+'_comp.html','r').read().split('公司网址',1)[-1].split('电子信箱',1)[0].split('</a>')[:2]
        #print(text[0].split('>')[-1],text[1].split('>')[-1])
        try:
            c.execute('update company set website="%s",num_tcss=%s where serial="%s"'%(
            text[0].split('>')[-1],text[1].split('>')[-1],l[1]
            ))
        except Exception as e:
            print(e)
    db.commit()
def parse_hold_comp(lst):
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    for l in lst:
        print('>>>>>>>>>>>>>>>>>>>'+l[1])
        text=open('pagez/'+l[1]+'_comp.html','r').read().split('◆参控公司◆',1)[-1].split('="ckgj_table_scroll">',1)[-1].split('</section>',1)[0].\
            replace('"w1"','').replace('"w2"','').replace('"w3"','').replace('"w4"','').replace('"w5"','').replace('"w6"','').\
            replace(' class=','').\
            split('<tr>')[1:]
        #print(text[0].split('>')[-1],text[1].split('>')[-1])
        try:
            for t in text:
                t=t.split('<td>')[2:]
                c.execute('insert into holding_company(cid,date,name,\
                relation,percent,profit,region)VALUES(\
                "%s","%s","%s","%s","%s","%s","%s")'%(
                l[0],
                t[0].split('<',1)[0],
                t[1].split('<',1)[0],
                t[2].split('<',1)[0],
                t[3].split('<',1)[0],
                t[4].split('<',1)[0],
                t[5].split('<',1)[0]))
        except Exception as e:
            print(e)
            # c.execute('update company set is_crawled=2 where serial="%s"'%l)
            #print(t.split('">',1)[-1].split('<',1)[0])
    db.commit()
def parse_hold_stock(lst):
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    for l in lst:
        print('>>>>>>>>>>>>>>>>>>>'+l[1])
        text=open('pagez/'+l[1]+'_comp.html','r').read().split('◆参控公司◆',1)[-1].split('="ckgj_table_scroll">',1)[-1].split('</section>',1)[0].\
            replace('"w1"','').replace('"w2"','').\
            replace(' class=','').\
            split('<tr>')[1:]
        #print(text[0].split('>')[-1],text[1].split('>')[-1])
        try:
            print(text)
            for t in text:
                t=t.split('<td>')[1:]
                print(t)
                #c.execute('insert into holding_stock(cid,stock_serial)VALUES(\
                #"%s","%s")'%(
                #l,t[0].split('<',1)[0]))
        except Exception as e:
            print(e)
            c.execute('update company set is_crawled=3 where serial="%s"'%l)
            #print(t.split('">',1)[-1].split('<',1)[0])
    db.commit()
def parse_new_stock(lst):
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    print(len(lst))
    for l in lst:
        #print('>>>>>>>>>>>>>>>>>>>'+l[1])
        text=open('pagez/'+l[1]+'_comp.html','r').read().split('<th>股票名称</th>',1)[-1].split('</table>',1)[-1].split('</table>',1)[0]\
        .split('</td>\n                                    <td>')[:-1]
        for t in text:
            #print(t)
            try:
                #print('$'+t.split('>')[-1]+'$')
                c.execute('insert into company(serial,is_crawled)values("%s",0)'%t.split('>')[-1])
            except Exception as e:
                print('#',end='')
    db.commit()
def parse_indiv(lst):
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    for l in lst:
        print('>>>>>>>>>>>>>>>>>>>'+l[1])
        text=open('pagez/'+l[1]+'_indiv.html','r').read().split('◆高管简历◆',1)[-1].split('姓名: ')[1:]
        for t in text:
            #print(t.split("简历: </pre></td><td style='padding-left:0px;padding-right:0px;' width='91.89%' colspan='1' align='left'><pre>",1)[-1].split('<',1)[0])
            try:
                c.execute('insert into individual(name,gender,edu,birth,resume)values("%s","%s","%s","%s","%s")'%(
                        t.split('<',1)[0],
                        t.split('性别: ',1)[-1].split('<',1)[0],
                        t.split('学历: ',1)[-1].split('<',1)[0],
                        t.split('出生日期: ',1)[-1].split('<',1)[0],
                        t.split("简历: </pre></td><td style='padding-left:0px;padding-right:0px;' width='91.89%' colspan='1' align='left'><pre>",1)[-1].split('</pre>',1)[0].replace('"','""')
                ))
            except sqlite3.IntegrityError:
                continue
    db.commit()
def parse_relation(lst):
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    for l in lst:
        #print('>>>>>>>>>>>>>>>>>>>'+l[1])
        text=open('pagez/'+l[1]+'_indiv.html','r').read().split('薪酬(万元)',1)[-1]
        text2=text.split('◆高管简历◆',1)[-1].split("任职日期: ")[1:]
        #print(text2)
        for i in range(len(text2)):
            text2[i]=text2[i].split("简历: </pre></td><td style='padding-left:0px;padding-right:0px;' width='91.89%' colspan='1' align='left'><pre>",1)
            text2[i][0]=text2[i][0].split('<',1)[0]
            text2[i][1]=text2[i][1].split('</pre>',1)[0].replace('"','""')
        #print(text2)

        text=text.split('◆董事、监事和高管人员年度报酬情况◆',1)[0]\
        .split("<tr><td style='padding-left:0px;padding-right:0px;' width='1.72%' colspan='1' align='left'><pre>")[1:]
        for i in range(len(text)):
            #print(text2[i])
            text[i]=text[i].split('<pre>')
            #print(text[i][0].split('<',1)[0])
            print(text[i][1].split('<',1)[0])
            #print(text[i][2].split('<',1)[0])
            print(text[i][3].split('<',1)[0])
            print(text[i][4].split('<',1)[0])
            #input()
            c.execute('select id from individual where resume="%s"'%(text2[i][1]))
            id=c.fetchone()[0]
            c.execute('insert into relation(idc,idi,job,date,stock10k,wages10k)values(\
            %s,%s,"%s","%s","%s","%s")'%(l[0],id,text[i][1].split('<',1)[0],
            text2[i][0],
            text[i][3].split('<',1)[0],text[i][4].split('<',1)[0]))
    db.commit()
def parse_resume01():
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    c.execute('select resume,id from individual')
    lst = c.fetchall()
    for l in lst:
        if '国籍' in l[0]:
            #print(l[0])
            na = l[0].split('国籍',1)[0].split('，')[-1].split('：')[-1].\
            split('。')[-1].split(',')[-1].split('、')[-1].split('；')[-1]
            c.execute('update individual set nationality="%s" where id=%s'%(na,l[1]))
            #input()
    db.commit()
def parse_resume02():
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    c.execute('select resume,id from individual where nationality=""')
    lst = c.fetchall()
    for l in lst:
        if '国籍' in l[0]:
            #print(l[0])
            na = l[0].split('国籍',1)[-1].split('，',1)[0]
            c.execute('update individual set nationality="%s" where id=%s'%(na,l[1]))
            #input()
    db.commit()
def parse_resume03():
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    c.execute('select resume,id from individual where nationality is null')
    lst = c.fetchall()
    for l in lst:
        if '国籍' in l[0]:
            continue
        elif '籍贯' in l[0]:
            continue
        elif '古籍' in l[0]:
            continue
        elif '籍' in l[0]:
            #print(l[0].split('籍',1)[0])
            na=l[0].split('籍',1)[0].split('，')[-1].split('：')[-1].split(',')[-1]
            if len(na)<6:
                c.execute('update individual set nationality="%s" where id=%s'%(na,l[1]))
                print(l[1],na)
    db.commit()
def parse_resume04(edu):
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    c.execute('select resume,id from individual where edu is null')
    lst = c.fetchall()
    for l in lst:

        if edu+'毕业' in l[0]:
            print(l[1],l[0])
            c.execute('update individual set edu="%s" where id=%s'%(edu,l[1]))
        elif edu+'学历' in l[0]:
            print(l[1],l[0])
            c.execute('update individual set edu="%s" where id=%s'%(edu,l[1]))
    #db.commit()
def parse_resume05():
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    c.execute('select resume,id from individual where edu is null')
    lst = c.fetchall()
    for l in lst:

        if '学位' in l[0]:
            print(l[1])
            c.execute('update individual set edu="本科" where id=%s'%(l[1]))
    db.commit()
def parse_resume06():
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    c.execute('select resume,id from individual where is_evil!=1')
    lst = c.fetchall()
    for l in lst:

        if '中共' in l[0]:
            print(l[0])
            c.execute('update individual set is_evil=1 where id=%s'%(l[1]))
    db.commit()
def update_market():
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    c.execute('select id,serial from company')
    lst = c.fetchall()
    for l in lst:
        if l[1][0] is '6':
            c.execute('update company set market="SH" where id=%s'%l[0])
        elif l[1][0] is '3':
            c.execute('update company set market="SZ" where id=%s'%l[0])
        elif l[1][0] is '0':
            c.execute('update company set market="SZ" where id=%s'%l[0])
    db.commit()
def getjson_news():
    urla='http://webf10.gw.com.cn/JSON/SJTX/LIST/'
    urlb='.json'
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    c.execute('select market,serial from company')
    lst = c.fetchall()
    for l in lst:
        url=urla+l[0]+l[1]+urlb
        try:
            request.urlretrieve(url,'jsonz/'+l[1]+'_news.json')
        except urllib.error.HTTPError:
            print(url)
def getjson_detail():
    urla='http://webf10.gw.com.cn/JSON/SJTX/DETAIL/'
    urlb='.json'
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    c.execute('select detail,id from news where detail_flag=0 and detail is not null')
    lst = c.fetchall()
    i=0
    for l in lst:
        url=urla+l[0][:2]+'/'+l[0][2:4]+'/'+l[0]+urlb
        #print(url)

        try:
            request.urlretrieve(url,'jsonz/'+l[0]+'_detail.json')
            c.execute('update news set detail_flag=1 where id=%s'%l[1])
            i+=1
            if i % 100 is 0:
                print('\x1B[0m\t\t\t\t\t\tSaving...')
                db.commit()
            print(color_header[random.randint(0,len(color_header)-1)],end='')
            print(i,url)
        except urllib.error.HTTPError:
            print("翻车网址"+url)

def parse_news():
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    c.execute('select id,serial from company where is_crawled=1')
    lst = c.fetchall()
    for l in lst:
        #print(l)
        f=open('jsonz/'+l[1]+'_news.json')
        jdata=json.load(f)
        print('>>>>>',l)
        for j in jdata:
            for i in j['data']:
                try:
                    #print(type(i['RM']))
                    try:
                        print(i['SJTYPE'],j['date'],i['CUID'],i['RM'].replace('\r\n','').replace('<span class="red">','').replace('</span>','').replace('<span class="green">',''))
                        c.execute('insert into news(cid,title,date,content,detail)values(%s,"%s","%s","%s","%s")'%(l[0],i['SJTYPE'],j['date'],i['RM'].replace('\r\n','').replace('<span class="red">','').replace('</span>','').replace('<span class="green">','').replace('"','""'),i['CUID']))
                    except KeyError:
                        print(i['SJTYPE'],j['date'],i['RM'].replace('\r\n','').replace('<span class="red">','').replace('</span>','').replace('<span class="green">',''))
                        c.execute('insert into news(cid,title,date,content)values(%s,"%s","%s","%s")'%(l[0],i['SJTYPE'],j['date'],i['RM'].replace('\r\n','').replace('<span class="red">','').replace('</span>','').replace('<span class="green">','').replace('"','""')))
                except KeyError:
                    for k in i['dList']:
                        try:
                            print(i['SJTYPE'],j['date'],k['CUID'],k['RM'].replace('\r\n','').replace('<span class="red">','').replace('</span>','').replace('<span class="green">',''))
                            c.execute('insert into news(cid,title,date,content,detail)values(%s,"%s","%s","%s","%s")'%(l[0],i['SJTYPE'],j['date'],k['RM'].replace('\r\n','').replace('<span class="red">','').replace('</span>','').replace('<span class="green">','').replace('"','""'),k['CUID']))
                        except KeyError:
                            print(i['SJTYPE'],j['date'],k['RM'].replace('\r\n','').replace('<span class="red">','').replace('</span>','').replace('<span class="green">',''))
                            c.execute('insert into news(cid,title,date,content)values(%s,"%s","%s","%s")'%(l[0],i['SJTYPE'],j['date'],k['RM'].replace('\r\n','').replace('<span class="red">','').replace('</span>','').replace('<span class="green">','').replace('"','""')))
        #input()
    db.commit()
def parse_detail():
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    c.execute('select id,detail from news where detail_flag=1')
    lst = c.fetchall()
    for l in lst:
        f=open('jsonz/'+l[1]+'_detail.json')
        try:
            jdata=json.load(f)
            #print(jdata['rm'],jdata['rc'].replace('<P class=Para>　　</P>',''))
            if jdata.get('url') is None:
                c.execute('insert into news_detail(serial,title,content)values("%s","%s","%s")'%(l[1],jdata['rm'],jdata['rc'].replace('<P class=Para>','').replace('　　</P>','').replace('"','""')))
            else:
                c.execute('insert into news_detail(serial,title,content,url)values("%s","%s","%s","%s")'%(l[1],jdata['rm'],jdata['rc'].replace('<P class=Para>','').replace('　　</P>','').replace('"','""'),jdata['url']))
                #print(l)
        except Exception:
            print(l)
        #print(jdata)
    db.commit()
def parse_test():
    f=open('jsonz/600028_news.json')
    jdata=json.load(f)
    for j in jdata:
        for i in j['data']:
            try:
                print(type(i['RM']))
                if type(i['RM']) is list:
                    for k in i['RM']:
                        print(i['SJTYPE'],j['date'])
                else:
                    print(i['SJTYPE'],j['date'],i['RM'])
            except KeyError:
                for k in i['dList']:
                    nop
                    #print(i['SJTYPE'],j['date'],k['RM'])

#######################################################
def parse_resume_find(str,con):
    db=sqlite3.connect('k.db3')
    c=db.cursor()
    c.execute('select resume,id,birth from individual '+con)
    lst = c.fetchall()
    for l in lst:

        if str in l[0]:
            print(l[1],l[2])
            print(l[0])
#print(get_list())
'''
print('getting ip...')
set_proxy()
print('ip disguise ready.')
'''
#print('parsing...')
#parse_detail()
##parse_news()
##parse_hold_comp(get_list_cond(1))
##parse_comp(get_list_cond(1))
##parse_comp2(get_list_cond(1))
##parse_new_stock(get_list_cond(1))
##crawl_both_new(get_list_cond(0))
##get_stock_name(get_list_cond(1))
##parse_indiv(get_list_cond(1))
##parse_relation(get_list_cond(1))
##get_stock_name(get_list_cond(0))
##parse_resume06()
##parse_resume_find('学位','where edu is null')
##import_company_id('sha.txt')
##import_company_id('shb.txt')
#print('done.')
