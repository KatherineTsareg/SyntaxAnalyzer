import re
from pprint import *

def getListTable(table):
    table_list = []
    for line in table:
        
        line_list = []
        start_set = []
        while not (line[0] == '0' or line[0] == '1'):
            start_set.append(line[0])
            line = line[1 : ]
        line_list.append(start_set)
        for el in line:
            line_list.append(el)
        if (len(line_list) == 6):
            table_list.append(line_list)
        else:
            print "ERROR!\n"
    return table_list

def getListTerminals(lin):
    string = ""
    for i, el in enumerate(lin):
        if i < (len(lin) - 1):
            string += ("\"" + el +"\", ")
        elif i == (len(lin) - 1):
            string += "\"" + el + "\""
    return string
    
def getAthomString(l):
    strr = "{{" + getListTerminals(l[0]) + "}," + l[1] + "," + l[2] + "," +  l[3] + "," +  l[4] + "," +  l[5] + "},\n"
    return strr

def setStringTable(table):
    table_list = getListTable(table)
    list_rows = "{\n"
    for line in table_list:
        list_rows += getAthomString(line)
    return list_rows + "}"

tableFile = open("xlxsTable.txt", "r")
fin = open("LL1_table.txt", "w")

table = tableFile.read()

a = table.split("\n")
reloadTable = []
for line in a:
    reloadTable.append(line.split(" "))

fin.write(setStringTable(reloadTable))

tableFile.close()
fin.close()
