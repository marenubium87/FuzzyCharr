#Handles the main simulation, number crunching, plotting,
#and matplotlib interfaces.

import random as rand
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math

from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import PySimpleGUI as sg
matplotlib.use('TkAgg')

version = '0.9.0'

class Simulator:
    #dictionary where keys are types of dice and vals are number of that die
    #e.g. 6 : 2 would mean 2d6
    dice = {}

    #available modes {SUM, SUCC}
    mode = 'SUM'
    #threshold for a die roll to be counted as a success
    succ_threshold = 0

    #available modes {'Do not drop', 'Drop lowest', 'Drop highest'}
    mode_drop = 'Do not drop'
    #number of dice to drop
    num_drops = 0

    reroll_threshold = 0

    num_trials = 1000
    #percent threshold (0.05 means 0.05%, not 5%) to omit outcome values
    cutoff_threshold = 0.2

    #the confidence level selected for the simulation
    CI_level = 90

    #dictionary storing outcomes as keys and frequencies as values for
    #any given simulation run
    freq = {}

    #for plot use
    x_sorted = []
    y_sorted = []

    #plot figure
    fig = None

    @classmethod
    def modify_dice(cls, d, o, n=1):
        '''
        Modifies simulator's dice dictionary entry of die type d
        with string operation o, and number n.  If d doesn't exist 
        in the dictionary it will be created.
        
        Acceptable values for o are as follows:
        +:  adds one die of the type to the die pool
        -:  subtracts one die of the type from the die pool
        =:  sets the number of dice of type to n

        '''
        if o == '+':
            if d in cls.dice:
                cls.dice[d] += n
            else:
                cls.dice[d] = n
        if o == '-':
            if d in cls.dice:
                cls.dice[d] -= n
            else:
                #if key not in dict then subtracting dice does nothing
                pass
        if o == '=':
            cls.dice[d] = n

        #final check, prunes any invalid entries to make sure dictionary
        #is in a valid state
        to_delete = []
        for die_type in cls.dice:
            if int(cls.dice[die_type]) < 1:
                to_delete.append(die_type)

        for die_type in to_delete:
            cls.dice.pop(die_type)

        #checking output, can safely comment out in prod code
        print(cls.dice)

    @classmethod
    def clear_die_pool(cls):
        '''
        Helper fcn; empties the dice dictionary and resets params relevant
        to dice pool (drops and success threshold)
        '''
        cls.dice.clear()
        cls.succ_threshold = 0
        cls.num_drops = 0
        cls.reroll_threshold = 0
        
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

    @classmethod
    def drop_dice(cls, roll):
        '''
        Helper fcn: drops highest or lowest dice from previous roll,
        then returns
        '''
        if cls.mode_drop != 'Do not drop':
            for i in range(cls.num_drops):
                if cls.mode_drop == 'Drop lowest':
                    roll.remove(min(roll))
                elif cls.mode_drop == 'Drop highest':
                    roll.remove(max(roll))
        return roll

    @classmethod
    def calculate_MoE(cls):
        '''
        Helper function.  Calculates the margin of error for each outcome
        using the expected CI (conservative estimate using 
        binomial dist, p=0.5) based on number of trials.
        '''
        #z-star critical values for various confidence intervals
        z_star_dict = {70:1.036, 80:1.281, 90:1.645, 95:1.96,
            97:2.17, 99:2.576}

        moe = math.sqrt(0.5 * 0.5 / cls.num_trials)
        moe = moe * 100 * z_star_dict[cls.CI_level]
        
        return round(moe, 1)

    @classmethod
    def generate_dice_str(cls):
        '''
        Helper function.  Generates a string from the current dice pool
        in 1d2+3d4 format.
        '''
        dice_str = ''
        for die_type in cls.dice:
            dice_str += f'+{cls.dice[die_type]}d{die_type}'
        #removes leading '+'
        return dice_str[1:]

    @classmethod
    def perform_roll(cls):
        '''
        Performs a single roll using dice dictionary, drops num_drops dice, 
        then returns a list of remaining dice rolls in this particular roll.
        '''
        single_roll = []
        new_result = 0

        #performs roll and rerolls dice until above reroll threshold
        for type in cls.dice:
            for die in range(cls.dice[type]):
                while True:
                    # +1 since dice values are in form [1, n], not [0, n)
                    new_result = rand.randrange(1, type + 1)
                    #strict inequality as reroll treshold defined as the highest
                    #value that needs to be rerolled
                    if new_result > cls.reroll_threshold:
                        break
                single_roll.append(new_result)

        #drops appropriate number of dice
        single_roll = cls.drop_dice(single_roll)

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

        #for debugging purposes, can delete
        #print(cls.freq)

    @classmethod
    def generate_plot(cls):
        '''
        Sets up matplotlib plot from freq dictionary in class
        and returns figure of plot.
        '''
        #grid spacing parameter
        gs = 2.5

        #closes previous figures, if any
        plt.close('all')

        #figure width and height in inches
        fig_w = 9
        fig_h = 5
        fig_dpi = 180

        #generates sorted x and y lists
        cls.x_sorted.clear()
        cls.y_sorted.clear()
        for outcome in sorted(cls.freq.keys()):
            cls.x_sorted.append(outcome)
            cls.y_sorted.append(cls.freq[outcome])

        #init figure and axes
        fig, ax = plt.subplots()

        #sets figure width and height in inches
        fig.set_size_inches(fig_w, fig_h)
        p1 = ax.bar(cls.x_sorted, cls.y_sorted)

        #creates x-index from smallest to largest outcome, and sets x-ticks to that
        ind_x = np.arange(cls.x_sorted[0], cls.x_sorted[-1] + 1, 1)
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

        #Title string concatenation
        mode_str_dict = {'SUM':'Sum', 'SUCC':'Successes'}
        dice_str = cls.generate_dice_str()
        
        succ_thresh_str = ''
        if cls.succ_threshold > 0:
            succ_thresh_str = f'(Threshold: >= {cls.succ_threshold})'
        
        reroll_str = ''
        if cls.reroll_threshold > 0:
            reroll_str = (f', Reroll {cls.reroll_threshold}s'
                f' and below')

        drop_str = ''
        if cls.mode_drop != 'Do not drop':
            drop_str = f', {cls.mode_drop} {cls.num_drops}'
        
        trials_str = f', {cls.num_trials} trials'

        plt.title(f'Probability Dist. for {mode_str_dict[cls.mode]}'
            f'{succ_thresh_str} of {dice_str}{reroll_str}'
            f'{drop_str}{trials_str}')

        plt.tight_layout()

        #for testing purposes, can comment out
        #plt.show()
        return plt.gcf()
        
    @classmethod
    def simulation_wrapper(cls):
        '''
        Runs entire simulation and returns a figure of the plot.
        '''
        cls.perform_sim()
        cls.decimalize_outcomes()
        return cls.generate_plot()

#matplotlib helper code
def draw_figure(canvas, figure):
    figure_canvas_agg = FigureCanvasTkAgg(figure, canvas)
    figure_canvas_agg.draw()
    figure_canvas_agg.get_tk_widget().pack(side='top', fill='both', expand=1)
    return figure_canvas_agg