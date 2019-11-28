import hashlib
import time
import math

'''
function() {
        var t = Math.floor((new Date).getTime() / 1e3)
          , e = t.toString(16).toUpperCase()
          , i = md5(t).toString().toUpperCase();
        if (8 != e.length)
            return {
                as: "479BB4B7254C150",
                cp: "7E0AC8874BB0985"
            };
        for (var n = i.slice(0, 5), a = i.slice(-5), s = "", o = 0; 5 > o; o++)
            s += n[o] + e[o];
        for (var r = "", c = 0; 5 > c; c++)
            r += e[c + 3] + a[c];
        return {
            as: "A1" + s + e.slice(-3),
            cp: e.slice(0, 3) + r + "E1"
        }
    }
function e(t) {
        var e = ascp.getHoney()
          , i = "";
        window.TAC && (i = TAC.sign("refresh" === t ? 0 : r.params.max_behot_time_tmp)),
        r.params = _.extend({}, r.params, {
            as: e.as,
            cp: e.cp,
            max_behot_time: "refresh" === t ? 0 : r.params.max_behot_time_tmp,
            _signature: i
        })
    }
1567638110
1567652429
1567652164629

'''

def gen(t):
    if t is 0:
        return "479BB4B7254C150", "7E0AC8874BB0985"
    #t=math.floor(time.time())
    #print(t)
    e=hex(t)[2:].upper()
    #print(e)

    i=hashlib.md5(str(t).encode()).hexdigest().upper()
    #print(e, i)
    s=''
    n=i[:5]
    a=i[-5:]
    for o in range(5):
        #print(o)
        s+=n[o]+e[o]
    #print(s)
    r=''
    for c in range(5):
        r+=e[c+3] + a[c]
    #print(r)

    AS="A1"+s+s[-3:]
    CP=e[:3]+r+"E1"

    #print(AS, CP)
    return AS, CP
    

