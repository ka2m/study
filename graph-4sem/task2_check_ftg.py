from graphfau.BaseGraph import BaseGraph
from graphfau.Algo import Algo


def circuit_rank(graph):
    vertices = graph.count_vertices()
    arcs = graph.count_arcs()
    ccs = len(Algo.connected_components(graph))
    return ccs + arcs - vertices


def check_circuit(graph):
    return bool(circuit_rank(graph))


def ftg(graph):
    score = 0
    ccs= Algo.connected_components(graph)
    if len(ccs) == 1 and \
       not check_circuit(graph) and \
       ccs[0] == graph.vertices:
        score = 1
    elif len(ccs) != 1:
        for c in ccs

    return score


g = BaseGraph(directed=True, filename='data')
print(g)
print(ftg(g))
