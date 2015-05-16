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
        dist = {}
        for i in g.adj.keys():
            p = {}
            for j in g.adj.keys():
                try:
                    cw = g.get_connection_weight(i, j)
                    if i == j:
                        p[j] = 0
                    else:
                        p[j] = cw
                except:
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
                        if count == len(graph.vertices) -1 :
                            cc.append(negv)

        return cc, negv, paths

    @staticmethod
    def find_flow_path(graph, id_list, flow, source, sink, path):
        if source == sink:
            return path
        for edge in [e for e in graph.get_connections(source) if e[2]]:
            edge = tuple(edge)
            residual = edge[2] - flow[Algo.get_flow_id_from_edge(edge,
                                                                 id_list,
                                                                 flow)]
            chk = True
            if len(path) >= 1:
                if edge[0] != path[0][1]:
                    chk = False

            if residual > 0 and edge not in path and chk:
                result = Algo.find_flow_path(graph,
                                             id_list,
                                             flow,
                                             edge[1],
                                             sink,
                                             [edge] + path)

                if result is not None:
                    return result[::-1]

    @staticmethod
    def get_flow_id_from_edge(edge, id_list, flow):
        for _id in id_list:
            if edge[0] == _id[1][0] and edge[1] == _id[1][1]:
                return _id[0]
