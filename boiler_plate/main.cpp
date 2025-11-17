#include <iostream>
#include "src/typeTraits.h"
#include "src/CPPProcess.h"
#include "src/MemoryBuffers.h"

int main()
{

    const int nevt = 24;
    HostBufferGs hstGs(nevt);
    HostBufferHelicityMask hstIsGoodHel( CPPProcess::ncomb );
    HostBufferCouplings m_couplings(nevt);

    for( unsigned int i = 0; i < nevt; ++i )
    {
        const fptype fixedG = 1.2177157847767195; // fixed G for aS=0.118 (hardcoded for now in check_sa.cc, fcheck_sa.f, runTest.cc)
        hstGs[i] = fixedG;
    }
    computeDependentCouplings(hstGs.data(), m_couplings.data(), nevt );


    //sigmaKin_setGoodHel();

    //computeDependentCouplings( m_gs.data(), m_couplings.data(), m_gs.size() );
    /*CPPProcess::sigmaKin(allmomenta, // input: momenta[nevt*npar*4]
             allcouplings, // input: couplings[nevt*ndcoup*2]
             allrndhel, // input: random numbers[nevt] for helicity selection
             allMEs, // output: allMEs[nevt], |M|^2 final_avg_over_helicities
             allselhel, // output: helicity selection[nevt]
             nevt);
    */
    return 0;

}
