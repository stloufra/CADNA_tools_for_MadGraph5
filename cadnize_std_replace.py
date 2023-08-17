#file from argument:
import sys
if len(sys.argv) > 1:
    fileName = sys.argv[1]
else:
    exit("No file name given")
#move every "$(LIBFLAGS)" to the end of the line in the file test.mak
f = open(fileName, "r")
lines = f.readlines()
f.close()

#std::functions
stds=[]

changes = 0

i=0
for l in lines:
    
    if "fp_show_class( me )" in l :
        if lines[i][:2] != "//":
            lines[i] = "//"+l
            l=lines[i]
            changes += 1 
            
    if  "isnormal" in l:
        if lines[i][:2] != "//":
            lines[i] = "//"+l
            l=lines[i]
            changes += 1 
            
    if "fp_show_class( const fptype& fp )" in l:
        #comment 9 more lines
        for j in range(9):
            if lines[i+j+2][:2] != "//":
                lines[i+j+2] = "//"+lines[i+j+2]
        if not "return" in lines[i+2+9] :
            lines.insert(i+2+9, "return \"unknown\";\n")
            changes += 1 
            
    
    if "stats.re" in l and not "double" in l:
        #paste (double) after "="
        s = l.find("=")
        l = l[:s+2]+" (double)"+l[s+1:]
        lines[i] = l
        changes += 1 
    
    if ("fptype OM3 =" in l or "fptype OM2 =" in l or "fptype OM1 =" in l) and not "(fptype)" in l:
        #paste (fptype) after "="
        s = l.find("=")
        l = l[:s+2]+" (fptype)"+l[s+1:]
        
        s = l.find(": 0.")
        l = l[:s+2]+" (fptype)"+l[s+1:]
        
        lines[i] = l
        changes += 1
        
        
    if "std::" in l and ("scientific" in l) == False:
        #find the first occurence of std::
        s = l.find("std::") # this returns the index of the first character of the string
        #find the function name - string beetween std:: and (
        s1 = l.find("(", s)
        if(s1 == -1 or l[s:s1].find("<<") != -1 or l[s:s1].find(" ") != -1):
            i=i+1
            continue
        print("Found std::function: ", l[s:s1])
        #check if the function is already in the list
        if l[s:s1] not in stds:
            stds.append(l[s:s1])
        
        # print("Changing the line:\n",l)
        l = l.replace("std::", "")
        lines[i] = l
        changes += 1 
    i=i+1

print(f"Changes in: {fileName} ", changes)
        

#insert using std::function after the last include
i=0
for l in lines:
    if "#include" in l:
        lastInclude = i
    i=i+1
    
i=1
for s in stds:
    lines.insert(lastInclude+i, "using "+s+";\n")
    print("Inserting using "+s+" after the last include. line:", lastInclude+i)
    i=i+1


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