//
// Created by Frantisek Stloukal on 14.11.2025.
//
#ifndef CPPPROCESS_STANDALONE_CPPPROCESS_CPP
#define CPPPROCESS_STANDALONE_CPPPROCESS_CPP
#include "CPPProcess.h"

constexpr int nw6 = CPPProcess::nw6;
// dimensions of each wavefunction (HELAS KEK 91-11): e.g. 6 for e+ e- -> mu+ mu- (fermions and vectors)
constexpr int npar = CPPProcess::npar; // #particles in total (external = initial + final): e.g. 4 for e+ e- -> mu+ mu-
constexpr int ncomb = CPPProcess::ncomb;
// #helicity combinations: e.g. 16 for e+ e- -> mu+ mu- (2**4 = fermion spin up/down ** npar)
constexpr int ncolor = CPPProcess::ncolor; // the number of leading colors
constexpr int nParity = 1;

constexpr int nIPD = 2; // SM independent parameters used in this CPPProcess.cc (FIXME? rename as sm_IndepParam?)
constexpr int nIPC = 0; // SM independent couplings used in this CPPProcess.cc (FIXME? rename as sm_IndepCoupl?)

static fptype cIPD[nIPD];
static fptype* cIPC = nullptr;

static short cHel[ncomb][npar];
static int cNGoodHel;
static int cGoodHel[ncomb];

static double* bsmIndepParam = nullptr;
using namespace mg5amcCpu;

int // output: nGoodHel (the number of good helicity combinations out of ncomb)
sigmaKin_setGoodHel(const bool* isGoodHel) // input: isGoodHel[ncomb] - host array (CUDA and C++)
{
    int nGoodHel = 0;
    int goodHel[ncomb] = {0}; // all zeros https://en.cppreference.com/w/c/language/array_initialization#Notes
    for (int ihel = 0; ihel < ncomb; ihel++)
    {
        if (isGoodHel[ihel])
        {
            goodHel[nGoodHel] = ihel;
            nGoodHel++;
        }
    }

    cNGoodHel = nGoodHel;
    for (int ihel = 0; ihel < ncomb; ihel++) cGoodHel[ihel] = goodHel[ihel];
    return nGoodHel;
}

inline const Parameters_sm_dependentCouplings::DependentCouplings_sv computeDependentCouplings_fromG(
    const fptype_sv& G_sv, const double* bsmIndepParamPtr)
{
    const cxtype cI(0., 1.);
    Parameters_sm_dependentCouplings::DependentCouplings_sv out;
    {
        const fptype_sv& G = G_sv;
        // *** NB Compute all dependent parameters, including aS, in terms of G rather than in terms of aS ***
        const fptype_sv mdl_G__exp__2 = ((G) * (G));
        out.GC_10 = -G;
        out.GC_11 = cI * G;
        out.GC_12 = cI * mdl_G__exp__2;
    }

    return out;
}

template <class G_ACCESS, class C_ACCESS>
inline void
G2COUP(const fptype gs[],
       fptype couplings[],
       const double* bsmIndepParamPtr)
{
    using namespace Parameters_sm_dependentCouplings;
    const fptype_sv& gs_sv = G_ACCESS::kernelAccessConst(gs);
    DependentCouplings_sv couplings_sv = computeDependentCouplings_fromG(gs_sv, bsmIndepParamPtr);
    fptype* GC_10s = C_ACCESS::idcoupAccessBuffer(couplings, idcoup_GC_10);
    fptype* GC_11s = C_ACCESS::idcoupAccessBuffer(couplings, idcoup_GC_11);
    fptype* GC_12s = C_ACCESS::idcoupAccessBuffer(couplings, idcoup_GC_12);
    cxtype_sv_ref GC_10s_sv = C_ACCESS::kernelAccess(GC_10s);
    cxtype_sv_ref GC_11s_sv = C_ACCESS::kernelAccess(GC_11s);
    cxtype_sv_ref GC_12s_sv = C_ACCESS::kernelAccess(GC_12s);
    GC_10s_sv = couplings_sv.GC_10;
    GC_11s_sv = couplings_sv.GC_11;
    GC_12s_sv = couplings_sv.GC_12;
    return;
}

void computeDependentCouplings(const fptype* allgs, // input: Gs[nevt]
                               fptype* allcouplings, // output: couplings[nevt*ndcoup*2]
                               const int nevt)
// input: #events (for cuda: nevt == ndim == gpublocks*gputhreads) /* clang-format on */
{
    using G_ACCESS = HostAccessGs;
    using C_ACCESS = HostAccessCouplings;
    for (int ipagV = 0; ipagV < nevt / neppV; ++ipagV)
    {
        const int ievt0 = ipagV * neppV;
        const fptype* gs = MemoryAccessGs::ieventAccessRecordConst(allgs, ievt0);
        fptype* couplings = MemoryAccessCouplings::ieventAccessRecord(allcouplings, ievt0);
        G2COUP<G_ACCESS, C_ACCESS>(gs, couplings, bsmIndepParam);
    }
}

//void /* clang-format off */
//  sigmaKin( const fptype* allmomenta,           // input: momenta[nevt*npar*4]
//            const fptype* allcouplings,         // input: couplings[nevt*ndcoup*2]
//            const fptype* allrndhel,            // input: random numbers[nevt] for helicity selection
//            fptype* allMEs,                     // output: allMEs[nevt], |M|^2 final_avg_over_helicities
//            int* allselhel,                     // output: helicity selection[nevt]
//            const int nevt                      // input: #events (for cuda: nevt == ndim == gpublocks*gputhreads)
//            ) /* clang-format on */
//{
//    // Denominators: spins, colors and identical particles
//    constexpr int helcolDenominators[1] = {512}; // assume nprocesses == 1 (#272 and #343)
//
//    using E_ACCESS = HostAccessMatrixElements; // non-trivial access: buffer includes all events
//
//    // Start sigmaKin_lines
//
//    // === PART 0 - INITIALISATION (before calculate_jamps) ===
//    // Reset the "matrix elements" - running sums of |M|^2 over helicities for the given event
//
//    // *** PART 0b - C++ ***
//    const int npagV = nevt / neppV;
//    for (int ipagV = 0; ipagV < npagV; ++ipagV)
//    {
//        const int ievt0 = ipagV * neppV;
//        fptype* MEs = E_ACCESS::ieventAccessRecord(allMEs, ievt0);
//        fptype_sv& MEs_sv = E_ACCESS::kernelAccess(MEs);
//        MEs_sv = fptype_sv{0};
//
//        const int npagV2 = npagV; // loop on one SIMD page (neppV events) at a time
//
//        for (int ipagV2 = 0; ipagV2 < npagV2; ++ipagV2)
//        {
//            const int ievt00 = ipagV2 * neppV; // loop on one SIMD page (neppV events) at a time
//
//            // Running sum of partial amplitudes squared for event by event color selection (#402)
//            // (jamp2[nParity][ncolor][neppV] for the SIMD vector - or the two SIMD vectors - of events processed in calculate_jamps)
//            fptype_sv jamp2_sv[nParity * ncolor] = {};
//            fptype_sv MEs_ighel[ncomb] = {};
//            // sum of MEs for all good helicities up to ighel (for the first - and/or only - neppV page)
//
//            for (int ighel = 0; ighel < cNGoodHel; ighel++)
//            {
//                const int ihel = cGoodHel[ighel];
//                cxtype_sv jamp_sv[nParity * ncolor] = {};
//                // fixed nasty bug (omitting 'nParity' caused memory corruptions after calling calculate_jamps)
//
//                calculate_jamps(ihel, allmomenta, allcouplings, jamp_sv, ievt00);
//                color_sum_cpu(allMEs, jamp_sv, ievt00);
//                MEs_ighel[ighel] = E_ACCESS::kernelAccess(E_ACCESS::ieventAccessRecord(allMEs, ievt00));
//            }
//            // Event-by-event random choice of helicity #403
//            for (int ieppV = 0; ieppV < neppV; ++ieppV)
//            {
//                const int ievt = ievt00 + ieppV;
//                //printf( "sigmaKin: ievt=%4d rndhel=%f\n", ievt, allrndhel[ievt] );
//                for (int ighel = 0; ighel < cNGoodHel; ighel++)
//                {
//                    const bool okhel = allrndhel[ievt] < (MEs_ighel[ighel] / MEs_ighel[cNGoodHel - 1]);
//                    if (okhel)
//                    {
//                        const int ihelF = cGoodHel[ighel] + 1; // NB Fortran [1,ncomb], cudacpp [0,ncomb-1]
//                        allselhel[ievt] = ihelF;
//                        //printf( "sigmaKin: ievt=%4d ihel=%4d\n", ievt, ihelF );
//                        break;
//                    }
//                }
//
//                for (int ipagV = 0; ipagV < npagV; ++ipagV)
//                {
//                    const int ievt0 = ipagV * neppV;
//                    fptype* MEs = E_ACCESS::ieventAccessRecord(allMEs, ievt0);
//                    fptype_sv& MEs_sv = E_ACCESS::kernelAccess(MEs);
//                    MEs_sv /= helcolDenominators[0];
//                }
//            }
//        }
//    }
//}

#endif
