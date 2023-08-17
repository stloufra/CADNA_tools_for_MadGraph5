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
    if "$(LIBFLAGS)" in l:
        # print("Changing the line:\n",l)
        l = l.replace(" $(LIBFLAGS)", "")
        l = l.replace("\n", "")
        l = l + " $(LIBFLAGS)\n"
        changes += 1
        
        lines[i] = l
    
    if "$(LINKLIBS)" in l and ("; fi" in l ) == False:
        # print("Changing the line:\n",l)
        l = l.replace(" $(LINKLIBS)", "")
        l = l.replace("\n", "")
        l = l + " $(LINKLIBS)\n"
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