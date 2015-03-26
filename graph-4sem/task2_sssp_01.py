from graphfau.WGraph import WGraph
from collections import deque


def bfs(graph, start):
    distances = {}
    for v in graph.vertices:
        distances[v] = 2
    queue = deque(str(start))
    distances[start] = 0
    while queue:
        vertex = int(queue.pop())
        for v in graph.adj[vertex]:
            print v
            if distances[v[0]] > distances[vertex] + v[1]:
                distances[vertex] = distances[vertex] + v[1]
                if not v[1]:
                    queue.appendleft(str(v[0]))
                else:
                    queue.append(str(v[0]))
    print distances

g = WGraph(filename='wdata')
print(g)
print('----')

v = input('vertex to go from: ')
bfs(g, v)
