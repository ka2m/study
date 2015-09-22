# split range equally
def split_range(start, end, count):
    step = abs((end - start) * 1.0 / (count * 1.0))
    result = [start]
    while len(result) < count - 1:
        start += step
        result.append(start)
    result.append(end)
    return [round(x, 10) for x in result]


def split_between(rng):
    new_range = []
    for i in xrange(len(rng) - 1):
        new_range.append(rng[i])
        new_range.append(round((rng[i] + rng[i + 1]) / 2, 5))
    new_range.append(rng[-1])
    return new_range, [x for x in new_range if x not in rng]
