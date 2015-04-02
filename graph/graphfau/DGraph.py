"""
    Directed unweighted graph
"""


class DGraph:
    def __init__(self, vertices, adj_list):
        self.vertices = vertices  # set
        self.adj = {}
        self.gen_adj_list(adj_list)  # map int-set of ints
        self.gen_connections()  # list of tuples

    def __str__(self):
        return 'Graph:\ndirected\nnot weighted\nVertices: %s\n' \
               'Adjcency map:\n%s\n' \
               'All connecions:\n%s\n' % \
               (' '.join([str(x) for x in self.vertices]),
                '\n'.join(['%s: %s' % (v,
                                       ' '.join([str(x) for x in self.adj[v]]))
                          for v in self.adj]), self.connections)

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
            raise Exception('Vertex to add edge FROM is not in graph')

        if vto not in self.vertices:
            raise Exception('Vertex to add edge TO is not in graph')

        self.adj[vfrom].add(vto)
        self.gen_connections()

    def add_arc(self, vfrom, vto):
        self.add_edge(vfrom, vto)
        self.add_edge(vto, vfrom)

    def remove_vertex(self, vertex):
        vertex = self.type_check(vertex)
        if vertex not in self.vertices:
            raise Exception('Vertex %d not found' % vertex)
        self.vertices.remove(vertex)
        for conn in self.get_connections(vertex):
            self.adj[conn[0]].remove(conn[1])
        del self.adj[vertex]
        self.gen_connections()

    def gen_connections(self):
        res = []
        for v in self.adj:
            for vv in self.adj[v]:
                res.append((v, vv))
        self.connections = res

    def gen_adj_list(self, adj_list):
        for v in self.vertices:
            self.adj[v] = set()
        for v in adj_list:
            for vv in adj_list[v]:
                self.adj[v].add(vv)

    def get_connections(self, vertex):
        vertex = self.type_check(vertex)
        if vertex not in self.vertices:
            raise Exception('Vertex %d not found' % vertex)
        return [v for v in self.connections if v[0] == vertex
                or v[1] == vertex]

    def get_connected_vertices(self, vertex, direction):
        # 0 - both, -1 - from, 1 - to
        vertex = self.type_check(vertex)
        if vertex not in self.vertices:
            raise Exception('Vertex %d not found' % vertex)
        res = set()
        for v in self.get_connections(vertex):
            if not direction:
                res.add(v[0])
                res.add(v[1])
            if direction == 1:
                res.add(v[1])
            if direction == -1:
                res.add(v[0])
        if vertex in res and \
           (vertex, vertex) not in self.get_connections(vertex):
            res.remove(vertex)
        return res
