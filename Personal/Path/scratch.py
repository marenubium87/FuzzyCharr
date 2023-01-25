from queue import Queue as q

class Thing:
    def __init__(self, k, v):
        self.k = k
        self.v = v

some_thing = Thing(5, 3)
a = dict()
a[some_thing.k] = some_thing

print(a)