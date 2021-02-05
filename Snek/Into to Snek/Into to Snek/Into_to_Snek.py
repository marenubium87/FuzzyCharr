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

#defines a dictionary
dict1 = {"cat": 69, "noms": 420, "fluffy": 666} #in format key:value
print(dict1["cat"])     #prints 69
print(dict1)            #prints out entire dictionary with key/value pairs
print(dict1.get("noms"))    #prints 420
print(dict1.keys())     #prints out "cat" "noms" "fluffy"

#dictionary keys can be numbers, strings... but ideally make all keys one type
#and all values another type, even though python will support mixed types

#valid!
for key in dict1.keys():
    print(key)

#can also do
if "cat" in dict1.keys():
    print("I'm a kitty")

#be aware that this is a thing
for key, value in dict1.items():
    print(key, value)

#be very careful, for set notation uses {} just as dictionary does
#set contains only unique items, will not print second "steak"
set1 = {"steak", "lamb", "chicken", "steak"}
print(set1)

#reversed creates an iterator, not a new list
newList = [1, 2, 3, 4]
for items in reversed(newList):
    print(items)

#sorted however will create a new list
for items in sorted(newList):
    print(items)

#tuples ~ like pared down structs
#immutable, but a tuple can contain lists whose contents are mutable
person = ("John", 1234567890, "Fluffy")
print(person[0])    #John

#functions
def showKitties(myKittyCollection):
    for key, value in myKittyCollection.items():
        print(key)
    return "All done"
print(showKitties(dict1))

#libraries and things
import math
print(math.ceil(6.9))

#can also do 
#import math as kittens
#print(kittens.ceil(6.9))
