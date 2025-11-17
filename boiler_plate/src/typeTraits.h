//
// Created by Frantisek Stloukal on 14.11.2025.
//

#ifndef CPPPROCESS_STANDALONE_TYPETRAITS_H
#define CPPPROCESS_STANDALONE_TYPETRAITS_H
template <typename FP> class cxsmpl;
class cxtype_ref;

const int neppV = 1;

typedef float fptype;
typedef float fptype2;
typedef cxsmpl<fptype> cxtype;

typedef bool bool_sv;
typedef fptype fptype_sv;
typedef fptype2 fptype2_sv;
typedef unsigned int uint_sv;
typedef cxtype cxtype_sv;
typedef cxtype_ref cxtype_sv_ref;

inline constexpr bool
ispoweroftwo( int n )
{
  return ( n > 0 ) && !( n & ( n - 1 ) );
}
#include "Complex.h"

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
}
#endif //CPPPROCESS_STANDALONE_TYPETRAITS_H