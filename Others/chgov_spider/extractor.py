from lxml import html
import sqlite3
db=sqlite3.connect('_gov.db')
c=db.cursor()
i=0
c.execute('select id, raw from posts where tag<>0')
cf=c.fetchall()
for r in cf:
    text =r[1]
    tree = html.document_fromstring(text)
    #print(tree)
    title = tree.xpath('/html/body/div/div/div/h1')
    contentl = tree.xpath('//*[@id="UCAP-CONTENT"]/p')

    if len(title) > 0 and len(contentl) > 0:
        ti = title[0].text.replace(' ', '')
        co=''
        ke=text.split('<meta name="keywords" content="', 1)[-1].split('">', 1)[0]
        #print('>>>', ke, '<<<')
        for content in contentl:
            if content.text is not None:
                co+=content.text.replace(' ', '').replace('\t', '')
            #print('#', end='')
        c.execute('insert into eposts(id, title, content, tags)values(?, ?, ?, ?)',(
            r[0], ti, co, ke))
        i+=1
        #if i%10000==0:
        #    print(i)
db.commit()
print(i)
    #print(t, '<<<')
