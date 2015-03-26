__author__ = 'fau'

import copy
import operator


class BaseGraph:
    vertices = []
    adj = {}
    directed = False

    def __init__(self, directed=False, filename=None):
        self.directed = directed
        if filename is not None:
            try:
                with open(filename, 'r') as f:
                    for line in f.read().splitlines():
                        vfrom = line.split(':')[0]
                        if vfrom not in self.vertices:
                            self.add_vertex(int(vfrom))
                            self.adj[int(vfrom)] = set()
                        print self.vertices
                        for vto in eval('[' + line.split(':')[1] + ']'):
                            if not directed:
                                self.add_edge(vfrom, vto)
                            else:
                                self.add_arc(vfrom, vto)

            except IOError as e:
                print('Unable to open file: %s\nCreating empty graph' % e)

    def __deepcopy__(self, memo):
        dup = BaseGraph()
        dup.vertices = copy.deepcopy(self.vertices)
        dup.adj = copy.deepcopy(self.adj)
        return dup

    def get_adjlist_by_vertex(self, vertex):
        if type(vertex) is not int:
            vertex = int(vertex)
        l = set()
        try:
            l = self.adj[vertex]
        except KeyError:
            print('No such vertex: %d' % vertex)
        finally:
            return l

    def add_vertex(self, key):
        if key not in self.vertices:
            self.vertices.append(key)

    def add_arc(self, vfrom, vto):
        print vfrom, vto
        print self.vertices
        if type(vfrom) is not int:
            vfrom = int(vfrom)
        if type(vto) is not int:
            vto = int(vto)

        if vto not in self.vertices:
            print vto
            self.add_vertex(vto)
            self.adj[vto] = set()
        if vfrom not in self.adj:
            self.adj[vfrom] = set()
        self.adj[vfrom].add(vto)

    def add_edge(self, vfrom, vto):
        self.add_arc(vfrom, vto)
        self.add_arc(vto, vfrom)

    def has_edge(self, v1, v2):
        if type(v1) is not int:
            v1 = int(v1)
        if type(v2) is not int:
            v2 = int(v2)
        return v2 in self.adj[v1] or v1 in self.adj[v2]

    def remove_arc(self, vfrom, vto):
        if vfrom not in self.adj.keys():
            raise Exception('Vertex %d not found' % vfrom)
        if vto not in self.adj[vfrom]:
            raise Exception('Arc %d - %d not found' % (vfrom, vto))

        self.adj[vfrom].remove(vto)

    def remove_edge(self, vfrom, vto):
        self.remove_arc(vfrom, vto)
        self.remove_arc(vto, vfrom)

    def remove_vertex(self, vertex):
        if type(vertex) is not int:
            vertex = int(vertex)
        try:
            self.vertices.remove(vertex)
            del self.adj[vertex]
        except KeyError:
            print 'Vertex %d not found' % vertex
        for v in self.adj.keys():
            if vertex in self.adj[v]:
                try:
                    self.adj[v].remove(vertex)
                except KeyError:
                    print 'Vertex %d not found' % vertex

    def degree(self, vertex):
        try:
            return len(self.adj[vertex])
        except KeyError:
            print('Vertex %s not found' % vertex)

    def count_vertices(self):
        return len(self.vertices)

    def count_arcs(self):
        return reduce(operator.add,
                      map(lambda x: self.degree(x), self.vertices), 0)

    def __str__(self):
        return 'D: %s\n%d\n%s\n' % (self.directed, len(self.adj),
                                    '\n'.join('%d:%s' % (x,
                                                         str(', '.join(str(y)
                                                                       for y in
                                                                       self.
                                                                       adj[x])))
                                                for x in self.adj.keys()))
