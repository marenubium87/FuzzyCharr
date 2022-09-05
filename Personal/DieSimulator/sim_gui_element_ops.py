#Functions for elements on GUI called during event activations.

import simulator as sim
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
        if temp[1] in d:
            d[temp[1]] = d[temp[1]] + temp[0]
        else:
            d[temp[1]] = temp[0]
    return d            

#all elements that need to be updated regardless of any event
def element_update(window):

    #update dealing with simulator mode and success threshold
    if sim.Simulator.mode == 'SUCC':
        
        #that is, the biggest value a die can contain
        #needed for success threshold and rerolls
        biggest_die = 0
        if sim.Simulator.dice:
            biggest_die = max(sim.Simulator.dice)

        mst = window['-MODE_SUCC_THRESH-']
        mst.update(values=list(range(0, biggest_die + 1)))
        
        #resets threshold for situation where a larger faced die is removed
        if int(mst.get()) > biggest_die:
            mst.update(value=biggest_die)
        
        #update success threshold from value in spinner
        sim.Simulator.succ_threshold = mst.get()

    #update of die pool and write to die pool multiline element
    pool = window['-POOL_CONTENTS-'+sim.sg.WRITE_ONLY_KEY]
    pool_str = ''
    pool.update(pool_str)
    if sim.Simulator.dice:
        for type in sim.Simulator.dice.keys():
            pool_str += f'{sim.Simulator.dice[type]} D{type}\n'
        #clears up an errant newline at the end of output
        pool_str = pool_str[:-1]
        pool.update(pool_str)

    #update dealing with number of drops
    if sim.Simulator.mode_drop != 'Do not drop':
        #prevents an annoying error when dice pool is empty causing
        #windows to report a value of -1
        total_dice = 1
        if sim.Simulator.dice:
            total_dice = sim.Simulator.get_total_dice()

        dn = window['-DROP_NUM-']
        #NOT an off-by-one error here; it doesn't make sense to drop all the dice
        #so the correct interval is [0, total_dice)
        dn.update(values=list(range(0, total_dice)))

        #resets number of drops for situation where dice are removed
        if int(dn.get()) >= total_dice:
            dn.update(value= total_dice - 1)

        sim.Simulator.num_drops = dn.get()

    #update reroll threshold; only care if the checkbox is checked
    if window['-REROLL_SELECT-'].get():
        #prevents an annoying error when dice pool is empty causing
        #windows to report a value of -1
        smallest_die = 1
        if sim.Simulator.dice:
            smallest_die = min(sim.Simulator.dice)
        rt = window['-REROLL_THRESH-']
        
        #NOT an off by one error - we want the interval to be [0, smallest_die)
        #since if we have to reroll the largest value then we'll reroll forever
        rt.update(values=list(range(0, smallest_die)))

        #resets threshold for situation where a larger faced die is removed
        if int(rt.get()) >= smallest_die:
            rt.update(value= smallest_die - 1)
            
        sim.Simulator.reroll_threshold = rt.get()

def man_ops(window, event, values):

    mi_string = values['-MAN_INPUT-']
    wmi = window['-MAN_INPUT-']
    if event == 'INPUT':
        #for debugging purposes, can remove
        print(values)
        if mi_string and mi_string[-1] not in ('0123456789d+'):
            wmi.update(mi_string[:-1])
    if event in ['REPLACE', 'APPEND']:
        new_dice_dict = parse_input(wmi.get())
        if not new_dice_dict:
            sg.popup('Unable to parse your dice string; ' 
                'please check your input.', title='Error Parsing Input')
        else:
            wmi.update(value = '')
            if event == 'REPLACE':
                sim.Simulator.clear_die_pool()
            for type in new_dice_dict:
                sim.Simulator.modify_dice(type, '+', new_dice_dict[type])

def mode_ops(window, event):
    #success threshold is updated in universal element update
    if event in ['SUM', 'SUCC']:
        mst = window['-MODE_SUCC_THRESH-']
        sim.Simulator.mode = event
        if event == 'SUM':
            mst.update(disabled=True, value=0)
            sim.Simulator.succ_threshold = 0
        if event == 'SUCC':
            mst.update(disabled=False)
    
def drop_ops(window, mode):
    '''
    mode has possible values {'Do not drop', 'Drop lowest', 'Drop highest'}
    '''

    #drop num range of values updated in universal element update
    sim.Simulator.mode_drop = mode
    #for debugging, can remove
    print(sim.Simulator.mode_drop)
    dn = window['-DROP_NUM-']
    if mode == 'Do not drop':
        dn.update(disabled=True, value=0)
    else:
        dn.update(disabled=False)

def reroll_select_ops(window, enabled):
    '''
    enabled is a bool that describes the current state of the checkbox
    '''

    #success threshold is updated in universal element update
    rt = window['-REROLL_THRESH-']
    if enabled:
        rt.update(disabled=False)
    else:
        rt.update(disabled=True, value=0)
        sim.Simulator.num_drops = 0

def num_trials_ops(window, event, values):
    nt_string = values['-NUM_TRIALS-']
    wnt = window['-NUM_TRIALS-']
    if event == '-NUM_TRIALS-':
        #for debugging purposes, can remove
        print(values)
        if nt_string and nt_string[-1] not in ('0123456789'):
            wnt.update(nt_string[:-1])

    if event == '-NUM_TRIALS_COMMIT-':
        if nt_string.isdigit() and int(nt_string) > 0:
            sim.Simulator.num_trials = int(nt_string)
            window['-NUM_TRIALS_MOE-'].update(
                value=f'{sim.Simulator.calculate_MoE()}%')
        else:
            #code to tell people to enter a valid number
            sg.popup(
                'Please enter a valid (integer, positive) number of trials.',
                title='Input Error')
            sim.Simulator.num_trials = 0
        wnt.update(value=sim.Simulator.num_trials)

    if event == '-NUM_TRIALS_CI-':
        sim.Simulator.CI_level = int(window['-NUM_TRIALS_CI-'].get())
        print(sim.Simulator.CI_level)