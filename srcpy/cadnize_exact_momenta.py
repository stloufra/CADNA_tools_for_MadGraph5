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


#Set the precision of momenta String to insert:
momentaString ='    //Set the precision of momenta to be exact\n    for(int i = 0; i < 4;i++){\n        for (int j = 0; j < npar; j++){\n            int precision = M_ACCESS::kernelAccessIp4Ipar( momenta, i, j ).nb_significant_digit();\n            // std::cout<<"i: "<<i<<" j: "<<j<<" Momenta precision: "<< precision;\n            M_ACCESS::kernelAccessIp4Ipar( momenta, i, j ) = fptype(double(M_ACCESS::kernelAccessIp4Ipar( momenta, i, j ).getx()));\n//            M_ACCESS::kernelAccessIp4Ipar( momenta, i, j ) = simParamsList[0].momenta[j].p[i];\n            // std::cout<<" Momentum: "<<M_ACCESS::kernelAccessIp4Ipar( momenta, i, j )<<"\\n";\n        }\n    }\n'

i=0
inFunctQ = False
secondReturnQ = False
for l in lines:
    if "ramboGetMomentaFinal" in l:
        inFunctQ = True
    if inFunctQ and "//Set the precision of momenta to be exact" in l:
        inFunctQ = False
        #check if load from file or exact
        if len(lines)<i+7 or ('simParamsList[0].momenta[j].p[i];' in lines[i+6] and ('//' in lines[i+5]) == True):
            print("Changing from reading to exact momenta")
            #comment reading
            lines[i+6] = lines[i+6].replace("M_ACCESS::kernelAccessIp4Ipar( momenta, i, j ) = simParamsList[0].momenta[j].p[i];", "// M_ACCESS::kernelAccessIp4Ipar( momenta, i, j ) = simParamsList[0].momenta[j].p[i];")
            changes += 1
            #uncomment setting to exact
            lines[i+5] = lines[i+5].replace("// ","")
            changes += 1
            
    if inFunctQ and "return;" in l:
        secondReturnQ =True
    if inFunctQ and secondReturnQ and "return;" in lines[i+1]:
        lines.insert(i+1, momentaString)
        changes += momentaString.count('\n')
        inFunctQ = False
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