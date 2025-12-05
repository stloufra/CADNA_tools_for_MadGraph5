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

#if defined __CADNA
#include "promiseTypes-Fitted.h"
typedef float_st fptypemomenta;
#elif defined ( __PRO__)
#include "promiseTypes.h"
#else
typedef float fptype;
typedef float fptype2;
typedef double fptypemomenta;
typedef float FT_FFV1P0_3;
typedef float FT_FFV1_0;
typedef float FT_FFV1_1;
typedef float FT_FFV1_2;
typedef float FT_VVV1P0_1;
typedef float FT_VVV1_0;
typedef float FT_VVVV1P0_1;
typedef float FT_VVVV1_0;
typedef float FT_VVVV3P0_1;
typedef float FT_VVVV3_0;
typedef float FT_VVVV4P0_1;
typedef float FT_VVVV4_0;
typedef float FT_imzxxx;
typedef float FT_ipzxxx;
typedef float FT_ixxxxx;
typedef float FT_ixzxxx;
typedef float FT_omzxxx;
typedef float FT_opzxxx;
typedef float FT_oxxxxx;
typedef float FT_oxzxxx;
typedef float FT_sxxxxx;
typedef float FT_vxxxxx;
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

template <typename FP>
inline FP
fpsqrt(const FP& f)
{
    return sqrt(f);
}

inline fptype
fpternary(const bool& mask, const fptype& a, const fptype& b)
{
    return (mask ? a : b);
}

#ifdef __CADNA

template <typename FP, typename FP2,
std::enable_if_t<std::is_same_v<FP, double_st> || std::is_same_v<FP2, double_st>, int> = 0>
auto
fpternary(const bool& mask, const  FP& a, const  FP2& b)
{
    if constexpr ( std::is_same_v<FP, double_st>)
        return (mask ? a : static_cast<double_st>(b));
    else if constexpr (std::is_same_v<FP2, double_st>)
        return (mask ? static_cast<double_st>(a) : b);
    //else
    //    return (mask ? static_cast<float_st>(a) : static_cast<float_st>(b));
}
#endif

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

#ifdef __CADNA
template <typename FP, typename FP2,
std::enable_if_t<std::is_same_v<FP, double_st> || std::is_same_v<FP2, double_st>, int> = 0>
inline const double_st
fpmax(const  FP& a, const  FP2& b)
{
    if constexpr (std::is_same_v<FP,double_st>)
        return max(a, static_cast<FP>(b));
    else
        return max(static_cast<FP2>(a), b);
}

template <typename FP, typename FP2,
std::enable_if_t<std::is_same_v<FP, double_st> || std::is_same_v<FP2, double_st>, int> = 0>
inline const double_st
fpmin(const  FP& a, const  FP2& b)
{
    if constexpr (std::is_same_v<FP,double_st>)
        return min(a, static_cast<FP>(b));
    else
        return min(static_cast<FP2>(a), b);
}

template <typename FP, typename FP2,
std::enable_if_t<std::is_same_v<FP, double_st> || std::is_same_v<FP2, double_st>, int> = 0>
inline const double_st
fpsqrt(const  FP& a, const  FP2& b)
{
    if constexpr (std::is_same_v<FP,double_st>)
        return sqrt(a, static_cast<FP>(b));
    else
        return sqrt(static_cast<FP2>(a), b);
}
#endif

#endif //CPPPROCESS_STANDALONE_TYPETRAITS_H
