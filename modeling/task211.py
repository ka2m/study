from random import random


def random_in_range(x, p):
    M = random()
    for i in range(len(p)):
        M -= p[i]
        if M <= 0:
            return x[i]

all_tries = 10000
first_won = 0

for _ in range(all_tries):
    if 6 in [random_in_range(range(1, 7), [1. / 6.] * 6) for _ in range(4)]:
        first_won += 1

print("число игр: {0}".format(all_tries))
print("побед игрока с шестерками: {0}".format(first_won))
print("побед другого игрока: {0}".format(all_tries - first_won))
print("вероятность победы игрока с шестерками: {0}".format(round(first_won / all_tries, 4)))

allItems = []
k = 0
for a in range(1, 7):
    for b in range(1, 7):
        for c in range(1, 7):
            for d in range(1, 7):
                allItems.append([a, b, c, d])
                if 6 in [a, b, c, d]:
                    k += 1

print("Статическая проверка полученных результатов (вероятность выпадения 6 на 4 кубиках): {0}".format(k/ len(allItems)))
