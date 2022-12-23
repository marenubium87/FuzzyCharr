import copy as c
#calculates the squared euclidean distance between tuples p1 and p2
def calc_sq_dist(p1, p2):
    diff_x = p2[0] - p1[0]
    diff_y = p2[1] - p1[1]
    return diff_x ** 2 + diff_y ** 2


#returns a tuple of the tail's new position based on tuples of
# the tail's old position, the head's old pos, and head's new pos
# (all tuples)
def update_tail(h_old, h_new, t_old):
    #if head's new position and tail's old position are adjacent
    # including diagonally adjacent, do nothing
    # here we use squared euclidean distance for that
    if calc_sq_dist(h_new, t_old) < 4:
        return t_old
    
    #otherwise, reduce the distance from tail to head by up to 1 in
    # both dimensions, if applicable
    t_new = t_old
    for i in range(2):
        if h_new[i] > t_new[i]:
            t_new[i] += 1
        elif h_new[i] < t_new[i]:
            t_new[i] -= 1
    return t_new
    
n = 999
start = [444, 444]
grid = []

for _ in range(n):
    grid.append([0] * n)

head_old = c.copy(start)
tail_old = c.copy(start)
head_new = c.copy(start)
tail_new = c.copy(start)
f = open(r'day9_input.txt', mode='r')

raw = f.read().splitlines()
raw = [s.split() for s in raw]

#returns a new location for head based on old location and instruction
def parse_instruction(ch, h_old):
    if ch == 'R':
        return [h_old[0], h_old[1] + 1]
    elif ch == 'L':
        return [h_old[0], h_old[1] - 1]
    elif ch == 'U':
        return [h_old[0] - 1, h_old[1]]
    elif ch == 'D':
        return [h_old[0] + 1, h_old[1]]

#part A starts here
# for instruction in raw:
#     for i in range(int(instruction[1])):
#         head_old = head_new
#         tail_old = tail_new

#         head_new = parse_instruction(instruction[0], head_old)
#         tail_new = update_tail(head_old, head_new, tail_old)
#         grid[tail_new[0]][tail_new[1]] = 1

# s = 0
# for i in range(n):
#     s += sum(grid[i])
# print(s)
# part A ends here

# part B starts here
#create a rope array of ten links as location tuples
# and do it again for new locations
n_links = 10

rope_old = []
rope_new = []

for _ in range(n_links):
    rope_old.append([444, 444])
    rope_new.append([444, 444])


for instruction in raw:

    for i in range(int(instruction[1])):
        #update head
        rope_old[0] = rope_new[0]
        rope_new[0] = parse_instruction(instruction[0], rope_old[0])
        #update rest of links
        for j in range(1, n_links):
            rope_old[j] = rope_new[j]
            rope_new[j] = update_tail(rope_old[j-1], rope_new[j-1], rope_old[j])
        grid[rope_new[-1][0]][rope_new[-1][1]] = 1
        s = 0
        for i in range(n):
            s += sum(grid[i])
s = 0
for i in range(n):
    s += sum(grid[i])
print(s)









f.close()