from collections import defaultdict
from functools import cmp_to_key

with open('day13_input.txt') as file:
    lines = [line.strip() for line in file.readlines()]

def compare(a, b):
    if type(a) == type(b) == int:
        if a < b:
            return -1
        elif a > b:
            return 1
        else:
            return 0
    elif type(a) == type(b) == list:
        n = len(a)
        m = len(b)
        res = 0
        for i in range(min(n, m)):
            res = compare(a[i], b[i])
            if res:
                break
        if res == 0:
            if n < m:
                return -1
            elif n > m:
                return 1
            else: return 0
    elif type(a) == int:
        res = compare([a], b)
    else:
        res = compare(a, [b])
    return res

# Part 1
d = defaultdict(list)
ans = 0
idx = 1
key = 'left'
s1 = set()
for line in lines:
    if not line:
        continue
    d[key] = eval(line)
    if key == 'left':
        key = 'right'
    else:
        key = 'left'
        res = compare(d['left'], d['right'])
        if res == -1:
            s1.add(idx)
            ans += idx
        idx += 1
print(s1)