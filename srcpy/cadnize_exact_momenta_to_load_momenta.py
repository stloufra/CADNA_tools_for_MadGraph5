#inserts include
#inserts reading momenta from file
#uncomments line where momenta are set to red momenta if necessary
#comments setting momenta to be exact if necessary

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


#insert #include "include/read_momenta.h" after #include "CPPProcess.h"
i=0
for l in lines:
    if '#include "CPPProcess.h"' in l:        
        if ('#include "include/read_momenta.h"' in lines[i+1]) == False:
            lines.insert(i+1, '#include "include/read_momenta.h"\n')   
            changes += 1
        break
    i=i+1


insert_readfile = '\t\t//read momenta from file\n\t\tconst std::string filename = "../../src/include/input_momenta.txt";\n\t\tstd::vector<Sim_params> simParamsList = readSim_paramsFromFile(filename);\n'

i=0
for l in lines:
    if "// nothing else to do in this event if all particles are massless (nm==0)" in l and ("//read momenta from file" in lines[i+1]) == False:
        lines.insert(i+1, insert_readfile)
        changes += insert_readfile.count('\n')
    if "//Set the precision of momenta to be exact" in l:
        #check if load from file or exact
        if 'simParamsList[0].momenta[j].p[i];' in lines[i+6] and ('//' in lines[i+6]) == True:
            print("Changing from exact to reading momenta")
            #comment exact
            lines[i+5] = lines[i+5].replace("M_ACCESS::kernelAccessIp4Ipar( momenta, i, j ) = fptype(double(M_ACCESS::kernelAccessIp4Ipar( momenta, i, j ).getx()));", "// M_ACCESS::kernelAccessIp4Ipar( momenta, i, j ) = fptype(double(M_ACCESS::kernelAccessIp4Ipar( momenta, i, j ).getx()));")
            #uncomment reading
            lines[i+6] = lines[i+6].replace("// ","")
               
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


#copy read_momenta.h to ../../src/include
import os

#get path to read_momenta.h
if len(sys.argv) > 2:
    fileName = sys.argv[2]
else:
    exit("No read_momenta.h file name given")

#if the path does not exist, create it

if not os.path.exists("../../src/include"):
    os.makedirs("../../src/include")
    
#read lines
f = open(fileName, "r")
lines = f.readlines()
f.close()

#Create a file with the same permissions as the old file
tempfileName = "../../src/include/read_momenta.h"
f = open(tempfileName, "w")
f.writelines(lines)
f.close()
 
#Copy the file permissions from the old file to the new file
copymode(fileName, tempfileName)


