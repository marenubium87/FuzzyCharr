#Simulator backend.  Handles simulating die rolls,
#sanitizing and aggregating results.

import sim_config as cfg

import math
import random as rand

class Simulator:
    #dictionary where keys are types of dice and vals are number of that die
    #e.g. 6 : 2 would mean 2d6
    dice = {}

    #available modes {SUM, SUCC}
    mode = 'SUM'
    #die roll must be >= this number to be counted as a success
    succ_threshold = 1

    #available modes {'Do not drop', 'Drop lowest', 'Drop highest'}
    mode_drop = 'Do not drop'
    #number of dice to drop
    num_drops = 0
    #reroll all dice equal to or below this number
    reroll_threshold = 0

    num_trials = cfg.SIM_DEFAULT_TRIALS
    #the confidence level selected for the simulation
    CI_level = cfg.SIM_DEFAULT_CI_LEVEL

    #dictionary storing outcomes as keys and frequencies as values for
    #any given simulation run
    freq = {}

    #for plot use
    x_sorted = []
    y_sorted = []

    #plot figure
    fig = None

    #interface for TKinter fig adaptor
    fig_agg = None

    @classmethod
    def modify_dice(cls, d, o, n=1):
        '''
        Modifies simulator's dice dictionary entry of die type d
        with string operation o, and number n.  If d doesn't exist 
        in the dictionary it will be created.
        
        Acceptable values for o are as follows:
        +:  adds one die of the type to the die pool
        -:  subtracts one die of the type from the die pool
        =:  sets the number of dice of type to n

        '''
        if o == '+':
            if d in cls.dice:
                cls.dice[d] += n
            else:
                cls.dice[d] = n
        if o == '-':
            if d in cls.dice:
                cls.dice[d] -= n
            else:
                #if key not in dict then subtracting dice does nothing
                pass
        if o == '=':
            cls.dice[d] = n

        #final check, prunes any invalid entries to make sure dictionary
        #is in a valid state
        to_delete = []
        for die_type in cls.dice:
            if int(cls.dice[die_type]) < 1:
                to_delete.append(die_type)

        for die_type in to_delete:
            cls.dice.pop(die_type)

        #checking output, can safely comment out in prod code
        print(cls.dice)

    @classmethod
    def clear_die_pool(cls):
        '''
        Helper fcn; empties the dice dictionary and resets params relevant
        to dice pool (drops and success threshold)
        '''
        cls.dice.clear()
        cls.succ_threshold = 1
        cls.num_drops = 0
        cls.reroll_threshold = 0
        
    @classmethod
    def get_total_dice(cls):
        '''
        Helper fcn: returns total dice currently in pool.
        '''
        result = 0
        #dice pool is not empty
        if cls.dice:
            result = sum(cls.dice.values())
        return result

    @classmethod
    def drop_dice(cls, roll):
        '''
        Helper fcn: drops highest or lowest dice from previous roll,
        then returns
        '''
        if cls.mode_drop != 'Do not drop':
            for i in range(cls.num_drops):
                if cls.mode_drop == 'Drop lowest':
                    roll.remove(min(roll))
                elif cls.mode_drop == 'Drop highest':
                    roll.remove(max(roll))
        return roll

    @classmethod
    def calculate_MoE(cls):
        '''
        Helper function.  Calculates the margin of error for each outcome
        using the expected CI (conservative estimate using 
        binomial dist, p=0.5) based on number of trials.
        '''
        #z-star critical values for various confidence intervals
        z_star_dict = cfg.SIM_ZSTAR_VALS

        moe = math.sqrt(0.5 * 0.5 / cls.num_trials)
        moe = moe * 100 * z_star_dict[cls.CI_level]
        
        return round(moe, 1)

    @classmethod
    def generate_dice_str(cls):
        '''
        Helper function.  Generates a string from the current dice pool
        in 1d2+3d4 format.
        '''
        dice_str = ''
        for die_type in cls.dice:
            dice_str += f'+{cls.dice[die_type]}d{die_type}'
        #removes leading '+'
        return dice_str[1:]

    @classmethod
    def perform_roll(cls):
        '''
        Performs a single roll using dice dictionary, drops num_drops dice, 
        then returns a list of remaining dice rolls in this particular roll.
        '''
        single_roll = []
        new_result = 0

        #performs roll and rerolls dice until above reroll threshold
        for type in cls.dice:
            for die in range(cls.dice[type]):
                while True:
                    # +1 since dice values are in form [1, n], not [0, n)
                    new_result = rand.randrange(1, type + 1)
                    #strict inequality as reroll treshold defined as the highest
                    #value that needs to be rerolled
                    if new_result > cls.reroll_threshold:
                        break
                single_roll.append(new_result)

        #drops appropriate number of dice
        single_roll = cls.drop_dice(single_roll)

        return single_roll

    @classmethod
    def get_successes(cls, r):
        s = 0
        for outcome in r:
            if outcome >= cls.succ_threshold:
                s += 1
        return s

    @classmethod
    def perform_sim(cls):
        '''
        Performs a simulation run using the die pool and number of trials
        loaded in the Simulator class, saving the result to the
        frequency dictionary.
        '''
        rand.seed()
        #resets frequency dictionary from any past simulation run(s)
        cls.freq.clear()
        single_roll = []

        #using this range instead of (0, t) for accurate simulation count
        for roll in range(1, cls.num_trials + 1):
            single_roll = cls.perform_roll()

            if cls.mode == 'SUM':
                outcome = sum(single_roll)
            elif cls.mode == 'SUCC':
                outcome = cls.get_successes(single_roll)

            if outcome in cls.freq:
                cls.freq[outcome] += 1
            else:
                #create entry outcome not yet recorded in dictionary
                cls.freq[outcome] = 1

    @classmethod
    def sanitize_outcomes(cls):
        '''
        Modifies frequency dictionary such that values corresponding to outcomes
        are now probabilities (percents) instead of counts.  Also removes outcomes
        from dictionary if their associated probability is below a dynamic
        cutoff threshold calculated by the cutoff sensitivity parameter.
        '''
        #if a data value is at least this number of times smaller than
        #largest data value, remove it from the plot
        cutoff_sensitivity = cfg.SIM_CUTOFF_SENSITVITY
        cutoff_threshold = (
            (max(cls.freq.values()) / cls.num_trials) / cutoff_sensitivity
        )
        
        to_delete = []
        for outcome in cls.freq:
            #rounds to 6 dec. places to avoid floating point inaccuracies in output.
            cls.freq[outcome] = round(cls.freq[outcome] / 
                cls.num_trials * 100, 6)
            if cls.freq[outcome] < cutoff_threshold:
                to_delete.append(outcome)

        for value in to_delete:
            cls.freq.pop(value)