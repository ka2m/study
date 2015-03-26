from graphfau.BaseGraph import BaseGraph


def nbs(graph, vertex1, vertex2):
    list1 = graph.get_adjlist_by_vertex(vertex1)
    list2 = graph.get_adjlist_by_vertex(vertex2)
    res = list(list1.intersection(list2))
    if not res:
        print('No neighbours!')
    return res

g = BaseGraph(filename='data')
print(g)
print('----')

v1 = input('nbs: enter 1st vertex: ')
v2 = input('nbs: enter 2nd vertex: ')
print(nbs(g, v1, v2))
