from random import random
from functools import reduce


def rand_normal(mu, sigma):
    sumr = 0
    for it in range(12):
        sumr += random()
    return mu + sigma * (sumr - 6.)

mu = 100.
sigma = 10.
max_tests = 1000

mix_results = []

answer = round(reduce(lambda x, y: x + y,
               [2 * min(rand_normal(mu, sigma), rand_normal(mu, sigma))
                for _ in range(max_tests)]) / max_tests, 3)

print("Мат. ожидание веса смеси: {0} кг".format(answer))
