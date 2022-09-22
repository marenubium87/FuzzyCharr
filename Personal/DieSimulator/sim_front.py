#Frontend GUI and driver for simulator.

'''
TODO:  user currently can type garbage into success threshold and the other spinner
TODO:  still not happy with plot y-formatting for more degenerate cases... consider splitting into helper fcn
TODO:  continued documentation and cleanup for gui element ops
TODO:  continued documentation and cleanup for sim_front
'''

import sim_config as cfg

import simulator
sim = simulator.Simulator

import sim_layout as slay
import sim_gui_element_ops as sops

import PySimpleGUI as sg

def create_window():
    return sg.Window(f'Aerie Dice Roll Simulator v {cfg.VERSION} Eval Copy', 
        layout = slay.layout, finalize=True, use_default_focus=False)
window = create_window()

while True:
    #In sg, events are keys
    #Value is a returned dictionary that corresponds to input values
    event, values = window.read()
    #for debugging purposes, can remove
    print(event)

    #quit events
    if event in (sg.WIN_CLOSED, None):
        break

    #button events for incre/decrementing common dice
    if event[1] in ('+', '-'):
        #string slicing to extract operation and die from event
        sim.modify_dice(int(event[2:-1]), event[1])

    #handles events related to manual input
    #slices the string to pass "sub-event" into man_ops
    if event[1:4] == 'MAN':
        sops.man_ops(window, event[5:-1], values)

    #handles events dealing with the mode selection frame
    #slices the string to pass "sub-event" into mode_ops
    if event[1:5] == 'MODE':
        sops.mode_ops(window, event[6:-1])

    #handles events dealing with the drop selection frame, 
    #passes in configuration of dropdown in values dictionary
    if event[1:5] == 'DROP':
        sops.drop_ops(window, values['-DROP_SELECT-'])

    #handles the clicking of the "Clear die pool" button
    if event == '-POOL_CLEAR-':
        sim.clear_die_pool()

    #handles events dealing with the reroll selection checkbox
    if event == '-REROLL_SELECT-':
        sops.reroll_select_ops(window, window['-REROLL_SELECT-'].get())

    #handles events dealing with the trials frame
    if event[1:11] == 'NUM_TRIALS':
        sops.num_trials_ops(window, event, values)

    #runs simulation sequence assuming that dice pool is not empty
    if event == '-ENGAGE-' and sim.dice:
        sops.engage_ops(window)

    #saves figure to file
    if event == '-SAVE_OUTPUT-':
        sops.save_output_ops()

    #element updates that must be performed regardless of event
    sops.element_update(window)

    window.refresh()

window.close()