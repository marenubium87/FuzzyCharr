#Frontend GUI and driver for simulator.

import PySimpleGUI as sg
import simulator as sim
import sim_layout as slay
import sim_gui_element_ops as sops

def create_window():
    return sg.Window(f'Aerie Dice Roll Simulator v {sim.version} Eval Copy', 
        layout = slay.layout, finalize=True, use_default_focus=False)

window = create_window()

fig_agg = None

while True:
    #events are keys, value is a returned dictionary that corresponds
    #to input values
    event, values = window.read()
    #for debugging purposes
    print(event)

    #quit events
    if event in (sg.WIN_CLOSED, None):
        break

    #button events for incre/decrementing common dice
    if event[1] in ('+', '-'):
        #string slicing to extract operation and die from event
        sim.Simulator.modify_dice(int(event[2:-1]), event[1])

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
        sim.Simulator.clear_die_pool()

    #handles events dealing with the reroll selection checkbox
    if event == '-REROLL_SELECT-':
        sops.reroll_select_ops(window, window['-REROLL_SELECT-'].get())

    #handles events dealing with the trials frame
    if event[1:11] == 'NUM_TRIALS':
        sops.num_trials_ops(window, event, values)

    #runs simulation sequence assuming that dice pool is not empty
    if event == '-ENGAGE-' and sim.Simulator.dice:
        #clear previous canvas
        if fig_agg is not None:
            fig_agg.get_tk_widget().forget()

        sim.Simulator.fig = sim.Simulator.simulation_wrapper()
        fig_agg = sim.draw_figure(window['-CANVAS-'].TKCanvas, 
            sim.Simulator.fig)

    #saves figure to file
    if event == '-SAVE_OUTPUT-':
        if sim.Simulator.fig is not None:
            file_path = sg.popup_get_file('Choose path to save figure (PNG):', 
                save_as=True, title='Save Figure')
            sim.plt.savefig(f'{file_path}.png')

    #element updates that must be performed regardless of event
    sops.element_update(window)

    window.refresh()

window.close() 