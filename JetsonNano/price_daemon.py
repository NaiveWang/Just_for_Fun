 
import matrix
import getprice
import time
_price = 0
price = 0
matrix.init()
while True:
    price=getprice.xmrusd()
    if price != _price:
        matrix.show(price,price-_price)
        _price=price
    
    time.sleep(10)
    
