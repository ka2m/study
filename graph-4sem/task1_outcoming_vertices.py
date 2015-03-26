from graphfau import BaseGraph


def outcoming_vertices(graph, vertex):
    return list(graph.get_adjlist_by_vertex(vertex))

g = BaseGraph.BaseGraph(filename='data')

print(g)
print('-----')

v = input('outcomingvertices:\nenter desired vertex to check: ')

print(outcoming_vertices(g, v))
