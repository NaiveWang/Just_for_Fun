# python3
 
from flask import Flask, render_template, request
import list_clawler_util as cwr
app = Flask(__name__)
@app.route('/jsfree')
def jsfree():
    url = request.args.get('url')
    xpath = request.args.get('xpath')
    list = cwr.jsfree_single(url,xpath)
    #print(list)
    return render_template('top.html', list = list)
@app.route('/jsfree/xpath')
def jsfree_xpath():
    url = request.args.get('url')
    xpath = request.args.get('xpath')
    xpathn = request.args.get('xpathn')
    list = cwr.jsfree_multi_xpath(url,xpath,xpathn)
    #print(list)
    return render_template('top.html', list = list)
@app.route('/jsfree/url')
def jsfree_url():
    url = request.args.get('url')
    xpath = request.args.get('xpath')
    list = cwr.jsfree_multi_url(url,xpath)
    #print(list)
    return render_template('top.html', list = list)


if __name__ == "__main__":
    app.run(debug=True)
