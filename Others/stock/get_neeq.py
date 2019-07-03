from selenium import webdriver
import time
page='http://www.neeq.com.cn/nq/quotation.html?tabId=G'
page_ab='http://www.neeq.com.cn/nq/quotation.html?tabId=L'

driver = webdriver.Chrome()
driver.get(page)
f=open('so.txt','w')
while True:
    
    lst = driver.find_elements_by_xpath('/html/body/div[2]/div[2]/div[5]/div/div[1]/table/tbody/tr/td[1]/a')
    for e in lst:
        f.write(e.text+'\n')
        print(e.text)
    nbt=driver.find_element_by_link_text('>')
    nbt.click()
    time.sleep(0.7)
    
