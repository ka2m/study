"""
    Undirected unweighted graph
"""

import copy


class Graph:
    def __init__(self, vertices, adj_list):
        self.vertices = vertices  # set
        self.adj = {}
        self.gen_adj_list_undir(adj_list)  # map int-set of ints
        self.gen_connections()  # list of tuples

    def __str__(self):
        return 'Graph:\nnot directed\nnot weighted\nVertices: %s\n' \
               'Adjcency map:\n%s\n' \
               'All connections:\n%s\n' % \
               (' '.join([str(x) for x in self.vertices]),
                '\n'.join(['%s: %s' % (v,
                                       ' '.join([str(x) for x in self.adj[v]]))
                          for v in self.adj]), self.connections)

    def __deepcopy__(self, memo):
        dup = Graph(copy.deepcopy(self.vertices),
                    copy.deepcopy(self.adj))
        dup.gen_connections()
        return dup

    def type_check(self, v):
        return v if type(v) is int else int(v)

    def add_vertex(self, vertex):
        vertex = self.type_check(vertex)
        if vertex in self.vertices:
            raise Exception('Vertex %d already exists' % vertex)
        self.vertices.add(vertex)
        self.adj[vertex] = set()

    def add_edge(self, vfrom, vto):
        vfrom = self.type_check(vfrom)
        vto = self.type_check(vto)

        if vfrom not in self.vertices:
            raise Exception('Vertex to add arc FROM is not in graph')

        if vto not in self.vertices:
            raise Exception('Vertex to add arc TO is not in graph')

        self.adj[vfrom].add(vto)
        self.adj[vto].add(vfrom)
        self.gen_connections()

    def remove_vertex(self, vertex):
        vertex = self.type_check(vertex)
        if vertex not in self.vertices:
            raise Exception('Vertex %d not found' % vertex)
        for conn in self.get_connections(vertex):
            self.adj[conn[0]].remove(conn[1])
        self.vertices.remove(vertex)
        del self.adj[vertex]
        self.gen_connections()

    def gen_connections(self):
        res = []
        for v in self.adj:
            for vv in self.adj[v]:
                res.append((v, vv))
        self.connections = res

    def gen_adj_list_undir(self, adj_list):
        for v in self.vertices:
            self.adj[v] = set()
        for v in adj_list:
            for vv in adj_list[v]:
                self.adj[v].add(vv)
                self.adj[vv].add(v)

    def get_connections(self, vertex):
        vertex = self.type_check(vertex)
        if vertex not in self.vertices:
            raise Exception('Vertex %d not found' % vertex)
        return [v for v in self.connections if v[0] == vertex
                or v[1] == vertex]

    def get_connected_vertices(self, vertex):
        vertex = self.type_check(vertex)
        if vertex not in self.vertices:
            raise Exception('Vertex %d not found' % vertex)
        res = set()
        for v in self.get_connections(vertex):
            res.add(v[0])
            res.add(v[1])
        if vertex in res and \
           (vertex, vertex) not in self.get_connections(vertex):
            res.remove(vertex)
        return res

    def get_unique_connections(self):
        unq = []
        for conn in self.connections:
            if conn not in unq and conn[::-1] not in unq:
                unq.append(conn)
        return unq

    def degree(self, vertex):
        return len(self.adj[vertex])

    def get_edges(self):
        unique_conns = []
        for conn in self.connections:
            if conn not in unique_conns and \
               conn[::-1] not in unique_conns:
                unique_conns.append(conn)
        return unique_conns

    def count_edges(self):
        return len(self.get_edges())

    def count_vertices(self):
        return len(self.vertices)

    def count_arcs(self):
        return len(self.connections)

    def has_edge(self, vfrom, vto):
        return (vfrom, vto) in self.connections or (vto, vfrom) \
            in self.connections
