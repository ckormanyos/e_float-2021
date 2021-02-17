
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef E_FLOAT_FUNCTIONS_2004_06_01_HPP_
  #define E_FLOAT_FUNCTIONS_2004_06_01_HPP_

  #include <cmath>
  #include <cstdint>
  #include <deque>
  #include <vector>

  #include <e_float/e_float.h>

  namespace ef
  {
    std::int32_t   max_iteration();
    std::int64_t   tolerance    ();

    e_float      fabs (const e_float& x);
    e_float      floor(const e_float& x);
    e_float      ceil (const e_float& x);
    std::int32_t sgn  (const e_float& x);
    e_float      ldexp(const e_float& v, int e);
    e_float      frexp(const e_float& v, int* expon);
    e_float      fmod (const e_float& v1, const e_float& v2);

    bool isnan(const double x);
    bool isnan(const e_float& x);

    bool isfinite(const double x);
    bool isfinite(const e_float& x);

    bool isinf(const double x);
    bool isinf(const e_float& x);

    bool isneg(const double x);
    bool isneg(const e_float& x);

    e_float abs (const e_float& x);
    e_float real(const e_float& x);
    e_float imag(const e_float&);

    bool ispos(const double x);
    bool ispos(const e_float& x);

    bool isint(const double x);
    bool isint(const e_float& x);

    bool isone(const double x);
    bool isone(const e_float& x);

    bool iszero(const double x);
    bool iszero(const e_float& x);

    e_float integer_part(const e_float& x);
    e_float decimal_part(const e_float& x);

    void to_parts(const e_float& x, double& mantissa, std::int64_t& exponent);

    double to_double(const double& x);
    double to_double(const e_float& x);

    std::int64_t order_of(const double x);
    std::int64_t order_of(const e_float& x);

    std::int64_t to_int64(const double x);
    std::int64_t to_int64(const e_float& x);

    std::int32_t to_int32(const double x);
    std::int32_t to_int32(const e_float& x);

    bool small_arg(const double x);
    bool small_arg(const e_float& x);

    bool large_arg(const double x);
    bool large_arg(const e_float& x);

    bool near_one(const double x);
    bool near_one(const e_float& x);

    bool near_int(const double x);
    bool near_int(const e_float& x);

    const e_float& two                     ();
    const e_float& three                   ();
    const e_float& four                    ();
    const e_float& five                    ();
    const e_float& six                     ();
    const e_float& seven                   ();
    const e_float& eight                   ();
    const e_float& nine                    ();
    const e_float& ten                     ();
    const e_float& fifty                   ();
    const e_float& hundred                 ();
    const e_float& thousand                ();
    const e_float& million                 ();
    const e_float& billion                 ();
    const e_float& trillion                ();
    const e_float& googol                  ();
    const e_float& int64_min               ();
    const e_float& int64_max               ();
    const e_float& int32_min               ();
    const e_float& int32_max               ();
    const e_float& unsigned_long_long_max  ();
    const e_float& signed_long_long_max    ();
    const e_float& signed_long_long_min    ();
    const e_float& double_min              ();
    const e_float& double_max              ();
    const e_float& long_double_min         ();
    const e_float& long_double_max         ();
    const e_float& one_minus               ();
    const e_float& tenth                   ();
    const e_float& eighth                  ();
    const e_float& fifth                   ();
    const e_float& quarter                 ();
    const e_float& third                   ();
    const e_float& two_third               ();
    const e_float& three_half              ();
    const e_float& sqrt2                   ();
    const e_float& pi                      ();
    const e_float& pi_half                 ();
    const e_float& pi_squared              ();
    const e_float& two_pi                  ();
    const e_float& sqrt_pi                 ();
    const e_float& e                       ();
    const e_float& ln2                     ();
    const e_float& ln10                    ();
    const e_float& phi                     ();
    const e_float& euler_gamma             ();
    const e_float& catalan                 ();
    const e_float& khinchin                ();
    const e_float& glaisher                ();

    e_float pow2         (const std::int64_t p);
    e_float inv          (const e_float& x);
    e_float sqrt         (const e_float& x);
    e_float cbrt         (const e_float& x);
    e_float rootn        (const e_float& x, const std::int32_t p);
    e_float rootn_inverse(const e_float& x, const std::int32_t p);
    e_float exp          (const e_float& x);
    e_float log          (const e_float& x);
    e_float log10        (const e_float& x);
    e_float loga         (const e_float& a, const e_float& x);
    e_float log1p        (const e_float& x);
    e_float log1p1m2     (const e_float& x);
    e_float pow          (const e_float& x, const e_float& a);
    e_float pow          (const e_float& b, const std::int64_t p);
    void    sincos       (const e_float& x, e_float* const p_sin, e_float* const p_cos);
    e_float sin          (const e_float& x);
    e_float cos          (const e_float& x);
    e_float tan          (const e_float& x);
    e_float csc          (const e_float& x);
    e_float sec          (const e_float& x);
    e_float cot          (const e_float& x);
    e_float asin         (const e_float& x);
    e_float acos         (const e_float& x);
    e_float atan         (const e_float& x);
    e_float atan2        (const e_float& y, const e_float& x);
    void    sinhcosh     (const e_float& x, e_float* const p_sin, e_float* const p_cos);
    e_float sinh         (const e_float& x);
    e_float cosh         (const e_float& x);
    e_float tanh         (const e_float& x);
    e_float asinh        (const e_float& x);
    e_float acosh        (const e_float& x);
    e_float atanh        (const e_float& x);

    e_float hypergeometric_0f0(const e_float& x);
    e_float hypergeometric_0f1(const e_float& b, const e_float& x);
    e_float hypergeometric_1f0(const e_float& a, const e_float& x);
    e_float hypergeometric_1f1(const e_float& a, const e_float& b, const e_float& x);
    e_float hypergeometric_2f0(const e_float& a, const e_float& b, const e_float& x);
    e_float hypergeometric_2f1(const e_float& a, const e_float& b, const e_float& c, const e_float& x);
    e_float hypergeometric_pfq(const std::deque<e_float>& a, const  std::deque<e_float>& b, const e_float& x);

    e_float gamma          (const e_float& x);
    e_float gamma_near_n   (const std::int32_t n, const e_float& x);
    e_float factorial      (const std::uint32_t n);
    e_float factorial2     (const std::int32_t  n);
    e_float binomial       (const std::uint32_t n, const std::uint32_t k);
    e_float binomial       (const std::uint32_t n, const e_float& y);
    e_float binomial       (const e_float& x, const std::uint32_t k);
    e_float binomial       (const e_float& x, const e_float& y);
    e_float pochhammer     (const e_float& x, const std::uint32_t n);
    e_float pochhammer     (const e_float& x, const e_float& a);
    e_float bernoulli      (const std::uint32_t n);
    void    bernoulli_table(std::vector<e_float>& bn, const std::uint32_t n);
    void    prime          (const std::uint32_t n, std::deque<std::uint32_t>& primes);
    e_float riemann_zeta   (const std::int32_t n);
    e_float riemann_zeta   (const e_float& s);
  }

#endif // E_FLOAT_FUNCTIONS_2004_06_01_HPP_
