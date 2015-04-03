"""
    Task 2.II.11 Calculate circuit rank
    Graph: directed, not weighted
"""

from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Tasks import Tasks as ts

params = {'directed': False, 'weigthed': False}
adj_list = {1: [4,5, 2], 2:[3], 3:[5], 4:[5,6], 5:[6]}
g = gg.create(params=params, adj_list=adj_list)

print g
print ts.circuit_rank(g)
