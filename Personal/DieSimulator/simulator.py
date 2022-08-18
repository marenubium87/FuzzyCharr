from dataclasses import dataclass
from os import name
import random as rand
import matplotlib.pyplot as plt
import numpy as np
import math

def perform_roll(d, n):
    '''
    d: dice, specified in list of tuples in form (num in group, type of group)

    example: [(6,20), (4, 8)] is 6d20+4d8

    n: number of (lowest) dice to drop

    Performs a single roll of d, drops n lowest dice, then returns a list of 
    remaining dice rolls in this particular roll.
    '''
    single_roll = []
    #die group in form {number of, type}
    for group in d:
        #rolls group[0] number of dice of type group[1]
        for die in range(group[0]):
            # +1 since dice are in form [1, n], not [0, n)
            single_roll.append(rand.randrange(1, group[1] + 1))

    #drops lowest n dice
    for i in range(n):
        single_roll.remove(min(single_roll))

    return single_roll

def perform_sim(d, t, n):
    '''
    d: dice, specified in list of tuples in form (num in group, type of group)

    t: number of trials

    n: number of (lowest) dice to drop 

    Performs an entire simulation of t trials for die list d
    and number of drops n, and returns a list of the total (sum)
    of each trial in simulation.
    '''
    rand.seed()
    single_roll = []
    sum_results_list = []

    #using this range instead of (0, t) for accurate simulation count
    for roll in range(1, t + 1):
        single_roll = perform_roll(d, n)
        sum_results_list.append(sum(single_roll))
    return sum_results_list

def tally_results(r):
    '''
    r: a list of results (outcomes) from performing a simulation.

    Tallies up results list r into a dictionary of unique outcomes
    of the form (outcome : frequency) for each (k : v) pair
    '''
    freq_dict = {}
    for outcome in r:
        if outcome in freq_dict:
            freq_dict[outcome] += 1
        else:
            #create entry outcome not yet recorded in dictionary
            freq_dict[outcome] = 1
    return freq_dict

def decimalize_outcomes(fd, t, ct=0):
    '''
    fd:  Frequency dictionary of outcomes, usu. output by tally_results fcn

    t:  Number of trials in simulation

    ct:  Cutoff threshold as a percent

    Modifies frequency dictionary fd such that values corresponding to outcomes
    are now probabilities (percents) instead of counts.  Also removes outcomes
    from dictionary if their associated probability is below cutoff threshold ct.
    '''
    to_delete = []
    for outcome in fd:
        #rounds to 6 dec. places to avoid floating point inaccuracies in output.
        fd[outcome] = round(fd[outcome] / t * 100, 6)
        if fd[outcome] < ct:
            to_delete.append(outcome)

    for value in to_delete:
        fd.pop(value)

    return fd

def generate_plot(fd):

    #generates sorted x and y lists
    x_sorted = []
    y_sorted = []
    for outcome in sorted(fd.keys()):
        x_sorted.append(outcome)
        y_sorted.append(fd[outcome])

    fig, ax = plt.subplots()
    p1 = ax.bar(x_sorted, y_sorted)

    #creates x-index from smallest to largest outcome, and sets x-ticks to that
    ind_x = np.arange(x_sorted[0], x_sorted[-1] + 1, 1)
    ax.set_xticks(ind_x, ind_x)
    ax.set_xlabel('Outcomes')

    #grid spacing parameter here
    gs = 4
    #uses above grid spacing to set up y-axis
    y_max = max(fd.values())
    y_max = math.ceil(y_max / gs) * gs
    ind_y = np.arange(0, y_max + 1, gs)
    ax.set_yticks(ind_y, ind_y)

    ax.set_ylabel('Probability (%)')
    #plots horizontal (y) grid lines and draws them under the bars
    ax.set_axisbelow(True)
    plt.grid(axis = 'y', linestyle='dashed')

    #shows labels above each bar indicating percentages
    ax.bar_label(p1, fmt='%.1f')
    plt.show()

num_trials = 80000
#percent threshold (0.05 means 0.05%, not 5%) to omit outcome values
cutoff_threshold = 0.05
#number of lowest dice to discard
num_drops = 2
die_list = [(4, 6)]
freq_dict = tally_results(perform_sim(die_list, num_trials, num_drops))
freq_dict = decimalize_outcomes(freq_dict, num_trials, cutoff_threshold)
generate_plot(freq_dict)