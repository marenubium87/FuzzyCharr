import copy
#parse input first

def move(stacks, num, i, j):
    for _ in range(num):
        stacks[j].append(stacks[i].pop())

def modified_move(stacks, num, i, j):
    temp = []
    for _ in range(num):
        temp.append(stacks[i].pop())
    for _ in range(num):
        stacks[j].append(temp.pop())

f = open(r'day5_input.txt', mode = 'r')
raw = f.read().splitlines()
raw_s = [s.split() for s in raw]

instructs = [[int(s[1]), int(s[3]), int(s[5])] for s in raw_s]
#print(instructs)

stacks_a = [
    #empty 0th index stack so that the instructions line up the stacks
    [],
    ['D', 'B', 'J', 'V'],
    ['P', 'V', 'B', 'W', 'R', 'D', 'F'],
    ['R', 'G', 'F', 'L', 'D', 'C', 'W', 'Q'],
    ['W', 'J', 'P', 'M', 'L', 'N', 'D', 'B'],
    ['H', 'N', 'B', 'P', 'C', 'S', 'Q'],
    ['R', 'D', 'B', 'S', 'N', 'G'],
    ['Z', 'B', 'P', 'M', 'Q', 'F', 'S', 'H'],
    ['W', 'L', 'F'],
    ['S', 'V', 'F', 'M', 'R']
]

stacks_b = copy.deepcopy(stacks_a)

for i in range(len(instructs)):
    move(stacks_a, instructs[i][0], instructs[i][1], instructs[i][2])

#part A
for i in range(1, len(stacks_a)):
    print(stacks_a[i].pop())

#part B
for i in range(len(instructs)):
    modified_move(stacks_b, instructs[i][0], instructs[i][1], instructs[i][2])

print('break:')

for i in range(1, len(stacks_b)):
    print(stacks_b[i].pop())










f.close()