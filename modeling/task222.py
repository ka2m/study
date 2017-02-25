from random import random
from functools import reduce


def rand_normal(mu, sigma):
    sumr = 0
    for it in range(12):
        sumr += random()
    return round(mu + sigma * (sumr - 6.), 3)

max_tries = 1000
max_bags = 5
real_mu = 5.
real_sigma = 0.03

customer_sigma = 0.1

real_bags = [rand_normal(real_mu, real_sigma)
             for _ in range(max_bags)]

real_max_wght = max(real_bags)

print("Реальные веса мешков (кг): ", real_bags)
print("Реальный максимальный вес (кг): ", real_max_wght)

count_wins = 0
all_customer_choices = []

for _ in range(max_tries):
    customer_choice = max([rand_normal(rbw, customer_sigma)
                           for rbw in real_bags])
    all_customer_choices.append(customer_choice)
    if customer_choice >= real_max_wght:
        count_wins += 1

answer = round(reduce(lambda x, y: x + y, all_customer_choices) / max_tries, 3)

print("Мат. ожидание веса <<тяжелого>> мешка: ", answer)

print("Вероятность выбора самого тяжелого мешка: ",
      round(count_wins / max_tries, 2))
