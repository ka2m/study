#!/usr/bin/python

from lib import split_range

V = 11
EPS = 10**(-8)

def calc_result(x):
    item = x
    result = item
    step = 1
    while abs(item) > EPS:
        item = (item * item * item) / ((step * 2) * (step * 2 + 1))
        if step % 2:
            result -= item
        else:
            result += item
        step += 1
    return result, step

if __name__ == "__main__":
    answer = []
    for x in split_range(-1, 1, 10):
        answer.append((x, calc_result(x)))

    print '\t  '.join([str(x[0]) for x in answer])
    print '\t'.join([str(round(x[1][0], 4)) for x in answer])
    print '\t  '.join([str(x[1][1]) for x in answer])
