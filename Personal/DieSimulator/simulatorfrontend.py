from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import PySimpleGUI as sg
import matplotlib
matplotlib.use('TkAgg')
import simulatorbackend as sim

col1a = [
    [sg.Text('Dice to roll:')],
    [sg.Text('Number of simulations:')],
    [sg.Button('Simulate')]
]

col1b = [
    [sg.Input()],
    [sg.Input()]
]

col1am = [
    [sg.Text('D4 Label')],
    [sg.Text('Number here')],
    [sg.Button('Add D4')],
    [sg.Button('Remove D4')]
]

col1bm = [
    [sg.Text('D6 Label')],
    [sg.Text('Number here')],
    [sg.Button('Add D6')],
    [sg.Button('Remove D6')]
]

col1 = [
    [sg.Column(col1a, vertical_alignment='top'), 
    sg.Column(col1b, vertical_alignment='top')],
    [sg.Column(col1am), sg.Column(col1bm)]
]

col2 = [
    [sg.Canvas(key='-CANVAS-')]
]

layout = [
    [sg.Column(col1, vertical_alignment = 'top'), sg.Column(col2)], 
]

window = sg.Window('Testing', layout, finalize = True)
figure_canvas_agg = sim.draw_figure(window['-CANVAS-'].TKCanvas, 
    sim.Simulator.generate_plot())

event, values = window.read()

window.close()