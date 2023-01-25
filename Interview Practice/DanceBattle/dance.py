# import sys
# sys.stdin = open("input1.txt", "r")

num_cases = int(input())

def parse_input():
    line = input().split()
    energy = int(line[0])
    num_competitors = int(line[1])
    competitors = input().split()
    competitors = [int(competitor) for competitor in competitors]
    competitors.sort()
    return energy, num_competitors, competitors
    
def compute_honor(parsed):
    energy = parsed[0]
    num_competitors = parsed[1]
    competitors = parsed[2]
    honor = 0
    
    while num_competitors > 1:
        #dance
        if energy > competitors[0]:
            energy -= competitors[0]
            num_competitors -= 1
            competitors.pop(0)
            honor += 1
        #recruit
        elif honor > 0:
            energy += competitors[-1]
            num_competitors -= 1
            competitors.pop()
            honor -= 1
        else:
            break
        
    #check last competitor; if can't dance don't recruit
    if energy > competitors[0]:
        honor += 1
    
    return honor
            
for i in range(num_cases):
    
    print(f'Case #{i + 1}: {compute_honor(parse_input())}')



