import mmap, random, time, os

with open('pipe', 'r+') as pipe:
    pipe.write(str(random.randint(10000000, 99999999)))
    pipe.flush()
    while True:
        m=mmap.mmap(pipe.fileno(), 0)
        m.write(bytes(str(random.randint(10000000, 99999999)), 'utf-8'))
        m.flush()
        m.close()
        time.sleep(1)
