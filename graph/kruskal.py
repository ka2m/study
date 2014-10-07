parent = dict()
rank = dict()


def make_set(vertex):
    parent[vertex] = vertex
    rank[vertex] = 0


def find(vertex):
    if parent[vertex] != vertex:
        parent[vertex] = find(parent[vertex])
    return parent[vertex]


def union(vertex1, vertex2):
    root_vertex1 = find(vertex1)
    root_vertex2 = find(vertex2)

    if root_vertex1 == root_vertex2:
        return

    if root_vertex1 < root_vertex2:
        parent[root_vertex1] = root_vertex2
    elif root_vertex1 > root_vertex2:
        parent[root_vertex2] = root_vertex1
    else:
        parent[root_vertex2] = root_vertex1
        rank[root_vertex1] += 1


def kruskal(vertexs, edges):
    mst = []
    for vertex in vertexs:
        make_set(vertex)

    edges.sort()

    for edge in edges:
        weight, vertex1, vertex2 = edge
        if find(vertex1) != find(vertex2):
            union(vertex1, vertex2)
            mst.append(edge)
    return mst

vertexs = ['A', 'B', 'C', 'D']
edges = [
    (1, 'A', 'B'),
    (5, 'A', 'C'),
    (3, 'A', 'D'),
    (4, 'B', 'C'),
    (2, 'B', 'D'),
    (1, 'C', 'D'),
]

print kruskal(vertexs, edges)


vertexs = ['A', 'B', 'C', 'D', 'E', 'F']
edges = [
    (5, 'A', 'B'),
    (1, 'A', 'F'),
    (2, 'A', 'D'),
    (3, 'B', 'C'),
    (3, 'B', 'E'),
    (1, 'C', 'D'),
    (4, 'C', 'F'),
    (4, 'D', 'E'),
    (2, 'E', 'F'),
]

print kruskal(vertexs, edges)
