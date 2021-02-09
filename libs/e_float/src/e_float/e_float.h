
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef E_FLOAT_2004_06_01_HPP_
  #define E_FLOAT_2004_06_01_HPP_

  #include <limits>
  #include <type_traits>

  // Select the e_float back-end big-number type by defining
  // E_FLOAT_TYPE_xxx, for example E_FLOAT_TYPE_EFX.
  // This preprocessor macro selects (at compile time)
  // the back-end big-number type that is to be compiled.

  #if defined(E_FLOAT_TYPE_EFX)
    #include <e_float/efx/e_float_efx.h>
  #elif defined(E_FLOAT_TYPE_GMP)
    #include <e_float/gmp/e_float_gmp.h>
  #elif defined(E_FLOAT_TYPE_MPFR)
    #include <e_float/mpfr/e_float_mpfr.h>
  #else
    #error e_float type undefined!
  #endif

  namespace ef
  {
    const e_float& zero     ();
    const e_float& one      ();
    const e_float& half     ();
    const e_float& value_min();
    const e_float& value_max();
    const e_float& value_eps();
    const e_float& value_inf();
    const e_float& value_nan();
  }

  // Specialization of std::numeric_limits<e_float>.
  namespace std
  {
    template <> class numeric_limits<e_float>
    {
    public:
      static constexpr bool                    is_specialized    = true;
      static constexpr bool                    is_signed         = true;
      static constexpr bool                    is_integer        = false;
      static constexpr bool                    is_exact          = false;
      static constexpr bool                    is_bounded        = true;
      static constexpr bool                    is_modulo         = false;
      static constexpr bool                    is_iec559         = false;
      static constexpr std::int64_t            digits            = e_float::ef_digits;       // Type differs from int.
      static constexpr std::int64_t            digits10          = e_float::ef_digits10;     // Type differs from int.
      static constexpr std::int64_t            max_digits10      = e_float::ef_max_digits10; // Type differs from int.
      static constexpr std::int64_t            min_exponent      = e_float::ef_min_exp;      // Type differs from int.
      static constexpr std::int64_t            min_exponent10    = e_float::ef_min_exp10;    // Type differs from int.
      static constexpr std::int64_t            max_exponent      = e_float::ef_max_exp;      // Type differs from int.
      static constexpr std::int64_t            max_exponent10    = e_float::ef_max_exp10;    // Type differs from int.
      static constexpr int                     radix             = e_float::ef_radix;
      static constexpr std::float_round_style  round_style       = std::round_to_nearest;
      static constexpr bool                    has_infinity      = true;
      static constexpr bool                    has_quiet_NaN     = true;
      static constexpr bool                    has_signaling_NaN = false;
      static constexpr std::float_denorm_style has_denorm        = std::denorm_absent;
      static constexpr bool                    has_denorm_loss   = false;
      static constexpr bool                    traps             = false;
      static constexpr bool                    tinyness_before   = false;

      static const e_float& (min)        () throw() { return ef::value_min(); }
      static const e_float& (max)        () throw() { return ef::value_max(); }
      static const e_float& lowest       () throw() { return ef::zero(); }
      static const e_float& epsilon      () throw() { return ef::value_eps(); }
      static const e_float& round_error  () throw() { return ef::half(); }
      static const e_float& infinity     () throw() { return ef::value_inf(); }
      static const e_float& quiet_NaN    () throw() { return ef::value_nan(); }
      static const e_float& signaling_NaN() throw() { return ef::zero(); }
      static const e_float& denorm_min   () throw() { return ef::zero(); }
    };
  }

  // Global unary operators of e_float reference.
  inline e_float operator+(const e_float& self) { return e_float(self); }
  inline e_float operator-(const e_float& self) { e_float tmp(self); tmp.negate(); return tmp; }

  // Global add/sub/mul/div of const e_float& with const e_float&.
  inline e_float operator+(const e_float& u, const e_float& v) { return e_float(u) += v; }
  inline e_float operator-(const e_float& u, const e_float& v) { return e_float(u) -= v; }
  inline e_float operator*(const e_float& u, const e_float& v) { return e_float(u) *= v; }
  inline e_float operator/(const e_float& u, const e_float& v) { return e_float(u) /= v; }

  // Global add/sub/mul/div of const e_float& with all built-in types.
  template<typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), e_float>::type operator+(const e_float& u, const SignedIntegralType& n)
  {
    return e_float(u).add_signed_long_long(n);
  }

  template<typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), e_float>::type operator+(const e_float& u, const UnsignedIntegralType& n)
  {
    return e_float(u).add_unsigned_long_long(n);
  }

  template<typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), e_float>::type operator+(const e_float& u, const FloatingPointType& f)
  {
    return e_float(u) += e_float(f);
  }

  template<typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), e_float>::type operator-(const e_float& u, const SignedIntegralType& n)
  {
    return e_float(u).sub_signed_long_long(n);
  }

  template<typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), e_float>::type operator-(const e_float& u, const UnsignedIntegralType& n)
  {
    return e_float(u).sub_unsigned_long_long(n);
  }

  template<typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), e_float>::type operator-(const e_float& u, const FloatingPointType& f)
  {
    return e_float(u) -= e_float(f);
  }

  template<typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), e_float>::type operator*(const e_float& u, const SignedIntegralType& n)
  {
    return e_float(u).mul_signed_long_long(n);
  }

  template<typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), e_float>::type operator*(const e_float& u, const UnsignedIntegralType& n)
  {
    return e_float(u).mul_unsigned_long_long(n);
  }

  template<typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), e_float>::type operator*(const e_float& u, const FloatingPointType& f)
  {
    return e_float(u) *= e_float(f);
  }

  template<typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), e_float>::type operator/(const e_float& u, const SignedIntegralType& n)
  {
    return e_float(u).div_signed_long_long(n);
  }

  template<typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), e_float>::type operator/(const e_float& u, const UnsignedIntegralType& n)
  {
    return e_float(u).div_unsigned_long_long(n);
  }

  template<typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), e_float>::type operator/(const e_float& u, const FloatingPointType& f)
  {
    return e_float(u) /= e_float(f);
  }

  // Global add/sub/mul/div of all built-in types with const e_float&.
  template<typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), e_float>::type operator+(const SignedIntegralType& n, const e_float& u)
  {
    return e_float(u).add_signed_long_long(n);
  }

  template<typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), e_float>::type operator+(const UnsignedIntegralType& n, const e_float& u)
  {
    return e_float(u).add_unsigned_long_long(n);
  }

  template<typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), e_float>::type operator+(const FloatingPointType& f, const e_float& u)
  {
    return e_float(f) += u;
  }

  template<typename ArithmeticType>
  typename std::enable_if<(std::is_arithmetic<ArithmeticType>::value == true), e_float>::type operator-(const ArithmeticType& n, const e_float& u)
  {
    return e_float(n) -= u;
  }

  template<typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), e_float>::type operator*(const SignedIntegralType& n, const e_float& u)
  {
    return e_float(u).mul_signed_long_long(n);
  }

  template<typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), e_float>::type operator*(const UnsignedIntegralType& n, const e_float& u)
  {
    return e_float(u).mul_unsigned_long_long(n);
  }

  template<typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), e_float>::type operator*(const FloatingPointType& f, const e_float& u)
  {
    return e_float(f) *= u;
  }

  template<typename ArithmeticType>
  typename std::enable_if<(std::is_arithmetic<ArithmeticType>::value == true), e_float>::type operator/(const ArithmeticType& n, const e_float& u)
  {
    return e_float(n) /= u;
  }

  // Global self add/sub/mul/div of e_float& with all built-in types.
  template<typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), e_float>::type operator+=(e_float& u, const SignedIntegralType& n)
  {
    return u.add_signed_long_long(n);
  }

  template<typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), e_float>::type operator+=(e_float& u, const UnsignedIntegralType& n)
  {
    return u.add_unsigned_long_long(n);
  }

  template<typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), e_float>::type operator+=(e_float& u, const FloatingPointType& f)
  {
    return u += e_float(f);
  }

  template<typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), e_float>::type operator-=(e_float& u, const SignedIntegralType& n)
  {
    return u.sub_signed_long_long(n);
  }

  template<typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), e_float>::type operator-=(e_float& u, const UnsignedIntegralType& n)
  {
    return u.sub_unsigned_long_long(n);
  }

  template<typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), e_float>::type operator-=(e_float& u, const FloatingPointType& f)
  {
    return u -= e_float(f);
  }

  template<typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), e_float>::type operator*=(e_float& u, const SignedIntegralType& n)
  {
    return u.mul_signed_long_long(n);
  }

  template<typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), e_float>::type operator*=(e_float& u, const UnsignedIntegralType& n)
  {
    return u.mul_unsigned_long_long(n);
  }

  template<typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), e_float>::type operator*=(e_float& u, const FloatingPointType& f)
  {
    return u *= e_float(f);
  }

  template<typename SignedIntegralType>
  typename std::enable_if<   (std::is_integral<SignedIntegralType>::value == true)
                          && (std::is_unsigned<SignedIntegralType>::value == false), e_float>::type operator/=(e_float& u, const SignedIntegralType& n)
  {
    return u.div_signed_long_long(n);
  }

  template<typename UnsignedIntegralType>
  typename std::enable_if<   (std::is_integral<UnsignedIntegralType>::value == true)
                          && (std::is_unsigned<UnsignedIntegralType>::value == true), e_float>::type operator/=(e_float& u, const UnsignedIntegralType& n)
  {
    return u.div_unsigned_long_long(n);
  }

  template<typename FloatingPointType>
  typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true), e_float>::type operator/=(e_float& u, const FloatingPointType& f)
  {
    return u /= e_float(f);
  }

  // Global comparison operators of const e_float& with const e_float&.
  inline bool operator< (const e_float& u, const e_float& v) { return (u.cmp(v) <  static_cast<std::int32_t>(0)); }
  inline bool operator<=(const e_float& u, const e_float& v) { return (u.cmp(v) <= static_cast<std::int32_t>(0)); }
  inline bool operator==(const e_float& u, const e_float& v) { return (u.cmp(v) == static_cast<std::int32_t>(0)); }
  inline bool operator!=(const e_float& u, const e_float& v) { return (u.cmp(v) != static_cast<std::int32_t>(0)); }
  inline bool operator>=(const e_float& u, const e_float& v) { return (u.cmp(v) >= static_cast<std::int32_t>(0)); }
  inline bool operator> (const e_float& u, const e_float& v) { return (u.cmp(v) >  static_cast<std::int32_t>(0)); }

  // Global comparison operators of const e_float& with all built-in types.
  template<typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator< (const e_float& u, const ArithmeticType& v) { return (u.cmp(e_float(v)) <  static_cast<std::int32_t>(0)); }
  template<typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator<=(const e_float& u, const ArithmeticType& v) { return (u.cmp(e_float(v)) <= static_cast<std::int32_t>(0)); }
  template<typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator==(const e_float& u, const ArithmeticType& v) { return (u.cmp(e_float(v)) == static_cast<std::int32_t>(0)); }
  template<typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator!=(const e_float& u, const ArithmeticType& v) { return (u.cmp(e_float(v)) != static_cast<std::int32_t>(0)); }
  template<typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator>=(const e_float& u, const ArithmeticType& v) { return (u.cmp(e_float(v)) >= static_cast<std::int32_t>(0)); }
  template<typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator> (const e_float& u, const ArithmeticType& v) { return (u.cmp(e_float(v)) >  static_cast<std::int32_t>(0)); }

  // Global comparison operators of all built-in types with const e_float&.
  template<typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator< (ArithmeticType u, const e_float& v) { return (e_float(u).cmp(v) <  static_cast<std::int32_t>(0)); }
  template<typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator<=(ArithmeticType u, const e_float& v) { return (e_float(u).cmp(v) <= static_cast<std::int32_t>(0)); }
  template<typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator==(ArithmeticType u, const e_float& v) { return (e_float(u).cmp(v) == static_cast<std::int32_t>(0)); }
  template<typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator!=(ArithmeticType u, const e_float& v) { return (e_float(u).cmp(v) != static_cast<std::int32_t>(0)); }
  template<typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator>=(ArithmeticType u, const e_float& v) { return (e_float(u).cmp(v) >= static_cast<std::int32_t>(0)); }
  template<typename ArithmeticType> typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true, bool>::type operator> (ArithmeticType u, const e_float& v) { return (e_float(u).cmp(v) >  static_cast<std::int32_t>(0)); }

#endif // E_FLOAT_2004_06_01_HPP_
