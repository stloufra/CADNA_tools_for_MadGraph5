// Copyright (C) 2010 The MadGraph5_aMC@NLO development team and contributors.
// Created by: J. Alwall (Oct 2010) for the MG5aMC CPP backend.
//==========================================================================
// Copyright (C) 2020-2024 CERN and UCLouvain.
// Licensed under the GNU Lesser General Public License (version 3 or later).
// Modified by: A. Valassi (Sep 2021) for the MG5aMC CUDACPP plugin.
// Further modified by: A. Valassi (2021-2024) for the MG5aMC CUDACPP plugin.
//==========================================================================
// This file has been automatically generated for CUDA/C++ standalone by
// MadGraph5_aMC@NLO v. 3.6.4, 2025-09-13
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#ifndef Parameters_sm_H
#define Parameters_sm_H

#include "typeTraits.h"

//==========================================================================

// AV Jan 2024 (PR #625): this ugly #define was the only way I found to avoid creating arrays[nBsm] in CPPProcess.cc if nBsm is 0
// The problem is that nBsm is determined when generating Parameters.h, which happens after CPPProcess.cc has already been generated
// For simplicity, keep this code hardcoded also for SM processes (a nullptr is needed as in the case nBsm == 0)
#undef MGONGPUCPP_NBSMINDEPPARAM_GT_0


#include "read_slha.h"

// NB: namespaces mg5amcGpu and mg5amcCpu includes types which are defined in different ways for CPU and GPU builds (see #318 and #725)

namespace mg5amcCpu
{
  class Parameters_sm
  {
  public:

    static Parameters_sm* getInstance();

    // Define "zero"
    double zero, ZERO;

    // Model parameters independent of aS
    //double aS; // now retrieved event-by-event (as G) from Fortran (running alphas #373)
    double mdl_WH, mdl_WW, mdl_WZ, mdl_WT, mdl_ymtau, mdl_ymt, mdl_ymb, mdl_Gf, aEWM1, mdl_MH, mdl_MZ, mdl_MTA, mdl_MT, mdl_MB, mdl_conjg__CKM3x3, mdl_conjg__CKM1x1, mdl_CKM3x3, mdl_MZ__exp__2, mdl_MZ__exp__4, mdl_sqrt__2, mdl_MH__exp__2, mdl_aEW, mdl_MW, mdl_sqrt__aEW, mdl_ee, mdl_MW__exp__2, mdl_sw2, mdl_cw, mdl_sqrt__sw2, mdl_sw, mdl_g1, mdl_gw, mdl_vev, mdl_vev__exp__2, mdl_lam, mdl_yb, mdl_yt, mdl_ytau, mdl_muH, mdl_ee__exp__2, mdl_sw__exp__2, mdl_cw__exp__2;
    cxsmpl<double> mdl_complexi, mdl_I1x33, mdl_I2x33, mdl_I3x33, mdl_I4x33;

    // Model couplings independent of aS
    // (none)

    // Model parameters dependent on aS
    //double mdl_sqrt__aS, G, mdl_G__exp__2; // now computed event-by-event (running alphas #373)

    // Model couplings dependent on aS
    //cxsmpl<double> GC_10, GC_11, GC_12; // now computed event-by-event (running alphas #373)

    // Set parameters that are unchanged during the run
    void setIndependentParameters( SLHAReader& slha );

    // Set couplings that are unchanged during the run
    void setIndependentCouplings();

    // Set parameters that are changed event by event
    //void setDependentParameters(); // now computed event-by-event (running alphas #373)

    // Set couplings that are changed event by event
    //void setDependentCouplings(); // now computed event-by-event (running alphas #373)

    // Print parameters that are unchanged during the run
    void printIndependentParameters();

    // Print couplings that are unchanged during the run
    void printIndependentCouplings();

    // Print parameters that are changed event by event
    //void printDependentParameters(); // now computed event-by-event (running alphas #373)

    // Print couplings that are changed event by event
    //void printDependentCouplings(); // now computed event-by-event (running alphas #373)

    // BSM parameters that do not depend on alphaS but are needed in the computation of alphaS-dependent couplings;
    static constexpr int nBsmIndepParam = 0;
    //double mdl_bsmIndepParam[nBsmIndepParam];

  private:

    static Parameters_sm* instance;
  };

} // end namespace mg5amcGpu/mg5amcCpu

//==========================================================================

// NB: namespaces mg5amcGpu and mg5amcCpu includes types which are defined in different ways for CPU and GPU builds (see #318 and #725)

namespace mg5amcCpu
{
  namespace Parameters_sm_dependentCouplings
  {
    constexpr size_t ndcoup = 3; // #couplings that vary event by event because they depend on the running alphas QCD
    constexpr size_t idcoup_GC_10 = 0;
    constexpr size_t idcoup_GC_11 = 1;
    constexpr size_t idcoup_GC_12 = 2;
    struct DependentCouplings_sv
    {
      cxtype_sv GC_10;
      cxtype_sv GC_11;
      cxtype_sv GC_12;
    };
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"        // e.g. <<warning: unused parameter ‘G’ [-Wunused-parameter]>>
#pragma GCC diagnostic ignored "-Wunused-variable"         // e.g. <<warning: unused variable ‘mdl_G__exp__2’ [-Wunused-variable]>>
#pragma GCC diagnostic ignored "-Wunused-but-set-variable" // e.g. <<warning: variable ‘mdl_G__exp__2’ set but not used [-Wunused-but-set-variable]>>
    __host__ __device__ inline const DependentCouplings_sv computeDependentCouplings_fromG( const fptype_sv& G_sv, const double* bsmIndepParamPtr )
    {

      // NB: hardcode cxtype cI(0,1) instead of cxtype (or hardcoded cxsmpl) mdl_complexi (which exists in Parameters_sm) because:
      // (1) mdl_complexi is always (0,1); (2) mdl_complexi is undefined in device code; (3) need cxsmpl conversion to cxtype in code below
      const cxtype cI( 0., 1. );
      DependentCouplings_sv out;
      // Couplings are (scalar, or vector of) doubles, or scalar floats - default implementation
      {
        const fptype_sv& G = G_sv;
        // Model parameters dependent on aS
        //const fptype_sv mdl_sqrt__aS = constexpr_sqrt( aS );
        //const fptype_sv G = 2. * mdl_sqrt__aS * constexpr_sqrt( M_PI );
        // *** NB Compute all dependent parameters, including aS, in terms of G rather than in terms of aS ***
        const fptype_sv mdl_G__exp__2 = ( ( G ) * ( G ) );
        // Model couplings dependent on aS
        out.GC_10 = -G;
        out.GC_11 = cI * G;
        out.GC_12 = cI * mdl_G__exp__2;
      }

      return out;
    }

  }

  //==========================================================================

  namespace Parameters_sm_independentCouplings
  {
    constexpr size_t nicoup = 0; // #couplings that are fixed for all events because they do not depend on the running alphas QCD
    // NB: there are no aS-independent couplings in this physics process
  }

  //==========================================================================

#pragma GCC diagnostic push
#ifndef __clang__
#pragma GCC diagnostic ignored "-Wunused-but-set-variable" // e.g. <<warning: variable ‘couplings_sv’ set but not used [-Wunused-but-set-variable]>>
#endif
  // Compute the output couplings (e.g. gc10 and gc11) from the input gs
  template<class G_ACCESS, class C_ACCESS>
  __device__ inline void
  G2COUP( const fptype gs[],
          fptype couplings[],
          const double* bsmIndepParamPtr )
  {
    mgDebug( 0, __FUNCTION__ );
    using namespace Parameters_sm_dependentCouplings;
    const fptype_sv& gs_sv = G_ACCESS::kernelAccessConst( gs );
    DependentCouplings_sv couplings_sv = computeDependentCouplings_fromG( gs_sv, bsmIndepParamPtr );
    fptype* GC_10s = C_ACCESS::idcoupAccessBuffer( couplings, idcoup_GC_10 );
    fptype* GC_11s = C_ACCESS::idcoupAccessBuffer( couplings, idcoup_GC_11 );
    fptype* GC_12s = C_ACCESS::idcoupAccessBuffer( couplings, idcoup_GC_12 );
    cxtype_sv_ref GC_10s_sv = C_ACCESS::kernelAccess( GC_10s );
    cxtype_sv_ref GC_11s_sv = C_ACCESS::kernelAccess( GC_11s );
    cxtype_sv_ref GC_12s_sv = C_ACCESS::kernelAccess( GC_12s );
    GC_10s_sv = couplings_sv.GC_10;
    GC_11s_sv = couplings_sv.GC_11;
    GC_12s_sv = couplings_sv.GC_12;
    mgDebug( 1, __FUNCTION__ );
    return;
  }
#pragma GCC diagnostic pop

} // end namespace mg5amcGpu/mg5amcCpu

//==========================================================================

#endif // Parameters_sm_H
