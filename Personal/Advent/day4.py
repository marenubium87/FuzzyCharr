import re

def detect_contain(a):
    if int(a[0]) <= int(a[2]) and int(a[1]) >= int(a[3]):
        return 1
    elif int(a[0]) >= int(a[2]) and int(a[1]) <= int(a[3]):
        return 1
    else:
        return 0

def detect_overlap(a):
    if int(a[0]) > int(a[3]):
        return 0
    elif int(a[1]) < int(a[2]):
        return 0
    else:
        return 1

f = open(r'day4_input.txt', mode='r')

raw_assigns = f.read().splitlines()

clean_assigns = [re.split('-|,', s) for s in raw_assigns]

#part A
contains_list = [detect_contain(s) for s in clean_assigns]
print(sum(contains_list))

#part B
overlap_list = [detect_overlap(s) for s in clean_assigns]
print(sum(overlap_list))

f.close()