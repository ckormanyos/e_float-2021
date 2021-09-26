
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <algorithm>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <iomanip>
#include <sstream>

#include <e_float/e_float_functions.h>

#include <utility/util_dynamic_array.h>
#include <utility/util_lexical_cast.h>
#include <utility/util_numeric_cast.h>

namespace local
{
  constexpr double d_log2()
  {
    return double(0.30102999566398119521373889472449302676819L);
  }
}

mpfr::e_float::e_float(const char* s)          { init(); static_cast<void>(rd_string(s)); }
mpfr::e_float::e_float(const std::string& str) { init(); static_cast<void>(rd_string(str.c_str())); }

mpfr::e_float::e_float(const double mantissa, const std::int64_t exponent)
{
  init();

  using std::fabs;

  const bool mantissa_is_iszero = (fabs(mantissa) < ((std::numeric_limits<double>::min)() * 2.0));

  if(mantissa_is_iszero)
  {
    if(exponent == static_cast<std::int64_t>(0))
    {
      mpfr_init_set(my_rop, (ef::one()).my_rop, GMP_RNDN);
    }
    else
    {
      mpfr_init_set(my_rop, (ef::zero()).my_rop, GMP_RNDN);
    }
  }
  else
  {
    mpfr_init_set(my_rop, (ef::zero()).my_rop, GMP_RNDN);

    operator =(e_float(mantissa));
    operator*=(e_float("1E" + Util::lexical_cast(exponent)));
  }
}

mpfr::e_float::e_float(std::initializer_list<std::uint32_t> limb_values,
                       const std::int64_t e,
                       const bool is_neg)
{
  std::string str;

  if(is_neg)
  {
    str.push_back('-');
  }

  auto it = limb_values.begin();

  if(limb_values.size() > 0U)
  {
    std::stringstream strm;

    strm << *it;

    ++it;

    str += strm.str();
  }

  if(limb_values.size() > 1U)
  {
    str.push_back('.');

    for( ; it != limb_values.end(); ++it)
    {
      std::stringstream strm;

      strm << std::setw(8) << std::setfill('0') << *it;

      str += strm.str();
    }
  }

  if(e != 0)
  {
    std::stringstream strm;

    strm << e;

    str += "e" + strm.str();
  }

  init();

  static_cast<void>(rd_string(str.c_str()));
}

mpfr::e_float::~e_float()
{
  ::mpfr_clear(my_rop);
}

void mpfr::e_float::from_unsigned_long_long(const unsigned long long u)
{
  if(u <= static_cast<unsigned long long>((std::numeric_limits<unsigned long>::max)()))
  {
    mpfr_init_set_ui(my_rop, static_cast<unsigned long>(u), GMP_RNDN);
  }
  else
  {
    static_cast<void>(::mpfr_init_set_str(my_rop, Util::lexical_cast(u).c_str(), 10, GMP_RNDN));
  }
}

void mpfr::e_float::from_long_double(const long double l)
{
  mpfr_init_set_ld(my_rop, l, GMP_RNDN);
}

const mpfr::e_float& mpfr::e_float::my_value_nan() const
{
  static const e_float val_qnan(ef::sqrt(e_float(-1)));

  return val_qnan;
}

const mpfr::e_float& mpfr::e_float::my_value_inf() const
{
  static const e_float val_inf(ef::one() / ef::zero());

  return val_inf;
}

mpfr::e_float& mpfr::e_float::operator+=(const e_float& v)
{
  static_cast<void>(::mpfr_add(my_rop, my_rop, v.my_rop, GMP_RNDN));

  return *this;
}

mpfr::e_float& mpfr::e_float::operator-=(const e_float& v)
{
  static_cast<void>(::mpfr_sub(my_rop, my_rop, v.my_rop, GMP_RNDN));

  return *this;
}

mpfr::e_float& mpfr::e_float::operator*=(const e_float& v)
{
  static_cast<void>(::mpfr_mul(my_rop, my_rop, v.my_rop, GMP_RNDN));

  return *this;
}

mpfr::e_float& mpfr::e_float::operator/=(const e_float& v)
{
  static_cast<void>(::mpfr_div(my_rop, my_rop, v.my_rop, GMP_RNDN));

  return *this;
}

mpfr::e_float& mpfr::e_float::add_unsigned_long_long(const unsigned long long n)
{
  if(n > static_cast<unsigned long long>((std::numeric_limits<unsigned long>::max)()))
  {
    operator+=(e_float(n));
  }
  else
  {
    static_cast<void>(::mpfr_add_ui(my_rop, my_rop, static_cast<unsigned long>(n), GMP_RNDN));
  }

  return *this;
}

mpfr::e_float& mpfr::e_float::sub_unsigned_long_long(const unsigned long long n)
{
  if(n > static_cast<unsigned long long>((std::numeric_limits<unsigned long>::max)()))
  {
    operator-=(e_float(n));
  }
  else
  {
    static_cast<void>(::mpfr_sub_ui(my_rop, my_rop, static_cast<unsigned long>(n), GMP_RNDN));
  }

  return *this;
}

mpfr::e_float& mpfr::e_float::mul_unsigned_long_long(const unsigned long long n)
{
  if(n > static_cast<unsigned long long>((std::numeric_limits<unsigned long>::max)()))
  {
    operator*=(e_float(n));
  }
  else
  {
    static_cast<void>(::mpfr_mul_ui(my_rop, my_rop, static_cast<unsigned long>(n), GMP_RNDN));
  }

  return *this;
}

mpfr::e_float& mpfr::e_float::div_unsigned_long_long(const unsigned long long n)
{
  if(n > static_cast<unsigned long long>((std::numeric_limits<unsigned long>::max)()))
  {
    operator/=(e_float(n));
  }
  else
  {
    static_cast<void>(::mpfr_div_ui(my_rop, my_rop, static_cast<unsigned long>(n), GMP_RNDN));
  }

  return *this;
}

std::int32_t mpfr::e_float::cmp(const e_float& v) const
{
  // Handle all non-finite cases.
  if((!isfinite()) || (!v.isfinite()))
  {
    // NaN can never equal NaN. Return an implementation-dependent
    // signed result. Also note that comparison of NaN with NaN
    // using operators greater-than or less-than is undefined.
    if(isnan() || v.isnan()) { return (isnan() ? static_cast<std::int32_t>(1) : static_cast<std::int32_t>(-1)); }

    if(isinf() && v.isinf())
    {
      // Both *this and v are infinite. They are equal if they have the same sign.
      // Otherwise, *this is less than v if and only if *this is negative.
      return ((isneg() == v.isneg()) ? static_cast<std::int32_t>(0) : (isneg() ? static_cast<std::int32_t>(-1) : static_cast<std::int32_t>(1)));
    }

    if(isinf())
    {
      // *this is infinite, but v is finite.
      // So negative infinite *this is less than any finite v.
      // Whereas positive infinite *this is greater than any finite v.
      return (isneg() ? static_cast<std::int32_t>(-1) : static_cast<std::int32_t>(1));
    }
    else
    {
      // *this is finite, and v is infinite.
      // So any finite *this is greater than negative infinite v.
      // Whereas any finite *this is less than positive infinite v.
      return (v.isneg() ? static_cast<std::int32_t>(1) : static_cast<std::int32_t>(-1));
    }
  }

  // And now handle all *finite* cases.
  if(iszero() && v.iszero())
  {
    return static_cast<std::int32_t>(0);
  }
  else
  {
    return static_cast<std::int32_t>(::mpfr_cmp3(my_rop, v.my_rop, 1));
  }
}

mpfr::e_float& mpfr::e_float::calculate_sqrt()
{
  static_cast<void>(::mpfr_sqrt(my_rop, my_rop, GMP_RNDN));
  return *this;
}

mpfr::e_float& mpfr::e_float::calculate_inv()
{
  static_cast<void>(::mpfr_div(my_rop, ef::one().my_rop, my_rop, GMP_RNDN));
  return *this;
}

bool mpfr::e_float::isnan   () const { return  (::mpfr_nan_p    (my_rop)  != 0); }
bool mpfr::e_float::isinf   () const { return  (::mpfr_inf_p    (my_rop)  != 0); }
bool mpfr::e_float::isfinite() const { return  ((!isnan()) && (!isinf())); }
bool mpfr::e_float::isone   () const { return ((::mpfr_integer_p(my_rop)  != 0) && (::mpfr_get_si(my_rop, GMP_RNDN) == static_cast<unsigned long>(1UL))); }
bool mpfr::e_float::isint   () const { return  (::mpfr_integer_p(my_rop)  != 0); }
bool mpfr::e_float::isneg   () const { return  (::mpfr_sgn      (my_rop)  <  0); }

bool mpfr::e_float::iszero() const
{
  return (::mpfr_zero_p(my_rop) != 0);
}

void mpfr::e_float::extract_parts(double& mantissa, std::int64_t& exponent) const
{
  const bool b_neg = isneg();

  long n2;
  const double d2    = ::mpfr_get_d_2exp(&n2, (ef::fabs(*this)).my_rop, GMP_RNDN);
  const double x_exp = static_cast<double>(static_cast<double>(n2) * local::d_log2());

  const double  x_exp_integer_part = static_cast<double>(static_cast<long>(x_exp));
  const double  x_exp_decimal_part = static_cast<double>(x_exp - x_exp_integer_part);

  using std::pow;

  double m = d2 * pow(10.0, x_exp_decimal_part);
  std::int64_t  e = static_cast<std::int64_t>(x_exp_integer_part);

  if(m < 1.0)
  {
    m *= 10.0;
    e -= static_cast<std::int64_t>(1);
  }

  mantissa = ((!b_neg) ? m : -m);
  exponent = e;
}

double mpfr::e_float::extract_double() const
{
  const bool b_neg = isneg();

  // Check for non-normal e_float.
  if(!isfinite())
  {
    if(isnan())
    {
      return std::numeric_limits<double>::quiet_NaN();
    }
    else
    {
      return ((!b_neg) ?  std::numeric_limits<double>::infinity()
                       : -std::numeric_limits<double>::infinity());
    }
  }

  const e_float xx(ef::fabs(*this));

  // Check for zero e_float.
  if(iszero() || (xx < ef::double_min()))
  {
    return 0.0;
  }

  // Check if e_float exceeds the maximum of double.
  if(xx > ef::double_max())
  {
    return ((!b_neg) ?  std::numeric_limits<double>::infinity()
                     : -std::numeric_limits<double>::infinity());
  }

  const double dx = ::mpfr_get_d(xx.my_rop, GMP_RNDN);

  return ((!b_neg) ? dx : -dx);
}

long double mpfr::e_float::extract_long_double() const
{
  const bool b_neg = isneg();

  // Check for non-normal e_float.
  if(!isfinite())
  {
    if(isnan())
    {
      return std::numeric_limits<long double>::quiet_NaN();
    }
    else
    {
      return ((!b_neg) ?  std::numeric_limits<long double>::infinity()
                       : -std::numeric_limits<long double>::infinity());
    }
  }

  const e_float xx(ef::fabs(*this));

  // Check for zero e_float.
  if(iszero() || (xx < ef::long_double_min()))
  {
    return static_cast<long double>(0.0);
  }

  // Check if e_float exceeds the maximum of double.
  if(xx > ef::long_double_max())
  {
    return ((!b_neg) ?  std::numeric_limits<long double>::infinity()
                     : -std::numeric_limits<long double>::infinity());
  }

  const long double ldx = ::mpfr_get_ld(xx.my_rop, GMP_RNDN);

  return ((!b_neg) ? ldx : -ldx);
}

signed long long mpfr::e_float::extract_signed_long_long() const
{
  const bool b_neg = isneg();

  const e_float nx = ef::fabs(*this);

  if(nx > ef::signed_long_long_max())
  {
    return ((!b_neg) ?  (std::numeric_limits<signed long long>::max)()
                     : -(std::numeric_limits<signed long long>::max)());
  }
  
  if(nx < ef::one())
  {
    return static_cast<signed long long>(0);
  }

  if(nx.isone())
  {
    return ((!b_neg) ? static_cast<signed long long>(1) : static_cast<signed long long>(-1));
  }

  util::dynamic_array<char> str(64U);

  mp_exp_t p10;

  static_cast<void>(::mpfr_get_str(str.data(), &p10, 10, str.size() - 1U, nx.my_rop, GMP_RNDN));

  std::string str_sll(static_cast<std::size_t>(p10), static_cast<char>('0'));

  std::copy(str.cbegin(),
            str.cbegin() + str_sll.size(),
            str_sll.begin());

  const signed long long n = Util::numeric_cast<signed long long>(str_sll);

  return ((!b_neg) ? n : -n);
}

unsigned long long mpfr::e_float::extract_unsigned_long_long() const
{
  if(isneg())
  {
    return static_cast<unsigned long long>(extract_signed_long_long());
  }

  if(*this > ef::unsigned_long_long_max())
  {
    return (std::numeric_limits<unsigned long long>::max)();
  }

  if(*this < ef::one())
  {
    return static_cast<unsigned long long>(0U);
  }

  if(isone())
  {
    return static_cast<unsigned long long>(1U);
  }

  util::dynamic_array<char> str(64U);

  mp_exp_t p10;

  static_cast<void>(::mpfr_get_str(str.data(), &p10, 10, str.size() - 1U, my_rop, GMP_RNDN));

  std::string str_ull(static_cast<std::size_t>(p10), static_cast<char>('0'));

  std::copy(str.cbegin(),
            str.cbegin() + str_ull.size(),
            str_ull.begin());

  const unsigned long long n = Util::numeric_cast<unsigned long long>(str_ull);

  return n;
}

mpfr::e_float mpfr::e_float::extract_integer_part() const
{
  const bool b_neg = isneg();

  e_float nx;

  ::mpfr_floor(nx.my_rop, (ef::fabs(*this)).my_rop, GMP_RNDN);

  return ((!b_neg) ? nx : -nx);
}

mpfr::e_float mpfr::e_float::extract_decimal_part() const
{
  const bool b_neg = isneg();

  const e_float xx = ef::fabs(*this);

  const e_float dx = xx - xx.extract_integer_part();

  return ((!b_neg) ? dx : -dx);
}

std::int64_t mpfr::e_float::get_order_exact() const
{
  // Get the order-10 of the e_float. This is done using a partial
  // string extraction with 10 decimal digits.

  // Create a format string for 10-digits and scientific notation.
  std::string str_fmt = std::string("%.10RNe");

  // Get the ten digits.
  util::dynamic_array<char> buf(64U);

  ::mpfr_sprintf(buf.data(), str_fmt.c_str(), my_rop);

  const std::string str = std::string(buf.data());

  // Extract the base-10 exponent.
  const std::size_t pos_letter_e = str.rfind(static_cast<char>('e'));

  const std::int64_t my_exp =
    ((pos_letter_e != std::string::npos)
      ? Util::numeric_cast<std::int64_t>(static_cast<const char*>(str.c_str() + (pos_letter_e + 1U)))
      : static_cast<std::int64_t>(0));

  return my_exp;
}

std::int64_t mpfr::e_float::get_order_fast() const
{
  const e_float xx = ef::fabs(*this);

  if(xx.iszero() || xx.isone())
  {
    return static_cast<std::int64_t>(0);
  }
  else
  {
    signed long int n2;

    using std::log10;

    const double d2    = ::mpfr_get_d_2exp(&n2, xx.my_rop, GMP_RNDN);
    const double lg10x = static_cast<double>(log10(d2) + (static_cast<double>(n2) * local::d_log2()));

    return ((lg10x < 0.0) ? static_cast<std::int64_t>(lg10x - 0.5)
                          : static_cast<std::int64_t>(lg10x + 0.5));
  }
}

void mpfr::e_float::get_output_string(std::string& str, std::int64_t& the_exp, const std::size_t number_of_digits) const
{
  static_cast<void>(the_exp);

  // Create a format string such as "%+.99RNe" in order to extract 100 digits
  // in scientific notation with the lowercase and noshowpos flags.
  const std::size_t the_number_of_digits_scientific = static_cast<std::size_t>((std::max)(number_of_digits, static_cast<std::size_t>(1U)) - static_cast<std::size_t>(1U));

  const std::string str_fmt =
       std::string("%.")
    + (Util::lexical_cast(the_number_of_digits_scientific) + "RNe");

  // Get the string representation of the e_float in scientific notation (lowercase, noshowpos).
  util::dynamic_array<char> buf(static_cast<std::size_t>(e_float::ef_max_digits10 + 32));

  ::mpfr_sprintf(buf.data(), str_fmt.c_str(), my_rop);

  str = std::string(buf.data());

  // Obtain the raw digits from the scientific notation string.

  // TBD: Well, this is a bit silly. First get the string in
  // scientific notation, then reduce it to raw digits.
  // Perhaps this can be improved.
  // Get the raw digits from a string in scientific notation (lowercase, showpos).

  // Erase the negative sign, if present.
  if(str.at(0U) == static_cast<char>('-'))
  {
    str.erase(str.cbegin(), str.cbegin() + 1U);
  }

  // Erase the exponent.
  const std::size_t pos_letter_e = str.rfind(static_cast<char>('e'));

  if(pos_letter_e != std::string::npos)
  {
    str.erase(str.cbegin() + (std::string::difference_type) pos_letter_e, str.cend());
  }

  // Erase the decimal point.
  const std::size_t pos_decimal_point = str.rfind(static_cast<char>('.'));

  if(pos_decimal_point != std::string::npos)
  {
    str.erase(str.cbegin() + (std::string::difference_type)  pos_decimal_point,
              str.cbegin() + (std::string::difference_type) (pos_decimal_point + 1U));
  }
}

bool mpfr::e_float::rd_string(const char* const s) { return (::mpfr_init_set_str(my_rop, s, 10, GMP_RNDN) == 1); }

e_float mpfr::e_float::my_own_cbrt         (const e_float& x) { e_float res; static_cast<void>(::mpfr_cbrt (res.my_rop, x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_rootn        (const e_float& x, const std::uint32_t p)
                                                              { e_float res; static_cast<void>(::mpfr_root (res.my_rop, x.my_rop, static_cast<unsigned long int>(p), GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_exp          (const e_float& x) { e_float res; static_cast<void>(::mpfr_exp  (res.my_rop, x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_log          (const e_float& x) { e_float res; static_cast<void>(::mpfr_log  (res.my_rop, x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_sin          (const e_float& x) { e_float res; static_cast<void>(::mpfr_sin  (res.my_rop, x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_cos          (const e_float& x) { e_float res; static_cast<void>(::mpfr_cos  (res.my_rop, x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_tan          (const e_float& x) { e_float res; static_cast<void>(::mpfr_tan  (res.my_rop, x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_asin         (const e_float& x) { e_float res; static_cast<void>(::mpfr_asin (res.my_rop, x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_acos         (const e_float& x) { e_float res; static_cast<void>(::mpfr_acos (res.my_rop, x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_atan         (const e_float& x) { e_float res; static_cast<void>(::mpfr_atan (res.my_rop, x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_sinh         (const e_float& x) { e_float res; static_cast<void>(::mpfr_sinh (res.my_rop, x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_cosh         (const e_float& x) { e_float res; static_cast<void>(::mpfr_cosh (res.my_rop, x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_tanh         (const e_float& x) { e_float res; static_cast<void>(::mpfr_tanh (res.my_rop, x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_asinh        (const e_float& x) { e_float res; static_cast<void>(::mpfr_asinh(res.my_rop, x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_acosh        (const e_float& x) { e_float res; static_cast<void>(::mpfr_acosh(res.my_rop, x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_atanh        (const e_float& x) { e_float res; static_cast<void>(::mpfr_atanh(res.my_rop, x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_gamma        (const e_float& x) { e_float res; static_cast<void>(::mpfr_gamma(res.my_rop, x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_riemann_zeta (const e_float& x) { e_float res; static_cast<void>(::mpfr_zeta (res.my_rop, x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_cyl_bessel_jn(const std::int32_t n, const e_float& x)
                                                              { e_float res; static_cast<void>(::mpfr_jn(res.my_rop, static_cast<long>(n), x.my_rop, GMP_RNDN)); return res; }
e_float mpfr::e_float::my_own_cyl_bessel_yn(const std::int32_t n, const e_float& x)
                                                              { e_float res; static_cast<void>(::mpfr_yn(res.my_rop, static_cast<long>(n), x.my_rop, GMP_RNDN)); return res; }
