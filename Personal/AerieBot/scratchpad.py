import re

myVar = bool(re.match("^A wild [a-zA-Z]+\sappears\.", "A wild Drynwyn appears."))
print(myVar)