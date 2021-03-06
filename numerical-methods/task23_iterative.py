#!/usr/bin/python


def solve(matrix, EPS):
    size = len(matrix)
    xlist = []
    ylist = []
    for i in range(0, size):
        xlist.append(0.0)
        ylist.append(0.0)

    for i in range(0, size):
        ylist[i] = matrix[i][size]

    iter_count = 0
    for k in range(0, size):
        while (abs(ylist[k] - xlist[k]) > EPS):
            iter_count += 1
            for i in range(0, size):
                xlist[i] = ylist[i]
                res = 0.0
                for j in range(0, size):
                    if i != j:
                        res += matrix[i][j] * xlist[j]
                ylist[i] = (matrix[i][size] - res) / matrix[i][i]
    return xlist, iter_count

if __name__ == "__main__":
    matrix = [[3, 1, 1, 8],
              [-2, 5, 1, 11],
              [-1, 0, 2, 5]]
    eps = 0.1
    for i in range(0, 20):
        result, ic = solve(matrix, eps)
        print result, ic, eps
        eps /= 10.0
