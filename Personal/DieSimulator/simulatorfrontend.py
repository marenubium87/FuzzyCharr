from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import PySimpleGUI as sg
import matplotlib
matplotlib.use('TkAgg')
import simulatorbackend as sim

#COMMON DICE FRAME STUFFS HERE
button_size = 3

col_d4 = sg.Column([
    [sg.Text('D4', key='-D4LABEL-', size=button_size, justification='center')],
    [sg.Button('+', key='-D4PLUS-', size=button_size)],
    [sg.Button('-', key='-D4MINUS', size=button_size)]
])

col_d6 = sg.Column([
    [sg.Text('D6', key='-D6LABEL-', size=button_size, justification='center')],
    [sg.Button('+', key='-D6PLUS-', size=button_size)],
    [sg.Button('-', key='-D6MINUS', size=button_size)]
])

col_d8 = sg.Column([
    [sg.Text('D8', key='-D8LABEL-', size=button_size, justification='center')],
    [sg.Button('+', key='-D8PLUS-', size=button_size)],
    [sg.Button('-', key='-D8MINUS', size=button_size)]
])

col_d10 = sg.Column([
    [sg.Text('D10', key='-D10LABEL-', size=button_size, justification='center')],
    [sg.Button('+', key='-D10PLUS-', size=button_size)],
    [sg.Button('-', key='-D10MINUS', size=button_size)]
])

col_d12 = sg.Column([
    [sg.Text('D12', key='-D12LABEL-', size=button_size, justification='center')],
    [sg.Button('+', key='-D12PLUS-', size=button_size)],
    [sg.Button('-', key='-D12MINUS', size=button_size)]
])

col_d20 = sg.Column([
    [sg.Text('D20', key='-D20LABEL-', size=button_size, justification='center')],
    [sg.Button('+', key='-D20PLUS-', size=button_size)],
    [sg.Button('-', key='-D20MINUS', size=button_size)]
])

#frame requires an iterable of iterables, be advised!
dice_frm = sg.Frame('Common Dice', [[col_d4, col_d6, col_d8, col_d10,
        col_d12, col_d20]])

#MANUAL INPUT FRAME STUFFS HERE

manual_layout = [
    [sg.Text('Dice to roll (e.g. 1d2+3d4):')],
    [sg.Input(size=21, key='-MAN_INPUT-')]
]

manual_frm = sg.Frame('Manual Control', manual_layout)

#DROP FRAME STUFFS HERE

drop_layout = [
    [sg.Combo(['Do not drop', 'Drop lowest', 'Drop highest'], 'Do not drop',
        key='-DROP_SELECT-')],
    [sg.Spin(list(range(sim.Simulator.get_total_dice())), 0, key='-NUM_DROP'),
    sg.Text(' Dice')]
]

drop_frm = sg.Frame('Drops', drop_layout)

col_left = [
    [dice_frm],
    [manual_frm, drop_frm],
    [sg.Text('Current dice pool')],
    [sg.Text('dice pool text goes here')],
    [sg.Button('Reset'), sg.Button('Run Simulation')]
    #frame requires an iterable of iterables, hence why syntax here is
    #[dice_layout] and not dice_layout
    
]

col_right = [
    [sg.Canvas(key='-CANVAS-')]
]

layout = [
    [sg.Column(col_left, vertical_alignment = 'top', element_justification='center'), 
        sg.Column(col_right)], 
]

window = sg.Window('Testing', layout, finalize = True)
figure_canvas_agg = sim.draw_figure(window['-CANVAS-'].TKCanvas, 
    sim.Simulator.simulation_wrapper())

event, values = window.read()

window.close()