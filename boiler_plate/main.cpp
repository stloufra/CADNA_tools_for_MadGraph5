#include <iostream>
#include "src/boilerplate/typeTraits.h"
#include "src/CPPProcess.h"
#include "src/boilerplate/MemoryBuffers.h"
#include "src/boilerplate/read_momenta.h"
#include "src/accesses/MemoryAccessMomenta.h"
#include "src/boilerplate/fillers.h"
#include <chrono>

int main(int argc, char* argv[])
{
#ifdef __CADNA
    cadna_init(-1);
#endif

    int nevt = 18893;

    std::cout << "nevt = " << nevt << std::endl;

    HostBufferMomenta hstMomenta(nevt);
    HostBufferGs hstGs(nevt);
    HostBufferSelectedHelicity hstSelHel(nevt);
    HostBufferRndNumHelicity hstRndHel(nevt);
    HostBufferHelicityMask hstIsGoodHel(CPPProcess::ncomb);

    CPPProcess process(true);

#if defined (__PRO__)
    process.initProc("src/Cards/param_card.dat");
    //fillMomentaFromFile("gdb_run_output_float-O3_1.out", hstMomenta, nevt, false, 3);
    fillMomentaFromFileNative("gdb_run_output_float-O3_1.out", hstMomenta, nevt, false);
#else
    process.initProc("../src/Cards/param_card.dat");
    //fillMomentaFromFile("../gdb_run_output_float-O3_1.out", hstMomenta, nevt, false, 3);
    fillMomentaFromFileNative("../gdb_run_output_float-O3_1.out", hstMomenta, nevt, false);
#endif

    fillGs(hstGs.data(), nevt);
    fillRndHel(hstRndHel.data(), nevt);

    computeDependentCouplings(hstGs.data(), hstCoup.data(), nevt);
    sigmaKin_getGoodHel(hstMomenta.data(), hstCoup.data(), hstMe.data(), hstIsGoodHel.data(), nevt);

    const int nGoodHel = sigmaKin_setGoodHel(hstIsGoodHel.data());

    sigmaKin(hstMomenta.data(), hstCoup.data(), hstRndHel.data(), hstMe.data(), hstSelHel.data(), nevt);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1.0e9 << "s" << std::endl;
    //---

#ifdef __CADNA
    printMEandPreccision(hstMomenta, hstMe, nevt, true);
    std::cout << "Number of good helicities: " << nGoodHel << std::endl;
    cadna_end();
#elif defined (__PRO__)
    PROMISE_CHECK_ARRAY(hstMe.data(), nevt);
#else
    printMEandPreccision(hstMomenta, hstMe, nevt, true);
    std::cout << "Number of good helicities: " << nGoodHel << std::endl;
#endif
    return 0;
}
