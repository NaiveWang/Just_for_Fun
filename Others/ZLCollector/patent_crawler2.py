import sqlite3
import _thread
import time
import math
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
from urllib import request
# encoding = UTF-8
page_login = [  "https://login.zlbaba.com/login?service=https://www.patexplorer.com/login/cas",
                "http://124.128.225.189:8060/"]
page_search = [ "https://www.patexplorer.com/",
                "http://124.128.225.189:8060/pubsearch/patentsearch/searchHomeIndex-searchHomeIndex.shtml"]

abstract_css_list = [
    "#Js_patent_view_container > div > div.fn-clear.Js_patent_view_item.ui-switchable-panel > div.g-info-l > div > div > div.Js_patent_view_content.ui-switchable-content > div:nth-child(1) > div > div.abstract.contenttext",
    "#Js_patent_view_container > div > div:nth-child(1) > div.g-info-l > div > div.Js_patent_view_content.ui-switchable-content > div:nth-child(1) > div > div.abstract.contenttext"
]



u = ["naive1995","18842584932","17862810565","18555131495","18615979059"] # used this user name to login
p = ["naive1995","18842584932","17862810565","18555131495","18615979059"] # used password to login
free_proxy = [  'http://www.xiongmaodaili.com/xiongmao-web/api/gbip?secret=98643b104113407fc33545f19bde0fc1&orderNo=GB20180718164818sRSzglco&count=50&isTxt=1',
                'http://www.xiongmaodaili.com/xiongmao-web/api/glip?secret=66311ee5ec03163c4722632eddf168f7&orderNo=GL20180416164758V2LW1eYs&count=1&isTxt=1']
# This function provides many ip address
def getip():
    res=request.urlopen(free_proxy[1])
    ip=res.read()
    return ip.decode('utf-8')
# configure the web driver

dvropt = Options()
'''
ip = getip()
print("IP address : %s"%(ip))
dvropt.add_argument('--proxy-server=%s' % ip)
'''
dvropt.add_argument('--proxy-server=182.34.18.195:9077')#182.34.18.195:9077s
# dvropt = add_argument("headless")# to hide the browser window, uncomment this line.
# set the web driver

def clawlerT(id,start_point):

    bw = webdriver.Chrome(chrome_options=dvropt)
    #open the intro page
    try:
        # start_point=input("T%d>Please type in the company id to start:"%id)
        bw.get(page_login[0])

        # find element on page

        input_user = bw.find_element_by_id("Js_loginId")
        input_pswd = bw.find_element_by_name("password")
        bt_login = bw.find_element_by_id("loginBtn")
        # input login info
        input_user.send_keys(u[id])
        input_pswd.send_keys(p[id])
        # login action
        bt_login.click()
        # current page should be the searching page
    except Exception as e:
        if e != "name \'find_element_by_name\' is not defined":
            print("maybe already logged.")
        else:
            print("Cannot open page:",e)
            bw.quit()
            exit()
    finally:
        # connect the local database
        print("connecting database...")
        localdb = sqlite3.connect("company.db3")
        c = localdb.cursor()
        print("fetching companys from database...")
        c.execute("select company_name, company_serial, company_type, ht_class_1st\
                    from company_info where batch=1 and company_serial >= %s order by company_id asc" % (start_point))
        company_list = c.fetchall()
        # trying to input the searching content
        for company_element in company_list: # loop
            print('CID=',company_element[1])
            bw.get(page_search[0])
            input_search = bw.find_element_by_name("q")
            bt_search = bw.find_element_by_xpath("/html/body/div[1]/div[4]/form/div[3]/input")
            input_search.send_keys(company_element[0])
            bt_search.click()
            # current page after search should be the index page
            # a = bw.find_element_by_xpath("//*[@id=\"paging\"]/div/span[3]/a")
            bw.refresh()
            time.sleep(1)
            if bw.page_source.find('过于频繁')!=-1:
                print("中招了，填填二维码，带带大师兄。")
                input()

            # get total result
            total=0
            while 1:
                try:
                    element = WebDriverWait(bw, 15).until(
                     EC.presence_of_element_located((By.CLASS_NAME, 'Js_total')))
                    total = int(bw.find_element_by_class_name("Js_total").text)
                    break
                except Exception as e:
                    print(id,'>',e)
            print(total)
            # at this time we do not have to change page any more!
            urls = []
            total = math.ceil(total/100)
            index_page=bw.current_url
            for a in range(0,total):
                bw.get(index_page+"#/100/%d"%(a+1))
                bw.refresh()
                time.sleep(5)
                for i in bw.find_elements_by_class_name("u-list-div"):
                    urls.append(i.find_element_by_tag_name('a').get_attribute('href'))
            # print(urls)
            for l in urls:
                print(l)
                failure=1
                linka=0
                # check if the link has been in the database
                c.execute("select * from patent where zl_url=\"%s\""%(l))
                if c.fetchone() == None:
                    bw.get(l)
                    while 1:# this is the error handling loop
                        try:
                            # bw.refresh()
                            time.sleep(0.1)
                            #element = WebDriverWait(bw, 15).until(
                            # EC.presence_of_element_located((By.CLASS_NAME, 'Js_h1_name')))
                            zln = bw.find_element_by_class_name('Js_h1_name').text
                            zli = bw.find_elements_by_tag_name('li')
                            zlsqn = ''
                            zlsqd = ''
                            zlsqp = ''
                            zlgkn = ''
                            zlgkd = ''
                            zliv = ''
                            zltm = ''
                            zlt = ''
                            zla = ''
                            zlgs = ''
                            zlagc = ''
                            zlag = ''
                            zlp=''
                            flaga = False
                            flagp = False
                            i=0
                            for t in zli:
                                # print('$',t.text,'$')
                                if t.text.find('申请号') != -1:
                                    zlsqn=t.text.split('\n')[1]
                                    break
                                i+=1
                            text_info = []
                            for t in range(i,len(zli)):
                                temp_text = zli[t].text
                                if temp_text=='':
                                    break
                                print('$'+temp_text+'$')
                                text_info.append(temp_text)
                                if temp_text.find('代理人') != -1:
                                    break
                            for t in text_info:
                                # print('$',t.text,'$')
                                if t.find('申请日') != -1:
                                    zlsqd=t.split('\n')[1]
                                    idx = text_info.index(t)
                                    zlgkn=text_info[idx+1].split('\n')[1]
                                    zlgkd=text_info[idx+2].split('\n')[1]
                                    zlsqp=text_info[idx+3].split('\n')[1]
                                    zliv=text_info[idx+4].split('\n')[1]
                                    zltm=text_info[idx+5].split('\n')[1]
                                    zlt=text_info[idx+6].split('\n')[1]
                                    zla=text_info[idx+7].split('\n')[1]
                                    text_info=text_info[8:]
                                    break
                            for t in text_info:
                                # print('$',t.text,'$')
                                if t.find('国省代码') != -1:
                                    zlgs=t.split('\n')[1]
                                    del(text_info[0])
                                    break
                            for t in text_info:
                                # print('$',t.text,'$')
                                if t.find('优先') != -1:
                                    zlp=t.split('\n')[1]
                                    flagp=True
                                    break
                            for t in text_info:
                                # print('$',t.text,'$')
                                if t.find('代理机构') != -1:
                                    zlagc=t.split('\n')[1]
                                    flaga=True
                                    break
                            for t in text_info:
                                # print('$',t.text,'$')
                                if t.find('代理人') != -1:
                                    zlag=t.split('\n')[1]
                                    break
                            abstract = bw.find_element_by_css_selector(abstract_css_list[linka]).text
                            print(abstract)#
                            # write to database basic data
                            while 1:
                                try:
                                    c.execute("insert into patent (company_name,company_type,company_id,ht1st,zl_url,zl_name,zl_sq_num,zl_sq_date,zl_sq_name,zl_gk_num,zl_gk_date,zl_inventor,type_main,type,address,gs,abstract)\
                                                            VALUES(\"%s\",\"%s\"  ,  \"%s\"    ,   \"%s\" ,\"%s\",\"%s\",\"%s\" ,\"%s\"   ,\"%s\"    ,\"%s\"    ,\"%s\"   ,\"%s\"    ,\"%s\"    ,\"%s\",\"%s\"   ,\"%s\",\"%s\")"%
                                                            (
                                                            company_element[0],
                                                            company_element[2],
                                                            company_element[1],
                                                            company_element[3],
                                                            l,
                                                            zln,
                                                            zlsqn,
                                                            zlsqd,
                                                            zlsqp,
                                                            zlgkn,
                                                            zlgkd,
                                                            zliv,
                                                            zltm,
                                                            zlt,
                                                            zla,
                                                            zlgs,
                                                            abstract.replace('"','""'),
                                                            ))
                                    localdb.commit()
                                    if flagp:
                                        c.execute('update patent set priority=\"%s\" where zl_url=\"%s\"' % (zlp,l))
                                        localdb.commit()
                                    if flaga:
                                        c.execute('update patent set agent_org=\"%s\",agent=\"%s\" where zl_url=\"%s\"'%(zlagc,zlag,l))
                                        localdb.commit()
                                    break
                                except Exception as e:
                                    print(e,"trying another time")
                                    continue
                            break
                        except Exception as e:
                            print(e)
                            if bw.page_source.find('过于频繁')!=-1:
                                print("Thread %d : 中招了，填填二维码，带带大师兄。"%(id))
                                input()
                            print('trying to reconnect...')
                            # delay+=0.5
                            linka = (linka+1)% len(abstract_css_list)
                            failure+=1
                            time.sleep(0.1)
                            if failure%10 == 3:
                                bw.refresh()
                            if failure==100:
                                print("quit.")
                                # msg=input()
                                bw.quit()
                                exit()
                                break
                            # input()

                            continue
                        # bw.back()
    print("T%d>All Done."%id)
    bw.close()
s=[0,0,0]

s[0]=int(input("mod=0:"))
#s[1]=int(input("mod=1:"))
#s[2]=int(input("mod=2:"))
print(s)
#input()
# _thread.start_new_thread(clawlerT,(0,s[0],))
# _thread.start_new_thread(clawlerT,(1,s[1],))
# _thread.start_new_thread(clawlerT,(2,s[2],))
'''
while 1:
   pass
'''
clawlerT(0,s[0])