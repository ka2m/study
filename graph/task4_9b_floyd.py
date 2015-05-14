"""
    Task 4.9b Get connection LENGTHS between all the vertices
    Graph: directed, weighted
    Graph contains negative edges, but not circuits
"""

from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Tasks import Tasks as ts

params = {'directed': True, 'weighted': True}
adj_list = {1: [(2, 10), (3, -4)],
            2: [(4, -1), (3, 8)],
            3: [(4, 7), (2, 8)]}
g = gg.create(params=params, adj_list=adj_list)

print g
ts.floyd_lengths(g)
