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
page_login = "https://login.zlbaba.com/login?service=https://www.patexplorer.com/login/cas"
page_search = "https://www.patexplorer.com/"

abstract_css_list = [
    "#Js_patent_view_container > div > div.fn-clear.Js_patent_view_item.ui-switchable-panel > div.g-info-l > div > div > div.Js_patent_view_content.ui-switchable-content > div:nth-child(1) > div > div.abstract.contenttext",
    "#Js_patent_view_container > div > div:nth-child(1) > div.g-info-l > div > div.Js_patent_view_content.ui-switchable-content > div:nth-child(1) > div > div.abstract.contenttext"
]



u = ["17862810565","18555131495","18615979059"] # used this user name to login
p = ["17862810565","18555131495","18615979059"] # used password to login
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

# dvropt.add_argument('--proxy-server=112.248.121.42:57856')#182.34.18.195:9077s
# dvropt = add_argument("headless")# to hide the browser window, uncomment this line.
# set the web driver

def clawlerT():

    bw = webdriver.Chrome(chrome_options=dvropt)

    #open the intro page
    try:
        # start_point=input("T%d>Please type in the company id to start:"%id)
        bw.get(page_login)

        # find element on page

        input_user = bw.find_element_by_id("Js_loginId")
        input_pswd = bw.find_element_by_name("password")
        bt_login = bw.find_element_by_id("loginBtn")
        # input login info
        input_user.send_keys(u[0])
        input_pswd.send_keys(p[0])
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
        print("fetching broken elements links from database...")
        c.execute("select zl_url,id from patent where zl_sq_num=''")
        url_list = c.fetchall()
        # trying to input the searching content
        for url_element in url_list: # loop
            bw.get(url_element[0].split('&')[0])
            try:
                time.sleep(0.3)
                if bw.page_source.find('过于频繁')!=-1:

                    input(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
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
                # abstract = bw.find_element_by_css_selector(abstract_css_list[linka]).text
                # print(abstract)#
                # write to database basic data
                c.execute("update patent set zl_name='%s',zl_sq_num='%s',zl_sq_date='%s',zl_sq_name='%s',zl_gk_num='%s',zl_gk_date='%s',zl_inventor='%s',type_main='%s',type='%s',address='%s',gs='%s' where id='%d'"%
                                                                (
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
                                                                url_element[1]
                                                                ))
                if flagp:
                    c.execute('update patent set priority=\"%s\" where id=\"%d\"' % (zlp,url_element[1]))
                if flaga:
                    c.execute('update patent set agent_org=\"%s\",agent=\"%s\" where id=\"%d\"'%(zlagc,zlag,url_element[1]))
                localdb.commit()
            except Exception as e:
                print(e)
                if bw.page_source.find('过于频繁')!=-1:
                    print("Thread %d : 中招了，填填二维码，带带大师兄。"%(id))
                    input()
                print('trying to reconnect...')
                # delay+=0.5
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
    bw.close()
# run the function
clawlerT()
