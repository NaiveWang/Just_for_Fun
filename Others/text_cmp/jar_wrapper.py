import os
'''
    Note : Implemented on Linux x64 enviroment, with java and python3
    This python file would execute the jar wrapper executible and
    extract data and prepare them for the flask server. 
    
    Some assumption are based on the format of java wrapper header.
'''
def gen_block():
    os.popen("java -jar text_cmp.jar 0").read()
def gen_chunk(lenB):
    os.popen("java -jar text_cmp.jar 1 %s"%lenB).read()
def cmp_post(src, dst):
    s=os.popen("java -jar text_cmp.jar 2 %s %s"%(src, dst)).read().split('\n')[:-1]
    lst = []
    
    for es in s:
        es=es.split(' ')
        tup = []
        for ees in es:
            tup.append(int(ees))
        lst.append(tup)
    return lst
def cmp_post_batch(src, dstL):
    s = ""
    for dst in dstL:
        s+=" "+dst.__str__()
    s=os.popen("java -jar text_cmp.jar 3 %s %d %s"%(src, len(dstL), s)).read().split('\n')[:-1]
    lst=[]
    for es in s:
        lst.append(int(es))
    return lst[0], lst[1:]
    
    
def cmp_instance(ins, lenB, dst):
    s=os.popen('java -jar text_cmp.jar 4 "%s" %s %s'%(ins, lenB, dst)).read().split("\n\n")[:-1]
    src=s[0].split('\n')
    lil=int(src[-1])
    del(src[-1])
    li=[]
    for esrc in src:
        li.append(esrc.split(" ")[-1])
    s=s[-1].split('\n')
    dst=[]
    dstc=int(s[-1])
    del s[-1]
    for es in s:
        es=es.split(' ')
        tup=[]
        for ees in es:
            tup.append(int(ees))
        dst.append(tup)
    return lil, li, dst, dstc
def cmp_instance_batch(ins, lenB, dstL):
    s = ""
    for dst in dstL:
        s+=" "+dst.__str__()
    s=os.popen('java -jar text_cmp.jar 5 "%s" %s %d %s'%(ins, lenB, len(dstL), s)).read().split("\n\n")[:-1]
    src=s[0].split('\n')
    lil=int(src[-1])
    del(src[-1])
    li=[]
    for esrc in src:
        li.append(esrc.split(" ")[-1])
    del(s[0])
        
    dstL=[]
    dstcL=[]
    for es in s:
        es=es.split('\n')
        dstcL.append(int(es[-1]))
        del(es[-1])
        tes=[]
        for ees in es:
            tees=[]
            ees=ees.split(' ')
            for eees in ees:
                tees.append(int(eees))
            tes.append(tees)
        dstL.append(tes)
    
    return lil, li, dstL, dstcL
