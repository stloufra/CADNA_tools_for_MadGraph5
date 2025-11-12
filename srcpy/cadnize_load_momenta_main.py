#file from argument:
import sys
if len(sys.argv) > 1:
    fileName = sys.argv[1]
else:
    exit("No file name given")

if len(sys.argv) > 2:
    mommentaFileName = sys.argv[2]
else:
    print("Using default momenta file name: gdb_run_output_float-O3_1.out")
    mommentaFileName = "gdb_run_output_float-O3_1.out"
#move every "$(LIBFLAGS)" to the end of the line in the file test.mak
f = open(fileName, "r")

#read lines
lines = f.readlines()
f.close()
changes = 0


#Set the precision of momenta String to insert:
momentaString ='''
//CADNA LOADING MOMENTA
auto in_params = readSim_paramsFromFile("''' + mommentaFileName + '''");
for( unsigned int ievt = 0; ievt < nevt; ++ievt ) // Loop over all events in this iteration
{
  if( verbose )
  {
    std::cout << "Momenta casting for event: " << ievt << std::endl;


    for( int ipar = 0; ipar < CPPProcess::npar; ipar++ )
    {
		double mass = in_params[ievt].momenta[ipar].p[0];
		double p1 = in_params[ievt].momenta[ipar].p[1];
		double p2 = in_params[ievt].momenta[ipar].p[2];
		double p3 = in_params[ievt].momenta[ipar].p[3];
		
      // NB: 'setw' affects only the next field (of any type)
	  const int ndigits = std::numeric_limits<double>::digits10;
      std::cout << std::scientific // fixed format: affects all floats (default precision: 6)
				<< std::setprecision( ndigits )
                << std::setw( 4 ) << ipar + 1
                << std::setw( ndigits + 8 ) << mass
                << std::setw( ndigits + 8 ) << p1
                << std::setw( ndigits + 8 ) << p2
                << std::setw( ndigits + 8 ) << p3
                << std::endl;

		MemoryAccessMomenta::ieventAccessIp4Ipar( hstMomenta.data(), ievt, 0, ipar ) = static_cast<fptype>( mass ) ;
		MemoryAccessMomenta::ieventAccessIp4Ipar( hstMomenta.data(), ievt, 1, ipar ) = static_cast<fptype>( p1 ) ;
		MemoryAccessMomenta::ieventAccessIp4Ipar( hstMomenta.data(), ievt, 2, ipar ) = static_cast<fptype>( p2 ) ;
		MemoryAccessMomenta::ieventAccessIp4Ipar( hstMomenta.data(), ievt, 3, ipar ) = static_cast<fptype>( p3 );

	  std::cout << std::scientific
				<< std::setw( ndigits + 8 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 0, ipar ).nb_significant_digit()
				<< std::setw( ndigits + 8 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 1, ipar ).nb_significant_digit()
				<< std::setw( ndigits + 8 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 2, ipar ).nb_significant_digit()
				<< std::setw( ndigits + 8 ) << MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 3, ipar ).nb_significant_digit()
				<< std::endl
                << std::defaultfloat; // default format: affects all floats
    }
    std::cout << std::string( SEP79, '-' ) << std::endl;
  }
}
'''

Fourmomentatring = '''        double mass = in_params[ievt].momenta[ipar].p[0];
		double p1 = in_params[ievt].momenta[ipar].p[1];
		double p2 = in_params[ievt].momenta[ipar].p[2];
		double p3 = in_params[ievt].momenta[ipar].p[3];
'''
#double mass = MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 0, ipar );
#double p1 = MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 1, ipar );
#double p2 = MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 2, ipar );
#double p3 = MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 3, ipar );

i=0
j=0
CastIn = False
LoadIn = False
for l in lines:
    if '#include "mgOnGpuConfig.h"' in l:
        if not  '#include "read_momenta.h"' in lines[i+1] :
            lines.insert(i+1, '#include "read_momenta.h"\n')
            changes += 1

    if "//CADNA CASTING TO MAKE EXACT" in l:
        lines.pop(i)
        lines.insert(i, "//CADNA LOADING MOMENTA\n")
        CastIn = True
        print(f"Casting exact momenta is in the {fileName}")
        lines.insert(i+1, f'auto in_params = readSim_paramsFromFile("{mommentaFileName}");\n')

    if "//CADNA LOADING MOMENTA" in l and not CastIn:
        LoadIn = True
        print(f"Loading exact momenta already in the {fileName}")

    if CastIn and 'double mass = MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 0, ipar );' in l:
        lines.pop(i)
        lines.pop(i)
        lines.pop(i)
        lines.pop(i)
        lines.insert(i, Fourmomentatring)
        changes += 4

    if not LoadIn and not CastIn and "// *** STOP THE OLD-STYLE TIMER FOR RAMBO ***" in l:
        inFunctQ = True
        lines.insert(i, momentaString)
        LoadIn = True

        changes += 1

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
