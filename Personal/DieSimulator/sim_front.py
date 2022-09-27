#Simulator frontend.  Activates PSG and runs main program.

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
    #In PSG, events are keys; values is a returned dict corresponding to
    #  element inputs or changes.
    event, values = window.read()

    #For debugging purposes, can remove!
    print(event)

    #Quitting events
    if event in (sg.WIN_CLOSED, None):
        break

    #Button events for inc/decrementing common dice
    if event[1] in ('+', '-'):
        #String slicing to extract operation and die from event
        sim.modify_dice(int(event[2:-1]), event[1])

    #Handle events related to manual input
    #  slices the string to pass "sub-event" into man_ops()
    if event[1:4] == 'MAN':
        sops.man_ops(window, event[5:-1], values)

    #Handle clicking of the "Clear die pool" button
    if event == '-POOL_CLEAR-':
        sim.clear_die_pool()

    #Handle events dealing with the mode selection frame
    #  slices the string to pass "sub-event" into mode_ops()
    if event[1:5] == 'MODE':
        sops.mode_ops(window, event[6:-1])

    #Handle events dealing with the drop selection frame, 
    #  passes in current state of dropdown in values dictionary
    if event[1:5] == 'DROP':
        sops.drop_ops(window, values['-DROP_SELECT-'])

    #Handle events dealing with the reroll selection checkbox,
    #  passing in enabled state of checkbox as bool
    if event == '-REROLL_SELECT-':
        sops.reroll_select_ops(window, window['-REROLL_SELECT-'].get())

    #Handle events dealing with the trials frame
    #  slices the string to pass "sub-event" into num_trials_ops()
    if event[1:11] == 'NUM_TRIALS':
        sops.num_trials_ops(window, event[12:-1], values)

    #Update dice pool text
    sops.pool_update(window)

    #Element updates that must be checked/performed for *any* event
    #If input errors detected, flag will equal 1; 0 else
    #Input error flag checked immediately below if ENGAGE event is triggered
    input_error_flag = sops.element_update(window, values)

    #Runs simulation sequence (simulate, sanitize, plot, draw)
    #  if dice pool is not empty
    if event == '-ENGAGE-':     
        if input_error_flag:
            sg.popup(
                    ('One or more input parameters is not\na valid value'
                    ' and has been reset.\n\n'
                    'Please check your inputs and try again.'),
                    title='Input Error')
        elif not sim.dice:
            sg.popup(f'No dice in pool; simulation aborted.', title='Empty Dice Pool')
        else:
            sops.engage_ops(window)

    #Saves figure to file
    if event == '-SAVE_OUTPUT-':
        sops.save_output_ops()

    window.refresh()

window.close()