__author__ = 'fau'


class Graph:

    def __init__(self, filename=None):
        self.adjmap = {}

        if not filename is None:
            with open(filename, 'r') as f:
                lines = f.readline()
                print(lines)
                for line in f.read().splitlines():
                    key = line.split(':')[0]
                    adj_list = eval('[' + line.split(':')[1] + ']')

                    self.add_node(key, adj_list)

    def add_node(self, key, *adj_list):
        print('---')
        print(key)
        print(adj_list)
        # if type(adj_list) is list:
        #     self.adjmap[key] = adj_list
        # else:
        #     if not len(self.adjmap[str(key)]):
        #         self.adjmap[key] = []

            # for elem in adj_list:
            #     self.adjmap[key].append(elem)
