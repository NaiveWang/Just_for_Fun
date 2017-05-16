'''
customize\op\bound
'''
LETTER = ('_','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        'a','b','c','d','e', 'f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z')
L_D = ('_','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        'a','b','c','d','e', 'f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
       '0', '1','2', '3', '4', '5', '6', '7', '8', '9' )
DIGIT = ('0','1','2','3','4','5','6','7','8','9','.')
WRITESPACE = (' ','\t','\n')
global nid
nid = 0
nim = 0
file = open('reserved.txt')
text = file.read()
file.close()
text = text.split('\n#\n')
temp0 = text[0].split('\n')
temp1 = text[1].split('\n')
id = [[]]
op = [[]]
for a in temp0:
    id.append(a.split(' '))
for a in temp1:
    op.append(a.split(' '))
del(id[0])
del(op[0])
stmt = open('stmt.out','w')
symbol = open('symbol.out','w')

def IDChecker(s):
    i=0
    global nid
    global nim
    tag = 0
    for t in LETTER:
        if s[i]==t[0]:
            i+=1
            tag = 1
            break
    if tag==0:
        while 1:
            for t in DIGIT:
                if t==s[i]:
                    i+=1
                    tag=1
                    break
            if tag==1:
                tag=0
                continue
            else:
                if(i>0):
                    stmt.writelines('IM'+s[0:i]+'\n')
                    nim+=1
                return i

    while 1:
        for t in L_D:
            if s[i]==t[0]:
                i+=1
                tag=0
                break
        if tag==0:
            tag=1
            continue
        else:
            temp=[]
            temp.append('ID'+nid.__str__())
            temp.append(s[0:i])
            id.append(temp)
            stmt.writelines('ID'+nid.__str__()+'\n')
            symbol.writelines('ID '+nid.__str__()+'\n')
            nid+=1
            return i


def Checker(s):
    for a in WRITESPACE:
        if s[0] == a:
            return 1
    for a in op:
        #print(len(a[1]))
        if s[0:len(a[1])] == a[1]:
            stmt.writelines(a[0]+'\n')
            return len(a[1])
    for a in id:
        tag = 0
        if s[0:len(a[1])] == a[1]:
            print(s[0:len(a[1])])
            print(a[1])
            for b in L_D:
                if s[len(a[1])] == b[0]:
                    tag=1
                    break
            if tag==0:
                stmt.writelines(a[0]+'\n')
                return len(a[1])
    return IDChecker(s)

file = open('easy.ec')

text = file.read()
file.close()
while len(text)>0:
    n = Checker(text)
    if n== 0:
        print('Wrong')
        break
    text = text[n:]
    print(text)
stmt.close()