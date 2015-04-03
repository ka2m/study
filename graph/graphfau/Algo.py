import copy


class Algo:
    @staticmethod
    def wu_bfs(g, start):
        distances = {}
        paths = {}
        for v in g.vertices:
            distances[v] = 0
            paths[v] = None
        q = list()
        q.append(start)
        while q:
            q.reverse()
            vertex = q.pop()
            q.reverse()
            for p in g.adj[vertex]:
                if paths[p] is None:
                    paths[p] = vertex
                    distances[p] = distances[vertex] + \
                        g.get_connection_weight(p, vertex)
                    q.append(p)
                    q.reverse()
        paths[start] = None
        distances[start] = 0
        return distances, paths

    @staticmethod
    def bfs(g, start):
        visited, queue = set(), [start]
        while queue:
            vertex = queue.pop(0)
            if vertex not in visited:
                visited.add(vertex)
                queue.extend(g.adj[vertex] - visited)
        return visited

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
            vertices = copy.copy(graph.vertices)
        if vertices == []:
            return result
        v = vertices.pop()
        comp = Algo.dfs(graph, int(v))
        result.append(comp)
        return Algo.connected_components(graph,
                                         result,
                                         list(set(vertices) - set(comp)))
