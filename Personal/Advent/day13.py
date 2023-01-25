import re

f = open('day13_input.txt', mode = 'r')

raw = f.read().splitlines()
#print(raw)

l1 = [raw[3 * n] for n in range(len(raw) // 3)]
l2 = [raw[3 * n + 1] for n in range(len(raw) // 3)]

def parse_wrapper(line):
    output = parse_input(line)
    return output[0]

def parse_input(line):
    output = []
    while len(line) > 0:
        if line[0].isdigit():
            #find all digits until next non-digit
            i = 1
            if len(line) == 1:
                output.append(int(line[0]))
            else:
                while i < len(line) and line[i].isdigit():
                    i += 1
                output.append(int(line[0:i]))
            line = line[i:]
        elif line[0] == ',':
            line = line[1:]
        elif line[0] == '[':
            #look for where the corresponding ] is
            i = 0
            #number of '['s that have not been closed by a ']'
            imbal = 1
            while(True):
                i += 1
                if line[i] == '[':
                    imbal += 1
                elif line[i] == ']':
                    imbal -= 1
                    if imbal == 0:
                        break
            output.append(parse_input(line[1:i]))
            line = line[i + 1:]
    return output

parsed_l1 = []
parsed_l2 = []

for i in range(len(l1)):
    parsed_l1.append(parse_wrapper(l1[i]))
    parsed_l2.append(parse_wrapper(l2[i]))

def make_lists(left, right):
    #if L & R are ints
    if isinstance(left, int) and isinstance(right, int):
        return [left], [right]
    #if L & R are lists
    elif isinstance(left, list) and isinstance(right, list):
        if left == [] or right == []:
            return left, right
        else:
            return make_lists(left[0], right[0])
    # if only R is a list (L is an int)
    elif isinstance(left, int):
        left = [left]
        if right == []:
            return left, right
        else:
            return make_lists(left[0], right[0])
    # if only L is a list (R is an int)
    elif isinstance(right, int):
        right = [right]
        if left == []:
            return left, right
        else:
            return make_lists(left[0], right[0])

#compares an individual element in the list, handling sublists via recursion
# returns 1 if left is smaller (correct order), -1 if right is smaller (wrong order)
# returns 0 if indeterminate between these two elements
def compare_individual_element(left, right):

    left, right = make_lists(left, right)

    if len(left) == 0 and len(right) == 0:
        return 0
    #only left side has run out of items
    elif len(left) == 0:
        return 1
    #only right side has run out of items
    elif len(right) == 0:
        return -1

    #if both sides have at least one element left, perform comparison of values
    else:
        if left[0] < right[0]:
            return 1
        elif left[0] > right[0]:
            return -1
        elif left[0] == right[0]:
            return compare_lists(left[1:], right[1:])            

#compares a list from left and right lists, each of which could contain sublists
# returns 1 if correct order, -1 if incorrect order
def compare_lists(left, right):
    result = 1
    i = 0
    if len(left) == 0:
        return 1
    elif len(right) == 0:
        return -1
    min_length = min(len(left), len(right))
    while result == 1 and i < min_length:
        result = compare_individual_element(left[i], right[i])
        if result == -1:
            break
        i += 1
    if i == min_length:
        if len(left) == min_length:
            result = 1
        else:
            result = -1
    return result

count = 0
for i in range(len(l1)):
    print(compare_lists(parsed_l1[i], parsed_l2[i]))

f.close()