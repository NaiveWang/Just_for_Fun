from selenium import webdriver
import time
page='http://www.neeq.com.cn/nq/quotation.html?tabId=G'
page_ab='http://www.neeq.com.cn/nq/quotation.html?tabId=L'

driver = webdriver.Chrome()
driver.get(page)
f=open('so.txt','w')
while True:
    
    l1 = driver.find_elements_by_xpath('/html/body/div[2]/div[2]/div[5]/div/div[1]/table/tbody/tr/td[1]/a')
    l2 = driver.find_elements_by_xpath('/html/body/div[2]/div[2]/div[5]/div/div[1]/table/tbody/tr/td[2]')
    #/html/body/div[2]/div[2]/div[5]/div/div[1]/table/tbody[8]/tr/td[2]
    #/html/body/div[2]/div[2]/div[5]/div/div[1]/table/tbody[8]/tr/td[1]/a
    for e1, e2 in zip(l1, l2):
        f.write(e1.text+' '+e2.text+'\n')
        print(e1.text, e2.text)
    nbt=driver.find_element_by_link_text('>')
    nbt.click()
    time.sleep(1)
    
