#ifndef E_FLOAT_BACKEND_2017_08_18_HPP_
  #define E_FLOAT_BACKEND_2017_08_18_HPP_

  #include <cstdint>
  #include <sstream>
  #include <type_traits>

  #include <boost/e_float/e_float.hpp>

  #include <boost/config.hpp>
  #include <boost/multiprecision/number.hpp>

  namespace boost { namespace multiprecision {

  // Forward declaration of the e_float_backend multiple precision class.
  // This class binds native e_float to boost::multiprecsion::e_float_backend.
  template<const std::int32_t MyDigits10>
  class e_float_backend;

  // Define the number category as a floating-point kind
  // for the e_float_backend. This is needed for properly
  // interacting as a backend with boost::muliprecision.
  template<const std::int32_t MyDigits10>
  struct boost::multiprecision::number_category<e_float_backend<MyDigits10>>
    : public boost::mpl::int_<boost::multiprecision::number_kind_floating_point> { };

  // This is the e_float_backend multiple precision class.
  template<const std::int32_t MyDigits10>
  class e_float_backend
  {
  public:
    typedef boost::mpl::list<  signed long long> signed_types;
    typedef boost::mpl::list<unsigned long long> unsigned_types;
    typedef boost::mpl::list<long double>        float_types;
    typedef std::int64_t                         exponent_type;

    e_float_backend() : m_value() { }

    explicit e_float_backend(const e_float& rep) : m_value(rep) { }

    e_float_backend(const e_float_backend& other) : m_value(other.m_value) { }

    template<typename UnsignedIntegralType,
             typename std::enable_if<(   (std::is_integral<UnsignedIntegralType>::value == true)
                                      && (std::is_unsigned<UnsignedIntegralType>::value == true))>::type const* = nullptr>
    e_float_backend(UnsignedIntegralType u) : m_value(e_float(std::uint64_t(u))) { }

    template<typename SignedIntegralType,
             typename std::enable_if<(   (std::is_integral<SignedIntegralType>::value == true)
                                      && (std::is_signed  <SignedIntegralType>::value == true))>::type const* = nullptr>
    e_float_backend(SignedIntegralType n) : m_value(e_float(std::int64_t(n))) { }

    template<typename FloatingPointType,
             typename std::enable_if<std::is_floating_point<FloatingPointType>::value == true>::type const* = nullptr>
    e_float_backend(FloatingPointType f) : m_value(e_float(static_cast<long double>(f))) { }

    e_float_backend(const char* c) : m_value(c) { }

    e_float_backend(const std::string& str) : m_value(str) { }

    virtual ~e_float_backend();

    e_float_backend& operator=(const e_float_backend& other)
    {
      m_value = other.m_value;

      return *this;
    }

    template<typename ArithmeticType,
             typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true>::type const* = nullptr>
    e_float_backend& operator=(const ArithmeticType& x)
    {
      m_value = e_float(x);

      return *this;
    }

    e_float_backend& operator=(const std::string& str_rep)  { m_value = e_float(str_rep);  return *this; }
    e_float_backend& operator=(const char*        char_ptr) { m_value = e_float(char_ptr); return *this; }

    void swap(e_float_backend& other_mp_cpp_backend)
    {
      m_value.swap(other_mp_cpp_backend.m_value);
    }

          e_float&  representation()       { return m_value; }
    const e_float&  representation() const { return m_value; }
    const e_float& crepresentation() const { return m_value; }

    std::string str(std::streamsize number_of_digits, const std::ios::fmtflags format_flags) const
    {
      std::string        my_result_str;
      std::stringstream  my_stream_str;

      my_stream_str.flags(format_flags);

      static_cast<void>(my_stream_str.precision(number_of_digits));

      m_value.wr_string(my_result_str, my_stream_str);

      return my_result_str;
    }

    void negate()
    {
      m_value.negate();
    }

    int compare(const e_float_backend& other_mp_cpp_backend) const
    {
      return static_cast<int>(m_value.compare(other_mp_cpp_backend.m_value));
    }

    template<typename ArithmeticType,
             typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true>::type const* = nullptr>
    int compare(ArithmeticType x)
    {
      return static_cast<int>(m_value.compare(e_float(x)));
    }

  private:
    e_float m_value;

    e_float_backend& operator=(const e_float&) = delete;
  };

  template<const std::int32_t MyDigits10>
  e_float_backend<MyDigits10>::~e_float_backend() { }

  template<const std::int32_t MyDigits10>
  void eval_add(e_float_backend<MyDigits10>& result, const e_float_backend<MyDigits10>& x)
  {
    result.representation() += x.crepresentation();
  }

  template<const std::int32_t MyDigits10>
  void eval_subtract(e_float_backend<MyDigits10>& result, const e_float_backend<MyDigits10>& x)
  {
    result.representation() -= x.crepresentation();
  }

  template<const std::int32_t MyDigits10>
  void eval_multiply(e_float_backend<MyDigits10>& result, const e_float_backend<MyDigits10>& x)
  {
    result.representation() *= x.crepresentation();
  }

  template<const std::int32_t MyDigits10,
           typename SignedIntegralType,
           typename std::enable_if<(   (std::is_integral<SignedIntegralType>::value == true)
                                    && (std::is_signed  <SignedIntegralType>::value == true))>::type const* = nullptr>
  void eval_multiply(e_float_backend<MyDigits10>& result, const SignedIntegralType& n)
  {
    result.representation().mul_signed_long_long(static_cast<std::int64_t>(n));
  }

  template<const std::int32_t MyDigits10>
  void eval_divide(e_float_backend<MyDigits10>& result, const e_float_backend<MyDigits10>& x)
  {
    result.representation() /= x.crepresentation();
  }

  template<const std::int32_t MyDigits10,
           typename SignedIntegralType,
           typename std::enable_if<(   (std::is_integral<SignedIntegralType>::value == true)
                                    && (std::is_signed  <SignedIntegralType>::value == true))>::type const* = nullptr>
  void eval_divide(e_float_backend<MyDigits10>& result, const SignedIntegralType& n)
  {
    result.representation().div_signed_long_long(static_cast<std::int64_t>(n));
  }

  template<const std::int32_t MyDigits10>
  bool eval_eq(const e_float_backend<MyDigits10>& a, const e_float_backend<MyDigits10>& b)
  {
    return (a.compare(b) == 0);
  }

  template<const std::int32_t MyDigits10,
           typename ArithmeticType,
           typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true>::type const* = nullptr>
  bool eval_eq(const e_float_backend<MyDigits10>& a, const ArithmeticType& b)
  {
    return (a.compare(b) == 0);
  }

  template<const std::int32_t MyDigits10,
           typename ArithmeticType,
           typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true>::type const* = nullptr>
  bool eval_eq(const ArithmeticType& a, const e_float_backend<MyDigits10>& b)
  {
    return (e_float_backend(a).compare(b) == 0);
  }

  template<const std::int32_t MyDigits10>
  bool eval_gt(const e_float_backend<MyDigits10>& a, const e_float_backend<MyDigits10>& b)
  {
    return (a.compare(b) == 1);
  }

  template<const std::int32_t MyDigits10,
           typename ArithmeticType,
           typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true>::type const* = nullptr>
  bool eval_gt(const e_float_backend<MyDigits10>& a, const ArithmeticType& b)
  {
    return (a.compare(b) == 1);
  }

  template<const std::int32_t MyDigits10,
           typename ArithmeticType,
           typename std::enable_if<std::is_arithmetic<ArithmeticType>::value>::type const* = nullptr>
  bool eval_gt(const ArithmeticType& a, const e_float_backend<MyDigits10>& b)
  {
    return (e_float_backend(a).compare(b) == 1);
  }

  template<const std::int32_t MyDigits10>
  bool eval_lt(const e_float_backend<MyDigits10>& a, const e_float_backend<MyDigits10>& b)
  {
    return (a.compare(b) == -1);
  }

  template<const std::int32_t MyDigits10,
           typename ArithmeticType,
           typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true>::type const* = nullptr>
  bool eval_lt(const e_float_backend<MyDigits10>& a, const ArithmeticType& b)
  {
    return (a.compare(b) == -1);
  }

  template<const std::int32_t MyDigits10,
           typename ArithmeticType,
           typename std::enable_if<std::is_arithmetic<ArithmeticType>::value == true>::type const* = nullptr>
  bool eval_lt(const ArithmeticType& a, const e_float_backend<MyDigits10>& b)
  {
    return (e_float_backend(a).compare(b) == -1);
  }

  template<const std::int32_t MyDigits10>
  bool eval_is_zero(const e_float_backend<MyDigits10>& x)
  {
    return x.crepresentation().iszero();
  }

  template<const std::int32_t MyDigits10>
  int eval_get_sign(const e_float_backend<MyDigits10>& x)
  {
    if     (x.crepresentation().iszero()) { return  0; }
    else if(x.crepresentation().isneg ()) { return -1; }
    else                                  { return  1; }
  }

  template<const std::int32_t MyDigits10>
  void eval_convert_to(unsigned long long* result,
                       const e_float_backend<MyDigits10>& val)
  {
    *result = (val.crepresentation()).extract_unsigned_long_long();
  }

  template<const std::int32_t MyDigits10>
  void eval_convert_to(signed long long* result,
                       const e_float_backend<MyDigits10>& val)
  {
    *result = (val.crepresentation()).extract_signed_long_long();
  }

  template<const std::int32_t MyDigits10>
  void eval_convert_to(long double* result,
                       const e_float_backend<MyDigits10>& val)
  {
    *result = (val.crepresentation()).extract_long_double();
  }

  template<const std::int32_t MyDigits10>
  void eval_frexp(      e_float_backend<MyDigits10>& result,
                  const e_float_backend<MyDigits10>& x,
                  const typename e_float_backend<MyDigits10>::exponent_type* expptr)
  {
    typedef std::int64_t local_exponent_type;

    local_exponent_type exp2;

    result.representation() = ef::frexp(x.crepresentation(), &exp2);

    *expptr = static_cast<typename e_float_backend<MyDigits10>::exponent_type>(exp2);
  }

  template<const std::int32_t MyDigits10>
  void eval_frexp(e_float_backend<MyDigits10>& result,
                  const e_float_backend<MyDigits10>& x,
                  int* expptr,
                  typename std::enable_if<std::is_same<typename e_float_backend<MyDigits10>::exponent_type, int>::value == false>::type const* = nullptr)
  {
    result.representation() = ef::frexp(x.crepresentation(), expptr);
  }

  template<const std::int32_t MyDigits10>
  void eval_ldexp(      e_float_backend<MyDigits10>& result,
                  const e_float_backend<MyDigits10>& x,
                  const typename e_float_backend<MyDigits10>::exponent_type exp_value)
  {
    typedef int local_exponent_type;

    result.representation() = ef::ldexp(x.crepresentation(), local_exponent_type(exp_value));
  }

  template<const std::int32_t MyDigits10>
  void eval_ldexp(e_float_backend<MyDigits10>& result,
                  const e_float_backend<MyDigits10>& x,
                  int exp_value,
                  typename std::enable_if<std::is_same<typename e_float_backend<MyDigits10>::exponent_type, int>::value == false>::type const* = nullptr)
  {
    typedef int local_exponent_type;

    result.representation() = ef::ldexp(x.crepresentation(), local_exponent_type(exp_value));
  }

  template<const std::int32_t MyDigits10>
  void eval_floor(      e_float_backend<MyDigits10>& result,
                  const e_float_backend<MyDigits10>& x)
  {
    result.representation() = ef::floor(x.crepresentation());
  }

  template<const std::int32_t MyDigits10>
  void eval_ceil(      e_float_backend<MyDigits10>& result,
                 const e_float_backend<MyDigits10>& x)
  {
    result.representation() = ef::ceil(x.crepresentation());
  }

  template<const std::int32_t MyDigits10>
  int eval_fpclassify(const e_float_backend<MyDigits10>& x)
  {
    if     ((x.crepresentation().isinf)()) { return FP_INFINITE; }
    else if((x.crepresentation().isnan)()) { return FP_NAN; }
    else if( x.crepresentation().iszero()) { return FP_ZERO; }
    else                                   { return FP_NORMAL; }
  }

  template<const std::int32_t MyDigits10>
  void eval_trunc(      e_float_backend<MyDigits10>& result,
                  const e_float_backend<MyDigits10>& x)
  {
    result.representation() = ef::integer_part(x.crepresentation());
  }

  template<const std::int32_t MyDigits10>
  void eval_abs(      e_float_backend<MyDigits10>& result,
                const e_float_backend<MyDigits10>& x)
  {
    result.representation() = x.crepresentation();

    if(result.crepresentation().isneg())
    {
      result.representation().negate();
    }
  }

  template<const std::int32_t MyDigits10>
  void eval_fabs(      e_float_backend<MyDigits10>& result,
                 const e_float_backend<MyDigits10>& x)
  {
    result.representation() = x.crepresentation();

    if(result.crepresentation().isneg())
    {
      result.representation().negate();
    }
  }

  template<const std::int32_t MyDigits10>
  void eval_sqrt(      e_float_backend<MyDigits10>& result,
                 const e_float_backend<MyDigits10>& x)
  {
    result.representation() = ef::sqrt(x.crepresentation());
  }

  template<const std::int32_t MyDigits10>
  void eval_sin(      e_float_backend<MyDigits10>& result,
                const e_float_backend<MyDigits10>& x)
  {
    result.representation() = ef::sin(x.crepresentation());
  }

  template<const std::int32_t MyDigits10>
  void eval_cos(      e_float_backend<MyDigits10>& result,
                const e_float_backend<MyDigits10>& x)
  {
    result.representation() = ef::cos(x.crepresentation());
  }

  template<const std::int32_t MyDigits10>
  void eval_tan(      e_float_backend<MyDigits10>& result,
                const e_float_backend<MyDigits10>& x)
  {
    result.representation() = ef::tan(x.crepresentation());
  }

  template<const std::int32_t MyDigits10>
  void eval_asin(      e_float_backend<MyDigits10>& result,
                 const e_float_backend<MyDigits10>& x)
  {
    result.representation() = ef::asin(x.crepresentation());
  }

  template<const std::int32_t MyDigits10>
  void eval_acos(      e_float_backend<MyDigits10>& result,
                 const e_float_backend<MyDigits10>& x)
  {
    result.representation() = ef::acos(x.crepresentation());
  }

  template<const std::int32_t MyDigits10>
  void eval_atan(      e_float_backend<MyDigits10>& result,
                 const e_float_backend<MyDigits10>& x)
  {
    result.representation() = ef::atan(x.crepresentation());
  }

  template<const std::int32_t MyDigits10>
  void eval_atan2(      e_float_backend<MyDigits10>& result,
                  const e_float_backend<MyDigits10>& y,
                  const e_float_backend<MyDigits10>& x)
  {
    result.representation() = ef::atan2(y.crepresentation(), x.crepresentation());
  }

  template<const std::int32_t MyDigits10>
  void eval_log(      e_float_backend<MyDigits10>& result,
                const e_float_backend<MyDigits10>& x)
  {
    result.representation() = ef::log(x.crepresentation());
  }

  template<const std::int32_t MyDigits10>
  void eval_log10(      e_float_backend<MyDigits10>& result,
                  const e_float_backend<MyDigits10>& x)
  {
    result.representation() = ef::log10(x.crepresentation());
  }

  template<const std::int32_t MyDigits10>
  void eval_exp(      e_float_backend<MyDigits10>& result,
                const e_float_backend<MyDigits10>& x)
  {
    result.representation() = ef::exp(x.crepresentation());
  }

  template<const std::int32_t MyDigits10>
  void eval_sinh(      e_float_backend<MyDigits10>& result,
                 const e_float_backend<MyDigits10>& x)
  {
    result.representation() = ef::sinh(x.crepresentation());
  }

  template<const std::int32_t MyDigits10>
  void eval_cosh(      e_float_backend<MyDigits10>& result,
                 const e_float_backend<MyDigits10>& x)
  {
    result.representation() = ef::cosh(x.crepresentation());
  }

  template<const std::int32_t MyDigits10>
  void eval_tanh(      e_float_backend<MyDigits10>& result,
                 const e_float_backend<MyDigits10>& x)
  {
    result.representation() = ef::tanh(x.crepresentation());
  }

  template<const std::int32_t MyDigits10>
  void eval_fmod(      e_float_backend<MyDigits10>& result,
                 const e_float_backend<MyDigits10>& x,
                 const e_float_backend<MyDigits10>& y)
  {
    if(y.crepresentation().iszero())
    {
      result.representation() = ef::zero();
    }
    else
    {
      // Calculate the fractional part of x such that:
      //   x = (integer_part * y) + fractional_part,
      // where
      //   |fractional_part| < |y|,
      // and fractional_part has the same sign as x.

      const e_float integer_part =
        ef::floor(x.crepresentation() / y.crepresentation());

      result.representation() =
        x.crepresentation() - (integer_part * y.crepresentation());

      if(x.crepresentation().isneg() != y.crepresentation().isneg())
      {
        result.representation() -= y.crepresentation();
      }
    }
  }

  template<const std::int32_t MyDigits10>
  void eval_pow(      e_float_backend<MyDigits10>& result,
                const e_float_backend<MyDigits10>& x,
                const e_float_backend<MyDigits10>& a)
  {
    result.representation() = ef::pow(x.crepresentation(), a.crepresentation());
  }

  } } // namespace boost::multiprecision

  namespace boost { namespace math { namespace policies {

  // Specialization of the precision structure.
  template<const std::int32_t MyDigits10,
           typename ThisPolicy,
           const boost::multiprecision::expression_template_option ExpressionTemplates>
  struct precision<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>,
                                                 ExpressionTemplates>,
                   ThisPolicy>
  {
    typedef typename ThisPolicy::precision_type precision_type;

    typedef digits2<((MyDigits10 + 1LL) * 1000LL) / 301LL> local_digits_2;

    typedef typename mpl::if_c
      <
        (   (local_digits_2::value <= precision_type::value)
         || (precision_type::value <= 0)),
        local_digits_2,
        precision_type
      >::type
    type;
  };

  } } } // namespaces boost::math::policies

  namespace std
  {
    template<const std::int32_t MyDigits10,
             const boost::multiprecision::expression_template_option ExpressionTemplates>
    class numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>,
                                                       ExpressionTemplates>>
    {
    public:
      BOOST_STATIC_CONSTEXPR bool is_specialized = true;
      BOOST_STATIC_CONSTEXPR bool is_signed      = true;
      BOOST_STATIC_CONSTEXPR bool is_integer     = false;
      BOOST_STATIC_CONSTEXPR bool is_exact       = false;
      BOOST_STATIC_CONSTEXPR bool is_bounded     = true;
      BOOST_STATIC_CONSTEXPR bool is_modulo      = false;
      BOOST_STATIC_CONSTEXPR bool is_iec559      = false;
      BOOST_STATIC_CONSTEXPR int  digits         = MyDigits10;
      BOOST_STATIC_CONSTEXPR int  digits10       = MyDigits10;
      BOOST_STATIC_CONSTEXPR int  max_digits10   = MyDigits10 + 1;

      BOOST_STATIC_CONSTEXPR std::int64_t max_exponent   = e_float::ef_max_exp;
      BOOST_STATIC_CONSTEXPR std::int64_t max_exponent10 = e_float::ef_max_exp10;
      BOOST_STATIC_CONSTEXPR std::int64_t min_exponent   = e_float::ef_min_exp;
      BOOST_STATIC_CONSTEXPR std::int64_t min_exponent10 = e_float::ef_min_exp10;

      BOOST_STATIC_CONSTEXPR int                     radix             = 10;
      BOOST_STATIC_CONSTEXPR std::float_round_style  round_style       = std::round_indeterminate;
      BOOST_STATIC_CONSTEXPR bool                    has_infinity      = true;
      BOOST_STATIC_CONSTEXPR bool                    has_quiet_NaN     = true;
      BOOST_STATIC_CONSTEXPR bool                    has_signaling_NaN = false;
      BOOST_STATIC_CONSTEXPR std::float_denorm_style has_denorm        = std::denorm_absent;
      BOOST_STATIC_CONSTEXPR bool                    has_denorm_loss   = false;
      BOOST_STATIC_CONSTEXPR bool                    traps             = false;
      BOOST_STATIC_CONSTEXPR bool                    tinyness_before   = false;

      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates> (min)        () { return boost::multiprecision::e_float_backend<MyDigits10>(ef::value_min()); }
      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates> (max)        () { return boost::multiprecision::e_float_backend<MyDigits10>(ef::value_max()); }
      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates> lowest       () { return boost::multiprecision::e_float_backend<MyDigits10>(ef::zero()); }
      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates> epsilon      () { return boost::multiprecision::e_float_backend<MyDigits10>(ef::value_eps()); }
      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates> round_error  () { return boost::multiprecision::e_float_backend<MyDigits10>(ef::half()); }
      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates> infinity     () { return boost::multiprecision::e_float_backend<MyDigits10>(ef::value_inf()); }
      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates> quiet_NaN    () { return boost::multiprecision::e_float_backend<MyDigits10>(ef::value_nan()); }
      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates> signaling_NaN() { return boost::multiprecision::e_float_backend<MyDigits10>(ef::zero()); }
      BOOST_STATIC_CONSTEXPR boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates> denorm_min   () { return boost::multiprecision::e_float_backend<MyDigits10>(ef::zero()); }
    };

    #ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION

    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::is_specialized;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::is_signed;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::is_integer;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::is_exact;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::is_bounded;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::is_modulo;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST bool std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::is_iec559;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST int  std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::digits;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST int  std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::digits10;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST int  std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::max_digits10;

    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST std::int64_t std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::max_exponent;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST std::int64_t std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::max_exponent10;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST std::int64_t std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::min_exponent;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST std::int64_t std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::min_exponent10;

    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST int                     std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::radix;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST std::float_round_style  std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::round_style;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::has_infinity;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::has_quiet_NaN;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::has_signaling_NaN;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST std::float_denorm_style std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::has_denorm;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::has_denorm_loss;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::traps;
    template<const std::int32_t MyDigits10, const boost::multiprecision::expression_template_option ExpressionTemplates> BOOST_CONSTEXPR_OR_CONST bool                    std::numeric_limits<boost::multiprecision::number<boost::multiprecision::e_float_backend<MyDigits10>, ExpressionTemplates>>::tinyness_before;

    #endif // !BOOST_NO_INCLASS_MEMBER_INITIALIZATION

  } // namespace std

#endif // E_FLOAT_BACKEND_2017_08_18_HPP_
