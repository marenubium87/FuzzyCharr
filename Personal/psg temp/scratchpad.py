import random as rand
import math

rand.seed()

total_trials = 1000
num_metatrials = 10000
metatrials_list = []

for j in range(1, num_metatrials + 1):
    successes = 0
    if(j % 100 == 0):
        print(j)
    for i in range(1, total_trials + 1):
        if rand.randrange(1, 5) == 1:
            successes = successes + 1
    successes = round(successes / total_trials * 100, 5)
    metatrials_list.append(successes)

est_two_sigma = math.sqrt(0.25 * 0.75 / total_trials) * 100 * 1.96

outside_two_sigma = 0
for result in metatrials_list:
     if abs(result - 25) > est_two_sigma:
        outside_two_sigma += 1

print(outside_two_sigma / num_metatrials * 100)