#include <iostream>
#include "src/boilerplate/typeTraits.h"
#include "src/CPPProcess.h"
#include "src/CPPProcess_proc.h"
#include "src/boilerplate/MemoryBuffers.h"
#include "src/boilerplate/read_momenta.h"
#include "src/accesses/MemoryAccessMomenta.h"
#include "src/boilerplate/fillers.h"
#include "src/boilerplate/momentaHandling.h"

#ifdef __CADNA
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
    HostBufferGs hstGs(nevt);
    HostBufferSelectedHelicity hstSelHel(nevt);
    HostBufferRndNumHelicity hstRndHel(nevt);
    HostBufferHelicityMask hstIsGoodHel(CPPProcess::ncomb);

    CPPProcess process(true);

    process.initProc("../src/Cards/param_card.dat");
    fillGs(hstGs.data(), nevt);
    fillRndHel(hstRndHel.data(), nevt);


   // Momenta sorting
    fillMomentaFromFile("../gdb_run_output_float-O3_1.out", hstMomenta, nevt, false, 8);
    auto begin = std::chrono::high_resolution_clock::now();
    auto broken = momenta_engine::PickMomenta(hstMomenta, n_broken, nevt, 0.995, 50.0);

    int n_f = nevt - n_broken;
    int n_d = n_broken;
    std::cout << "Number of good events: " << n_f << std::endl;
    std::cout << "Number of broken events: " << n_d << std::endl;

    HostBufferMomenta_f hstMomenta_f(n_f);
    HostBufferMomenta_d hstMomenta_d(n_d);

    HostBufferMatrixElements_f hstMe_f(n_f);
    HostBufferMatrixElements_d hstMe_d(n_d);

    HostBufferCouplings_f hstCoup_f(n_f);
    HostBufferCouplings_d hstCoup_d(n_d);

    momenta_engine::SortMomenta(hstMomenta, hstMomenta_f, hstMomenta_d, broken, nevt);

    computeDependentCouplings(hstGs.data(), hstCoup_f.data(), n_f);
    computeDependentCouplings<fptype_d>(hstGs.data(), hstCoup_d.data(), n_d);

    sigmaKin_getGoodHel<fptype_f>(hstMomenta_f.data(), hstCoup_f.data(), hstMe_f.data(), hstIsGoodHel.data(), n_f);
    sigmaKin_getGoodHel<fptype_d>(hstMomenta_d.data(), hstCoup_d.data(), hstMe_d.data(), hstIsGoodHel.data(), n_d);

    const int nGoodHel = sigmaKin_setGoodHel(hstIsGoodHel.data());

    sigmaKin<fptype_f>(hstMomenta_f.data(), hstCoup_f.data(), hstRndHel.data(), hstMe_f.data(), hstSelHel.data(), n_f);
    sigmaKin<fptype_d>(hstMomenta_d.data(), hstCoup_d.data(), hstRndHel.data(), hstMe_d.data(), hstSelHel.data(), n_d);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1'000'000'000.0 << "s" << std::endl;

#ifdef __CADNA
    printMEandPreccision<fptype_f>(hstMomenta_f.data(), hstMe_f.data(), n_f, true);
    printMEandPreccision<fptype_d>(hstMomenta_d.data(), hstMe_d.data(), n_d, true);
    std::cout << "Number of good helicities: " << nGoodHel << std::endl;
    cadna_end();
#endif
    return 0;
}
