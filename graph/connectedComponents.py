class Data(object):

    def __init__(self, name):
        self.__name = name
        self.__links = set()

    @property
    def name(self):
        return self.__name

    @property
    def links(self):
        return set(self.__links)

    def add_link(self, other):
        self.__links.add(other)
        other.__links.add(self)


def connected_components(nodes):

    result = []

    nodes = set(nodes)

    while nodes:

        n = nodes.pop()

        group = {n}

        queue = [n]

        # Iterate the queue.
        # When it's empty, we finished visiting a group of connected nodes.
        while queue:

            n = queue.pop(0)

            neighbors = n.links

            neighbors.difference_update(group)

            nodes.difference_update(neighbors)

            group.update(neighbors)

            queue.extend(neighbors)

        result.append(group)

    return result


if __name__ == "__main__":

    # The first group, let's make a tree.
    a = Data("a")
    b = Data("b")
    c = Data("c")
    d = Data("d")
    e = Data("e")
    f = Data("f")
    a.add_link(b)    # '     a
    a.add_link(c)    # '    / \
    b.add_link(d)    # '   b   c
    c.add_link(e)    # '  /   / \
    c.add_link(f)    # ' d   e   f

    # The second group, let's leave a single, isolated node.
    g = Data("g")

    # The third group, let's make a cycle.
    h = Data("h")
    i = Data("i")
    j = Data("j")
    k = Data("k")
    h.add_link(i)    # '   h----i
    i.add_link(j)    # '   |    |
    j.add_link(k)    # '   |    |
    k.add_link(h)    # '   k----j

    # Put all the nodes together in one big set.
    nodes = {a, b, c, d, e, f, g, h, i, j, k}

    # Find all the connected components.
    number = 1
    for components in connected_components(nodes):
        names = sorted(node.name for node in components)
        names = ", ".join(names)
        print "Group #%i: %s" % (number, names)
        number += 1
