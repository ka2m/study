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
                        self.add_vertex(str(vfrom))
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
        if type(vertex) is not str:
            vertex = str(vertex)
        l = set()
        try:
            l = self.adj[vertex]
        except KeyError:
            print('No such vertex: %s' % vertex)
        finally:
            return l

    def add_vertex(self, key):
        self.vertices.append(key)
        self.adj[key] = set()

    def add_arc(self, vfrom, vto):
        if vfrom not in self.adj:
            self.adj[vfrom] = set()
        self.adj[vfrom].add(vto)

    def add_edge(self, vfrom, vto):
        self.add_arc(vfrom, vto)
        self.add_arc(vto, vfrom)

    def has_edge(self, v1, v2):
        if type(v1) is not str:
            v1 = str(v1)
        if type(v2) is not str:
            v2 = str(v2)
        return int(v2) in self.adj[v1] or int(v1) in self.adj[v2]

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
        if type(vertex) is not str:
            vertex = str(vertex)
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
            print('Vertex %d not found' % vertex)

    def count_vertices(self):
        return len(self.vertices)

    def count_arcs(self):
        return reduce(operator.add,
                      map(lambda x: self.degree(x), self.vertices), 0)

    def __str__(self):
        return '%d\n%s\n' % (len(self.adj), '\n'.join('%s:%s' %
                             (x, ' '.join(str(y) for y in self.adj[x]))
                             for x in sorted(self.adj.keys())))
