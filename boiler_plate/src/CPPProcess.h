#ifndef CPPPROCESS_STANDALONE_CPPPROCESS_H
#define CPPPROCESS_STANDALONE_CPPPROCESS_H
#include "typeTraits.h"

class CPPProcess
{
public:
    const int neppV = 1;
    int nitter = 1; //3rd number in the arg

    // Process-independent compile-time constants
    static constexpr int np4 = 4; // dimensions of 4-momenta (E,px,py,pz)
    static constexpr int nw6 = 6; // dimensions of each wavefunction (HELAS KEK 91-11): e.g. 6 for e+ e- -> mu+ mu- (fermions and vectors)

    // Process-dependent compile-time constants
    static constexpr int npari = 2; // #particles in the initial state (incoming): e.g. 2 (e+ e-) for e+ e- -> mu+ mu-
    static constexpr int nparf = 4; // #particles in the final state (outgoing): e.g. 2 (mu+ mu-) for e+ e- -> mu+ mu-
    static constexpr int npar = npari + nparf; // #particles in total (external = initial + final): e.g. 4 for e+ e- -> mu+ mu-
    static constexpr int ncomb = 64; // #helicity combinations: e.g. 16 for e+ e- -> mu+ mu- (2**4 = fermion spin up/down ** npar)
    static constexpr int ndiagrams = 123; // #Feynman diagrams: e.g. 3 for e+ e- -> mu+ mu-
    static constexpr int ncolor = 24; // the number of leading colors: e.g. 1 for e+ e- -> mu+ mu-
};
    void
    computeDependentCouplings(const fptype* allgs, // input: Gs[nevt]
                              fptype* allcouplings, // output: couplings[nevt*ndcoup*2]
                              const int nevt); // input: #events (for cuda: nevt == ndim == gpublocks*gputhreads)

    void
    sigmakin_GetGoodHel(const fptype* allmomenta, // input: momenta[nevt*npar*4]
                        const fptype* allcouplings, // input: couplings[nevt*ndcoup*2]
                        fptype* allmes, // output: allmes[nevt], |m|^2 final_avg_over_helicities
                        bool* isGoodHel, // output: isGoodHel[ncomb] - host array (C++ implementation)
                        const int nevt); // input: #events (for cuda: nevt == ndim == gpublocks*gputhreads)

    int // output: nGoodHel (the number of good helicity combinations out of ncomb)
    sigmaKin_setGoodHel(const bool* isGoodHel); // input: isGoodHel[ncomb] - host array

    void
    sigmaKin(const fptype* allmomenta, // input: momenta[nevt*npar*4]
             const fptype* allcouplings, // input: couplings[nevt*ndcoup*2]
             const fptype* allrndhel, // input: random numbers[nevt] for helicity selection
             fptype* allMEs, // output: allMEs[nevt], |M|^2 final_avg_over_helicities
             int* allselhel, // output: helicity selection[nevt]
             const int nevt); // input: #events (for cuda: nevt == ndim == gpublocks*gputhreads)

#include "accesses/includeAcesses.h"
#include "CPPProcess.cpp"


#endif //CPPPROCESS_STANDALONE_CPPPROCESS_H
