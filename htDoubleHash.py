import random


class Item:
    def __init__(self, aKey, aValue):
        self.key = aKey
        self.value = aValue


class MyHashTable:
    def __init__(self, size):
        self.table = [None] * size
        self.deleted = [True] * size

    def add(self, item):
        x = self.hash1(item.key)
        y = self.hash2(item.key)
        size = len(self.table)
        for i in range(0, size - 1):
            if x >= size - 1:
                self.table.extend(None for i in range(0, size - x + 1))
                self.deleted.extend(True for i in range(0, size - x + 1))
                size = len(self.table)
            if self.table[x] is None or self.deleted[x]:
                self.table[x] = item
                self.deleted[x] = False
                print("Add item with key: %d, value: %s to %d" % (item.key,
                                                                  item.value,
                                                                  x))
                return
            x = (x + y) % size

    def search(self, key):
        x = self.hash1(key)
        y = self.hash2(key)
        size = len(self.table)
        for i in range(0, size - 1):
            if self.table[x].key == key and not self.deleted[x]:
                return self.table[x]
            x = (x + y) % size
        return None

    def delete(self, key):
        x = self.hash1(key)
        y = self.hash2(key)
        for i in range(len(self.table)):
            if table[x] is not None:
                if table[x].key == key:
                    self.deleted[x] = True
                else:
                    return
            x = (x + y) % len(self.table)

    def hash1(self, key):
        key = key**2
        key = key << 15
        return int(key % 1024)

    def hash2(self, key):
        f = key * 0.618
        f = f - int(f)
        return int(701*f)


table = MyHashTable(13)
it = Item(0, "Vasya")
table.add(it)
it = Item(1, "Petya")
table.add(it)
it = Item(2, "Igor")
table.add(it)
it = Item(8, "Yoba")
table.add(it)
print(table.search(2).value)
print(str(table.table))
