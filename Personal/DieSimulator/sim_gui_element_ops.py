#Functions for elements on GUI called during event activations.

import sim_config as cfg

import simulator
sim = simulator.Simulator

import sim_plotter as splot

import PySimpleGUI as sg

#helper function to parse input from manual input field
def parse_input(s):
    d = {}
    #split into groups based on the + character
    die_groups = s.split('+')
    for group in die_groups:
        temp = group.split('d')
        if len(temp) != 2:
            return {}
        if not temp[0].isdigit() or not temp[1].isdigit():
            return {}
        if int(temp[0]) < 1 or int(temp[1]) < 1:
            return {}
        temp[0] = int(temp[0])
        temp[1] = int(temp[1])
        if temp[1] in d:
            d[temp[1]] = d[temp[1]] + temp[0]
        else:
            d[temp[1]] = temp[0]
    return d            

#all elements that need to be updated regardless of any event
def element_update(window):

    #update dealing with simulator mode and success threshold
    if sim.mode == 'SUCC':
        
        #that is, the biggest value a die can contain
        #needed for success threshold and rerolls
        mst = window['-MODE_SUCC_THRESH-']
        if sim.dice:
            biggest_die = 0
            mst.update(disabled=False)
            #range starts at 1 because it makes no sense to ever have
            #a success threshold of 0
            biggest_die = max(sim.dice)
            mst.update(values=list(range(1, biggest_die + 1)))
            #resets threshold for situation where a larger faced die is removed
            if int(mst.get()) > biggest_die:
                mst.update(value=biggest_die)
        else:
            #disables and resets spinner if dice pool is empty
            mst.update(value=1, values=[1], disabled=True)

        #update success threshold from value in spinner
        sim.succ_threshold = int(mst.get())

    #update of die pool and write to die pool multiline element
    pool = window['-POOL_CONTENTS-'+sg.WRITE_ONLY_KEY]
    pool_str = ''
    pool.update(pool_str)
    if sim.dice:
        for type in sim.dice.keys():
            pool_str += f'{sim.dice[type]} D{type}\n'
        #clears up an errant newline at the end of output
        pool_str = pool_str[:-1]
        pool.update(pool_str)

    #update dealing with number of drops
    if sim.mode_drop != 'Do not drop':
        #prevents an annoying error when dice pool is empty causing
        #windows to report a value of -1
        total_dice = 1
        if sim.dice:
            total_dice = sim.get_total_dice()

        dn = window['-DROP_NUM-']
        #NOT an off-by-one error here; it doesn't make sense to drop all the dice
        #so the correct interval is [0, total_dice)
        dn.update(values=list(range(0, total_dice)))

        #resets number of drops for situation where dice are removed
        if int(dn.get()) >= total_dice:
            dn.update(value= total_dice - 1)

        sim.num_drops = dn.get()

    #update reroll threshold; only care if the checkbox is checked
    if window['-REROLL_SELECT-'].get():
        #prevents an annoying error when dice pool is empty causing
        #windows to report a value of -1
        smallest_die = 1
        if sim.dice:
            smallest_die = min(sim.dice)
        rt = window['-REROLL_THRESH-']
        
        #NOT an off by one error - we want the interval to be [0, smallest_die)
        #since if we have to reroll the largest value then we'll reroll forever
        rt.update(values=list(range(0, smallest_die)))

        #resets threshold for situation where a larger faced die is removed
        if int(rt.get()) >= smallest_die:
            rt.update(value= smallest_die - 1)
            
        sim.reroll_threshold = rt.get()

def man_ops(window, event, values):

    mi_str = values['-MAN_INPUT-']
    window_mi = window['-MAN_INPUT-']
    if event == 'INPUT':
        #for debugging purposes, can remove
        print(values)
        if mi_str and mi_str[-1] not in ('0123456789d+'):
            window_mi.update(mi_str[:-1])
    if event in ['REPLACE', 'APPEND']:
        new_dice_dict = parse_input(window_mi.get())
        if not new_dice_dict:
            sg.popup('Unable to parse your dice string; ' 
                'please check your input.', title='Error Parsing Input')
        else:
            window_mi.update(value = '')
            if event == 'REPLACE':
                sim.clear_die_pool()
            for type in new_dice_dict:
                sim.modify_dice(type, '+', new_dice_dict[type])

def mode_ops(window, event):
    #success threshold is updated in universal element update, and not here
    if event in ['SUM', 'SUCC']:
        mst = window['-MODE_SUCC_THRESH-']
        sim.mode = event
        if event == 'SUM':
            mst.update(disabled=True, value=1)
            sim.succ_threshold = 1
        if event == 'SUCC':
            mst.update(disabled=False, value=1)
    
def drop_ops(window, mode):
    '''
    mode has possible values {'Do not drop', 'Drop lowest', 'Drop highest'}
    '''

    #drop num range of values updated in universal element update
    sim.mode_drop = mode
    #for debugging, can remove
    print(sim.mode_drop)
    window_dn = window['-DROP_NUM-']
    if mode == 'Do not drop':
        window_dn.update(disabled=True, value=0)
    else:
        window_dn.update(disabled=False)

def reroll_select_ops(window, enabled):
    '''
    enabled is a bool that describes the current state of the checkbox
    '''

    #success threshold is updated in universal element update
    window_rt = window['-REROLL_THRESH-']
    if enabled:
        window_rt.update(disabled=False)
    else:
        window_rt.update(disabled=True, value=0)
        sim.num_drops = 0

def num_trials_ops(window, event, values):
    nt_str = values['-NUM_TRIALS-']
    window_nt = window['-NUM_TRIALS-']
    if event == '-NUM_TRIALS-':
        #for debugging purposes, can remove
        print(values)
        if nt_str and nt_str[-1] not in ('0123456789'):
            window_nt.update(nt_str[:-1])

    if event == '-NUM_TRIALS_COMMIT-':
        if nt_str.isdigit() and int(nt_str) > 0:
            sim.num_trials = int(nt_str)
            window['-NUM_TRIALS_MOE-'].update(
                value=f'{sim.calculate_MoE()}%')
        else:
            #code to tell people to enter a valid number
            sg.popup(
                'Please enter a valid (integer, positive) number of trials.',
                title='Input Error')
            sim.num_trials = 0
        window_nt.update(value=sim.num_trials)

    if event == '-NUM_TRIALS_CI-':
        sim.CI_level = int(window['-NUM_TRIALS_CI-'].get())
        print(sim.CI_level)

def engage_ops(window):
    #clear previous canvas
    if sim.fig_agg is not None:
        sim.fig_agg.get_tk_widget().forget()

    #TODO:  WRITE THE LINES OF CODE THAT SIMULATION WRAPPER CONTAINS, HERE,
    #USING STUFFS FROM SIM AND SPLOT CLASSES

    sim.perform_sim()
    sim.sanitize_outcomes()
    sim.fig = splot.generate_plot()

    sim.fig_agg = splot.draw_figure(window['-CANVAS-'].TKCanvas, sim.fig)

#FIGURE OUT HOW TO DO PATH STUFFS DISPLAY FOR THE SAVE DIR
def save_output_ops():
    if sim.fig is not None:
        file_path = sg.popup_get_file('Choose path to save figure (PNG):', 
            save_as=True, title='Save Figure')
        splot.plt.savefig(f'{file_path}.png')
        sg.popup('Saved.')