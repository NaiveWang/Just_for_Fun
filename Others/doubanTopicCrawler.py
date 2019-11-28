from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import time

douban_zhengyoudahui='https://www.douban.com/gallery/topic/51644/'


driver = webdriver.Firefox()
driver.get(douban_zhengyoudahui)

i=2

while 1:
    i-=1
    if i<=0 :
        i=int(input('>>>PRESS ANY KEY TO CONTINUE<<<'))
    driver.find_element_by_tag_name('body').send_keys(Keys.END)
    time.sleep(5)
    try:
        expand = driver.find_elements_by_partial_link_text('(展开)')

        for e in expand:
            try:
                e.click()
            except Exception as e:
                print("inner loop",e)
    except Exception as e:
        print(e)
    try:
        expand = driver.find_elements_by_partial_link_text('(展开)')

        for e in reversed(expand):
            try:
                e.click()
            except Exception as e:
                print("inner loop reversed",e)
    except Exception as e:
        print(e)
