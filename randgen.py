import random

randList = [x for x in xrange(0, 50000)]
random.shuffle(randList)
print "\n".join([str(x) for x in randList])
