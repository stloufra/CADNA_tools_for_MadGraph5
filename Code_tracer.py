#%%
import sys
#open file gdb.out or one provided in argument
if len(sys.argv) > 1:
    f = open(sys.argv[1], 'r')
else:
    f = open('gdb.out', 'r')

#read file
lines = f.readlines()
#close file
f.close()
#count the number of times "hit breakpoint" was called
#create a list of indexes where "hit breakpoint" was called
breakpoint_lines = [i for i in range(len(lines)) if lines[i].find("Breakpoint") != -1][1:]
print("Breakpoints:", len(breakpoint_lines))
# print(breakpoint_lines)


#create a 2d map of file names and line numbers
#key: file name
#value:list of line numbers and number of times they were called and operator name
files = {}

#to display the line in "no operator found" file
lines_no_operator_found = 0

# create a map of possible operators:
# key: operator name
# value: number of times it was called
op = {}
foundQ = False
#find operator in the form of "operator+(...)" or "operator-(...)" etc. in beetween breakpoint lines
for i in range(len(breakpoint_lines)):
    if i == len(breakpoint_lines)-1:
        next_index = len(lines)-1
    else:
        next_index = breakpoint_lines[i+1]
        
    operator = "undefined"
    for l in lines[breakpoint_lines[i]: next_index]:
        if l.find("operator") != -1 and l.find("cadna") != -1:
            #print characters between "operator" and "("
            operator = l[l.find("operator")+8:l.find("(")]
            op[operator] = op.get(operator, 0) + 1
            foundQ = True
        if foundQ == False and l.find("std::") != -1:
            operator = l[l.find("std::")+5:l.find("(")]
            op[operator] = op.get(operator, 0) + 1
            foundQ = True
        if foundQ == False and l.find(" pow ") != -1:
            operator = "pow"
            op[operator] = op.get(operator, 0) + 1
            foundQ = True
            
        if l.find(" at ") != -1 and l.find("#") != -1 and l.find("cadna") == -1:
            file = l[l.rfind(" at ")+4:l.rfind(":")]
            line = l[l.rfind(":")+1:-1]
            files[file] = files.get(file, {}) #Create a set of lines for each file
            #each line has a number of times it was called and an operator name
            files[file][line] = files[file].get(line, [0, {}]) #initialize the number of times the line was called to 0 and the operator name to the one found
            files[file][line][0] += 1 #increment the number of times the line was called
            files[file][line][1][operator] = files[file][line][1].get(operator, 0) + 1
            
            #save the operator name
            
            
            
            
    if not foundQ:
        print("no operator found in ","gdb_no_operator_found.txt:", lines_no_operator_found,sep = "")
        #Save the lines where no operator was found to a file called "gdb_no_operator_found.txt"
        f = open("gdb_no_operator_found.txt", "a")
        f.write("no operator found between lines "+str(breakpoint_lines[i])+" and "+str(next_index)+"\n")
        for l in lines[breakpoint_lines[i]: next_index]:
            f.write(l)
        f.write("\n")
        f.write("\n")
        lines_no_operator_found += 3+(next_index-breakpoint_lines[i])
    foundQ = False
    
    

#sort operators by number of times they were called
op = sorted(op.items(), key=lambda x: x[0], reverse=True)
#print in a nicer way
print("operators:")
for o in op:
    print(o[0], ":", o[1])
#show sum of all operators
print("\noperators found:", sum([o[1] for o in op]))


#sort the lines in each file by number of times they were called
# print(files)

#sort files in line numbers
files_sorted = {}
for f in files:
    files_sorted[f] = sorted(files[f].items(), key=lambda x: int(x[0]), reverse=False)

    
# print(files_sorted)
for f in files_sorted:
    content = files_sorted[f]
    # print(content) #  list of (line, [sum, {op:times, op:times}])   ex. [('173', [16, {'- ': 16}]), ('186', [24, {'- ': 16, 'pow': 8}])]
        
    print(f, "  sum:", sum([int(l[1][0]) for l in content]), sep="")
    for l in content: #l -> lines and operators: 
        #print <file>:<line> x<sum> -> (line, [sum, {op:times, op:times}])
        print("\t",f'{f+":"+l[0]:<30}' ,"\t x", l[1][0],sep="",end="\t -> ")
        for o in l[1][1]: # o - operators
            print("\t",o, ": ", l[1][1][o],sep="",end=" ")
        print()
    