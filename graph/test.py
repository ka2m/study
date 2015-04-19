"""
    Task 2.II.11 Get all out-connected vertices for the vertice
    Graph: directed, not weighted
"""

from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Tasks import Tasks as ts
from graphfau.Algo import Algo
params = {'directed': False, 'weighted': True}
adj_list = {1: [(2, 0), (3, 1), (4, 0)], 4:[(5, 1)], 7:[], 3: [(5,1)]}
g = gg.create(params=params, adj_list=adj_list)

print g
print Algo.wu_bfs(g, 1)

