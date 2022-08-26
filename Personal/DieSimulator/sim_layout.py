#Handles theming and layout of the main GUI.

import PySimpleGUI as sg

#THEME GOES HERE
my_theme = {    'BACKGROUND': '#AAB8D0',    #blue-gray
            'TEXT': '#1015C9',              #dark blue
            'INPUT': '#5EF57A',             #light green
            'TEXT_INPUT': '#F73232',        #red
            'SCROLL': '#550D63',            #dark purple
            'BUTTON': ('#F2A97F', '#242F50'), #peach, navy
            'PROGRESS': ('#406FFF', '#C8D5FF'), #med blue, light blue
            'BORDER': 1,
            'SLIDER_DEPTH': 0,
            'PROGRESS_DEPTH': 0
        }
sg.theme_add_new('mytheme', my_theme)
sg.theme('mytheme')

#COMMON DICE FRAME STUFFS HERE
b_size = 3

#button padding, pixels
b_pad = 5
b_vpad = 3

#dist btwn leftmost button and frame, and rightmost button and frame
b_margin = 15

d4_plus_btn = sg.Button('+', key='-+4-', size=b_size,  
    pad=((b_margin, b_pad), b_vpad))
d6_plus_btn = sg.Button('+', key='-+6-', size=b_size,  
    pad=((b_pad, b_pad), b_vpad))
d8_plus_btn = sg.Button('+', key='-+8-', size=b_size,  
    pad=((b_pad, b_pad), b_vpad))
d10_plus_btn = sg.Button('+', key='-+10-', size=b_size, 
    pad=((b_pad, b_pad), b_vpad))
d12_plus_btn = sg.Button('+', key='-+12-', size=b_size, 
    pad=((b_pad, b_pad), b_vpad))
d20_plus_btn = sg.Button('+', key='-+20-', size=b_size, 
    pad=((b_pad, b_margin), b_vpad))

d4_minus_btn = sg.Button('-', key='--4-', size=b_size,  
    pad=((b_margin, b_pad), (b_vpad, 2 * b_vpad)))
d6_minus_btn = sg.Button('-', key='--6-', size=b_size,  
    pad=((b_pad, b_pad), (b_vpad, 2 * b_vpad)))
d8_minus_btn = sg.Button('-', key='--8-', size=b_size,  
    pad=((b_pad, b_pad), (b_vpad, 2 * b_vpad)))
d10_minus_btn = sg.Button('-', key='--10-', size=b_size, 
    pad=((b_pad, b_pad), (b_vpad, 2 * b_vpad)))
d12_minus_btn = sg.Button('-', key='--12-', size=b_size, 
    pad=((b_pad, b_pad), (b_vpad, 2 * b_vpad)))
d20_minus_btn = sg.Button('-', key='--20-', size=b_size, 
    pad=((b_pad, b_margin), (b_vpad, 2 * b_vpad)))

col_d4 = sg.Column([
    [sg.Text('D4', key='-D4LABEL-', size=b_size, justification='center',
        pad=((b_margin, b_pad), b_vpad))],
    [d4_plus_btn],
    [d4_minus_btn]
    ],
    element_justification='center'
)

col_d6 = sg.Column([
    [sg.Text('D6', key='-D6LABEL-', size=b_size, justification='center',
        pad=((b_pad, b_pad), b_vpad))],
    [d6_plus_btn],
    [d6_minus_btn]
    ],
    element_justification='center'
)

col_d8 = sg.Column([
    [sg.Text('D8', key='-D8LABEL-', size=b_size, justification='center',
        pad=((b_pad, b_pad), b_vpad))],
    [d8_plus_btn],
    [d8_minus_btn]
    ],
    element_justification='center'
)

col_d10 = sg.Column([
    [sg.Text('D10', key='-D10LABEL-', size=b_size, justification='center',
        pad=((b_pad, b_pad), b_vpad))],
    [d10_plus_btn],
    [d10_minus_btn]
    ],
    element_justification='center'
)

col_d12 = sg.Column([
    [sg.Text('D12', key='-D12LABEL-', size=b_size, justification='center',
        pad=((b_pad, b_pad), b_vpad))],
    [d12_plus_btn],
    [d12_minus_btn]
    ],
    element_justification='center'
)

col_d20 = sg.Column([
    [sg.Text('D20', key='-D20LABEL-', size=b_size, justification='center',
        pad=((b_pad, b_margin), b_vpad))],
    [d20_plus_btn],
    [d20_minus_btn]
    ],
    element_justification='center'
)

#frame requires an iterable of iterables, be advised!
dice_frm = sg.Frame('Common Dice', [[col_d4, col_d6, col_d8, col_d10,
        col_d12, col_d20]])

#MANUAL INPUT FRAME STUFFS HERE

manual_layout = [
    [sg.Text('Dice to roll:')],
    [sg.Text(text='e.g. 1d2+3d4', pad=(5, (0,2)))],
    [sg.Input(size=17, key='-MAN_INPUT-')],
    [sg.Button('Replace', key='-MAN_REPLACE-'), 
        sg.Button('Append', key='-MAN_APPEND-')]
]

manual_frm = sg.Frame('Manual Control', manual_layout)

#DIE POOL FRAME STUFFS HERE

die_pool_layout = [
    [sg.Multiline(size=(15, 4), 
        key='-POOL_CONTENTS-')],
    [sg.Button('Reset Die Pool', key='-POOL_RESET-')]
]

die_pool_frm = sg.Frame('Die Pool', die_pool_layout)

#DROP FRAME STUFFS HERE

drop_layout = [
    [sg.Combo(['Do not drop', 'Drop lowest', 'Drop highest'], 'Do not drop',
        size=10, key='-DROP_SELECT-')],
    [sg.Spin(0, key='-DROP_NUM-', disabled=True),
    sg.Text(' Dice')]
]

drop_frm = sg.Frame('Drops', drop_layout)

#MODE FRAME STUFFS HERE
mode_layout = [
    [sg.Radio(text='Sum', default=True, group_id=1, enable_events=True,
        pad=(5,0), circle_color = 'white', key='-MODE_SUM-')],
    [sg.Radio(text='Successes', group_id=1, enable_events=True,
        pad=(5,0), circle_color = 'white', key='-MODE_SUCC-')],
    [sg.Text('Threshold:', pad=((5, 0), 0)), 
    sg.Spin([0], initial_value=0, disabled=True, key='-MODE_SUCC_THRESH-', 
        enable_events=True, size=2)]
]

mode_frm = sg.Frame('Mode', mode_layout)

#REROLL FRAME STUFFS HERE

reroll_layout = [
    [sg.Checkbox('Reroll dice', pad=(5,(0,2)), key='-REROLL_SELECT-')],
    [sg.Spin(list(range(0,20)), 0, disabled=True, key='-REROLL_THRESH-'), 
        sg.Text('and below')]
]

reroll_frm = sg.Frame('Reroll', reroll_layout)

#SUBCOLUMN STUFF HERE

col_sub_left = sg.Column([
    [drop_frm, reroll_frm],
    [sg.Text('Number of trials:', pad =(5, (10, 0))), 
        sg.Input(size=15, key='-NUM_TRIALS-', pad =(5, (10, 0)))]
])

#LEFT COLUMN STUFFS HERE

col_left = [
    [dice_frm],
    [manual_frm, die_pool_frm],
    sg.vtop([mode_frm, col_sub_left]),
    [sg.Button('  Run Simulation  ', pad=((5,50), 20), key='-ENGAGE-'),
    sg.Button('Save Output to File', key='-SAVE_OUTPUT-')]
]

#RIGHT COLUMN STUFFS HERE

col_right = [
    [sg.Canvas(size=(900, 480), key='-CANVAS-', pad=(10, 10))]
]

#FULL LAYOUT HERE

layout = [
    [sg.Column(col_left, vertical_alignment = 'top', element_justification='center'), 
        sg.VerticalSeparator(), sg.Column(col_right)]
]