import math
import random as rand

num_trials = 30
min_val = 1
max_val = 300

results_set = set()

while len(results_set) < num_trials:
    results_set.add(rand.randint(min_val, max_val))

results_list = list(results_set)
results_list.sort()

print(results_list)