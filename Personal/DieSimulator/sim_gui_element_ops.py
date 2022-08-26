#Functions for elements on GUI called during event activations.

import simulator as sim

#all elements that need to be updated regardless of any event
def element_update(window):
    if sim.Simulator.dice and sim.Simulator.mode == 'SUCC':
        biggest_die = max(sim.Simulator.dice)
        print(window['-MODE_SUCC_THRESH-'].get())
        sim.Simulator.succ_threshold = window['-MODE_SUCC_THRESH-'].get()
        window['-MODE_SUCC_THRESH-'].update(values=list(range(0, biggest_die + 1)))
    else:
        window['-MODE_SUCC_THRESH-'].update(value=0)
        sim.Simulator.succ_threshold = 0
    print(sim.Simulator.succ_threshold)
    

#wrapper function for mode operations
def mode_ops(window, event):
    if event in ['SUM', 'SUCC']:
        sim.Simulator.mode = event
        if event == 'SUM':
            window['-MODE_SUCC_THRESH-'].update(disabled=True, value=0)
        if event == 'SUCC':
            window['-MODE_SUCC_THRESH-'].update(disabled=False)
    #success threshold is updated in universal element update
        
    