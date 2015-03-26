from graphfau.BaseGraph import BaseGraph
from graphfau.Algo import Algo


def circuit_rank(graph):
    vertices = graph.count_vertices()
    arcs = graph.count_arcs()
    ccs = len(Algo.connected_components(graph))
    print vertices
    print arcs
    print ccs
    return ccs + arcs - vertices

g = BaseGraph(directed=True, filename='data')
print(g)
print(circuit_rank(g))
