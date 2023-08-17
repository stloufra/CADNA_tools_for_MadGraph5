#file from argument:
import sys
if len(sys.argv) > 1:
    fileName = sys.argv[1]
else:
    exit("No file name given")
f = open(fileName, "r")

#read lines
lines = f.readlines()
f.close()
changes = 0

i=0
first_amp_fp = len(lines)
for l in lines:
    if 'amp_fp' in l and ('=' in l) == False and ('std::cout' in l) == False and ('//' in l) == False and ('fptype*' in l) == False:
        if i < first_amp_fp:
            first_amp_fp = i
        #find the function name - everything before the <
        function_name = l.split('<')[0]
        
        function_arguments = []
        #find the function arguments - everything between the ()
        function_arguments = l.split('(')[1].split(')')[0].split(',')   
        
        build_line = "\t\t\tfor (int i = 0; i< 12;i++){\n\t\t\t\tstd::cout<<i"
        for j in range(len(function_arguments)-2):
            build_line = build_line + '<<" '+str(j)+': "<<'+ function_arguments[j] + '[i].nb_significant_digit()'
        build_line = build_line + '<<std::endl;\n\t\t\t}\n'
            
            
        
        print(function_name)
        if ('std::cout' in lines[i+1]) == False:
            # print("Inserting cout")
            lines.insert(i+1, '\t\t\tstd::cout<<__LINE__<<" f_name: '+function_name+' precision real: "<<amp_fp[0].nb_significant_digit()<<" precision imag: "<<amp_fp[1].nb_significant_digit();\n')
            lines.insert(i+2, '\t\t\tstd::cout<<" amp_sv real: "<<amp_fp[0]<<" amp_sv imag: "<<amp_fp[1]<<std::endl;\n')
            lines.insert(i+3, build_line) # carefull
            changes += 1
            changes += 1
            changes += build_line.count('\n')
    i=i+1

#insert "End of event" after last amp_fp
if ("std::cout" in lines[first_amp_fp-2]) == False:
    lines.insert(first_amp_fp-1, '\t\t\tstd::cout<<"Event number: "<<ievt0<<std::endl;\n')
    changes += 1
        
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