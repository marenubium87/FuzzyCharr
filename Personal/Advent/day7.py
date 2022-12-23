#make a node class
class TreeNode:
    def __init__(self, name, size=0):
        self.name = name
        self.size = size
        self.children = []

    def add_child(self, child):
        self.children.append(child)
    
    def __str__(self):
        return f'Name: {self.name}\nSize: {self.size}\nChildren: {[k.name for k in self.children]}'

    def select_child(self, child_name):
        return next((child for child in self.children if child.name == child_name), 
            None)
    
    def set_size(self):
        self.size = sum([s.size for s in self.children])

f = open(r'day7_input.txt', mode = 'r')

#clean data
raw = f.read().splitlines()
raw_s = [s.split() for s in raw]
raw_sa = [[int(sub) if sub.isnumeric() else sub for sub in sublist] for sublist in raw_s]
#print(raw_sa)

dir_stack = []
root = TreeNode("Root", 0)
dir_stack.append(root)
sum_sizes = 0

#for part B
size_list = []

for instruction in raw_sa:
    #make new directory or files as children of current directory
    if instruction[0] == 'dir':
        dir_stack[-1].add_child(TreeNode(instruction[1], 0))
    elif isinstance(instruction[0], int):
        dir_stack[-1].add_child(TreeNode(instruction[1], instruction[0]))
    
    #handling changing directory
    elif instruction[0] == '$' and instruction[1] == 'cd':
        #moving "down" a layer (into a subfolder)
        if instruction[2] != '..':
            dir_stack.append(dir_stack[-1].select_child(instruction[2]))
        else:
            #move up but also do the summation of file sizes of everything
            # that is a child of this directory here
            dir_stack[-1].set_size()
            size_list.append(dir_stack[-1].size)
            if dir_stack[-1].size <= 100000:
                sum_sizes += dir_stack[-1].size
            dir_stack.pop()
    
#for whatever's left in the stack, move back up and populate dir sizes
while len(dir_stack) > 0:
    dir_stack[-1].set_size()
    size_list.append(dir_stack[-1].size)
    if dir_stack[-1].size <= 100000:
        sum_sizes += dir_stack[-1].size
    dir_stack.pop()

size_sorted = sorted(size_list)
#print(size_sorted)
amt_to_delete = root.size - 40000000

for i in range(len(size_sorted)):
    if size_sorted[i] > amt_to_delete:
        print(size_sorted[i])
        break

f.close()