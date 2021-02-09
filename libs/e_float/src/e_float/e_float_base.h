
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef E_FLOAT_BASE_2004_06_01_HPP_
  #define E_FLOAT_BASE_2004_06_01_HPP_

  #include <cmath>
  #include <cstdint>
  #include <limits>
  #include <iostream>
  #include <string>
  #include <type_traits>

  //#define E_FLOAT_TEST_PI_ALGOS_TESTS
  //#define E_FLOAT_TEST_REAL_IMAG_TESTS
  //#define E_FLOAT_TEST_ALGEBRA_TESTS

  #if !defined(E_FLOAT_TEST_PI_ALGOS_TESTS) && !defined(E_FLOAT_TEST_REAL_IMAG_TESTS) && !defined(E_FLOAT_TEST_ALGEBRA_TESTS)
  #define E_FLOAT_TEST_REAL_IMAG_TESTS
  #endif

  // Select the number of decimal digits in e_float
  // by setting the value of E_FLOAT_DIGITS10.
  // This is a compile-time constant.

  #if defined(E_FLOAT_TEST_PI_ALGOS_TESTS)
  #define E_FLOAT_DIGITS10 1000001
  #elif defined(E_FLOAT_TEST_REAL_IMAG_TESTS)
  #define E_FLOAT_DIGITS10 101
  #elif defined(E_FLOAT_TEST_ALGEBRA_TESTS)
  #define E_FLOAT_DIGITS10 10001
  #else
  #error Error Please define either E_FLOAT_TEST_PI_ALGOS_TESTS or E_FLOAT_TEST_REAL_IMAG_TESTS
  #endif

  #if defined(E_FLOAT_TYPE_EFX)
    namespace efx { class e_float; }
    using efx::e_float;
  #elif defined(E_FLOAT_TYPE_GMP)
    namespace gmp { class e_float; }
    using gmp::e_float;
  #elif defined(E_FLOAT_TYPE_MPFR)
    namespace mpfr { class e_float; }
    using mpfr::e_float;
  #else
    #error The e_float type is undefined. Please define the e_float type.
  #endif

  class e_float_base
  {
  public:
    static const std::int32_t ef_digits10_limit   = static_cast<std::int32_t>(1UL << 30);
    static const std::int32_t ef_digits10_setting = E_FLOAT_DIGITS10;
    static const std::int32_t ef_digits10         = ((ef_digits10_setting < static_cast<std::int32_t>(30)) ? static_cast<std::int32_t>(30) : ((ef_digits10_setting > ef_digits10_limit) ? ef_digits10_limit : ef_digits10_setting));
    static const std::int32_t ef_max_digits10     = static_cast<std::int32_t>(ef_digits10 + 1);

    virtual ~e_float_base() { }

    // Specific special values.
    virtual const e_float& my_value_nan() const = 0;
    virtual const e_float& my_value_inf() const = 0;

    const e_float& my_value_max() const;
    const e_float& my_value_min() const;

    virtual void precision(const std::int32_t) = 0;

    // Assignment operator.
    virtual e_float& operator=(const e_float&) = 0;

    // Binary arithmetic operators.
    virtual e_float& operator+=(const e_float&) = 0;
    virtual e_float& operator-=(const e_float&) = 0;
    virtual e_float& operator*=(const e_float&) = 0;
    virtual e_float& operator/=(const e_float&) = 0;

    // Arithmetic operators with unsigned long long.
    virtual e_float& add_unsigned_long_long(const unsigned long long) = 0;
    virtual e_float& sub_unsigned_long_long(const unsigned long long) = 0;
    virtual e_float& mul_unsigned_long_long(const unsigned long long) = 0;
    virtual e_float& div_unsigned_long_long(const unsigned long long) = 0;

    // Arithmetic operators with signed long long.
    e_float& add_signed_long_long(const signed long long);
    e_float& sub_signed_long_long(const signed long long);
    e_float& mul_signed_long_long(const signed long long);
    e_float& div_signed_long_long(const signed long long);

    // Elementary primitives.
    virtual e_float& calculate_inv () = 0;
    virtual e_float& calculate_sqrt() = 0;

    virtual e_float& negate() = 0;

    // Comparison functions.
    virtual std::int32_t cmp(const e_float&) const = 0;

    int compare(const e_float& v) const
    {
      const std::int32_t this_compare_result = cmp(v);

      return static_cast<int>(this_compare_result);
    }

    virtual bool isnan   () const = 0;
    virtual bool isinf   () const = 0;
    virtual bool isfinite() const = 0;

    virtual bool iszero  () const = 0;
    virtual bool isone   () const = 0;
    virtual bool isint   () const = 0;
    virtual bool isneg   () const = 0;
            bool ispos   () const { return (!isneg()); }

    // Fast order-10 range check.
    std::int64_t order() const { return get_order_fast(); }

    // Conversion routines.
    virtual void               extract_parts             (double&, std::int64_t&) const = 0;
    virtual double             extract_double            () const = 0;
    virtual long double        extract_long_double       () const = 0;
    virtual signed long long   extract_signed_long_long  () const = 0;
    virtual unsigned long long extract_unsigned_long_long() const = 0;
    virtual e_float            extract_integer_part      () const = 0;
    virtual e_float            extract_decimal_part      () const = 0;

    // Formated I/O routines.
            void wr_string(std::string& str, std::ostream& os) const;
    virtual bool rd_string(const char* const) = 0;

    // Specific higher functions which might be present in the MP implementation.
    virtual bool i_have_my_own_ldexp        () const { return false; }
    virtual bool i_have_my_own_frexp        () const { return false; }
    virtual bool i_have_my_own_fmod         () const { return false; }
    virtual bool i_have_my_own_cbrt         () const { return false; }
    virtual bool i_have_my_own_rootn        () const { return false; }
    virtual bool i_have_my_own_exp          () const { return false; }
    virtual bool i_have_my_own_log          () const { return false; }
    virtual bool i_have_my_own_sin          () const { return false; }
    virtual bool i_have_my_own_cos          () const { return false; }
    virtual bool i_have_my_own_tan          () const { return false; }
    virtual bool i_have_my_own_asin         () const { return false; }
    virtual bool i_have_my_own_acos         () const { return false; }
    virtual bool i_have_my_own_atan         () const { return false; }
    virtual bool i_have_my_own_sinh         () const { return false; }
    virtual bool i_have_my_own_cosh         () const { return false; }
    virtual bool i_have_my_own_tanh         () const { return false; }
    virtual bool i_have_my_own_asinh        () const { return false; }
    virtual bool i_have_my_own_acosh        () const { return false; }
    virtual bool i_have_my_own_atanh        () const { return false; }
    virtual bool i_have_my_own_gamma        () const { return false; }
    virtual bool i_have_my_own_riemann_zeta () const { return false; }
    virtual bool i_have_my_own_cyl_bessel_jn() const { return false; }
    virtual bool i_have_my_own_cyl_bessel_yn() const { return false; }

    static e_float my_own_ldexp        (const e_float&, int);
    static e_float my_own_frexp        (const e_float&, int*);
    static e_float my_own_fmod         (const e_float&, const e_float&);
    static e_float my_own_cbrt         (const e_float&);
    static e_float my_own_rootn        (const e_float&, const std::uint32_t);
    static e_float my_own_exp          (const e_float&);
    static e_float my_own_log          (const e_float&);
    static e_float my_own_sin          (const e_float&);
    static e_float my_own_cos          (const e_float&);
    static e_float my_own_tan          (const e_float&);
    static e_float my_own_asin         (const e_float&);
    static e_float my_own_acos         (const e_float&);
    static e_float my_own_atan         (const e_float&);
    static e_float my_own_sinh         (const e_float&);
    static e_float my_own_cosh         (const e_float&);
    static e_float my_own_tanh         (const e_float&);
    static e_float my_own_asinh        (const e_float&);
    static e_float my_own_acosh        (const e_float&);
    static e_float my_own_atanh        (const e_float&);
    static e_float my_own_gamma        (const e_float&);
    static e_float my_own_riemann_zeta (const e_float&);
    static e_float my_own_cyl_bessel_jn(const std::int32_t, const e_float&);
    static e_float my_own_cyl_bessel_yn(const std::int32_t, const e_float&);

  protected:
    inline e_float_base();

    // Emphasize: This template class can be used with native floating-point
    // types like float, double and long double. Note: For long double,
    // you need to verify that the mantissa fits in unsigned long long.
    template<typename native_float_type>
    class native_float_parts final
    {
    public:
      native_float_parts(const native_float_type f) : u(0ULL), e(0) { make_parts(f); }

      const unsigned long long& get_mantissa() const { return u; }
      const int&                get_exponent() const { return e; }

    private:
      native_float_parts();
      native_float_parts(const native_float_parts&);

      const native_float_parts& operator=(const native_float_parts&);

      unsigned long long u;
      int e;

      void make_parts(const native_float_type f)
      {
        const native_float_type ff = ((f < static_cast<native_float_type>(0)) ? -f : f);

        if(ff < (std::numeric_limits<native_float_type>::min)())
        {
          return;
        }

        // Get the fraction and base-2 exponent.
        native_float_type man = ::frexp(f, &e);

        std::uint32_t n2 = 0U;

        for(std::uint32_t i = static_cast<std::uint32_t>(0U); i < static_cast<std::uint32_t>(std::numeric_limits<native_float_type>::digits); i++)
        {
          // Extract the mantissa of the floating-point type in base-2
          // (one bit at a time) and store it in an unsigned long long.
          man *= 2;

          n2   = static_cast<std::uint32_t>(man);
          man -= static_cast<native_float_type>(n2);

          if(n2 != static_cast<std::uint32_t>(0U))
          {
            u |= 1U;
          }

          if(i < static_cast<std::uint32_t>(std::numeric_limits<native_float_type>::digits - 1))
          {
            u <<= 1U;
          }
        }

        // Ensure that the value is normalized and adjust the exponent.
        u |= static_cast<unsigned long long>(1ULL << (std::numeric_limits<native_float_type>::digits - 1));
        e -= 1;
      }
    };

    virtual std::int64_t get_order_exact() const = 0;
    virtual std::int64_t get_order_fast () const = 0;

    virtual void get_output_string(std::string& str,
                                   std::int64_t& the_exp,
                                   const std::size_t number_of_digits) const = 0;
  };

  inline e_float_base::e_float_base() { }

  std::ostream& operator<<(std::ostream& os, const e_float_base& f);
  std::istream& operator>>(std::istream& is,       e_float_base& f);

#endif // E_FLOAT_BASE_2004_06_01_HPP_
