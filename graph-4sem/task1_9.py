from graphfau import BaseGraph

def outcomingVertexes(graph, vertex):
	return graph.get_adjlist_by_vertex(vertex)

g = BaseGraph.BaseGraph('data')

print(g)
print('-----')

print(outcomingVertexes(g, 0))

print('-----')

print(outcomingVertexes(g, 23))
print('-----')
