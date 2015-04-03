"""
    Task 2.II.11 Get all out-connected vertices for the vertice
    Graph: directed, not weighted
"""

from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Tasks import Tasks as ts
params = {'directed': True, 'weigthed': False}
adj_list = {1: [2, 3, 4], 7: [], 3: [1, 5]}
g = gg.create(params=params, adj_list=adj_list)

print g
print ts.tf(g)
