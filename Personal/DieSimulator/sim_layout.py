#Handles theming and layout of the main GUI.

import sim_config as cfg

import simulator
sim = simulator.Simulator

import PySimpleGUI as sg

####    ####    ####    ####
####    THEME SECTION HERE
my_theme = {    'BACKGROUND': '#AAB8D0',    #blue-gray
            'TEXT': '#1015C9',              #dark blue
            'INPUT': '#C0FFBF',             #light green
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

####    ####    ####    ####
####    COMMON DICE FRAME STUFFS STARTS HERE
d4_plus_btn = sg.Button('+', key='-+4-', size=cfg.BTN_SIZE,  
    pad=((cfg.BTN_MARGIN, cfg.BTN_HPAD), cfg.BTN_VPAD))
d6_plus_btn = sg.Button('+', key='-+6-', size=cfg.BTN_SIZE,  
    pad=((cfg.BTN_HPAD, cfg.BTN_HPAD), cfg.BTN_VPAD))
d8_plus_btn = sg.Button('+', key='-+8-', size=cfg.BTN_SIZE,  
    pad=((cfg.BTN_HPAD, cfg.BTN_HPAD), cfg.BTN_VPAD))
d10_plus_btn = sg.Button('+', key='-+10-', size=cfg.BTN_SIZE, 
    pad=((cfg.BTN_HPAD, cfg.BTN_HPAD), cfg.BTN_VPAD))
d12_plus_btn = sg.Button('+', key='-+12-', size=cfg.BTN_SIZE, 
    pad=((cfg.BTN_HPAD, cfg.BTN_HPAD), cfg.BTN_VPAD))
d20_plus_btn = sg.Button('+', key='-+20-', size=cfg.BTN_SIZE, 
    pad=((cfg.BTN_HPAD, cfg.BTN_MARGIN), cfg.BTN_VPAD))

d4_minus_btn = sg.Button('-', key='--4-', size=cfg.BTN_SIZE,  
    pad=((cfg.BTN_MARGIN, cfg.BTN_HPAD), (cfg.BTN_VPAD, 2 * cfg.BTN_VPAD)))
d6_minus_btn = sg.Button('-', key='--6-', size=cfg.BTN_SIZE,  
    pad=((cfg.BTN_HPAD, cfg.BTN_HPAD), (cfg.BTN_VPAD, 2 * cfg.BTN_VPAD)))
d8_minus_btn = sg.Button('-', key='--8-', size=cfg.BTN_SIZE,  
    pad=((cfg.BTN_HPAD, cfg.BTN_HPAD), (cfg.BTN_VPAD, 2 * cfg.BTN_VPAD)))
d10_minus_btn = sg.Button('-', key='--10-', size=cfg.BTN_SIZE, 
    pad=((cfg.BTN_HPAD, cfg.BTN_HPAD), (cfg.BTN_VPAD, 2 * cfg.BTN_VPAD)))
d12_minus_btn = sg.Button('-', key='--12-', size=cfg.BTN_SIZE, 
    pad=((cfg.BTN_HPAD, cfg.BTN_HPAD), (cfg.BTN_VPAD, 2 * cfg.BTN_VPAD)))
d20_minus_btn = sg.Button('-', key='--20-', size=cfg.BTN_SIZE, 
    pad=((cfg.BTN_HPAD, cfg.BTN_MARGIN), (cfg.BTN_VPAD, 2 * cfg.BTN_VPAD)))

col_d4 = sg.Column([
    [sg.Text('D4', key='-D4LABEL-', size=cfg.BTN_SIZE, justification='center',
        pad=((cfg.BTN_MARGIN, cfg.BTN_HPAD), cfg.BTN_VPAD))],
    [d4_plus_btn],
    [d4_minus_btn]
    ],
    element_justification='center'
)

col_d6 = sg.Column([
    [sg.Text('D6', key='-D6LABEL-', size=cfg.BTN_SIZE, justification='center',
        pad=((cfg.BTN_HPAD, cfg.BTN_HPAD), cfg.BTN_VPAD))],
    [d6_plus_btn],
    [d6_minus_btn]
    ],
    element_justification='center'
)

col_d8 = sg.Column([
    [sg.Text('D8', key='-D8LABEL-', size=cfg.BTN_SIZE, justification='center',
        pad=((cfg.BTN_HPAD, cfg.BTN_HPAD), cfg.BTN_VPAD))],
    [d8_plus_btn],
    [d8_minus_btn]
    ],
    element_justification='center'
)

col_d10 = sg.Column([
    [sg.Text('D10', key='-D10LABEL-', size=cfg.BTN_SIZE, justification='center',
        pad=((cfg.BTN_HPAD, cfg.BTN_HPAD), cfg.BTN_VPAD))],
    [d10_plus_btn],
    [d10_minus_btn]
    ],
    element_justification='center'
)

col_d12 = sg.Column([
    [sg.Text('D12', key='-D12LABEL-', size=cfg.BTN_SIZE, justification='center',
        pad=((cfg.BTN_HPAD, cfg.BTN_HPAD), cfg.BTN_VPAD))],
    [d12_plus_btn],
    [d12_minus_btn]
    ],
    element_justification='center'
)

col_d20 = sg.Column([
    [sg.Text('D20', key='-D20LABEL-', size=cfg.BTN_SIZE, justification='center',
        pad=((cfg.BTN_HPAD, cfg.BTN_MARGIN), cfg.BTN_VPAD))],
    [d20_plus_btn],
    [d20_minus_btn]
    ],
    element_justification='center'
)

#frame requires an iterable of iterables, be advised!
dice_frm = sg.Frame('Common Dice', [[col_d4, col_d6, col_d8, col_d10,
        col_d12, col_d20]])

####    COMMON DICE FRAME STUFFS ENDS HERE

####    ####    ####    ####
####    MANUAL INPUT FRAME STUFFS STARTS HERE
manual_layout = [
    [sg.Text('Dice to roll:')],
    [sg.Text(text='e.g. 1d2+3d4', pad=(5, (0,2)))],
    [sg.Input(size=17, key='-MAN_INPUT-', enable_events=True)],
    [sg.Button('Replace', key='-MAN_REPLACE-', pad=(5, (3, 5))), 
        sg.Button('Append', key='-MAN_APPEND-', pad=(5, (3, 5)))]
]

manual_frm = sg.Frame('Manual Control', manual_layout)

####    MANUAL INPUT FRAME STUFFS ENDS HERE

####    ####    ####    ####
####    DIE POOL FRAME STUFFS STARTS HERE
dice_pool_layout = [
    #makes this element write-only so that it's not included in values dict
    [sg.Multiline(size=(15, 4), key='-POOL_CONTENTS-'+sg.WRITE_ONLY_KEY, 
        #disabled means contents can't be modified in any way
        autoscroll=True, disabled=True)],
    [sg.Button('Clear Dice Pool', key='-POOL_CLEAR-', pad=(5, (3, 5)))]
]

dice_pool_frm = sg.Frame('Dice Pool', dice_pool_layout)

####    DIE POOL FRAME STUFFS ENDS HERE

####    ####    ####    ####
####    MODE FRAME STUFFS STARTS HERE
mode_layout = [
    [sg.Radio(text='Sum', default=True, group_id=1, enable_events=True,
        pad=(5,0), circle_color = 'white', key='-MODE_SUM-')],
    [sg.Radio(text='Successes', group_id=1, enable_events=True,
        pad=(5,0), circle_color = 'white', key='-MODE_SUCC-')],
    [sg.Text('Threshold:', pad=((5, 0), 0)), 
        sg.Spin([1], initial_value=1, disabled=True, key='-MODE_SUCC_THRESH-',
            enable_events=True, size=2
            )
    ]
]

mode_frm = sg.Frame('Mode', mode_layout)

####    MODE FRAME STUFFS ENDS HERE

####    ####    ####    ####
####    REROLL FRAME STUFFS STARTS HERE
reroll_layout = [
    [sg.Checkbox('Reroll dice', pad=(5,(0,2)), key='-REROLL_SELECT-', 
        checkbox_color='white', enable_events=True)],
    [sg.Spin(list(range(0,20)), 0, disabled=True, key='-REROLL_THRESH-',
        enable_events=True, size=2, pad=(5, (5, 4))), 
        sg.Text('and below', pad=((2, 5), (5, 4)))]
]

reroll_frm = sg.Frame('Reroll', reroll_layout)

####    REROLL FRAME STUFFS ENDS HERE

####    ####    ####    ####
####    DROP FRAME STUFFS STARTS HERE
drop_layout = [
    [sg.Combo(['Do not drop', 'Drop lowest', 'Drop highest'], 'Do not drop',
        size=11, key='-DROP_SELECT-', enable_events=True)],
    [sg.Spin([0], initial_value=0, key='-DROP_NUM-', disabled=True,
        enable_events=True, pad=(5, (5, 4))),
    sg.Text('Dice', pad=(5, (5, 4)))]
]

drop_frm = sg.Frame('Drops', drop_layout)

####    DROP FRAME STUFFS ENDS HERE

####    ####    ####    ####
####    TRIALS FRAME STUFFS STARTS HERE
trials_layout = [
    [
        sg.Text('Number of trials:', pad =(5, 0)),
        sg.Input(size=6, key='-NUM_TRIALS-', 
            default_text=sim.num_trials, pad =(4, 0),
            enable_events=True),
        sg.Button('Update', pad=((5,5), 5), key='-NUM_TRIALS_COMMIT-')
    ],
    [
        sg.Text('Est. MoE: +/-', pad=((5,0), 5)),
        sg.Text(f'{sim.calculate_MoE()}%', pad=((0, 5), 5), size=5,
            justification='right', key='-NUM_TRIALS_MOE-'),
        sg.Text('CI (%):', pad=((4, 0), 5)),
        sg.Combo([key for key in cfg.SIM_ZSTAR_VALS.keys()], 
            enable_events=True, default_value=cfg.SIM_DEFAULT_CI_LEVEL, 
            size=2, key='-NUM_TRIALS_CI-', pad=((5, 5), 5))
    ]
]

trials_frm = sg.Frame('Trials', trials_layout)

####    TRIALS FRAME STUFFS ENDS HERE

####    ####    ####    ####
####    CREDITS FRAME STUFFS STARTS HERE

credits_layout = [
    [sg.Text('Made with <3 by Aerie')],
    [sg.Text(f'v {cfg.VERSION} Eval Copy')]
]

credits_frm = sg.Frame('About', credits_layout)

####    CREDITS FRAME STUFFS ENDS HERE

####    ####    ####    ####
####    (LEFT) SUBCOLUMNS STUFFS STARTS HERE
col_L1 = sg.Column([[reroll_frm, drop_frm], [trials_frm], [credits_frm]],
    element_justification='left')

col_L2 = sg.Column([
    [mode_frm],
    [sg.Button(' Run Simulation ', size=13, key='-ENGAGE-', pad=(5, (10, 2)))],
    [sg.Button(' Save Output... ', size=13, key='-SAVE_OUTPUT-',
        pad=(5, (5, 5)))]  
    ], element_justification='center')

####    (LEFT) SUBCOLUMNS STUFFS ENDS HERE

####    ####    ####    ####
####    LEFT AND RIGHT COLUMN STUFFS STARTS HERE
col_left = [
    [dice_frm],
    [manual_frm, dice_pool_frm],
    sg.vtop([col_L1, col_L2]),
]

col_right = [
    [sg.Canvas(size=
        (cfg.PLT_WIDTH * cfg.PLT_DPI, cfg.PLT_HEIGHT * cfg.PLT_DPI),
        key='-CANVAS-', pad=(10, 10))]
]
####    LEFT AND RIGHT COLUMN STUFFS ENDS HERE

####    ####    ####    ####
####    FULL LAYOUT
layout = [
    [
        sg.Column(col_left, vertical_alignment = 'top', 
            element_justification='center'), 
        sg.VerticalSeparator(), sg.Column(col_right)
    ]
]