import random as rand

#create number and type of dice as tuples in a list

rand.seed(5)

user_die_entry = input("Add dice: ").split('+')
die_list = []
for group in user_die_entry:
    die_tuple = tuple(group.split('d'))
    die_tuple = tuple((int(x) for x in die_tuple))
    die_list.append(die_tuple)

#expects a list of tuples listing number of and type of dice
#e.g. [{6, 12}, {3, 4}] is 6d12 + 3d4
#returns a list of int die rolls
def perform_roll(die_list):
    print("Performing roll...")
    results_list = []
    for die_group in die_list:
        for die in range(die_group[0]):
            results_list.append(rand.randrange(1, die_group[1]))
    print(results_list)
    return results_list

perform_roll(die_list)