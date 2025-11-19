//
// Created by Frantisek Stloukal on 14.11.2025.
//
#ifndef CPPPROCESS_STANDALONE_CPPPROCESS_CPP
#define CPPPROCESS_STANDALONE_CPPPROCESS_CPP

#include "../CPPProcess.h"
#include "../commonNums.h"

static fptype cIPD[nIPD];
static fptype* cIPC = nullptr;

static short cHel[ncomb][npar];
static int cNGoodHel;
static int cGoodHel[ncomb];

static double* bsmIndepParam = nullptr;
using namespace mg5amcCpu;

#include "../calculate_jamps.h"
//#include "color_sum.cc"

CPPProcess::CPPProcess( bool verbose,
                          bool debug )
    : m_verbose( verbose )
    , m_debug( debug )
    , m_pars( 0 )
    , m_masses()
  {
    // Helicities for the process [NB do keep 'static' for this constexpr array, see issue #283]
    // *** NB There is no automatic check yet that these are in the same order as Fortran! #569 ***
    static constexpr short tHel[ncomb][npar] = {
      { -1, -1, -1, 1, -1, -1 },
      { -1, -1, -1, 1, -1, 1 },
      { -1, -1, -1, 1, 1, -1 },
      { -1, -1, -1, 1, 1, 1 },
      { -1, -1, -1, -1, -1, -1 },
      { -1, -1, -1, -1, -1, 1 },
      { -1, -1, -1, -1, 1, -1 },
      { -1, -1, -1, -1, 1, 1 },
      { -1, -1, 1, 1, -1, -1 },
      { -1, -1, 1, 1, -1, 1 },
      { -1, -1, 1, 1, 1, -1 },
      { -1, -1, 1, 1, 1, 1 },
      { -1, -1, 1, -1, -1, -1 },
      { -1, -1, 1, -1, -1, 1 },
      { -1, -1, 1, -1, 1, -1 },
      { -1, -1, 1, -1, 1, 1 },
      { -1, 1, -1, 1, -1, -1 },
      { -1, 1, -1, 1, -1, 1 },
      { -1, 1, -1, 1, 1, -1 },
      { -1, 1, -1, 1, 1, 1 },
      { -1, 1, -1, -1, -1, -1 },
      { -1, 1, -1, -1, -1, 1 },
      { -1, 1, -1, -1, 1, -1 },
      { -1, 1, -1, -1, 1, 1 },
      { -1, 1, 1, 1, -1, -1 },
      { -1, 1, 1, 1, -1, 1 },
      { -1, 1, 1, 1, 1, -1 },
      { -1, 1, 1, 1, 1, 1 },
      { -1, 1, 1, -1, -1, -1 },
      { -1, 1, 1, -1, -1, 1 },
      { -1, 1, 1, -1, 1, -1 },
      { -1, 1, 1, -1, 1, 1 },
      { 1, -1, -1, 1, -1, -1 },
      { 1, -1, -1, 1, -1, 1 },
      { 1, -1, -1, 1, 1, -1 },
      { 1, -1, -1, 1, 1, 1 },
      { 1, -1, -1, -1, -1, -1 },
      { 1, -1, -1, -1, -1, 1 },
      { 1, -1, -1, -1, 1, -1 },
      { 1, -1, -1, -1, 1, 1 },
      { 1, -1, 1, 1, -1, -1 },
      { 1, -1, 1, 1, -1, 1 },
      { 1, -1, 1, 1, 1, -1 },
      { 1, -1, 1, 1, 1, 1 },
      { 1, -1, 1, -1, -1, -1 },
      { 1, -1, 1, -1, -1, 1 },
      { 1, -1, 1, -1, 1, -1 },
      { 1, -1, 1, -1, 1, 1 },
      { 1, 1, -1, 1, -1, -1 },
      { 1, 1, -1, 1, -1, 1 },
      { 1, 1, -1, 1, 1, -1 },
      { 1, 1, -1, 1, 1, 1 },
      { 1, 1, -1, -1, -1, -1 },
      { 1, 1, -1, -1, -1, 1 },
      { 1, 1, -1, -1, 1, -1 },
      { 1, 1, -1, -1, 1, 1 },
      { 1, 1, 1, 1, -1, -1 },
      { 1, 1, 1, 1, -1, 1 },
      { 1, 1, 1, 1, 1, -1 },
      { 1, 1, 1, 1, 1, 1 },
      { 1, 1, 1, -1, -1, -1 },
      { 1, 1, 1, -1, -1, 1 },
      { 1, 1, 1, -1, 1, -1 },
      { 1, 1, 1, -1, 1, 1 } };

    memcpy( cHel, tHel, ncomb * npar * sizeof( short ) );
  }

  //--------------------------------------------------------------------------

  CPPProcess::~CPPProcess() {}

  //--------------------------------------------------------------------------

  // Initialize process (with parameters read from user cards)
  void
  CPPProcess::initProc( const std::string& param_card_name )
  {
    // Instantiate the model class and set parameters that stay fixed during run
    m_pars = Parameters_sm::getInstance();
    SLHAReader slha( param_card_name, m_verbose );
    m_pars->setIndependentParameters( slha );
    m_pars->setIndependentCouplings();
    //m_pars->setDependentParameters(); // now computed event-by-event (running alphas #373)
    //m_pars->setDependentCouplings(); // now computed event-by-event (running alphas #373)
    if( m_verbose )
    {
      m_pars->printIndependentParameters();
      m_pars->printIndependentCouplings();
      //m_pars->printDependentParameters(); // now computed event-by-event (running alphas #373)
      //m_pars->printDependentCouplings(); // now computed event-by-event (running alphas #373)
    }
    // Set external particle masses for this matrix element
    m_masses.push_back( m_pars->ZERO );
    m_masses.push_back( m_pars->ZERO );
    m_masses.push_back( m_pars->mdl_MT );
    m_masses.push_back( m_pars->mdl_MT );
    m_masses.push_back( m_pars->ZERO );
    m_masses.push_back( m_pars->ZERO );
    // Read physics parameters like masses and couplings from user configuration files (static: initialize once)
    // Then copy them to CUDA constant memory (issue #39) or its C++ emulation in file-scope static memory
    const fptype tIPD[nIPD] = { (fptype)m_pars->mdl_MT, (fptype)m_pars->mdl_WT };
    memcpy( cIPD, tIPD, nIPD * sizeof( fptype ) );
}

//--------------------------------------------------------------------------

void /* clang-format off */
computeDependentCouplings( const fptype* allgs, // input: Gs[nevt]
                           fptype* allcouplings // output: couplings[nevt*ndcoup*2]
                           , const int nevt     // input: #events (for cuda: nevt == ndim == gpublocks*gputhreads)
) /* clang-format on */
{
    using namespace mg5amcCpu;
    using G_ACCESS = HostAccessGs;
    using C_ACCESS = HostAccessCouplings;
    for( int ipagV = 0; ipagV < nevt / neppV; ++ipagV )
    {
        const int ievt0 = ipagV * neppV;
        const fptype* gs = MemoryAccessGs::ieventAccessRecordConst( allgs, ievt0 );
        fptype* couplings = MemoryAccessCouplings::ieventAccessRecord( allcouplings, ievt0 );
        G2COUP<G_ACCESS, C_ACCESS>( gs, couplings, bsmIndepParam );
    }
}

//--------------------------------------------------------------------------
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

void sigmakin_GetGoodHel(const fptype* allmomenta, // input: momenta[nevt*npar*4]
                         const fptype* allcouplings, // input: couplings[nevt*ndcoup*2]
                         fptype* allMEs, // output: allMEs[nevt], |M|^2 final_avg_over_helicities
                         bool* isGoodHel, // output: isGoodHel[ncomb] - host array
                         const int nevt) // input: #events (for cuda: nevt == ndim == gpublocks*gputhreads)
{
    // Allocate arrays at build time to contain at least 16 events (or at least neppV events if neppV>16, e.g. in future VPUs)
    constexpr int maxtry0 = std::max(16, neppV);
    // 16, but at least neppV (otherwise the npagV loop does not even start)
    const int maxtry = std::min(maxtry0, nevt); // 16, but at most nevt (avoid invalid memory access if nevt<maxtry0)
    const int npagV = maxtry / neppV;
    const int npagV2 = npagV; // loop on one SIMD page (neppV events) at a time
    for (int ipagV2 = 0; ipagV2 < npagV2; ++ipagV2)
    {
        const int ievt00 = ipagV2 * neppV; // loop on one SIMD page (neppV events) at a time
        for (int ihel = 0; ihel < ncomb; ihel++)
        {
            // NEW IMPLEMENTATION OF GETGOODHEL (#630): RESET THE RUNNING SUM OVER HELICITIES TO 0 BEFORE ADDING A NEW HELICITY
            for (int ieppV = 0; ieppV < neppV; ++ieppV)
            {
                const int ievt = ievt00 + ieppV;
                allMEs[ievt] = 0;
            }
            constexpr fptype_sv* jamp2_sv = nullptr; // no need for color selection during helicity filtering
            cxtype_sv jamp_sv[ncolor] = {}; // all zeros
            calculate_jamps(ihel, allmomenta, allcouplings, jamp_sv, ievt00); //maxtry?
            color_sum_cpu(allMEs, jamp_sv, ievt00);
            for (int ieppV = 0; ieppV < neppV; ++ieppV)
            {
                const int ievt = ievt00 + ieppV;
                //std::cout << "sigmaKin_getGoodHel allMEs[ievt]=" << allMEs[ievt] << std::endl;
                if (allMEs[ievt] != 0)
                // NEW IMPLEMENTATION OF GETGOODHEL (#630): COMPARE EACH HELICITY CONTRIBUTION TO 0
                {
                    //if ( !isGoodHel[ihel] ) std::cout << "sigmaKin_getGoodHel ihel=" << ihel << " TRUE" << std::endl;
                    isGoodHel[ihel] = true;
                }
            }
        }
    }
}



void /* clang-format off */
  sigmaKin( const fptype* allmomenta,           // input: momenta[nevt*npar*4]
            const fptype* allcouplings,         // input: couplings[nevt*ndcoup*2]
            const fptype* allrndhel,            // input: random numbers[nevt] for helicity selection
            fptype* allMEs,                     // output: allMEs[nevt], |M|^2 final_avg_over_helicities
            int* allselhel,                     // output: helicity selection[nevt]
            const int nevt                      // input: #events (for cuda: nevt == ndim == gpublocks*gputhreads)
            ) /* clang-format on */
{
    // Denominators: spins, colors and identical particles
    constexpr int helcolDenominators[1] = {512}; // assume nprocesses == 1 (#272 and #343)

    using E_ACCESS = HostAccessMatrixElements; // non-trivial access: buffer includes all events

    // Start sigmaKin_lines

    // === PART 0 - INITIALISATION (before calculate_jamps) ===
    // Reset the "matrix elements" - running sums of |M|^2 over helicities for the given event

    // *** PART 0b - C++ ***
    const int npagV = nevt / neppV;
    for (int ipagV = 0; ipagV < npagV; ++ipagV)
    {
        const int ievt0 = ipagV * neppV;
        fptype* MEs = E_ACCESS::ieventAccessRecord(allMEs, ievt0);
        fptype_sv& MEs_sv = E_ACCESS::kernelAccess(MEs);
        MEs_sv = fptype_sv{0};

        const int npagV2 = npagV; // loop on one SIMD page (neppV events) at a time

        for (int ipagV2 = 0; ipagV2 < npagV2; ++ipagV2)
        {
            const int ievt00 = ipagV2 * neppV; // loop on one SIMD page (neppV events) at a time

            // Running sum of partial amplitudes squared for event by event color selection (#402)
            // (jamp2[nParity][ncolor][neppV] for the SIMD vector - or the two SIMD vectors - of events processed in calculate_jamps)
            fptype_sv jamp2_sv[nParity * ncolor] = {};
            fptype_sv MEs_ighel[ncomb] = {};
            // sum of MEs for all good helicities up to ighel (for the first - and/or only - neppV page)

            for (int ighel = 0; ighel < cNGoodHel; ighel++)
            {
                const int ihel = cGoodHel[ighel];
                cxtype_sv jamp_sv[nParity * ncolor] = {};
                // fixed nasty bug (omitting 'nParity' caused memory corruptions after calling calculate_jamps)

                calculate_jamps(ihel, allmomenta, allcouplings, jamp_sv, ievt00);
                color_sum_cpu(allMEs, jamp_sv, ievt00);
                MEs_ighel[ighel] = E_ACCESS::kernelAccess(E_ACCESS::ieventAccessRecord(allMEs, ievt00));
            }
            // Event-by-event random choice of helicity #403
            for (int ieppV = 0; ieppV < neppV; ++ieppV)
            {
                const int ievt = ievt00 + ieppV;
                //printf( "sigmaKin: ievt=%4d rndhel=%f\n", ievt, allrndhel[ievt] );
                for (int ighel = 0; ighel < cNGoodHel; ighel++)
                {
                    const bool okhel = allrndhel[ievt] < (MEs_ighel[ighel] / MEs_ighel[cNGoodHel - 1]);
                    if (okhel)
                    {
                        const int ihelF = cGoodHel[ighel] + 1; // NB Fortran [1,ncomb], cudacpp [0,ncomb-1]
                        allselhel[ievt] = ihelF;
                        //printf( "sigmaKin: ievt=%4d ihel=%4d\n", ievt, ihelF );
                        break;
                    }
                }

                for (int ipagV = 0; ipagV < npagV; ++ipagV)
                {
                    const int ievt0 = ipagV * neppV;
                    fptype* MEs = E_ACCESS::ieventAccessRecord(allMEs, ievt0);
                    fptype_sv& MEs_sv = E_ACCESS::kernelAccess(MEs);
                    MEs_sv /= helcolDenominators[0];
                }
            }
        }
    }
}

#endif
