from queue import Queue as q
from operator import add
from operator import mul
from operator import pow

class Monkey:
    def __init__(self, id, throw_t_id, throw_f_id, operation, operand):
        self.id = id
        self.items = q()
        self.throw_t_id = throw_t_id
        self.throw_f_id = throw_f_id
        self.num_inspects = 0
        self.operand = operand
        self.operation = operation

    def __repr__(self):
        return f'id {self.id} n_ins {self.num_inspects}'

#returns value after monkey operation and div by 3
def monkey_op(id, item):
    if id == 0:
        item *= 7
    elif id == 1:
        item += 5
    elif id == 2:
        item *= item
    elif id == 3:
        item += 6
    elif id == 4:
        item *= 11
    elif id == 5:
        item += 8
    elif id == 6:
        item += 1
    elif id == 7:
        item += 4
    return item // 3

def test_monkey_op(id, item):
    if id == 0:
        item *= 19
    elif id == 1:
        item += 6
    elif id == 2:
        item *= item
    elif id == 3:
        item += 3
    return item // 3

# after division by 3, monkey tests to decide who to throw to
def monkey_test(id, item):
    test = 1
    if id == 0:
        test -= item % 3
    elif id == 1:
        test -= item % 13
    elif id == 2:
        test -= item % 2
    elif id == 3:
        test -= item % 11
    elif id == 4:
        test -= item % 5
    elif id == 5:
        test -= item % 17
    elif id == 6:
        test -= item % 19
    elif id == 7:
        test -= item % 7
    
    if test < 0:
        test = 0
    return test

def test_monkey_test(id, item):
    test = 1
    if id == 0:
        test -= item % 23
    elif id == 1:
        test -= item % 19
    elif id == 2:
        test -= item % 13
    elif id == 3:
        test -= item % 17

    if test < 0:
        test = 0
    return test

monkeys = []
monkeys.append(Monkey(0, 4, 1, mul, 7))
monkeys.append(Monkey(1, 7, 3, add, 5))
monkeys.append(Monkey(2, 6, 5, pow, 2))
monkeys.append(Monkey(3, 2, 6, add, 6))
monkeys.append(Monkey(4, 1, 7, mul, 11))
monkeys.append(Monkey(5, 4, 0, add, 8))
monkeys.append(Monkey(6, 0, 5, add, 1))
monkeys.append(Monkey(7, 3, 2, add, 4))

# test_monkeys = []
# test_monkeys.append(Monkey(0, 2, 3))
# test_monkeys.append(Monkey(1, 2, 0))
# test_monkeys.append(Monkey(2, 1, 3))
# test_monkeys.append(Monkey(3, 0, 1))


# test_monkey_items = [
#     [79, 98],
#     [54, 65, 75, 74],
#     [79, 60, 97],
#     [74]
# ]

monkey_items = [
    [64, 89, 65, 95],
    [76, 66, 74, 87, 70, 56, 51, 66],
    [91, 60, 63],
    [92, 61, 79, 97, 79],
    [93, 54],
    [60, 79, 92, 69, 88, 82, 70],
    [64, 57, 73, 89, 55, 53],
    [62]
]

for i in range(8):
    for thing in monkey_items[i]:
        monkeys[i].items.put(thing)

# num_rounds = 20
# for z in range(num_rounds):
#     print(z)
#     for i in range(4):
#         while test_monkeys[i].items.empty() == False:
#             next_item = test_monkeys[i].items.get()
#             test_monkeys[i].num_inspects += 1
#             item_val = test_monkey_op(i, next_item)

#             if test_monkey_test(i, item_val) == 1:
#                 test_monkeys[test_monkeys[i].throw_t_id].items.put(item_val)
#             else:
#                 test_monkeys[test_monkeys[i].throw_f_id].items.put(item_val)     

# inspects = []
# for i in range(4):
#     inspects.append(test_monkeys[i].num_inspects)

# inspects.sort()
# print(inspects)



num_rounds = 10000
for z in range(num_rounds):
    if(z % 500 == 0):
        print(f'round {z + 1}')
    #cycle through all monkeys
    for i in range(8):
        #print(f'monkey {i}')
        while monkeys[i].items.empty() == False:
            next_item = monkeys[i].items.get()
            monkeys[i].num_inspects += 1
            item_val = monkeys[i].operation(next_item, monkeys[i].operand)
            #item_val = monkey_op(i, next_item)
            if item_val > 9699690:
                item_val = item_val % 9699690

            if monkey_test(i, item_val) == 1:
                monkeys[monkeys[i].throw_t_id].items.put(item_val)
            else:
                monkeys[monkeys[i].throw_f_id].items.put(item_val)     

inspects = []
for i in range(8):
    inspects.append(monkeys[i].num_inspects)

inspects.sort()
print(inspects)
print(inspects[-1] * inspects[-2])