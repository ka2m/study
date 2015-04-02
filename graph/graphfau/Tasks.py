from graphfau.Graph import Graph
from graphfau.DGraph import DGraph


class Tasks:
    @staticmethod
    def nbs(g, v1, v2):
        """
            Task 1.15 Find out if two vertices has one common neighbor
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
            Task 1.9 Get all out-connected vertices for the vertice
            Graph: directed, not weighted
        """
        return g.get_connected_vertices(v, 1)
