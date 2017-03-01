import math
D = 40
K = 2000
h = 0.6
L = 20

y_star = math.ceil(math.sqrt(2*K*D/h))
t0_star = math.ceil(y_star / D)
print(t0_star)
if (t0_star < L):
    Le = L - math.floor(L / t0_star) * t0_star
    lowest_level = Le * D
    print(u"Заказывать {0} ламп как только уровень запаса понижается до {1}".format(y_star, lowest_level))
else:
    print(u"Заказывать {0} ламп через каждые {1} дней".format(y_star, t0_star))

tcu = K / (y_star / D) + (h * y_star / 2)
print(tcu)
