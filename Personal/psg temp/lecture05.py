'''see http://calls.PySimpleGUI.org for more info as well
Keys in PySimpleGUI:
1.  identify elements, essentially like an element's name
2.  events are usually keys
3.  used as keys in values dictionary

key convention "-KEY-"
'''

import PySimpleGUI as sg

layout = [  [sg.Text('text element')],
            #input element - gets a line of text
            #specify the key that will be used in the values dict later
            #every element can be given a key
            [sg.Input(key='-MYINPUT-')],
            [sg.Button('ok', key='-OK-'), sg.Button('exit')]
        ]

window = sg.Window('Title', layout)

while True:
    #remember values is a dictionary; remember the key from earlier
    event, values = window.read()
    #really good for debugging
    print(event, values)
    if event in (sg.WIN_CLOSED, 'exit'):
        break
    #referencing the values dictionary generated from earlier
    print(values['-MYINPUT-'])
    #can call this key as well to find this element
    #overloaded [ ] operator
    #can also do window.find_element('-MYINPUT-')

    #clears window after input
    window['-MYINPUT-'].update('')

window.close()
