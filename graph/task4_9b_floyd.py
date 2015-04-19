"""
    Task 4.9b Get connections between all the vertices
    Graph: directed, weighted
"""

from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Tasks import Tasks as ts

params = {'directed': True, 'weighted': True}
adj_list = {1: [(2, 30), (3, 10)],
            2: [(9, 15)],
            3: [(5, 25), (4, 40)],
            4: [(8, 12)],
            5: [(6, 7)],
            6: [(7, 12)],
            7: [(9, 30)],
            8: [(9, 25)],
            9: [(10, 11)]}
g = gg.create(params=params, adj_list=adj_list)

print g
ts.fb_pairs(g)
