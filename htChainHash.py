import random


class Item:
    def __init__(self, aKey, aValue):
        self.key = aKey
        self.value = aValue

    def __str__(self):
        return ('(%d, %s)' % (self.key, self.value))


class MyHashTable:
    def __init__(self, size):
        self.table = []
        for i in range(0, size - 1):
            self.table.insert(i, [])

    def add(self, item):
        x = self.hash(item.key)

        added = False
        for entry in self.table[x]:
            if entry.key == item.key:
                print('here')
                entry.value = item.value
                added = True
                break

        if not added:
            self.table[x].append(item)

        print('Add item with key: %d value: %s to chain: %d at %d' % (item.key,
              item.value, x, self.table[x].index(item)))

    def search(self, key):
        x = self.hash(key)
        if self.table[x] is None:
            return Item(None, None)

        for entry in self.table[x]:
            if entry.key == key:
                return entry

        return Item(None, None)

    def hash(self, key):
        return int(len(self.table) * ((key * 0.61) % 1.0))

    def printout(self):
        for item in self.table:
            try:
                print('chain #%d: ' % self.table.index(item) +
                      '[', item[0], ', '.join(map(str, item[1:])) + ']')
            except IndexError:
                pass


table = MyHashTable(10)
it = Item(0, 'Vasya')
table.add(it)
it = Item(1, 'Petya')
table.add(it)
it = Item(2, 'Igor')
table.add(it)
it = Item(5, 'Vlad')
table.add(it)
print(table.search(0).value)
table.printout()