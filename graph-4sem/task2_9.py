from graphfau import BaseGraph
import copy

def removeEvenVertexes(graph):
    g2 = copy.deepcopy(graph)
    for v in graph.vertexes:
        if not graph.degree(v) % 2:
            g2.remove_vertex(v)
    return g2

g = BaseGraph.BaseGraph('data')
print(g)
g2 = removeEvenVertexes(g)
print(g2)