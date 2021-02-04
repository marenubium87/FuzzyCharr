# comments are like this

'''Makes text that doesn't get evaluated 
helpful for multiline comments'''

x = 5       # variable declaration, don't declare types
y = 7       # no semicolons either

z = y * x + 3.5     # z is now a double b/c of the 3.5
print(z)            # prints to console, automatically adds newline char
print("z equals %f" % z)    # formatting

myStr = "This is a string"
myStr2 = "This will concatenate" + " both strings together"

myStr2 += ", yay!"  #appends to current string
                    #there are no chars, a char is a string of size 1
print(myStr2[3])    #prints the ith element of the given string

#python has no arrays, only lists
#indices still work
list1 = [1, 2, 3, 4]
list1.append(5)     #appends value to end of list
print(list1)
list1.append("k")   #lists can have multiple types
print(list1)
list2 = [list1]     #a list of lists
print(list2)
list2 = list1[0:2]  #can specify ranges -> 0 <= x < 2
                    #ranges in python are [ )
                    #can have negative indices, counts from end of list

list3 = [5, 6, 7, 8, 9, 10]
list4 = list3[-3:-1]    #grabs the 8 and 9 -> "slicing", grabbing a range
list4 = list3[-3:]      #grabs the 8, 9, and 10

list4 = list3[-50:]     #actually works!  grabs the furthest left element
                        #that is possible, closest to the -50 value

list3[1:4] = [15, 16]   #replaces the [1, 4) slice with the right hand side
list3[1:4] = []         #removes that slice from list3

#conditionals
if len(list1) == 7:
    print(list1)
else:
    print(list2)

#is keyword - checks if identity is the same
#== checks logical equivalence
#if len(list1) is 7         will work
#if list1 = [0, 1, 2, 3]    will never work, b/c the list1 object is not technically
#                           equivalent to the "thing" [0, 1, 2, 3]

#loops, no whiles
for num in list1:   #goes through entire list once
    print(str(num) + "Kitties~")

#to print out partial list, make a slice, e.g.
for num in list1[0:2]:
    #do things
    print(num)

#prints 4 maows, not 5... b/c remember range is [0, 4)
for num in range(0, 4):
    print("Maow!")
