#include <iostream>
#include "src/boilerplate/typeTraits.h"
#include "src/CPPProcess.h"
#include "src/boilerplate/MemoryBuffers.h"
#include "src/boilerplate/read_momenta.h"
#include "src/accesses/MemoryAccessMomenta.h"
#include "src/boilerplate/fillers.h"

#ifdef __CADNA
#include "src/boilerplate/momentaHandling.h"
#endif

int main(int argc, char* argv[])
{
#ifdef __CADNA
    cadna_init(-1);
#endif

    int nevt = 80000;
    int n_broken = 0;


    std::cout << "nevt = " << nevt << std::endl;

    HostBufferMomenta hstMomenta(nevt);
    HostBufferMatrixElements hstMe(nevt);
    HostBufferGs hstGs(nevt);
    HostBufferSelectedHelicity hstSelHel(nevt);
    HostBufferCouplings hstCoup(nevt);
    HostBufferRndNumHelicity hstRndHel(nevt);
    HostBufferHelicityMask hstIsGoodHel(CPPProcess::ncomb);

    CPPProcess process(true);

    process.initProc("../src/Cards/param_card.dat");
    fillMomentaFromFile("../gdb_run_output_float-O3_1.out", hstMomenta, nevt, false, 8);

   // Momenta sorting

    auto broken = momenta_engine::PickMomenta(hstMomenta, n_broken, nevt, 0.995, 50.0);

    std::cout << "Number of broken events: " << n_broken << std::endl;
    std::cout << "Number of good events: " << (nevt - n_broken) << std::endl;

    typedef HostBuffer<fptype_f, sizePerEventMomenta, HostBufferALIGNED> HostBufferMomenta_f;
    typedef HostBuffer<fptype_d, sizePerEventMomenta, HostBufferALIGNED> HostBufferMomenta_d;

    HostBufferMomenta_f hstMomenta_f(nevt - n_broken);
    HostBufferMomenta_d hstMomenta_d(n_broken);

    momenta_engine::SortMomenta(hstMomenta, hstMomenta_f, hstMomenta_d, broken, nevt);

    /*fillGs(hstGs.data(), nevt);
    fillRndHel(hstRndHel.data(), nevt);

    computeDependentCouplings(hstGs.data(), hstCoup.data(), nevt);
    sigmaKin_getGoodHel(hstMomenta.data(), hstCoup.data(), hstMe.data(), hstIsGoodHel.data(), nevt);

    const int nGoodHel = sigmaKin_setGoodHel(hstIsGoodHel.data());

    sigmaKin(hstMomenta.data(), hstCoup.data(), hstRndHel.data(), hstMe.data(), hstSelHel.data(), nevt);


#ifdef __CADNA
    printMEandPreccision(hstMomenta, hstMe, nevt, true);
    std::cout << "Number of good helicities: " << nGoodHel << std::endl;
    cadna_end();
#endif*/
    return 0;
}
