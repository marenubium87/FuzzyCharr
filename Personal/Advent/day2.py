#returns 0 if loss, 3 if draw, 6 if win
def determine_outcome(opp, user):
    opp = ord(opp)
    #ascii correction to be able to compare the two inputs
    user = ord(user) - 23
    if opp == user:
        return 3
    #necessary because in this situation, scissors is nontransitive
    elif user == 67 and opp == 65:
        return 0
    elif user == 65 and opp == 67:
        return 6
    else:
        return 6 * int(user > opp)

#for the opponent sign and the outcome desired, returns the point value
# of the object we need to choose for the desired outcome
# return values 1 = rock, 2 = paper, 3 = scissors
def determine_shape(opp, outcome):
    #converts outcome to an int - 
    # 0 = lose, 1 = draw, 2 = win
    outcome = ord(outcome) - ord('X')
    #converts opponent's sign to an int in same order as return values
    opp = ord(opp) - ord('A') + 1
    if outcome == 1:
        return opp
    elif outcome == 2:
        #scissors is weird
        if opp == 3:
            return 1
        else:
            return opp + 1
    else:
        #scissors is weird; again - if opponent is rock we need to lose to it
        if opp == 1:
            return 3
        else:
            return opp - 1

f = open(r"day2_input.txt", mode = 'r')

strat_list = f.read().splitlines()

strat_array = [s.split() for s in strat_list]
strat_scores = [determine_outcome(s[0], s[1]) + ord(s[1]) - ord('W') for s in strat_array]

#part A result
print(sum(strat_scores))

#part B result
new_strat_scores = [determine_shape(s[0], s[1]) + 3 * (ord(s[1]) - ord('X')) 
    for s in strat_array]
print(sum(new_strat_scores))

f.close()