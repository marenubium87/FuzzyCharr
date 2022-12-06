f = open(r'day6_input.txt', mode = 'r')

str = f.read()
#print(str)

my_set = set()
index = -1

while len(my_set) < 4:
    index += 1
    #unpacking
    my_set = {*str[index:index+4]}

#part A
#index is the start of the four character unique sequence so
#the end of it is at index + 3
#plus another 1 because normal, non-weird people start counting from 1, not 0
print(index + 3 + 1)

#part B
index = -1
while len(my_set) < 14:
    index += 1
    my_set = {*str[index:index+14]}
    
print(index + 13 + 1)

