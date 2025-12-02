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
typedef float_st fptype;
typedef double_st fptype2;
typedef double_st fptype3;
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

#ifdef __CADNA
/*inline fptype3
fpsqrt(const fptype3& f)
{
    return sqrt(f);
}

inline const fptype3&
fpmax(const fptype3& a, const fptype3& b)
{
    return max(a, b);
}

inline const fptype3&
fpmin(const fptype3& a, const fptype3& b)
{
    return min(a, b);
}*/
#endif

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
