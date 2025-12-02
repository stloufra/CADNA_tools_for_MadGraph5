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

template <typename FP>
class cxtype_ref;

const int neppV = 1;

#if defined __CADNA
typedef float_st fptype;
typedef float_st fptype2;
typedef double_st fptype_d;
typedef float_st fptype_f;

typedef double_st fptype_momenta;
#else
typedef float fptype;
typedef float fptype2;
typedef double fptype_d;
typedef float fptype_f;

typedef double fptype_momenta;
#endif

typedef cxsmpl<fptype> cxtype;
typedef cxsmpl<fptype_d> cxtype_d;
typedef cxsmpl<fptype_f> cxtype_f;

typedef bool bool_sv;
typedef fptype fptype_sv;
typedef fptype2 fptype2_sv;
typedef fptype_f fptype_f_sv;
typedef fptype_d fptype_d_sv;

typedef unsigned int uint_sv;
typedef cxtype cxtype_sv;

//template<typename FT>
//typedef cxtype_ref<FT> cxtype_sv_ref;

#include "Complex.h"

inline constexpr bool
ispoweroftwo(int n)
{
    return (n > 0) && !(n & (n - 1));
}

using std::max;
using std::min;
using std::sqrt;

template<typename FP>
inline const FP&
fpmax(const FP& a, const FP& b)
{
    return max(a, b);
}

template<typename FP>
inline const FP&
fpmin(const FP& a, const FP& b)
{
    return min(a, b);
}

template<typename FP>
inline FP
fpsqrt(const FP& f)
{
    return sqrt(f);
}

template<typename FP>
inline FP
fpternary(const bool& mask, const FP& a, const FP& b)
{
    return (mask ? a : b);
}
#ifdef __CADNA

/*template <typename FP, typename FP2,
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
}*/
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

/*#ifdef __CADNA
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
#endif*/

#endif //CPPPROCESS_STANDALONE_TYPETRAITS_H
