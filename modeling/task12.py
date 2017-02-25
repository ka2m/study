import matplotlib.pyplot as plt


maxT = 5000
startX = 30.
startY = 50.
A1 = 0.008
A2 = 0.1
B1 = 0.001
B2 = 1.
X = 400.
Y = 800.


def step(x, y, popCoef, maxPop, strugPop):
    return popCoef * x * (maxPop - (x + strugPop * y)) / maxPop


def func(x0, y0, maxt, h):
    n = int(maxt / h)
    xs = [x0]
    ys = [y0]
    for i in range(n):
        xi = xs[-1]
        yi = ys[-1]
        xs.append(xi + h * step(xi, yi, A1, X, B1))
        ys.append(yi + h * step(yi, xi, A2, Y, B2))
    return xs, ys


result = func(startX, startY, maxT, 0.01)
plt.plot(result[0], result[1])
plt.xlabel('хищники')
plt.ylabel('жертвы')

startX = 100.
startY = 100.
A1 = 0.008
A2 = 0.1
B1 = 0.001
B2 = 1.
X = 400.
Y = 800.

result = func(startX, startY, maxT, 0.01)
plt.plot(result[0], result[1])


startX = 200.
startY = 1000.
A1 = 0.008
A2 = 0.1
B1 = 0.001
B2 = 1.
X = 400.
Y = 800.

result = func(startX, startY, maxT, 0.01)
plt.plot(result[0], result[1])

startX = 350.
startY = 100.
A1 = 0.008
A2 = 0.1
B1 = 0.001
B2 = 1.
X = 400.
Y = 800.

result = func(startX, startY, maxT, 0.01)
plt.plot(result[0], result[1])

startX = 400.
startY = 700.
A1 = 0.008
A2 = 0.1
B1 = 0.06
B2 = 1.
X = 400.
Y = 800.

result = func(startX, startY, maxT, 0.01)
plt.plot(result[0], result[1])



plt.show()



