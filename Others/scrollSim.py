import time
from pynput.mouse import Controller

m=Controller()

while True:
    time.sleep(1)
    m.scroll(0,-100)
