#file from argument:
import sys
if len(sys.argv) > 1:
    fileName = sys.argv[1]
else:
    exit("No file name given")
if len(sys.argv) > 2:
    if sys.argv[2] == "0":
        print("Cadna mode 0 cadna wont check for instabilities.")
        cadnaMode = int(sys.argv[2])
    elif sys.argv[2] == "-1":
        print("Cadna mode 1 cadna will check for all instabilities.")
        cadnaMode = int(sys.argv[2])
    else:
        print("Unknown cadna mode given assuming full analysis")
        cadnaMode = -1
else:
    print("No cadnaMode given assuming full analysis")
    cadnaMode = -1

#move every "$(LIBFLAGS)" to the end of the line in the file test.mak
f = open(fileName, "r")

#read lines
lines = f.readlines()
f.close()


print_momenta_string = '\t\t\t\t\t\t\t\t\t\t<< std::setw( 14 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 0, ipar ).nb_significant_digit()\n\t\t\t\t\t\t\t\t\t\t<< std::setw( 14 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 1, ipar ).nb_significant_digit()\n\t\t\t\t\t\t\t\t\t\t<< std::setw( 14 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 2, ipar ).nb_significant_digit()\n\t\t\t\t\t\t\t\t\t\t<< std::setw( 14 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 3, ipar ).nb_significant_digit()\n\t\t\t\t\t\t\t\t\t\t<< std::endl\n'
addeQ = False
changes = 0

i=0
for l in lines:
    if "#include <unistd.h>" in l:
        if not "#include <cadna.h>" in lines[i+1] :
            lines.insert(i+1, "#include <cadna.h>\n")
            print("Added #include <cadna.h> after #include <unistd.h>")
            changes += 1
    #putting cadna_init(-1); in main
    if "main( int argc, char** argv )" in l:
        if not "cadna_init" in lines[i+2] :
            changes += 1
            lines.insert(i+2, f"cadna_init({cadnaMode});\n")
            # print("Added cadna_init(-1); after main( int argc, char** argv )")
            changes += 1
            lines.insert(i+3, "double avg_matrixElementPrecision = 0;\n")
            # print("Added double avg_matrixElementPrecision = 0; after cadna_init(-1);")
            changes += 1
            lines.insert(i+4, "int avg_matrixElementPrecision_n = 0;\n")
            # print("Added int avg_matrixElementPrecision_n = 0; after cadna_init(-1);")
    
    #putting cadna_end(); before return in main
    if "return 0;" in l:
        if not "cadna_end();" in lines[i-1] and not "cadna_end();" in lines[i-2]  :
            changes += 1
            lines.insert(i, "  cadna_end();\n")
            # print("Added cadna_end(); before return 0;")
    
    #comment out:
    if "std::cout << \".\";" in l:
        if lines[i][:2] != "//":
            lines[i] = "//"+l
            print("Commented out std::cout << \".\";")
            changes += 1
            
    if 'std::cout << " Matrix element = " << MemoryAccessMatrixElements::ieventAccessConst( hstMatrixElements.data(), ievt )' in l:
        if not "Matrix element number of sig dig =" in lines[i+2] :
            lines.insert(i+2, '        std::cout << " Matrix element number of sig dig = " << MemoryAccessMatrixElements::ieventAccessConst( hstMatrixElements.data(), ievt ).nb_significant_digit()<< " "<<std::endl;\n')
            changes += 1
        
        if not ("avg_matrixElementPrecision += MemoryAccessMatrixElements::ieventAccessConst( hstMatrixElements.data(), ievt )" in lines[i+4] or "avg_matrixElementPrecision += MemoryAccessMatrixElements::ieventAccessConst( hstMatrixElements.data(), ievt )" in lines[i+5]) :
            lines.insert(i+4, "             avg_matrixElementPrecision += MemoryAccessMatrixElements::ieventAccessConst( hstMatrixElements.data(), ievt ).nb_significant_digit();\n")
            lines.insert(i+5, "             avg_matrixElementPrecision_n++;\n")
            lines.insert(i+13, 'if(verbose){\nstd::cout<<"avg_matrixElementPrecision = "<<avg_matrixElementPrecision<<std::endl;\nstd::cout<<"avg_matrixElementPrecision_n = "<<avg_matrixElementPrecision_n<<std::endl;\nstd::cout<<"(1)/(2) = "<<avg_matrixElementPrecision/avg_matrixElementPrecision_n<<std::endl;}\n')
            changes += 1
            changes += 1
            changes += 4
            print("Added avg matrix element precision calculation and visualization")   
    
    #add momentum precision cout
    if 'std::setw( 14 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 3, ipar )' in l and ('.nb_significant_digit()' in l )==False and ('.nb_significant_digit()' in lines[i+2] )==False:
        if addeQ==False:
            lines.insert(i+2, print_momenta_string)
            #how many '\n' are in print_momenta_string?
            changes += print_momenta_string.count('\n')
            addeQ = True
            print("\n\nAdded momentum precision cout\n\n")
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