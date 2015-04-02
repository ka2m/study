from graphfau.Graph import Graph


class Tasks:
    @staticmethod
    def nbs(g, v1, v2):
        l1 = g.get_connected_vertices(v1)
        l2 = g.get_connected_vertices(v2)
        res = set(l1).intersection(set(l2))
        if not res:
            print('No neighbours!')
        return list(res)
