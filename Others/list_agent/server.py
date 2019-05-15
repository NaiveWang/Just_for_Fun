# python3
 
from flask import Flask, render_template, request
import list_clawler_util as cwr
app = Flask(__name__)
@app.route('/')
def top():
    return render_template('top.html', link="/")

@app.route("/", methods=['POST'])
def gen():
    api=request.form['api']
    url=request.form['url'].replace('&','%26')
    xpath=request.form['xph']
    xpathn=request.form['xphn']
    delay=request.form['delay']
    lgen=api+"?url="+url+"&xpath="+xpath+"&xpathn="+xpathn+"&delay="+delay
    
    return render_template('top.html', link=lgen)



@app.route('/jsfree')
def jsfree():
    url = request.args.get('url')
    xpath = request.args.get('xpath')
    list = cwr.jsfree_single(url,xpath)
    #print(list)
    return render_template('list.html', list = list)
@app.route('/jsfree/xpath')
def jsfree_xpath():
    url = request.args.get('url')
    xpath = request.args.get('xpath')
    xpathn = request.args.get('xpathn')
    list = cwr.jsfree_multi_xpath(url,xpath,xpathn)
    #print(list)
    return render_template('list.html', list = list)
@app.route('/jsfree/url')
def jsfree_url():
    url = request.args.get('url')
    xpath = request.args.get('xpath')
    list = cwr.jsfree_multi_url(url,xpath)
    #print(list)
    return render_template('list.html', list = list)
@app.route('/js')
def js():
    url = request.args.get('url')
    xpath = request.args.get('xpath')
    try:
        delay = int(request.args.get('delay'))
    except Exception:
        delay = 3
    list = cwr.js_single(url,xpath,delay)
    #print(list)
    return render_template('list.html', list = list)
@app.route('/js/click')
def js_xpath():
    url = request.args.get('url')
    xpath = request.args.get('xpath')
    xpathb = request.args.get('xpathn')
    try:
        delay = int(request.args.get('delay'))
    except Exception:
        delay = 3
    #print(xpathb)
    list = cwr.js_multi_click(url,xpath,xpathb,delay)
    #print(list)
    return render_template('list.html', list = list)
if __name__ == "__main__":
    app.run(debug=False)
    
