#include <iostream>
#include "src/typeTraits.h"
#include "src/CPPProcess.h"
#include "src/MemoryBuffers.h"
#include "src/read_momenta.h"
#include "src/accesses/MemoryAccessMomenta.h"
#include "src/fillers.h"

int main()
{
    const int nevt = 24;
    HostBufferMomenta hstMomenta(nevt);
    HostBufferMatrixElements hstMe(nevt);
    HostBufferGs hstGs(nevt);
    HostBufferSelectedHelicity hstSelHel(nevt);
    HostBufferCouplings hstCoup(nevt);
    HostBufferRndNumHelicity hstRndHel(nevt);
    HostBufferHelicityMask hstIsGoodHel(CPPProcess::ncomb);

    CPPProcess process( true );
    process.initProc( "../src/Cards/param_card.dat" );

    fillMomentaFromFile("gdb_run_output_float-O3_1.out", hstMomenta, nevt, true);
    fillGs(hstGs.data(), nevt);
    fillRndHel(hstRndHel.data(), nevt);

    computeDependentCouplings(hstGs.data(), hstCoup.data(), nevt);
    sigmaKin_getGoodHel(hstMomenta.data(), hstCoup.data(), hstMe.data(), hstIsGoodHel.data(), nevt);

    const int nGoodHel = sigmaKin_setGoodHel(hstIsGoodHel.data());

    sigmaKin(hstMomenta.data(), hstCoup.data(), hstRndHel.data(), hstMe.data(), hstSelHel.data(), nevt);

    printMEandPreccision(hstMomenta, hstMe, nevt, true);
    std::cout << "Number of good helicities: " << nGoodHel << std::endl;
    return 0;
}
