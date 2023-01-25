# feels_good = True

# def generate_weather(n):
#     if n % 2 == 0:
#         return 'sunny'
#     else:
#         return 'rainy'

# def generate_day(n):
#     if n % 2 == 0:
#         return 'Tuesday'
#     else:
#         return 'Wednesday'

# n = 5

# print(f'Today is {generate_day(n)} and ' +
#     f'the weather is {generate_day(2) if n % 2 == 0 else generate_day(3)}')

# my_list = ['alpha', 'bravo', 'charlie']
# element = 'delta'
# print(f'{element in my_list}')

# def in_list(list, element):
#     return element in list

# print(in_list(my_list, 'omega'))

# my_list = ['a', 'b', 'c']
# my_list.insert(2, 'e')
# print(my_list)
# del my_list[-1]
# print(my_list)

# for item in reversed(my_list):
#     print(item)

# my_arr = [[(j) for j in range(4)] for i in range(3)]
# print(my_arr)

# transpose = [[my_arr[j][i] for j in range(len(my_arr))] for i in range(len(my_arr[0]))]
# print(transpose)

# for item in my_list[::-1]:
#     print(item)

# my_list.extend(['s', 't', 'w'])
# print(my_list)

# x, *y, z = my_list
# print(x)
# print(y)
# print(z)

myList = ['a', 'b', 'c']
myList.insert(2, 'e')
myList.append('k')
myList[0] = 't'
print(myList)
x, *y, z = myList
print(x)
print(y)
print(z)

s1 = {3, 5, 9, 11}
s2 = {3, 5, 8, 7}
print(s1 - s2)
my_list = [6, 5, 9, 11, 13]
s1.update(my_list)
print(s1)
print(s1.pop())
print(s1.pop())