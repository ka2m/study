"""
    Task 2.II.20 Check if graph is forest, tree or not
    Graph: directed, not weighted
"""

from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Tasks import Tasks as ts
params = {'directed': False, 'weigthed': False}
adj_list = {1: [2], 2: [3], 3: [4]}
g = gg.create(params=params, adj_list=adj_list)

print g
print ts.tf(g)
