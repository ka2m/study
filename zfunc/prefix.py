def prefix_func(s):
    res = [0] * len(s)
    for i in xrange(1, len(s)):
        j = res[i-1]
        while j > 0 and s[i] != s[j]:
            j = res[j-1]
        if s[i] == s[j]:
            j += 1
        res[i] = j
    return res

print prefix_func('aabaaab')
print prefix_func('abcab')
print prefix_func('abcabc')
