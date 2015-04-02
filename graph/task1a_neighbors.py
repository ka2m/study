"""
    Task 1a.15 Find out if two vertices has one common neighbor
    Graph: undirected, not weighted
"""
from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Tasks import Tasks as ts

params = {'directed': False, 'weigthed': False}
adj_list = {1: [2, 3, 4], 3: [5, 4], 6: []}

g = gg.create(params=params, adj_list=adj_list)
print g

print ts.nbs(g, 1, 3)
print
print ts.nbs(g, 2, 6)
print
print ts.nbs(g, 4, 5)
