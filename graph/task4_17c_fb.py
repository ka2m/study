"""
    Task 4.17c Get connection length between all the vertices
    Graph: directed, weighted
"""

from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Tasks import Tasks as ts

params = {'directed': True, 'weighted': True}
adj_list = {1: [(2, 2), (3, -2)],
            2: [(5, 3), (4, 2), (6, 12)],
            3: [(4, -2)],
            4: [(5, 1), (1, -1)],
            5: [(6, 4)]}

g = gg.create(params=params, adj_list=adj_list)

print g
ts.ford_pairs(g)
