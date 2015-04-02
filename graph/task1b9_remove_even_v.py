"""
    Task 1b.9 Return copy of graph with deleted even vertices
    Graph: undirected, not weighted
"""

from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Tasks import Tasks as ts

params = {'directed': False, 'weigthed': False}
adj_list = {1: [2, 3, 4], 3: [5, 4], 6: []}
g = gg.create(params=params, adj_list=adj_list)

print g
g2 = ts.remove_even_vertices(g)
print g2
