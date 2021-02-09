# comments are like this


'''Makes text that doesn't get evaluated'''

"""
Multiline Comments
"""


x = 5       # variable declaration, don't declare types
y = 7       # no semicolons either

z = y * x + 3.5     # z is now a double b/c of the 3.5
print(z)            # prints to console, automatically adds newline char
print("z equals %f" % z)    # formatting
print(z, end='')    #won't add newline
print("a", "b", sep = '') #won't add spaces

myStr = "This is a string"
myStr2 = "This will concatenate" + " both strings together" #doesn't add \n or spaces

#variable types int, float, str, list, tuple, dict, bool
#has support for complex numbers too
#x= ["a", "b", "c"]     #list
#x= ("a", "b", "c")     #tuple
#x= {"a" : 1, "b" : 2}     #dict



myStr2 += ", yay!"  #appends to current string
                    #there are no chars, a char is a string of size 1
print(myStr2[3])    #prints the ith element of the given string
print(myStr2)

#txt.strip() clears whitespace from beginning and end
#txt.upper() uppercase
#txt.replace("A", "B") replaces A with B in txt
#txt.split("delim") splits strings into substrings upon instances of delim


#python has no arrays, only lists
#indices still work
list1 = [1, 2, 3, 4]
list1.append(5)     #appends value to end of list
list1.append("k")   #lists can have multiple types
print(list1)
list2 = [list1[0:2], list1[0:2]]     #a list of lists
print(list2)
list2 = list1[0:2]  #can specify ranges -> 0 <= x < 2
                    #ranges in python are [ )
                    #can have negative indices, counts from end of list

list3 = [5, 6, 7, 8, 9, 10]
list4 = list3[-3:-1]    #grabs the 8 and 9 -> "slicing", grabbing a range
list4 = list3[-3:]      #grabs the 8, 9, and 10

list4 = list3[-50:]     #actually works!  grabs the furthest left element
                        #that is possible, closest to the -50 value
print(list4)
list3[1:4] = [15, 16]   #replaces the [1, 4) slice with the right hand side
list3[1:4] = []         #removes that slice from list3
print(list3)

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

#loops
for num in list1:   #goes through entire list once
    print(str(num) + "Kitties~")

x = 0
i = 0
n = 10
while i <= n:
    x = x + i
    i = i + 1
print(x)

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

cubes = []
for x in range(1, 11):
    cubes.append(x * x * x)

print(cubes)

#can also do ~ list comprehensions
#(set comprehension is also a thing, just use {} instead of []
#cubes = [x * x * x for x in range(1, 11)]
#  use \ if need to write a single line onto multiple lines b/c of 80 char limit

#dictionary
#cubes = {x : x * x for x in [1, 2, 3, 4]}

#higher order functions
#map - takes a unary function and a list, and does a transform
def plusOne(x):
    return x + 1

srcList1 = [2, 3, 5, 7, 11, 13]
mapList1 = list(map(plusOne, srcList1))
print(mapList1)
#[3, 4, 6, 8, 12, 14]

#predicate function, returns a bool
def isCat(myString):
    if myString[-3:] == "Cat":
        return True
    else:
        return False

srcList2 = ["moo", "fluffyCat", "steak", "chompCat"]
#filter function, filters based on a predicate fcn (see above)
filterList = list(filter(isCat, srcList2))
print(filterList)
#["fluffyCat", "chompCat"]

#reduce, fold, or accumulate
#actual fcn is called reduce
from functools import reduce

def concatenate(string1, string2):
    return string1 + string2

srcList3 = ["Kitties", " go", " nomz"]
longString = reduce(concatenate, srcList3)
print(longString)
#Kitties go nomz

#anonymous/lambda function/expression
#remember this?
#mapList1 = list(map(plusOne, srcList1))
#can also write as
mapList1 = list(marg_path(lambda x : x + 1, srcList1))
#filterList = list(filter(isCat, srcList2))
#can also write as
filterList = list(filter(lambda string : string[-3:] == "Cat", srcList2))
#longString = reduce(concatenate, srcList3)
#can also write as
longString = reduce(lambda str1, str2 : str1 + str2, srcList3)

