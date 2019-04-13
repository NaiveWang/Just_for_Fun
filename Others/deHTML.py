
'''
 This script will delete all of the HTML tags like <*>, and which remains are the raw text content.
 it's very useful when the text file is too big to process in a editor. 
'''
file_name = "raw.txt"
 
raw = open(file_name).read()
 
w = open("post_raw.txt","w")
 
flag = False
 
for c in raw:
    if c=='>':
        flag = False
        continue
    elif c=='<':
        flag = True
        continue
    elif flag==True:
        continue
    w.write(c)
w.close()
 
 
 
 
