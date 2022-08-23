import PySimpleGUI as sg

#COMMON DICE FRAME STUFFS HERE
button_size = 3

col_d4 = sg.Column([
    [sg.Text('D4', key='-D4LABEL-', size=button_size, justification='center')],
    [sg.Button('+', key='-D4PLUS-', size=button_size)],
    [sg.Button('-', key='-D4MINUS', size=button_size)]
    ],
    element_justification='center'
)

col_d6 = sg.Column([
    [sg.Text('D6', key='-D6LABEL-', size=button_size, justification='center')],
    [sg.Button('+', key='-D6PLUS-', size=button_size)],
    [sg.Button('-', key='-D6MINUS', size=button_size)]
    ],
    element_justification='center'
)

col_d8 = sg.Column([
    [sg.Text('D8', key='-D8LABEL-', size=button_size, justification='center')],
    [sg.Button('+', key='-D8PLUS-', size=button_size)],
    [sg.Button('-', key='-D8MINUS', size=button_size)]
    ],
    element_justification='center'
)

col_d10 = sg.Column([
    [sg.Text('D10', key='-D10LABEL-', size=button_size, justification='center')],
    [sg.Button('+', key='-D10PLUS-', size=button_size)],
    [sg.Button('-', key='-D10MINUS', size=button_size)]
    ],
    element_justification='center'
)

col_d12 = sg.Column([
    [sg.Text('D12', key='-D12LABEL-', size=button_size, justification='center')],
    [sg.Button('+', key='-D12PLUS-', size=button_size)],
    [sg.Button('-', key='-D12MINUS', size=button_size)]
    ],
    element_justification='center'
)

col_d20 = sg.Column([
    [sg.Text('D20', key='-D20LABEL-', size=button_size, justification='center')],
    [sg.Button('+', key='-D20PLUS-', size=button_size)],
    [sg.Button('-', key='-D20MINUS', size=button_size)]
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
    [sg.Radio(text='Sum', default=True, group_id=1, pad=(5,0), 
        key='-MODE_SUM-')],
    [sg.Radio(text='Successes', group_id=1, pad=(5,0), key='-MODE_SUCC-')],
    [sg.Text('Threshold:'), 
        sg.Spin(0, disabled=True, key='-MODE_SUCC_THRESH-')]
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
    [sg.Text('Number of trials:'), 
        sg.Input(size=15, key='-NUM_TRIALS-')]
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
    [sg.Canvas(key='-CANVAS-')]
]

#FULL LAYOUT HERE

layout = [
    [sg.Column(col_left, vertical_alignment = 'top', element_justification='center'), 
        sg.Column(col_right)]
]