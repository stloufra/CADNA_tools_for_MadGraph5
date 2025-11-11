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
momentaString ='''
//CADNA CASTING TO MAKE EXACT
for( unsigned int ievt = 0; ievt < nevt; ++ievt ) // Loop over all events in this iteration
{
  if( verbose )
  {
    std::cout << "Momenta casting for event: " << ievt << std::endl;


    for( int ipar = 0; ipar < CPPProcess::npar; ipar++ )
    {
		double mass = MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 0, ipar );
		double p1 = MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 1, ipar );
		double p2 = MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 2, ipar );
		double p3 = MemoryAccessMomenta::ieventAccessIp4IparConst( hstMomenta.data(), ievt, 3, ipar );
		
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
i=0
inFunctQ = False
secondReturnQ = False
for l in lines:
    if "//CADNA CASTING TO MAKE EXACT" in l:
        inFunctQ = True
        print(f"Casting exact momenta already in the {fileName}")

    if not inFunctQ and "// *** STOP THE OLD-STYLE TIMER FOR RAMBO ***" in l:
        inFunctQ = True
        lines.insert(i, momentaString)
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
