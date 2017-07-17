from urllib import request
from urllib import parse

import socket
socket.setdefaulttimeout(15)
def get_page(kw):

    url_learner = 'http://www.learnersdictionary.com/definition/'
    # initilization ended


    # url_learner=parse.quote(url_learner)
    url_learner += kw
    print(url_learner)
    response = request.urlopen(url_learner)
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
text = open('Improvise.html').read()


def HParser(html_text):
    html_text = html_text.split('def_text\">')
    del (html_text[0])
    voca = "improvise"
    c1=1
    print("\t\t"+voca)
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
            #print(eg)
            eg = eg.split('</div>', 1)
            del eg[-1]

            eg=eg[0]
            #print(eg.find('<em class="mw_spm_it">'))
            eg=eg.replace('<em class="mw_spm_it">','')
            eg=eg.replace('</em>', "")
            print('\texample '+c2.__str__()+": "+eg)
            c2+=1
        c1+=1

w=input()

HParser(get_page(w))