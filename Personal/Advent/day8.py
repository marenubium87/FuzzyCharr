f = open(r'day8_input.txt', mode = 'r')

raw = f.read().splitlines()
raw_grid = [[int(ch) for ch in string] for string in raw]

#print(raw_grid)
g_x = 99
g_y = 99

def vis_from_w(input):
    output = []
    for i in range(g_x):
        next_line = []
        highest = -1
        for j in range(g_y):
            if input[i][j] > highest:
                highest = input[i][j]
                next_line.append(1)
            else:
                next_line.append(0)
        output.append(next_line)
    return output

#from north and south the resulting grid needs to be transposed
def vis_from_n(input):
    output = []
    for j in range(g_y):
        next_line = []
        highest = -1
        for i in range(g_x):
            if input[i][j] > highest:
                highest = input[i][j]
                next_line.append(1)
            else:
                next_line.append(0)
        output.append(next_line)
    #transposition here
    transpose = [[output[j][i] for j in range(len(output))] for i in range(len(output[0]))]
    return transpose

def vis_from_e(input):
    output = []
    for i in range(g_x):
        next_line = []
        highest = -1
        for j in range(g_y):
            if input[i][g_y - 1 - j] > highest:
                highest = input[i][g_y - 1 - j]
                next_line.append(1)
            else:
                next_line.append(0)
        output.append(next_line)
    
    #this result needs to be flipped horizontally to be correct
    corrected = [[output[i][g_y - 1 - j] for j in range(len(output))] 
        for i in range(len(output[0]))]
    return corrected

#from north and south the resulting grid needs to be transposed
def vis_from_s(input):
    output = []
    for j in range(g_y):
        next_line = []
        highest = -1
        for i in range(g_x):
            if input[g_x - 1 - i][j] > highest:
                highest = input[g_x - 1 - i][j]
                next_line.append(1)
            else:
                next_line.append(0)
        output.append(next_line)
    #transposition here
    transpose = [[output[j][i] for j in range(len(output))] for i in range(len(output[0]))]
    corrected = [[transpose[g_x - 1 - i][j] for j in range(len(transpose))]
        for i in range(len(transpose[0]))]
    return corrected

vis_e = vis_from_e(raw_grid)
vis_n = vis_from_n(raw_grid)
vis_s = vis_from_s(raw_grid)
vis_w = vis_from_w(raw_grid)

answer_grid = []
sum = 0
for i in range(g_x):
    next_line = []
    for j in range(g_y):
        if vis_e[i][j] > 0 or vis_s[i][j] > 0 or  vis_n[i][j] > 0 or vis_w[i][j] > 0:
            next_line.append(1)
            sum += 1
        else:
            next_line.append(0)
    answer_grid.append(next_line)

#part A
#print(sum)

#individual sight distances
def compute_e_dist(input, i, j):
    ref_height = input[i][j]
    dist = 0
    for x in range(1, g_x - j):
        dist += 1
        if(input[i][j + x] >= ref_height):
            break
    return dist

def compute_s_dist(input, i, j):
    ref_height = input[i][j]
    dist = 0
    for y in range(1, g_y - i):
        dist += 1
        if(input[i + y][j] >= ref_height):
            break
    return dist

def compute_w_dist(input, i, j):
    ref_height = input[i][j]
    dist = 0
    for x in range(1, j + 1):
        dist += 1
        if(input[i][j - x] >= ref_height):
            break
    return dist

def compute_n_dist(input, i, j):
    ref_height = input[i][j]
    dist = 0
    for y in range(1, i + 1):
        dist += 1
        if(input[i - y][j] >= ref_height):
            break
    return dist

# figures out the viewing score for any given tree in input
# at location i, j
def compute_scenic_score(input, i, j):
    return (
        compute_e_dist(input, i, j) * 
        compute_w_dist(input, i, j) * 
        compute_s_dist(input, i, j) *
        compute_n_dist(input, i, j)
    )

#print(compute_scenic_score(raw_grid, 3, 2))

max_score = 0
for i in range(1, g_y - 1):
    for j in range(1, g_x - 1):
        scenic_score = compute_scenic_score(raw_grid, i, j)
        if scenic_score > max_score:
            max_score = scenic_score

#part B
print(max_score)

f.close()