f = open(r"day1_input.txt", mode = 'r')

#create list of calorie entries with empty strings for gaps
cal_list = f.readlines()
cal_list = [entry.strip('\n') for entry in cal_list]
cal_list = [int(entry) if entry.isdigit() else 0 for entry in cal_list]

#place 0 at 0th index so that the ith index corresponds to the ith elf
#when we populate this list of the sum of the calories the elves are carrying
sum_list = [0]

current_sum = 0
#populate the list containing the total calories per elf
for i in range(len(cal_list)):
    if cal_list[i] > 0:
        current_sum += cal_list[i]
    else:
        sum_list.append(current_sum)
        current_sum = 0

#part A answer
print(max(sum_list))

#part B answer
top_three_sum = 0
for _ in range(0, 3):
    top_three_sum += max(sum_list)
    sum_list.remove(max(sum_list))

print(top_three_sum)



f.close()