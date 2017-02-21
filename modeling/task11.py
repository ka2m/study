import matplotlib.pyplot as plt

LMBD = 0.12


def step(x, t):
    val = -LMBD * x
    return val


def func(x0, maxt, h):
    n = int(maxt / h)
    ts = [0]
    xs = [x0]
    for i in range(n):
        ti = ts[-1]
        xi = xs[-1]
        ts.append(ti + h)
        xs.append(xi + h * step(xi, ti))
    return ts, xs

maxX = 100

result = func(2.53e23, maxX, 0.01)
plt.plot(result[0], result[1])
plt.xlabel('время t')
plt.ylabel('количество нераспавшихся частиц x')
plt.show()
