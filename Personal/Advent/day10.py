f = open(r'day10_input.txt', mode='r')

raw = f.read().splitlines()
raw = [s.split() for s in raw]

print(raw)

cycles = []
cycles.append(0)
cycles.append(1)

for instruction in raw:
    if instruction[0] == 'noop':
        cycles.append(cycles[-1])
    elif instruction[0] == 'addx':
        cycles.append(cycles[-1])
        cycles.append(cycles[-1] + int(instruction[1]))

#part A
s = 0
for i in range(6):
    partial = cycles[20 + 40 * i] * (20 + 40 * i)
    s += partial
print(s)

output = []
for z in range(6):
    output_line = []
    for i in range(40):
        if abs(cycles[40 * z + i + 1] - i) < 2:
            output_line.append('#')
        else:
            output_line.append('.')
    output.append(output_line)

print(cycles)

for line in output:
    print(line)













f.close()