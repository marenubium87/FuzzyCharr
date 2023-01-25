import math as m
from queue import PriorityQueue as pq

class Node:
    def __init__(self, loc, height):
        self.loc = loc
        self.height = height
        self.cost = [9999, 9999]
        self.est_cost = 9999
        self.parent = (0, 0)
        self.visited = False
    
    def __str__(self):
        return f'loc: {self.loc} height: {self.height} cost: {self.cost} parent: {self.parent}'

def make_node(loc, height_ch):
    height = -1
    if height_ch == 'S':
        height = 0
    elif height_ch == 'E':
        height = 27
    else:
        height = ord(height_ch) - ord('a') + 1
    return Node(loc, height)

#finds first node that has a height matching request, returns the node
#mainly used to find start (height = 0) or end (height = 27)
def find_node(nodes, height):
    for i in range(len(nodes)):
        for j in range(len(nodes[i])):
            if nodes[i][j].height == height:
                return nodes[i][j]

#figures out the height difference from node here to the neighbor in the dir given
# for example, if the north neighbor is two higher than here, returns 2
def find_height_change(nodes, here, dir):
    neighbor_height = -1
    row, col = here.loc
    if dir == 'n':
        neighbor_height = nodes[row - 1][col].height
    if dir == 's':
        neighbor_height = nodes[row+1][col].height
    if dir == 'e':
        neighbor_height = nodes[row][col+1].height
    if dir == 'w':
        neighbor_height = nodes[row][col-1].height
    return neighbor_height - nodes[row][col].height

#returns 1 if on the node grid can visit dir (n, e, s, w) from node here, 0 else
def can_visit(nodes, here, dir):
    grid_height = len(nodes)
    grid_width = len(nodes[0])

    row, col = here.loc

    #check if we're at a boundary
    if dir == 'n':
        #top of grid, can't go north
        if row == 0:
            return 0
    elif dir == 's':
        #bottom of grid, can't go south
        if row == grid_height - 1:
            return 0
    elif dir == 'e':
        #right side of grid, can't go east
        if col == grid_width - 1:
            return 0
    elif dir == 'w':
        #left side of grid, can't go west
        if col == 0:
            return 0

    #if direction is fine,
    #check the height diff btwn the two nodes; 2 or mroe is no good
    if find_height_change(nodes, here, dir) > 1:
        return 0

    return 1

#calculates distance to goal for each node in nodes
def calc_heuristic_cost(nodes, end):
    for i in range(len(nodes)):
        for j in range(len(nodes[0])):
            nodes[i][j].cost[1] = dist(nodes[i][j].loc, end.loc)

#returns the node on the nodes grid from here in direction dir (n, e, s, w)
def get_neighbor(nodes, here, dir):
    row, col = here.loc
    if dir == 'n':
        return nodes[row - 1][col]
    elif dir == 'e':
        return nodes[row][col + 1]
    elif dir == 's':
        return nodes[row + 1][col]
    elif dir == 'w':
        return nodes[row][col - 1]

#finds distance between s (tuple) and t (tuple) in deci-units, 
# with integer truncation
def dist(s, t):
    c_sq = pow(t[0] - s[0], 2) + pow(t[1] - s[1], 2)
    return int(m.sqrt(c_sq) * 10)

f = open(r'day12_input.txt', mode = 'r')

raw = f.read().splitlines()
raw = [list(s) for s in raw]
# print(raw)

#makes node grid
def make_nodes(raw):
    nodes = []
    for i in range(len(raw)):
        node_row = []
        for j in range(len(raw[i])):
            node_row.append(make_node((i, j), raw[i][j]))
        nodes.append(node_row)
    return nodes





def do_astar_things(starting_coords, raw):
    nodes = make_nodes(raw)

    starting = nodes[starting_coords[0]][starting_coords[1]]
    ending = find_node(nodes, 27)
    calc_heuristic_cost(nodes, ending)
    starting.cost[0] = 0
    starting.est_cost = sum(starting.cost)
    starting.parent = starting.loc
    starting.height = 1
    #print(starting.est_cost)

    dirs = ['n', 'e', 'w', 's']
    # for dir in dirs:
    #     print(find_height_change(nodes, nodes[1][3], dir))

    to_visit = pq()
    to_visit.put((starting.est_cost, id(starting), starting))
    current = starting
    cycles = 0

    while current.height != 27:
        cycles += 1
        current = to_visit.get()[2]     #for pq, get returns in form of (priority, item)
        if current.visited == True:
            continue
        #print(f'visiting {current.loc}')
        current.visited = True
        #look at each neighbor that hasn't been visited
        for dir in dirs:
            if can_visit(nodes, current, dir) == 1:
                neighbor = get_neighbor(nodes, current, dir)
                if neighbor.visited == False:
                    #update cost to get to this neighbor if lower than previously
                    if current.cost[0] + 10 < neighbor.cost[0]:
                        neighbor.cost[0] = current.cost[0] + 10
                        neighbor.parent = current.loc
                    #recompute total est cost
                    neighbor.est_cost = sum(neighbor.cost)
                    to_visit.put((neighbor.est_cost, id(neighbor), neighbor))


    count = 0
    current = ending
    while current.loc != starting.loc:
        count += 1
        #print(current.loc)
        current = nodes[current.parent[0]][current.parent[1]]
    return count


path_lengths = [do_astar_things((i, 0), raw) for i in range(0, 41)]
print(path_lengths)



























f.close()