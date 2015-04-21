"""
    Task 4.20a Get number of shortest paths from some vertex to all the
    others
    Graph: not directed, weighted
"""

from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Tasks import Tasks as ts
from graphfau.Algo import Algo
params = {'directed': False, 'weighted': True}
adj_list = {1: [(2, 2), (3, 2)],
            2: [(5, 3), (4, 2), (6, 12)],
            3: [(4, 2)],
            4: [(5, 1)],
            5: [(6, 4)]}
g = gg.create(params=params, adj_list=adj_list)

print g
print Algo.djikstra(g, 1, multi_path=True)
