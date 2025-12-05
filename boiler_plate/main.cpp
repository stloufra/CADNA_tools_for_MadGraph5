#include <iostream>
#include "src/boilerplate/typeTraits.h"
#include "src/CPPProcess.h"
#include "src/boilerplate/MemoryBuffers.h"
#include "src/boilerplate/read_momenta.h"
#include "src/accesses/MemoryAccessMomenta.h"
#include "src/boilerplate/fillers.h"

#ifdef __CADNA
#include "src/boilerplate/repair_momenta.h"
#endif

int main(int argc, char* argv[])
{
#ifdef __CADNA
    cadna_init(-1);
#endif

    int nevt;
    if (argc == 1)
        nevt = 24;
    else
        nevt = std::stoi(argv[1]);

    std::cout << "nevt = " << nevt << std::endl;

    HostBufferMomenta hstMomenta(nevt);
    HostBufferMatrixElements hstMe(nevt);
    HostBufferGs hstGs(nevt);
    HostBufferSelectedHelicity hstSelHel(nevt);
    HostBufferCouplings hstCoup(nevt);
    HostBufferRndNumHelicity hstRndHel(nevt);
    HostBufferHelicityMask hstIsGoodHel(CPPProcess::ncomb);

    CPPProcess process(true);

#if defined (__PRO__)
    process.initProc("src/Cards/param_card.dat");
    fillMomentaFromFile("gdb_run_output_float-O3_1.out", hstMomenta, nevt, false, 3);
#else
    process.initProc("../src/Cards/param_card.dat");
    fillMomentaFromFile("../gdb_run_output_float-O3_1.out", hstMomenta, nevt, false, 3);
//    for (int i = 0; i < 100; ++i)
//    momenta_reparator::BoostMomenta(hstMomenta, nevt);
#endif

    fillGs(hstGs.data(), nevt);
    fillRndHel(hstRndHel.data(), nevt);

    computeDependentCouplings(hstGs.data(), hstCoup.data(), nevt);
    sigmaKin_getGoodHel(hstMomenta.data(), hstCoup.data(), hstMe.data(), hstIsGoodHel.data(), nevt);

    const int nGoodHel = sigmaKin_setGoodHel(hstIsGoodHel.data());

    sigmaKin(hstMomenta.data(), hstCoup.data(), hstRndHel.data(), hstMe.data(), hstSelHel.data(), nevt);

#if defined (__PRO__)
    PROMISE_CHECK_ARRAY(hstMe.data(), nevt);
#endif

#ifdef __CADNA
    printMEandPreccision(hstMomenta, hstMe, nevt, true);
    std::cout << "Number of good helicities: " << nGoodHel << std::endl;
    auto res = convert_to_array(hstMe, nevt);
    //for (auto a : res) std::cout << a.nb_significant_digit() << std::endl;
    //for (int ievt = 0; ievt < nevt; ++ievt) std::cout << (res[ievt].nb_significant_digit() == hstMe.data()[ievt].nb_significant_digit()) << std::endl;
    cadna_end();
#endif
    return 0;
}
