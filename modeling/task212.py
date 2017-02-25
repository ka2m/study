from random import random

max_bank_count = 4
max_try = 10000

probs = dict((k, 0) for k in range(0, max_bank_count + 1))


for _ in range(max_try):
    k = 0
    for _ in range(max_bank_count):
        r = random()
        if r <= 0.2:
            k += 1
    probs[k] += 1

print('Полученные результаты: ', probs)

for k in sorted(probs.keys()):
    print('Число банков: {0}. Вероятность банкротства: {1}'.format(k, round(probs[k] / max_try, 3)))
