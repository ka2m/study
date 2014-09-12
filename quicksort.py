def qsort(arr):
    if len(arr) <= 1:
        return arr
    else:
        return qsort([x for x in arr[1:] if x < arr[0]]) + \
            [arr[0]] + \
            qsort([x for x in arr[1:] if x >= arr[0]])

with open('rex') as f:
    array = []
    for line in f:
        p = [int(x) for x in line.split()]
        array = array + p
    print array
    array = qsort(array)
    print('--'*80)
    print array
