import PySimpleGUI as sg

sg.theme('LightBrown2')

layout = [[sg.Text('sample text'), sg.Button('sample button')]]

window = sg.Window("hi", layout)

while True:  # Event Loop
    event, values = window.read()

    if event in (sg.WIN_CLOSED, None):
        break

window.close()