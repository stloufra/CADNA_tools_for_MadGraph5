#file from argument:
import sys,re
if len(sys.argv) > 1:
    fileName = sys.argv[1]
else:
    exit("No file name given")
f = open(fileName, "r")
lines = f.readlines()
f.close()

def findOccurrences(text,substr,indexes):
    startposition = 0

    while True:
        i = text.find(substr, startposition)
        if i == -1: break
        indexes.append(i)
        startposition = i + len(substr)

    return indexes

i=0
newlines = []
for l in lines:
    #paste "\n" after every operator (*,/,-,+) but only after "=" in line
    if "=" in l and " * " in l or " / " in l or " + " in l or " - " in l :
        eq = l.find("=")
        comment = l.find("//")
        if comment == -1:
            comment = len(l)-4
        indexes = []
        for o in [" * ", " / ", " - ", " + "]:
            indexes = findOccurrences(l, o, indexes)
        indexes.sort(reverse=True)
        tabs = indexes[-1]
        for i in indexes:
            if i > eq and i < comment:
                l = l[:i+3]+"\n"+(tabs*' ')+l[i+3:]    
        # print(l)
    newlines.append(l)
    i=i+1
        
changes = len(lines)-len(newlines)
print("Changes in: "+fileName+"\t\t"+str(changes),"Expanded equations")
lines = newlines
from tempfile import mkstemp
from shutil import move, copymode
from os import fdopen, remove


#replace old file with new file
tempfileName = fileName+"_temp"
f = open(tempfileName, "w")
f.writelines(lines)
f.close()



#Copy the file permissions from the old file to the new file
copymode(fileName, tempfileName)
#Remove original file
remove(fileName)
#Move new file
move(tempfileName, fileName)