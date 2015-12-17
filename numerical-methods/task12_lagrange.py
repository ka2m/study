#!/usr/bin/python

from lib import split_between, split_range
from math import sin
# lagrange


def lagrange(data, x):
    n = len(data)
    nx = len(x)

    dx = [d[0] for d in data]
    fy = [d[1] for d in data]
    L = [0.0]*(nx)

    def item(j, x_i):
        v = 1.0
        for k in xrange(n):
            if k != j:
                v *= (x_i-dx[k]) / (dx[j]-dx[k])
        return v

    for i, x_i in enumerate(x):
        for j in xrange(n):
            L[i] += fy[j] * item(j, x_i)

    return [round(t, 5) for t in L]


def test():
    x2_dots = [1.0, 2.0, 3.0]
    x2_values = [x**2 for x in x2_dots]
    x2_all_dots, x2_inbetween_dots = split_between(x2_dots)
    print 'old_values: %s' % ' ' .join(str(x) for x in zip(x2_dots, x2_values))
    L = lagrange(zip(x2_dots, x2_values), x2_inbetween_dots)
    new = []
    i = 0
    for x in x2_values:
        new.append(x)
        if i < len(L):
            new.append(L[i])
        i += 1
    print zip(x2_all_dots, new)


def task():
    old_range = split_range(-1.0, 1.0, 10)
    old_results = [round(sin(x), 8) for x in old_range]
    new_range, only_new_range = split_between(old_range)
    print 'x dots: %s' % ' '.join([str(x) for x in old_range])
    print 'sin(x) values: %s' % ' '.join([str(x) for x in old_results])
    print 'task 2 dots (in-between): %s' % ' '.join(str(x) for x in only_new_range)
    L = lagrange(zip(old_range, old_results), only_new_range)
    print 'task 2 results (la grange): %s' % ' '.join(str(x) for x in L)
    new = []
    i = 0
    for x in old_results:
        new.append(x)
        if i < len(L):
            new.append(L[i])
        i += 1
    print 'task 2 all pairs: %s' % ' '.join(str(x) for x in zip(new_range, new))


if __name__ == "__main__":
    test()
    print '---------'
    task()
