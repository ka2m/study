#!/usr/bin/python


def asum(xl, al, k, size):
    res = 0.0
    for j in range(k, size):
        res += al[k][j] * xl[j]
    return res


def directFlow(al, bl, size):
    t = []
    for i in range(0, size):
        l = []
        for j in range(0, size):
            l.append(0.0)
        t.append(l)

    for k in range(0, size - 1):
        for i in range(k + 1, size):
            t[i][k] = al[i][k] / al[k][k]
            bl[i] -= t[i][k] * bl[k]
            for j in range(k + 1, size):
                al[i][j] -= t[i][k] * al[k][j]


def reverseFlow(xl, al, bl, size):
    xl[size - 1] = bl[size - 1] / al[size - 1][size - 1]
    for k in reversed(range(0, size - 1)):
        xl[k] = (bl[k] - asum(xl, al, k, size)) / al[k][k]


def solve(al, bl):
    size = len(al)
    xl = [0.0 for x in range(size)]
    directFlow(al, bl, size)
    reverseFlow(xl, al, bl, size)
    return xl

if __name__ == "__main__":
    a = [[2.0, -5.0, 3.0],
         [4.0, 0.0, -1.0],
         [-9.0, 6.0, 2.0]]
    b = [3.0, -1.0, 2.0]
    print 'solve'
    print solve(a, b)
