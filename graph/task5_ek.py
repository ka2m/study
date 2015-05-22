"""
    Task 5 Edmonds-Karp algorithm: max flow in the network
    Graph: network
"""

from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Tasks import Tasks as ts

adj_list = {1: [(2, 1), (4, 1)],
            2: [(3, 1)],
            3: [(5, 1)],
            4: [(6, 1), (5, 1)],
            5: [(8, 1)],
            6: [(7, 1)],
            7: [(8, 1)]}
g = gg.create(network=True, adj_list=adj_list)
print g
print ts.flow_edmonds_karp(g, 1, 8)
