import PySimpleGUI as sg

#each sublist represents a row
layout = [[sg.Text('Continue?')], [sg.Button('Yes'), sg.Button('No'), sg.Button('Bye')]]

window = sg.Window('Title', layout)

#comment out this line for event loop to work
#event, values = window.read(close = True)

#replaced with above close = True
#window.close()

#can shorten the above
#event, values = sg.Window('Title', layout).read(close = True)

#event loop
while True:
    #events are keys, value is a returned dictionary that corresponds
    #to input values
    #for this to work comment out line mentioned above
    event, values = window.read()
    if event in (sg.WIN_CLOSED, 'Bye'):
        break
    print(event)

window.close()
