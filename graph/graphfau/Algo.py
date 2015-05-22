import copy
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
    def bfs_paths(g, start, goal):
        queue = [(start, [start])]
        while queue:
            (vertex, path) = queue.pop(0)
            for next in g.adj[vertex] - set(path):
                if next == goal:
                    yield path + [next]
                else:
                    queue.append((next, path + [next]))

    @staticmethod
    def short_bfs(g, start, goal):
        try:
            return next(Algo.bfs_paths(g, start, goal))
        except StopIteration:
            return None

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
        while True:
            mst_edges = []
            emin = float('inf')
            candidate = None
            ccs = Algo.connected_components(mst)
            if len(ccs) == 1:
                break
            for component in ccs:
                for vertex in component:
                    for other_vertex in graph.adj[vertex]:
                        if other_vertex not in component and graph.has_edge(vertex, other_vertex):
                            wg = graph.get_connection_weight(vertex, other_vertex)
                            if wg == -1:  # reverse it
                                wg = graph.get_connection_weight(other_vertex, vertex)
                            if wg < emin:
                                emin = wg
                                candidate = (vertex, other_vertex, wg)
                mst_edges.append(candidate)

            for edge in mst_edges:
                if type(edge) is tuple:
                    mst.add_edge(*edge)
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
    def convert_adjmap_to_adjmatrix(g, flow=False):
        dist = {}
        for i in g.adj.keys():
            p = {}
            for j in g.adj.keys():
                try:
                    cw = g.get_connection_weight(i, j)
                    if i == j:
                        if flow:
                            p[j] = None
                        else:
                            p[j] = 0
                    else:
                        p[j] = cw
                except:
                    if flow:
                        p[j] = None
                    else:
                        p[j] = float('inf')
            dist[i] = p
        return dist

    @staticmethod
    def djikstra(graph, from_vertex, multi_path=False):
        dist = dict.fromkeys(graph.vertices, float('inf'))
        paths = dict.fromkeys(graph.vertices, [None]) if multi_path else \
            dict.fromkeys(graph.vertices, None)
        visited = dict.fromkeys(graph.vertices, False)
        dist[from_vertex] = 0
        for count in graph.vertices:
            vertex = None
            for vv in graph.vertices:
                if not visited[vv] and (vertex is None
                                        or dist[vv] < dist[vertex]):
                    vertex = vv
            if dist[vertex] == float('inf'):
                break
            visited[vertex] = True

            for conns in graph.get_unique_connections_from_vertex(vertex):
                to_vertex = conns[1]
                if conns[1] == vertex:
                    to_vertex = conns[0]
                wght = conns[2]
                new_wght = dist[vertex] + wght
                if new_wght < dist[to_vertex]:
                    dist[to_vertex] = new_wght
                    paths[to_vertex] = [vertex] if multi_path else vertex
                elif new_wght == dist[to_vertex] and multi_path:
                    paths[to_vertex].append(vertex)

        return dist, paths

    @staticmethod
    def floyd(graph):
        vertices = graph.vertices
        d = dict(Algo.convert_adjmap_to_adjmatrix(graph))
        print d
        for k in vertices:
            for i in vertices:
                for j in vertices:
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j])
        return d

    @staticmethod
    def ford(graph, from_vertex):
        dist = dict.fromkeys(graph.vertices, float('inf'))
        paths = dict.fromkeys(graph.vertices, None)
        dist[from_vertex] = 0
        cc = []
        for count in range(len(graph.vertices)):
            negv = None
            for edge in graph.connections:
                if dist[edge[0]] < float('inf'):
                    new_wght = dist[edge[0]] + edge[2]
                    if dist[edge[1]] > new_wght:
                        dist[edge[1]] = new_wght
                        paths[edge[1]] = edge[0]
                        negv = edge[1]
                        if count == len(graph.vertices) - 1:
                            cc.append(negv)

        return cc,  paths

    @staticmethod
    def bfs_flow(capacities, flow, source, sink):
        queue = [source]
        paths = {source: []}
        while queue:
            u = queue.pop(0)
            for v in capacities[u]:
                if capacities[u][v] is not None:
                    if capacities[u][v] - flow[u][v] > 0 and v not in paths:
                        paths[v] = paths[u] + [(u, v)]
                        if v == sink:
                            return paths[v]
                        queue.append(v)
        return None

    @staticmethod
    def edmonds_karp(capacities, flow, source, sink):
        while True:
            path = Algo.bfs_flow(capacities, flow, source, sink)
            if not path:
                break
            fl = min(capacities[u][v] - flow[u][v] for u, v in path)
            print path
            for u, v in path:
                flow[u][v] += fl
                flow[v][u] -= fl
        return sum(flow[source][i] for i in capacities[source]
                   if flow[source][i] is not None)
