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
cadnaHin = False
undefSIMD = False
for l in lines:
    if "cadna.h" in l:
       cadnaHin = True
    if "undef MGONGPU_CPPSIMD //for CADNA" in l:
       undefSIMD = True

for l in lines:
    if not cadnaHin and ("namespace mgOnGpu" in l):
        lines.insert(i, "#include \"cadna.h\"\n")
        changes += 1
        cadnaHin = True
    if not undefSIMD and ("#define mgDebugDeclare()" in l):
        lines.insert(i-1, "#undef MGONGPU_CPPSIMD //for CADNA\n")
        changes += 1
        undefSIMD = True

    if "typedef" in l and ("fptype" in l or "fptype2" in l):
        if not "_st" in l:
            lines[i] = l.replace("float", "float_st")
            lines[i] = l.replace("double", "float_st")
            changes += 1
        
    i=i+1

print(f"Changes in: {fileName:<30}\t{changes}")

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