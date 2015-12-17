#!/usr/bin/python

import math


def solve(eqs, x, eps):
    mdiff = 0.0
    ic = 0
    p = x
    while True:
        ic += 1
        p = x
        x = [var(*x) for var in eqs]
        mdiff = max(abs(x[0] - p[0]),
                    abs(x[1] - p[1]))
        if mdiff < eps:
            return x, ic

if __name__ == "__main__":
    eqs = [lambda x, y: math.sqrt((x*(y+5)-1)/2),
           lambda x, y: math.sqrt(x + 3 * math.log10(x))]
    eps = 0.1
    for i in range(0, 20):
        x = [3.5, 2.5]
        result, iter_count = solve(eqs, x, eps)
        print result, iter_count, eps
        eps /= 10.0
