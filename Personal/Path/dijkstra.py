from queue import PriorityQueue

class Node:
    def __init__(self, name, neighbors):
        self.name = name
        self.visited = False
        self.cost = 1000    #arbitrary max
        self.neighbors = neighbors
        self.parent = ''

    def __str__(self):
        return f'{self.name} : {self.neighbors}; Cost = {self.cost}; Parent = {self.parent}'

graph = dict()

graph['A'] = Node('A', {'F': 12, 'L': 6})
graph['F'] = Node('F', {'A': 12, 'L': 3, 'V': 4, 'W': 9})
graph['L'] = Node('L', {'A': 6, 'F': 3, 'V': 1, 'E': 5})
graph['V'] = Node('V', {'F': 4, 'L': 1, 'E': 5, 'W': 6})
graph['E'] = Node('E', {'L': 5, 'V': 5, 'W': 2})
graph['W'] = Node('W', {'E': 2, 'V': 6, 'F': 9})

for key, val in graph.items():
    print(val)

to_visit = PriorityQueue()
graph['A'].cost = 0
to_visit.put((0, 'A'))

while to_visit.empty() == False:
    #dequeue the next node (which is the lowest cum cost from start), henceforth "here"
    here = graph[to_visit.get()[1]]     #get returns in form of (priority, item)
    #mark here as visited
    here.visited = True
    for adj in here.neighbors:
        #check costs of every node in adjacency list which hasn't been visited
        if graph[adj].visited == False:
            #if cost is > cost of current node + adj_val(here, there)
            #then update cost and make that node's parent this node
            if graph[adj].cost > here.cost + here.neighbors[adj]:
                graph[adj].cost = here.cost + here.neighbors[adj]
                graph[adj].parent = here.name
            #then enqueue child node
            to_visit.put((here.neighbors[adj], adj))

for key in graph:
    print(graph[key])
    
    
    # can have negative edges
    # can have cycles, but
    # cannot do the same cycle consecutively
    # cannot visit the same edge more than three times

    # A -> B -> A -> C -> D -> A
    

