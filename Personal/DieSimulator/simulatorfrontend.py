from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import PySimpleGUI as sg
import matplotlib
matplotlib.use('TkAgg')
import simulatorbackend as sim
import simulatorlayout as slay

layout = slay.layout

window = sg.Window('Die Simulator Testing Version', layout, finalize = True)
figure_canvas_agg = sim.draw_figure(window['-CANVAS-'].TKCanvas, 
    sim.Simulator.simulation_wrapper())

event, values = window.read()

window.close()