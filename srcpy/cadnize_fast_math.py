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
    if "fast-math" in l and not "CADNA" in l:
       l = l.replace('\n', '')
       l = l.replace(l, "#" + l + ' #removed for CADNA \n')
       changes += 1

    lines[i] = l
    
    i=i+1
print(f"Changes in: {fileName:<30}\t{changes}")
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