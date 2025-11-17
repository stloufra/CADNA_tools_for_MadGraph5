//
// Created by Frantisek Stloukal on 14.11.2025.
//

#ifndef CPPPROCESS_STANDALONE_COMPLEX_H
#define CPPPROCESS_STANDALONE_COMPLEX_H
#include <complex>
#include "typeTraits.h"
#include "cadna.h"
#include "Complex.h"

// The number of floating point types in a complex type (real, imaginary)
namespace mgOnGpu
{
    constexpr int nx2 = 2;
    constexpr int cppAlign = 64;
}

// --- Type definition (simple complex type derived from cxtype_v)
template <typename FP>
class cxsmpl
{
public:
    constexpr cxsmpl() : m_real(0), m_imag(0)
    {
    }

    cxsmpl(const cxsmpl&) = default;
    cxsmpl(cxsmpl&&) = default;

    constexpr cxsmpl(const FP& r, const FP& i = 0) : m_real(r), m_imag(i)
    {
    }

    constexpr cxsmpl(const std::complex<FP>& c) : m_real(c.real()), m_imag(c.imag())
    {
    }

    cxsmpl& operator=(const cxsmpl&) = default;
    cxsmpl& operator=(cxsmpl&&) = default;

    constexpr cxsmpl& operator+=(const cxsmpl& c)
    {
        m_real += c.real();
        m_imag += c.imag();
        return *this;
    }

    constexpr cxsmpl& operator-=(const cxsmpl& c)
    {
        m_real -= c.real();
        m_imag -= c.imag();
        return *this;
    }

    constexpr const FP& real() const { return m_real; }
    constexpr const FP& imag() const { return m_imag; }

    template <typename FP2>
    constexpr operator cxsmpl<FP2>() const { return cxsmpl<FP2>(m_real, m_imag); }

private:
    FP m_real, m_imag; // RI
};

template <typename FP>
constexpr
inline cxsmpl<FP>
conj(const cxsmpl<FP>& c)
{
    return cxsmpl<FP>(c.real(), -c.imag());
}

template <typename FP>
inline std::ostream&
operator<<(std::ostream& out, const cxsmpl<FP>& c)
{
    out << "(" << c.real() << ", " << c.imag() << ")"; // add a space after the comma
    return out;
}

// Operators for cxsmpl
template <typename FP>
inline
constexpr cxsmpl<FP>
operator+(const cxsmpl<FP> a)
{
    return a;
}

template <typename FP>
inline
constexpr cxsmpl<FP>
operator-(const cxsmpl<FP>& a)
{
    return cxsmpl<FP>(-a.real(), -a.imag());
}

template <typename FP>
inline
constexpr cxsmpl<FP>
operator+(const cxsmpl<FP>& a, const cxsmpl<FP>& b)
{
    return cxsmpl<FP>(a.real() + b.real(), a.imag() + b.imag());
}

template <typename FP>
inline
constexpr cxsmpl<FP>
operator+(const FP& a, const cxsmpl<FP>& b)
{
    return cxsmpl<FP>(a, 0) + b;
}

template <typename FP>
inline
constexpr cxsmpl<FP>
operator-(const cxsmpl<FP>& a, const cxsmpl<FP>& b)
{
    return cxsmpl<FP>(a.real() - b.real(), a.imag() - b.imag());
}

template <typename FP>
inline
constexpr cxsmpl<FP>
operator-(const FP& a, const cxsmpl<FP>& b)
{
    return cxsmpl<FP>(a, 0) - b;
}

template <typename FP>
inline
constexpr cxsmpl<FP>
operator*(const cxsmpl<FP>& a, const cxsmpl<FP>& b)
{
    return cxsmpl<FP>(a.real() * b.real() - a.imag() * b.imag(), a.imag() * b.real() + a.real() * b.imag());
}

template <typename FP>
inline
constexpr cxsmpl<FP>
operator*(const FP& a, const cxsmpl<FP>& b)
{
    return cxsmpl<FP>(a, 0) * b;
}

inline
constexpr cxsmpl<float>
operator*(const double& a, const cxsmpl<float>& b)
{
    return cxsmpl<float>(a, 0) * b;
}

inline
constexpr cxsmpl<float>
operator*(const cxsmpl<float>& a, const double& b)
{
    return a * cxsmpl<float>(b, 0);
}

template <typename FP>
inline
constexpr cxsmpl<FP>
operator/(const cxsmpl<FP>& a, const cxsmpl<FP>& b)
{
    FP bnorm = b.real() * b.real() + b.imag() * b.imag();
    return cxsmpl<FP>((a.real() * b.real() + a.imag() * b.imag()) / bnorm,
                      (a.imag() * b.real() - a.real() * b.imag()) / bnorm);
}

template <typename FP>
inline
constexpr cxsmpl<FP>
operator/(const FP& a, const cxsmpl<FP>& b)
{
    return cxsmpl<FP>(a, 0) / b;
}

template <typename FP>
inline
constexpr cxsmpl<FP>
operator+(const cxsmpl<FP>& a, const FP& b)
{
    return a + cxsmpl<FP>(b, 0);
}

template <typename FP>
inline
constexpr cxsmpl<FP>
operator-(const cxsmpl<FP>& a, const FP& b)
{
    return a - cxsmpl<FP>(b, 0);
}

template <typename FP>
inline
constexpr cxsmpl<FP>
operator*(const cxsmpl<FP>& a, const FP& b)
{
    return a * cxsmpl<FP>(b, 0);
}

template <typename FP>
inline
constexpr cxsmpl<FP>
operator/(const cxsmpl<FP>& a, const FP& b)
{
    return a / cxsmpl<FP>(b, 0);
}

//CADNA operator overload
template <typename T>
constexpr bool is_special_fp_v =
    std::is_same_v<T, double_st> || std::is_same_v<T, float_st>;

template <typename FP, typename FP2,
          std::enable_if_t<is_special_fp_v<FP> || is_special_fp_v<FP2>, int> = 0>
inline constexpr auto
operator+(const cxsmpl<FP>& a, const cxsmpl<FP2>& b)
{
    if constexpr (is_special_fp_v<FP>)
    {
        cxsmpl<FP> b_temp = b;
        return cxsmpl<FP>(a.real() + b_temp.real(), a.imag() + b_temp.imag());
    }
    else
    {
        cxsmpl<FP2> a_temp = a;
        return cxsmpl<FP2>(a_temp.real() + b.real(), a_temp.imag() + b.imag());
    }
}

template <typename FP, typename FP2,
          std::enable_if_t<is_special_fp_v<FP> || is_special_fp_v<FP2>, int> = 0>
inline constexpr auto
operator-(const cxsmpl<FP>& a, const cxsmpl<FP2>& b)
{
    if constexpr (is_special_fp_v<FP>)
    {
        cxsmpl<FP> b_temp = b;
        return cxsmpl<FP>(a.real() - b_temp.real(), a.imag() - b_temp.imag());
    }
    else
    {
        cxsmpl<FP2> a_temp = a;
        return cxsmpl<FP2>(a_temp.real() - b.real(), a_temp.imag() - b.imag());
    }
}

template <typename FP, typename FP2,
          std::enable_if_t<is_special_fp_v<FP> || is_special_fp_v<FP2>, int> = 0>
inline constexpr auto
operator*(const cxsmpl<FP>& a, const cxsmpl<FP2>& b)
{
    if constexpr (is_special_fp_v<FP>)
    {
        cxsmpl<FP> b_temp = b;
        return cxsmpl<FP>(a.real() * b_temp.real() - a.imag() * b_temp.imag(),
                          a.imag() * b_temp.real() + a.real() * b_temp.imag());
    }
    else
    {
        cxsmpl<FP2> a_temp = a;
        return cxsmpl<FP2>(a_temp.real() * b.real() - a_temp.imag() * b.imag(),
                           a_temp.imag() * b.real() + a_temp.real() * b.imag());
    }
}

template <typename FP, typename FP2,
          std::enable_if_t<is_special_fp_v<FP> || is_special_fp_v<FP2>, int> = 0>
inline constexpr auto
operator/(const cxsmpl<FP>& a, const cxsmpl<FP2>& b)
{
    if constexpr (is_special_fp_v<FP>)
    {
        cxsmpl<FP> b_temp = b;
        FP bnorm = b_temp.real() * b_temp.real() + b_temp.imag() * b_temp.imag();
        return cxsmpl<FP>((a.real() * b_temp.real() + a.imag() * b_temp.imag()) / bnorm,
                          (a.imag() * b_temp.real() - a.real() * b_temp.imag()) / bnorm);
    }
    else
    {
        cxsmpl<FP2> a_temp = a;
        FP2 bnorm = b.real() * b.real() + b.imag() * b.imag();
        return cxsmpl<FP2>((a_temp.real() * b.real() + a_temp.imag() * b.imag()) / bnorm,
                           (a_temp.imag() * b.real() - a_temp.real() * b.imag()) / bnorm);
    }
}

inline cxtype
  cxmake( const fptype& r, const fptype& i )
{
    return cxtype( r, i ); // cxsmpl constructor
}

inline fptype
cxreal( const cxtype& c )
{
    return c.real(); // cxsmpl::real()
}

inline fptype
cximag( const cxtype& c )
{
    return c.imag(); // cxsmpl::imag()
}

inline cxtype
cxconj( const cxtype& c )
{
    return conj( c ); // conj( cxsmpl )
}

inline cxtype                 // NOT __device__
cxmake( const std::complex<float>& c ) // std::complex to cxsmpl (float-to-float or float-to-double)
{
    return cxmake( c.real(), c.imag() );
}

inline cxtype                  // NOT __device__
cxmake( const std::complex<double>& c ) // std::complex to cxsmpl (double-to-float or double-to-double)
{
    return cxmake( c.real(), c.imag() );
}
class cxtype_ref
{
public:
    cxtype_ref() = delete;
    cxtype_ref( const cxtype_ref& ) = delete;
    cxtype_ref( cxtype_ref&& ) = default; // copy const refs
    cxtype_ref( fptype& r, fptype& i )
      : m_preal( &r ), m_pimag( &i ) {} // copy (create from) const refs
    cxtype_ref& operator=( const cxtype_ref& ) = delete;
    cxtype_ref& operator=( const cxtype& c )
    {
        *m_preal = cxreal( c );
        *m_pimag = cximag( c );
        return *this;
    } // copy (assign) non-const values
    operator cxtype() const { return cxmake( *m_preal, *m_pimag ); }
private:
    fptype* const m_preal; // const pointer to non-const fptype R
    fptype* const m_pimag; // const pointer to non-const fptype I
};

// Printout to stream for user defined types
inline std::ostream&
operator<<( std::ostream& out, const cxtype_ref& c )
{
    out << (cxtype)c;
    return out;
}
#endif //CPPPROCESS_STANDALONE_COMPLEX_H
