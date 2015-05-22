from graphfau.Algo import Algo as func
# from graphfau.GraphGenerator import GraphGenerator as gg
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
        count_cc = len(func.connected_components(g))
        # if graph has one connected component and has no circuits
        # it is a tree
        rank = Tasks.circuit_rank(g)
        if count_cc == 1 and not rank:
            return 'Tree'
            # if graph has many CCs and has no circuits
            # it is a forest
        if count_cc > 1 and not rank:
            return 'Forest'
            """
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
                params = {'directed': False, 'weighted': False}
                subtree = gg.create(params=params, adj_list=subtree_adj)
                scc = func.connected_components(subtree)
                if len(scc) == 1 and not Tasks.circuit_rank(subtree):
                    flag = True
                else:
                    flag = False
            if flag:
                return 'Forest'
            """
        return 'Graph'

    @staticmethod
    def boruvka(g):
        mst = func.boruvka(g)
        print mst.get_unique_connections()

    @staticmethod
    def floyd_lengths(g):
        """
            Task 4.9b Get connection LENGTHS between all the vertices
            Graph: directed, weighted
        """
        verbose = True
        d = func.floyd(g)
        for vertex in d:
            for to in d[vertex]:
                lng = d[vertex][to]
                if not vertex == to:
                    if not lng == float('inf'):
                        print vertex, '--', to, 'has path of length', lng
                    elif verbose:
                        print 'There is no path between %d and %d' % (vertex,
                                                                      to)

    @staticmethod
    def djikstra_count_paths(g, from_vertex):
        """
            Task 4.20a Get number of shortest paths from some vertex to all
            the others
            Graph: not directed, weighted
        """
        _, path = func.djikstra(g, from_vertex, multi_path=True)
        for vertex in path:
            if not vertex == from_vertex:
                print '%d-%d: %d' % (from_vertex, vertex, len(path[vertex]))

    @staticmethod
    def ford_pairs(g):
        """
            Task 4.17c Get CONNECTIONS between all the vertices
            Graph: directed, weighted
        """
        for vertex in g.vertices:
            cc, path = func.ford(g, vertex)
            for to_vertex in path:
                if to_vertex in cc:
                    if not to_vertex == vertex:
                        print 'There is negative cycle %d-%d' % (vertex, to_vertex)
                else:
                    if path[to_vertex] is None:
                        if not to_vertex == vertex:
                            print 'There is no path %d-%d' % (vertex, to_vertex)
                    else:
                        if not to_vertex == vertex:
                            rpath = []
                            curv = to_vertex

                            while curv is not None:
                                rpath.append(curv)
                                curv = path[curv]
                            print 'Path %d-%d: %s' %  (vertex, to_vertex, rpath[::-1])




    @staticmethod
    def flow_ford_fulkerson(g, source, sink):
        """
            Task 5 Ford-Fulkerson algorithm: max flow in the network
            Graph: network
        """
        edge_id_list = []
        idx = 1
        for edge in g.get_w_edges():
            edge_id_list.append((idx, (edge[0], edge[1])))
            edge_id_list.append((-idx, (edge[1], edge[0])))
            idx += 1
        flow = dict.fromkeys([t[0] for t in edge_id_list], 0)
        path = func.find_flow_path(g,
                                   edge_id_list,
                                   flow,
                                   source,
                                   sink,
                                   [])
        while path is not None:
            residuals = [edge[2] -
                         flow[func.get_flow_id_from_edge(edge,
                                                         edge_id_list,
                                                         flow)]
                         for edge in path]
            print residuals
            _flow = min(residuals)
            for edge in path:
                _id = func.get_flow_id_from_edge(edge, edge_id_list, flow)
                flow[_id] += _flow
                flow[-_id] -= _flow
            path = func.find_flow_path(g, edge_id_list, flow, source, sink, [])

        return sum(flow[func.get_flow_id_from_edge(edge, edge_id_list, flow)]
                   for edge in g.get_connections(source) if edge[2])
