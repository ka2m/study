"""
    Task 4.20a Get number of shortest paths from some vertex to all the
    others
    Graph: not directed, weighted
"""

from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Algo import Algo

params = {'directed': True, 'weighted': True}
adj_list = {1: [(2, 20), (4, 25), (7, 15)],
            2: [(2, 5), (5, 5)],
            3: [(4, 5), (5, 5), (6, 20)],
            4: [(6, 15), (7, 10)],
            5: [(8, 15), (9, 10), (10, 20)],
            6: [(5, 5), (10, 20)],
            7: [(6, 10), (8, 15), (9, 20)],
            8: [(11, 5)],
            9: [(10, 15), (12, 20)],
            10: [(11, 10), (12, 20)],
            11: [(12, 15)]

            }
g = gg.create(params=params, adj_list=adj_list)

print g
print Algo.djikstra(g, 1, True)
