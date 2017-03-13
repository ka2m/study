from random import random
from functools import reduce
from math import log, sqrt


def rand_exponential(l):
    return (- 1.0 / l) * log(random())

def rand_uniform(a, b):
    return a + random() * (b - a)


max_tries = 10000
exp_length = 2.0


negativeParticles = []
positiveParticles = []

for _ in range(1000):
    distance = rand_exponential(2.0)
    direction = rand_uniform(0.0, 1.0)
    if direction >= 0.5:
        positiveParticles.append(distance)
    else:
        negativeParticles.append(distance)

allParticles = negativeParticles + positiveParticles

expected_value = round(reduce(lambda x, y: x + y,
                              allParticles) / max_tries
                       , 3)

mean = sqrt(round(
    reduce(lambda x, y: x + y,
           map(lambda z:
               (z - expected_value) ** 2,
               allParticles[0:-1])) / (max_tries - 1), 3)**2)


print("Оценка мат. ожидания координаты: ", expected_value)
print("Среднее квадратчиное отклонение: ", mean)
