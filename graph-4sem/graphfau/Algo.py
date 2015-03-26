__author__ = 'fau'


class Algo:
    @staticmethod
    def dfs(graph, start, visited=None):
        if visited is None:
            visited = set()
        visited.add(start)
        for next in graph.adj[int(start)] - visited:
            Algo.dfs(graph, next, visited)
        return list(visited)

    @staticmethod
    def connected_components(graph, result=None, vertices=None):
        if vertices is None:
            result = []
            vertices = graph.vertices
        if vertices == []:
            return result
        v = vertices[0]
        comp = Algo.dfs(graph, int(v))
        # directed graph safety
        # cases like 5:
        if [v] != comp or graph.has_edge(v, v):
            result.append(comp)
        return Algo.connected_components(graph,
                                         result,
                                         list(set(vertices) - set(comp)))
