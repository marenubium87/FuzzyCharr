#Plotter.  Handles everything graph related - labels, axes...
#And also plot image generation.

import sim_config as cfg

import simulator
sim = simulator.Simulator

import math
import numpy as np

import matplotlib
import matplotlib.pyplot as plt
import matplotlib.ticker as plttick
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
matplotlib.use('TkAgg')

#create sorted lists for matplotlib from sim's freq dictionary
def generate_sorted_lists(sim):
    sim.x_sorted.clear()
    sim.y_sorted.clear()
    for outcome in sorted(sim.freq.keys()):
        sim.x_sorted.append(outcome)
        sim.y_sorted.append(sim.freq[outcome])

#sets up labels for x-axis
def generate_x_axis(ax, lbl_sp):
    #creates x-index from smallest to largest values, and sets x-ticks
    num_x_ticks = cfg.PLT_X_AX_TICKS_POP
    plot_x_sci_thresh = cfg.PLT_X_AX_SCI_THRESH
    if sim.x_sorted[-1] > plot_x_sci_thresh:
        num_x_ticks = int(num_x_ticks / 2)

    ind_x = np.arange(
        sim.x_sorted[0], sim.x_sorted[-1] + 1, 
        max(int((sim.x_sorted[-1] - sim.x_sorted[0]) / num_x_ticks), lbl_sp)
    )

    ax.set_xlabel('Outcome')
    ax.set_xticks(ind_x, ind_x)
    if max(ind_x) > plot_x_sci_thresh:
        ax.xaxis.set_major_formatter(plttick.FormatStrFormatter('%.1e'))

#sets up labels for y-axis
def generate_y_axis(ax, plt):
    #parameter determining how many y-gridlines should be displayed
    #(excluding the x-axis); graph will adjust scaling to satisfy this
    y_gl = 6
    y_spacing = math.ceil(max(sim.freq.values()) / y_gl)
    y_max = max(y_spacing * y_gl,
        int(max(sim.freq.values()) * 1.2)
    )
    ind_y = np.linspace(0, y_max, y_gl + 1)
    ind_y = [round(x, 2) for x in ind_y]
    ax.set_yticks(ind_y, ind_y)
    if max(ind_y) < 5:
        ax.yaxis.set_major_formatter(plttick.FormatStrFormatter('%.2f'))

    ax.set_ylabel('Probability (%)')
    #plots horizontal (y) grid lines and draws them under the bars
    ax.set_axisbelow(True)
    plt.grid(axis = 'y', linestyle='dashed')

#sets up labels above data bars.
def generate_data_labels(graph, ax, lbl_sp):
    data_labels = [str(round(x, 1)) for x in sim.y_sorted]
    if lbl_sp > 1:
        for i in range(0, len(data_labels)):
            if i % lbl_sp != 0:
                data_labels[i] = ''
    ax.bar_label(graph, fmt='%.1f', labels=data_labels, padding=15)

#Creates title string based on simulation parameters
def generate_title(plt):
    mode_str_dict = {'SUM':'Sum', 'SUCC':'Successes'}
    dice_str = sim.generate_dice_str()
    
    succ_thresh_str = ''
    if sim.succ_threshold > 1:
        succ_thresh_str = f' (Threshold: >= {sim.succ_threshold})'
    
    reroll_str = ''
    if sim.reroll_threshold > 0:
        reroll_str = (f', Reroll {sim.reroll_threshold}s'
            f' and below')

    drop_str = ''
    if sim.mode_drop != 'Do not drop':
        drop_str = f', {sim.mode_drop} {sim.num_drops}'
    
    trials_str = f', {sim.num_trials} trials'

    plt.title(f'Probability Dist. for {mode_str_dict[sim.mode]}'
        f'{succ_thresh_str} of {dice_str}{reroll_str}'
        f'{drop_str}{trials_str}')

#matplotlib helper code
def draw_figure(canvas, figure):
    figure_canvas_agg = FigureCanvasTkAgg(figure, canvas)
    figure_canvas_agg.draw()
    figure_canvas_agg.get_tk_widget().pack(side='top', fill='both', expand=1)
    return figure_canvas_agg

def calc_xbar(freq):
    weighted_sum = 0
    for outcome in freq.keys():
        weighted_sum += outcome * freq[outcome] / 100
    return round(weighted_sum, cfg.SIM_ROUND_PREC)

def calc_sx(freq, xbar):
    print(freq)
    weighted_sq_sum = 0
    for outcome in freq.keys():
        weighted_sq_sum += (outcome ** 2) * freq[outcome] / 100

    weighted_sq_sum -= xbar ** 2
    return round(math.sqrt(weighted_sq_sum), cfg.SIM_ROUND_PREC)

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

#takes the sim object and performs plot stuffs on it
def generate_plot():
    '''
    Sets up matplotlib plot from freq dictionary in class
    and returns figure of plot.
    '''
    #If no usable data, do not plot.
    if not sim.freq:
        return
    #closes previous figures, if any
    plt.close('all')



    #spacing for x-tick and value labels; 2 means every other one, etc.
    lbl_sp = cfg.PLT_LBL_SPACING

    #number of entries on chart before skipping algorithm kicks in
    lbl_sp_thresh = cfg.PLT_LBL_SPACING_THRESH

    #Alternative label spacing threshold calculation.
    if max(sim.freq.keys()) - min(sim.freq.keys()) > lbl_sp_thresh:
        lbl_sp = math.ceil(
            (max(sim.freq.keys()) - min(sim.freq.keys())) / lbl_sp_thresh)

    #create sorted lists for matplotlib from sim's freq dictionary
    generate_sorted_lists(sim)
    
    #init figure and axes
    fig, ax = plt.subplots()
    
    #sets figure width and height in inches
    fig.set_size_inches(cfg.PLT_WIDTH, cfg.PLT_HEIGHT)

    #generate bar graph object with data.
    bar_graph = ax.bar(sim.x_sorted, sim.y_sorted)

    #generate and format axes, labels, and title.
    generate_x_axis(ax, lbl_sp)
    generate_y_axis(ax, plt)
    generate_data_labels(bar_graph, ax, lbl_sp)
    generate_title(plt)

    xbar = round(calc_xbar(sim.freq), cfg.SIM_ROUND_PREC)
    sx = calc_sx(sim.freq, xbar)

    cum_prob = calc_med(sim.freq, cfg.PLT_CUM_PROB_STEP)

    print(f'mean is {xbar} stddev is {sx}')

    plt.tight_layout()

    #returns current figure
    return plt.gcf()
