from selenium import webdriver
from selenium.webdriver.common.keys import Keys
page00 = "http://forum.home.news.cn/detail/141261449/1.html"
bw = webdriver.Firefox()
bw.get(page00)

btn1 = bw.find_element_by_id("etx2141270741")
btn2 = bw.find_element_by_class_name("de-zan")
cnt = 0
while 1 :
    cnt+=1
    print('我他妈又赞了一下, 这个线程已经他奶奶的赞了',cnt,'下')
    btn1.click()
    btn2.click()
