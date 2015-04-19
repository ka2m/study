import copy
from operator import itemgetter
from graphfau.GraphGenerator import GraphGenerator as gg


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
    def boruvka(graph):
        props = {'directed': False, 'weighted': True}
        mst = gg.create(params=props,
                        adj_list={x: [] for x in graph.vertices})
        all_edges = graph.get_w_edges()
        print all_edges
        while mst.count_edges() < (mst.count_vertices() - 1):
            for edge in all_edges:
                ccs = Algo.connected_components(mst)
                print ccs
                do_add_edge = True
                for comp in ccs:
                    if edge[0] in comp and edge[1] in comp:
                        do_add_edge = False
                if do_add_edge:
                    emin = sorted([x for x in all_edges if x[0] == edge[0] and
                                  x[1] == edge[1]], key=itemgetter(2))[0]
                    mst.add_edge(*emin)
        return mst

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

    @staticmethod
    def convert_adjmap_to_adjmatrix(g):
        vertices = g.keys()
        dist = {}
        for i in vertices:
            dist[i] = {}
            for j in vertices:
                try:
                    dist[i][j] = g[i][j]
                except KeyError:
                    if i == j:
                        dist[i][j] = 0
                    else:
                        dist[i][j] = float('inf')
        return dist

    @staticmethod
    def djikstra(graph):
        pass

    @staticmethod
    def fb(graph):
        vertices = graph.vertices
        d = dict(Algo.convert_adjmap_to_adjmatrix(graph.adj))
        for k in vertices:
            for i in vertices:
                for j in vertices:
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j])
        return d

    @staticmethod
    def floyd(graph):
        pass
