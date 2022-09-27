#Plotter.  Handles everything graph related - labels, axes...
#  also generates plot figure.

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
        #  spacing based on either pre-defined label spacing, or overwrite
        #  with explicit number of labels
        ind_x = np.arange(
            cls.x_sorted[0], cls.x_sorted[-1] + 1, 
            max(int((cls.x_sorted[-1] - cls.x_sorted[0]) / num_x_labels), 
                cls.plt_lbl_spacing)
        )

        ax.set_xlabel('Outcome')
        ax.set_xticks(ind_x, ind_x)

    @classmethod
    def generate_y_spacing(cls):
        '''
        Returns a list of y-dimension ticks for the graph using either 
        predetermined setting and the largest data value on the graph
        or alternative procedure for more degenerate graphs.
        '''
        y_dim = 0
        y_max = max(sim.freq.values())
        y_round_prec = 0

        #TODO: comment on the logic in this code here

        #For data with large peaks, have the table max be a value 
        #  divisible by 20, starting with 40
        c = 1.16
        if y_max > 33:

            y_dim = int(math.ceil(y_max * c / 10))
            if y_dim % 2 == 1:
                y_dim += 1
            y_dim *= 10
        elif y_max > 5:

            y_spacing = math.ceil(y_max / cfg.PLT_Y_GRIDLINES)
            y_dim = max(y_spacing * cfg.PLT_Y_GRIDLINES,
                math.ceil(y_max * c / cfg.PLT_Y_GRIDLINES) * cfg.PLT_Y_GRIDLINES)
        elif y_max > 0.7:
            y_dim = math.ceil(y_max * c)
            y_round_prec = 2
        else:
            y_dim = y_max * c
            y_round_prec = 2
            pass



        #Creates gridlines using y-dimension and number of gridlines specified
        ind_y = np.linspace(0, y_dim, cfg.PLT_Y_GRIDLINES + 1)
        return ind_y, y_round_prec


    @classmethod
    def generate_y_axis(cls, ax, plt):
        '''
        Sets up labels and settings for y-axis, using the
        matplotlib ax axis and plt plot objects.
        '''
        ind_y, y_round_prec = Plotter.generate_y_spacing()
        ax.set_yticks(ind_y, ind_y)

        #Sets up y-axis formatting, without percent symbols 
        ax.yaxis.set_major_formatter(
            plttick.PercentFormatter(decimals=y_round_prec, symbol=''))

        #Draws gridlines underneath data bars
        ax.set_axisbelow(True)
        plt.grid(axis = 'y', linestyle='dashed')
        ax.set_ylabel('Probability (%)')

    @classmethod
    def generate_data_labels(cls, graph, ax):
        '''
        Sets up labels and settings for the actual data bars, using the
        matplotlib (bar) graph object and ax axis objects
        '''
        data_labels = [str(round(x, 1)) for x in cls.y_sorted]

        #Eliminates values from being labeled according to label spacing param
        if cls.plt_lbl_spacing > 1:
            for i in range(0, len(data_labels)):
                if i % cls.plt_lbl_spacing != 0:
                    data_labels[i] = ''

        #Padding is distance above bar to place labels
        ax.bar_label(graph, fmt='%.1f', labels=data_labels, padding=10)

    @classmethod
    def generate_title(cls, plt):
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
    def calc_xbar(freq):
        weighted_sum = 0
        for outcome in freq.keys():
            weighted_sum += outcome * freq[outcome] / 100
        return round(weighted_sum, cfg.SIM_ROUND_PREC)

    @classmethod
    def calc_sx(freq, xbar):
        print(freq)
        weighted_sq_sum = 0
        for outcome in freq.keys():
            weighted_sq_sum += (outcome ** 2) * freq[outcome] / 100

        weighted_sq_sum -= xbar ** 2
        return round(math.sqrt(weighted_sq_sum), cfg.SIM_ROUND_PREC)

    @classmethod
    def calc_med(freq, step):
        #list that will store cumulative probabilities
        cum_prob = []

        for outcome in sorted(freq.keys()):
            if not cum_prob:
                cum_prob.append((outcome, round(freq[outcome], cfg.SIM_ROUND_PREC)))
            else:
                cum_prob.append((outcome, 
                    round(freq[outcome], cfg.SIM_ROUND_PREC) + cum_prob[-1][1]))

        cum_threshold_current = step
        #the outcomes that correspond to cum_threshold_step, 2*cum_threshold step,
        #etc.  
        cum_threshold_outcomes = []

        i = 0
        while cum_threshold_current < 100 and i < len(cum_prob):
            if cum_prob[i][1] > cum_threshold_current:
                cum_threshold_outcomes.append(cum_prob[i][0])
                cum_threshold_current += step
            i += 1
        print(cum_prob)
        print(cum_threshold_outcomes)

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

        #Initialize figure and axes
        fig, ax = plt.subplots()
        
        #Sets figure width and height in inches
        fig.set_size_inches(cfg.PLT_WIDTH, cfg.PLT_HEIGHT)

        #Generate bar graph object with data
        bar_graph = ax.bar(cls.x_sorted, cls.y_sorted)

        #Resets plot spacing; necessary for running a simulation not requiring
        #  alternative label spacing, after running a simulation that did
        cls.plt_lbl_spacing = 1

        #Alternative label spacing threshold calculation, if applicable.
        if max(sim.freq.keys()) - min(sim.freq.keys()) > cfg.PLT_LBL_SPACING_THRESH:
            cls.plt_lbl_spacing = math.ceil((
                max(sim.freq.keys()) - min(sim.freq.keys())) 
                / cfg.PLT_LBL_SPACING_THRESH
            )

        #Generate and format axes, labels, and title.
        cls.generate_x_axis(ax)
        cls.generate_y_axis(ax, plt)
        cls.generate_data_labels(bar_graph, ax)
        cls.generate_title(plt)

        #xbar = round(calc_xbar(sim.freq), cfg.SIM_ROUND_PREC)
        #sx = calc_sx(sim.freq, xbar)
        #cum_prob = calc_med(sim.freq, cfg.PLT_CUM_PROB_STEP)
        #print(f'mean is {xbar} stddev is {sx}')

        plt.tight_layout()
        #Returns current figure
        return plt.gcf()

#Matplotlib helper code from PySimpleGUI documentation
def draw_figure(canvas, figure):
    figure_canvas_agg = FigureCanvasTkAgg(figure, canvas)
    figure_canvas_agg.draw()
    figure_canvas_agg.get_tk_widget().pack(side='top', fill='both', expand=1)
    return figure_canvas_agg