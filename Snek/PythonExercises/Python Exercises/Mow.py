f1 = ["mow "]
f2 = ["mow "]

iMax = 8

def capitalizeFirstForPrint(x):
    #Capitalizes first mow in list x, prints list, then reverts.

    """
    Usage:  Given x, a list consisting of "mow "s, capitalizes the first mow,
    prints out the list, then uncapitalizes the "mow" for further editing.
    """

    x[0] = "Mow "
    print(x)
    x[0] = "mow "


for i in range(iMax):
    print(i)
    if(i == 0):
        capitalizeFirstForPrint(f1)
    elif(i == 1):
        capitalizeFirstForPrint(f2)
    elif(i % 2 == 0):
        for x in f2:
            f1.append(x)
        capitalizeFirstForPrint(f1)
    else:
        for x in f1:
            f2.append(x)
        capitalizeFirstForPrint(f2)

