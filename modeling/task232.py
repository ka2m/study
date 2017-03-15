from random import random
from math import log


def rand_exponential(l):
    return (- 1.0 / l) * log(random())

t = 0.0
flow_size = 1.0
total_time_intervals = 1000
interval_step = 3.0

highlight_intervals = []
particle_count = 0

vals = [t]
for _ in range(total_time_intervals):
    vals.append(vals[-1] - rand_exponential(flow_size))

low_boundry = 0.0
high_boundry = interval_step
for _ in range(total_time_intervals):
    cnt = len([x for x in vals if abs(x) >= low_boundry and abs(x) <= high_boundry])
    if cnt >= 3:
        highlight_intervals.append(int(high_boundry))
    low_boundry += interval_step
    high_boundry += interval_step


print("Вероятность того, что лампочка горит: ", len(highlight_intervals)/total_time_intervals)
