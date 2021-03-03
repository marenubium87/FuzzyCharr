from functools import reduce

myDict = {'Barnes & Noble':{'Mon':30,'Wed':100,'Sat':200}, 
          'Etsy':{'Mon':50,'Tue':20,'Wed':25,'Fri':30}, 
          'Sur La Table':{'Tue':60,'Wed':100,'Thu':30}, 
          'Williams-Sonoma':{'Tue':100,'Thu':50,'Sat':20}} 



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

myTotal = sumSales(myDict)

for keys, vals in myTotal.items():
    print(keys, vals)

log = [
    {'Barnes & Noble':{'Mon':30,'Wed':100,'Sat':200},
     'Etsy':{'Mon':50,'Tue':20,'Wed':25,'Fri':30}, 
     'Sur La Table':{'Tue':60,'Wed':100,'Thu':30}, 
     'Williams-Sonoma':{'Tue':100,'Thu':50,'Sat':20}}, 

    {'Williams-Sonoma':{'Mon':25}, 'Etsy':{'Thu':40, 'Fri':50}, 
    'Sur La Table':{'Mon':100,'Sat':30}}, 

    {'Barnes & Noble':{'Sun':88}, 
     'Etsy':{'Fri':55}, 
     'Sur La Table':{'Mon':40}, 
     'Williams-Sonoma':{'Sat':35}} 
    ] 

anotherTotal = myTotal.copy()
myTotal.pop("Tue")

#print(myTotal)
#print(anotherTotal)

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

d3 = combine(myTotal, anotherTotal)
print(d3)

refDict = {'Fri': 135,'Mon':245,'Sat':285,'Sun': 88,'Thu': 120,'Tue':180,'Wed':225} 

def sumSalesN(L):
   x = map(sumSales, L)
   y = reduce(combine, x)
   return y

print(sumSalesN(log))
print(refDict)


