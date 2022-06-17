
try:
    x = 5
    x / 0
except ZeroDivisionError as err:
    print(err)