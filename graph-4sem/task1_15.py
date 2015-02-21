from graphfau import BaseGraph


def nbs(graph, vertex1, vertex2):
    list1 = graph.get_adjlist_by_vertex(vertex1)
    list2 = graph.get_adjlist_by_vertex(vertex2)
    res = list(set(list1).intersection(set(list2)))
    if res == []:
        print('No neighbours!')
    return res

g = BaseGraph.BaseGraph('data')
print(g)
print('----')

print(nbs(g, 0, 1))
print('----')

print(nbs(g, 1, 2))
print('----')

print(nbs(g, 0, 2))
print('----')

print(nbs(g, 0, 3))
print('----')

print(nbs(g, 5, 6))
print('----')
