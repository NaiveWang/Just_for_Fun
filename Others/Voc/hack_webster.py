from urllib import request
from urllib import parse

import socket
socket.setdefaulttimeout(15)
def get_page(kw):

    url_learner = 'http://www.learnersdictionary.com/definition/'
    # initilization ended


    # url_learner=parse.quote(url_learner)
    url_learner += kw
    #print(url_learner)
    print("Searching "+kw)
    try:
        response = request.urlopen(url_learner)
    except Exception:
        print('What the phuck did U just input??')
        return ''
    try:
        html = response.read()
    except Exception:
        print("Your network just fucked up.")
        # !!!
        return ''
    else:

        return bytes.decode(html)

# <span class="def_text">$</span>
# <div class="vi_content"><em class="mw_spm_it">improvisational</em>
#word = input()

def HParser(html_text):
    html_text = html_text.split('def_text\">')
    del (html_text[0])
    c1=1
    #print("\t\t"+voca)
    for meaning in html_text:
        meaning = meaning.split('<', 1)
        print("meaning "+c1.__str__()+": "+meaning[0])
        del (meaning[0])
        #print(meaning[0])
        meaning = meaning[0]
        meaning = meaning.split('vi_content\">')
        del(meaning[0])
        c2=1
        for eg in meaning:

            eg = eg.split('</div>', 1)
            #print(eg)
            del eg[-1]
            #print(eg)
            eg=eg[0]
            #print(eg.find('<em class="mw_spm_it">'))
            eg=eg.replace('<em class="mw_spm_it">','')
            eg=eg.replace('<span class="mw_spm_phrase">','')
            eg=eg.replace('</span>','')
            eg=eg.replace('</em>', "")
            print('\texample '+c2.__str__()+": "+eg)
            c2+=1
        c1+=1


print('Welcome to my dict script alpha version 1.1 !')
print('Current Dictionary : Webster for English Learners.')
while 1:
    print('Keep your internet connected & input a word now, or type \'q\' to quit.')
    w = input()
    if w=='q':
        break
    try:
        HParser(get_page(w))
    except Exception:
        continue

