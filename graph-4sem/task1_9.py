from graphfau import BaseGraph

def outcomingVertexes(graph, vertex):
	return graph.get_adjlist_by_vertex(vertex)

g = BaseGraph.BaseGraph('data')

print(g)
print('-----')

v = input('outcomingVertexes: enter desired vertex to check: ')

print(outcomingVertexes(g, v))
