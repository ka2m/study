def ineffective_z_func(s):
    res = [0] * len(s)
    for i in xrange(1, len(s)):
        while i + res[i] < len(s) and s[res[i]] == s[i + res[i]]:
            res[i] += 1

    return res

def effective_z_func(s):
    res = [0] * len(s)
    l = 0
    r = 0
    for i in xrange(1, len(s)):
        if i <= r:
            res[i] = min(r - i + 1, res[i - l])
        while  i + res[i] < len(s) and s[res[i]] == s[i + res[i]]:
            res[i] += 1

        t = i + res[i] - 1
        if (t > r):
            l = i
            r = t

    return res

print ineffective_z_func('aaabaab')
print ineffective_z_func('aaaaaaa')
print ineffective_z_func('abracadabra')

print effective_z_func('aaabaab')
print effective_z_func('aaaaaaa')
print effective_z_func('abracadabra')
