def Prim(adj):
    T = []
    n = len(adj)
    nearest = []
    min_dist = []

    for i in range(0, n):
        nearest.append(0)
        min_dist.append(0)

    for i in range(1, n):
        nearest[i] = 0
        min_dist[i] = adj[i][0]

    for i in range(0, n - 1):
        min = None
        for j in range(1, n):
            if (((min and min_dist[j] and 0 <= min_dist[j] < min)
               or(not min and 0 <= min_dist[j]))):
                min = min_dist[j]
                k = j

        T.append((k, nearest[k]))
        print(map(lambda t: (vertexList[t[0]], vertexList[t[1]]), T))

        min_dist[k] = -1
        min_dist[nearest[k]] = -1

        for j in range(1, n):
            if (((min_dist[j] and adj[k][j] and adj[k][j] < min_dist[j])
                 or not min_dist[j])):
                min_dist[j] = adj[k][j]
                min_dist[k] = adj[j][k]

                nearest[j] = k
                nearest[k] = j

    return T

#         a    b    c   d   e     f    g
adj = [[None, 1, None, 4, None, None, None],
       [1, None, 2, 6, 4, None, None],
       [None, 2, None, None, 5, 6, None],
       [4, 6, None, None, 3, None, 4],
       [None, 4, 5, 3, None, 8, 7],
       [None, None, 6, None, 8, None, 3],
       [None, None, None, 4, 7, 3, None]]

vertexList = 'ABCDEFG'
print(map(lambda t: (vertexList[t[0]], vertexList[t[1]]), Prim(adj)))
