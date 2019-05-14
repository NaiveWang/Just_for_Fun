 
from urllib import request as req
from lxml import html
from selenium import webdriver
from selenium.webdriver.chrome.options import Options

# bw = webdriver.Chrome()

url1="http://www.qhdkjj.gov.cn/news-list-zdhd.html"
xph1="/html/body/table/tbody/tr[2]/td/table/tbody/tr/td[2]/table/tbody/tr[4]/td/table/tbody/tr/td[4]/table/tbody/tr/td/table/tbody/tr[3]/td/table/tbody/tr/td/div/div/div/form/table/tbody/tr[1]/td/table/tbody/tr/td/table/tbody/tr/td[1]/a"
xph1n="/html/body/table/tbody/tr[2]/td/table/tbody/tr/td[2]/table/tbody/tr[4]/td/table/tbody/tr/td[4]/table/tbody/tr/td/table/tbody/tr[3]/td/table/tbody/tr/td/div/div/div/form/table/tbody/tr[2]/td/div/ul/li[2]/a[3]"
url1u='http://www.qhdkjj.gov.cn/news-list-zdhd-<<<>>>1<<<>>>.html'

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



#jsfree_multi_url(url1u,xph1)
