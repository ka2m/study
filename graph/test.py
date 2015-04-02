from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Tasks import Tasks as ts
params = {'directed': False, 'weigthed': False}
adj_list = {1: [2, 3, 4], 3: [5, 4], 6: []}
r = gg.create(params=params, adj_list=adj_list)
print ts.nbs(r, 1, 3)
