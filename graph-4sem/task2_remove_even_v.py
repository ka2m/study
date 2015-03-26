from graphfau import BaseGraph
import copy


def remove_even_vertices(graph):
    g2 = copy.deepcopy(graph)
    flag = False
    for v in graph.vertices:
        if not graph.degree(v) % 2:
            g2.remove_vertex(v)
            flag = True
    if not flag:
        print('No even vertices found')
    return g2


g = BaseGraph.BaseGraph(filename='data')
print(g)
g2 = remove_even_vertices(g)
print(g2)
