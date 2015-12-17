#!/usr/bin/python

import math
from task21_gauss import reverse as gauss_reverse


def derivative(f, x0, itm=0, delta=1e-10):
    if not isinstance(x0, list):
        x0 = [x0]
    xd = x0[:itm] + [x0[itm] + delta] + x0[itm + 1:]
    print 'xd', xd
    return (f(*xd) - f(*x0)) / delta + 0.000000000000000001


def solve(eqs, x, eps):
    if not isinstance(x, list):
        x = [x]
    delta = eps * 10
    ic = 0

    while delta > eps:
        ic += 1
        jacobian = [[derivative(f, x, itm=i) for i in range(len(x))]
                    for f in eqs]
        _t = gauss_reverse(jacobian)
        print _t
        _tminus = [[-_t[i][j] for j in range(len(_t[i]))] for i in range(len(_t))]
        F = [f(*x) for f in eqs]
        new_dx = []
        for i in range(len(_t)):
            new_dx.append(0.0)

        for i in range(len(_t)):
            for k in range(len(_t)):
                new_dx[i] += _tminus[i][k] * F[k]
        print _tminus
        print new_dx
        new_x = [x[i] + new_dx[i] for i in range(len(x))]
        print new_x, x, delta
        delta = max([abs(new_x[i] - x[i]) for i in range(len(x))])
        x = new_x
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
