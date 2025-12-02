// Copyright (C) 2010 The ALOHA Development team and Contributors.
// Copyright (C) 2010 The MadGraph5_aMC@NLO development team and contributors.
// Created by: J. Alwall (Sep 2010) for the MG5aMC backend.
//==========================================================================
// Copyright (C) 2020-2024 CERN and UCLouvain.
// Licensed under the GNU Lesser General Public License (version 3 or later).
// Modified by: A. Valassi (Sep 2021) for the MG5aMC CUDACPP plugin.
// Further modified by: J. Teig, A. Valassi (2021-2024) for the MG5aMC CUDACPP plugin.
//==========================================================================
// This file has been automatically generated for CUDA/C++ standalone by
// MadGraph5_aMC@NLO v. 3.6.4, 2025-09-13
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#ifndef HelAmps_sm_H
#define HelAmps_sm_H 1

#include "boilerplate/typeTraits.h"


#include "boilerplate/Parameters_sm.h"

#include <cassert>
//#include <cmath>
//#include <cstdlib>
//#include <iomanip>
//#include <iostream>
using std::abs;

#ifdef MGONGPUCPP_GPUIMPL
namespace mg5amcGpu
#else
namespace mg5amcCpu
#endif
{
  //--------------------------------------------------------------------------

#ifdef MGONGPU_INLINE_HELAMPS
#define INLINE inline
#define ALWAYS_INLINE __attribute__( ( always_inline ) )
#else
#define INLINE
#define ALWAYS_INLINE
#endif

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fi[6] from the input momenta[npar*4*nevt]
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT = cxsmpl<FT>>  __host__ __device__ INLINE void
  ixxxxx( const FT momenta[], // input: momenta
          const FT fmass,     // input: fermion mass
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          FT wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fi[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PX == PY == 0 and E == +PZ > 0)
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT = cxsmpl<FT>>  __host__ __device__ INLINE void
  ipzxxx( const FT momenta[], // input: momenta
          //const FT fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          FT wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fi[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PX == PY == 0 and E == -PZ > 0)
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT = cxsmpl<FT>>  __host__ __device__ INLINE void
  imzxxx( const FT momenta[], // input: momenta
          //const FT fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          FT wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fi[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PT > 0)
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT = cxsmpl<FT>>  __host__ __device__ INLINE void
  ixzxxx( const FT momenta[], // input: momenta
          //const FT fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          FT wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction vc[6] from the input momenta[npar*4*nevt]
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT = cxsmpl<FT>>  __host__ __device__ INLINE void
  vxxxxx( const FT momenta[], // input: momenta
          const FT vmass,     // input: vector boson mass
          const int nhel,         // input: -1, 0 (only if vmass!=0) or +1 (helicity of vector boson)
          const int nsv,          // input: +1 (final) or -1 (initial)
          FT wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction sc[3] from the input momenta[npar*4*nevt]
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT = cxsmpl<FT>>  __host__ __device__ INLINE void
  sxxxxx( const FT momenta[], // input: momenta
          //const FT,                 // WARNING: input "smass" unused (missing in Fortran) - scalar boson mass
          //const int,                    // WARNING: input "nhel" unused (missing in Fortran) - scalar has no helicity!
          const int nss,          // input: +1 (final) or -1 (initial)
          FT wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fo[6] from the input momenta[npar*4*nevt]
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT = cxsmpl<FT>>
  __host__ __device__ INLINE void
  oxxxxx( const FT momenta[], // input: momenta
          const FT fmass,     // input: fermion mass
          const int nhel,         // input: -1, 0 (only if vmass!=0) or +1 (helicity of vector boson)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          FT wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fo[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PX == PY == 0 and E == +PZ > 0)
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT = cxsmpl<FT>>
  __host__ __device__ INLINE void
  opzxxx( const FT momenta[], // input: momenta
          //const FT fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          FT wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fo[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PX == PY == 0 and E == -PZ > 0)
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT = cxsmpl<FT>>
  __host__ __device__ INLINE void
  omzxxx( const FT momenta[], // input: momenta
          //const FT fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          FT wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fo[6] from the input momenta[npar*4*nevt]
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT = cxsmpl<FT>>
  __host__ __device__ INLINE void
  oxzxxx( const FT momenta[], // input: momenta
          //const FT fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          FT wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //==========================================================================

  // Compute the output wavefunction fi[6] from the input momenta[npar*4*nevt]
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT>
  __host__ __device__ void
  ixxxxx( const FT momenta[], // input: momenta
          const FT fmass,     // input: fermion mass
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          FT wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    // NEW IMPLEMENTATION FIXING FLOATING POINT EXCEPTIONS IN SIMD CODE (#701)
    // Variables xxxDENOM are a hack to avoid division-by-0 FPE while preserving speed (#701 and #727)
    // Variables xxxDENOM are declared as 'volatile' to make sure they are not optimized away on clang! (#724)
    // A few additional variables are declared as 'volatile' to avoid sqrt-of-negative-number FPEs (#736)
    const FT& pvec0 = M_ACCESS::kernelAccessIp4IparConst( momenta, 0, ipar );
    const FT& pvec1 = M_ACCESS::kernelAccessIp4IparConst( momenta, 1, ipar );
    const FT& pvec2 = M_ACCESS::kernelAccessIp4IparConst( momenta, 2, ipar );
    const FT& pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    CT* fi = W_ACCESS::kernelAccess( wavefunctions );
    fi[0] = cxmake<FT>( -pvec0 * (FT)nsf, -pvec3 * (FT)nsf );
    fi[1] = cxmake<FT>( -pvec1 * (FT)nsf, -pvec2 * (FT)nsf );
    const int nh = nhel * nsf;
    if( fmass != 0. )
    {
#ifndef MGONGPU_CPPSIMD
      const FT pp = fpmin<FT>( pvec0, fpsqrt<FT>( pvec1 * pvec1 + pvec2 * pvec2 + pvec3 * pvec3 ) );
#else
      volatile FT p2 = pvec1 * pvec1 + pvec2 * pvec2 + pvec3 * pvec3; // volatile fixes #736
      const FT pp = fpmin<FT>( pvec0, fpsqrt<FT>( p2 ) );
#endif
      // In C++ ixxxxx, use a single ip/im numbering that is valid both for pp==0 and pp>0, which have two numbering schemes in Fortran ixxxxx:
      // for pp==0, Fortran sqm(0:1) has indexes 0,1 as in C++; but for Fortran pp>0, omega(2) has indexes 1,2 and not 0,1
      // NB: this is only possible in ixxxx, but in oxxxxx two different numbering schemes must be used
      const int ip = ( 1 + nh ) / 2; // NB: same as in Fortran pp==0, differs from Fortran pp>0, which is (3+nh)/2 because omega(2) has indexes 1,2
      const int im = ( 1 - nh ) / 2; // NB: same as in Fortran pp==0, differs from Fortran pp>0, which is (3-nh)/2 because omega(2) has indexes 1,2
#ifndef MGONGPU_CPPSIMD
      if( pp == 0. )
      {
        // NB: Do not use "abs" for floats! It returns an integer with no build warning! Use std::abs!
        FT sqm[2] = { fpsqrt<FT>( abs( fmass ) ), 0. }; // possibility of negative fermion masses
        //sqm[1] = ( fmass < 0. ? -abs( sqm[0] ) : abs( sqm[0] ) ); // AV: why abs here?
        sqm[1] = ( fmass < 0. ? -sqm[0] : sqm[0] ); // AV: removed an abs here
        fi[2] = cxmake<FT>( ip * sqm[ip], 0 );
        fi[3] = cxmake<FT>( im * nsf * sqm[ip], 0 );
        fi[4] = cxmake<FT>( ip * nsf * sqm[im], 0 );
        fi[5] = cxmake<FT>( im * sqm[im], 0 );
      }
      else
      {
        const FT sf[2] = { FT( 1 + nsf + ( 1 - nsf ) * nh ) * (FT)0.5,
                               FT( 1 + nsf - ( 1 - nsf ) * nh ) * (FT)0.5 };
        FT omega[2] = { fpsqrt<FT>( pvec0 + pp ), 0. };
        omega[1] = fmass / omega[0];
        const FT sfomega[2] = { sf[0] * omega[ip], sf[1] * omega[im] };
        const FT pp3 = fpmax<FT>( pp + pvec3, 0. );
        const CT chi[2] = { cxmake<FT>( fpsqrt<FT>( pp3 * (FT)0.5 / pp ), 0. ),
                                ( pp3 == 0. ? cxmake<FT>( -nh, 0. ) : cxmake<FT>( nh * pvec1, pvec2 ) / fpsqrt<FT>( 2. * pp * pp3 ) ) };
        fi[2] = sfomega[0] * chi[im];
        fi[3] = sfomega[0] * chi[ip];
        fi[4] = sfomega[1] * chi[im];
        fi[5] = sfomega[1] * chi[ip];
      }
#else
      // Branch A: pp == 0.
      // NB: Do not use "abs" for floats! It returns an integer with no build warning! Use std::abs!
      FT sqm[2] = { fpsqrt<FT>( abs( fmass ) ), 0 }; // possibility of negative fermion masses (NB: SCALAR!)
      sqm[1] = ( fmass < 0 ? -sqm[0] : sqm[0] );          // AV: removed an abs here (as above)
      const CT fiA_2 = ip * sqm[ip];                  // scalar CT: real part initialised from FT, imag part = 0
      const CT fiA_3 = im * nsf * sqm[ip];            // scalar CT: real part initialised from FT, imag part = 0
      const CT fiA_4 = ip * nsf * sqm[im];            // scalar CT: real part initialised from FT, imag part = 0
      const CT fiA_5 = im * sqm[im];                  // scalar CT: real part initialised from FT, imag part = 0
      // Branch B: pp != 0.
      const FT sf[2] = { FT( 1 + nsf + ( 1 - nsf ) * nh ) * (FT)0.5,
                             FT( 1 + nsf - ( 1 - nsf ) * nh ) * (FT)0.5 };
      FT_v omega[2] = { fpsqrt<FT>( pvec0 + pp ), 0 };
      omega[1] = fmass / omega[0];
      const FT_v sfomega[2] = { sf[0] * omega[ip], sf[1] * omega[im] };
      const FT_v pp3 = fpmax<FT>( pp + pvec3, 0 );
      volatile FT_v ppDENOM = fpternary<FT>( pp != 0, pp, 1. );    // hack: ppDENOM[ieppV]=1 if pp[ieppV]==0
      volatile FT_v pp3DENOM = fpternary<FT>( pp3 != 0, pp3, 1. ); // hack: pp3DENOM[ieppV]=1 if pp3[ieppV]==0
      volatile FT_v chi0r2 = pp3 * 0.5 / ppDENOM;              // volatile fixes #736
      const CT chi[2] = { cxmake<FT>( fpsqrt<FT>( chi0r2 ), 0 ),     // hack: dummy[ieppV] is not used if pp[ieppV]==0
                                cxternary( ( pp3 == 0. ),
                                           cxmake<FT>( -nh, 0 ),
                                           cxmake<FT>( (FT)nh * pvec1, pvec2 ) / fpsqrt<FT>( 2. * ppDENOM * pp3DENOM ) ) }; // hack: dummy[ieppV] is not used if pp[ieppV]==0
      const CT fiB_2 = sfomega[0] * chi[im];
      const CT fiB_3 = sfomega[0] * chi[ip];
      const CT fiB_4 = sfomega[1] * chi[im];
      const CT fiB_5 = sfomega[1] * chi[ip];
      // Choose between the results from branch A and branch B
      const bool_v mask = ( pp == 0. );
      fi[2] = cxternary( mask, fiA_2, fiB_2 );
      fi[3] = cxternary( mask, fiA_3, fiB_3 );
      fi[4] = cxternary( mask, fiA_4, fiB_4 );
      fi[5] = cxternary( mask, fiA_5, fiB_5 );
#endif
    }
    else
    {
#ifdef MGONGPU_CPPSIMD
      volatile FT p0p3 = fpmax<FT>( pvec0 + pvec3, 0 ); // volatile fixes #736
      volatile FT sqp0p3 = fpternary<FT>( ( pvec1 == 0. and pvec2 == 0. and pvec3 < 0. ),
                                             FT{ 0 },
                                             fpsqrt<FT>( p0p3 ) * (FT)nsf );
      volatile FT sqp0p3DENOM = fpternary<FT>( sqp0p3 != 0, (FT)sqp0p3, 1. ); // hack: dummy sqp0p3DENOM[ieppV]=1 if sqp0p3[ieppV]==0
      CT chi[2] = { cxmake<FT>( (FT_v)sqp0p3, 0. ),
                           cxternary( sqp0p3 == 0,
                                      cxmake<FT>( -(FT)nhel * fpsqrt<FT>( 2. * pvec0 ), 0. ),
                                      cxmake<FT>( (FT)nh * pvec1, pvec2 ) / (const FT_v)sqp0p3DENOM ) }; // hack: dummy[ieppV] is not used if sqp0p3[ieppV]==0
#else
      const FT sqp0p3 = fpternary<FT>( ( pvec1 == 0. and pvec2 == 0. and pvec3 < 0. ),
                                          FT{ 0 },
                                          fpsqrt<FT>( fpmax<FT>( pvec0 + pvec3, 0. ) ) * (FT)nsf );
      const CT chi[2] = { cxmake<FT>( sqp0p3, 0. ),
                                 ( sqp0p3 == 0. ? cxmake<FT>( -(FT)nhel * fpsqrt<FT>( 2. * pvec0 ), 0. ) : cxmake<FT>( (FT)nh * pvec1, pvec2 ) / sqp0p3 ) };
#endif
      if( nh == 1 )
      {
        fi[2] = cxzero_sv<CT>();
        fi[3] = cxzero_sv<CT>();
        fi[4] = chi[0];
        fi[5] = chi[1];
      }
      else
      {
        fi[2] = chi[1];
        fi[3] = chi[0];
        fi[4] = cxzero_sv<CT>();
        fi[5] = cxzero_sv<CT>();
      }
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fi[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PX == PY == 0 and E == +PZ > 0)
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT >  __host__ __device__ void
  ipzxxx( const FT momenta[], // input: momenta
          //const FT fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          FT wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    const FT& pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    FT* fi = W_ACCESS::kernelAccess( wavefunctions );
    fi[0] = cxmake<FT>( -pvec3 * (FT)nsf, -pvec3 * (FT)nsf );
    fi[1] = cxzero_sv<CT>();
    const int nh = nhel * nsf;
    const FT sqp0p3 = cxmake<FT>( fpsqrt<FT>( 2. * pvec3 ) * (FT)nsf, 0. );
    fi[2] = fi[1];
    if( nh == 1 )
    {
      fi[3] = fi[1];
      fi[4] = sqp0p3;
    }
    else
    {
      fi[3] = sqp0p3;
      fi[4] = fi[1];
    }
    fi[5] = fi[1];
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fi[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PX == PY == 0 and E == -PZ > 0)
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT >  __host__ __device__ void
  imzxxx( const FT momenta[], // input: momenta
          //const FT fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          FT wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    const FT& pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    FT* fi = W_ACCESS::kernelAccess( wavefunctions );
    fi[0] = cxmake<FT>( pvec3 * (FT)nsf, -pvec3 * (FT)nsf );
    fi[1] = cxzero_sv<CT>();
    const int nh = nhel * nsf;
    const CT chi = cxmake<FT>( -(FT)nhel * fpsqrt<FT>( -2. * pvec3 ), 0. );
    fi[3] = cxzero_sv<CT>();
    fi[4] = cxzero_sv<CT>();
    if( nh == 1 )
    {
      fi[2] = cxzero_sv<CT>();
      fi[5] = chi;
    }
    else
    {
      fi[2] = chi;
      fi[5] = cxzero_sv<CT>();
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fi[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PT > 0)
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT >  __host__ __device__ void
  ixzxxx( const FT momenta[], // input: momenta
          //const FT fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          FT wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    const FT& pvec0 = M_ACCESS::kernelAccessIp4IparConst( momenta, 0, ipar );
    const FT& pvec1 = M_ACCESS::kernelAccessIp4IparConst( momenta, 1, ipar );
    const FT& pvec2 = M_ACCESS::kernelAccessIp4IparConst( momenta, 2, ipar );
    const FT& pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    FT* fi = W_ACCESS::kernelAccess( wavefunctions );
    //fi[0] = cxmake<FT>( -pvec0 * nsf, -pvec2 * nsf ); // AV: BUG! not the same as ixxxxx
    //fi[1] = cxmake<FT>( -pvec0 * nsf, -pvec1 * nsf ); // AV: BUG! not the same as ixxxxx
    fi[0] = cxmake<FT>( -pvec0 * (FT)nsf, -pvec3 * (FT)nsf ); // AV: BUG FIX
    fi[1] = cxmake<FT>( -pvec1 * (FT)nsf, -pvec2 * (FT)nsf ); // AV: BUG FIX
    const int nh = nhel * nsf;
    //const float sqp0p3 = sqrtf( pvec0 + pvec3 ) * nsf; // AV: why force a float here?
    const FT sqp0p3 = fpsqrt<FT>( pvec0 + pvec3 ) * (FT)nsf;
    const CT chi0 = cxmake<FT>( sqp0p3, 0. );
    const CT chi1 = cxmake<FT>( (FT)nh * pvec1 / sqp0p3, pvec2 / sqp0p3 );
    if( nh == 1 )
    {
      fi[2] = cxzero_sv<CT>();
      fi[3] = cxzero_sv<CT>();
      fi[4] = chi0;
      fi[5] = chi1;
    }
    else
    {
      fi[2] = chi1;
      fi[3] = chi0;
      fi[4] = cxzero_sv<CT>();
      fi[5] = cxzero_sv<CT>();
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction vc[6] from the input momenta[npar*4*nevt]
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT >  __host__ __device__ void
  vxxxxx( const FT momenta[], // input: momenta
          const FT vmass,     // input: vector boson mass
          const int nhel,         // input: -1, 0 (only if vmass!=0) or +1 (helicity of vector boson)
          const int nsv,          // input: +1 (final) or -1 (initial)
          FT wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    // NEW IMPLEMENTATION FIXING FLOATING POINT EXCEPTIONS IN SIMD CODE (#701)
    // Variables xxxDENOM are a hack to avoid division-by-0 FPE while preserving speed (#701 and #727)
    // Variables xxxDENOM are declared as 'volatile' to make sure they are not optimized away on clang! (#724)
    // A few additional variables are declared as 'volatile' to avoid sqrt-of-negative-number FPEs (#736)
    const FT& pvec0 = M_ACCESS::kernelAccessIp4IparConst( momenta, 0, ipar );
    const FT& pvec1 = M_ACCESS::kernelAccessIp4IparConst( momenta, 1, ipar );
    const FT& pvec2 = M_ACCESS::kernelAccessIp4IparConst( momenta, 2, ipar );
    const FT& pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    CT* vc = W_ACCESS::kernelAccess( wavefunctions );
    const FT sqh = fpsqrt<FT>( (FT)0.5 ); // AV this is > 0!
    const FT hel = nhel;
    vc[0] = cxmake<FT>( pvec0 * (FT)nsv, pvec3 * (FT)nsv );
    vc[1] = cxmake<FT>( pvec1 * (FT)nsv, pvec2 * (FT)nsv );
    if( vmass != 0. )
    {
      const int nsvahl = nsv * abs( hel );
      const FT hel0 = 1. - abs( hel );
#ifndef MGONGPU_CPPSIMD
      const FT pt2 = ( pvec1 * pvec1 ) + ( pvec2 * pvec2 );
      const FT pp = fpmin<FT>( pvec0, fpsqrt<FT>( pt2 + ( pvec3 * pvec3 ) ) );
      const FT pt = fpmin<FT>( pp, fpsqrt<FT>( pt2 ) );
      if( pp == 0. )
      {
        vc[2] = cxmake<FT>( 0., 0. );
        vc[3] = cxmake<FT>( -hel * sqh, 0. );
        vc[4] = cxmake<FT>( 0., nsvahl * sqh );
        vc[5] = cxmake<FT>( hel0, 0. );
      }
      else
      {
        //printf( "DEBUG1011 (before emp): pvec0=%f vmass=%f pp=%f vmass*pp=%f\n", pvec0, vmass, pp, vmass * pp );
        //const FT emp = pvec / ( vmass * pp ); // this may give a FPE #1011 (why?! maybe when vmass=+-epsilon?)
        const FT emp = pvec0 / vmass / pp; // workaround for FPE #1011
        //printf( "DEBUG1011 (after emp): emp=%f\n", emp );
        vc[2] = cxmake<FT>( hel0 * pp / vmass, 0. );
        vc[5] = cxmake<FT>( hel0 * pvec3 * emp + hel * pt / pp * sqh, 0. );
        if( pt != 0. )
        {
          const FT pzpt = pvec3 / ( pp * pt ) * sqh * hel;
          vc[3] = cxmake<FT>( hel0 * pvec1 * emp - pvec1 * pzpt, -nsvahl * pvec2 / pt * sqh );
          vc[4] = cxmake<FT>( hel0 * pvec2 * emp - pvec2 * pzpt, nsvahl * pvec1 / pt * sqh );
        }
        else
        {
          vc[3] = cxmake<FT>( -hel * sqh, 0. );
          // NB: Do not use "abs" for floats! It returns an integer with no build warning! Use std::abs!
          //vc[4] = cxmake<FT>( 0., nsvahl * ( pvec3 < 0. ? -abs( sqh ) : abs( sqh ) ) ); // AV: why abs here?
          vc[4] = cxmake<FT>( 0., nsvahl * ( pvec3 < 0. ? -sqh : sqh ) ); // AV: removed an abs here
        }
      }
#else
      volatile FT pt2 = ( pvec1 * pvec1 ) + ( pvec2 * pvec2 );
      volatile FT p2 = pt2 + ( pvec3 * pvec3 ); // volatile fixes #736
      const FT pp = fpmin<FT>( pvec0, fpsqrt<FT>( p2 ) );
      const FT pt = fpmin<FT>( pp, fpsqrt<FT>( pt2 ) );
      // Branch A: pp == 0.
      const CT vcA_2 = cxmake<FT>( 0, 0 );
      const CT vcA_3 = cxmake<FT>( -hel * sqh, 0 );
      const CT vcA_4 = cxmake<FT>( 0, nsvahl * sqh );
      const CT vcA_5 = cxmake<FT>( hel0, 0 );
      // Branch B: pp != 0.
      volatile FT_v ppDENOM = fpternary<FT>( pp != 0, pp, 1. ); // hack: ppDENOM[ieppV]=1 if pp[ieppV]==0
      const FT_v emp = pvec0 / ( vmass * ppDENOM );         // hack: dummy[ieppV] is not used if pp[ieppV]==0
      const CT vcB_2 = cxmake<FT>( hel0 * pp / vmass, 0 );
      const CT vcB_5 = cxmake<FT>( hel0 * pvec3 * emp + hel * pt / ppDENOM * sqh, 0 ); // hack: dummy[ieppV] is not used if pp[ieppV]==0
      // Branch B1: pp != 0. and pt != 0.
      volatile FT_v ptDENOM = fpternary<FT>( pt != 0, pt, 1. );                                                     // hack: ptDENOM[ieppV]=1 if pt[ieppV]==0
      const FT_v pzpt = pvec3 / ( ppDENOM * ptDENOM ) * sqh * hel;                                              // hack: dummy[ieppV] is not used if pp[ieppV]==0
      const CT vcB1_3 = cxmake<FT>( hel0 * pvec1 * emp - pvec1 * pzpt, -(FT)nsvahl * pvec2 / ptDENOM * sqh ); // hack: dummy[ieppV] is not used if pt[ieppV]==0
      const CT vcB1_4 = cxmake<FT>( hel0 * pvec2 * emp - pvec2 * pzpt, (FT)nsvahl * pvec1 / ptDENOM * sqh );  // hack: dummy[ieppV] is not used if pt[ieppV]==0
      // Branch B2: pp != 0. and pt == 0.
      const CT vcB2_3 = cxmake<FT>( -hel * sqh, 0. );
      const CT vcB2_4 = cxmake<FT>( 0., (FT)nsvahl * fpternary<FT>( ( pvec3 < 0 ), -sqh, sqh ) ); // AV: removed an abs here
      // Choose between the results from branch A and branch B (and from branch B1 and branch B2)
      const bool_v mask = ( pp == 0. );
      const bool_v maskB = ( pt != 0. );
      vc[2] = cxternary( mask, vcA_2, vcB_2 );
      vc[3] = cxternary( mask, vcA_3, cxternary( maskB, vcB1_3, vcB2_3 ) );
      vc[4] = cxternary( mask, vcA_4, cxternary( maskB, vcB1_4, vcB2_4 ) );
      vc[5] = cxternary( mask, vcA_5, vcB_5 );
#endif
    }
    else
    {
      const FT& pp = pvec0; // NB: rewrite the following as in Fortran, using pp instead of pvec0
#ifndef MGONGPU_CPPSIMD
      const FT pt = fpsqrt<FT>( ( pvec1 * pvec1 ) + ( pvec2 * pvec2 ) );
#else
      volatile FT pt2 = pvec1 * pvec1 + pvec2 * pvec2; // volatile fixes #736
      const FT pt = fpsqrt<FT>( pt2 );
#endif
      vc[2] = cxzero_sv<CT>();
      vc[5] = cxmake<FT>( hel * pt / pp * sqh, 0. );
#ifndef MGONGPU_CPPSIMD
      if( pt != 0. )
      {
        const FT pzpt = pvec3 / ( pp * pt ) * sqh * hel;
        vc[3] = cxmake<FT>( -pvec1 * pzpt, -nsv * pvec2 / pt * sqh );
        vc[4] = cxmake<FT>( -pvec2 * pzpt, nsv * pvec1 / pt * sqh );
      }
      else
      {
        vc[3] = cxmake<FT>( -hel * sqh, 0. );
        // NB: Do not use "abs" for floats! It returns an integer with no build warning! Use std::abs!
        //vc[4] = cxmake<FT>( 0, nsv * ( pvec3 < 0. ? -abs( sqh ) : abs( sqh ) ) ); // AV why abs here?
        vc[4] = cxmake<FT>( 0., nsv * ( pvec3 < 0. ? -sqh : sqh ) ); // AV: removed an abs here
      }
#else
      // Branch A: pt != 0.
      volatile FT_v ptDENOM = fpternary<FT>( pt != 0, pt, 1. );                             // hack: ptDENOM[ieppV]=1 if pt[ieppV]==0
      const FT_v pzpt = pvec3 / ( pp * ptDENOM ) * sqh * hel;                           // hack: dummy[ieppV] is not used if pt[ieppV]==0
      const CT vcA_3 = cxmake<FT>( -pvec1 * pzpt, -(FT)nsv * pvec2 / ptDENOM * sqh ); // hack: dummy[ieppV] is not used if pt[ieppV]==0
      const CT vcA_4 = cxmake<FT>( -pvec2 * pzpt, (FT)nsv * pvec1 / ptDENOM * sqh );  // hack: dummy[ieppV] is not used if pt[ieppV]==0
      // Branch B: pt == 0.
      const CT vcB_3 = cxmake<FT>( -(FT)hel * sqh, 0 );
      const CT vcB_4 = cxmake<FT>( 0, (FT)nsv * fpternary<FT>( ( pvec3 < 0 ), -sqh, sqh ) ); // AV: removed an abs here
      // Choose between the results from branch A and branch B
      const bool_v mask = ( pt != 0. );
      vc[3] = cxternary( mask, vcA_3, vcB_3 );
      vc[4] = cxternary( mask, vcA_4, vcB_4 );
#endif
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction sc[3] from the input momenta[npar*4*nevt]
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT >  __host__ __device__ void
  sxxxxx( const FT momenta[], // input: momenta
          //const FT,                 // WARNING: input "smass" unused (missing in Fortran) - scalar boson mass
          //const int,                    // WARNING: input "nhel" unused (missing in Fortran) - scalar has no helicity!
          const int nss,          // input: +1 (final) or -1 (initial)
          FT wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    const FT& pvec0 = M_ACCESS::kernelAccessIp4IparConst( momenta, 0, ipar );
    const FT& pvec1 = M_ACCESS::kernelAccessIp4IparConst( momenta, 1, ipar );
    const FT& pvec2 = M_ACCESS::kernelAccessIp4IparConst( momenta, 2, ipar );
    const FT& pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    FT* sc = W_ACCESS::kernelAccess( wavefunctions );
    sc[2] = cxmake<FT>( 1 + FT{ 0 }, 0 );
    sc[0] = cxmake<FT>( pvec0 * (FT)nss, pvec3 * (FT)nss );
    sc[1] = cxmake<FT>( pvec1 * (FT)nss, pvec2 * (FT)nss );
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fo[6] from the input momenta[npar*4*nevt]
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT >  __host__ __device__ void
  oxxxxx( const FT momenta[], // input: momenta
          const FT fmass,     // input: fermion mass
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          FT wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    // NEW IMPLEMENTATION FIXING FLOATING POINT EXCEPTIONS IN SIMD CODE (#701)
    // Variables xxxDENOM are a hack to avoid division-by-0 FPE while preserving speed (#701 and #727)
    // Variables xxxDENOM are declared as 'volatile' to make sure they are not optimized away on clang! (#724)
    // A few additional variables are declared as 'volatile' to avoid sqrt-of-negative-number FPEs (#736)
    const FT& pvec0 = M_ACCESS::kernelAccessIp4IparConst( momenta, 0, ipar );
    const FT& pvec1 = M_ACCESS::kernelAccessIp4IparConst( momenta, 1, ipar );
    const FT& pvec2 = M_ACCESS::kernelAccessIp4IparConst( momenta, 2, ipar );
    const FT& pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    CT* fo = W_ACCESS::kernelAccess( wavefunctions );
    fo[0] = cxmake<FT>( pvec0 * (FT)nsf, pvec3 * (FT)nsf );
    fo[1] = cxmake<FT>( pvec1 * (FT)nsf, pvec2 * (FT)nsf );
    const int nh = nhel * nsf;
    if( fmass != 0. )
    {
#ifndef MGONGPU_CPPSIMD
      const FT pp = fpmin<FT>( pvec0, fpsqrt<FT>( ( pvec1 * pvec1 ) + ( pvec2 * pvec2 ) + ( pvec3 * pvec3 ) ) );
      if( pp == 0. )
      {
        // NB: Do not use "abs" for floats! It returns an integer with no build warning! Use std::abs!
        FT sqm[2] = { fpsqrt<FT>( abs( fmass ) ), 0. }; // possibility of negative fermion masses
        //sqm[1] = ( fmass < 0. ? -abs( sqm[0] ) : abs( sqm[0] ) ); // AV: why abs here?
        sqm[1] = ( fmass < 0. ? -sqm[0] : sqm[0] ); // AV: removed an abs here
        const int ip = -( ( 1 - nh ) / 2 ) * nhel;  // NB: Fortran sqm(0:1) also has indexes 0,1 as in C++
        const int im = ( 1 + nh ) / 2 * nhel;       // NB: Fortran sqm(0:1) also has indexes 0,1 as in C++
        fo[2] = cxmake<FT>( im * sqm[abs( ip )], 0 );
        fo[3] = cxmake<FT>( ip * nsf * sqm[abs( ip )], 0 );
        fo[4] = cxmake<FT>( im * nsf * sqm[abs( im )], 0 );
        fo[5] = cxmake<FT>( ip * sqm[abs( im )], 0 );
      }
      else
      {
        const FT sf[2] = { FT( 1 + nsf + ( 1 - nsf ) * nh ) * (FT)0.5,
                               FT( 1 + nsf - ( 1 - nsf ) * nh ) * (FT)0.5 };
        FT omega[2] = { fpsqrt<FT>( pvec0 + pp ), 0. };
        omega[1] = fmass / omega[0];
        const int ip = ( 1 + nh ) / 2; // NB: Fortran is (3+nh)/2 because omega(2) has indexes 1,2 and not 0,1
        const int im = ( 1 - nh ) / 2; // NB: Fortran is (3-nh)/2 because omega(2) has indexes 1,2 and not 0,1
        const FT sfomeg[2] = { sf[0] * omega[ip], sf[1] * omega[im] };
        const FT pp3 = fpmax<FT>( pp + pvec3, 0. );
        const CT chi[2] = { cxmake<FT>( fpsqrt<FT>( pp3 * (FT)0.5 / pp ), 0. ),
                                ( ( pp3 == 0. ) ? cxmake<FT>( -nh, 0. )
                                                : cxmake<FT>( nh * pvec1, -pvec2 ) / fpsqrt<FT>( 2. * pp * pp3 ) ) };
        fo[2] = sfomeg[1] * chi[im];
        fo[3] = sfomeg[1] * chi[ip];
        fo[4] = sfomeg[0] * chi[im];
        fo[5] = sfomeg[0] * chi[ip];
      }
#else
      volatile FT p2 = pvec1 * pvec1 + pvec2 * pvec2 + pvec3 * pvec3; // volatile fixes #736
      const FT pp = fpmin<FT>( pvec0, fpsqrt<FT>( p2 ) );
      // Branch A: pp == 0.
      // NB: Do not use "abs" for floats! It returns an integer with no build warning! Use std::abs!
      FT sqm[2] = { fpsqrt<FT>( abs( fmass ) ), 0 }; // possibility of negative fermion masses
      sqm[1] = ( fmass < 0 ? -sqm[0] : sqm[0] );          // AV: removed an abs here (as above)
      const int ipA = -( ( 1 - nh ) / 2 ) * nhel;
      const int imA = ( 1 + nh ) / 2 * nhel;
      const CT foA_2 = imA * sqm[abs( ipA )];
      const CT foA_3 = ipA * nsf * sqm[abs( ipA )];
      const CT foA_4 = imA * nsf * sqm[abs( imA )];
      const CT foA_5 = ipA * sqm[abs( imA )];
      // Branch B: pp != 0.
      const FT sf[2] = { FT( 1 + nsf + ( 1 - nsf ) * nh ) * (FT)0.5,
                             FT( 1 + nsf - ( 1 - nsf ) * nh ) * (FT)0.5 };
      FT_v omega[2] = { fpsqrt<FT>( pvec0 + pp ), 0 };
      omega[1] = fmass / omega[0];
      const int ipB = ( 1 + nh ) / 2;
      const int imB = ( 1 - nh ) / 2;
      const FT_v sfomeg[2] = { sf[0] * omega[ipB], sf[1] * omega[imB] };
      const FT_v pp3 = fpmax<FT>( pp + pvec3, 0. );
      volatile FT_v ppDENOM = fpternary<FT>( pp != 0, pp, 1. );    // hack: ppDENOM[ieppV]=1 if pp[ieppV]==0
      volatile FT_v pp3DENOM = fpternary<FT>( pp3 != 0, pp3, 1. ); // hack: pp3DENOM[ieppV]=1 if pp3[ieppV]==0
      volatile FT_v chi0r2 = pp3 * 0.5 / ppDENOM;              // volatile fixes #736
      const CT chi[2] = { cxmake<FT>( fpsqrt<FT>( chi0r2 ), 0. ),    // hack: dummy[ieppV] is not used if pp[ieppV]==0
                                ( cxternary( ( pp3 == 0. ),
                                             cxmake<FT>( -nh, 0. ),
                                             cxmake<FT>( (FT)nh * pvec1, -pvec2 ) / fpsqrt<FT>( 2. * ppDENOM * pp3DENOM ) ) ) }; // hack: dummy[ieppV] is not used if pp[ieppV]==0
      const CT foB_2 = sfomeg[1] * chi[imB];
      const CT foB_3 = sfomeg[1] * chi[ipB];
      const CT foB_4 = sfomeg[0] * chi[imB];
      const CT foB_5 = sfomeg[0] * chi[ipB];
      // Choose between the results from branch A and branch B
      const bool_v mask = ( pp == 0. );
      fo[2] = cxternary( mask, foA_2, foB_2 );
      fo[3] = cxternary( mask, foA_3, foB_3 );
      fo[4] = cxternary( mask, foA_4, foB_4 );
      fo[5] = cxternary( mask, foA_5, foB_5 );
#endif
    }
    else
    {
#ifdef MGONGPU_CPPSIMD
      volatile FT p0p3 = fpmax<FT>( pvec0 + pvec3, 0 ); // volatile fixes #736
      volatile FT sqp0p3 = fpternary<FT>( ( pvec1 == 0. and pvec2 == 0. and pvec3 < 0. ),
                                             FT{ 0 },
                                             fpsqrt<FT>( p0p3 ) * (FT)nsf );
      volatile FT_v sqp0p3DENOM = fpternary<FT>( sqp0p3 != 0, (FT)sqp0p3, 1. ); // hack: sqp0p3DENOM[ieppV]=1 if sqp0p3[ieppV]==0
      const CT chi[2] = { cxmake<FT>( (FT_v)sqp0p3, 0. ),
                                cxternary( ( sqp0p3 == 0. ),
                                           cxmake<FT>( -nhel, 0. ) * fpsqrt<FT>( 2. * pvec0 ),
                                           cxmake<FT>( (FT)nh * pvec1, -pvec2 ) / (const FT)sqp0p3DENOM ) }; // hack: dummy[ieppV] is not used if sqp0p3[ieppV]==0
#else
      const FT sqp0p3 = fpternary<FT>( ( pvec1 == 0. ) and ( pvec2 == 0. ) and ( pvec3 < 0. ),
                                          0,
                                          fpsqrt<FT>( fpmax<FT>( pvec0 + pvec3, 0. ) ) * (FT)nsf );
      const CT chi[2] = { cxmake<FT>( sqp0p3, 0. ),
                                 ( sqp0p3 == 0. ? cxmake<FT>( -nhel, 0. ) * fpsqrt<FT>( 2. * pvec0 ) : cxmake<FT>( (FT)nh * pvec1, -pvec2 ) / sqp0p3 ) };
#endif
      if( nh == 1 )
      {
        fo[2] = chi[0];
        fo[3] = chi[1];
        fo[4] = cxzero_sv<CT>();
        fo[5] = cxzero_sv<CT>();
      }
      else
      {
        fo[2] = cxzero_sv<CT>();
        fo[3] = cxzero_sv<CT>();
        fo[4] = chi[1];
        fo[5] = chi[0];
      }
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fo[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PX == PY == 0 and E == +PZ > 0)
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT >
  __host__ __device__ void
  opzxxx( const FT momenta[], // input: momenta
          //const FT fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          FT wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    const FT& pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    FT* fo = W_ACCESS::kernelAccess( wavefunctions );
    fo[0] = cxmake<FT>( pvec3 * (FT)nsf, pvec3 * (FT)nsf );
    fo[1] = cxzero_sv<CT>();
    const int nh = nhel * nsf;
    const FT csqp0p3 = cxmake<FT>( fpsqrt<FT>( 2. * pvec3 ) * (FT)nsf, 0. );
    fo[3] = cxzero_sv<CT>();
    fo[4] = cxzero_sv<CT>();
    if( nh == 1 )
    {
      fo[2] = csqp0p3;
      fo[5] = cxzero_sv<CT>();
    }
    else
    {
      fo[2] = cxzero_sv<CT>();
      fo[5] = csqp0p3;
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fo[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PX == PY == 0 and E == -PZ > 0)
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT >  __host__ __device__ void
  omzxxx( const FT momenta[], // input: momenta
          //const FT fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          FT wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    const FT& pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    FT* fo = W_ACCESS::kernelAccess( wavefunctions );
    fo[0] = cxmake<FT>( -pvec3 * (FT)nsf, pvec3 * (FT)nsf ); // remember pvec0 == -pvec3
    fo[1] = cxzero_sv<CT>();
    const int nh = nhel * nsf;
    const CT chi1 = cxmake<FT>( -nhel, 0. ) * fpsqrt<FT>( -2. * pvec3 );
    if( nh == 1 )
    {
      fo[2] = cxzero_sv<CT>();
      fo[3] = chi1;
      fo[4] = cxzero_sv<CT>();
      fo[5] = cxzero_sv<CT>();
    }
    else
    {
      fo[2] = cxzero_sv<CT>();
      fo[3] = cxzero_sv<CT>();
      fo[4] = chi1;
      //fo[5] = chi1; // AV: BUG!
      fo[5] = cxzero_sv<CT>(); // AV: BUG FIX
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fo[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PT > 0)
  template<class M_ACCESS, class W_ACCESS, typename FT, typename CT >  __host__ __device__ void
  oxzxxx( const FT momenta[], // input: momenta
          //const FT fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          FT wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    const FT& pvec0 = M_ACCESS::kernelAccessIp4IparConst( momenta, 0, ipar );
    const FT& pvec1 = M_ACCESS::kernelAccessIp4IparConst( momenta, 1, ipar );
    const FT& pvec2 = M_ACCESS::kernelAccessIp4IparConst( momenta, 2, ipar );
    const FT& pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    FT* fo = W_ACCESS::kernelAccess( wavefunctions );
    fo[0] = cxmake<FT>( pvec0 * (FT)nsf, pvec3 * (FT)nsf );
    fo[1] = cxmake<FT>( pvec1 * (FT)nsf, pvec2 * (FT)nsf );
    const int nh = nhel * nsf;
    //const float sqp0p3 = sqrtf( pvec0 + pvec3 ) * nsf; // AV: why force a float here?
    const FT sqp0p3 = fpsqrt<FT>( pvec0 + pvec3 ) * (FT)nsf;
    const CT chi0 = cxmake<FT>( sqp0p3, 0. );
    const CT chi1 = cxmake<FT>( (FT)nh * pvec1 / sqp0p3, -pvec2 / sqp0p3 );
    if( nh == 1 )
    {
      fo[2] = chi0;
      fo[3] = chi1;
      fo[4] = cxzero_sv<CT>();
      fo[5] = cxzero_sv<CT>();
    }
    else
    {
      fo[2] = cxzero_sv<CT>();
      fo[3] = cxzero_sv<CT>();
      fo[4] = chi1;
      fo[5] = chi0;
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //==========================================================================

  // Compute the output amplitude 'vertex' from the input wavefunctions V1[6], V2[6], V3[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS, typename FT, typename CT = cxsmpl<FT>>
  __device__ INLINE void
  VVV1_0( const FT allV1[],
          const FT allV2[],
          const FT allV3[],
          const FT allCOUP[],
          const FT Ccoeff,
          FT allvertexes[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V1[6]' from the input wavefunctions V2[6], V3[6]
  template<class W_ACCESS, class C_ACCESS, typename FT, typename CT = cxsmpl<FT>>

  __device__ INLINE void
  VVV1P0_1( const FT allV2[],
            const FT allV3[],
            const FT allCOUP[],
            const FT Ccoeff,
            const FT M1,
            const FT W1,
            FT allV1[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions F1[6], F2[6], V3[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS, typename FT, typename CT = cxsmpl<FT>>
  __device__ INLINE void
  FFV1_0( const FT allF1[],
          const FT allF2[],
          const FT allV3[],
          const FT allCOUP[],
          const FT Ccoeff,
          FT allvertexes[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'F1[6]' from the input wavefunctions F2[6], V3[6]
  template<class W_ACCESS, class C_ACCESS, typename FT, typename CT = cxsmpl<FT>>
  __device__ INLINE void
  FFV1_1( const FT allF2[],
          const FT allV3[],
          const FT allCOUP[],
          const FT Ccoeff,
          const FT M1,
          const FT W1,
          FT allF1[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'F2[6]' from the input wavefunctions F1[6], V3[6]
  template<class W_ACCESS, class C_ACCESS, typename FT, typename CT = cxsmpl<FT>>
  __device__ INLINE void
  FFV1_2( const FT allF1[],
          const FT allV3[],
          const FT allCOUP[],
          const FT Ccoeff,
          const FT M2,
          const FT W2,
          FT allF2[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V3[6]' from the input wavefunctions F1[6], F2[6]
  template<class W_ACCESS, class C_ACCESS, typename FT, typename CT = cxsmpl<FT>>
  __device__ INLINE void
  FFV1P0_3( const FT allF1[],
            const FT allF2[],
            const FT allCOUP[],
            const FT Ccoeff,
            const FT M3,
            const FT W3,
            FT allV3[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions V1[6], V2[6], V3[6], V4[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS, typename FT, typename CT = cxsmpl<FT>>
  __device__ INLINE void
  VVVV1_0( const FT allV1[],
           const FT allV2[],
           const FT allV3[],
           const FT allV4[],
           const FT allCOUP[],
           const FT Ccoeff,
           FT allvertexes[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V1[6]' from the input wavefunctions V2[6], V3[6], V4[6]
  template<class W_ACCESS, class C_ACCESS, typename FT, typename CT = cxsmpl<FT>>
  __device__ INLINE void
  VVVV1P0_1( const FT allV2[],
             const FT allV3[],
             const FT allV4[],
             const FT allCOUP[],
             const FT Ccoeff,
             const FT M1,
             const FT W1,
             FT allV1[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions V1[6], V2[6], V3[6], V4[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS, typename FT, typename CT = cxsmpl<FT>>
  __device__ INLINE void
  VVVV3_0( const FT allV1[],
           const FT allV2[],
           const FT allV3[],
           const FT allV4[],
           const FT allCOUP[],
           const FT Ccoeff,
           FT allvertexes[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V1[6]' from the input wavefunctions V2[6], V3[6], V4[6]
  template<class W_ACCESS, class C_ACCESS, typename FT, typename CT = cxsmpl<FT>>
  __device__ INLINE void
  VVVV3P0_1( const FT allV2[],
             const FT allV3[],
             const FT allV4[],
             const FT allCOUP[],
             const FT Ccoeff,
             const FT M1,
             const FT W1,
             FT allV1[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions V1[6], V2[6], V3[6], V4[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS, typename FT, typename CT = cxsmpl<FT>>
  __device__ INLINE void
  VVVV4_0( const FT allV1[],
           const FT allV2[],
           const FT allV3[],
           const FT allV4[],
           const FT allCOUP[],
           const FT Ccoeff,
           FT allvertexes[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V1[6]' from the input wavefunctions V2[6], V3[6], V4[6]
  template<class W_ACCESS, class C_ACCESS, typename FT, typename CT = cxsmpl<FT>>
  __device__ INLINE void
  VVVV4P0_1( const FT allV2[],
             const FT allV3[],
             const FT allV4[],
             const FT allCOUP[],
             const FT Ccoeff,
             const FT M1,
             const FT W1,
             FT allV1[] ) ALWAYS_INLINE;

  //==========================================================================

  // Compute the output amplitude 'vertex' from the input wavefunctions V1[6], V2[6], V3[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS, typename FT, typename CT >
  __device__ void
  VVV1_0( const FT allV1[],
          const FT allV2[],
          const FT allV3[],
          const FT allCOUP[],
          const FT Ccoeff,
          FT allvertexes[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const CT* V1 = W_ACCESS::kernelAccessConst( allV1 );
    const CT* V2 = W_ACCESS::kernelAccessConst( allV2 );
    const CT* V3 = W_ACCESS::kernelAccessConst( allV3 );
    const CT COUP = C_ACCESS::kernelAccessConst( allCOUP );
    CT*  vertex = A_ACCESS::kernelAccess( allvertexes );
    const CT cI = cxmake<FT>( 0., 1. );
    const FT P1[4] = { +cxreal( V1[0] ), +cxreal( V1[1] ), +cximag( V1[1] ), +cximag( V1[0] ) };
    const FT P2[4] = { +cxreal( V2[0] ), +cxreal( V2[1] ), +cximag( V2[1] ), +cximag( V2[0] ) };
    const FT P3[4] = { +cxreal( V3[0] ), +cxreal( V3[1] ), +cximag( V3[1] ), +cximag( V3[0] ) };
    const CT TMP0 = ( V3[2] * P1[0] - V3[3] * P1[1] - V3[4] * P1[2] - V3[5] * P1[3] );
    const CT TMP1 = ( V2[2] * V1[2] - V2[3] * V1[3] - V2[4] * V1[4] - V2[5] * V1[5] );
    const CT TMP2 = ( V3[2] * P2[0] - V3[3] * P2[1] - V3[4] * P2[2] - V3[5] * P2[3] );
    const CT TMP3 = ( V3[2] * V1[2] - V3[3] * V1[3] - V3[4] * V1[4] - V3[5] * V1[5] );
    const CT TMP4 = ( P1[0] * V2[2] - P1[1] * V2[3] - P1[2] * V2[4] - P1[3] * V2[5] );
    const CT TMP5 = ( V2[2] * P3[0] - V2[3] * P3[1] - V2[4] * P3[2] - V2[5] * P3[3] );
    const CT TMP6 = ( V3[2] * V2[2] - V3[3] * V2[3] - V3[4] * V2[4] - V3[5] * V2[5] );
    const CT TMP7 = ( V1[2] * P2[0] - V1[3] * P2[1] - V1[4] * P2[2] - V1[5] * P2[3] );
    const CT TMP8 = ( V1[2] * P3[0] - V1[3] * P3[1] - V1[4] * P3[2] - V1[5] * P3[3] );
    ( *vertex ) = Ccoeff * COUP * ( TMP1 * ( -cI * TMP0 + cI * TMP2 ) + ( TMP3 * ( +cI * TMP4 - cI * TMP5 ) + TMP6 * ( -cI * TMP7 + cI * TMP8 ) ) );
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V1[6]' from the input wavefunctions V2[6], V3[6]
  template<class W_ACCESS, class C_ACCESS, typename FT, typename CT >
  __device__ void
  VVV1P0_1( const FT allV2[],
            const FT allV3[],
            const FT allCOUP[],
            const FT Ccoeff,
            const FT M1,
            const FT W1,
            FT allV1[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const CT* V2 = W_ACCESS::kernelAccessConst( allV2 );
    const CT* V3 = W_ACCESS::kernelAccessConst( allV3 );
    const CT COUP = C_ACCESS::kernelAccessConst( allCOUP );
     CT* V1 = W_ACCESS::kernelAccess( allV1 );
    const CT cI = cxmake<FT>( 0., 1. );
    const FT P2[4] = { +cxreal( V2[0] ), +cxreal( V2[1] ), +cximag( V2[1] ), +cximag( V2[0] ) };
    const FT P3[4] = { +cxreal( V3[0] ), +cxreal( V3[1] ), +cximag( V3[1] ), +cximag( V3[0] ) };
    V1[0] = +V2[0] + V3[0];
    V1[1] = +V2[1] + V3[1];
    const FT P1[4] = { -cxreal( V1[0] ), -cxreal( V1[1] ), -cximag( V1[1] ), -cximag( V1[0] ) };
    const CT TMP0 = ( V3[2] * P1[0] - V3[3] * P1[1] - V3[4] * P1[2] - V3[5] * P1[3] );
    const CT TMP2 = ( V3[2] * P2[0] - V3[3] * P2[1] - V3[4] * P2[2] - V3[5] * P2[3] );
    const CT TMP4 = ( P1[0] * V2[2] - P1[1] * V2[3] - P1[2] * V2[4] - P1[3] * V2[5] );
    const CT TMP5 = ( V2[2] * P3[0] - V2[3] * P3[1] - V2[4] * P3[2] - V2[5] * P3[3] );
    const CT TMP6 = ( V3[2] * V2[2] - V3[3] * V2[3] - V3[4] * V2[4] - V3[5] * V2[5] );
    const  CT denom = Ccoeff * COUP / ( ( P1[0] * P1[0] ) - ( P1[1] * P1[1] ) - ( P1[2] * P1[2] ) - ( P1[3] * P1[3] ) - M1 * ( M1 - cI * W1 ) );
    V1[2] = denom * ( TMP6 * ( -cI * P2[0] + cI * P3[0] ) + ( V2[2] * ( -cI * TMP0 + cI * TMP2 ) + V3[2] * ( +cI * TMP4 - cI * TMP5 ) ) );
    V1[3] = denom * ( TMP6 * ( -cI * P2[1] + cI * P3[1] ) + ( V2[3] * ( -cI * TMP0 + cI * TMP2 ) + V3[3] * ( +cI * TMP4 - cI * TMP5 ) ) );
    V1[4] = denom * ( TMP6 * ( -cI * P2[2] + cI * P3[2] ) + ( V2[4] * ( -cI * TMP0 + cI * TMP2 ) + V3[4] * ( +cI * TMP4 - cI * TMP5 ) ) );
    V1[5] = denom * ( TMP6 * ( -cI * P2[3] + cI * P3[3] ) + ( V2[5] * ( -cI * TMP0 + cI * TMP2 ) + V3[5] * ( +cI * TMP4 - cI * TMP5 ) ) );
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions F1[6], F2[6], V3[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS, typename FT, typename CT >
  __device__ void
  FFV1_0( const FT allF1[],
          const FT allF2[],
          const FT allV3[],
          const FT allCOUP[],
          const FT Ccoeff,
          FT allvertexes[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const CT* F1 = W_ACCESS::kernelAccessConst( allF1 );
    const CT* F2 = W_ACCESS::kernelAccessConst( allF2 );
    const CT* V3 = W_ACCESS::kernelAccessConst( allV3 );
    const CT COUP = C_ACCESS::kernelAccessConst( allCOUP );
    CT*  vertex = A_ACCESS::kernelAccess( allvertexes );
    const CT cI = cxmake<FT>( 0., 1. );
    const CT TMP9 = ( F1[2] * ( F2[4] * ( V3[2] + V3[5] ) + F2[5] * ( V3[3] + cI * V3[4] ) ) + ( F1[3] * ( F2[4] * ( V3[3] - cI * V3[4] ) + F2[5] * ( V3[2] - V3[5] ) ) + ( F1[4] * ( F2[2] * ( V3[2] - V3[5] ) - F2[3] * ( V3[3] + cI * V3[4] ) ) + F1[5] * ( F2[2] * ( -V3[3] + cI * V3[4] ) + F2[3] * ( V3[2] + V3[5] ) ) ) ) );
    ( *vertex ) = Ccoeff * COUP * -cI * TMP9;
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'F1[6]' from the input wavefunctions F2[6], V3[6]
  template<class W_ACCESS, class C_ACCESS, typename FT, typename CT >
  __device__ void
  FFV1_1( const FT allF2[],
          const FT allV3[],
          const FT allCOUP[],
          const FT Ccoeff,
          const FT M1,
          const FT W1,
          FT allF1[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const CT* F2 = W_ACCESS::kernelAccessConst( allF2 );
    const CT* V3 = W_ACCESS::kernelAccessConst( allV3 );
    const CT COUP = C_ACCESS::kernelAccessConst( allCOUP );
    CT* F1 = W_ACCESS::kernelAccess( allF1 );
    const CT cI = cxmake<FT>( 0., 1. );
    F1[0] = +F2[0] + V3[0];
    F1[1] = +F2[1] + V3[1];
    const FT P1[4] = { -cxreal( F1[0] ), -cxreal( F1[1] ), -cximag( F1[1] ), -cximag( F1[0] ) };
    const FT one( 1. );
    const  CT denom = Ccoeff * COUP / ( ( P1[0] * P1[0] ) - ( P1[1] * P1[1] ) - ( P1[2] * P1[2] ) - ( P1[3] * P1[3] ) - M1 * ( M1 - cI * W1 ) );
    F1[2] = denom * cI * ( F2[2] * ( P1[0] * ( -V3[2] + V3[5] ) + ( P1[1] * ( V3[3] - cI * V3[4] ) + ( P1[2] * ( +cI * V3[3] + V3[4] ) + P1[3] * ( -V3[2] + V3[5] ) ) ) ) + ( F2[3] * ( P1[0] * ( V3[3] + cI * V3[4] ) + ( P1[1] * ( -one ) * ( V3[2] + V3[5] ) + ( P1[2] * ( -one ) * ( +cI * ( V3[2] + V3[5] ) ) + P1[3] * ( V3[3] + cI * V3[4] ) ) ) ) + M1 * ( F2[4] * ( V3[2] + V3[5] ) + F2[5] * ( V3[3] + cI * V3[4] ) ) ) );
    F1[3] = denom * ( -cI ) * ( F2[2] * ( P1[0] * ( -V3[3] + cI * V3[4] ) + ( P1[1] * ( V3[2] - V3[5] ) + ( P1[2] * ( -cI * V3[2] + cI * V3[5] ) + P1[3] * ( V3[3] - cI * V3[4] ) ) ) ) + ( F2[3] * ( P1[0] * ( V3[2] + V3[5] ) + ( P1[1] * ( -one ) * ( V3[3] + cI * V3[4] ) + ( P1[2] * ( +cI * V3[3] - V3[4] ) - P1[3] * ( V3[2] + V3[5] ) ) ) ) + M1 * ( F2[4] * ( -V3[3] + cI * V3[4] ) + F2[5] * ( -V3[2] + V3[5] ) ) ) );
    F1[4] = denom * ( -cI ) * ( F2[4] * ( P1[0] * ( V3[2] + V3[5] ) + ( P1[1] * ( -V3[3] + cI * V3[4] ) + ( P1[2] * ( -one ) * ( +cI * V3[3] + V3[4] ) - P1[3] * ( V3[2] + V3[5] ) ) ) ) + ( F2[5] * ( P1[0] * ( V3[3] + cI * V3[4] ) + ( P1[1] * ( -V3[2] + V3[5] ) + ( P1[2] * ( -cI * V3[2] + cI * V3[5] ) - P1[3] * ( V3[3] + cI * V3[4] ) ) ) ) + M1 * ( F2[2] * ( -V3[2] + V3[5] ) + F2[3] * ( V3[3] + cI * V3[4] ) ) ) );
    F1[5] = denom * cI * ( F2[4] * ( P1[0] * ( -V3[3] + cI * V3[4] ) + ( P1[1] * ( V3[2] + V3[5] ) + ( P1[2] * ( -one ) * ( +cI * ( V3[2] + V3[5] ) ) + P1[3] * ( -V3[3] + cI * V3[4] ) ) ) ) + ( F2[5] * ( P1[0] * ( -V3[2] + V3[5] ) + ( P1[1] * ( V3[3] + cI * V3[4] ) + ( P1[2] * ( -cI * V3[3] + V3[4] ) + P1[3] * ( -V3[2] + V3[5] ) ) ) ) + M1 * ( F2[2] * ( -V3[3] + cI * V3[4] ) + F2[3] * ( V3[2] + V3[5] ) ) ) );
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'F2[6]' from the input wavefunctions F1[6], V3[6]
  template<class W_ACCESS, class C_ACCESS, typename FT, typename CT >
  __device__ void
  FFV1_2( const FT allF1[],
          const FT allV3[],
          const FT allCOUP[],
          const FT Ccoeff,
          const FT M2,
          const FT W2,
          FT allF2[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const CT* F1 = W_ACCESS::kernelAccessConst( allF1 );
    const CT* V3 = W_ACCESS::kernelAccessConst( allV3 );
    const CT COUP = C_ACCESS::kernelAccessConst( allCOUP );
    CT* F2 = W_ACCESS::kernelAccess( allF2 );
    const CT cI = cxmake<FT>( 0., 1. );
    F2[0] = +F1[0] + V3[0];
    F2[1] = +F1[1] + V3[1];
    const FT P2[4] = { -cxreal( F2[0] ), -cxreal( F2[1] ), -cximag( F2[1] ), -cximag( F2[0] ) };
    const FT one( 1. );
    const  CT denom = Ccoeff * COUP / ( ( P2[0] * P2[0] ) - ( P2[1] * P2[1] ) - ( P2[2] * P2[2] ) - ( P2[3] * P2[3] ) - M2 * ( M2 - cI * W2 ) );
    F2[2] = denom * cI * ( F1[2] * ( P2[0] * ( V3[2] + V3[5] ) + ( P2[1] * ( -one ) * ( V3[3] + cI * V3[4] ) + ( P2[2] * ( +cI * V3[3] - V3[4] ) - P2[3] * ( V3[2] + V3[5] ) ) ) ) + ( F1[3] * ( P2[0] * ( V3[3] - cI * V3[4] ) + ( P2[1] * ( -V3[2] + V3[5] ) + ( P2[2] * ( +cI * V3[2] - cI * V3[5] ) + P2[3] * ( -V3[3] + cI * V3[4] ) ) ) ) + M2 * ( F1[4] * ( V3[2] - V3[5] ) + F1[5] * ( -V3[3] + cI * V3[4] ) ) ) );
    F2[3] = denom * ( -cI ) * ( F1[2] * ( P2[0] * ( -one ) * ( V3[3] + cI * V3[4] ) + ( P2[1] * ( V3[2] + V3[5] ) + ( P2[2] * ( +cI * ( V3[2] + V3[5] ) ) - P2[3] * ( V3[3] + cI * V3[4] ) ) ) ) + ( F1[3] * ( P2[0] * ( -V3[2] + V3[5] ) + ( P2[1] * ( V3[3] - cI * V3[4] ) + ( P2[2] * ( +cI * V3[3] + V3[4] ) + P2[3] * ( -V3[2] + V3[5] ) ) ) ) + M2 * ( F1[4] * ( V3[3] + cI * V3[4] ) - F1[5] * ( V3[2] + V3[5] ) ) ) );
    F2[4] = denom * ( -cI ) * ( F1[4] * ( P2[0] * ( -V3[2] + V3[5] ) + ( P2[1] * ( V3[3] + cI * V3[4] ) + ( P2[2] * ( -cI * V3[3] + V3[4] ) + P2[3] * ( -V3[2] + V3[5] ) ) ) ) + ( F1[5] * ( P2[0] * ( V3[3] - cI * V3[4] ) + ( P2[1] * ( -one ) * ( V3[2] + V3[5] ) + ( P2[2] * ( +cI * ( V3[2] + V3[5] ) ) + P2[3] * ( V3[3] - cI * V3[4] ) ) ) ) + M2 * ( F1[2] * ( -one ) * ( V3[2] + V3[5] ) + F1[3] * ( -V3[3] + cI * V3[4] ) ) ) );
    F2[5] = denom * cI * ( F1[4] * ( P2[0] * ( -one ) * ( V3[3] + cI * V3[4] ) + ( P2[1] * ( V3[2] - V3[5] ) + ( P2[2] * ( +cI * V3[2] - cI * V3[5] ) + P2[3] * ( V3[3] + cI * V3[4] ) ) ) ) + ( F1[5] * ( P2[0] * ( V3[2] + V3[5] ) + ( P2[1] * ( -V3[3] + cI * V3[4] ) + ( P2[2] * ( -one ) * ( +cI * V3[3] + V3[4] ) - P2[3] * ( V3[2] + V3[5] ) ) ) ) + M2 * ( F1[2] * ( V3[3] + cI * V3[4] ) + F1[3] * ( V3[2] - V3[5] ) ) ) );
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V3[6]' from the input wavefunctions F1[6], F2[6]
  template<class W_ACCESS, class C_ACCESS, typename FT, typename CT >
  __device__ void
  FFV1P0_3( const FT allF1[],
            const FT allF2[],
            const FT allCOUP[],
            const FT Ccoeff,
            const FT M3,
            const FT W3,
            FT allV3[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const CT* F1 = W_ACCESS::kernelAccessConst( allF1 );
    const CT* F2 = W_ACCESS::kernelAccessConst( allF2 );
    const CT COUP = C_ACCESS::kernelAccessConst( allCOUP );
     CT* V3 = W_ACCESS::kernelAccess( allV3 );
    const CT cI = cxmake<FT>( 0., 1. );
    V3[0] = +F1[0] + F2[0];
    V3[1] = +F1[1] + F2[1];
    const FT P3[4] = { -cxreal( V3[0] ), -cxreal( V3[1] ), -cximag( V3[1] ), -cximag( V3[0] ) };
    const  CT denom = Ccoeff * COUP / ( ( P3[0] * P3[0] ) - ( P3[1] * P3[1] ) - ( P3[2] * P3[2] ) - ( P3[3] * P3[3] ) - M3 * ( M3 - cI * W3 ) );
    V3[2] = denom * ( -cI ) * ( F1[2] * F2[4] + F1[3] * F2[5] + F1[4] * F2[2] + F1[5] * F2[3] );
    V3[3] = denom * ( -cI ) * ( -F1[2] * F2[5] - F1[3] * F2[4] + F1[4] * F2[3] + F1[5] * F2[2] );
    V3[4] = denom * ( -cI ) * ( -cI * ( F1[2] * F2[5] + F1[5] * F2[2] ) + cI * ( F1[3] * F2[4] + F1[4] * F2[3] ) );
    V3[5] = denom * ( -cI ) * ( -F1[2] * F2[4] - F1[5] * F2[3] + F1[3] * F2[5] + F1[4] * F2[2] );
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions V1[6], V2[6], V3[6], V4[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS, typename FT, typename CT >
  __device__ void
  VVVV1_0( const FT allV1[],
           const FT allV2[],
           const FT allV3[],
           const FT allV4[],
           const FT allCOUP[],
           const FT Ccoeff,
           FT allvertexes[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const CT* V1 = W_ACCESS::kernelAccessConst( allV1 );
    const CT* V2 = W_ACCESS::kernelAccessConst( allV2 );
    const CT* V3 = W_ACCESS::kernelAccessConst( allV3 );
    const CT* V4 = W_ACCESS::kernelAccessConst( allV4 );
    const CT COUP = C_ACCESS::kernelAccessConst( allCOUP );
    CT*  vertex = A_ACCESS::kernelAccess( allvertexes );
    const CT cI = cxmake<FT>( 0., 1. );
    const CT TMP10 = ( V1[2] * V4[2] - V1[3] * V4[3] - V1[4] * V4[4] - V1[5] * V4[5] );
    const CT TMP11 = ( V2[2] * V4[2] - V2[3] * V4[3] - V2[4] * V4[4] - V2[5] * V4[5] );
    const CT TMP3 = ( V3[2] * V1[2] - V3[3] * V1[3] - V3[4] * V1[4] - V3[5] * V1[5] );
    const CT TMP6 = ( V3[2] * V2[2] - V3[3] * V2[3] - V3[4] * V2[4] - V3[5] * V2[5] );
    ( *vertex ) = Ccoeff * COUP * ( -cI * ( TMP6 * TMP10 ) + cI * ( TMP3 * TMP11 ) );
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V1[6]' from the input wavefunctions V2[6], V3[6], V4[6]
  template<class W_ACCESS, class C_ACCESS, typename FT, typename CT >
  __device__ void
  VVVV1P0_1( const FT allV2[],
             const FT allV3[],
             const FT allV4[],
             const FT allCOUP[],
             const FT Ccoeff,
             const FT M1,
             const FT W1,
             FT allV1[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const CT* V2 = W_ACCESS::kernelAccessConst( allV2 );
    const CT* V3 = W_ACCESS::kernelAccessConst( allV3 );
    const CT* V4 = W_ACCESS::kernelAccessConst( allV4 );
    const CT COUP = C_ACCESS::kernelAccessConst( allCOUP );
     CT* V1 = W_ACCESS::kernelAccess( allV1 );
    const CT cI = cxmake<FT>( 0., 1. );
    V1[0] = +V2[0] + V3[0] + V4[0];
    V1[1] = +V2[1] + V3[1] + V4[1];
    const FT P1[4] = { -cxreal( V1[0] ), -cxreal( V1[1] ), -cximag( V1[1] ), -cximag( V1[0] ) };
    const CT TMP11 = ( V2[2] * V4[2] - V2[3] * V4[3] - V2[4] * V4[4] - V2[5] * V4[5] );
    const CT TMP6 = ( V3[2] * V2[2] - V3[3] * V2[3] - V3[4] * V2[4] - V3[5] * V2[5] );
    const  CT denom = Ccoeff * COUP / ( ( P1[0] * P1[0] ) - ( P1[1] * P1[1] ) - ( P1[2] * P1[2] ) - ( P1[3] * P1[3] ) - M1 * ( M1 - cI * W1 ) );
    V1[2] = denom * ( -cI * ( TMP6 * V4[2] ) + cI * ( V3[2] * TMP11 ) );
    V1[3] = denom * ( -cI * ( TMP6 * V4[3] ) + cI * ( V3[3] * TMP11 ) );
    V1[4] = denom * ( -cI * ( TMP6 * V4[4] ) + cI * ( V3[4] * TMP11 ) );
    V1[5] = denom * ( -cI * ( TMP6 * V4[5] ) + cI * ( V3[5] * TMP11 ) );
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions V1[6], V2[6], V3[6], V4[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS, typename FT, typename CT >
  __device__ void
  VVVV3_0( const FT allV1[],
           const FT allV2[],
           const FT allV3[],
           const FT allV4[],
           const FT allCOUP[],
           const FT Ccoeff,
           FT allvertexes[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const CT* V1 = W_ACCESS::kernelAccessConst( allV1 );
    const CT* V2 = W_ACCESS::kernelAccessConst( allV2 );
    const CT* V3 = W_ACCESS::kernelAccessConst( allV3 );
    const CT* V4 = W_ACCESS::kernelAccessConst( allV4 );
    const CT COUP = C_ACCESS::kernelAccessConst( allCOUP );
    CT*  vertex = A_ACCESS::kernelAccess( allvertexes );
    const CT cI = cxmake<FT>( 0., 1. );
    const CT TMP1 = ( V2[2] * V1[2] - V2[3] * V1[3] - V2[4] * V1[4] - V2[5] * V1[5] );
    const CT TMP10 = ( V1[2] * V4[2] - V1[3] * V4[3] - V1[4] * V4[4] - V1[5] * V4[5] );
    const CT TMP12 = ( V3[2] * V4[2] - V3[3] * V4[3] - V3[4] * V4[4] - V3[5] * V4[5] );
    const CT TMP6 = ( V3[2] * V2[2] - V3[3] * V2[3] - V3[4] * V2[4] - V3[5] * V2[5] );
    ( *vertex ) = Ccoeff * COUP * ( -cI * ( TMP6 * TMP10 ) + cI * ( TMP1 * TMP12 ) );
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V1[6]' from the input wavefunctions V2[6], V3[6], V4[6]
  template<class W_ACCESS, class C_ACCESS, typename FT, typename CT >
  __device__ void
  VVVV3P0_1( const FT allV2[],
             const FT allV3[],
             const FT allV4[],
             const FT allCOUP[],
             const FT Ccoeff,
             const FT M1,
             const FT W1,
             FT allV1[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const CT* V2 = W_ACCESS::kernelAccessConst( allV2 );
    const CT* V3 = W_ACCESS::kernelAccessConst( allV3 );
    const CT* V4 = W_ACCESS::kernelAccessConst( allV4 );
    const CT COUP = C_ACCESS::kernelAccessConst( allCOUP );
     CT* V1 = W_ACCESS::kernelAccess( allV1 );
    const CT cI = cxmake<FT>( 0., 1. );
    V1[0] = +V2[0] + V3[0] + V4[0];
    V1[1] = +V2[1] + V3[1] + V4[1];
    const FT P1[4] = { -cxreal( V1[0] ), -cxreal( V1[1] ), -cximag( V1[1] ), -cximag( V1[0] ) };
    const CT TMP12 = ( V3[2] * V4[2] - V3[3] * V4[3] - V3[4] * V4[4] - V3[5] * V4[5] );
    const CT TMP6 = ( V3[2] * V2[2] - V3[3] * V2[3] - V3[4] * V2[4] - V3[5] * V2[5] );
    const  CT denom = Ccoeff * COUP / ( ( P1[0] * P1[0] ) - ( P1[1] * P1[1] ) - ( P1[2] * P1[2] ) - ( P1[3] * P1[3] ) - M1 * ( M1 - cI * W1 ) );
    V1[2] = denom * ( -cI * ( TMP6 * V4[2] ) + cI * ( V2[2] * TMP12 ) );
    V1[3] = denom * ( -cI * ( TMP6 * V4[3] ) + cI * ( V2[3] * TMP12 ) );
    V1[4] = denom * ( -cI * ( TMP6 * V4[4] ) + cI * ( V2[4] * TMP12 ) );
    V1[5] = denom * ( -cI * ( TMP6 * V4[5] ) + cI * ( V2[5] * TMP12 ) );
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions V1[6], V2[6], V3[6], V4[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS, typename FT, typename CT >
  __device__ void
  VVVV4_0( const FT allV1[],
           const FT allV2[],
           const FT allV3[],
           const FT allV4[],
           const FT allCOUP[],
           const FT Ccoeff,
           FT allvertexes[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const CT* V1 = W_ACCESS::kernelAccessConst( allV1 );
    const CT* V2 = W_ACCESS::kernelAccessConst( allV2 );
    const CT* V3 = W_ACCESS::kernelAccessConst( allV3 );
    const CT* V4 = W_ACCESS::kernelAccessConst( allV4 );
    const CT COUP = C_ACCESS::kernelAccessConst( allCOUP );
    CT*  vertex = A_ACCESS::kernelAccess( allvertexes );
    const CT cI = cxmake<FT>( 0., 1. );
    const CT TMP1 = ( V2[2] * V1[2] - V2[3] * V1[3] - V2[4] * V1[4] - V2[5] * V1[5] );
    const CT TMP11 = ( V2[2] * V4[2] - V2[3] * V4[3] - V2[4] * V4[4] - V2[5] * V4[5] );
    const CT TMP12 = ( V3[2] * V4[2] - V3[3] * V4[3] - V3[4] * V4[4] - V3[5] * V4[5] );
    const CT TMP3 = ( V3[2] * V1[2] - V3[3] * V1[3] - V3[4] * V1[4] - V3[5] * V1[5] );
    ( *vertex ) = Ccoeff * COUP * ( -cI * ( TMP3 * TMP11 ) + cI * ( TMP1 * TMP12 ) );
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V1[6]' from the input wavefunctions V2[6], V3[6], V4[6]
  template<class W_ACCESS, class C_ACCESS, typename FT, typename CT >
  __device__ void
  VVVV4P0_1( const FT allV2[],
             const FT allV3[],
             const FT allV4[],
             const FT allCOUP[],
             const FT Ccoeff,
             const FT M1,
             const FT W1,
             FT allV1[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const CT* V2 = W_ACCESS::kernelAccessConst( allV2 );
    const CT* V3 = W_ACCESS::kernelAccessConst( allV3 );
    const CT* V4 = W_ACCESS::kernelAccessConst( allV4 );
    const CT COUP = C_ACCESS::kernelAccessConst( allCOUP );
     CT* V1 = W_ACCESS::kernelAccess( allV1 );
    const CT cI = cxmake<FT>( 0., 1. );
    V1[0] = +V2[0] + V3[0] + V4[0];
    V1[1] = +V2[1] + V3[1] + V4[1];
    const FT P1[4] = { -cxreal( V1[0] ), -cxreal( V1[1] ), -cximag( V1[1] ), -cximag( V1[0] ) };
    const CT TMP11 = ( V2[2] * V4[2] - V2[3] * V4[3] - V2[4] * V4[4] - V2[5] * V4[5] );
    const CT TMP12 = ( V3[2] * V4[2] - V3[3] * V4[3] - V3[4] * V4[4] - V3[5] * V4[5] );
    const  CT denom = Ccoeff * COUP / ( ( P1[0] * P1[0] ) - ( P1[1] * P1[1] ) - ( P1[2] * P1[2] ) - ( P1[3] * P1[3] ) - M1 * ( M1 - cI * W1 ) );
    V1[2] = denom * ( -cI * ( V3[2] * TMP11 ) + cI * ( V2[2] * TMP12 ) );
    V1[3] = denom * ( -cI * ( V3[3] * TMP11 ) + cI * ( V2[3] * TMP12 ) );
    V1[4] = denom * ( -cI * ( V3[4] * TMP11 ) + cI * ( V2[4] * TMP12 ) );
    V1[5] = denom * ( -cI * ( V3[5] * TMP11 ) + cI * ( V2[5] * TMP12 ) );
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

} // end namespace

#endif // HelAmps_sm_H
