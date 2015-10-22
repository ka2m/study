#!/usr/bin/python
# cubic splines

from math import sin
from lib import split_range, split_between


class SplineElement:
    a, b, c, d, x = [0., 0., 0.0, 0., 0.]

    def __str__(self):
        return "a: %f\nb: %f\nc: %f\nd: %f\nx: %f\n" % (self.a,
                                                        self.b,
                                                        self.c,
                                                        self.d,
                                                        self.x)


def build_spline(x_list, y_list, n):
    splines = [SplineElement() for x in range(0, n)]

    for tpl in zip(splines, x_list, y_list):
        tpl[0].x = tpl[1]
        tpl[0].a = tpl[2]

    splines[0].c = splines[n - 1].c = 0.0

    alpha = [0.0 for x in range(0, n - 1)]
    beta = [0.0 for x in range(0, n - 1)]

    for i in range(1, n - 1):
        hi = x_list[i] - x_list[i - 1]
        hi1 = x_list[i + 1] - x_list[i]
        a = hi
        c = 2. * (hi + hi1)
        b = hi1
        f = 6.0 * ((y_list[i + 1] - y_list[i]) / hi1 - (y_list[i] - y_list[i - 1]) / hi)
        z = a * alpha[i - 1] + c

        alpha[i] = -b / z
        beta[i] = (f - a * beta[i - 1]) / z

    for i in reversed(range(0, n - 2)):
        splines[i].c = alpha[i] * splines[i + 1].c + beta[i]

    for i in reversed(range(0, n - 1)):
        hi = x_list[i] - x_list[i - 1]
        splines[i].d = (splines[i].c - splines[i - 1].c) / hi
        splines[i].b = hi * (2. * splines[i].c + splines[i - 1].c) / 6. + (y_list[i] - y_list[i - 1]) / hi

    return splines


def build_f(x, splines):
    se = SplineElement()
    n = len(splines)
    if (x <= splines[0].x):
        se = splines[1]
    elif (x >= splines[n - 1].x):
        se = splines[n - 1]
    else:
        l = 0
        r = n - 1
        while l + 1 < r:
            m = l + (r - l) / 2
            if x <= splines[m].x:
                r = m
            else:
                l = m
        se = splines[r]
    dx = (x - se.x)
    return se.a + (se.b + (se.c / 2. + se.d * dx / 6.) * dx) * dx


if __name__ == "__main__":
    x_list = split_range(-1, 1, 10)
    y_list = [sin(x) for x in x_list]
    n = len(x_list)
    splines = build_spline(x_list, y_list, n)
    x_all, x_btwn = split_between(x_list)
    res_f = [sin(x) for x in x_all]
    res_spline = [build_f(x, splines) for x in x_all]

    print '\t'.join(str(x) for x in x_all)
    print '-------'
    print '  '.join(str(round(y, 8)) for y in res_f)
    print '-------'
    print '  '.join(str(round(x, 8)) for x in res_spline)
    print '-------'
    print '  '.join(str(abs(x[0] - x[1])) for x in zip([round(y, 8) for y in res_f],
                                                       [round(y, 8) for y in res_spline]))
