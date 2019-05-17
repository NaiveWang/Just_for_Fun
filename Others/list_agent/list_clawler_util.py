 
from urllib import request as req
from lxml import html

import time
import _init_



url1="http://www.qhdkjj.gov.cn/news-list-zdhd.html"
xph1="/html/body/table/tbody/tr[2]/td/table/tbody/tr/td[2]/table/tbody/tr[4]/td/table/tbody/tr/td[4]/table/tbody/tr/td/table/tbody/tr[3]/td/table/tbody/tr/td/div/div/div/form/table/tbody/tr[1]/td/table/tbody/tr/td/table/tbody/tr/td[1]/a"
xph1n="/html/body/table/tbody/tr[2]/td/table/tbody/tr/td[2]/table/tbody/tr[4]/td/table/tbody/tr/td[4]/table/tbody/tr/td/table/tbody/tr[3]/td/table/tbody/tr/td/div/div/div/form/table/tbody/tr[2]/td/div/ul/li[2]/a[3]"
url1u='http://www.qhdkjj.gov.cn/news-list-zdhd-<<<>>>1<<<>>>.html'

url2="http://www.gzsi.gov.cn/gzsi/kpzl_kpjd/list.shtml"
xph2="/html/body/div[1]/div[3]/div[2]/div[2]/ul/li/a"
xph2b='//*[@id="page_div"]/span[8]/a'

def jsfree_single(url, xpath):
    tree = html.parse(req.urlopen(url))
    list = tree.xpath(xpath)
    dic={}
    for e in list:
        dic[e.text]=e.attrib['href']
        #print(e.text, e.attrib['href'])
    return dic

def jsfree_multi_xpath(url, xpath, xpath_next):
    dic={}
    try:
        while(True):
            tree = html.parse(req.urlopen(url))
            list = tree.xpath(xpath)
            for e in list:
                dic[e.text]=e.attrib['href']
                #print(e.text, e.attrib['href'])
            nextp=tree.xpath(xpath_next)
            url=nextp[0].attrib['href']
    except Exception as e:
        return dic

def jsfree_multi_url(url, xpath):
    url = url.split('<<<>>>')
    url[1] = int(url[1])
    dic={}
    try:
        while(True):
            tree = html.parse(req.urlopen(url[0]+url[1].__str__()+url[2]))
            list = tree.xpath(xpath)
            if len(list)==0:
                return dic
            for e in list:
                dic[e.text]=e.attrib['href']
                #print(e.text, e.attrib['href'])
            url[1]+=1
    except Exception as e:
        return dic
def js_single(url, xpath, delay=1):
    dic={}
    _init_.bw.get(url)
    time.sleep(delay)
    elm=_init_.bw.find_elements_by_xpath(xpath)
    for e in elm:
        dic[e.text]=e.get_attribute("href")
        #print(e.text, e.get_attribute("href"))
    return dic

def js_multi_click(url, xpath, xpath_next, delay=1, page=5):
    dic={}
    try:
        _init_.bw.get(url)
        for i in range(0,page):
            time.sleep(delay)
            elm=_init_.bw.find_elements_by_xpath(xpath)
            for e in elm:
                dic[e.text]=e.get_attribute("href")
                #print(e.text, e.get_attribute("href"))
            btn = _init_.bw.find_element_by_xpath(xpath_next)
            btn.click()
    except Exception as e:
        print(e)
        return dic
    return dic



#print(js_multi_click("http://www.moe.gov.cn/jyb_xwfb/gzdt_gzdt/","/html/body/div[2]/div[1]/div[6]/div[2]/div[1]/ul/li/a",'//*[@id="page"]/li[7]/a'))
