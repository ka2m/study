from graphfau.Algo import Algo as func
import copy


class Tasks:
    @staticmethod
    def nbs(g, v1, v2):
        """
            Task 1a.15 Find out if two vertices has one common neighbor
            Graph: undirected, not weighted
        """
        l1 = g.get_connected_vertices(v1)
        l2 = g.get_connected_vertices(v2)
        res = set(l1).intersection(set(l2))
        if not res:
            print('No neighbours!')
        return list(res)

    @staticmethod
    def outcomming_connected_vertices(g, v):
        """
            Task 1a.9 Get all out-connected vertices for the vertice
            Graph: directed, not weighted
        """
        return g.get_connected_vertices(v, 1)

    @staticmethod
    def remove_even_vertices(g):
        """
            Task 1b.9 Return copy of graph with deleted even vertices
            Graph: undirected, not weighted
        """
        g2 = copy.deepcopy(g)

        flag = False
        for v in g.vertices:
            if not g.degree(v) % 2:
                g2.remove_vertex(v)
                flag = True
        if not flag:
            print('No even vertices found')

        return g2

    @staticmethod
    def circuit_rank(g):
        """
            Task 2.II.11 Found circuit rank of graph (directed or not)
        """
        vertices = g.count_vertices()
        edges = g.count_edges()
        ccs = len(func.connected_components(g))
        return ccs + edges - vertices
