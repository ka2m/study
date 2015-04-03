from graphfau.Algo import Algo as func
from graphfau.GraphGenerator import GraphGenerator as gg
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

    @staticmethod
    def tf(g):
        """
            Task 2.II.20 Check if graph is forest, tree or not
        """
        cc = func.connected_components(g)
        # if graph has one connected component and has no circuits
        # it is a tree
        if len(cc) == 1 and not Tasks.circuit_rank(g):
            return 'Tree'
        if len(cc) > 1:
            flag = False
            for subtree in cc:
                subtree_adj = {}
                for vertex in subtree:
                    for vu in g.get_edges():
                        # vertex found - add its connections
                        if vertex == vu[0] or vertex == vu[1]:
                            if vu[0] not in subtree_adj.keys():
                                subtree_adj[vu[0]] = set()
                            subtree_adj[vu[0]].add(vu[1])

                # convert back to map of lists
                for v in subtree_adj:
                    subtree_adj[v] = list(subtree_adj[v])
                # is adjacency map is empty, then we have
                # separated vertices
                # create empty lists for them
                if subtree_adj == {}:
                    for vertex in subtree:
                        subtree_adj[vertex] = []
                params = {'directed': False, 'weigthed': False}
                subtree = gg.create(params=params, adj_list=subtree_adj)
                scc = func.connected_components(subtree)
                if len(scc) == 1 and not Tasks.circuit_rank(subtree):
                    flag = True
                else:
                    flag = False
            if flag:
                return 'Forest'
        return 'Graph'
