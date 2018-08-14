global a
b = 'abc'
def inner():
    global b
    global a
    a = 0
    b+='d'
    print(b)
def post():
    global a
    global b
    print(a)
    print(b)
inner()
post()
