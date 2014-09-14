import random


class Item:
    def __init__(self, aKey, aValue):
        self.key = aKey
        self.value = aValue


class MyHashTable:
    def __init__(self, size):
        self.table = [None] * size

    def add(self, item):
        x = self.hash1(item.key)
        y = self.hash2(item.key)
        size = len(self.table)
        for i in range(0, size - 1):
            if self.table[x] is None:
                self.table[x] = item
                print("Add item with key: %d, value: %s to %d" % (item.key,
                                                                  item.value,
                                                                  x))
                return
            x = (x + y) % size
        self.resize()

    def search(self, key):
        x = self.hash1(key)
        y = self.hash2(key)
        size = len(self.table)
        for i in range(0, size - 1):
            if self.table[x] is not None and self.table[x].key == key:
                return self.table[x]
            x = (x + y) % size
        return Item(None, None)

    def hash1(self, key):
        key = key**2
        key = key << 15
        return int(key % 1024)

    def hash2(self, key):
        f = key * 0.618
        f = f - int(f)
        return int(701*f)

    def resize(self):
        size = len(self.table)
        self.table.extend(None)


table = MyHashTable(8)
it = Item(0, "Vasya")
table.add(it)
it = Item(1, "Petya")
table.add(it)
it = Item(2, "Igor")
table.add(it)
it = Item(8, "Vlad")
table.add(it)
print(table.search(9).value)
print(str(table.table))
