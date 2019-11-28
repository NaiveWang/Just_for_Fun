import mmap, time

with open('pipe', 'r+') as pipe:
    while True:
        m=mmap.mmap(pipe.fileno(), 0)
        print(m[:8])
        time.sleep(0.9)
