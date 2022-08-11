from dataclasses import dataclass
import random as rand
import matplotlib.pyplot as plt
import numpy as np

#create number and type of dice as tuples in a list

rand.seed()

num_trials = 80000
truncate_threshold = 0.05
num_drops = 2

die_list = [(4, 3)]


def perform_roll(die_list, num_drops):
    '''
    Performs a single roll of all dice specified in die_list
    Drops num_drops lowest dice, then returns a list of remaining
    dice rolls in the particular roll.
    '''
    single_roll = []
    #die group in form {number of, type}
    for die_group in die_list:
        #throws die_group[0] number of dice
        for die in range(die_group[0]):
            single_roll.append(rand.randrange(1, die_group[1] + 1))
    
    #drops lowest num_drops dice
    for i in range(num_drops):
        single_roll.remove(min(single_roll))

    return single_roll

def perform_sim(die_list, trials, num_drops):
    single_roll = []
    sum_results_list = []
    for roll in range(1, trials + 1):
        single_roll = perform_roll(die_list, num_drops)
        sum_results_list.append(sum(single_roll))
    return sum_results_list

def combine_data(results_list):
    freq_dict = {}
    for value in results_list:
        if value in freq_dict:
            freq_dict[value] += 1
        else:
            freq_dict[value] = 1

    return freq_dict

def decimalize_outcomes(d, n, threshold=0):
    '''
    Converts dictionary d with keys as outcomes such that values
    are divided by n number of trials, so that outcomes are now probabilities
    instead of counts.

    Also removes outcomes (keys) from dict d if their associated probability
    value falls below threshold.
    '''
    to_delete = []
    for outcome in d:
        d[outcome] = d[outcome] / n * 100
        if d[outcome] < threshold:
            to_delete.append(outcome)

    for value in to_delete:
        d.pop(value)


freq_dict = combine_data(perform_sim(die_list, num_trials, num_drops))
decimalize_outcomes(freq_dict, num_trials, truncate_threshold)

x_sorted = []
y_sorted = []

for key in sorted(freq_dict.keys()):
    x_sorted.append(key)
    y_sorted.append(freq_dict[key])

print(x_sorted)
print(y_sorted)


plt.bar(x_sorted, y_sorted)

plt.xticks(x_sorted)
plt.show()