"""
    Task 5 Ford-Fulkerson algorithm: max flow in the network
    Graph: network
"""

from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Tasks import Tasks as ts

adj_list = {1: [(2, 8), (3, 6)],
            2: [(4, 4), (5, 2)],
            3: [(5, 3), (2, 3)],
            4: [(6, 10), (5, 8)],
            5: [(6, 7)]}
g = gg.create(network=True, adj_list=adj_list)
