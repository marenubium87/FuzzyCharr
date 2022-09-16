#Environment and configuration settings.

VERSION = '0.9.6'
LAST_UPDATED = '09/16/22'

####    ####    ####    ####
####    VALUES FOR SIMULATOR STUFFS STARTS HERE

#default number of trials
SIM_DEFAULT_TRIALS = 60000

#dict containing critical z* values for selected confidence intervals
SIM_ZSTAR_VALS = {70:1.036, 80:1.281, 90:1.645, 95:1.96,
            97:2.17, 99:2.576}

#default confidence interval for MoE calculations
#must be one of the confidence interval values above!
SIM_DEFAULT_CI_LEVEL = 90

#if a data value is at least this number of times smaller than
#largest data value, remove it from the plot
SIM_CUTOFF_SENSITVITY = 45

####    VALUES FOR SIMULATOR STUFFS ENDS HERE

####    ####    ####    ####
####    VALUES FOR PLOT STUFFS STARTS HERE

#plot dimensions in inches, DPI in pixels
PLT_WIDTH = 9
PLT_HEIGHT = 5
PLT_DPI = 100

#default plot label spacing
# 1 means label each bar, 2 means skip every other one, etc.
#this value may get overwritten if there are too many ticks on plot
#(see label spacing threshold below)
PLT_LBL_SPACING = 1

#number of bars on graph before alternate label spacing rules kick in
#number of labels is approximately equal to data range divided by
#this parameter.
PLT_LBL_SPACING_THRESH = 28

PLT_X_AX_TICKS_POP = 20

PLT_X_AX_SCI_THRESH = 999

####    VALUES FOR PLOT STUFFS ENDS HERE

####    ####    ####    ####
####    VALUES FOR LAYOUT STUFFS STARTS HERE

#button size
BTN_SIZE = 3
#button hotizontal and vertical padding, pixels
BTN_HPAD = 5
BTN_VPAD = 3
#dist btwn leftmost button and frame, and rightmost button and frame, pixels
BTN_MARGIN = 15

####    VALUES FOR LAYOUT STUFFS ENDS HERE