#!/usr/bin/env python

with open('input', 'r') as f:
    a = int(f.readline())
    b = int(f.readline())
    xs = map(int, f.readline()[:-1].split(" "))
    qxs = map(float, f.readline()[:-1].split(" "))

q = {}

print "x  " + "     ".join(map(str,xs))
print "qx " + "   ".join(map(str,qxs))
i = 0
for x in xs:
    q[x] = qxs[i]
    i += 1



def p(x):
    if x < xs[0]:
        return 0 
    return q[x] * P(x-1)
    
    
def P(x):
    s = 0
    for i in range(x+1):
        s += p(i)
    return 1 - s

def O(x):
    s = 0
    for i in range(x):
        s += P(i)
    return s


print "px " + "  ".join(map(lambda x: str(round(p(x), 2)), xs))
print "Px " + "  ".join(map(lambda x: str(round(P(x), 2)), xs))
print "Ox " + "  ".join(map(lambda x: str(round(O(x), 2)), xs))

def s(x):
    return (a + b) * (1 - P(x-1)) + b * P(x-1)


print "sx " + "  ".join(map(lambda x: str(round(s(x), 2)), xs))

def K(x):
    return s(x)/O(x)

print "Kx " + "  ".join(map(lambda x: str(round(K(x), 2)), xs))
