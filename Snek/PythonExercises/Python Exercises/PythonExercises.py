# Python exercises
# Taken from CptS 355, Spring 2020, Sakire Arslan-Ay

from functools import reduce

# 1. a)

def sumSales(d):
    #Sums up sales from n stores grouped on days of the week.

    """
    Usage:  For a dictionary consisting of key:values as 
    stores:{dictionary consisting of key:values as day, sale amt},
    collects and accumulates all sales from all stores by day
    and returns a dictionary, total, consisting of key:values as
    day:(total sales that day)
    """

    totals = {}
    #cycle through all sales dictionaries
    for sales in d.values():
        #cycle through all days per dictionary
        for day in sales:
            #is that day already accounted for in totals dictionary?
            if day not in totals:
                totals.update({day: sales[day]})
            else:
                totals[day] += sales[day]
    return totals

# 1. b)

def combine(d1, d2):
    #Combines total sales from two dictionaries; Aux function for sumSalesN.

    """
    Usage:  For sales dictionaries d1 and d2 consisting of key:values as
    day:total sales that day, combines total sales corresponding to day
    and returns as another dictionary, d3.  

    Required for sumSalesN which calls reduce on this function
    to "collapse" n dictionaries.
    """
    #include everything from d1
    d3 = d1.copy()
    #add entries from d2
    for day in d2:
        #is the day already represented in d3?
        if day in d3:
            d3[day] += d2[day]
        else:
            d3.update({day:d2[day]})
    return d3

def sumSalesN(L):
    #Sums up a list of dictionaries corresponding to weekly sales.

    """
    Usage:  Given L, a list of dictionaries of the same form as in the
    sumSales function, combines sales values from all dictionaries and 
    returns a dictionary containing the total amount of sales for each
    day of the week.
    """
    #applies sumSales fcn to each entry of L
    x = map(sumSales, L)
    #utilizes user-defined combine fcn to reduce x, a list of dictionaries
    #into a single dictionary
    y = reduce(combine, x)
    return y

# 2. a)

def searchDicts(L, k):
    #Searches a list of dictionaries L for key k in reverse list order.

    #reverse order of searching through list, searches through each dictionary
    for dict in reversed(L):
        #is the key found in the current dictionary?
        if k in dict:
            return dict[k]
    return

# 2. b)

def searchCurrentDict(list, key, index):
    #Searches dictionaries in a list recursively using tuple value at current
    #index to determine next dictionary to search; Aux Function for SearchDicts2
    
    #unpack the tuple at the list[index] position
    (nextIndex, currDict) = list[index]

    #is the key found in the current dictionary?
    if key in currDict:
        return (currDict[key])
    #are we at the index zero dictionary?  if not, search the next dict
    #as prescribed by the value in the current tuple
    elif index > 0:
        return searchCurrentDict(list, key, nextIndex)
    #if we're at the index zero dictionary and still haven't found the key,
    #return None
    else:
        return

def searchDicts2(tL, k):
    #Searches a list of tuples consisting of (index, dict) where index
    #describes the next dictionary to check in the list

    #Use aux function and start at the end of the list
    return searchCurrentDict(tL, k, len(tL) - 1)

# 3.

def busStops(buses, stop):
    #Returns all routes in dictionary buses which contain the given stop

    #Note on syntax:  returns a list [ ]
    #of routes (keys) for all routes (keys) in the buses dictionary,
    #if the stop is found in the list (value) 
    #which is paired with the route (key)
    return [route for route in buses if stop in buses[route]]

# 4.

def palindromes(S):
    #Returns all nontrivial (len > 1) substrings of given str S

    #initialize substring and palindrome list
    subStr = ""
    palindromeList = []

    #i determines the str element to start with
    for i in range(0, len(S)):

        #len(S) + 1 prevents an off-by-one error b/c range
        #doesn't include last element...
        for j in range(i + 1, len(S) + 1):
            
            #and this slice also doesn't include the last element, so
            #the cumulative effect is an off-by-one error without the
            #above fix

            #anyway, take the current slice of the list
            subStr = S[i:j]
            #if the length is greater than one...
            if len(subStr) > 1:
                #is the substring equal to its reverse?
                if subStr == subStr[::-1]:
                    palindromeList.append(subStr)
    #casting as set destroys all duplicates, then re-cast as list
    palindromeList = list(set(palindromeList))
    #alphabetical order as indicated in assignment prompt
    palindromeList.sort()
    return palindromeList

print(palindromes("cabbbaccab"))
