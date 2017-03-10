
def getListTerminals(lin):
    string = ""
    for i, el in enumerate(lin):
        if i < (len(lin) - 1):
            string += ("\"" + el +"\", ")
        elif i == (len(lin) - 1):
            string += "\"" + el + "\""
    return string

strr = raw_input("Input string: ")
listt = strr.split(" ")
print "{" + getListTerminals(listt) + "}"


