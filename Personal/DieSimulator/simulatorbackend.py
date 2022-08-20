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
    #dictionary where keys are types of dice and vals are number of that die
    #e.g. 6 : 2 would mean 2d6
    dice = { 6 : 4}
    num_trials = 50000
    #number of lowest dice to discard
    num_drops = 1
    #percent threshold (0.05 means 0.05%, not 5%) to omit outcome values
    cutoff_threshold = 0.1
    #dictionary storing outcomes as keys and frequencies as values for
    #any given simulation run
    freq = {}

    @classmethod
    def perform_roll(cls):
        '''
        Performs a single roll using dice dictionary, drops num_drops dice, 
        then returns a list of remaining dice rolls in this particular roll.
        '''
        single_roll = []
        for type in cls.dice:
            for die in range(cls.dice[type]):
                # +1 since dice values are in form [1, n], not [0, n)
                single_roll.append(rand.randrange(1, type + 1))

        #drops lowest num_drops dice
        for i in range(cls.num_drops):
            single_roll.remove(min(single_roll))

        return single_roll

    @classmethod
    def perform_sim(cls):
        '''
        Performs a simulation run using the die pool and number of trials
        loaded in the Simulator class, saving the result to the
        frequency dictionary.
        '''
        rand.seed()
        #resets frequency dictionary from any past simulation run(s)
        cls.freq.clear()
        single_roll = []

        #using this range instead of (0, t) for accurate simulation count
        for roll in range(1, cls.num_trials + 1):
            single_roll = cls.perform_roll()
            outcome = sum(single_roll) 
            if outcome in cls.freq:
                cls.freq[outcome] += 1
            else:
                #create entry outcome not yet recorded in dictionary
                cls.freq[outcome] = 1

    @classmethod
    def decimalize_outcomes(cls):
        '''
        Modifies frequency dictionary such that values corresponding to outcomes
        are now probabilities (percents) instead of counts.  Also removes outcomes
        from dictionary if their associated probability is below cutoff threshold.
        '''
        to_delete = []
        for outcome in cls.freq:
            #rounds to 6 dec. places to avoid floating point inaccuracies in output.
            cls.freq[outcome] = round(cls.freq[outcome] / 
                cls.num_trials * 100, 6)
            if cls.freq[outcome] < cls.cutoff_threshold:
                to_delete.append(outcome)

        for value in to_delete:
            cls.freq.pop(value)

    @classmethod
    def generate_plot(cls):
        '''
        Sets up matplotlib plot from freq dictionary in class
        and returns figure of plot.
        '''
        #grid spacing parameter
        gs = 4

        #generates sorted x and y lists
        x_sorted = []
        y_sorted = []
        for outcome in sorted(cls.freq.keys()):
            x_sorted.append(outcome)
            y_sorted.append(cls.freq[outcome])

        fig, ax = plt.subplots()
        p1 = ax.bar(x_sorted, y_sorted)

        #creates x-index from smallest to largest outcome, and sets x-ticks to that
        ind_x = np.arange(x_sorted[0], x_sorted[-1] + 1, 1)
        ax.set_xticks(ind_x, ind_x)
        ax.set_xlabel('Outcome')

        #uses above grid spacing to set up y-axis
        y_max = max(cls.freq.values())
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
        '''
        Runs entire simulation and generates plot.
        '''
        cls.perform_sim()
        cls.decimalize_outcomes()
        return cls.generate_plot()

    @classmethod
    def get_total_dice(cls):
        '''
        Helper fcn: returns total dice currently in pool.
        '''
        result = 0
        #dice pool is not empty
        if cls.dice:
            result = sum(cls.dice.values())
        return result

#matplotlib helper code
def draw_figure(canvas, figure):
    figure_canvas_agg = FigureCanvasTkAgg(figure, canvas)
    figure_canvas_agg.draw()
    figure_canvas_agg.get_tk_widget().pack(side='top', fill='both', expand=1)
    return figure_canvas_agg