__author__ = 'fau'

import copy
from BaseGraph import BaseGraph


class WGraph(BaseGraph):

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
                        for vto in eval('[' + line.split(':')[1] + ']'):
                            if not directed:
                                self.add_edge((int(vfrom), vto[1]), vto)
                            else:
                                self.add_arc(int(vfrom), vto)

            except IOError as e:
                print('Unable to open file: %s\nCreating empty graph' % e)

    def __deepcopy__(self, memo):
        dup = WGraph()
        dup.vertices = copy.deepcopy(self.vertices)
        dup.adj = copy.deepcopy(self.adj)
        return dup

    def get_adjlist_by_vertex(self, vertex):
        l = set()
        try:
            l = self.adj[vertex]
        except KeyError:
            print('No such vertex: %s' % vertex)
        finally:
            return l

    def get_only_vertices_list(self, v):
        return [x[0] for x in self.adj[v]]

    def add_vertex(self, key):
        self.vertices.append(key)

    def add_arc(self, vfrom, vto):
        if type(vfrom) is tuple:
            vfrom = vfrom[0]

        if vto[0] not in self.vertices:
            self.vertices.append(vto[0])
            self.adj[vto[0]] = set()

        if vfrom not in self.adj:
            self.adj[vfrom] = set()
        self.adj[vfrom].add(vto)

    def add_edge(self, vfrom, vto):
        print vfrom, vto
        self.add_arc(vfrom, vto)
        self.add_arc(vto[0], vfrom)

    def has_edge(self, v1, v2):
        return v2 in self.get_only_vertices_list(v1) \
            or v1 in self.get_only_vertices_list(v2)

    def remove_arc(self, vfrom, vto):
        if vfrom not in self.adj.keys():
            raise Exception('Vertex %d not found' % vfrom)
        if vto not in self.get_only_vertices_list(vfrom):
            raise Exception('Arc %d - %d not found' % (vfrom, vto))
        vto = [v for v in self.adj[vfrom] if v[0] == vto][0]

        self.adj[vfrom].remove(vto)

    def remove_vertex(self, vertex):
        try:
            self.vertices.remove(vertex)
            del self.adj[vertex]
        except KeyError:
            print 'Vertex %d not found' % vertex
        for v in self.adj.keys():
            if vertex in self.get_only_vertices_list(v):
                try:
                    self.adj[v].remove(vertex)
                except KeyError:
                    print 'Vertex %d not found' % vertex
