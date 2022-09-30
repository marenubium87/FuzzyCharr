#Plotter.  Handles everything graph related - labels, axes...
#  also generates plot figure.

from sqlite3 import DateFromTicks
import sim_config as cfg

import simulator
sim = simulator.Simulator

import math
import numpy as np

import matplotlib
import matplotlib.pyplot as plt
import matplotlib.ticker as plttick
from matplotlib.ticker import MultipleLocator, FormatStrFormatter
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
matplotlib.use('TkAgg')

class Plotter:
    #Sorted x and y lists to generate histogram
    x_sorted = []
    y_sorted = []

    #Plot figure object
    fig = None

    #Interface for TKinter fig adaptor
    fig_agg = None

    #Default label spacing for historgram bars
    #  see config for more info
    plt_lbl_spacing = cfg.PLT_LBL_SPACING

    #Step size for cumulative probability distribution thresholds
    #  for example, step size of 25 would result in cumulative probability
    #  values reported at 25, 50, and 75 percent
    plt_cum_prob_step = 25

    #Statistical variables
    xbar = 0
    sx = 0

    #Labels
    lbl_data = []
    lbl_quartiles = []

    @classmethod
    def generate_sorted_lists(cls):
        '''
        Splits Simulator's freq dictionary into two lists for matplotlib,
        sorted by outcome of roll:
        - x: outcome
        - y: frequency (in percent of total trials)
        '''
        cls.x_sorted.clear()
        cls.y_sorted.clear()

        for outcome in sorted(sim.freq.keys()):
            cls.x_sorted.append(outcome)
            cls.y_sorted.append(sim.freq[outcome])

    @classmethod
    def calc_xbar(cls, freq):
        '''
        Calculates x-bar for the distribution using frequency dict
        Uses standard Σ x * p(x) formula; rounds to places defined in cfg
        Must be run before calc_sx()
        '''
        weighted_sum = 0
        for outcome in freq.keys():
            weighted_sum += outcome * freq[outcome] / 100
        cls.xbar = round(weighted_sum, cfg.ROUNDING_PREC)

    @classmethod
    def calc_sx(cls, freq, xbar):
        '''
        Calculates the standard deviation of the distribution using frequency
        dict and rounds to places defined in cfg
        Uses variance shortcut equation; specifically:
        s^2 = Σ [x^2 * p(x)] - x-bar^2
        Must call after calc_xbar(); depends on correct value of x-bar in class
        '''
        #for debugging, can delete!
        print(freq)

        weighted_sq_sum = 0
        for outcome in freq.keys():
            weighted_sq_sum += (outcome ** 2) * freq[outcome] / 100

        weighted_sq_sum -= xbar ** 2
        cls.sx = round(math.sqrt(weighted_sq_sum), cfg.ROUNDING_PREC)

    @classmethod
    def calc_quartiles(cls, freq):
        '''
        Generates a list of outcome values that correspond to the
        location of the three quartiles (Q1, M, Q3) of the distribution
        '''

        #List that will store cumulative probability less than or equal
        #  to a given outcome as tuples in form (outcome, probability)
        cum_prob = [(-1, 0)]

        #Generate CDF
        for outcome in sorted(freq.keys()):
            cum_prob.append((outcome, 
                round(freq[outcome] + cum_prob[-1][1], cfg.ROUNDING_PREC)))

        #Step size to generate CDF thresholds; for quartiles, use 25
        #  i.e. [25, 50, 75]
        step = 25
        cum_threshold_current = step
        #The outcomes that correspond to CDF values exceeding each step
        #  as described above
        new_quartiles = []

        #Build quartiles list
        i = 0
        while cum_threshold_current < 100 and i < len(cum_prob):
            if cum_prob[i][1] > cum_threshold_current:
                new_quartiles.append(cum_prob[i][0])
                cum_threshold_current += step
            i += 1

        #These two lines is for debugging purposes, can safely remove
        print(cum_prob)
        print(new_quartiles)

        cls.quartiles = new_quartiles

    @classmethod
    def generate_x_axis(cls, ax):
        '''
        Sets up labels and settings for x-axis, using the
        matplotlib ax axis object and the calculated label spacing
        '''
        #Default number of x-labels
        num_x_labels = cfg.PLT_X_AX_LABELS_POP

        #If largest outcome value is greater than scientific threshold,
        #  set x-labels to scientific notation, and
        #  prune number of labels by additional factor of two for spacing
        if cls.x_sorted[-1] > cfg.PLT_X_AX_SCI_THRESH:
            num_x_labels = int(num_x_labels / 2)
            ax.xaxis.set_major_formatter(FormatStrFormatter('%.1e'))

        #Creates x-index from smallest to largest values, and sets x-label
        #  spacing based on either pre-defined label spacing, or override
        #  with explicit number of labels
        ind_x = np.arange(
            cls.x_sorted[0], cls.x_sorted[-1] + 1, 
            max(int((cls.x_sorted[-1] - cls.x_sorted[0]) / num_x_labels), 
                cls.plt_lbl_spacing)
        )

        ax.set_xlabel('Outcome')
        ax.set_xticks(ind_x, ind_x)

    @staticmethod
    #TODO:  HAVE THE CUTOFFS BE PASSED IN PARAMS
    def calc_y_dim():
        '''
        Returns y_dim, the y-dimension of the graph in terms of a probability %
        This is *NOT* equal to the highest data bar on the graph, as we usually
        want to leave some room at the top.  This function dynamically
        calculates an acceptable y-dimension based on the highest data value
        (outcome frequency) stored in the simulator.
        Necessary for: generate_y_axis()
        '''
        #The y_dimension of the graph, which is equivalent to the highest value
        #  displayed on the graph window itself (henceforth colloquially
        #  'top of graph'), since bottom value necessarily must be zero
        y_dim = 0
        y_data_max = max(sim.freq.values())

        #This parameter roughly represents how high, at minimum,
        #  the top of the graph should be above the highest data bar,
        #  as a proportion (1.16 = 116%)
        h = 1.16

        #Mode 1
        #For data with peak above this value, make top of graph
        #  divisible by 20, possible values starting with 40 
        #  and ending with 120
        if y_data_max > 33:
            y_dim = int(math.ceil(y_data_max * h / 10))
            if y_dim % 2 == 1:
                y_dim += 1
            y_dim *= 10

        #Mode 2
        #For data with peak above this value but less than previous value,
        #  have top of graph satisfy the minimum height requirement above,
        #  but also be divisible by the gridline number value, for neat
        #  (integer) values on y-axis
        elif y_data_max > 9:
            y_dim = (math.ceil(y_data_max * h / cfg.PLT_Y_GRIDLINES) 
                 * cfg.PLT_Y_GRIDLINES)

        #Mode 3
        #For data with peak above this value but less than previous value,
        #  peaks are now too small to insist on integer divisibility for
        #  gridlines; but we insist top of graph is still integer value
        elif y_data_max > 0.7:
            y_dim = math.ceil(y_data_max * h)

        #For data with peaks below previous value,
        #  peaks are now too small to even insist on top of graph 
        #  being integer values, so simply calculate a reasonable value for
        #  top of graph
        else:
            y_dim = y_data_max * h

        return y_dim

    @classmethod
    def generate_y_axis(cls, ax):
        '''
        Sets up labels and settings for y-axis, using the
        matplotlib ax axis object
        Requires: calc_y_dim()
        '''
        #Y-axis dimension bounds
        y_dim = cls.calc_y_dim()
        ax.set_ylim([0, y_dim])

        #Draw number of gridlines as defined by config file at equally spaced
        #  intervals; minor gridlines at half the distance between majors
        ax.yaxis.set_major_locator(
            MultipleLocator(y_dim / cfg.PLT_Y_GRIDLINES))
        ax.yaxis.set_minor_locator(
            MultipleLocator(y_dim / cfg.PLT_Y_GRIDLINES / 2))
        #In this context color is a string decimal btwn
        #  0 (black) and 1 (white)
        ax.grid(axis='y', which='major', linewidth=0.7, color='0.7', 
            linestyle='--')
        ax.grid(axis='y', which='minor', linewidth=0.5, color='0.3', 
            linestyle=':')

        #For datasets with small peaks, have y-axis labels contain
        #  more decimal points
        y_round_prec = 0
        if max(sim.freq.values()) <= 9:
            y_round_prec += 2

        #Sets up y-axis formatting, without percent symbols 
        ax.yaxis.set_major_formatter(
            plttick.PercentFormatter(decimals=y_round_prec, symbol=''))

        #Draws gridlines underneath data bars
        ax.set_axisbelow(True)
        ax.set_ylabel('Probability (%)')

    @classmethod
    def calc_lbl_spacing(cls):
        '''
        Determines whether to use alternate label spacing rules, and
        determines an appropriate label spacing
        '''
        #Resets plot spacing; necessary for running a simulation not requiring
        #  alternative label spacing, after running a simulation that did
        cls.plt_lbl_spacing = 1

        #Alternative label spacing threshold calculation, if applicable.
        if max(sim.freq.keys()) - min(sim.freq.keys()) > cfg.PLT_LBL_SPACING_THRESH:
            cls.plt_lbl_spacing = math.ceil((
                max(sim.freq.keys()) - min(sim.freq.keys())) 
                / cfg.PLT_LBL_SPACING_THRESH
            )

    @classmethod
    def generate_lbl_list(cls):
        '''
        Sets up labels for the actual data bars, and based on class
        label spacing parameter
        '''
        cls.lbl_data = [str(round(y, 1)) for y in cls.y_sorted]

        #Eliminates values from being labeled according to label spacing param
        for i in range(0, len(cls.lbl_data)):
            if i % cls.plt_lbl_spacing != 0:
                cls.lbl_data[i] = ''
        
    @classmethod
    def generate_quartile_list(cls):
        '''
        Generates a second list for the quartile labels
        '''
        quartile_names = ['Q1', 'M', 'Q3']
        #Merges quartile values and names into dict
        quartile_dict = {cls.quartiles[i]: quartile_names[i] 
            for i in range(len(cls.quartiles))}

        #Clear labels from previous run; not doing so was creating problems
        cls.lbl_quartiles = []
        for i in range(0, len(cls.x_sorted)):
            if cls.x_sorted[i] in quartile_dict:
                #Adds quartile labels in correct location
                cls.lbl_quartiles.append(quartile_dict[cls.x_sorted[i]])
                #Also clears same location from data labels, so that figures
                #  don't overlap
                cls.lbl_data[i] = ''
            else:
                cls.lbl_quartiles.append('')           

    @classmethod
    def generate_lbls_highlights(cls, graph, ax):
        '''
        Wrapper handling labels and highlighting tasks on the bar graph object
        '''
        #Update label spacing first, then generate label lists
        cls.calc_lbl_spacing()
        cls.generate_lbl_list()
        cls.generate_quartile_list()

        #Place data labels
        #Padding is distance above the relevant bar to place labels
        ax.bar_label(graph, fmt='%.1f', labels=cls.lbl_data, padding=8)
        
        #Colors for quartile labels and bars
        #TODO:  make these colors a little lighter
        solid_color = '#0bb012'     #green
        lbl_color = '#003b03'       #dark green
        #Place quartile labels
        ax.bar_label(graph, labels=cls.lbl_quartiles, padding=8,
            color=lbl_color, fontweight='heavy')

        #Highlight quartile bars
        for i in range(0, len(cls.lbl_quartiles)):
            if cls.lbl_quartiles[i] != '':
                graph[i].set(color=solid_color, edgecolor=lbl_color)

    @classmethod
    def generate_annotations(cls, ax):
        #Draw vertical line for x-bar location
        plt.vlines(x=cls.xbar, ymin = ax.get_ylim()[1] * 0.85,
            ymax = ax.get_ylim()[1] * 0.97, linewidths=1.7, 
            color='#d6c7ff'     #lavender
        )
        #Note value of x-bar and std dev nearby
        plt.annotate(f'x-bar = {round(cls.xbar, 2)}\n'
            f's.d. = {round(cls.sx, 2)}',
            xy=(cls.xbar, ax.get_ylim()[1] * 0.94),
            #This calculates an offset from the vertical line to determine
            #  where to put the text
            xytext=(cls.xbar + (ax.get_xlim()[1] - ax.get_xlim()[0]) * 0.13, 
                ax.get_ylim()[1] * 0.90),
            ha='right',
            color='#3b1d8f'     #dark violet
        )

    @staticmethod
    def generate_title():
        '''
        Reads parameters from Simulator to dynamically generate title string
        '''
        mode_str = sim.mode

        dice_str = sim.generate_dice_str_from_pool()
        
        succ_thresh_str = ''
        #Doesn't make sense to print out success threshold if it's equal to 1
        #  (those are auto-successes)
        if sim.succ_threshold > 1:
            succ_thresh_str = f' (>= {sim.succ_threshold})'
        
        reroll_str = ''
        #Doesn't make sense to print out reroll threshold is it's equal to 0
        #  (there will be no rerolls)
        if sim.reroll_threshold > 0:
            reroll_str = (f', Reroll <= {sim.reroll_threshold}')

        drop_str = ''
        #Doesn't make sense to print out number of drops if it's equal to 0
        #  (since we aren't dropping anything)
        if sim.num_drops > 0:
            drop_str = f', {sim.mode_drop} {sim.num_drops}'
        
        trials_str = f', {sim.num_trials} Trials'

        plt.title(f'{mode_str}'
            f'{succ_thresh_str} of {dice_str}{reroll_str}'
            f'{drop_str}{trials_str}')

    @classmethod
    def generate_plot(cls):
        '''
        Sets up matplotlib plot from freq dictionary in class
        and returns figure of plot.
        Requires:  all class functions above.
        '''
        #If no usable data, do not plot
        if not sim.freq:
            return
        #Closes previous figures, if any
        plt.close('all')

        #Create sorted lists for matplotlib from sim's freq dictionary
        cls.generate_sorted_lists()

        #Calculate statistical parameters
        cls.calc_xbar(sim.freq)
        cls.calc_sx(sim.freq, cls.xbar)
        cls.calc_quartiles(sim.freq)

        #Initialize figure and axes
        fig, ax = plt.subplots()
        
        #Sets figure width and height in inches
        fig.set_size_inches(cfg.PLT_WIDTH, cfg.PLT_HEIGHT)

        #Generate bar graph object with data; draws the actual bars
        bar_graph = ax.bar(cls.x_sorted, cls.y_sorted,
            color='#7ac1ff',        #light blue
            edgecolor='#1f7bcc',    #med blue
            linewidth=1.4
            )

        #Generate and format x and y axes.
        cls.generate_x_axis(ax)
        cls.generate_y_axis(ax)

        #Labels, annotations, and title
        cls.generate_lbls_highlights(bar_graph, ax)
        cls.generate_annotations(ax)
        cls.generate_title()

        plt.tight_layout()
        #Returns current figure
        return plt.gcf()

#Matplotlib helper code from PySimpleGUI documentation
def draw_figure(canvas, figure):
    figure_canvas_agg = FigureCanvasTkAgg(figure, canvas)
    figure_canvas_agg.draw()
    figure_canvas_agg.get_tk_widget().pack(side='top', fill='both', expand=1)
    return figure_canvas_agg