#use online call reference for information on elements
#also can call sg.main_sdk_help()

#sg.set_options() will change program options like font, etc.

#to define fonts
font_var = ('font_name', size, 'underline italic bold overstrike')

#general element call
layout = [
    [elements go in here, each one being a list],
    [etc]
    #example
    sg.Text('text message', pad=((5, 50), (10, 20), other params here))
    #pad is tuples describing L/R and then U/D padding in pixels
    #size is a tuple in the form (characters wide, rows high)

]