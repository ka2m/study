"""
    Task 2.II.30 Get shortest path in 0-1 graph
    Graph: not directed, weighted
"""

from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Algo import Algo
params = {'directed': False, 'weigthed': True}
adj_list = {1: [(2, 0), (3, 1), (4, 0)], 4: [(5, 1)], 7: [], 3: [(5, 1)]}
g = gg.create(params=params, adj_list=adj_list)

print g
print Algo.wu_bfs(g, 1)
