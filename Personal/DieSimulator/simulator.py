import random as rand
import matplotlib.pyplot as plt
import numpy as np

#create number and type of dice as tuples in a list

rand.seed()

# user_die_entry = input("Add dice: ").split('+')
# die_list = []
# for group in user_die_entry:
#     die_tuple = tuple(group.split('d'))
#     die_tuple = tuple((int(x) for x in die_tuple))
#     die_list.append(die_tuple)

#expects a list of tuples listing number of and type of dice
#e.g. [(6, 12), (3, 4)] is 6d12 + 3d4
#returns a list of int die rolls

num_trials = 50000
die_list = [(6, 6)]

def perform_roll(die_list):
    die_results_list = []
    for die_group in die_list:
        for die in range(die_group[0]):
            die_results_list.append(rand.randrange(1, die_group[1] + 1))
    return die_results_list

def perform_sim(die_list, trials):
    die_results_list = []
    sum_results_list = []
    for roll in range(1, trials + 1):
        die_results_list = perform_roll(die_list)
        sum_results_list.append(sum(die_results_list))
    return sum_results_list

def combine_data(results_list):
    freq_dict = {}
    for value in results_list:
        if value in freq_dict:
            freq_dict[value] += 1
        else:
            freq_dict[value] = 1

    return freq_dict


combined_data = combine_data(perform_sim(die_list, num_trials))
x_sorted = []
y_sorted = []

for key in sorted(combined_data.keys()):
    x_sorted.append(key)
    y_sorted.append(combined_data[key])

print(x_sorted)
print(y_sorted)


plt.bar(x_sorted, y_sorted)

plt.xticks(x_sorted)
plt.show()