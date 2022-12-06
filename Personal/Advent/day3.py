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
print(sum(dup_vals))
f.close()