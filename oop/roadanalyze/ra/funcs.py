from ra.models import PointOfInterest, Road, RoadLoadEvent, Car


def generate_connection_list():
    res = []
    for road in Road.objects.all():
        res.append([road.point_from.name,
                    road.point_to.name,
                    road.length])
    return res


def djikstra(all_conns, from_vertex, dest):
    vertices = [x.name for x in PointOfInterest.objects.all()]
    dist = dict.fromkeys(vertices, float('inf'))
    paths = dict.fromkeys(vertices, None)
    visited = dict.fromkeys(vertices, False)
    dist[from_vertex] = 0
    for count in vertices:
        vertex = None
        for vv in vertices:
            if not visited[vv] and (vertex is None
                                    or dist[vv] < dist[vertex]):
                vertex = vv
        if dist[vertex] == float('inf'):
            break
        visited[vertex] = True

        for conns in [x for x in all_conns if x[0] == vertex or x[1] == vertex]:
            to_vertex = conns[0]
            if conns[0] == vertex:
                to_vertex = conns[1]
            wght = conns[2]
            new_wght = dist[vertex] + wght
            if new_wght < dist[to_vertex]:
                dist[to_vertex] = new_wght
                paths[to_vertex] = vertex
    res = [dest]
    ptr = paths[dest]
    while paths[ptr] is not None:
        res.append(ptr)
        ptr = paths[ptr]
    res.append(from_vertex)
    return res[::-1]


def add_car(cname, spd, pfrom, pto, hr, mn, sec):
    dt = hr * 3600 + mn * 60 + sec
    location_from = PointOfInterest.objects.get(pk=pfrom)
    location_to = PointOfInterest.objects.get(pk=pto)
    Car(name=cname, speed=spd,
        drive_from=location_from,
        drive_to=location_to,
        starting_time=dt).save()
    path = djikstra(generate_connection_list(), location_from.name, location_to.name)

    locs = []
    for p in path:
        locs.append(PointOfInterest.objects.get(name=p))

    roads = []
    for i in range(0, len(locs) - 1):
        try:
            roads.append(Road.objects.get(point_from=locs[i], point_to=locs[i+1]))
        except Road.DoesNotExist:
            roads.append(Road.objects.get(point_from=locs[i+1], point_to=locs[i]))

    current_time = dt
    for road in roads:
        prev_time = current_time
        current_time += int((road.length / spd) * 3600)
        RoadLoadEvent(road=road,
                      load_started=prev_time,
                      load_ended=current_time).save()
