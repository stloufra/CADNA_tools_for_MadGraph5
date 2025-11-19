//
// Created by Frantisek Stloukal on 14.11.2025.
//

#ifndef CPPPROCESS_STANDALONE_TYPETRAITS_H
#define CPPPROCESS_STANDALONE_TYPETRAITS_H
#include <cmath>
#include <algorithm>

#ifdef __CADNA
#include "cadna.h"
#endif

#define __host__
#define __device__
#define __global__
#define mgDebug(x,y)
#define SEP79 79
#define mgDebugInitialise(x)
#define mgDebugFinalise(x)


template <typename FP>
class cxsmpl;
class cxtype_ref;

const int neppV = 1;

#ifdef __CADNA
typedef float_st fptype;
typedef float_st fptype2;
#else
typedef double fptype;
typedef double fptype2;
#endif

typedef cxsmpl<fptype> cxtype;

typedef bool bool_sv;
typedef fptype fptype_sv;
typedef fptype2 fptype2_sv;
typedef unsigned int uint_sv;
typedef cxtype cxtype_sv;
typedef cxtype_ref cxtype_sv_ref;

#include "Complex.h"

inline constexpr bool
ispoweroftwo(int n)
{
    return (n > 0) && !(n & (n - 1));
}

using std::max;
using std::min;
using std::sqrt;

inline const fptype&
fpmax(const fptype& a, const fptype& b)
{
    return max(a, b);
}

inline const fptype&
fpmin(const fptype& a, const fptype& b)
{
    return min(a, b);
}

inline fptype
fpsqrt(const fptype& f)
{
    return sqrt(f);
}

inline fptype
fpternary(const bool& mask, const fptype& a, const fptype& b)
{
    return (mask ? a : b);
}

inline cxtype
cxternary(const bool& mask, const cxtype& a, const cxtype& b)
{
    return (mask ? a : b);
}

inline bool
maskand(const bool& mask)
{
    return mask;
}
#endif //CPPPROCESS_STANDALONE_TYPETRAITS_H
