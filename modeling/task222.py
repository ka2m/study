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

count_wins = 0
all_real_bags = []

for _ in range(max_tries):
    real_bags = [rand_normal(real_mu, real_sigma)
                 for _ in range(max_bags)]
    all_real_bags.append(max(real_bags))

    customer_choice = [rand_normal(rbw, customer_sigma)
                       for rbw in real_bags]

    if real_bags.index(max(real_bags)) == customer_choice.index(max(customer_choice)):
        count_wins += 1

answer = round(reduce(lambda x, y: x + y, all_real_bags) / max_tries, 3)

print("Оценка мат. ожидания веса <<тяжелого>> мешка: ", answer)

print("Вероятность выбора самого тяжелого мешка: ",
      round(count_wins / max_tries, 3))
