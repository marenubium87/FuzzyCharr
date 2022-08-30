#Functions for elements on GUI called during event activations.

import simulator as sim

#all elements that need to be updated regardless of any event
def element_update(window):

    #portion dealing with simulator mode (successes vs sum)
    if sim.Simulator.dice and sim.Simulator.mode == 'SUCC':
        biggest_die = max(sim.Simulator.dice)
        window['-MODE_SUCC_THRESH-'].update(values=list(range(0, biggest_die + 1)))
        
        #resets die size for situation where a larger faced die is removed
        if int(window['-MODE_SUCC_THRESH-'].get()) > biggest_die:
            window['-MODE_SUCC_THRESH-'].update(value=biggest_die)
        
        #update success threshold from value in spinner
        sim.Simulator.succ_threshold = window['-MODE_SUCC_THRESH-'].get()

    #update of die pool and write to die pool multiline element
    pool = window['-POOL_CONTENTS-'+sim.sg.WRITE_ONLY_KEY]
    pool.update('')
    if sim.Simulator.dice:
        for type in sim.Simulator.dice.keys():
            pool.update(f'{sim.Simulator.dice[type]} D{type}\n', append=True)

    #drop number updates; makes sure dict isn't empty 
    #to prevent annoying error where number of drops can read -1
    if sim.Simulator.drop_mode != 'Do not drop' and sim.Simulator.dice:
        total_dice = sim.Simulator.get_total_dice()
        #NOT an off-by-one error here; it doesn't make sense to drop all the dice
        #so the correct interval is [0, total_dice)
        window['-DROP_NUM-'].update(values=list(range(0, total_dice)))

        #resets number of drops for situation where dice are removed
        if int(window['-DROP_NUM-'].get()) >= total_dice:
            window['-DROP_NUM-'].update(value = total_dice - 1)

        sim.Simulator.num_drops = window['-DROP_NUM-'].get()

#wrapper function for mode operations
def mode_ops(window, event):
    #success threshold is updated in universal element update
    if event in ['SUM', 'SUCC']:
        sim.Simulator.mode = event
        if event == 'SUM':
            window['-MODE_SUCC_THRESH-'].update(disabled=True, value=0)
            sim.Simulator.succ_threshold = 0
        if event == 'SUCC':
            window['-MODE_SUCC_THRESH-'].update(disabled=False)
    
        
#wrapper function for drop operations
def drop_ops(window, mode):
    '''
    mode has possible values {'Do not drop', 'Drop lowest', 'Drop highest'}
    '''
    #drop num range of values updated in universal element update
    sim.Simulator.drop_mode = mode
    #for debugging, can remove
    print(sim.Simulator.drop_mode)
    if mode == 'Do not drop':
        window['-DROP_NUM-'].update(disabled=True, value=0)
    else:
        window['-DROP_NUM-'].update(disabled=False)

def reroll_select_ops(window, enabled):
    '''
    enabled is a bool that describes the current state of the checkbox
    '''
    if enabled:
        pass
    else:
        pass