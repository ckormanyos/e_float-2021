
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef E_FLOAT_EFX_2004_06_01_HPP_
  #define E_FLOAT_EFX_2004_06_01_HPP_

  #if defined(__INTEL_COMPILER)
    #pragma warning (disable:981)
  #endif

  #include <algorithm>
  #include <cmath>
  #include <string>
  #include <type_traits>

  #include <boost/e_float/e_float_base.hpp>
  #include <boost/e_float/e_float_detail_dynamic_array.hpp>

  namespace ef
  {
    const e_float& one();
  }

  namespace efx
  {
    class e_float : public ::e_float_base
    {
    public:
      static const std::int32_t ef_radix             = static_cast<std::int32_t>(10);
      static const std::int32_t ef_digits            = ef_digits10;

      static const std::int64_t ef_max_exp           = static_cast<std::int64_t>(+9223372036854775795LL);
      static const std::int64_t ef_min_exp           = static_cast<std::int64_t>(-9223372036854775795LL);
      static const std::int64_t ef_max_exp10         = static_cast<std::int64_t>(+3063937869882635616LL); // Approx. [ef_max_exp / log10(2)], also an even multiple of 8
      static const std::int64_t ef_min_exp10         = static_cast<std::int64_t>(-3063937869882635616LL);

      static const std::int32_t ef_elem_digits10     = static_cast<std::int32_t>(8);
      static const std::int32_t ef_digits10_num_base = static_cast<std::int32_t>((ef_max_digits10 / ef_elem_digits10) + (((ef_max_digits10 % ef_elem_digits10) != 0) ? 1 : 0));
      static const std::int32_t ef_elem_number       = static_cast<std::int32_t>(ef_digits10_num_base + 3);

      typedef enum fpclass_type_enum
      {
        ef_finite,
        ef_inf,
        ef_NaN
      }
      fpclass_type;

      static const std::int32_t ef_elem_mask = static_cast<std::int32_t>(100000000);

      typedef ef::detail::fixed_dynamic_array<std::uint32_t,
                                              static_cast<std::size_t>(ef_elem_number),
                                              std::allocator<std::uint32_t>>
      array_type;

      // Default constructor.
      e_float() noexcept : my_data     (),
                           my_exp      (static_cast<std::int64_t>(0)),
                           my_neg      (false),
                           my_fpclass  (ef_finite),
                           my_prec_elem(ef_elem_number) { }

      // Constructors from built-in unsigned integral types.
      template<typename UnsignedIntegralType,
               typename std::enable_if<(   (std::is_integral<UnsignedIntegralType>::value == true)
                                        && (std::is_unsigned<UnsignedIntegralType>::value == true))>::type const* = nullptr>
      e_float(const UnsignedIntegralType u) : my_data     (),
                                              my_exp      (static_cast<std::int64_t>(0)),
                                              my_neg      (false),
                                              my_fpclass  (ef_finite),
                                              my_prec_elem(ef_elem_number)
      {
        from_unsigned_long_long(u);
      }

      // Constructors from built-in signed integral types.
      template<typename SignedIntegralType,
               typename std::enable_if<(   (std::is_integral<SignedIntegralType>::value == true)
                                        && (std::is_signed  <SignedIntegralType>::value == true))>::type const* = nullptr>
      e_float(const SignedIntegralType n) : my_data     (),
                                            my_exp      (static_cast<std::int64_t>(0)),
                                            my_neg      (n < static_cast<signed long long>(0)),
                                            my_fpclass  (ef_finite),
                                            my_prec_elem(ef_elem_number)
      {
        const unsigned long long u =
          ((!my_neg) ? static_cast<unsigned long long>(n)
                     : static_cast<unsigned long long>(-static_cast<signed long long>(n)));

        from_unsigned_long_long(u);
      }

      // Constructors from built-in floating-point types.
      template<typename FloatingPointType,
               typename std::enable_if<std::is_floating_point<FloatingPointType>::value == true>::type const* = nullptr>
      e_float(const FloatingPointType f) : my_data     (),
                                           my_exp      (static_cast<std::int64_t>(0)),
                                           my_neg      (false),
                                           my_fpclass  (ef_finite),
                                           my_prec_elem(ef_elem_number)
      {
        from_long_double(static_cast<long double>(f));
      }

      // Constructors from character representations.
      e_float(const char* const  s);
      e_float(const std::string& str);

      // Copy constructor.
      e_float(const e_float& f) : my_data     (f.my_data),
                                  my_exp      (f.my_exp),
                                  my_neg      (f.my_neg),
                                  my_fpclass  (f.my_fpclass),
                                  my_prec_elem(f.my_prec_elem) { }

      // Move constructor.
      e_float(e_float&& f) : my_data     (static_cast<array_type&&>(f.my_data)),
                             my_exp      (f.my_exp),
                             my_neg      (f.my_neg),
                             my_fpclass  (f.my_fpclass),
                             my_prec_elem(f.my_prec_elem) { }

      // Constructor from mantissa and exponent.
      e_float(const double mantissa, const std::int64_t exponent);

      // Constructor from floating-point class.
      explicit e_float(const fpclass_type fpc) : my_data     (),
                                                 my_exp      (static_cast<std::int64_t>(0)),
                                                 my_neg      (false),
                                                 my_fpclass  (fpc),
                                                 my_prec_elem(ef_elem_number) { }

      virtual ~e_float() = default;

      virtual std::int32_t cmp(const e_float&) const;

      // Specific special values.
      virtual const e_float& my_value_nan() const;
      virtual const e_float& my_value_inf() const;

      virtual void precision(const std::int32_t prec_digits)
      {
        if(prec_digits >= ef_digits10)
        {
          my_prec_elem = ef_elem_number;
        }
        else
        {
          const std::int32_t elems =
            static_cast<std::int32_t>(  static_cast<std::int32_t>( (prec_digits + (ef_elem_digits10 / 2)) / ef_elem_digits10)
                                      + static_cast<std::int32_t>(((prec_digits %  ef_elem_digits10) != 0) ? 1 : 0));

          my_prec_elem = (std::min)(ef_elem_number, (std::max)(elems, static_cast<std::int32_t>(2)));
        }
      }

      // Assignment operator.
      virtual e_float& operator=(const e_float& v)
      {
        if(this != &v)
        {
          my_data      = v.my_data;
          my_exp       = v.my_exp;
          my_neg       = v.my_neg;
          my_fpclass   = v.my_fpclass;
          my_prec_elem = v.my_prec_elem;
        }

        return *this;
      }

      // Move assignment operator.
      e_float& operator=(e_float&& other)
      {
        my_data      = static_cast<array_type&&>(other.my_data);
        my_exp       = other.my_exp;
        my_neg       = other.my_neg;
        my_fpclass   = other.my_fpclass;
        my_prec_elem = other.my_prec_elem;

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
        if(!iszero())
        {
          my_neg = (!my_neg);
        }

        return *this;
      }

      // Comparison functions.
      virtual bool isnan   () const { return (my_fpclass == ef_NaN); }
      virtual bool isinf   () const { return (my_fpclass == ef_inf); }
      virtual bool isfinite() const { return (my_fpclass == ef_finite); }

      virtual bool iszero  () const;
      virtual bool isone   () const;
      virtual bool isint   () const;
      virtual bool isneg   () const { return my_neg; }

      // Operators pre-increment and pre-decrement.
      virtual e_float& operator++() { return *this += ef::one(); }
      virtual e_float& operator--() { return *this -= ef::one(); }

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
      array_type   my_data;
      std::int64_t my_exp;
      bool         my_neg;
      fpclass_type my_fpclass;
      std::int32_t my_prec_elem;

      void from_unsigned_long_long(const unsigned long long u)
      {
        std::fill(my_data.begin(), my_data.end(), static_cast<array_type::value_type>(0U));

        my_exp = static_cast<std::int64_t>(0);

        std::size_t i =static_cast<std::size_t>(0U);

        unsigned long long uu = u;

        std::uint32_t temp[(std::numeric_limits<unsigned long long>::digits10 / static_cast<int>(ef_elem_digits10)) + 3] = { static_cast<std::uint32_t>(0U) };

        while(uu != static_cast<unsigned long long>(0U))
        {
          temp[i] = static_cast<std::uint32_t>(uu % static_cast<unsigned long long>(ef_elem_mask));

          uu = static_cast<unsigned long long>(uu / static_cast<unsigned long long>(ef_elem_mask));

          ++i;
        }

        if(i > static_cast<std::size_t>(1U))
        {
          my_exp += static_cast<std::int64_t>((i - 1U) * static_cast<std::size_t>(ef_elem_digits10));
        }

        std::reverse(temp, temp + i);

        std::copy(temp, temp + (std::min)(i, static_cast<std::size_t>(ef_elem_number)), my_data.begin());
      }

      void from_long_double(const long double        l);

      std::int32_t cmp_data(const array_type& vd) const;

      static std::uint32_t mul_loop_uv (std::uint32_t* const u, const std::uint32_t* const v, const std::int32_t p);
      static std::uint32_t mul_loop_n  (std::uint32_t* const u,       std::uint32_t n,        const std::int32_t p);
      static std::uint32_t div_loop_n  (std::uint32_t* const u,       std::uint32_t n,        const std::int32_t p);
      static void          mul_loop_fft(std::uint32_t* const u, const std::uint32_t* const v, const std::int32_t p);

      virtual std::int64_t get_order_exact() const { return get_order_fast(); }
      virtual std::int64_t get_order_fast () const;

      virtual void  get_output_string(std::string& str,
                                      std::int64_t& the_exp,
                                      const std::size_t number_of_digits) const;

      virtual bool rd_string(const char* const s);
    };
  }

#endif // E_FLOAT_EFX_2004_06_01_HPP_
