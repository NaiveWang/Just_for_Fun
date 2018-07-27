# Patent Crawler/专利抓取脚本
This script crawls information of target patents via manipulating web page in a automated way.
The target source page, however, has some CAPTCHA which this script cannot nail them down.
But the script could detect them and pause, wait for user's help.
此脚本通过自动化的操作网页驱动然后抓取页面元素来获得专利信息。
但是抓取过程中有一些人机验证本脚本无能为力，但是能把它们检测出来， 并等待使用者手动来操作。

##Author
Elvin Wang/王植文/中科院计算机所烟台分所-实习

## v1.0 - July/18/2018

### features/特点
1. Crawler(patent_crawler.py) Writes data into a local database(company.db3)
2. Get company list from remote database by running an additional script(import_merged_list.py)
3. Crawler could conquer any issues except for network connection failure, database operating failure and CAPTCHA

### usage/用法
1. run patent_crawler.py or run makefile directly.
2. input the company id to set the start point which skips companys you have already crawled.
3. note that the script may pause when mets CAPTCHA, then handle the test and then type anything to resume the script.
4. be careful although the crawler has been robust enough, there are still some pitfalls caused by connection timeout, then the script would not get proper data from pages and may skip some patents which should have been traversed.

### prerequisites/环境配置:
linux
python3+pymysql/sqlite3/time/selenium(chromedriver<the latest version>)
db browser for sqlite
