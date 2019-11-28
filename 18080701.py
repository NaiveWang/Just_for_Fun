# python3
import pymysql
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
import time
url = 'http://10.20.16.1:7070/test_cnkeet.html'
# set up browser
opt = Options()
bw = webdriver.Chrome(chrome_options=opt)
# connect db
db = pymysql.connect(host='10.6.12.3', user='cd_back', password='123456', database='gjkj',charset='utf8')
c = db.cursor()
# get data
c.execute('SELECT id,name,introduce FROM gjkj.t_achievement_info where keywords=""')
rowz = c.fetchall()
for row in rowz:
    print(row[1])
    bw.get(url)
    #time.sleep(0.3)
    bw.find_element_by_id('title').send_keys(row[1])
    bw.find_element_by_tag_name('textarea').send_keys(row[2])
    bw.find_element_by_xpath('/html/body/table/tbody/tr[4]/td[2]/input').click()
    #b.click()
    #input()
    #time.sleep(10)
    keyz = bw.page_source.split(':"',1)[-1].split('"',1)[0].split(')[')
    del(keyz[-1])
    while len(keyz) > 4:
        del(keyz[-1])
    keyf = ''
    for keye in keyz:
        keyf+=keye.split('(',1)[-1]+' '
    keyf = keyf[:-1]
    print('$'+keyf+'$')
    c.execute('update gjkj.t_achievement_info set keywords="%s" where id="%s"'%
    (keyf,row[0]))
    db.commit()
