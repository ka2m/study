#!/usr/bin/env python

CONST_L = 9000

def r(t):
    return 5000 - 500 * (t - 1)

def s(t, l=CONST_L):
    if t == 0:
         return 0
    return l / (2 ** t)

def c(t, l=CONST_L):
    return l * t / 10

def table(n):
    table = []
    for t in range(n):
        table.append([t, r(t), c(t), s(t)])
    return table


def f_s(i, t, l, n):

    return r(t) - c(t) + (f_max(i+1, t+1, l, n)[0] if i < n else s(t+1))

def f_r(i, t, l, n):
    return r(0) + s(t) - c(0) - l + (f_max(i+1, 1, l, n)[0] if i < n else s(1))

def f_max(i, t, l, n):
    fs = f_s(i, t, l, n)
    fr = f_r(i, t, l, n)
    if fs > fr:
        res = (fs, 's')
    elif fs == fr:
        res = (fs, 'sr')
    else:
        res = (fr, 'r')
    print "i={}, t={}, res={}".format(i, t, res)
    return res



print f_max(1, 2, CONST_L, 4)
