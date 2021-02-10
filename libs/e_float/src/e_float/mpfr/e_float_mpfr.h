
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef E_FLOAT_MPFR_2008_06_01_HPP_
  #define E_FLOAT_MPFR_2008_06_01_HPP_

  #include <climits>
  #include <cmath>
  #include <limits>
  #include <string>

  #include <e_float/e_float_base.h>
  #include <e_float/mpfr/e_float_mpfr_protos.h>

  namespace mpfr
  {
    class e_float : public ::e_float_base
    {
    public:
      static constexpr int ef_digits    = static_cast<int>((static_cast<signed long long>(ef_digits10) * 1000LL) / 301LL);
      static constexpr int ef_radix     = 2;

      static constexpr int ef_max_exp   = (std::numeric_limits<int>::max)() / 2;
      static constexpr int ef_min_exp   = (std::numeric_limits<int>::min)() / 2;

      static constexpr int ef_max_exp10 = static_cast<int>(static_cast<long long>(static_cast<long long>(ef_max_exp) * 301LL) / 1000LL);
      static constexpr int ef_min_exp10 = static_cast<int>(static_cast<long long>(static_cast<long long>(ef_min_exp) * 301LL) / 1000LL);

      // Default constructor.
      e_float() : my_rop()
      {
        init();

        mpfr_init_set_ui(my_rop, 0UL, GMP_RNDN);
      }

      // Constructors from built-in unsigned integral types.
      template<typename UnsignedIntegralType,
               typename std::enable_if<(   (std::is_integral<UnsignedIntegralType>::value == true)
                                        && (std::is_unsigned<UnsignedIntegralType>::value == true))>::type const* = nullptr>
      e_float(const UnsignedIntegralType u) : my_rop()
      {
        from_unsigned_long_long(u);
      }

      // Constructors from built-in signed integral types.
      template<typename SignedIntegralType,
               typename std::enable_if<(   (std::is_integral<SignedIntegralType>::value == true)
                                        && (std::is_signed  <SignedIntegralType>::value == true))>::type const* = nullptr>
      e_float(const SignedIntegralType n) : my_rop()
      {
        const bool is_neg = (n < SignedIntegralType(0));

        const unsigned long long u =
          ((!is_neg) ? static_cast<unsigned long long>(n)
                     : static_cast<unsigned long long>(-static_cast<signed long long>(n)));

        from_unsigned_long_long(u);

        if(is_neg)
        {
          ::mpfr_neg(my_rop, my_rop, GMP_RNDN);
        }
      }

      // Constructors from built-in floating-point types.
      template<typename FloatingPointType,
               typename std::enable_if<std::is_floating_point<FloatingPointType>::value == true>::type const* = nullptr>
      e_float(const FloatingPointType f) : my_rop()
      {
        from_long_double(static_cast<long double>(f));
      }

      // Constructors from character representations.
      e_float(const char* const  s);
      e_float(const std::string& str);

      // Copy constructor.
      e_float(const e_float& f) : my_rop()
      {
        init();

        mpfr_init_set(my_rop, f.my_rop, GMP_RNDN);
      }

      // Move constructor.
      e_float(e_float&& f) : my_rop()
      {
        init();

        mpfr_init_set(my_rop, f.my_rop, GMP_RNDN);
      }

      // Constructor from mantissa and exponent.
      e_float(const double mantissa, const std::int64_t exponent);

      virtual ~e_float();

      virtual std::int32_t cmp(const e_float&) const;

      // Specific special values.
      virtual const e_float& my_value_nan() const;
      virtual const e_float& my_value_inf() const;

      virtual void precision(const std::int32_t) { }

      // Assignment operator.
      virtual e_float& operator=(const e_float& other)
      {
        if(this != &other)
        {
          static_cast<void>(::mpfr_set(my_rop, other.my_rop, GMP_RNDN));
        }

        return *this;
      }

      // Move assignment operator.
      virtual e_float& operator=(e_float&& other)
      {
        static_cast<void>(::mpfr_set(my_rop, other.my_rop, GMP_RNDN));

        return *this;
      }

      // Binary arithmetic operators.
      virtual e_float& operator+=(const e_float&);
      virtual e_float& operator-=(const e_float&);
      virtual e_float& operator*=(const e_float&);
      virtual e_float& operator/=(const e_float&);

      // Arithmetic operators with unsigned long long.
      virtual e_float& add_unsigned_long_long(const unsigned long long);
      virtual e_float& sub_unsigned_long_long(const unsigned long long);
      virtual e_float& mul_unsigned_long_long(const unsigned long long);
      virtual e_float& div_unsigned_long_long(const unsigned long long);

      void swap(e_float& other_e_float)
      {
        if(this != &other_e_float)
        {
          const e_float tmp_value_this(*this);

          *this = other_e_float;

          other_e_float = tmp_value_this;
        }
      }

      // Elementary primitives.
      virtual e_float& calculate_inv ();
      virtual e_float& calculate_sqrt();

      virtual e_float& negate()
      {
        ::mpfr_neg(my_rop, my_rop, GMP_RNDN);

        return *this;
      }

      // Comparison functions
      virtual bool isnan   () const;
      virtual bool isinf   () const;
      virtual bool isfinite() const;

      virtual bool iszero  () const;
      virtual bool isone   () const;
      virtual bool isint   () const;
      virtual bool isneg   () const;

      // Operators pre-increment and pre-decrement.
      virtual e_float& operator++() { ::mpfr_add_ui(my_rop, my_rop, static_cast<unsigned long>(1UL), GMP_RNDN); return *this; }
      virtual e_float& operator--() { ::mpfr_sub_ui(my_rop, my_rop, static_cast<unsigned long>(1UL), GMP_RNDN); return *this; }

      // Operators post-increment and post-decrement.
      e_float operator++(int) { const e_float w(*this); static_cast<void>(++(*this)); return w; }
      e_float operator--(int) { const e_float w(*this); static_cast<void>(--(*this)); return w; }

      // Conversion routines.
      virtual void               extract_parts             (double& mantissa, std::int64_t& exponent) const;
      virtual double             extract_double            () const;
      virtual long double        extract_long_double       () const;
      virtual signed long long   extract_signed_long_long  () const;
      virtual unsigned long long extract_unsigned_long_long() const;
      virtual e_float            extract_integer_part      () const;
      virtual e_float            extract_decimal_part      () const;

      static e_float my_own_cbrt         (const e_float& x);
      static e_float my_own_rootn        (const e_float& x, const std::uint32_t p);
      static e_float my_own_exp          (const e_float& x);
      static e_float my_own_log          (const e_float& x);
      static e_float my_own_sin          (const e_float& x);
      static e_float my_own_cos          (const e_float& x);
      static e_float my_own_tan          (const e_float& x);
      static e_float my_own_asin         (const e_float& x);
      static e_float my_own_acos         (const e_float& x);
      static e_float my_own_atan         (const e_float& x);
      static e_float my_own_sinh         (const e_float& x);
      static e_float my_own_cosh         (const e_float& x);
      static e_float my_own_tanh         (const e_float& x);
      static e_float my_own_asinh        (const e_float& x);
      static e_float my_own_acosh        (const e_float& x);
      static e_float my_own_atanh        (const e_float& x);
      static e_float my_own_gamma        (const e_float& x);
      static e_float my_own_riemann_zeta (const e_float& x);
      static e_float my_own_cyl_bessel_jn(const std::int32_t n, const e_float& x);
      static e_float my_own_cyl_bessel_yn(const std::int32_t n, const e_float& x);

      virtual bool i_have_my_own_cbrt         () const { return true; }
      virtual bool i_have_my_own_rootn        () const { return true; }
      virtual bool i_have_my_own_exp          () const { return true; }
      virtual bool i_have_my_own_log          () const { return true; }
      virtual bool i_have_my_own_sin          () const { return true; }
      virtual bool i_have_my_own_cos          () const { return true; }
      virtual bool i_have_my_own_tan          () const { return true; }
      virtual bool i_have_my_own_asin         () const { return true; }
      virtual bool i_have_my_own_acos         () const { return true; }
      virtual bool i_have_my_own_atan         () const { return true; }
      virtual bool i_have_my_own_sinh         () const { return true; }
      virtual bool i_have_my_own_cosh         () const { return true; }
      virtual bool i_have_my_own_tanh         () const { return true; }
      virtual bool i_have_my_own_asinh        () const { return true; }
      virtual bool i_have_my_own_acosh        () const { return true; }
      virtual bool i_have_my_own_atanh        () const { return true; }
      virtual bool i_have_my_own_gamma        () const { return false; }
      virtual bool i_have_my_own_riemann_zeta () const { return false; }
      virtual bool i_have_my_own_cyl_bessel_jn() const { return false; }
      virtual bool i_have_my_own_cyl_bessel_yn() const { return false; }

    private:
      ::mpfr_t my_rop;

      static const mp_prec_t my_default_prec =
        static_cast<mp_prec_t>(static_cast<mp_prec_t>(mpfr::e_float::ef_digits) + ((16 * 1000) / 301));

      static void init()
      {
        static bool precision_is_initialized;

        if(precision_is_initialized == false)
        {
          precision_is_initialized = true;

          ::mpfr_set_default_prec(my_default_prec);
        }
      }

      void from_unsigned_long_long(const unsigned long long);
      void from_long_double       (const long double);

      virtual bool rd_string(const char* const);

      virtual std::int64_t get_order_exact() const;
      virtual std::int64_t get_order_fast () const;

      virtual void get_output_string(std::string& str,
                                     std::int64_t& the_exp,
                                     const std::size_t number_of_digits) const;
    };
  }

#endif // E_FLOAT_MPFR_2008_06_01_HPP_
