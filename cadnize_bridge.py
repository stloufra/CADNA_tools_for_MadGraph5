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


print_momenta_string = '\t\t//For CADNA analysis\n\t\tfor(unsigned int ievt = 0 ; ievt< m_nevt; ievt++)\n\t\t{ \n\t\t  // Display momenta\n\t\t    std::cout << "Momenta:" << std::endl;\n\t\t    for( int ipar = 0; ipar < CPPProcess::npar; ipar++ )\n\t\t    {\n\t\t      // NB: \'setw\' affects only the next field (of any type)\n\t\t      std::cout << std::scientific // fixed format: affects all floats (default precision: 6)\n\t\t                << std::setw( 4 ) << ipar + 1\n\t\t                << std::setw( 14 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( m_hstMomentaC.data(), ievt, 0, ipar )\n\t\t                << std::setw( 14 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( m_hstMomentaC.data(), ievt, 1, ipar )\n\t\t                << std::setw( 14 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( m_hstMomentaC.data(), ievt, 2, ipar )\n\t\t                << std::setw( 14 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( m_hstMomentaC.data(), ievt, 3, ipar )\n\t\t                << std::endl\n\t\t									<< std::setw( 14 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( m_hstMomentaC.data(), ievt, 0, ipar ).nb_significant_digit()\n\t\t									<< std::setw( 14 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( m_hstMomentaC.data(), ievt, 1, ipar ).nb_significant_digit()\n\t\t									<< std::setw( 14 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( m_hstMomentaC.data(), ievt, 2, ipar ).nb_significant_digit()\n\t\t									<< std::setw( 14 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( m_hstMomentaC.data(), ievt, 3, ipar ).nb_significant_digit()\n\t\t									<< std::endl\n\t\t                << std::defaultfloat; // default format: affects all floats\n\t\t    }\n\t\t  std::cout << std::string( SEP79, \'-\' ) << std::endl;\n\t\t  std::cout << " Matrix element = " <<  m_hstMEs.data()[ievt] << " GeV^"  << std::endl;\n\t\t  std::cout << " Matrix element number of sig dig = " <<  m_hstMEs.data()[ievt].nb_significant_digit() << std::endl;\n\t\t  std::cout << std::string( SEP79, \'-\' ) << std::endl;\n\t\t}\n '

addeQ = False
changes = 0

i=0
for l in lines:
    if '#include "MemoryBuffers.h"' in l:
        if not "#include <cadna.h>" in lines[i+1] :
            lines.insert(i+1, "#include <cadna.h>\n#define SEP79 79\n #include <iomanip>")
            changes += 1
            print('Added #include <cadna.h> after #include "MemoryBuffers.h" in file '+fileName)
    
    if 'flagAbnormalMEs( m_hstMEs.data(), m_nevt );' in l:
        if not '//For CADNA analysis' in lines[i+1] :
            lines.insert(i+1, print_momenta_string)
            changes += 1
            print('Added print_momenta_string after flagAbnormalMEs( m_hstMEs.data(), m_nevt ); in file '+fileName)
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