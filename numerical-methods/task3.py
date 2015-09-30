#!/usr/bin/python

from math import sin
from lib import split_range, split_between, join_between_range


def divided_sub(xlist, ylist):
    lyl = len(ylist)
    ds = [[0]*(lyl) for i in range(lyl)]
    for i in xrange(lyl):
        ds[0][i] = ylist[i]
    for i in xrange(1, lyl):
        for j in xrange(lyl - i):
            ds[i][j] = (ds[i - 1][j] - ds[i - 1][j + 1]) \
                / (xlist[j] - xlist[j + i])
    return ds


def newton(x0, xlist, ylist):
    ds = divided_sub(xlist, ylist)
    res = ds[0][0]
    xdiff = 1
    for i in xrange(1, len(ylist)):
        xdiff *= (x0 - xlist[i-1])
        res += ds[i][0] * xdiff
    return res


def test():
    x2_dots = [1.0, 2.0, 3.0]
    x2_values = [x**2 for x in x2_dots]
    x2_all_dots, x2_inb_dots = split_between(x2_dots)
    res = [newton(y, x2_dots, x2_values) for y in x2_inb_dots]
    print '------ test 1 -----'
    print 'original x: ', x2_dots
    print 'original y: ', x2_values
    print 'between original x: ', x2_inb_dots
    print 'newton: ', res
    print 'final result (x): ', x2_all_dots
    print 'final result (y): ', join_between_range(x2_values, res)


def test2():
    print '------ test 2 -----'
    orig_range = split_range(-1.0, 1.0, 10)
    orig_results = [sin(x) for x in orig_range]
    new_range, only_new_range = split_between(orig_range)
    orig_full_results = [sin(x) for x in new_range]

    new_results = [newton(x, orig_range, orig_results) for x in only_new_range]
    new_results_on_old_range = [newton(x, orig_range, orig_results) for x in orig_range]

    print orig_full_results
    all_results = join_between_range(new_results_on_old_range, new_results)
    print all_results
    print [abs(x[0] - x[1]) for x in zip([round(y, 12) for y in orig_full_results],
                                         [round(y, 12) for y in all_results])]


if __name__ == "__main__":
    test2()
