def get_dup_vals(character):
    if ord(character) >= ord('a') and ord(character) <= ord('z'):
        #a-z are 1-26
        
        return ord(character) - ord('a') + 1
    else:
        #A-Z are 27 - 52
        return ord(character) - ord('A') + 27

f = open(r'day3_input.txt', mode='r')

raw_packlist = f.read().splitlines()
corrected_packlist = [[s[0:len(s)//2], s[len(s)//2:]] for s in raw_packlist]

duplicates = [set(s[0]) & set(s[1]) for s in corrected_packlist]

dup_vals = [get_dup_vals(min(ch)) for ch in duplicates]
#Part A
print(sum(dup_vals))

badge_list = []
for i in range(0, 300, 3):
    badge = set(raw_packlist[i]) & set(raw_packlist[i+1]) & set(raw_packlist[i+2])
    badge_list.append(badge)

print(badge_list)
badge_vals = [get_dup_vals(min(ch)) for ch in badge_list]
#part b
print(sum(badge_vals))

f.close()