
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef E_FLOAT_GMP_2008_06_01_HPP_
  #define E_FLOAT_GMP_2008_06_01_HPP_

  #if defined(__INTEL_COMPILER)
    #pragma warning (disable:193)
    #pragma warning (disable:981)
  #endif

  #include <cmath>
  #include <climits>
  #include <limits>
  #include <string>
  #include <type_traits>

  #include <boost/e_float/e_float_base.hpp>

  #include "e_float_gmp_protos.hpp"

  namespace gmp
  {
    class e_float : public ::e_float_base
    {
    public:
      static const std::int64_t ef_digits    = static_cast<std::int64_t>((static_cast<signed long long>(ef_digits10) * 1000LL) / 301LL);
      static const std::int64_t ef_radix     = 2;

      static const std::int64_t ef_max_exp   = static_cast<std::int64_t>(LONG_MAX - 31LL);
      static const std::int64_t ef_min_exp   = static_cast<std::int64_t>(LONG_MIN + 31LL);

      static const std::int64_t ef_max_exp10 = static_cast<std::int64_t>((static_cast<signed long long>(ef_max_exp) * 301LL) / 1000LL);
      static const std::int64_t ef_min_exp10 = static_cast<std::int64_t>((static_cast<signed long long>(ef_min_exp) * 301LL) / 1000LL);

      typedef enum fpclass_type_enum
      {
        ef_finite,
        ef_inf_pos,
        ef_inf_neg,
        ef_NaN
      }
      fpclass_type;

      // Default constructor.
      e_float() : my_rop      (),
                  my_fpclass  (ef_finite),
                  my_prec_elem(ef_max_digits10)
      {
        init();

        ::mpf_init_set_ui(my_rop, 0U);
      }

      // Constructors from built-in unsigned integral types.
      template<typename UnsignedIntegralType,
               typename std::enable_if<(   (std::is_integral<UnsignedIntegralType>::value == true)
                                        && (std::is_unsigned<UnsignedIntegralType>::value == true))>::type const* = nullptr>
      e_float(const UnsignedIntegralType u) : my_rop      (),
                                              my_fpclass  (ef_finite),
                                              my_prec_elem(ef_max_digits10)
      {
        init();

        from_unsigned_long_long(u);
      }

      // Constructors from built-in signed integral types.
      template<typename SignedIntegralType,
               typename std::enable_if<(   (std::is_integral<SignedIntegralType>::value == true)
                                        && (std::is_signed  <SignedIntegralType>::value == true))>::type const* = nullptr>
      e_float(const SignedIntegralType n) : my_rop      (),
                                            my_fpclass  (ef_finite),
                                            my_prec_elem(ef_max_digits10)
      {
        init();

        const bool is_neg = (n < SignedIntegralType(0));

        const unsigned long long u =
          ((!is_neg) ? static_cast<unsigned long long>(n)
                     : static_cast<unsigned long long>(-static_cast<signed long long>(n)));

        from_unsigned_long_long(u);

        if(is_neg)
        {
          ::mpf_neg(my_rop, my_rop);
        }
      }

      // Constructors from built-in floating-point types.
      template<typename FloatingPointType,
               typename std::enable_if<std::is_floating_point<FloatingPointType>::value == true>::type const* = nullptr>
      e_float(const FloatingPointType f) : my_rop      (),
                                           my_fpclass  (ef_finite),
                                           my_prec_elem(ef_max_digits10)
      {
        init();

        from_long_double(static_cast<long double>(f));
      }

      // Constructors from character representations.
      e_float(const char* const  s);
      e_float(const std::string& str);

      // Copy constructor.
      e_float(const e_float& f) : my_rop      (),
                                  my_fpclass  (f.my_fpclass),
                                  my_prec_elem(f.my_prec_elem)
      {
        init();

        ::mpf_init_set(my_rop, f.my_rop);
      }

      // Move constructor.
      e_float(e_float&& f) : my_rop      (),
                             my_fpclass  (f.my_fpclass),
                             my_prec_elem(f.my_prec_elem)
      {
        init();

        ::mpf_init_set(my_rop, f.my_rop);
      }

      // Constructor from mantissa and exponent.
      e_float(const double mantissa, const std::int64_t exponent);

      // Constructor from floating-point class.
      explicit e_float(const fpclass_type fpc) : my_rop      (),
                                                 my_fpclass  (ef_finite),
                                                 my_prec_elem(ef_max_digits10)
      {
        init();

        ::mpf_init_set_ui(my_rop, 0U);

        my_fpclass = fpc;
      }

      virtual ~e_float();

      virtual std::int32_t cmp(const e_float& v) const;

      // Specific special values.
      virtual const e_float& my_value_nan() const;
      virtual const e_float& my_value_inf() const;

      virtual void precision(const std::int32_t);

      // Assignment operator.
      virtual e_float& operator=(const e_float&);

      // Move assignment operator.
      e_float& operator=(e_float&&);

      // Binary arithmetic operators.
      virtual e_float& operator+=(const e_float& v);
      virtual e_float& operator-=(const e_float& v);
      virtual e_float& operator*=(const e_float& v);
      virtual e_float& operator/=(const e_float& v);

      // Arithmetic operators with unsigned long long.
      virtual e_float& add_unsigned_long_long(const unsigned long long n);
      virtual e_float& sub_unsigned_long_long(const unsigned long long n);
      virtual e_float& mul_unsigned_long_long(const unsigned long long n);
      virtual e_float& div_unsigned_long_long(const unsigned long long n);

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
        if(my_fpclass == ef_inf_pos)
        {
          my_fpclass = ef_inf_neg;
        }
        else if(my_fpclass == ef_inf_neg)
        {
          my_fpclass = ef_inf_pos;
        }
        else
        {
          ::mpf_neg(my_rop, my_rop);
        }

        return *this;
      }

      // Comparison functions
      virtual bool isnan   () const { return  (my_fpclass == ef_NaN); }
      virtual bool isinf   () const { return ((my_fpclass == ef_inf_pos) || (my_fpclass == ef_inf_neg)); }
      virtual bool isfinite() const { return  (my_fpclass == ef_finite); }

      virtual bool iszero  () const;
      virtual bool isone   () const;
      virtual bool isint   () const;
      virtual bool isneg   () const;

      // Operators pre-increment and pre-decrement.
      virtual e_float& operator++() { ::mpf_add_ui(my_rop, my_rop, 1U); return *this; }
      virtual e_float& operator--() { ::mpf_sub_ui(my_rop, my_rop, 1U); return *this; }

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

    private:
      ::mpf_t      my_rop;
      fpclass_type my_fpclass;
      std::int32_t my_prec_elem;

      static const unsigned long my_default_prec =
        static_cast<unsigned long>(static_cast<unsigned long>(gmp::e_float::ef_digits) + ((16UL * 1000UL) / 301UL));

      explicit e_float(const ::mpf_t& op);

      static const std::int64_t& max_exp2();
      static const std::int64_t& min_exp2();

      static void init()
      {
        static bool precision_is_initialized;

        if(precision_is_initialized == false)
        {
          precision_is_initialized = true;

          ::mpf_set_default_prec(my_default_prec);
        }
      }

      void from_unsigned_long_long(const unsigned long long u);
      void from_long_double       (const long double l);

      virtual bool rd_string(const char* const s);

      virtual std::int64_t get_order_exact() const;
      virtual std::int64_t get_order_fast () const;

      virtual void get_output_string(std::string& str,
                                     std::int64_t& the_exp,
                                     const std::size_t number_of_digits) const;
    };
  }

#endif // E_FLOAT_GMP_2008_06_01_HPP_
