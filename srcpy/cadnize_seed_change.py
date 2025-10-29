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
    
if len(sys.argv) > 2:
    randomQ = sys.argv[2]
    if randomQ == "True" or randomQ == "true" or randomQ == "1" or randomQ == "t" or randomQ == "T" or randomQ == "random":
        randomQ = True
    elif randomQ == "False" or randomQ == "false" or randomQ == "0" or randomQ == "f" or randomQ == "F" or randomQ == "original":
        randomQ = False
else:
    exit("No argumnet given for random seed")
    
#move every "$(LIBFLAGS)" to the end of the line in the file test.mak
f = open(fileName, "r")

#read lines
lines = f.readlines()
f.close()
changes = 0

i=0
import random
#get rand int
rand_num = random.randint(0, 1_000_000)
for l in lines:
    if "const unsigned long long seed = " in l:
        if randomQ == True:
            if (" + " in l) == False:
                #add a random number at the end of the seed before the ;
                lines[i] = l.split(';')[0] + " + "+str(rand_num)+";\n"
            else:
                #change the random number at the end of the seed before the ;
                lines[i] = l.split(' + ')[0] + " + "+str(rand_num)+";\n"
            print("Changing from original to random seed: "+str(rand_num))
        else:
            print("Changing from random to original seed")
            #remove the random number at the end of the seed before the ;
            lines[i] = l.split(' + ')[0] + ";\n"
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


