from selenium import webdriver
from selenium.webdriver.common.keys import Keys
page00 = "http://forum.home.news.cn/detail/141261449/1.html"
bw = webdriver.Firefox()
bw.get(page00)

btn = bw.find_element_by_class_name("de-zan")
while 1 :
    btn.click()
