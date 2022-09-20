#Environment and configuration, default settings.

VERSION = '0.9.6'
LAST_UPDATED = '09/16/22'


####    ####    ####    ####
####    VALUES FOR SIMULATOR STUFFS STARTS HERE

#Default number of trials when program starts
SIM_DEFAULT_TRIALS = 60000

#Dict containing critical z* values for selected confidence intervals
SIM_ZSTAR_VALS = {70:1.036, 80:1.281, 90:1.645, 95:1.96, 97:2.17, 99:2.576}

#Default confidence interval for MoE calculations
#Must be one of the confidence interval values above!
SIM_DEFAULT_CI_LEVEL = 90

#If a data value is at least this number of times smaller than
#  the largest data value, remove it from the plot
SIM_CUTOFF_SENSITVITY = 45

#Number of decimal places to round results to truncate floating-point
#  inaccuracies in representation
SIM_ROUND_PREC = 6

####    VALUES FOR SIMULATOR STUFFS ENDS HERE


####    ####    ####    ####
####    VALUES FOR PLOT STUFFS STARTS HERE

#Plot dimensions in inches, DPI in pixels
PLT_WIDTH = 9
PLT_HEIGHT = 5
PLT_DPI = 100

#Default label spacing for the actual historgram bars
#  1 means label each bar, 2 means skip every other one, etc.
#  this value may get overwritten if there are too many bars on plot
#  (see label spacing threshold below)
PLT_LBL_SPACING = 1

#Number of bars on graph before alternate label spacing rules kick in
#  if above this threshold, number of labels is approximately equal to 
#  number of bars divided by this parameter
PLT_LBL_SPACING_THRESH = 28

#Number of labeled x-axis ticks along bottom of graph (approximate)
PLT_X_AX_TICKS_POP = 20

#Value above which x-axis labels become written in scientific notation
PLT_X_AX_SCI_THRESH = 999

#Step size for cumulative probability distribution
#  for example, step size of 25 would result in cumulative probability
#  values reported at 25, 50, and 75 percent
PLT_CUM_PROB_STEP = 25

####    VALUES FOR PLOT STUFFS ENDS HERE


####    ####    ####    ####
####    VALUES FOR LAYOUT STUFFS STARTS HERE

#Button size for the D(n) +/- buttons
BTN_SIZE = 3
#Horizontal and vertical padding for the D(n) +/- buttons, in
BTN_HPAD = 5
BTN_VPAD = 3
#For D(n) +/- buttons, distance btwn leftmost button and frame, 
#  and rightmost button and frame, pixels
BTN_MARGIN = 15

####    VALUES FOR LAYOUT STUFFS ENDS HERE