# sub process is the c file
import os

print('#'+os.popen('./subp').read()+'#')
