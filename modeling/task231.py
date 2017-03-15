from random import random
from functools import reduce
from math import log, sqrt


def rand_exponential(l):
    return (- 1.0 / l) * log(random())


def rand_uniform(a, b):
    return a + random() * (b - a)


max_tries = 10000

allParticles = []

for _ in range(1000):
    distance = rand_exponential(2.0)
    direction = rand_uniform(0.0, 1.0)
    allParticles.append(distance if direction >= 0.5 else -distance)

expected_value = round(reduce(lambda x, y: x + y,
                              allParticles) / max_tries
                       , 3)

mean = sqrt(round(
    reduce(lambda x, y: x + y,
           map(lambda z:
               (z - expected_value) ** 2,
               allParticles)) / (max_tries - 1), 3))

print("Оценка мат. ожидания координаты: ", expected_value)
print("Среднее квадратчиное отклонение: ", mean)

