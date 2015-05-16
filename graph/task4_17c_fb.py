"""
    Task 4.17c Get CONNECTIONS between all the vertices
    Graph: directed, weighted
    Graph contains negative circuits
"""

from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Tasks import Tasks as ts

params = {'directed': True, 'weighted': True}
adj_list = {1: [(2, 3), (4, 2)],
            2: [(3, 1)],
            3: [(2, -2)]}

g = gg.create(params=params, adj_list=adj_list)

print g
ts.ford_pairs(g)
