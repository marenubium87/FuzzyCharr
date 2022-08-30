#Frontend GUI and driver for simulator.

import PySimpleGUI as sg
import simulator as sim
import sim_layout as slay
import sim_gui_element_ops as sops

def create_window():
    return sg.Window('Dice Roll Simulator', layout = slay.layout,
        finalize=True, use_default_focus=False)

window = create_window()

fig_agg = None

while True:
    #events are keys, value is a returned dictionary that corresponds
    #to input values
    event, values = window.read()
    #for debugging purposes
    print(event)

    #to quit
    if event in (sg.WIN_CLOSED, None):
        break

    #button events for incre/decrementing common dice
    if event[1] in ('+', '-'):
        #string slicing to extract operation and die from event
        sim.Simulator.modify_dice(int(event[2:-1]), event[1])

    #handles events dealing with the mode selection frame, slicing the
    #"sub-event" to pass into mode_ops
    if event[1:5] == 'MODE':
        sops.mode_ops(window, event[6:-1])

    #handles events dealing with the drop selection frame, 
    #passes in configuration of dropdown in values dictionary
    if event[1:5] == 'DROP':
        sops.drop_ops(window, values['-DROP_SELECT-'])

    if event == '-POOL_RESET-':
        sim.Simulator.reset_die_pool()

    #handles events dealing with the reroll selection checkbox
    if event == '-REROLL_SELECT-':
        sops.reroll_select_ops(window, window['-REROLL_SELECT-'].get())

    #runs simulation sequence assuming that dice pool is not empty
    if event == '-ENGAGE-' and sim.Simulator.dice:
        #clear previous canvas
        if fig_agg is not None:
            fig_agg.get_tk_widget().forget()

        fig = sim.Simulator.simulation_wrapper()
        fig_agg = sim.draw_figure(window['-CANVAS-'].TKCanvas, fig)

    #element updates that must be performed regardless of event
    sops.element_update(window)
    window.refresh()

window.close() 