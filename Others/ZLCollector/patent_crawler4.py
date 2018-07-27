import sqlite3
import _thread
import time
import math
import selenium
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
from urllib import request
# encoding = UTF-8
page_login = [  "https://login.zlbaba.com/login?service=https://www.patexplorer.com/login/cas",
                "http://124.128.225.189:8060/pubsearch/portal/uilogin-forwardLogin.shtml"]
page_search = [ "https://www.patexplorer.com/",
                "http://124.128.225.189:8060/"]

abstract_css_list = [
    "#Js_patent_view_container > div > div.fn-clear.Js_patent_view_item.ui-switchable-panel > div.g-info-l > div > div > div.Js_patent_view_content.ui-switchable-content > div:nth-child(1) > div > div.abstract.contenttext",
    "#Js_patent_view_container > div > div:nth-child(1) > div.g-info-l > div > div.Js_patent_view_content.ui-switchable-content > div:nth-child(1) > div > div.abstract.contenttext"
]



u = ["dummy001","naive1995","18842584932","17862810565","18555131495","18615979059"] # used this user name to login
p = ["dummy001","naive1995","18842584932","17862810565","18555131495","18615979059"] # used password to login
free_proxy = ['http://www.xiongmaodaili.com/xiongmao-web/api/glip?secret=66311ee5ec03163c4722632eddf168f7&orderNo=GL20180416164758V2LW1eYs&count=1&isTxt=1']
# This function provides many ip address
def getip():
    res=request.urlopen(free_proxy[0])
    ip=res.read()
    return ip.decode('utf-8')
# configure the web driver

dvropt = Options()
'''
ip = getip()
print("IP address : %s"%(ip))
dvropt.add_argument('--proxy-server=%s' % ip)
'''
# dvropt.add_argument('--proxy-server=47.92.32.25:16817')
# dvropt = add_argument("headless")# to hide the browser window, uncomment this line.
# set the web driver
def insertD(c,qc,qb):
    try:
        c.execute("insert into patent(company_name,company_id,zl_name,zl_sq_num,zl_sq_date,\
            zl_gk_num,zl_gk_date,type,zl_sq_name,zl_inventor,agent,agent_org,priority)VALUES(\
            '%s',%s,\
            '%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s'\
            )"%(qc[0],qc[1],qb[0].replace("'","''"),qb[1],qb[2],qb[3],qb[4],qb[5],qb[6],qb[7],qb[8],qb[9],qb[10]))
        print(">",end='')
    except sqlite3.IntegrityError:
        print("#",end='')
def clawlerT(id,start_point):

    bw = webdriver.Chrome(chrome_options=dvropt)
    #open the intro page
    try:
        # start_point=input("T%d>Please type in the company id to start:"%id)
        bw.get(page_login[1])

        # find element on page

        input_user = bw.find_element_by_id("j_username")
        input_pswd = bw.find_element_by_id("j_password_show")
        # bt_login = bw.find_element_by_class_name("btn btn-login")
        # input login info
        input_user.send_keys(u[id])
        input_pswd.send_keys(p[id])
        # login action
        input("Waiting for logging in>>>>>[ENTER]<<<<<")
        # bt_login.click()
        # current page should be the searching page
        bw.refresh()
    except Exception as e:
        print(e)
        exit()
    finally:
        # connect the local database
        print("connecting database...")
        localdb = sqlite3.connect("company.db3")
        c = localdb.cursor()
        print("fetching companys from database...")
        c.execute("select company_name, company_serial\
                    from company_info where batch=1 and company_serial >= %s order by company_id asc" % (start_point))
        company_list = c.fetchall()
        # trying to input the searching content
        for company_element in company_list: # loop
            print('\nCID=',company_element[1],end='')
            bw.get(page_search[1])
            time.sleep(1)
            input_search = bw.find_element_by_id("search_input")
            bt_search = bw.find_element_by_id("btn_generalSearch")
            input_search.send_keys(company_element[0])
            bt_search.click()
            #time.sleep(0.25)
            #bt_search.click()

            # current page after search should be the index page
            # a = bw.find_element_by_xpath("//*[@id=\"paging\"]/div/span[3]/a")
            #bw.refresh()
            while 1:
                time.sleep(3)
                if bw.page_source.find('请稍候')>0:
                    #print('continue waiting')
                    continue
                else:
                    break
            pgs=0
            try:
                n = int(bw.find_element_by_xpath('//*[@id="common_search_history"]/div/div/ul/li[1]/div/div[3]/span[1]').text.
                    split("篇")[0])
                pgs = int(n/12) # pgs have to be at least 1
                #print("Rows/>>>>>",n)
                if n<1:
                    continue
            except selenium.common.exceptions.NoSuchElementException:
                    #print('loadig info source 1 failed.')
                    try:
                        pgs = int(bw.find_element_by_xpath('//*[@id="resultMode"]/div/div[2]/div/div/div/div/p[1]').text.split(' ')[-2])
                        #print("Pages/>>>>>"+n)
                    except selenium.common.exceptions.NoSuchElementException:
                        #print("Source 2 was failed too, cannot get proper page information, mark company, continue.")
                        c.execute('update company_info set p=-1 where company_serial=%s'%company_element[1])
                        localdb.commit()
                        # exit()
                        continue
            # branch : just one page???
            if pgs>1:
                # loop
                # caculate how much pages we have to deal with

                #print(pgs)
                for pg in range(pgs):
                    # each single page
                    #print('###########################%d#########################'%pg)
                    i0=bw.find_element_by_xpath('//*[@id="resultMode"]/div/div[1]/ul').find_elements_by_tag_name("li")
                    for i in i0:
                        #print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
                        # check if sqn has already existed
                        qb=['','','','','','','','','','','']#name/sqn/sqd/gkn/gkd/col/sqp/ivt/agt/ago/prx
                        qb[0]=i.find_element_by_tag_name('b').text
                        P = i.find_elements_by_tag_name('p')
                        qb[1]=P[0].text.split(': ')[-1]
                        qb[2]=P[1].text.split(': ')[-1].replace('.','')
                        qb[3]=P[2].text.split(': ')[-1]
                        qb[4]=P[3].text.split(': ')[-1].replace('.','')
                        qb[5]=P[4].text.split(':\n')[-1].replace(' ;','').replace('\n',';')
                        qb[6]=P[5].text.split(':\n')[-1].replace(' ;','').replace('\n',';')
                        qb[7]=P[6].text.split(':\n')[-1].replace(' ;','').replace('\n',';')
                        if len(P) > 7:
                            ptext = []
                            for pp in P[7:]:
                                ptext.append(pp.text)
                            for pt in range(len(ptext)):
                                if ptext[pt].find("代理人") > -1:
                                    qb[8]=ptext[pt].split(': ')[-1]
                                    qb[9]=ptext[pt+1].split(': ')[-1]
                            for pt in range(len(ptext)):
                                if ptext[pt].find("优先权号") > -1:
                                    qb[10]=ptext[pt+1].split(': ')[-1]+' '+ptext[pt].split(': ')[-1]
                        #print(qb)
                        insertD(c,company_element,qb)

                    # click action, next page
                    if pg != pgs:
                        btnext=bw.find_element_by_link_text('下一页')
                        btnext.send_keys(webdriver.common.keys.Keys.RETURN)
                    # wait for server
                    while 1:
                        time.sleep(3)
                        if bw.page_source.find('请稍候')>0:
                            #print('continue waiting')
                            continue
                        else:
                            break
                    # easy work
                    localdb.commit()
            i0=bw.find_element_by_xpath('//*[@id="resultMode"]/div/div[1]/ul').find_elements_by_tag_name("li")
            for i in i0:
                #print(">",end='')
                # check if sqn has already existed
                qb=['','','','','','','','','','','']#name/sqn/sqd/gkn/gkd/col/sqp/ivt/agt/ago/prx
                qb[0]=i.find_element_by_tag_name('b').text
                P = i.find_elements_by_tag_name('p')
                qb[1]=P[0].text.split(': ')[-1]
                qb[2]=P[1].text.split(': ')[-1].replace('.','')
                qb[3]=P[2].text.split(': ')[-1]
                qb[4]=P[3].text.split(': ')[-1].replace('.','')
                qb[5]=P[4].text.split(':\n')[-1].replace(' ;','').replace('\n',';')
                qb[6]=P[5].text.split(':\n')[-1].replace(' ;','').replace('\n',';')
                qb[7]=P[6].text.split(':\n')[-1].replace(' ;','').replace('\n',';')
                if len(P) > 7:
                    ptext = []
                    for pp in P[7:]:
                        ptext.append(pp.text)
                    for pt in range(len(ptext)):
                        if ptext[pt].find("代理人") > -1:
                            qb[8]=ptext[pt].split(': ')[-1]
                            qb[9]=ptext[pt+1].split(': ')[-1]
                    for pt in range(len(ptext)):
                        if ptext[pt].find("优先权号") > -1:
                            qb[10]=ptext[pt+1].split(': ')[-1]+' '+ptext[pt].split(': ')[-1]
                #print(qb)
                insertD(c,company_element,qb)
            #btnext=bw.find_element_by_link_text('下一页')
            #btnext.send_keys(webdriver.common.keys.Keys.RETURN)
            localdb.commit()
            time.sleep(2)
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
