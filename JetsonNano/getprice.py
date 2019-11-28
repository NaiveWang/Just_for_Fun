import urllib.request, json
def xmrusd():
    with urllib.request.urlopen("https://min-api.cryptocompare.com/data/price?fsym=XMR&tsyms=USD") as url:
        data = json.loads(url.read().decode())
        return data["USD"]

