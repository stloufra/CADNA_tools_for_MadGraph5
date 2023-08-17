#file from argument:
import sys
if len(sys.argv) > 1:
    fileName = sys.argv[1]
else:
    exit("No file name given")
#move every "$(LIBFLAGS)" to the end of the line in the file test.mak
f = open(fileName, "r")

#read lines
lines = f.readlines()
f.close()
changes = 0 

i=0
for l in lines:
    if "constexpr fptype " in l or "constexpr fptype2 " in l:
        # print("Changing the line:\n",l)
        l = l.replace("constexpr", "const")
        changes += 1
        # print("To:\n",l)
        lines[i] = l
    if "TriangularNormalizedColorMatrix" in l and "const" in l:
        # print("Changing the line:\n",l)
        changes += 1
        l = l.replace("constexpr ", "")
        lines[i] = l
    if "static constexpr fptype energy" in l or "static const fptype energy" in l:
        # print("Changing the line:\n",l)
        l = l.replace("static constexpr ", "")
        l = l.replace("static const ", "")
        changes += 1
        lines[i] = l
    if "volatile fptype " in l:
        # print("Changing the line:\n",l)
        l = l.replace("volatile", "const")
        changes += 1
        lines[i] = l
    if "volatile constexpr fptype " in l:
        # print("Changing the line:\n",l)
        l = l.replace("volatile constexpr", "const")
        changes += 1
        lines[i] = l
    i=i+1
        
print("Changes in: "+fileName+"\t\t"+str(changes))
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