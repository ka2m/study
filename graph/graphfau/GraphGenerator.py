from graphfau.Graph import Graph
from graphfau.DGraph import DGraph
from graphfau.WGraph import WGraph
from graphfau.DWGraph import DWGraph


class GraphGenerator:
    @staticmethod
    def create(params=None, use_file=False, filename=None, adj_list=None):
        if not use_file and not adj_list:
            raise Exception('Using bare adj_list, but passed None')
        if use_file and filename is None:
            raise Exception('Graph creation uses file, but there is None')
        if params is None:
            raise Exception('Params map not passed.')

        used_adj_list = {}
        if adj_list:
            used_adj_list = adj_list
        elif use_file:
            try:
                with open(filename, 'r') as f:
                    for line in f.read().splitlines():
                        vfrom = line.split(':')[0]
                        adj_l = eval('[' + line.split(':')[1] + ']')
                        used_adj_list[vfrom] = set(adj_l)
            except Exception as gen_exp:
                print 'Encountered problems: ', gen_exp

        for v in used_adj_list:
            if type(v) is not int:
                v = int(v)
            for vv in adj_list[v]:
                if type(vv) is not int and type(vv) is not tuple:
                    vv = int(vv)
        return GraphGenerator.generate(params, used_adj_list)

    @staticmethod
    def generate(params, adjacency_list):
        try:
            directed = params['directed']
            weighted = params['weigthed']
        except KeyError as error:
            print 'Not all parameters has been passed: %s' % error
            return None

        if not directed and not GraphGenerator.conform_undir(adjacency_list):
            raise Exception('Adjacency list doesn\'t conform to '
                            'undirected graph')
        if weighted and GraphGenerator.conform_wgh(adjacency_list):
            raise Exception('Adjacency list doesn\'t conform to '
                            'weighted graph')
        if weighted and directed \
           and GraphGenerator.conform_wgh(adjacency_list) \
           and not GraphGenerator.conform_undir(adjacency_list):
            raise Exception('Adjcaency list doesn\'t conform to '
                            'either weighted or directed graph')

        vertices = GraphGenerator.create_vertices_list(adjacency_list)
        adj = GraphGenerator.adjl_to_set(adjacency_list)
        if not directed and not weighted:
            return Graph(vertices, adj)
        if directed and not weighted:
            return DGraph(vertices, adj)
        if not directed and weighted:
            vv = set()
            for v in vertices:
                vv.add(v)
            return WGraph(vv, adj)
        if directed and weighted:
            vv = set()
            for v in vertices:
                vv.add(v)
            return DWGraph(vv, adj)

    @staticmethod
    def conform_undir(adj_list):
        all_conn = []
        for v in adj_list:
            for vv in adj_list[v]:
                conn = {v, vv}
                if conn in all_conn:
                    return False
                all_conn.append(conn)
        return True

    @staticmethod
    def conform_wgh(adj_list):
        for v in adj_list:
            if type(v) is not tuple:
                return False
        return True

    @staticmethod
    def create_vertices_list(adj_list):
        result = set()
        for v in adj_list:
            result.add(v)
            for vv in adj_list[v]:
                if type(vv) is tuple:
                    result.add(vv[0])
                else:
                    result.add(vv)
        return result

    @staticmethod
    def adjl_to_set(adj_list):
        res = {}
        for v in adj_list:
            res[v] = set(adj_list[v])
        return res
