import hashlib
key =  open('11.pdf','rb').read()
lock = open('0.pdf','rb').read()
print(hashlib.md5(key).hexdigest)
print(hashlib.md5(lock).hexdigest)
print(len(key))
print(len(lock))
if hashlib.md5(key).digest() == hashlib.md5(lock).digest():
    print('match')
else:
    print('mismatch')
