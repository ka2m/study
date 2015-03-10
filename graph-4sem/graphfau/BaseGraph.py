__author__ = 'fau'

import copy


class BaseGraph:
    vertexes = []
    adj = {}

    def __init__(self, filename=None):
        if filename is not None:
            try:
                with open(filename, 'r') as f:
                    for line in f.read().splitlines():
                        vfrom = line.split(':')[0]
                        self.add_vertex(vfrom)
                        for vto in eval('[' + line.split(':')[1] + ']'):
                            self.add_arc(vfrom, vto)

            except IOError as e:
                print('Unable to open file: %s\nCreating empty graph' % e)

    def __deepcopy__(self, memo):
        dup = BaseGraph()
        dup.vertexes = copy.deepcopy(self.vertexes)
        dup.adj = copy.deepcopy(self.adj)
        return dup

    def get_adjlist_by_vertex(self, vertex):
        l = []
        try:
            l = self.adj[str(vertex)]
        except KeyError:
            print('No such vertex: %s' % vertex)
        finally:
            return l

    def add_vertex(self, key):
        self.vertexes.append(key)
        self.adj[key] = []

    def add_arc(self, vfrom, vto):
        if not vfrom in self.adj:
            self.adj[vfrom] = []
        self.adj[vfrom].append(vto)

    def add_edge(self, vfrom, vto):
        self.add_arc(vfrom, vto)
        self.add_arc(vto, vfrom)

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
        if str(vertex) not in self.vertexes:
            raise Exception('Vertex %d not found' % vertex)
        self.vertexes.remove(str(vertex))
        del self.adj[str(vertex)]
        for v in self.adj.keys():
            if vertex in self.adj[v]:
                self.adj[v].remove(vertex)


    def degree(self, vertex):
        try:
            return len(self.adj[vertex])
        except KeyError:
            print('Vertex %d not found' % vertex)

    def __str__(self):
        return '%d\n%s\n' % (len(self.adj), '\n'.join('%s:%s' %
                             (x, ' '.join(str(y) for y in self.adj[x]))
                             for x in sorted(self.adj.keys())))
