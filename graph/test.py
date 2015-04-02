"""
    Task 1.9 Get all out-connected vertices for the vertice
    Graph: directed, not weighted
"""

from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Tasks import Tasks as ts

params = {'directed': False, 'weigthed': False}
adj_list = {1: [2, 3, 4], 3: [5, 4, 2], 6: []}
g = gg.create(params=params, adj_list=adj_list)

print g
print g.get_connected_vertices(3)
