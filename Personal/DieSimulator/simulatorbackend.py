from dataclasses import dataclass
from os import name
import random as rand
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math

from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import PySimpleGUI as sg
matplotlib.use('TkAgg')

class Simulator:
    #in form [(num dice in subgroup, type of subgroup)]
    #e.g. [(2,6), (3,20)] is 2d6 + 3d20
    die_list = [(2, 6)]
    num_trials = 3
    #number of lowest dice to discard
    num_drops = 0
    #percent threshold (0.05 means 0.05%, not 5%) to omit outcome values
    cutoff_threshold = 0.1
    #stores outcomes and frequencies on any given simulation run
    freq_dict = {}

    @classmethod
    def perform_roll(cls):
        '''
        d: dice, specified in list of tuples in form (num in group, type of group)

        example: [(6,20), (4, 8)] is 6d20+4d8

        n: number of (lowest) dice to drop

        Performs a single roll of d, drops n lowest dice, then returns a list of 
        remaining dice rolls in this particular roll.
        '''
        single_roll = []
        #die group in form {number of, type}
        for group in cls.die_list:
            #rolls group[0] number of dice of type group[1]
            for die in range(group[0]):
                # +1 since dice are in form [1, n], not [0, n)
                single_roll.append(rand.randrange(1, group[1] + 1))

        #drops lowest n dice
        for i in range(cls.num_drops):
            single_roll.remove(min(single_roll))

        return single_roll

    @classmethod
    def perform_sim(cls):
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
        for roll in range(1, cls.num_trials + 1):
            single_roll = cls.perform_roll()
            sum_results_list.append(sum(single_roll))
        return sum_results_list

    @classmethod
    def tally_results(cls, r):
        '''
        r: a list of results (outcomes) from performing a simulation.

        Tallies up results list r into a dictionary of unique outcomes
        of the form (outcome : frequency) for each (k : v) pair
        '''
        cls.freq_dict.clear()

        for outcome in r:
            if outcome in cls.freq_dict:
                cls.freq_dict[outcome] += 1
            else:
                #create entry outcome not yet recorded in dictionary
                cls.freq_dict[outcome] = 1

    @classmethod
    def decimalize_outcomes(cls):
        '''
        fd:  Frequency dictionary of outcomes, usu. output by tally_results fcn

        t:  Number of trials in simulation

        ct:  Cutoff threshold as a percent

        Modifies frequency dictionary fd such that values corresponding to outcomes
        are now probabilities (percents) instead of counts.  Also removes outcomes
        from dictionary if their associated probability is below cutoff threshold ct.
        '''
        to_delete = []
        for outcome in cls.freq_dict:
            #rounds to 6 dec. places to avoid floating point inaccuracies in output.
            cls.freq_dict[outcome] = round(cls.freq_dict[outcome] / 
                cls.num_trials * 100, 6)
            if cls.freq_dict[outcome] < cls.cutoff_threshold:
                to_delete.append(outcome)

        for value in to_delete:
            cls.freq_dict.pop(value)

    @classmethod
    def generate_plot(cls):
        #grid spacing parameter
        gs = 4

        #generates sorted x and y lists
        x_sorted = []
        y_sorted = []
        for outcome in sorted(cls.freq_dict.keys()):
            x_sorted.append(outcome)
            y_sorted.append(cls.freq_dict[outcome])

        fig, ax = plt.subplots()
        p1 = ax.bar(x_sorted, y_sorted)

        #creates x-index from smallest to largest outcome, and sets x-ticks to that
        ind_x = np.arange(x_sorted[0], x_sorted[-1] + 1, 1)
        ax.set_xticks(ind_x, ind_x)
        ax.set_xlabel('Outcome')

        #uses above grid spacing to set up y-axis
        y_max = max(cls.freq_dict.values())
        y_max = math.ceil(y_max / gs) * gs
        ind_y = np.arange(0, y_max + 1, gs)
        ax.set_yticks(ind_y, ind_y)

        ax.set_ylabel('Probability (%)')
        #plots horizontal (y) grid lines and draws them under the bars
        ax.set_axisbelow(True)
        plt.grid(axis = 'y', linestyle='dashed')

        #shows labels above each bar indicating percentages
        ax.bar_label(p1, fmt='%.1f')
        return plt.gcf()
        
    @classmethod
    def simulation_wrapper(cls):
        cls.tally_results(cls.perform_sim())
        cls.decimalize_outcomes()
        cls.generate_plot()

#matplotlib helper code
def draw_figure(canvas, figure):
    figure_canvas_agg = FigureCanvasTkAgg(figure, canvas)
    figure_canvas_agg.draw()
    figure_canvas_agg.get_tk_widget().pack(side='top', fill='both', expand=1)
    return figure_canvas_agg

Simulator.simulation_wrapper()