"""
    Task 3.b Implement Boruvka's algorithm
    Graph: not directed, weighted
"""

from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Algo import Algo

params = {'directed': False, 'weigthed': True}
adj_list = {1: [(2, 5), (3, 7), (4, 12)],
            2: [(5, 1), (3, 5)],
            3: [(5, 4), (6, 3), (4, 4)],
            4: [(6, 7)],
            5: [(7, 5), (6, 2)],
            6: [(7, 2)]}
g = gg.create(params=params, adj_list=adj_list)

print g
print Algo.boruvka(g)
