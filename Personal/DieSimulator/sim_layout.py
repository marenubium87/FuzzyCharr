#Handles theming and layout of the main GUI.

import PySimpleGUI as sg
import simulator as sim

#THEME GOES HERE
my_theme = {    'BACKGROUND': '#AAB8D0',    #blue-gray
            'TEXT': '#1015C9',              #dark blue
            'INPUT': '#5EF57A',             #light green
            'TEXT_INPUT': '#F73232',        #red
            'SCROLL': '#550D63',            #dark purple
            'BUTTON': ('#FFD6CC', '#242F50'), #light peach, navy
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

dice_pool_layout = [
    #makes this element write-only so that it's not included in values dict
    [sg.Multiline(size=(15, 4), 
        key='-POOL_CONTENTS-'+sg.WRITE_ONLY_KEY, 
        #disabled means contents can't be modified in any way
        autoscroll=True, disabled=True)],
    [sg.Button('Reset Dice Pool', key='-POOL_RESET-')]
]

dice_pool_frm = sg.Frame('Dice Pool', dice_pool_layout)

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
    [sg.Checkbox('Reroll dice', pad=(5,(0,2)), key='-REROLL_SELECT-', 
        checkbox_color='white', enable_events=True)],
    [sg.Spin(list(range(0,20)), 0, disabled=True, key='-REROLL_THRESH-',
        enable_events=True, size=2), 
        sg.Text('and below')]
]

reroll_frm = sg.Frame('Reroll', reroll_layout)


#DROP FRAME STUFFS HERE

drop_layout = [
    [sg.Combo(['Do not drop', 'Drop lowest', 'Drop highest'], 'Do not drop',
        size=11, key='-DROP_SELECT-', enable_events=True)],
    [sg.Spin([0], initial_value=0, key='-DROP_NUM-', disabled=True,
        enable_events=True),
    sg.Text(' Dice')]
]

drop_frm = sg.Frame('Drops', drop_layout)

#TRIALS FRAME STUFFS HERE
trials_layout = [
    [
        sg.Text('Number of trials:', pad =(5, 0)),
        sg.Input(size=15, key='-NUM_TRIALS-', 
            default_text=sim.Simulator.num_trials, pad =(6, 0),
            enable_events=True)
    ],
    [
        sg.Text('Est. 90% CI: +/-', pad=((5,0), 10)), 
        sg.Text(f'{sim.Simulator.calculate_MoE()}%', pad=(0, 10), size=6,
            justification='right', key='-NUM_TRIALS_CI-'), 
        sg.Button('Update', pad=((18,5), 5), key='-NUM_TRIALS_COMMIT-')
    ]
]

trials_frm = sg.Frame('Trials', trials_layout)

#SUBCOLUMN STUFF HERE

col_L1 = sg.Column([[reroll_frm, drop_frm], [trials_frm]])

col_L2 = sg.Column([
    [mode_frm],
    [sg.Button(' Run Simulation ', size=13, key='-ENGAGE-')],
    [sg.Button(' Save Output... ', size=13, key='-SAVE_OUTPUT-')]  
    ], element_justification='center')

#LEFT COLUMN STUFFS HERE

col_left = [
    [dice_frm],
    [manual_frm, dice_pool_frm],
    sg.vtop([col_L1, col_L2]),
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