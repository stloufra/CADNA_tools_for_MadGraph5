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
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ INLINE void
  ixxxxx( const fptype momenta[], // input: momenta
          const fptype fmass,     // input: fermion mass
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fi[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PX == PY == 0 and E == +PZ > 0)
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ INLINE void
  ipzxxx( const fptype momenta[], // input: momenta
          //const fptype fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fi[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PX == PY == 0 and E == -PZ > 0)
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ INLINE void
  imzxxx( const fptype momenta[], // input: momenta
          //const fptype fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fi[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PT > 0)
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ INLINE void
  ixzxxx( const fptype momenta[], // input: momenta
          //const fptype fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction vc[6] from the input momenta[npar*4*nevt]
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ INLINE void
  vxxxxx( const fptype momenta[], // input: momenta
          const fptype vmass,     // input: vector boson mass
          const int nhel,         // input: -1, 0 (only if vmass!=0) or +1 (helicity of vector boson)
          const int nsv,          // input: +1 (final) or -1 (initial)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction sc[3] from the input momenta[npar*4*nevt]
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ INLINE void
  sxxxxx( const fptype momenta[], // input: momenta
          //const fptype,                 // WARNING: input "smass" unused (missing in Fortran) - scalar boson mass
          //const int,                    // WARNING: input "nhel" unused (missing in Fortran) - scalar has no helicity!
          const int nss,          // input: +1 (final) or -1 (initial)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fo[6] from the input momenta[npar*4*nevt]
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ INLINE void
  oxxxxx( const fptype momenta[], // input: momenta
          const fptype fmass,     // input: fermion mass
          const int nhel,         // input: -1, 0 (only if vmass!=0) or +1 (helicity of vector boson)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fo[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PX == PY == 0 and E == +PZ > 0)
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ INLINE void
  opzxxx( const fptype momenta[], // input: momenta
          //const fptype fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fo[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PX == PY == 0 and E == -PZ > 0)
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ INLINE void
  omzxxx( const fptype momenta[], // input: momenta
          //const fptype fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fo[6] from the input momenta[npar*4*nevt]
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ INLINE void
  oxzxxx( const fptype momenta[], // input: momenta
          //const fptype fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar          // input: particle# out of npar
          ) ALWAYS_INLINE;

  //==========================================================================

  // Compute the output wavefunction fi[6] from the input momenta[npar*4*nevt]
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ void
  ixxxxx( const fptype momenta[], // input: momenta
          const fptype fmass,     // input: fermion mass
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    // NEW IMPLEMENTATION FIXING FLOATING POINT EXCEPTIONS IN SIMD CODE (#701)
    // Variables xxxDENOM are a hack to avoid division-by-0 FPE while preserving speed (#701 and #727)
    // Variables xxxDENOM are declared as 'volatile' to make sure they are not optimized away on clang! (#724)
    // A few additional variables are declared as 'volatile' to avoid sqrt-of-negative-number FPEs (#736)
    const fptype& _pvec0 = M_ACCESS::kernelAccessIp4IparConst( momenta, 0, ipar );
    const fptype& _pvec1 = M_ACCESS::kernelAccessIp4IparConst( momenta, 1, ipar );
    const fptype& _pvec2 = M_ACCESS::kernelAccessIp4IparConst( momenta, 2, ipar );
    const fptype& _pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    cxtype_sv* fi = W_ACCESS::kernelAccess( wavefunctions );
	 	 const FT_ixxxxx fmass_FT = static_cast<FT_ixxxxx>(fmass);
	 	 const FT_ixxxxx pvec0 = static_cast<FT_ixxxxx>(_pvec0);
	 	 const FT_ixxxxx pvec1 = static_cast<FT_ixxxxx>(_pvec1);
	 	 const FT_ixxxxx pvec2 = static_cast<FT_ixxxxx>(_pvec2);
	 	 const FT_ixxxxx pvec3 = static_cast<FT_ixxxxx>(_pvec3);
    fi[0] =static_cast<cxsmpl<fptype>>( cxmake<FT_ixxxxx>( -pvec0 * (FT_ixxxxx)nsf, -pvec3 * (FT_ixxxxx)nsf ));
    fi[1] =static_cast<cxsmpl<fptype>>( cxmake<FT_ixxxxx>( -pvec1 * (FT_ixxxxx)nsf, -pvec2 * (FT_ixxxxx)nsf ));
    const int nh = nhel * nsf;
    if( fmass_FT != 0. )
    {
#ifndef MGONGPU_CPPSIMD
      const FT_ixxxxx pp = fpmin<FT_ixxxxx>( pvec0, fpsqrt<FT_ixxxxx>( pvec1 * pvec1 + pvec2 * pvec2 + pvec3 * pvec3 ) );
#else
      volatile FT_ixxxxx p2 = pvec1 * pvec1 + pvec2 * pvec2 + pvec3 * pvec3; // volatile fixes #736
      const FT_ixxxxx pp = fpmin( pvec0, fpsqrt<FT_ixxxxx>( p2 ) );
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
        FT_ixxxxx sqm[2] = { fpsqrt<FT_ixxxxx>( abs( fmass_FT ) ), 0. }; // possibility of negative fermion masses
        //sqm[1] = ( fmass_FT < 0. ? -abs( sqm[0] ) : abs( sqm[0] ) ); // AV: why abs here?
        sqm[1] = ( fmass_FT < 0. ? -sqm[0] : sqm[0] ); // AV: removed an abs here
        fi[2] =static_cast<cxsmpl<fptype>>( cxmake<FT_ixxxxx>( ip * sqm[ip], 0 ));
        fi[3] =static_cast<cxsmpl<fptype>>( cxmake<FT_ixxxxx>( im * nsf * sqm[ip], 0 ));
        fi[4] =static_cast<cxsmpl<fptype>>( cxmake<FT_ixxxxx>( ip * nsf * sqm[im], 0 ));
        fi[5] =static_cast<cxsmpl<fptype>>( cxmake<FT_ixxxxx>( im * sqm[im], 0 ));
      }
      else
      {
        const FT_ixxxxx sf[2] = { FT_ixxxxx( 1 + nsf + ( 1 - nsf ) * nh ) * (FT_ixxxxx)0.5,
                               FT_ixxxxx( 1 + nsf - ( 1 - nsf ) * nh ) * (FT_ixxxxx)0.5 };
        FT_ixxxxx omega[2] = { fpsqrt<FT_ixxxxx>( pvec0 + pp ), 0. };
        omega[1] = fmass_FT / omega[0];
        const FT_ixxxxx sfomega[2] = { sf[0] * omega[ip], sf[1] * omega[im] };
        const FT_ixxxxx pp3 = fpmax<FT_ixxxxx>( pp + pvec3, 0. );
        const cxsmpl<FT_ixxxxx> chi[2] = { cxmake<FT_ixxxxx>( fpsqrt<FT_ixxxxx>( pp3 * (FT_ixxxxx)0.5 / pp ), 0. ),
                                ( pp3 == 0. ? cxmake<FT_ixxxxx>( -nh, 0. ) : cxmake<FT_ixxxxx>( nh * pvec1, pvec2 ) / fpsqrt<FT_ixxxxx>( 2. * pp * pp3 ) ) };
        fi[2] =static_cast<cxsmpl<fptype>>( sfomega[0] * chi[im]);
        fi[3] =static_cast<cxsmpl<fptype>>( sfomega[0] * chi[ip]);
        fi[4] =static_cast<cxsmpl<fptype>>( sfomega[1] * chi[im]);
        fi[5] =static_cast<cxsmpl<fptype>>( sfomega[1] * chi[ip]);
      }
#else
      // Branch A: pp == 0.
      // NB: Do not use "abs" for floats! It returns an integer with no build warning! Use std::abs!
      FT_ixxxxx sqm[2] = { fpsqrt<FT_ixxxxx>( abs( fmass_FT ) ), 0 }; // possibility of negative fermion masses (NB: SCALAR!)
      sqm[1] = ( fmass_FT < 0 ? -sqm[0] : sqm[0] );          // AV: removed an abs here (as above)
      const cxsmpl<FT_ixxxxx> fiA_2 = ip * sqm[ip];                  // scalar cxsmpl<FT_ixxxxx>: real part initialised from FT_ixxxxx, imag part = 0
      const cxsmpl<FT_ixxxxx> fiA_3 = im * nsf * sqm[ip];            // scalar cxsmpl<FT_ixxxxx>: real part initialised from FT_ixxxxx, imag part = 0
      const cxsmpl<FT_ixxxxx> fiA_4 = ip * nsf * sqm[im];            // scalar cxsmpl<FT_ixxxxx>: real part initialised from FT_ixxxxx, imag part = 0
      const cxsmpl<FT_ixxxxx> fiA_5 = im * sqm[im];                  // scalar cxsmpl<FT_ixxxxx>: real part initialised from FT_ixxxxx, imag part = 0
      // Branch B: pp != 0.
      const FT_ixxxxx sf[2] = { FT_ixxxxx( 1 + nsf + ( 1 - nsf ) * nh ) * (FT_ixxxxx)0.5,
                             FT_ixxxxx( 1 + nsf - ( 1 - nsf ) * nh ) * (FT_ixxxxx)0.5 };
      FT_ixxxxx_v omega[2] = { fpsqrt<FT_ixxxxx>( pvec0 + pp ), 0 };
      omega[1] = fmass_FT / omega[0];
      const FT_ixxxxx_v sfomega[2] = { sf[0] * omega[ip], sf[1] * omega[im] };
      const FT_ixxxxx_v pp3 = fpmax( pp + pvec3, 0 );
      volatile FT_ixxxxx_v ppDENOM = fpternary( pp != 0, pp, 1. );    // hack: ppDENOM[ieppV]=1 if pp[ieppV]==0
      volatile FT_ixxxxx_v pp3DENOM = fpternary( pp3 != 0, pp3, 1. ); // hack: pp3DENOM[ieppV]=1 if pp3[ieppV]==0
      volatile FT_ixxxxx_v chi0r2 = pp3 * 0.5 / ppDENOM;              // volatile fixes #736
      const cxsmpl<FT_ixxxxx>_v chi[2] = { cxmake<FT_ixxxxx>( fpsqrt<FT_ixxxxx>( chi0r2 ), 0 ),     // hack: dummy[ieppV] is not used if pp[ieppV]==0
                                cxternary( ( pp3 == 0. ),
                                           cxmake<FT_ixxxxx>( -nh, 0 ),
                                           cxmake<FT_ixxxxx>( (FT_ixxxxx)nh * pvec1, pvec2 ) / fpsqrt<FT_ixxxxx>( 2. * ppDENOM * pp3DENOM ) ) }; // hack: dummy[ieppV] is not used if pp[ieppV]==0
      const cxsmpl<FT_ixxxxx>_v fiB_2 = sfomega[0] * chi[im];
      const cxsmpl<FT_ixxxxx>_v fiB_3 = sfomega[0] * chi[ip];
      const cxsmpl<FT_ixxxxx>_v fiB_4 = sfomega[1] * chi[im];
      const cxsmpl<FT_ixxxxx>_v fiB_5 = sfomega[1] * chi[ip];
      // Choose between the results from branch A and branch B
      const bool_v mask = ( pp == 0. );
      fi[2] =static_cast<cxsmpl<fptype>>( cxternary( mask, fiA_2, fiB_2 ));
      fi[3] =static_cast<cxsmpl<fptype>>( cxternary( mask, fiA_3, fiB_3 ));
      fi[4] =static_cast<cxsmpl<fptype>>( cxternary( mask, fiA_4, fiB_4 ));
      fi[5] =static_cast<cxsmpl<fptype>>( cxternary( mask, fiA_5, fiB_5 ));
#endif
    }
    else
    {
#ifdef MGONGPU_CPPSIMD
      volatile FT_ixxxxx p0p3 = fpmax( pvec0 + pvec3, 0 ); // volatile fixes #736
      volatile FT_ixxxxx sqp0p3 = fpternary( ( pvec1 == 0. and pvec2 == 0. and pvec3 < 0. ),
                                             FT_ixxxxx{ 0 },
                                             fpsqrt<FT_ixxxxx>( p0p3 ) * (FT_ixxxxx)nsf );
      volatile FT_ixxxxx sqp0p3DENOM = fpternary( sqp0p3 != 0, (FT_ixxxxx)sqp0p3, 1. ); // hack: dummy sqp0p3DENOM[ieppV]=1 if sqp0p3[ieppV]==0
      cxsmpl<FT_ixxxxx> chi[2] = { cxmake<FT_ixxxxx>( (FT_ixxxxx_v)sqp0p3, 0. ),
                           cxternary( sqp0p3 == 0,
                                      cxmake<FT_ixxxxx>( -(FT_ixxxxx)nhel * fpsqrt<FT_ixxxxx>( 2. * pvec0 ), 0. ),
                                      cxmake<FT_ixxxxx>( (FT_ixxxxx)nh * pvec1, pvec2 ) / (const FT_ixxxxx_v)sqp0p3DENOM ) }; // hack: dummy[ieppV] is not used if sqp0p3[ieppV]==0
#else
      const FT_ixxxxx sqp0p3 = fpternary( ( pvec1 == 0. and pvec2 == 0. and pvec3 < 0. ),
                                          FT_ixxxxx{ 0 },
                                          fpsqrt<FT_ixxxxx>( fpmax( pvec0 + pvec3, 0. ) ) * (FT_ixxxxx)nsf );
      const cxsmpl<FT_ixxxxx> chi[2] = { cxmake<FT_ixxxxx>( sqp0p3, 0. ),
                                 ( sqp0p3 == 0. ? cxmake<FT_ixxxxx>( -(FT_ixxxxx)nhel * fpsqrt<FT_ixxxxx>( 2. * pvec0 ), 0. ) : cxmake<FT_ixxxxx>( (FT_ixxxxx)nh * pvec1, pvec2 ) / sqp0p3 ) };
#endif
      if( nh == 1 )
      {
        fi[2] =static_cast<cxsmpl<fptype>>( cxzero<FT_ixxxxx>());
        fi[3] =static_cast<cxsmpl<fptype>>( cxzero<FT_ixxxxx>());
        fi[4] =static_cast<cxsmpl<fptype>>( chi[0]);
        fi[5] =static_cast<cxsmpl<fptype>>( chi[1]);
      }
      else
      {
        fi[2] =static_cast<cxsmpl<fptype>>( chi[1]);
        fi[3] =static_cast<cxsmpl<fptype>>( chi[0]);
        fi[4] =static_cast<cxsmpl<fptype>>( cxzero<FT_ixxxxx>());
        fi[5] =static_cast<cxsmpl<fptype>>( cxzero<FT_ixxxxx>());
      }
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fi[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PX == PY == 0 and E == +PZ > 0)
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ void
  ipzxxx( const fptype momenta[], // input: momenta
          //const fptype fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    const fptype& _pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    cxtype_sv* fi = W_ACCESS::kernelAccess( wavefunctions );
	 	 const FT_ipzxxx pvec3 = static_cast<FT_ipzxxx>(_pvec3);
    fi[0] =static_cast<cxsmpl<fptype>>( cxmake<FT_ipzxxx>( -pvec3 * (FT_ipzxxx)nsf, -pvec3 * (FT_ipzxxx)nsf ));
    fi[1] =static_cast<cxsmpl<fptype>>( cxzero<FT_ipzxxx>());
    const int nh = nhel * nsf;
    const cxsmpl<FT_ipzxxx> sqp0p3 = cxmake<FT_ipzxxx>( fpsqrt<FT_ipzxxx>( 2. * pvec3 ) * (FT_ipzxxx)nsf, 0. );
    fi[2] =static_cast<cxsmpl<fptype>>( fi[1]);
    if( nh == 1 )
    {
      fi[3] =static_cast<cxsmpl<fptype>>( fi[1]);
      fi[4] =static_cast<cxsmpl<fptype>>( sqp0p3);
    }
    else
    {
      fi[3] =static_cast<cxsmpl<fptype>>( sqp0p3);
      fi[4] =static_cast<cxsmpl<fptype>>( fi[1]);
    }
    fi[5] =static_cast<cxsmpl<fptype>>( fi[1]);
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fi[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PX == PY == 0 and E == -PZ > 0)
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ void
  imzxxx( const fptype momenta[], // input: momenta
          //const fptype fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    const fptype& _pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    cxtype_sv* fi = W_ACCESS::kernelAccess( wavefunctions );
	 	 const FT_imzxxx pvec3 = static_cast<FT_imzxxx>(_pvec3);
    fi[0] =static_cast<cxsmpl<fptype>>( cxmake<FT_imzxxx>( pvec3 * (FT_imzxxx)nsf, -pvec3 * (FT_imzxxx)nsf ));
    fi[1] =static_cast<cxsmpl<fptype>>( cxzero<FT_imzxxx>());
    const int nh = nhel * nsf;
    const cxsmpl<FT_imzxxx> chi = cxmake<FT_imzxxx>( -(FT_imzxxx)nhel * fpsqrt<FT_imzxxx>( -2. * pvec3 ), 0. );
    fi[3] =static_cast<cxsmpl<fptype>>( cxzero<FT_imzxxx>());
    fi[4] =static_cast<cxsmpl<fptype>>( cxzero<FT_imzxxx>());
    if( nh == 1 )
    {
      fi[2] =static_cast<cxsmpl<fptype>>( cxzero<FT_imzxxx>());
      fi[5] =static_cast<cxsmpl<fptype>>( chi);
    }
    else
    {
      fi[2] =static_cast<cxsmpl<fptype>>( chi);
      fi[5] =static_cast<cxsmpl<fptype>>( cxzero<FT_imzxxx>());
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fi[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PT > 0)
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ void
  ixzxxx( const fptype momenta[], // input: momenta
          //const fptype fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    const fptype& _pvec0 = M_ACCESS::kernelAccessIp4IparConst( momenta, 0, ipar );
    const fptype& _pvec1 = M_ACCESS::kernelAccessIp4IparConst( momenta, 1, ipar );
    const fptype& _pvec2 = M_ACCESS::kernelAccessIp4IparConst( momenta, 2, ipar );
    const fptype& _pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    cxtype_sv* fi = W_ACCESS::kernelAccess( wavefunctions );
	 	 const FT_ixzxxx pvec0 = static_cast<FT_ixzxxx>(_pvec0);
	 	 const FT_ixzxxx pvec1 = static_cast<FT_ixzxxx>(_pvec1);
	 	 const FT_ixzxxx pvec2 = static_cast<FT_ixzxxx>(_pvec2);
	 	 const FT_ixzxxx pvec3 = static_cast<FT_ixzxxx>(_pvec3);
    //fi[0] =static_cast<cxsmpl<fptype>>( cxmake<FT_ixzxxx>( -pvec0 * nsf, -pvec2 * nsf )); // AV: BUG! not the same as ixxxxx
    //fi[1] =static_cast<cxsmpl<fptype>>( cxmake<FT_ixzxxx>( -pvec0 * nsf, -pvec1 * nsf )); // AV: BUG! not the same as ixxxxx
    fi[0] =static_cast<cxsmpl<fptype>>( cxmake<FT_ixzxxx>( -pvec0 * (FT_ixzxxx)nsf, -pvec3 * (FT_ixzxxx)nsf )); // AV: BUG FIX
    fi[1] =static_cast<cxsmpl<fptype>>( cxmake<FT_ixzxxx>( -pvec1 * (FT_ixzxxx)nsf, -pvec2 * (FT_ixzxxx)nsf )); // AV: BUG FIX
    const int nh = nhel * nsf;
    //const float sqp0p3 = sqrtf( pvec0 + pvec3 ) * nsf; // AV: why force a float here?
    const FT_ixzxxx sqp0p3 = fpsqrt<FT_ixzxxx>( pvec0 + pvec3 ) * (FT_ixzxxx)nsf;
    const cxsmpl<FT_ixzxxx> chi0 = cxmake<FT_ixzxxx>( sqp0p3, 0. );
    const cxsmpl<FT_ixzxxx> chi1 = cxmake<FT_ixzxxx>( (FT_ixzxxx)nh * pvec1 / sqp0p3, pvec2 / sqp0p3 );
    if( nh == 1 )
    {
      fi[2] =static_cast<cxsmpl<fptype>>( cxzero<FT_ixzxxx>());
      fi[3] =static_cast<cxsmpl<fptype>>( cxzero<FT_ixzxxx>());
      fi[4] =static_cast<cxsmpl<fptype>>( chi0);
      fi[5] =static_cast<cxsmpl<fptype>>( chi1);
    }
    else
    {
      fi[2] =static_cast<cxsmpl<fptype>>( chi1);
      fi[3] =static_cast<cxsmpl<fptype>>( chi0);
      fi[4] =static_cast<cxsmpl<fptype>>( cxzero<FT_ixzxxx>());
      fi[5] =static_cast<cxsmpl<fptype>>( cxzero<FT_ixzxxx>());
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction vc[6] from the input momenta[npar*4*nevt]
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ void
  vxxxxx( const fptype momenta[], // input: momenta
          const fptype vmass,     // input: vector boson mass
          const int nhel,         // input: -1, 0 (only if vmass!=0) or +1 (helicity of vector boson)
          const int nsv,          // input: +1 (final) or -1 (initial)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    // NEW IMPLEMENTATION FIXING FLOATING POINT EXCEPTIONS IN SIMD CODE (#701)
    // Variables xxxDENOM are a hack to avoid division-by-0 FPE while preserving speed (#701 and #727)
    // Variables xxxDENOM are declared as 'volatile' to make sure they are not optimized away on clang! (#724)
    // A few additional variables are declared as 'volatile' to avoid sqrt-of-negative-number FPEs (#736)
    const fptype& _pvec0 = M_ACCESS::kernelAccessIp4IparConst( momenta, 0, ipar );
    const fptype& _pvec1 = M_ACCESS::kernelAccessIp4IparConst( momenta, 1, ipar );
    const fptype& _pvec2 = M_ACCESS::kernelAccessIp4IparConst( momenta, 2, ipar );
    const fptype& _pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    cxtype_sv* vc = W_ACCESS::kernelAccess( wavefunctions );
	 	 const FT_vxxxxx pvec0 = static_cast<FT_vxxxxx>(_pvec0);
	 	 const FT_vxxxxx pvec1 = static_cast<FT_vxxxxx>(_pvec1);
	 	 const FT_vxxxxx pvec2 = static_cast<FT_vxxxxx>(_pvec2);
	 	 const FT_vxxxxx pvec3 = static_cast<FT_vxxxxx>(_pvec3);
    const FT_vxxxxx sqh = fpsqrt<FT_vxxxxx>( 0.5 ); // AV this is > 0!
    const FT_vxxxxx hel = nhel;
    vc[0] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( pvec0 * (FT_vxxxxx)nsv, pvec3 * (FT_vxxxxx)nsv ));
    vc[1] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( pvec1 * (FT_vxxxxx)nsv, pvec2 * (FT_vxxxxx)nsv ));
    if( vmass != 0. )
    {
      const int nsvahl = nsv * abs( hel );
      const FT_vxxxxx hel0 = 1. - abs( hel );
#ifndef MGONGPU_CPPSIMD
      const FT_vxxxxx pt2 = ( pvec1 * pvec1 ) + ( pvec2 * pvec2 );
      const FT_vxxxxx pp = fpmin( pvec0, fpsqrt<FT_vxxxxx>( pt2 + ( pvec3 * pvec3 ) ) );
      const FT_vxxxxx pt = fpmin( pp, fpsqrt<FT_vxxxxx>( pt2 ) );
      if( pp == 0. )
      {
        vc[2] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( 0., 0. ));
        vc[3] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( -hel * sqh, 0. ));
        vc[4] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( 0., nsvahl * sqh ));
        vc[5] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( hel0, 0. ));
      }
      else
      {
        //printf( "DEBUG1011 (before emp): pvec0=%f vmass=%f pp=%f vmass*pp=%f\n", pvec0, vmass, pp, vmass * pp );
        //const FT_vxxxxx emp = pvec / ( vmass * pp ); // this may give a FPE #1011 (why?! maybe when vmass=+-epsilon?)
        const FT_vxxxxx emp = pvec0 / vmass / pp; // workaround for FPE #1011
        //printf( "DEBUG1011 (after emp): emp=%f\n", emp );
        vc[2] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( hel0 * pp / vmass, 0. ));
        vc[5] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( hel0 * pvec3 * emp + hel * pt / pp * sqh, 0. ));
        if( pt != 0. )
        {
          const FT_vxxxxx pzpt = pvec3 / ( pp * pt ) * sqh * hel;
          vc[3] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( hel0 * pvec1 * emp - pvec1 * pzpt, -nsvahl * pvec2 / pt * sqh ));
          vc[4] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( hel0 * pvec2 * emp - pvec2 * pzpt, nsvahl * pvec1 / pt * sqh ));
        }
        else
        {
          vc[3] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( -hel * sqh, 0. ));
          // NB: Do not use "abs" for floats! It returns an integer with no build warning! Use std::abs!
          //vc[4] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( 0., nsvahl * ( pvec3 < 0. ? -abs( sqh ) : abs( sqh ) ) )); // AV: why abs here?
          vc[4] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( 0., nsvahl * ( pvec3 < 0. ? -sqh : sqh ) )); // AV: removed an abs here
        }
      }
#else
      volatile FT_vxxxxx pt2 = ( pvec1 * pvec1 ) + ( pvec2 * pvec2 );
      volatile FT_vxxxxx p2 = pt2 + ( pvec3 * pvec3 ); // volatile fixes #736
      const FT_vxxxxx pp = fpmin( pvec0, fpsqrt<FT_vxxxxx>( p2 ) );
      const FT_vxxxxx pt = fpmin( pp, fpsqrt<FT_vxxxxx>( pt2 ) );
      // Branch A: pp == 0.
      const cxsmpl<FT_vxxxxx> vcA_2 = cxmake<FT_vxxxxx>( 0, 0 );
      const cxsmpl<FT_vxxxxx> vcA_3 = cxmake<FT_vxxxxx>( -hel * sqh, 0 );
      const cxsmpl<FT_vxxxxx> vcA_4 = cxmake<FT_vxxxxx>( 0, nsvahl * sqh );
      const cxsmpl<FT_vxxxxx> vcA_5 = cxmake<FT_vxxxxx>( hel0, 0 );
      // Branch B: pp != 0.
      volatile FT_vxxxxx_v ppDENOM = fpternary( pp != 0, pp, 1. ); // hack: ppDENOM[ieppV]=1 if pp[ieppV]==0
      const FT_vxxxxx_v emp = pvec0 / ( vmass * ppDENOM );         // hack: dummy[ieppV] is not used if pp[ieppV]==0
      const cxsmpl<FT_vxxxxx>_v vcB_2 = cxmake<FT_vxxxxx>( hel0 * pp / vmass, 0 );
      const cxsmpl<FT_vxxxxx>_v vcB_5 = cxmake<FT_vxxxxx>( hel0 * pvec3 * emp + hel * pt / ppDENOM * sqh, 0 ); // hack: dummy[ieppV] is not used if pp[ieppV]==0
      // Branch B1: pp != 0. and pt != 0.
      volatile FT_vxxxxx_v ptDENOM = fpternary( pt != 0, pt, 1. );                                                     // hack: ptDENOM[ieppV]=1 if pt[ieppV]==0
      const FT_vxxxxx_v pzpt = pvec3 / ( ppDENOM * ptDENOM ) * sqh * hel;                                              // hack: dummy[ieppV] is not used if pp[ieppV]==0
      const cxsmpl<FT_vxxxxx>_v vcB1_3 = cxmake<FT_vxxxxx>( hel0 * pvec1 * emp - pvec1 * pzpt, -(FT_vxxxxx)nsvahl * pvec2 / ptDENOM * sqh ); // hack: dummy[ieppV] is not used if pt[ieppV]==0
      const cxsmpl<FT_vxxxxx>_v vcB1_4 = cxmake<FT_vxxxxx>( hel0 * pvec2 * emp - pvec2 * pzpt, (FT_vxxxxx)nsvahl * pvec1 / ptDENOM * sqh );  // hack: dummy[ieppV] is not used if pt[ieppV]==0
      // Branch B2: pp != 0. and pt == 0.
      const cxsmpl<FT_vxxxxx> vcB2_3 = cxmake<FT_vxxxxx>( -hel * sqh, 0. );
      const cxsmpl<FT_vxxxxx>_v vcB2_4 = cxmake<FT_vxxxxx>( 0., (FT_vxxxxx)nsvahl * fpternary( ( pvec3 < 0 ), -sqh, sqh ) ); // AV: removed an abs here
      // Choose between the results from branch A and branch B (and from branch B1 and branch B2)
      const bool_v mask = ( pp == 0. );
      const bool_v maskB = ( pt != 0. );
      vc[2] =static_cast<cxsmpl<fptype>>( cxternary( mask, vcA_2, vcB_2 ));
      vc[3] =static_cast<cxsmpl<fptype>>( cxternary( mask, vcA_3, cxternary( maskB, vcB1_3, vcB2_3 ) ));
      vc[4] =static_cast<cxsmpl<fptype>>( cxternary( mask, vcA_4, cxternary( maskB, vcB1_4, vcB2_4 ) ));
      vc[5] =static_cast<cxsmpl<fptype>>( cxternary( mask, vcA_5, vcB_5 ));
#endif
    }
    else
    {
      const FT_vxxxxx& pp = pvec0; // NB: rewrite the following as in Fortran, using pp instead of pvec0
#ifndef MGONGPU_CPPSIMD
      const FT_vxxxxx pt = fpsqrt<FT_vxxxxx>( ( pvec1 * pvec1 ) + ( pvec2 * pvec2 ) );
#else
      volatile FT_vxxxxx pt2 = pvec1 * pvec1 + pvec2 * pvec2; // volatile fixes #736
      const FT_vxxxxx pt = fpsqrt<FT_vxxxxx>( pt2 );
#endif
      vc[2] =static_cast<cxsmpl<fptype>>( cxzero<FT_vxxxxx>());
      vc[5] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( hel * pt / pp * sqh, 0. ));
#ifndef MGONGPU_CPPSIMD
      if( pt != 0. )
      {
        const FT_vxxxxx pzpt = pvec3 / ( pp * pt ) * sqh * hel;
        vc[3] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( -pvec1 * pzpt, -nsv * pvec2 / pt * sqh ));
        vc[4] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( -pvec2 * pzpt, nsv * pvec1 / pt * sqh ));
      }
      else
      {
        vc[3] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( -hel * sqh, 0. ));
        // NB: Do not use "abs" for floats! It returns an integer with no build warning! Use std::abs!
        //vc[4] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( 0, nsv * ( pvec3 < 0. ? -abs( sqh ) : abs( sqh ) ) )); // AV why abs here?
        vc[4] =static_cast<cxsmpl<fptype>>( cxmake<FT_vxxxxx>( 0., nsv * ( pvec3 < 0. ? -sqh : sqh ) )); // AV: removed an abs here
      }
#else
      // Branch A: pt != 0.
      volatile FT_vxxxxx_v ptDENOM = fpternary( pt != 0, pt, 1. );                             // hack: ptDENOM[ieppV]=1 if pt[ieppV]==0
      const FT_vxxxxx_v pzpt = pvec3 / ( pp * ptDENOM ) * sqh * hel;                           // hack: dummy[ieppV] is not used if pt[ieppV]==0
      const cxsmpl<FT_vxxxxx>_v vcA_3 = cxmake<FT_vxxxxx>( -pvec1 * pzpt, -(FT_vxxxxx)nsv * pvec2 / ptDENOM * sqh ); // hack: dummy[ieppV] is not used if pt[ieppV]==0
      const cxsmpl<FT_vxxxxx>_v vcA_4 = cxmake<FT_vxxxxx>( -pvec2 * pzpt, (FT_vxxxxx)nsv * pvec1 / ptDENOM * sqh );  // hack: dummy[ieppV] is not used if pt[ieppV]==0
      // Branch B: pt == 0.
      const cxsmpl<FT_vxxxxx> vcB_3 = cxmake<FT_vxxxxx>( -(FT_vxxxxx)hel * sqh, 0 );
      const cxsmpl<FT_vxxxxx>_v vcB_4 = cxmake<FT_vxxxxx>( 0, (FT_vxxxxx)nsv * fpternary( ( pvec3 < 0 ), -sqh, sqh ) ); // AV: removed an abs here
      // Choose between the results from branch A and branch B
      const bool_v mask = ( pt != 0. );
      vc[3] =static_cast<cxsmpl<fptype>>( cxternary( mask, vcA_3, vcB_3 ));
      vc[4] =static_cast<cxsmpl<fptype>>( cxternary( mask, vcA_4, vcB_4 ));
#endif
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction sc[3] from the input momenta[npar*4*nevt]
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ void
  sxxxxx( const fptype momenta[], // input: momenta
          //const fptype,                 // WARNING: input "smass" unused (missing in Fortran) - scalar boson mass
          //const int,                    // WARNING: input "nhel" unused (missing in Fortran) - scalar has no helicity!
          const int nss,          // input: +1 (final) or -1 (initial)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    const fptype& _pvec0 = M_ACCESS::kernelAccessIp4IparConst( momenta, 0, ipar );
    const fptype& _pvec1 = M_ACCESS::kernelAccessIp4IparConst( momenta, 1, ipar );
    const fptype& _pvec2 = M_ACCESS::kernelAccessIp4IparConst( momenta, 2, ipar );
    const fptype& _pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    cxtype_sv* sc = W_ACCESS::kernelAccess( wavefunctions );
	 	 const FT_sxxxxx pvec0 = static_cast<FT_sxxxxx>(_pvec0);
	 	 const FT_sxxxxx pvec1 = static_cast<FT_sxxxxx>(_pvec1);
	 	 const FT_sxxxxx pvec2 = static_cast<FT_sxxxxx>(_pvec2);
	 	 const FT_sxxxxx pvec3 = static_cast<FT_sxxxxx>(_pvec3);
    sc[2] =static_cast<cxsmpl<fptype>>( cxmake<FT_sxxxxx>( 1 + FT_sxxxxx{ 0 }, 0 ));
    sc[0] =static_cast<cxsmpl<fptype>>( cxmake<FT_sxxxxx>( pvec0 * (FT_sxxxxx)nss, pvec3 * (FT_sxxxxx)nss ));
    sc[1] =static_cast<cxsmpl<fptype>>( cxmake<FT_sxxxxx>( pvec1 * (FT_sxxxxx)nss, pvec2 * (FT_sxxxxx)nss ));
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fo[6] from the input momenta[npar*4*nevt]
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ void
  oxxxxx( const fptype momenta[], // input: momenta
          const fptype fmass,     // input: fermion mass
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    // NEW IMPLEMENTATION FIXING FLOATING POINT EXCEPTIONS IN SIMD CODE (#701)
    // Variables xxxDENOM are a hack to avoid division-by-0 FPE while preserving speed (#701 and #727)
    // Variables xxxDENOM are declared as 'volatile' to make sure they are not optimized away on clang! (#724)
    // A few additional variables are declared as 'volatile' to avoid sqrt-of-negative-number FPEs (#736)
    const fptype& _pvec0 = M_ACCESS::kernelAccessIp4IparConst( momenta, 0, ipar );
    const fptype& _pvec1 = M_ACCESS::kernelAccessIp4IparConst( momenta, 1, ipar );
    const fptype& _pvec2 = M_ACCESS::kernelAccessIp4IparConst( momenta, 2, ipar );
    const fptype& _pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    cxtype_sv* fo = W_ACCESS::kernelAccess( wavefunctions );
	 	 const FT_oxxxxx fmass_FT = static_cast<FT_oxxxxx>(fmass);
	 	 const FT_oxxxxx pvec0 = static_cast<FT_oxxxxx>(_pvec0);
	 	 const FT_oxxxxx pvec1 = static_cast<FT_oxxxxx>(_pvec1);
	 	 const FT_oxxxxx pvec2 = static_cast<FT_oxxxxx>(_pvec2);
	 	 const FT_oxxxxx pvec3 = static_cast<FT_oxxxxx>(_pvec3);
    fo[0] =static_cast<cxsmpl<fptype>>( cxmake<FT_oxxxxx>( pvec0 * (FT_oxxxxx)nsf, pvec3 * (FT_oxxxxx)nsf ));
    fo[1] =static_cast<cxsmpl<fptype>>( cxmake<FT_oxxxxx>( pvec1 * (FT_oxxxxx)nsf, pvec2 * (FT_oxxxxx)nsf ));
    const int nh = nhel * nsf;
    if( fmass_FT != 0. )
    {
#ifndef MGONGPU_CPPSIMD
      const FT_oxxxxx pp = fpmin( pvec0, fpsqrt<FT_oxxxxx>( ( pvec1 * pvec1 ) + ( pvec2 * pvec2 ) + ( pvec3 * pvec3 ) ) );
      if( pp == 0. )
      {
        // NB: Do not use "abs" for floats! It returns an integer with no build warning! Use std::abs!
        FT_oxxxxx sqm[2] = { fpsqrt<FT_oxxxxx>( abs( fmass_FT ) ), 0. }; // possibility of negative fermion masses
        //sqm[1] = ( fmass_FT < 0. ? -abs( sqm[0] ) : abs( sqm[0] ) ); // AV: why abs here?
        sqm[1] = ( fmass_FT < 0. ? -sqm[0] : sqm[0] ); // AV: removed an abs here
        const int ip = -( ( 1 - nh ) / 2 ) * nhel;  // NB: Fortran sqm(0:1) also has indexes 0,1 as in C++
        const int im = ( 1 + nh ) / 2 * nhel;       // NB: Fortran sqm(0:1) also has indexes 0,1 as in C++
        fo[2] =static_cast<cxsmpl<fptype>>( cxmake<FT_oxxxxx>( im * sqm[abs( ip )], 0 ));
        fo[3] =static_cast<cxsmpl<fptype>>( cxmake<FT_oxxxxx>( ip * nsf * sqm[abs( ip )], 0 ));
        fo[4] =static_cast<cxsmpl<fptype>>( cxmake<FT_oxxxxx>( im * nsf * sqm[abs( im )], 0 ));
        fo[5] =static_cast<cxsmpl<fptype>>( cxmake<FT_oxxxxx>( ip * sqm[abs( im )], 0 ));
      }
      else
      {
        const FT_oxxxxx sf[2] = { FT_oxxxxx( 1 + nsf + ( 1 - nsf ) * nh ) * (FT_oxxxxx)0.5,
                               FT_oxxxxx( 1 + nsf - ( 1 - nsf ) * nh ) * (FT_oxxxxx)0.5 };
        FT_oxxxxx omega[2] = { fpsqrt<FT_oxxxxx>( pvec0 + pp ), 0. };
        omega[1] = fmass_FT / omega[0];
        const int ip = ( 1 + nh ) / 2; // NB: Fortran is (3+nh)/2 because omega(2) has indexes 1,2 and not 0,1
        const int im = ( 1 - nh ) / 2; // NB: Fortran is (3-nh)/2 because omega(2) has indexes 1,2 and not 0,1
        const FT_oxxxxx sfomeg[2] = { sf[0] * omega[ip], sf[1] * omega[im] };
        const FT_oxxxxx pp3 = fpmax( pp + pvec3, 0. );
        const cxsmpl<FT_oxxxxx> chi[2] = { cxmake<FT_oxxxxx>( fpsqrt<FT_oxxxxx>( pp3 * (FT_oxxxxx)0.5 / pp ), 0. ),
                                ( ( pp3 == 0. ) ? cxmake<FT_oxxxxx>( -nh, 0. )
                                                : cxmake<FT_oxxxxx>( nh * pvec1, -pvec2 ) / fpsqrt<FT_oxxxxx>( 2. * pp * pp3 ) ) };
        fo[2] =static_cast<cxsmpl<fptype>>( sfomeg[1] * chi[im]);
        fo[3] =static_cast<cxsmpl<fptype>>( sfomeg[1] * chi[ip]);
        fo[4] =static_cast<cxsmpl<fptype>>( sfomeg[0] * chi[im]);
        fo[5] =static_cast<cxsmpl<fptype>>( sfomeg[0] * chi[ip]);
      }
#else
      volatile FT_oxxxxx p2 = pvec1 * pvec1 + pvec2 * pvec2 + pvec3 * pvec3; // volatile fixes #736
      const FT_oxxxxx pp = fpmin( pvec0, fpsqrt<FT_oxxxxx>( p2 ) );
      // Branch A: pp == 0.
      // NB: Do not use "abs" for floats! It returns an integer with no build warning! Use std::abs!
      FT_oxxxxx sqm[2] = { fpsqrt<FT_oxxxxx>( abs( fmass_FT ) ), 0 }; // possibility of negative fermion masses
      sqm[1] = ( fmass_FT < 0 ? -sqm[0] : sqm[0] );          // AV: removed an abs here (as above)
      const int ipA = -( ( 1 - nh ) / 2 ) * nhel;
      const int imA = ( 1 + nh ) / 2 * nhel;
      const cxsmpl<FT_oxxxxx> foA_2 = imA * sqm[abs( ipA )];
      const cxsmpl<FT_oxxxxx> foA_3 = ipA * nsf * sqm[abs( ipA )];
      const cxsmpl<FT_oxxxxx> foA_4 = imA * nsf * sqm[abs( imA )];
      const cxsmpl<FT_oxxxxx> foA_5 = ipA * sqm[abs( imA )];
      // Branch B: pp != 0.
      const FT_oxxxxx sf[2] = { FT_oxxxxx( 1 + nsf + ( 1 - nsf ) * nh ) * (FT_oxxxxx)0.5,
                             FT_oxxxxx( 1 + nsf - ( 1 - nsf ) * nh ) * (FT_oxxxxx)0.5 };
      FT_oxxxxx_v omega[2] = { fpsqrt<FT_oxxxxx>( pvec0 + pp ), 0 };
      omega[1] = fmass_FT / omega[0];
      const int ipB = ( 1 + nh ) / 2;
      const int imB = ( 1 - nh ) / 2;
      const FT_oxxxxx_v sfomeg[2] = { sf[0] * omega[ipB], sf[1] * omega[imB] };
      const FT_oxxxxx_v pp3 = fpmax( pp + pvec3, 0. );
      volatile FT_oxxxxx_v ppDENOM = fpternary( pp != 0, pp, 1. );    // hack: ppDENOM[ieppV]=1 if pp[ieppV]==0
      volatile FT_oxxxxx_v pp3DENOM = fpternary( pp3 != 0, pp3, 1. ); // hack: pp3DENOM[ieppV]=1 if pp3[ieppV]==0
      volatile FT_oxxxxx_v chi0r2 = pp3 * 0.5 / ppDENOM;              // volatile fixes #736
      const cxsmpl<FT_oxxxxx>_v chi[2] = { cxmake<FT_oxxxxx>( fpsqrt<FT_oxxxxx>( chi0r2 ), 0. ),    // hack: dummy[ieppV] is not used if pp[ieppV]==0
                                ( cxternary( ( pp3 == 0. ),
                                             cxmake<FT_oxxxxx>( -nh, 0. ),
                                             cxmake<FT_oxxxxx>( (FT_oxxxxx)nh * pvec1, -pvec2 ) / fpsqrt<FT_oxxxxx>( 2. * ppDENOM * pp3DENOM ) ) ) }; // hack: dummy[ieppV] is not used if pp[ieppV]==0
      const cxsmpl<FT_oxxxxx>_v foB_2 = sfomeg[1] * chi[imB];
      const cxsmpl<FT_oxxxxx>_v foB_3 = sfomeg[1] * chi[ipB];
      const cxsmpl<FT_oxxxxx>_v foB_4 = sfomeg[0] * chi[imB];
      const cxsmpl<FT_oxxxxx>_v foB_5 = sfomeg[0] * chi[ipB];
      // Choose between the results from branch A and branch B
      const bool_v mask = ( pp == 0. );
      fo[2] =static_cast<cxsmpl<fptype>>( cxternary( mask, foA_2, foB_2 ));
      fo[3] =static_cast<cxsmpl<fptype>>( cxternary( mask, foA_3, foB_3 ));
      fo[4] =static_cast<cxsmpl<fptype>>( cxternary( mask, foA_4, foB_4 ));
      fo[5] =static_cast<cxsmpl<fptype>>( cxternary( mask, foA_5, foB_5 ));
#endif
    }
    else
    {
#ifdef MGONGPU_CPPSIMD
      volatile FT_oxxxxx p0p3 = fpmax( pvec0 + pvec3, 0 ); // volatile fixes #736
      volatile FT_oxxxxx sqp0p3 = fpternary( ( pvec1 == 0. and pvec2 == 0. and pvec3 < 0. ),
                                             FT_oxxxxx{ 0 },
                                             fpsqrt<FT_oxxxxx>( p0p3 ) * (FT_oxxxxx)nsf );
      volatile FT_oxxxxx_v sqp0p3DENOM = fpternary( sqp0p3 != 0, (FT_oxxxxx)sqp0p3, 1. ); // hack: sqp0p3DENOM[ieppV]=1 if sqp0p3[ieppV]==0
      const cxsmpl<FT_oxxxxx>_v chi[2] = { cxmake<FT_oxxxxx>( (FT_oxxxxx_v)sqp0p3, 0. ),
                                cxternary( ( sqp0p3 == 0. ),
                                           cxmake<FT_oxxxxx>( -nhel, 0. ) * fpsqrt<FT_oxxxxx>( 2. * pvec0 ),
                                           cxmake<FT_oxxxxx>( (FT_oxxxxx)nh * pvec1, -pvec2 ) / (const FT_oxxxxx)sqp0p3DENOM ) }; // hack: dummy[ieppV] is not used if sqp0p3[ieppV]==0
#else
      const FT_oxxxxx sqp0p3 = fpternary( ( pvec1 == 0. ) and ( pvec2 == 0. ) and ( pvec3 < 0. ),
                                          0,
                                          fpsqrt<FT_oxxxxx>( fpmax( pvec0 + pvec3, 0. ) ) * (FT_oxxxxx)nsf );
      const cxsmpl<FT_oxxxxx> chi[2] = { cxmake<FT_oxxxxx>( sqp0p3, 0. ),
                                 ( sqp0p3 == 0. ? cxmake<FT_oxxxxx>( -nhel, 0. ) * fpsqrt<FT_oxxxxx>( 2. * pvec0 ) : cxmake<FT_oxxxxx>( (FT_oxxxxx)nh * pvec1, -pvec2 ) / sqp0p3 ) };
#endif
      if( nh == 1 )
      {
        fo[2] =static_cast<cxsmpl<fptype>>( chi[0]);
        fo[3] =static_cast<cxsmpl<fptype>>( chi[1]);
        fo[4] =static_cast<cxsmpl<fptype>>( cxzero<FT_oxxxxx>());
        fo[5] =static_cast<cxsmpl<fptype>>( cxzero<FT_oxxxxx>());
      }
      else
      {
        fo[2] =static_cast<cxsmpl<fptype>>( cxzero<FT_oxxxxx>());
        fo[3] =static_cast<cxsmpl<fptype>>( cxzero<FT_oxxxxx>());
        fo[4] =static_cast<cxsmpl<fptype>>( chi[1]);
        fo[5] =static_cast<cxsmpl<fptype>>( chi[0]);
      }
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fo[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PX == PY == 0 and E == +PZ > 0)
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ void
  opzxxx( const fptype momenta[], // input: momenta
          //const fptype fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    const fptype& _pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    cxtype_sv* fo = W_ACCESS::kernelAccess( wavefunctions );
	 	 const FT_opzxxx pvec3 = static_cast<FT_opzxxx>(_pvec3);
    fo[0] =static_cast<cxsmpl<fptype>>( cxmake<FT_opzxxx>( pvec3 * (FT_opzxxx)nsf, pvec3 * (FT_opzxxx)nsf ));
    fo[1] =static_cast<cxsmpl<fptype>>( cxzero<FT_opzxxx>());
    const int nh = nhel * nsf;
    const cxsmpl<FT_opzxxx> csqp0p3 = cxmake<FT_opzxxx>( fpsqrt<FT_opzxxx>( 2. * pvec3 ) * (FT_opzxxx)nsf, 0. );
    fo[3] =static_cast<cxsmpl<fptype>>( cxzero<FT_opzxxx>());
    fo[4] =static_cast<cxsmpl<fptype>>( cxzero<FT_opzxxx>());
    if( nh == 1 )
    {
      fo[2] =static_cast<cxsmpl<fptype>>( csqp0p3);
      fo[5] =static_cast<cxsmpl<fptype>>( cxzero<FT_opzxxx>());
    }
    else
    {
      fo[2] =static_cast<cxsmpl<fptype>>( cxzero<FT_opzxxx>());
      fo[5] =static_cast<cxsmpl<fptype>>( csqp0p3);
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fo[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PX == PY == 0 and E == -PZ > 0)
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ void
  omzxxx( const fptype momenta[], // input: momenta
          //const fptype fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    const fptype& _pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    cxtype_sv* fo = W_ACCESS::kernelAccess( wavefunctions );
	 	 const FT_omzxxx pvec3 = static_cast<FT_omzxxx>(_pvec3);
    fo[0] =static_cast<cxsmpl<fptype>>( cxmake<FT_omzxxx>( -pvec3 * (FT_omzxxx)nsf, pvec3 * (FT_omzxxx)nsf )); // remember pvec0 == -pvec3
    fo[1] =static_cast<cxsmpl<fptype>>( cxzero<FT_omzxxx>());
    const int nh = nhel * nsf;
    const cxsmpl<FT_omzxxx> chi1 = cxmake<FT_omzxxx>( -nhel, 0. ) * fpsqrt<FT_omzxxx>( -2. * pvec3 );
    if( nh == 1 )
    {
      fo[2] =static_cast<cxsmpl<fptype>>( cxzero<FT_omzxxx>());
      fo[3] =static_cast<cxsmpl<fptype>>( chi1);
      fo[4] =static_cast<cxsmpl<fptype>>( cxzero<FT_omzxxx>());
      fo[5] =static_cast<cxsmpl<fptype>>( cxzero<FT_omzxxx>());
    }
    else
    {
      fo[2] =static_cast<cxsmpl<fptype>>( cxzero<FT_omzxxx>());
      fo[3] =static_cast<cxsmpl<fptype>>( cxzero<FT_omzxxx>());
      fo[4] =static_cast<cxsmpl<fptype>>( chi1);
      //fo[5] =static_cast<cxsmpl<fptype>>( chi1); // AV: BUG!
      fo[5] =static_cast<cxsmpl<fptype>>( cxzero<FT_omzxxx>()); // AV: BUG FIX
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction fo[6] from the input momenta[npar*4*nevt]
  // ASSUMPTIONS: (FMASS == 0) and (PT > 0)
  template<class M_ACCESS, class W_ACCESS>
  __host__ __device__ void
  oxzxxx( const fptype momenta[], // input: momenta
          //const fptype fmass,   // [skip: ASSUME fermion mass==0]
          const int nhel,         // input: -1 or +1 (helicity of fermion)
          const int nsf,          // input: +1 (particle) or -1 (antiparticle)
          fptype wavefunctions[], // output: wavefunctions
          const int ipar )        // input: particle# out of npar
  {
    mgDebug( 0, __FUNCTION__ );
    const fptype& _pvec0 = M_ACCESS::kernelAccessIp4IparConst( momenta, 0, ipar );
    const fptype& _pvec1 = M_ACCESS::kernelAccessIp4IparConst( momenta, 1, ipar );
    const fptype& _pvec2 = M_ACCESS::kernelAccessIp4IparConst( momenta, 2, ipar );
    const fptype& _pvec3 = M_ACCESS::kernelAccessIp4IparConst( momenta, 3, ipar );
    cxtype_sv* fo = W_ACCESS::kernelAccess( wavefunctions );
	 	 const FT_oxzxxx pvec0 = static_cast<FT_oxzxxx>(_pvec0);
	 	 const FT_oxzxxx pvec1 = static_cast<FT_oxzxxx>(_pvec1);
	 	 const FT_oxzxxx pvec2 = static_cast<FT_oxzxxx>(_pvec2);
	 	 const FT_oxzxxx pvec3 = static_cast<FT_oxzxxx>(_pvec3);
    fo[0] =static_cast<cxsmpl<fptype>>( cxmake<FT_oxzxxx>( pvec0 * (FT_oxzxxx)nsf, pvec3 * (FT_oxzxxx)nsf ));
    fo[1] =static_cast<cxsmpl<fptype>>( cxmake<FT_oxzxxx>( pvec1 * (FT_oxzxxx)nsf, pvec2 * (FT_oxzxxx)nsf ));
    const int nh = nhel * nsf;
    //const float sqp0p3 = sqrtf( pvec0 + pvec3 ) * nsf; // AV: why force a float here?
    const FT_oxzxxx sqp0p3 = fpsqrt<FT_oxzxxx>( pvec0 + pvec3 ) * (FT_oxzxxx)nsf;
    const cxsmpl<FT_oxzxxx> chi0 = cxmake<FT_oxzxxx>( sqp0p3, 0. );
    const cxsmpl<FT_oxzxxx> chi1 = cxmake<FT_oxzxxx>( (FT_oxzxxx)nh * pvec1 / sqp0p3, -pvec2 / sqp0p3 );
    if( nh == 1 )
    {
      fo[2] =static_cast<cxsmpl<fptype>>( chi0);
      fo[3] =static_cast<cxsmpl<fptype>>( chi1);
      fo[4] =static_cast<cxsmpl<fptype>>( cxzero<FT_oxzxxx>());
      fo[5] =static_cast<cxsmpl<fptype>>( cxzero<FT_oxzxxx>());
    }
    else
    {
      fo[2] =static_cast<cxsmpl<fptype>>( cxzero<FT_oxzxxx>());
      fo[3] =static_cast<cxsmpl<fptype>>( cxzero<FT_oxzxxx>());
      fo[4] =static_cast<cxsmpl<fptype>>( chi1);
      fo[5] =static_cast<cxsmpl<fptype>>( chi0);
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //==========================================================================

  // Compute the output wavefunction 'F1[6]' from the input wavefunctions F2[6], V3[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ INLINE void
  FFV1_1( const fptype allF2[],
          const fptype allV3[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          const fptype M1,
          const fptype W1,
          fptype allF1[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'F2[6]' from the input wavefunctions F1[6], V3[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ INLINE void
  FFV1_2( const fptype allF1[],
          const fptype allV3[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          const fptype M2,
          const fptype W2,
          fptype allF2[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V3[6]' from the input wavefunctions F1[6], F2[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ INLINE void
  FFV1P0_3( const fptype allF1[],
            const fptype allF2[],
            const fptype allCOUP[],
            const fptype Ccoeff,
            const fptype M3,
            const fptype W3,
            fptype allV3[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions F1[6], F2[6], V3[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS>
  __device__ INLINE void
  FFV2_0( const fptype allF1[],
          const fptype allF2[],
          const fptype allV3[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          fptype allvertexes[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V3[6]' from the input wavefunctions F1[6], F2[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ INLINE void
  FFV2_3( const fptype allF1[],
          const fptype allF2[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          const fptype M3,
          const fptype W3,
          fptype allV3[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions F1[6], F2[6], V3[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS>
  __device__ INLINE void
  FFV5_0( const fptype allF1[],
          const fptype allF2[],
          const fptype allV3[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          fptype allvertexes[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V3[6]' from the input wavefunctions F1[6], F2[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ INLINE void
  FFV5_3( const fptype allF1[],
          const fptype allF2[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          const fptype M3,
          const fptype W3,
          fptype allV3[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions V1[6], V2[6], S3[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS>
  __device__ INLINE void
  VVS1_0( const fptype allV1[],
          const fptype allV2[],
          const fptype allS3[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          fptype allvertexes[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V1[6]' from the input wavefunctions V2[6], S3[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ INLINE void
  VVS1_1( const fptype allV2[],
          const fptype allS3[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          const fptype M1,
          const fptype W1,
          fptype allV1[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V2[6]' from the input wavefunctions V1[6], S3[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ INLINE void
  VVS1_2( const fptype allV1[],
          const fptype allS3[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          const fptype M2,
          const fptype W2,
          fptype allV2[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions F1[6], F2[6], V3[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS>
  __device__ INLINE void
  FFV3_0( const fptype allF1[],
          const fptype allF2[],
          const fptype allV3[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          fptype allvertexes[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V3[6]' from the input wavefunctions F1[6], F2[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ INLINE void
  FFV3_3( const fptype allF1[],
          const fptype allF2[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          const fptype M3,
          const fptype W3,
          fptype allV3[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V1[6]' from the input wavefunctions V2[6], V3[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ INLINE void
  VVV1P0_1( const fptype allV2[],
            const fptype allV3[],
            const fptype allCOUP[],
            const fptype Ccoeff,
            const fptype M1,
            const fptype W1,
            fptype allV1[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions F1[6], F2[6], V3[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS>
  __device__ INLINE void
  FFV2_5_0( const fptype allF1[],
            const fptype allF2[],
            const fptype allV3[],
            const fptype allCOUP1[],
            const fptype Ccoeff1,
            const fptype allCOUP2[],
            const fptype Ccoeff2,
            fptype allvertexes[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V3[6]' from the input wavefunctions F1[6], F2[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ INLINE void
  FFV2_5_3( const fptype allF1[],
            const fptype allF2[],
            const fptype allCOUP1[],
            const fptype Ccoeff1,
            const fptype allCOUP2[],
            const fptype Ccoeff2,
            const fptype M3,
            const fptype W3,
            fptype allV3[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions F1[6], F2[6], V3[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS>
  __device__ INLINE void
  FFV2_3_0( const fptype allF1[],
            const fptype allF2[],
            const fptype allV3[],
            const fptype allCOUP1[],
            const fptype Ccoeff1,
            const fptype allCOUP2[],
            const fptype Ccoeff2,
            fptype allvertexes[] ) ALWAYS_INLINE;

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V3[6]' from the input wavefunctions F1[6], F2[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ INLINE void
  FFV2_3_3( const fptype allF1[],
            const fptype allF2[],
            const fptype allCOUP1[],
            const fptype Ccoeff1,
            const fptype allCOUP2[],
            const fptype Ccoeff2,
            const fptype M3,
            const fptype W3,
            fptype allV3[] ) ALWAYS_INLINE;

  //==========================================================================

  // Compute the output wavefunction 'F1[6]' from the input wavefunctions F2[6], V3[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ void
  FFV1_1( const fptype allF2[],
          const fptype allV3[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          const fptype M1,
          const fptype W1,
          fptype allF1[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const cxtype_sv* F2_ = W_ACCESS::kernelAccessConst( allF2 );
    const cxtype_sv* V3_ = W_ACCESS::kernelAccessConst( allV3 );
    const cxtype_sv COUP_ = C_ACCESS::kernelAccessConst( allCOUP );
    cxtype_sv* F1 = W_ACCESS::kernelAccess( allF1 );
	 	 cxsmpl<FT_FFV1_1> F2[6];
	 	 cxsmpl<FT_FFV1_1> V3[6];
	 	 const cxsmpl<FT_FFV1_1> COUP = static_cast<cxsmpl<FT_FFV1_1>>(COUP_);
		for(int i = 0; i < 6; ++i)
		{
	 	 F2[i] = static_cast<cxsmpl<FT_FFV1_1>>(F2_[i]);
	 	 V3[i] = static_cast<cxsmpl<FT_FFV1_1>>(V3_[i]);
		}
    const cxsmpl<FT_FFV1_1> cI = cxmake<FT_FFV1_1>( 0., 1. );
    F1[0] =static_cast<cxsmpl<fptype>>( +F2[0] + V3[0]);
    F1[1] =static_cast<cxsmpl<fptype>>( +F2[1] + V3[1]);
    const FT_FFV1_1 P1[4] = { static_cast<FT_FFV1_1>(-cxreal( F1[0] )), static_cast<FT_FFV1_1>(-cxreal( F1[1] )), static_cast<FT_FFV1_1>(-cximag( F1[1] )), static_cast<FT_FFV1_1>(-cximag( F1[0] )) };
    const FT_FFV1_1 one( 1. );
    const cxsmpl<FT_FFV1_1> denom = static_cast<FT_FFV1_1>(Ccoeff) * COUP / ( ( P1[0] * P1[0] ) - ( P1[1] * P1[1] ) - ( P1[2] * P1[2] ) - ( P1[3] * P1[3] ) - static_cast<FT_FFV1_1>(M1) * ( static_cast<FT_FFV1_1>(M1) - cI * static_cast<FT_FFV1_1>(W1) ) );
    F1[2] =static_cast<cxsmpl<fptype>>( denom * cI * ( F2[2] * ( P1[0] * ( -V3[2] + V3[5] ) + ( P1[1] * ( V3[3] - cI * V3[4] ) + ( P1[2] * ( +cI * V3[3] + V3[4] ) + P1[3] * ( -V3[2] + V3[5] ) ) ) ) + ( F2[3] * ( P1[0] * ( V3[3] + cI * V3[4] ) + ( P1[1] * ( -one ) * ( V3[2] + V3[5] ) + ( P1[2] * ( -one ) * ( +cI * ( V3[2] + V3[5] ) ) + P1[3] * ( V3[3] + cI * V3[4] ) ) ) ) + static_cast<FT_FFV1_1>(M1) * ( F2[4] * ( V3[2] + V3[5] ) + F2[5] * ( V3[3] + cI * V3[4] ) ) ) ));
    F1[3] =static_cast<cxsmpl<fptype>>( denom * ( -cI ) * ( F2[2] * ( P1[0] * ( -V3[3] + cI * V3[4] ) + ( P1[1] * ( V3[2] - V3[5] ) + ( P1[2] * ( -cI * V3[2] + cI * V3[5] ) + P1[3] * ( V3[3] - cI * V3[4] ) ) ) ) + ( F2[3] * ( P1[0] * ( V3[2] + V3[5] ) + ( P1[1] * ( -one ) * ( V3[3] + cI * V3[4] ) + ( P1[2] * ( +cI * V3[3] - V3[4] ) - P1[3] * ( V3[2] + V3[5] ) ) ) ) + static_cast<FT_FFV1_1>(M1) * ( F2[4] * ( -V3[3] + cI * V3[4] ) + F2[5] * ( -V3[2] + V3[5] ) ) ) ));
    F1[4] =static_cast<cxsmpl<fptype>>( denom * ( -cI ) * ( F2[4] * ( P1[0] * ( V3[2] + V3[5] ) + ( P1[1] * ( -V3[3] + cI * V3[4] ) + ( P1[2] * ( -one ) * ( +cI * V3[3] + V3[4] ) - P1[3] * ( V3[2] + V3[5] ) ) ) ) + ( F2[5] * ( P1[0] * ( V3[3] + cI * V3[4] ) + ( P1[1] * ( -V3[2] + V3[5] ) + ( P1[2] * ( -cI * V3[2] + cI * V3[5] ) - P1[3] * ( V3[3] + cI * V3[4] ) ) ) ) + static_cast<FT_FFV1_1>(M1) * ( F2[2] * ( -V3[2] + V3[5] ) + F2[3] * ( V3[3] + cI * V3[4] ) ) ) ));
    F1[5] =static_cast<cxsmpl<fptype>>( denom * cI * ( F2[4] * ( P1[0] * ( -V3[3] + cI * V3[4] ) + ( P1[1] * ( V3[2] + V3[5] ) + ( P1[2] * ( -one ) * ( +cI * ( V3[2] + V3[5] ) ) + P1[3] * ( -V3[3] + cI * V3[4] ) ) ) ) + ( F2[5] * ( P1[0] * ( -V3[2] + V3[5] ) + ( P1[1] * ( V3[3] + cI * V3[4] ) + ( P1[2] * ( -cI * V3[3] + V3[4] ) + P1[3] * ( -V3[2] + V3[5] ) ) ) ) + static_cast<FT_FFV1_1>(M1) * ( F2[2] * ( -V3[3] + cI * V3[4] ) + F2[3] * ( V3[2] + V3[5] ) ) ) ));
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'F2[6]' from the input wavefunctions F1[6], V3[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ void
  FFV1_2( const fptype allF1[],
          const fptype allV3[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          const fptype M2,
          const fptype W2,
          fptype allF2[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const cxtype_sv* F1_ = W_ACCESS::kernelAccessConst( allF1 );
    const cxtype_sv* V3_ = W_ACCESS::kernelAccessConst( allV3 );
    const cxtype_sv COUP_ = C_ACCESS::kernelAccessConst( allCOUP );
    cxtype_sv* F2 = W_ACCESS::kernelAccess( allF2 );
	 	 cxsmpl<FT_FFV1_2> F1[6];
	 	 cxsmpl<FT_FFV1_2> V3[6];
	 	 const cxsmpl<FT_FFV1_2> COUP = static_cast<cxsmpl<FT_FFV1_2>>(COUP_);
		for(int i = 0; i < 6; ++i)
		{
	 	 F1[i] = static_cast<cxsmpl<FT_FFV1_2>>(F1_[i]);
	 	 V3[i] = static_cast<cxsmpl<FT_FFV1_2>>(V3_[i]);
		}
    const cxsmpl<FT_FFV1_2> cI = cxmake<FT_FFV1_2>( 0., 1. );
    F2[0] =static_cast<cxsmpl<fptype>>( +F1[0] + V3[0]);
    F2[1] =static_cast<cxsmpl<fptype>>( +F1[1] + V3[1]);
    const FT_FFV1_2 P2[4] = { static_cast<FT_FFV1_2>(-cxreal( F2[0] )), static_cast<FT_FFV1_2>(-cxreal( F2[1] )), static_cast<FT_FFV1_2>(-cximag( F2[1] )), static_cast<FT_FFV1_2>(-cximag( F2[0] )) };
    const FT_FFV1_2 one( 1. );
    const cxsmpl<FT_FFV1_2> denom = static_cast<FT_FFV1_2>(Ccoeff) * COUP / ( ( P2[0] * P2[0] ) - ( P2[1] * P2[1] ) - ( P2[2] * P2[2] ) - ( P2[3] * P2[3] ) - static_cast<FT_FFV1_2>(M2) * ( static_cast<FT_FFV1_2>(M2) - cI * static_cast<FT_FFV1_2>(W2) ) );
    F2[2] =static_cast<cxsmpl<fptype>>( denom * cI * ( F1[2] * ( P2[0] * ( V3[2] + V3[5] ) + ( P2[1] * ( -one ) * ( V3[3] + cI * V3[4] ) + ( P2[2] * ( +cI * V3[3] - V3[4] ) - P2[3] * ( V3[2] + V3[5] ) ) ) ) + ( F1[3] * ( P2[0] * ( V3[3] - cI * V3[4] ) + ( P2[1] * ( -V3[2] + V3[5] ) + ( P2[2] * ( +cI * V3[2] - cI * V3[5] ) + P2[3] * ( -V3[3] + cI * V3[4] ) ) ) ) + static_cast<FT_FFV1_2>(M2) * ( F1[4] * ( V3[2] - V3[5] ) + F1[5] * ( -V3[3] + cI * V3[4] ) ) ) ));
    F2[3] =static_cast<cxsmpl<fptype>>( denom * ( -cI ) * ( F1[2] * ( P2[0] * ( -one ) * ( V3[3] + cI * V3[4] ) + ( P2[1] * ( V3[2] + V3[5] ) + ( P2[2] * ( +cI * ( V3[2] + V3[5] ) ) - P2[3] * ( V3[3] + cI * V3[4] ) ) ) ) + ( F1[3] * ( P2[0] * ( -V3[2] + V3[5] ) + ( P2[1] * ( V3[3] - cI * V3[4] ) + ( P2[2] * ( +cI * V3[3] + V3[4] ) + P2[3] * ( -V3[2] + V3[5] ) ) ) ) + static_cast<FT_FFV1_2>(M2) * ( F1[4] * ( V3[3] + cI * V3[4] ) - F1[5] * ( V3[2] + V3[5] ) ) ) ));
    F2[4] =static_cast<cxsmpl<fptype>>( denom * ( -cI ) * ( F1[4] * ( P2[0] * ( -V3[2] + V3[5] ) + ( P2[1] * ( V3[3] + cI * V3[4] ) + ( P2[2] * ( -cI * V3[3] + V3[4] ) + P2[3] * ( -V3[2] + V3[5] ) ) ) ) + ( F1[5] * ( P2[0] * ( V3[3] - cI * V3[4] ) + ( P2[1] * ( -one ) * ( V3[2] + V3[5] ) + ( P2[2] * ( +cI * ( V3[2] + V3[5] ) ) + P2[3] * ( V3[3] - cI * V3[4] ) ) ) ) + static_cast<FT_FFV1_2>(M2) * ( F1[2] * ( -one ) * ( V3[2] + V3[5] ) + F1[3] * ( -V3[3] + cI * V3[4] ) ) ) ));
    F2[5] =static_cast<cxsmpl<fptype>>( denom * cI * ( F1[4] * ( P2[0] * ( -one ) * ( V3[3] + cI * V3[4] ) + ( P2[1] * ( V3[2] - V3[5] ) + ( P2[2] * ( +cI * V3[2] - cI * V3[5] ) + P2[3] * ( V3[3] + cI * V3[4] ) ) ) ) + ( F1[5] * ( P2[0] * ( V3[2] + V3[5] ) + ( P2[1] * ( -V3[3] + cI * V3[4] ) + ( P2[2] * ( -one ) * ( +cI * V3[3] + V3[4] ) - P2[3] * ( V3[2] + V3[5] ) ) ) ) + static_cast<FT_FFV1_2>(M2) * ( F1[2] * ( V3[3] + cI * V3[4] ) + F1[3] * ( V3[2] - V3[5] ) ) ) ));
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V3[6]' from the input wavefunctions F1[6], F2[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ void
  FFV1P0_3( const fptype allF1[],
            const fptype allF2[],
            const fptype allCOUP[],
            const fptype Ccoeff,
            const fptype M3,
            const fptype W3,
            fptype allV3[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const cxtype_sv* F1_ = W_ACCESS::kernelAccessConst( allF1 );
    const cxtype_sv* F2_ = W_ACCESS::kernelAccessConst( allF2 );
    const cxtype_sv COUP_ = C_ACCESS::kernelAccessConst( allCOUP );
    cxtype_sv* V3 = W_ACCESS::kernelAccess( allV3 );
	 	 cxsmpl<FT_FFV1P0_3> F1[6];
	 	 cxsmpl<FT_FFV1P0_3> F2[6];
	 	 const cxsmpl<FT_FFV1P0_3> COUP = static_cast<cxsmpl<FT_FFV1P0_3>>(COUP_);
		for(int i = 0; i < 6; ++i)
		{
	 	 F1[i] = static_cast<cxsmpl<FT_FFV1P0_3>>(F1_[i]);
	 	 F2[i] = static_cast<cxsmpl<FT_FFV1P0_3>>(F2_[i]);
		}
    const cxsmpl<FT_FFV1P0_3> cI = cxmake<FT_FFV1P0_3>( 0., 1. );
    V3[0] =static_cast<cxsmpl<fptype>>( +F1[0] + F2[0]);
    V3[1] =static_cast<cxsmpl<fptype>>( +F1[1] + F2[1]);
    const FT_FFV1P0_3 P3[4] = { static_cast<FT_FFV1P0_3>(-cxreal( V3[0] )), static_cast<FT_FFV1P0_3>(-cxreal( V3[1] )), static_cast<FT_FFV1P0_3>(-cximag( V3[1] )), static_cast<FT_FFV1P0_3>(-cximag( V3[0] )) };
    const cxsmpl<FT_FFV1P0_3> denom = static_cast<FT_FFV1P0_3>(Ccoeff) * COUP / ( ( P3[0] * P3[0] ) - ( P3[1] * P3[1] ) - ( P3[2] * P3[2] ) - ( P3[3] * P3[3] ) - static_cast<FT_FFV1P0_3>(M3) * ( static_cast<FT_FFV1P0_3>(M3) - cI * static_cast<FT_FFV1P0_3>(W3) ) );
    V3[2] =static_cast<cxsmpl<fptype>>( denom * ( -cI ) * ( F2[4] * F1[2] + F2[5] * F1[3] + F2[2] * F1[4] + F2[3] * F1[5] ));
    V3[3] =static_cast<cxsmpl<fptype>>( denom * ( -cI ) * ( -F2[5] * F1[2] - F2[4] * F1[3] + F2[3] * F1[4] + F2[2] * F1[5] ));
    V3[4] =static_cast<cxsmpl<fptype>>( denom * ( -cI ) * ( -cI * ( F2[5] * F1[2] + F2[2] * F1[5] ) + cI * ( F2[4] * F1[3] + F2[3] * F1[4] ) ));
    V3[5] =static_cast<cxsmpl<fptype>>( denom * ( -cI ) * ( -F2[4] * F1[2] - F2[3] * F1[5] + F2[5] * F1[3] + F2[2] * F1[4] ));
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions F1[6], F2[6], V3[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS>
  __device__ void
  FFV2_0( const fptype allF1[],
          const fptype allF2[],
          const fptype allV3[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          fptype allvertexes[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const cxtype_sv* F1_ = W_ACCESS::kernelAccessConst( allF1 );
    const cxtype_sv* F2_ = W_ACCESS::kernelAccessConst( allF2 );
    const cxtype_sv* V3_ = W_ACCESS::kernelAccessConst( allV3 );
    const cxtype_sv COUP_ = C_ACCESS::kernelAccessConst( allCOUP );
    cxtype_sv* vertex = A_ACCESS::kernelAccess( allvertexes );
	 	 cxsmpl<FT_FFV2_0> F1[6];
	 	 cxsmpl<FT_FFV2_0> F2[6];
	 	 cxsmpl<FT_FFV2_0> V3[6];
	 	 const cxsmpl<FT_FFV2_0> COUP = static_cast<cxsmpl<FT_FFV2_0>>(COUP_);
		for(int i = 0; i < 6; ++i)
		{
	 	 F1[i] = static_cast<cxsmpl<FT_FFV2_0>>(F1_[i]);
	 	 F2[i] = static_cast<cxsmpl<FT_FFV2_0>>(F2_[i]);
	 	 V3[i] = static_cast<cxsmpl<FT_FFV2_0>>(V3_[i]);
		}
    const cxsmpl<FT_FFV2_0> cI = cxmake<FT_FFV2_0>( 0., 1. );
    const cxsmpl<FT_FFV2_0> TMP0 = ( F1[2] * ( F2[4] * ( V3[2] + V3[5] ) + F2[5] * ( V3[3] + cI * V3[4] ) ) + F1[3] * ( F2[4] * ( V3[3] - cI * V3[4] ) + F2[5] * ( V3[2] - V3[5] ) ) );
    ( *vertex ) =static_cast<cxsmpl<fptype>>( static_cast<FT_FFV2_0>(Ccoeff) * COUP * -cI * TMP0);
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V3[6]' from the input wavefunctions F1[6], F2[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ void
  FFV2_3( const fptype allF1[],
          const fptype allF2[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          const fptype M3,
          const fptype W3,
          fptype allV3[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const cxtype_sv* F1_ = W_ACCESS::kernelAccessConst( allF1 );
    const cxtype_sv* F2_ = W_ACCESS::kernelAccessConst( allF2 );
    const cxtype_sv COUP_ = C_ACCESS::kernelAccessConst( allCOUP );
    cxtype_sv* V3 = W_ACCESS::kernelAccess( allV3 );
	 	 cxsmpl<FT_FFV2_3> F1[6];
	 	 cxsmpl<FT_FFV2_3> F2[6];
	 	 const cxsmpl<FT_FFV2_3> COUP = static_cast<cxsmpl<FT_FFV2_3>>(COUP_);
		for(int i = 0; i < 6; ++i)
		{
	 	 F1[i] = static_cast<cxsmpl<FT_FFV2_3>>(F1_[i]);
	 	 F2[i] = static_cast<cxsmpl<FT_FFV2_3>>(F2_[i]);
		}
    const cxsmpl<FT_FFV2_3> cI = cxmake<FT_FFV2_3>( 0., 1. );
    const FT_FFV2_3 OM3 =  (FT_FFV2_3) ( static_cast<FT_FFV2_3>(M3) != 0. ? 1. / ( static_cast<FT_FFV2_3>(M3) * static_cast<FT_FFV2_3>(M3) ) :  (FT_FFV2_3) 0. );
    V3[0] =static_cast<cxsmpl<fptype>>( +F1[0] + F2[0]);
    V3[1] =static_cast<cxsmpl<fptype>>( +F1[1] + F2[1]);
    const FT_FFV2_3 P3[4] = { static_cast<FT_FFV2_3>(-cxreal( V3[0] )), static_cast<FT_FFV2_3>(-cxreal( V3[1] )), static_cast<FT_FFV2_3>(-cximag( V3[1] )), static_cast<FT_FFV2_3>(-cximag( V3[0] )) };
    const cxsmpl<FT_FFV2_3> TMP1 = ( F1[2] * ( F2[4] * ( P3[0] + P3[3] ) + F2[5] * ( P3[1] + cI * P3[2] ) ) + F1[3] * ( F2[4] * ( P3[1] - cI * P3[2] ) + F2[5] * ( P3[0] - P3[3] ) ) );
    const cxsmpl<FT_FFV2_3> denom = static_cast<FT_FFV2_3>(Ccoeff) * COUP / ( ( P3[0] * P3[0] ) - ( P3[1] * P3[1] ) - ( P3[2] * P3[2] ) - ( P3[3] * P3[3] ) - static_cast<FT_FFV2_3>(M3) * ( static_cast<FT_FFV2_3>(M3) - cI * static_cast<FT_FFV2_3>(W3) ) );
    V3[2] =static_cast<cxsmpl<fptype>>( denom * ( -cI ) * ( F2[4] * F1[2] + F2[5] * F1[3] - P3[0] * OM3 * TMP1 ));
    V3[3] =static_cast<cxsmpl<fptype>>( denom * ( -cI ) * ( -F2[4] * F1[3] - F2[5] * F1[2] - P3[1] * OM3 * TMP1 ));
    V3[4] =static_cast<cxsmpl<fptype>>( denom * ( -cI ) * ( +cI * ( F2[4] * F1[3] ) - cI * ( F2[5] * F1[2] ) - P3[2] * OM3 * TMP1 ));
    V3[5] =static_cast<cxsmpl<fptype>>( denom * ( -cI ) * ( -F2[4] * F1[2] - P3[3] * OM3 * TMP1 + F2[5] * F1[3] ));
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions F1[6], F2[6], V3[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS>
  __device__ void
  FFV5_0( const fptype allF1[],
          const fptype allF2[],
          const fptype allV3[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          fptype allvertexes[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const cxtype_sv* F1_ = W_ACCESS::kernelAccessConst( allF1 );
    const cxtype_sv* F2_ = W_ACCESS::kernelAccessConst( allF2 );
    const cxtype_sv* V3_ = W_ACCESS::kernelAccessConst( allV3 );
    const cxtype_sv COUP_ = C_ACCESS::kernelAccessConst( allCOUP );
    cxtype_sv* vertex = A_ACCESS::kernelAccess( allvertexes );
	 	 cxsmpl<FT_FFV5_0> F1[6];
	 	 cxsmpl<FT_FFV5_0> F2[6];
	 	 cxsmpl<FT_FFV5_0> V3[6];
	 	 const cxsmpl<FT_FFV5_0> COUP = static_cast<cxsmpl<FT_FFV5_0>>(COUP_);
		for(int i = 0; i < 6; ++i)
		{
	 	 F1[i] = static_cast<cxsmpl<FT_FFV5_0>>(F1_[i]);
	 	 F2[i] = static_cast<cxsmpl<FT_FFV5_0>>(F2_[i]);
	 	 V3[i] = static_cast<cxsmpl<FT_FFV5_0>>(V3_[i]);
		}
    const cxsmpl<FT_FFV5_0> cI = cxmake<FT_FFV5_0>( 0., 1. );
    const FT_FFV5_0 one( 1. );
    const cxsmpl<FT_FFV5_0> TMP2 = ( F1[2] * ( F2[4] * ( V3[2] + V3[5] ) + F2[5] * ( V3[3] + cI * V3[4] ) ) + F1[3] * ( F2[4] * ( V3[3] - cI * V3[4] ) + F2[5] * ( V3[2] - V3[5] ) ) );
    const cxsmpl<FT_FFV5_0> TMP3 = ( F1[4] * ( F2[2] * ( V3[2] - V3[5] ) - F2[3] * ( V3[3] + cI * V3[4] ) ) + F1[5] * ( F2[2] * ( -V3[3] + cI * V3[4] ) + F2[3] * ( V3[2] + V3[5] ) ) );
    ( *vertex ) =static_cast<cxsmpl<fptype>>( static_cast<FT_FFV5_0>(Ccoeff) * COUP * ( -one ) * ( +cI * TMP2 + ( 4. * cI ) * TMP3 ));
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V3[6]' from the input wavefunctions F1[6], F2[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ void
  FFV5_3( const fptype allF1[],
          const fptype allF2[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          const fptype M3,
          const fptype W3,
          fptype allV3[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const cxtype_sv* F1_ = W_ACCESS::kernelAccessConst( allF1 );
    const cxtype_sv* F2_ = W_ACCESS::kernelAccessConst( allF2 );
    const cxtype_sv COUP_ = C_ACCESS::kernelAccessConst( allCOUP );
    cxtype_sv* V3 = W_ACCESS::kernelAccess( allV3 );
	 	 cxsmpl<FT_FFV5_3> F1[6];
	 	 cxsmpl<FT_FFV5_3> F2[6];
	 	 const cxsmpl<FT_FFV5_3> COUP = static_cast<cxsmpl<FT_FFV5_3>>(COUP_);
		for(int i = 0; i < 6; ++i)
		{
	 	 F1[i] = static_cast<cxsmpl<FT_FFV5_3>>(F1_[i]);
	 	 F2[i] = static_cast<cxsmpl<FT_FFV5_3>>(F2_[i]);
		}
    const cxsmpl<FT_FFV5_3> cI = cxmake<FT_FFV5_3>( 0., 1. );
    const FT_FFV5_3 OM3 =  (FT_FFV5_3) ( static_cast<FT_FFV5_3>(M3) != 0. ? 1. / ( static_cast<FT_FFV5_3>(M3) * static_cast<FT_FFV5_3>(M3) ) :  (FT_FFV5_3) 0. );
    V3[0] =static_cast<cxsmpl<fptype>>( +F1[0] + F2[0]);
    V3[1] =static_cast<cxsmpl<fptype>>( +F1[1] + F2[1]);
    const FT_FFV5_3 P3[4] = { static_cast<FT_FFV5_3>(-cxreal( V3[0] )), static_cast<FT_FFV5_3>(-cxreal( V3[1] )), static_cast<FT_FFV5_3>(-cximag( V3[1] )), static_cast<FT_FFV5_3>(-cximag( V3[0] )) };
    const FT_FFV5_3 quarter( 1. / 4. );
    const cxsmpl<FT_FFV5_3> TMP1 = ( F1[2] * ( F2[4] * ( P3[0] + P3[3] ) + F2[5] * ( P3[1] + cI * P3[2] ) ) + F1[3] * ( F2[4] * ( P3[1] - cI * P3[2] ) + F2[5] * ( P3[0] - P3[3] ) ) );
    const cxsmpl<FT_FFV5_3> TMP4 = ( F1[4] * ( F2[2] * ( P3[0] - P3[3] ) - F2[3] * ( P3[1] + cI * P3[2] ) ) + F1[5] * ( F2[2] * ( -P3[1] + cI * P3[2] ) + F2[3] * ( P3[0] + P3[3] ) ) );
    const cxsmpl<FT_FFV5_3> denom = static_cast<FT_FFV5_3>(Ccoeff) * COUP / ( ( P3[0] * P3[0] ) - ( P3[1] * P3[1] ) - ( P3[2] * P3[2] ) - ( P3[3] * P3[3] ) - static_cast<FT_FFV5_3>(M3) * ( static_cast<FT_FFV5_3>(M3) - cI * static_cast<FT_FFV5_3>(W3) ) );
    V3[2] =static_cast<cxsmpl<fptype>>( denom * ( -4. * cI ) * ( OM3 * -quarter * P3[0] * ( TMP1 + 4. * TMP4 ) + ( +quarter * ( F2[4] * F1[2] + F2[5] * F1[3] ) + F2[2] * F1[4] + F2[3] * F1[5] ) ));
    V3[3] =static_cast<cxsmpl<fptype>>( denom * ( -4. * cI ) * ( OM3 * -quarter * P3[1] * ( TMP1 + 4. * TMP4 ) + ( -quarter * ( F2[4] * F1[3] + F2[5] * F1[2] ) + F2[2] * F1[5] + F2[3] * F1[4] ) ));
    V3[4] =static_cast<cxsmpl<fptype>>( denom * ( 4. * cI ) * ( OM3 * quarter * P3[2] * ( TMP1 + 4. * TMP4 ) + ( +( -quarter * cI ) * ( F2[4] * F1[3] ) + ( quarter * cI ) * ( F2[5] * F1[2] ) + cI * ( F2[2] * F1[5] ) - cI * ( F2[3] * F1[4] ) ) ));
    V3[5] =static_cast<cxsmpl<fptype>>( denom * ( 4. * cI ) * ( OM3 * quarter * P3[3] * ( TMP1 + 4. * TMP4 ) + ( +quarter * ( F2[4] * F1[2] ) - quarter * ( F2[5] * F1[3] ) - F2[2] * F1[4] + F2[3] * F1[5] ) ));
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions V1[6], V2[6], S3[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS>
  __device__ void
  VVS1_0( const fptype allV1[],
          const fptype allV2[],
          const fptype allS3[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          fptype allvertexes[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const cxtype_sv* V1_ = W_ACCESS::kernelAccessConst( allV1 );
    const cxtype_sv* V2_ = W_ACCESS::kernelAccessConst( allV2 );
    const cxtype_sv* S3_ = W_ACCESS::kernelAccessConst( allS3 );
    const cxtype_sv COUP_ = C_ACCESS::kernelAccessConst( allCOUP );
    cxtype_sv* vertex = A_ACCESS::kernelAccess( allvertexes );
	 	 cxsmpl<FT_VVS1_0> V1[6];
	 	 cxsmpl<FT_VVS1_0> V2[6];
	 	 cxsmpl<FT_VVS1_0> S3[6];
	 	 const cxsmpl<FT_VVS1_0> COUP = static_cast<cxsmpl<FT_VVS1_0>>(COUP_);
		for(int i = 0; i < 6; ++i)
		{
	 	 V1[i] = static_cast<cxsmpl<FT_VVS1_0>>(V1_[i]);
	 	 V2[i] = static_cast<cxsmpl<FT_VVS1_0>>(V2_[i]);
	 	 S3[i] = static_cast<cxsmpl<FT_VVS1_0>>(S3_[i]);
		}
    const cxsmpl<FT_VVS1_0> cI = cxmake<FT_VVS1_0>( 0., 1. );
    const cxsmpl<FT_VVS1_0> TMP5 = ( V2[2] * V1[2] - V2[3] * V1[3] - V2[4] * V1[4] - V2[5] * V1[5] );
    ( *vertex ) =static_cast<cxsmpl<fptype>>( static_cast<FT_VVS1_0>(Ccoeff) * COUP * -cI * TMP5 * S3[2]);
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V1[6]' from the input wavefunctions V2[6], S3[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ void
  VVS1_1( const fptype allV2[],
          const fptype allS3[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          const fptype M1,
          const fptype W1,
          fptype allV1[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const cxtype_sv* V2_ = W_ACCESS::kernelAccessConst( allV2 );
    const cxtype_sv* S3_ = W_ACCESS::kernelAccessConst( allS3 );
    const cxtype_sv COUP_ = C_ACCESS::kernelAccessConst( allCOUP );
    cxtype_sv* V1 = W_ACCESS::kernelAccess( allV1 );
	 	 cxsmpl<FT_VVS1_1> V2[6];
	 	 cxsmpl<FT_VVS1_1> S3[6];
	 	 const cxsmpl<FT_VVS1_1> COUP = static_cast<cxsmpl<FT_VVS1_1>>(COUP_);
		for(int i = 0; i < 6; ++i)
		{
	 	 V2[i] = static_cast<cxsmpl<FT_VVS1_1>>(V2_[i]);
	 	 S3[i] = static_cast<cxsmpl<FT_VVS1_1>>(S3_[i]);
		}
    const cxsmpl<FT_VVS1_1> cI = cxmake<FT_VVS1_1>( 0., 1. );
    const FT_VVS1_1 OM1 =  (FT_VVS1_1) ( static_cast<FT_VVS1_1>(M1) != 0. ? 1. / ( static_cast<FT_VVS1_1>(M1) * static_cast<FT_VVS1_1>(M1) ) :  (FT_VVS1_1) 0. );
    V1[0] =static_cast<cxsmpl<fptype>>( +V2[0] + S3[0]);
    V1[1] =static_cast<cxsmpl<fptype>>( +V2[1] + S3[1]);
    const FT_VVS1_1 P1[4] = { static_cast<FT_VVS1_1>(-cxreal( V1[0] )), static_cast<FT_VVS1_1>(-cxreal( V1[1] )), static_cast<FT_VVS1_1>(-cximag( V1[1] )), static_cast<FT_VVS1_1>(-cximag( V1[0] )) };
    const cxsmpl<FT_VVS1_1> TMP6 = ( P1[0] * V2[2] - P1[1] * V2[3] - P1[2] * V2[4] - P1[3] * V2[5] );
    const cxsmpl<FT_VVS1_1> denom = static_cast<FT_VVS1_1>(Ccoeff) * COUP / ( ( P1[0] * P1[0] ) - ( P1[1] * P1[1] ) - ( P1[2] * P1[2] ) - ( P1[3] * P1[3] ) - static_cast<FT_VVS1_1>(M1) * ( static_cast<FT_VVS1_1>(M1) - cI * static_cast<FT_VVS1_1>(W1) ) );
    V1[2] =static_cast<cxsmpl<fptype>>( denom * S3[2] * ( -cI * V2[2] + cI * ( P1[0] * OM1 * TMP6 ) ));
    V1[3] =static_cast<cxsmpl<fptype>>( denom * S3[2] * ( -cI * V2[3] + cI * ( P1[1] * OM1 * TMP6 ) ));
    V1[4] =static_cast<cxsmpl<fptype>>( denom * S3[2] * ( -cI * V2[4] + cI * ( P1[2] * OM1 * TMP6 ) ));
    V1[5] =static_cast<cxsmpl<fptype>>( denom * S3[2] * ( -cI * V2[5] + cI * ( P1[3] * OM1 * TMP6 ) ));
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V2[6]' from the input wavefunctions V1[6], S3[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ void
  VVS1_2( const fptype allV1[],
          const fptype allS3[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          const fptype M2,
          const fptype W2,
          fptype allV2[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const cxtype_sv* V1_ = W_ACCESS::kernelAccessConst( allV1 );
    const cxtype_sv* S3_ = W_ACCESS::kernelAccessConst( allS3 );
    const cxtype_sv COUP_ = C_ACCESS::kernelAccessConst( allCOUP );
    cxtype_sv* V2 = W_ACCESS::kernelAccess( allV2 );
	 	 cxsmpl<FT_VVS1_2> V1[6];
	 	 cxsmpl<FT_VVS1_2> S3[6];
	 	 const cxsmpl<FT_VVS1_2> COUP = static_cast<cxsmpl<FT_VVS1_2>>(COUP_);
		for(int i = 0; i < 6; ++i)
		{
	 	 V1[i] = static_cast<cxsmpl<FT_VVS1_2>>(V1_[i]);
	 	 S3[i] = static_cast<cxsmpl<FT_VVS1_2>>(S3_[i]);
		}
    const cxsmpl<FT_VVS1_2> cI = cxmake<FT_VVS1_2>( 0., 1. );
    const FT_VVS1_2 OM2 =  (FT_VVS1_2) ( static_cast<FT_VVS1_2>(M2) != 0. ? 1. / ( static_cast<FT_VVS1_2>(M2) * static_cast<FT_VVS1_2>(M2) ) :  (FT_VVS1_2) 0. );
    V2[0] =static_cast<cxsmpl<fptype>>( +V1[0] + S3[0]);
    V2[1] =static_cast<cxsmpl<fptype>>( +V1[1] + S3[1]);
    const FT_VVS1_2 P2[4] = { static_cast<FT_VVS1_2>(-cxreal( V2[0] )), static_cast<FT_VVS1_2>(-cxreal( V2[1] )), static_cast<FT_VVS1_2>(-cximag( V2[1] )), static_cast<FT_VVS1_2>(-cximag( V2[0] )) };
    const cxsmpl<FT_VVS1_2> TMP7 = ( P2[0] * V1[2] - P2[1] * V1[3] - P2[2] * V1[4] - P2[3] * V1[5] );
    const cxsmpl<FT_VVS1_2> denom = static_cast<FT_VVS1_2>(Ccoeff) * COUP / ( ( P2[0] * P2[0] ) - ( P2[1] * P2[1] ) - ( P2[2] * P2[2] ) - ( P2[3] * P2[3] ) - static_cast<FT_VVS1_2>(M2) * ( static_cast<FT_VVS1_2>(M2) - cI * static_cast<FT_VVS1_2>(W2) ) );
    V2[2] =static_cast<cxsmpl<fptype>>( denom * S3[2] * ( -cI * V1[2] + cI * ( P2[0] * OM2 * TMP7 ) ));
    V2[3] =static_cast<cxsmpl<fptype>>( denom * S3[2] * ( -cI * V1[3] + cI * ( P2[1] * OM2 * TMP7 ) ));
    V2[4] =static_cast<cxsmpl<fptype>>( denom * S3[2] * ( -cI * V1[4] + cI * ( P2[2] * OM2 * TMP7 ) ));
    V2[5] =static_cast<cxsmpl<fptype>>( denom * S3[2] * ( -cI * V1[5] + cI * ( P2[3] * OM2 * TMP7 ) ));
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions F1[6], F2[6], V3[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS>
  __device__ void
  FFV3_0( const fptype allF1[],
          const fptype allF2[],
          const fptype allV3[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          fptype allvertexes[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const cxtype_sv* F1_ = W_ACCESS::kernelAccessConst( allF1 );
    const cxtype_sv* F2_ = W_ACCESS::kernelAccessConst( allF2 );
    const cxtype_sv* V3_ = W_ACCESS::kernelAccessConst( allV3 );
    const cxtype_sv COUP_ = C_ACCESS::kernelAccessConst( allCOUP );
    cxtype_sv* vertex = A_ACCESS::kernelAccess( allvertexes );
	 	 cxsmpl<FT_FFV3_0> F1[6];
	 	 cxsmpl<FT_FFV3_0> F2[6];
	 	 cxsmpl<FT_FFV3_0> V3[6];
	 	 const cxsmpl<FT_FFV3_0> COUP = static_cast<cxsmpl<FT_FFV3_0>>(COUP_);
		for(int i = 0; i < 6; ++i)
		{
	 	 F1[i] = static_cast<cxsmpl<FT_FFV3_0>>(F1_[i]);
	 	 F2[i] = static_cast<cxsmpl<FT_FFV3_0>>(F2_[i]);
	 	 V3[i] = static_cast<cxsmpl<FT_FFV3_0>>(V3_[i]);
		}
    const cxsmpl<FT_FFV3_0> cI = cxmake<FT_FFV3_0>( 0., 1. );
    const FT_FFV3_0 two( 2. );
    const cxsmpl<FT_FFV3_0> TMP2 = ( F1[2] * ( F2[4] * ( V3[2] + V3[5] ) + F2[5] * ( V3[3] + cI * V3[4] ) ) + F1[3] * ( F2[4] * ( V3[3] - cI * V3[4] ) + F2[5] * ( V3[2] - V3[5] ) ) );
    const cxsmpl<FT_FFV3_0> TMP3 = ( F1[4] * ( F2[2] * ( V3[2] - V3[5] ) - F2[3] * ( V3[3] + cI * V3[4] ) ) + F1[5] * ( F2[2] * ( -V3[3] + cI * V3[4] ) + F2[3] * ( V3[2] + V3[5] ) ) );
    ( *vertex ) =static_cast<cxsmpl<fptype>>( static_cast<FT_FFV3_0>(Ccoeff) * COUP * ( -cI * TMP2 + ( two * cI ) * TMP3 ));
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V3[6]' from the input wavefunctions F1[6], F2[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ void
  FFV3_3( const fptype allF1[],
          const fptype allF2[],
          const fptype allCOUP[],
          const fptype Ccoeff,
          const fptype M3,
          const fptype W3,
          fptype allV3[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const cxtype_sv* F1_ = W_ACCESS::kernelAccessConst( allF1 );
    const cxtype_sv* F2_ = W_ACCESS::kernelAccessConst( allF2 );
    const cxtype_sv COUP_ = C_ACCESS::kernelAccessConst( allCOUP );
    cxtype_sv* V3 = W_ACCESS::kernelAccess( allV3 );
	 	 cxsmpl<FT_FFV3_3> F1[6];
	 	 cxsmpl<FT_FFV3_3> F2[6];
	 	 const cxsmpl<FT_FFV3_3> COUP = static_cast<cxsmpl<FT_FFV3_3>>(COUP_);
		for(int i = 0; i < 6; ++i)
		{
	 	 F1[i] = static_cast<cxsmpl<FT_FFV3_3>>(F1_[i]);
	 	 F2[i] = static_cast<cxsmpl<FT_FFV3_3>>(F2_[i]);
		}
    const cxsmpl<FT_FFV3_3> cI = cxmake<FT_FFV3_3>( 0., 1. );
    const FT_FFV3_3 OM3 =  (FT_FFV3_3) ( static_cast<FT_FFV3_3>(M3) != 0. ? 1. / ( static_cast<FT_FFV3_3>(M3) * static_cast<FT_FFV3_3>(M3) ) :  (FT_FFV3_3) 0. );
    V3[0] =static_cast<cxsmpl<fptype>>( +F1[0] + F2[0]);
    V3[1] =static_cast<cxsmpl<fptype>>( +F1[1] + F2[1]);
    const FT_FFV3_3 P3[4] = { static_cast<FT_FFV3_3>(-cxreal( V3[0] )), static_cast<FT_FFV3_3>(-cxreal( V3[1] )), static_cast<FT_FFV3_3>(-cximag( V3[1] )), static_cast<FT_FFV3_3>(-cximag( V3[0] )) };
    const FT_FFV3_3 two( 2. );
    const FT_FFV3_3 half( 1. / 2. );
    const cxsmpl<FT_FFV3_3> TMP1 = ( F1[2] * ( F2[4] * ( P3[0] + P3[3] ) + F2[5] * ( P3[1] + cI * P3[2] ) ) + F1[3] * ( F2[4] * ( P3[1] - cI * P3[2] ) + F2[5] * ( P3[0] - P3[3] ) ) );
    const cxsmpl<FT_FFV3_3> TMP4 = ( F1[4] * ( F2[2] * ( P3[0] - P3[3] ) - F2[3] * ( P3[1] + cI * P3[2] ) ) + F1[5] * ( F2[2] * ( -P3[1] + cI * P3[2] ) + F2[3] * ( P3[0] + P3[3] ) ) );
    const cxsmpl<FT_FFV3_3> denom = static_cast<FT_FFV3_3>(Ccoeff) * COUP / ( ( P3[0] * P3[0] ) - ( P3[1] * P3[1] ) - ( P3[2] * P3[2] ) - ( P3[3] * P3[3] ) - static_cast<FT_FFV3_3>(M3) * ( static_cast<FT_FFV3_3>(M3) - cI * static_cast<FT_FFV3_3>(W3) ) );
    V3[2] =static_cast<cxsmpl<fptype>>( denom * ( two * cI ) * ( OM3 * half * P3[0] * ( TMP1 - two * TMP4 ) + ( -half * ( F2[4] * F1[2] + F2[5] * F1[3] ) + F2[2] * F1[4] + F2[3] * F1[5] ) ));
    V3[3] =static_cast<cxsmpl<fptype>>( denom * ( two * cI ) * ( OM3 * half * P3[1] * ( TMP1 - two * TMP4 ) + ( +half * ( F2[4] * F1[3] + F2[5] * F1[2] ) + F2[2] * F1[5] + F2[3] * F1[4] ) ));
    V3[4] =static_cast<cxsmpl<fptype>>( denom * ( -two * cI ) * ( OM3 * half * P3[2] * ( -TMP1 + two * TMP4 ) + ( half * cI * ( F2[4] * F1[3] ) - half * cI * ( F2[5] * F1[2] ) + cI * ( F2[2] * F1[5] ) - cI * ( F2[3] * F1[4] ) ) ));
    V3[5] =static_cast<cxsmpl<fptype>>( denom * ( -two * cI ) * ( OM3 * half * P3[3] * ( -TMP1 + two * TMP4 ) + ( -half * ( F2[4] * F1[2] ) + half * ( F2[5] * F1[3] ) - F2[2] * F1[4] + F2[3] * F1[5] ) ));
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V1[6]' from the input wavefunctions V2[6], V3[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ void
  VVV1P0_1( const fptype allV2[],
            const fptype allV3[],
            const fptype allCOUP[],
            const fptype Ccoeff,
            const fptype M1,
            const fptype W1,
            fptype allV1[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const cxtype_sv* V2_ = W_ACCESS::kernelAccessConst( allV2 );
    const cxtype_sv* V3_ = W_ACCESS::kernelAccessConst( allV3 );
    const cxtype_sv COUP_ = C_ACCESS::kernelAccessConst( allCOUP );
    cxtype_sv* V1 = W_ACCESS::kernelAccess( allV1 );
	 	 cxsmpl<FT_VVV1P0_1> V2[6];
	 	 cxsmpl<FT_VVV1P0_1> V3[6];
	 	 const cxsmpl<FT_VVV1P0_1> COUP = static_cast<cxsmpl<FT_VVV1P0_1>>(COUP_);
		for(int i = 0; i < 6; ++i)
		{
	 	 V2[i] = static_cast<cxsmpl<FT_VVV1P0_1>>(V2_[i]);
	 	 V3[i] = static_cast<cxsmpl<FT_VVV1P0_1>>(V3_[i]);
		}
    const cxsmpl<FT_VVV1P0_1> cI = cxmake<FT_VVV1P0_1>( 0., 1. );
    const FT_VVV1P0_1 P2[4] = { static_cast<FT_VVV1P0_1>(+cxreal( V2[0] )), static_cast<FT_VVV1P0_1>(+cxreal( V2[1] )), static_cast<FT_VVV1P0_1>(+cximag( V2[1] )), static_cast<FT_VVV1P0_1>(+cximag( V2[0] )) };
    const FT_VVV1P0_1 P3[4] = { static_cast<FT_VVV1P0_1>(+cxreal( V3[0] )), static_cast<FT_VVV1P0_1>(+cxreal( V3[1] )), static_cast<FT_VVV1P0_1>(+cximag( V3[1] )), static_cast<FT_VVV1P0_1>(+cximag( V3[0] )) };
    V1[0] =static_cast<cxsmpl<fptype>>( +V2[0] + V3[0]);
    V1[1] =static_cast<cxsmpl<fptype>>( +V2[1] + V3[1]);
    const FT_VVV1P0_1 P1[4] = { static_cast<FT_VVV1P0_1>(-cxreal( V1[0] )), static_cast<FT_VVV1P0_1>(-cxreal( V1[1] )), static_cast<FT_VVV1P0_1>(-cximag( V1[1] )), static_cast<FT_VVV1P0_1>(-cximag( V1[0] )) };
    const cxsmpl<FT_VVV1P0_1> TMP10 = ( P3[0] * V2[2] - P3[1] * V2[3] - P3[2] * V2[4] - P3[3] * V2[5] );
    const cxsmpl<FT_VVV1P0_1> TMP11 = ( V3[2] * V2[2] - V3[3] * V2[3] - V3[4] * V2[4] - V3[5] * V2[5] );
    const cxsmpl<FT_VVV1P0_1> TMP6 = ( P1[0] * V2[2] - P1[1] * V2[3] - P1[2] * V2[4] - P1[3] * V2[5] );
    const cxsmpl<FT_VVV1P0_1> TMP8 = ( V3[2] * P1[0] - V3[3] * P1[1] - V3[4] * P1[2] - V3[5] * P1[3] );
    const cxsmpl<FT_VVV1P0_1> TMP9 = ( V3[2] * P2[0] - V3[3] * P2[1] - V3[4] * P2[2] - V3[5] * P2[3] );
    const cxsmpl<FT_VVV1P0_1> denom = static_cast<FT_VVV1P0_1>(Ccoeff) * COUP / ( ( P1[0] * P1[0] ) - ( P1[1] * P1[1] ) - ( P1[2] * P1[2] ) - ( P1[3] * P1[3] ) - static_cast<FT_VVV1P0_1>(M1) * ( static_cast<FT_VVV1P0_1>(M1) - cI * static_cast<FT_VVV1P0_1>(W1) ) );
    V1[2] =static_cast<cxsmpl<fptype>>( denom * ( TMP11 * ( -cI * P2[0] + cI * P3[0] ) + ( V2[2] * ( -cI * TMP8 + cI * TMP9 ) + V3[2] * ( +cI * TMP6 - cI * TMP10 ) ) ));
    V1[3] =static_cast<cxsmpl<fptype>>( denom * ( TMP11 * ( -cI * P2[1] + cI * P3[1] ) + ( V2[3] * ( -cI * TMP8 + cI * TMP9 ) + V3[3] * ( +cI * TMP6 - cI * TMP10 ) ) ));
    V1[4] =static_cast<cxsmpl<fptype>>( denom * ( TMP11 * ( -cI * P2[2] + cI * P3[2] ) + ( V2[4] * ( -cI * TMP8 + cI * TMP9 ) + V3[4] * ( +cI * TMP6 - cI * TMP10 ) ) ));
    V1[5] =static_cast<cxsmpl<fptype>>( denom * ( TMP11 * ( -cI * P2[3] + cI * P3[3] ) + ( V2[5] * ( -cI * TMP8 + cI * TMP9 ) + V3[5] * ( +cI * TMP6 - cI * TMP10 ) ) ));
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions F1[6], F2[6], V3[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS>
  __device__ void
  FFV2_5_0( const fptype allF1[],
            const fptype allF2[],
            const fptype allV3[],
            const fptype allCOUP1[],
            const fptype Ccoeff1,
            const fptype allCOUP2[],
            const fptype Ccoeff2,
            fptype allvertexes[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const cxtype_sv* F1_ = W_ACCESS::kernelAccessConst( allF1 );
    const cxtype_sv* F2_ = W_ACCESS::kernelAccessConst( allF2 );
    const cxtype_sv* V3_ = W_ACCESS::kernelAccessConst( allV3 );
    const cxtype_sv COUP1_ = C_ACCESS::kernelAccessConst( allCOUP1 );
    const cxtype_sv COUP2_ = C_ACCESS::kernelAccessConst( allCOUP2 );
    cxtype_sv* vertex = A_ACCESS::kernelAccess( allvertexes );
	 	 cxsmpl<FT_FFV2_5_0> F1[6];
	 	 cxsmpl<FT_FFV2_5_0> F2[6];
	 	 cxsmpl<FT_FFV2_5_0> V3[6];
	 	 const cxsmpl<FT_FFV2_5_0> COUP1 = static_cast<cxsmpl<FT_FFV2_5_0>>(COUP1_);
	 	 const cxsmpl<FT_FFV2_5_0> COUP2 = static_cast<cxsmpl<FT_FFV2_5_0>>(COUP2_);
		for(int i = 0; i < 6; ++i)
		{
	 	 F1[i] = static_cast<cxsmpl<FT_FFV2_5_0>>(F1_[i]);
	 	 F2[i] = static_cast<cxsmpl<FT_FFV2_5_0>>(F2_[i]);
	 	 V3[i] = static_cast<cxsmpl<FT_FFV2_5_0>>(V3_[i]);
		}
    const cxsmpl<FT_FFV2_5_0> cI = cxmake<FT_FFV2_5_0>( 0., 1. );
    const FT_FFV2_5_0 one( 1. );
    const cxsmpl<FT_FFV2_5_0> TMP2 = ( F1[2] * ( F2[4] * ( V3[2] + V3[5] ) + F2[5] * ( V3[3] + cI * V3[4] ) ) + F1[3] * ( F2[4] * ( V3[3] - cI * V3[4] ) + F2[5] * ( V3[2] - V3[5] ) ) );
    const cxsmpl<FT_FFV2_5_0> TMP3 = ( F1[4] * ( F2[2] * ( V3[2] - V3[5] ) - F2[3] * ( V3[3] + cI * V3[4] ) ) + F1[5] * ( F2[2] * ( -V3[3] + cI * V3[4] ) + F2[3] * ( V3[2] + V3[5] ) ) );
    ( *vertex ) =static_cast<cxsmpl<fptype>>( ( -one ) * ( static_cast<FT_FFV2_5_0>(Ccoeff2) * COUP2 * ( +cI * TMP2 + ( 4. * cI ) * TMP3 ) + cI * ( TMP2 * static_cast<FT_FFV2_5_0>(Ccoeff1) * COUP1 ) ));
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V3[6]' from the input wavefunctions F1[6], F2[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ void
  FFV2_5_3( const fptype allF1[],
            const fptype allF2[],
            const fptype allCOUP1[],
            const fptype Ccoeff1,
            const fptype allCOUP2[],
            const fptype Ccoeff2,
            const fptype M3,
            const fptype W3,
            fptype allV3[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const cxtype_sv* F1_ = W_ACCESS::kernelAccessConst( allF1 );
    const cxtype_sv* F2_ = W_ACCESS::kernelAccessConst( allF2 );
    const cxtype_sv COUP1_ = C_ACCESS::kernelAccessConst( allCOUP1 );
    const cxtype_sv COUP2_ = C_ACCESS::kernelAccessConst( allCOUP2 );
    cxtype_sv* V3 = W_ACCESS::kernelAccess( allV3 );
	 	 cxsmpl<FT_FFV2_5_3> F1[6];
	 	 cxsmpl<FT_FFV2_5_3> F2[6];
	 	 const cxsmpl<FT_FFV2_5_3> COUP1 = static_cast<cxsmpl<FT_FFV2_5_3>>(COUP1_);
	 	 const cxsmpl<FT_FFV2_5_3> COUP2 = static_cast<cxsmpl<FT_FFV2_5_3>>(COUP2_);
		for(int i = 0; i < 6; ++i)
		{
	 	 F1[i] = static_cast<cxsmpl<FT_FFV2_5_3>>(F1_[i]);
	 	 F2[i] = static_cast<cxsmpl<FT_FFV2_5_3>>(F2_[i]);
		}
    const cxsmpl<FT_FFV2_5_3> cI = cxmake<FT_FFV2_5_3>( 0., 1. );
    const FT_FFV2_5_3 OM3 =  (FT_FFV2_5_3) ( static_cast<FT_FFV2_5_3>(M3) != 0. ? 1. / ( static_cast<FT_FFV2_5_3>(M3) * static_cast<FT_FFV2_5_3>(M3) ) :  (FT_FFV2_5_3) 0. );
    V3[0] =static_cast<cxsmpl<fptype>>( +F1[0] + F2[0]);
    V3[1] =static_cast<cxsmpl<fptype>>( +F1[1] + F2[1]);
    const FT_FFV2_5_3 P3[4] = { static_cast<FT_FFV2_5_3>(-cxreal( V3[0] )), static_cast<FT_FFV2_5_3>(-cxreal( V3[1] )), static_cast<FT_FFV2_5_3>(-cximag( V3[1] )), static_cast<FT_FFV2_5_3>(-cximag( V3[0] )) };
    const FT_FFV2_5_3 one( 1. );
    const FT_FFV2_5_3 quarter( 1. / 4. );
    const cxsmpl<FT_FFV2_5_3> TMP1 = ( F1[2] * ( F2[4] * ( P3[0] + P3[3] ) + F2[5] * ( P3[1] + cI * P3[2] ) ) + F1[3] * ( F2[4] * ( P3[1] - cI * P3[2] ) + F2[5] * ( P3[0] - P3[3] ) ) );
    const cxsmpl<FT_FFV2_5_3> TMP4 = ( F1[4] * ( F2[2] * ( P3[0] - P3[3] ) - F2[3] * ( P3[1] + cI * P3[2] ) ) + F1[5] * ( F2[2] * ( -P3[1] + cI * P3[2] ) + F2[3] * ( P3[0] + P3[3] ) ) );
    const cxsmpl<FT_FFV2_5_3> denom = one / ( ( P3[0] * P3[0] ) - ( P3[1] * P3[1] ) - ( P3[2] * P3[2] ) - ( P3[3] * P3[3] ) - static_cast<FT_FFV2_5_3>(M3) * ( static_cast<FT_FFV2_5_3>(M3) - cI * static_cast<FT_FFV2_5_3>(W3) ) );
    V3[2] =static_cast<cxsmpl<fptype>>( denom * ( -4. * cI ) * ( static_cast<FT_FFV2_5_3>(Ccoeff2) * COUP2 * ( OM3 * -quarter * P3[0] * ( TMP1 + 4. * TMP4 ) + ( +quarter * ( F2[4] * F1[2] + F2[5] * F1[3] ) + F2[2] * F1[4] + F2[3] * F1[5] ) ) + quarter * ( static_cast<FT_FFV2_5_3>(Ccoeff1) * COUP1 * ( F2[4] * F1[2] + F2[5] * F1[3] - P3[0] * OM3 * TMP1 ) ) ));
    V3[3] =static_cast<cxsmpl<fptype>>( denom * ( -4. * cI ) * ( static_cast<FT_FFV2_5_3>(Ccoeff2) * COUP2 * ( OM3 * -quarter * P3[1] * ( TMP1 + 4. * TMP4 ) + ( -quarter * ( F2[4] * F1[3] + F2[5] * F1[2] ) + F2[2] * F1[5] + F2[3] * F1[4] ) ) - quarter * ( static_cast<FT_FFV2_5_3>(Ccoeff1) * COUP1 * ( F2[4] * F1[3] + F2[5] * F1[2] + P3[1] * OM3 * TMP1 ) ) ));
    V3[4] =static_cast<cxsmpl<fptype>>( denom * cI * ( static_cast<FT_FFV2_5_3>(Ccoeff2) * COUP2 * ( OM3 * P3[2] * ( TMP1 + 4. * TMP4 ) + ( -cI * ( F2[4] * F1[3] ) + cI * ( F2[5] * F1[2] ) + ( 4. * cI ) * ( F2[2] * F1[5] ) + ( -4. * cI ) * ( F2[3] * F1[4] ) ) ) + static_cast<FT_FFV2_5_3>(Ccoeff1) * COUP1 * ( -cI * ( F2[4] * F1[3] ) + cI * ( F2[5] * F1[2] ) + P3[2] * OM3 * TMP1 ) ));
    V3[5] =static_cast<cxsmpl<fptype>>( denom * ( 4. * cI ) * ( static_cast<FT_FFV2_5_3>(Ccoeff2) * COUP2 * ( OM3 * quarter * P3[3] * ( TMP1 + 4. * TMP4 ) + ( +quarter * ( F2[4] * F1[2] ) - quarter * ( F2[5] * F1[3] ) - F2[2] * F1[4] + F2[3] * F1[5] ) ) + quarter * ( static_cast<FT_FFV2_5_3>(Ccoeff1) * COUP1 * ( F2[4] * F1[2] + P3[3] * OM3 * TMP1 - F2[5] * F1[3] ) ) ));
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output amplitude 'vertex' from the input wavefunctions F1[6], F2[6], V3[6]
  template<class W_ACCESS, class A_ACCESS, class C_ACCESS>
  __device__ void
  FFV2_3_0( const fptype allF1[],
            const fptype allF2[],
            const fptype allV3[],
            const fptype allCOUP1[],
            const fptype Ccoeff1,
            const fptype allCOUP2[],
            const fptype Ccoeff2,
            fptype allvertexes[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const cxtype_sv* F1_ = W_ACCESS::kernelAccessConst( allF1 );
    const cxtype_sv* F2_ = W_ACCESS::kernelAccessConst( allF2 );
    const cxtype_sv* V3_ = W_ACCESS::kernelAccessConst( allV3 );
    const cxtype_sv COUP1_ = C_ACCESS::kernelAccessConst( allCOUP1 );
    const cxtype_sv COUP2_ = C_ACCESS::kernelAccessConst( allCOUP2 );
    cxtype_sv* vertex = A_ACCESS::kernelAccess( allvertexes );
	 	 cxsmpl<FT_FFV2_3_0> F1[6];
	 	 cxsmpl<FT_FFV2_3_0> F2[6];
	 	 cxsmpl<FT_FFV2_3_0> V3[6];
	 	 const cxsmpl<FT_FFV2_3_0> COUP1 = static_cast<cxsmpl<FT_FFV2_3_0>>(COUP1_);
	 	 const cxsmpl<FT_FFV2_3_0> COUP2 = static_cast<cxsmpl<FT_FFV2_3_0>>(COUP2_);
		for(int i = 0; i < 6; ++i)
		{
	 	 F1[i] = static_cast<cxsmpl<FT_FFV2_3_0>>(F1_[i]);
	 	 F2[i] = static_cast<cxsmpl<FT_FFV2_3_0>>(F2_[i]);
	 	 V3[i] = static_cast<cxsmpl<FT_FFV2_3_0>>(V3_[i]);
		}
    const cxsmpl<FT_FFV2_3_0> cI = cxmake<FT_FFV2_3_0>( 0., 1. );
    const FT_FFV2_3_0 one( 1. );
    const FT_FFV2_3_0 two( 2. );
    const cxsmpl<FT_FFV2_3_0> TMP2 = ( F1[2] * ( F2[4] * ( V3[2] + V3[5] ) + F2[5] * ( V3[3] + cI * V3[4] ) ) + F1[3] * ( F2[4] * ( V3[3] - cI * V3[4] ) + F2[5] * ( V3[2] - V3[5] ) ) );
    const cxsmpl<FT_FFV2_3_0> TMP3 = ( F1[4] * ( F2[2] * ( V3[2] - V3[5] ) - F2[3] * ( V3[3] + cI * V3[4] ) ) + F1[5] * ( F2[2] * ( -V3[3] + cI * V3[4] ) + F2[3] * ( V3[2] + V3[5] ) ) );
    ( *vertex ) =static_cast<cxsmpl<fptype>>( ( -one ) * ( static_cast<FT_FFV2_3_0>(Ccoeff2) * COUP2 * ( +cI * TMP2 + ( -two * cI ) * TMP3 ) + cI * ( TMP2 * static_cast<FT_FFV2_3_0>(Ccoeff1) * COUP1 ) ));
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  // Compute the output wavefunction 'V3[6]' from the input wavefunctions F1[6], F2[6]
  template<class W_ACCESS, class C_ACCESS>
  __device__ void
  FFV2_3_3( const fptype allF1[],
            const fptype allF2[],
            const fptype allCOUP1[],
            const fptype Ccoeff1,
            const fptype allCOUP2[],
            const fptype Ccoeff2,
            const fptype M3,
            const fptype W3,
            fptype allV3[] )
  {
    mgDebug( 0, __FUNCTION__ );
    const cxtype_sv* F1_ = W_ACCESS::kernelAccessConst( allF1 );
    const cxtype_sv* F2_ = W_ACCESS::kernelAccessConst( allF2 );
    const cxtype_sv COUP1_ = C_ACCESS::kernelAccessConst( allCOUP1 );
    const cxtype_sv COUP2_ = C_ACCESS::kernelAccessConst( allCOUP2 );
    cxtype_sv* V3 = W_ACCESS::kernelAccess( allV3 );
	 	 cxsmpl<FT_FFV2_3_3> F1[6];
	 	 cxsmpl<FT_FFV2_3_3> F2[6];
	 	 const cxsmpl<FT_FFV2_3_3> COUP1 = static_cast<cxsmpl<FT_FFV2_3_3>>(COUP1_);
	 	 const cxsmpl<FT_FFV2_3_3> COUP2 = static_cast<cxsmpl<FT_FFV2_3_3>>(COUP2_);
		for(int i = 0; i < 6; ++i)
		{
	 	 F1[i] = static_cast<cxsmpl<FT_FFV2_3_3>>(F1_[i]);
	 	 F2[i] = static_cast<cxsmpl<FT_FFV2_3_3>>(F2_[i]);
		}
    const cxsmpl<FT_FFV2_3_3> cI = cxmake<FT_FFV2_3_3>( 0., 1. );
    const FT_FFV2_3_3 OM3 =  (FT_FFV2_3_3) ( static_cast<FT_FFV2_3_3>(M3) != 0. ? 1. / ( static_cast<FT_FFV2_3_3>(M3) * static_cast<FT_FFV2_3_3>(M3) ) :  (FT_FFV2_3_3) 0. );
    V3[0] =static_cast<cxsmpl<fptype>>( +F1[0] + F2[0]);
    V3[1] =static_cast<cxsmpl<fptype>>( +F1[1] + F2[1]);
    const FT_FFV2_3_3 P3[4] = { static_cast<FT_FFV2_3_3>(-cxreal( V3[0] )), static_cast<FT_FFV2_3_3>(-cxreal( V3[1] )), static_cast<FT_FFV2_3_3>(-cximag( V3[1] )), static_cast<FT_FFV2_3_3>(-cximag( V3[0] )) };
    const FT_FFV2_3_3 one( 1. );
    const FT_FFV2_3_3 two( 2. );
    const FT_FFV2_3_3 half( 1. / 2. );
    const cxsmpl<FT_FFV2_3_3> TMP1 = ( F1[2] * ( F2[4] * ( P3[0] + P3[3] ) + F2[5] * ( P3[1] + cI * P3[2] ) ) + F1[3] * ( F2[4] * ( P3[1] - cI * P3[2] ) + F2[5] * ( P3[0] - P3[3] ) ) );
    const cxsmpl<FT_FFV2_3_3> TMP4 = ( F1[4] * ( F2[2] * ( P3[0] - P3[3] ) - F2[3] * ( P3[1] + cI * P3[2] ) ) + F1[5] * ( F2[2] * ( -P3[1] + cI * P3[2] ) + F2[3] * ( P3[0] + P3[3] ) ) );
    const cxsmpl<FT_FFV2_3_3> denom = one / ( ( P3[0] * P3[0] ) - ( P3[1] * P3[1] ) - ( P3[2] * P3[2] ) - ( P3[3] * P3[3] ) - static_cast<FT_FFV2_3_3>(M3) * ( static_cast<FT_FFV2_3_3>(M3) - cI * static_cast<FT_FFV2_3_3>(W3) ) );
    V3[2] =static_cast<cxsmpl<fptype>>( denom * ( two * cI ) * ( static_cast<FT_FFV2_3_3>(Ccoeff2) * COUP2 * ( OM3 * half * P3[0] * ( TMP1 - two * TMP4 ) + ( -half * ( F2[4] * F1[2] + F2[5] * F1[3] ) + F2[2] * F1[4] + F2[3] * F1[5] ) ) - half * ( static_cast<FT_FFV2_3_3>(Ccoeff1) * COUP1 * ( F2[4] * F1[2] + F2[5] * F1[3] - P3[0] * OM3 * TMP1 ) ) ));
    V3[3] =static_cast<cxsmpl<fptype>>( denom * ( two * cI ) * ( static_cast<FT_FFV2_3_3>(Ccoeff2) * COUP2 * ( OM3 * half * P3[1] * ( TMP1 - two * TMP4 ) + ( +half * ( F2[4] * F1[3] + F2[5] * F1[2] ) + F2[2] * F1[5] + F2[3] * F1[4] ) ) + half * ( static_cast<FT_FFV2_3_3>(Ccoeff1) * COUP1 * ( F2[4] * F1[3] + F2[5] * F1[2] + P3[1] * OM3 * TMP1 ) ) ));
    V3[4] =static_cast<cxsmpl<fptype>>( denom * ( -cI ) * ( static_cast<FT_FFV2_3_3>(Ccoeff2) * COUP2 * ( OM3 * P3[2] * ( -TMP1 + two * TMP4 ) + ( +cI * ( F2[4] * F1[3] ) - cI * ( F2[5] * F1[2] ) + ( two * cI ) * ( F2[2] * F1[5] ) + ( -two * cI ) * ( F2[3] * F1[4] ) ) ) - static_cast<FT_FFV2_3_3>(Ccoeff1) * COUP1 * ( -cI * ( F2[4] * F1[3] ) + cI * ( F2[5] * F1[2] ) + P3[2] * OM3 * TMP1 ) ));
    V3[5] =static_cast<cxsmpl<fptype>>( denom * ( -two * cI ) * ( static_cast<FT_FFV2_3_3>(Ccoeff2) * COUP2 * ( OM3 * half * P3[3] * ( -TMP1 + two * TMP4 ) + ( -half * ( F2[4] * F1[2] ) + half * ( F2[5] * F1[3] ) - F2[2] * F1[4] + F2[3] * F1[5] ) ) - half * ( static_cast<FT_FFV2_3_3>(Ccoeff1) * COUP1 * ( F2[4] * F1[2] + P3[3] * OM3 * TMP1 - F2[5] * F1[3] ) ) ));
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

} // end namespace

#endif // HelAmps_sm_H
