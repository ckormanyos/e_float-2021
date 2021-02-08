
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <vector>

#include <boost/e_float/e_float_functions.hpp>

#include <src/utility/util_dynamic_array.h>
#include <src/utility/util_lexical_cast.h>
#include <src/utility/util_numeric_cast.h>

namespace local
{
  const double value_log2(0.30102999566398119521373889472449302676819L);
}

const std::int64_t& gmp::e_float::max_exp2()
{
  static const std::int64_t val_max_exp2 =
    static_cast<std::int64_t>(static_cast<double>(ef_max_exp10) / local::value_log2);

  return val_max_exp2;
}

const std::int64_t& gmp::e_float::min_exp2()
{
  static const std::int64_t val_min_exp2 =
    static_cast<std::int64_t>(static_cast<double>(ef_min_exp10) / local::value_log2);

  return val_min_exp2;
}

gmp::e_float::e_float(const char* const s) : my_rop      (),
                                             my_fpclass  (ef_finite),
                                             my_prec_elem(ef_max_digits10)
{
  init();

  static_cast<void>(rd_string(s));
}

gmp::e_float::e_float(const std::string& str) : my_rop      (),
                                                my_fpclass  (ef_finite),
                                                my_prec_elem(ef_max_digits10)
{
  init();

  static_cast<void>(rd_string(str.c_str()));
}

gmp::e_float::e_float(const double mantissa,
                      const std::int64_t exponent) : my_rop      (),
                                                     my_fpclass  (ef_finite),
                                                     my_prec_elem(ef_max_digits10)
{
  init();

  using std::fabs;

  const bool mantissa_is_iszero = (fabs(mantissa) < ((std::numeric_limits<double>::min)() * 2.0));

  if(mantissa_is_iszero)
  {
    if(exponent == static_cast<std::int64_t>(0))
    {
      ::mpf_init_set_ui(my_rop, 1U);
    }
    else
    {
      ::mpf_init_set_ui(my_rop, 0U);
    }
  }
  else
  {
    ::mpf_init_set_ui(my_rop, 0U);

    operator =(e_float(mantissa));
    operator*=(e_float("1E" + Util::lexical_cast(exponent)));
  }
}

gmp::e_float::e_float(const ::mpf_t& op) : my_rop      (),
                                           my_fpclass  (ef_finite),
                                           my_prec_elem(ef_max_digits10)
{
  init();

  ::mpf_init_set(my_rop, op);
}

gmp::e_float::~e_float()
{
  if(my_rop[0]._mp_d != nullptr)
  {
    ::mpf_clear(my_rop);
  }
}

void gmp::e_float::from_unsigned_long_long(const unsigned long long u)
{
  if(u <= static_cast<unsigned long long>((std::numeric_limits<unsigned long>::max)()))
  {
    ::mpf_init_set_ui(my_rop, static_cast<unsigned long>(u));
  }
  else
  {
    ::mpf_init_set_str(my_rop, Util::lexical_cast(u).c_str(), 10);
  }
}

void gmp::e_float::from_long_double(const long double l)
{
  const bool b_neg = (l < static_cast<long double>(0.0));

  using std::isfinite;

  if(isfinite(static_cast<double>(l)) == 0)
  {
    using std::isnan;

    operator=(isnan(static_cast<double>(l)) ? my_value_nan() : ((!b_neg) ? my_value_inf() : -my_value_inf()));

    return;
  }

  const native_float_parts<long double> fb((!b_neg) ? l : -l);

  // Create an e_float from the fractional part of the
  // mantissa expressed as an unsigned long long.
  from_unsigned_long_long(fb.get_mantissa());

  // Scale the unsigned long long representation to the fractional
  // part of the long double and multiply with the base-2 exponent.
  const int p2 = fb.get_exponent() - (std::numeric_limits<long double>::digits - 1);

  if(p2 != 0)
  {
    operator*=(ef::pow2(static_cast<std::int64_t>(p2)));
  }

  if(b_neg)
  {
    ::mpf_neg(my_rop, my_rop);
  }
}

void gmp::e_float::precision(const std::int32_t prec_digits)
{
  const unsigned long int digits2_request =
    static_cast<unsigned long int>(static_cast<std::uint64_t>(static_cast<double>(prec_digits) / local::value_log2));

  const unsigned long int d2              =
    static_cast<unsigned long int>(my_default_prec);

  const unsigned long int digits2_set     =
    (std::min)(digits2_request, d2);

  my_prec_elem =
    static_cast<std::int32_t>(static_cast<std::int64_t>(static_cast<double>(digits2_set) * local::value_log2));

  ::mpf_set_prec_raw(my_rop, digits2_set);
}

gmp::e_float& gmp::e_float::operator+=(const e_float& v)
{
  if(isnan())
  {
    return *this;
  }

  if(isinf())
  {
    if(v.isinf() && (isneg() != v.isneg()))
    {
      *this = std::numeric_limits<e_float>::quiet_NaN();
    }

    return *this;
  }

  ::mpf_add(my_rop, my_rop, v.my_rop);

  // Check for overflow.
  long u_exp2_signed;
  static_cast<void>(::mpf_get_d_2exp(&u_exp2_signed, my_rop));

  if(   (u_exp2_signed   >=  std::numeric_limits<e_float>::max_exponent)
     && (ef::fabs(*this) >  (std::numeric_limits<e_float>::max)()))
  {
    const bool b_result_is_neg = isneg();

    *this = ((!b_result_is_neg) ?  std::numeric_limits<e_float>::infinity()
                                : -std::numeric_limits<e_float>::infinity());
  }

  return *this;
}

gmp::e_float& gmp::e_float::operator-=(const e_float& v)
{
  // Use *this - v = -(-*this + v).
  return (negate().operator+=(v)).negate();
}

gmp::e_float& gmp::e_float::operator*=(const e_float& v)
{
  const bool b_u_is_inf =   isinf();
  const bool b_v_is_inf = v.isinf();

  if(   (isnan()    || v.isnan())
     || (b_u_is_inf && v.iszero())
     || (b_v_is_inf &&   iszero())
    )
  {
    return *this = std::numeric_limits<e_float>::quiet_NaN();
  }

  if(b_u_is_inf || b_v_is_inf)
  {
    const bool b_result_is_neg = (isneg() != v.isneg());

    *this = ((!b_result_is_neg) ?  std::numeric_limits<e_float>::infinity()
                                : -std::numeric_limits<e_float>::infinity());

    return *this;
  }

  // Get the base-2 exponent of *this and v and...
  long u_exp2_signed;
  long v_exp2_signed;

  static_cast<void>(::mpf_get_d_2exp(&u_exp2_signed,   my_rop));
  static_cast<void>(::mpf_get_d_2exp(&v_exp2_signed, v.my_rop));

  // Check for overflow or underflow.
  const bool u_exp2_is_neg = (u_exp2_signed < static_cast<long>(0));
  const bool v_exp2_is_neg = (v_exp2_signed < static_cast<long>(0));

  if(u_exp2_is_neg == v_exp2_is_neg)
  {
    // Get the unsigned base-2 exponents of *this and v and...
    const std::int64_t u_exp2 = ((!u_exp2_is_neg) ? u_exp2_signed : -u_exp2_signed);
    const std::int64_t v_exp2 = ((!v_exp2_is_neg) ? v_exp2_signed : -v_exp2_signed);

    // Check the range of the upcoming multiplication.
    const bool b_result_is_out_of_range = (v_exp2 >= static_cast<long>(static_cast<long>(ef_max_exp) - u_exp2));

    if(b_result_is_out_of_range)
    {
      if(u_exp2_is_neg)
      {
        *this = ef::zero();
      }
      else
      {
        const bool b_result_is_neg = (isneg() != v.isneg());

        *this = ((!b_result_is_neg) ?  std::numeric_limits<e_float>::infinity()
                                    : -std::numeric_limits<e_float>::infinity());
      }

      return *this;
    }
  }

  // Multiply *this by v.
  ::mpf_mul(my_rop, my_rop, v.my_rop);

  return *this;
}

gmp::e_float& gmp::e_float::operator/=(const e_float& v)
{
  return operator*=(e_float(v).calculate_inv());
}

// TBD: This needs an overflow and underflow check.
gmp::e_float& gmp::e_float::add_unsigned_long_long(const unsigned long long n)
{
  if(n <= (std::numeric_limits<unsigned long>::max)())
  {
    ::mpf_add_ui(my_rop, my_rop, static_cast<unsigned long>(n));

    return *this;
  }
  else
  {
    return operator+=(e_float(n));
  }
}

// TBD: This needs an overflow and underflow check.
gmp::e_float& gmp::e_float::sub_unsigned_long_long(const unsigned long long n)
{
  if(n <= (std::numeric_limits<unsigned long>::max)())
  {
    ::mpf_sub_ui(my_rop, my_rop, static_cast<unsigned long>(n));
    return *this;
  }
  else
  {
    return operator+=(e_float(n));
  }
}

gmp::e_float& gmp::e_float::mul_unsigned_long_long(const unsigned long long n)
{
  // Multiply *this with a constant unsigned long long.

  const bool b_u_is_inf  = isinf();
  const bool b_n_is_zero = (n == static_cast<std::int32_t>(0));

  if(isnan() || (b_u_is_inf && b_n_is_zero))
  {
    return (*this = std::numeric_limits<e_float>::quiet_NaN());
  }

  if(b_u_is_inf)
  {
    *this = ((!isneg()) ?  std::numeric_limits<e_float>::infinity()
                        : -std::numeric_limits<e_float>::infinity());

    return *this;
  }

  if(n > static_cast<unsigned long long>((std::numeric_limits<unsigned long>::max)()))
  {
    operator*=(e_float(n));
  }
  else
  {
    ::mpf_mul_ui(my_rop, my_rop, static_cast<unsigned long>(n));
  }

  return *this;
}

gmp::e_float& gmp::e_float::div_unsigned_long_long(const unsigned long long n)
{
  if(isnan())
  {
    return *this;
  }

  if(isinf())
  {
    *this = ((!isneg()) ?  std::numeric_limits<e_float>::infinity()
                        : -std::numeric_limits<e_float>::infinity());
    return *this;
  }

  if(n == static_cast<std::int32_t>(0))
  {
    // Divide by 0.
    if(iszero())
    {
      return (*this = std::numeric_limits<e_float>::quiet_NaN());
    }
    else
    {
      *this = ((!isneg()) ?  std::numeric_limits<e_float>::infinity()
                          : -std::numeric_limits<e_float>::infinity());

      return *this;
    }
  }

  if(iszero())
  {
    return *this;
  }

  if(n > static_cast<unsigned long long>((std::numeric_limits<unsigned long>::max)()))
  {
    operator/=(e_float(n));
  }
  else
  {
    ::mpf_div_ui(my_rop, my_rop, static_cast<unsigned long>(n));
  }

  // Check for underflow.
  long u_exp2_signed;
  static_cast<void>(::mpf_get_d_2exp(&u_exp2_signed, my_rop));

  if(   (u_exp2_signed   <=  std::numeric_limits<e_float>::min_exponent)
     && (ef::fabs(*this) <  (std::numeric_limits<e_float>::min)()))
  {
    return (*this = ef::zero());
  }

  return *this;
}

gmp::e_float& gmp::e_float::calculate_inv()
{
  // Compute the inverse of *this.

  bool b_result_is_neg = isneg();

  if(iszero())
  {
    *this = ((!b_result_is_neg) ?  std::numeric_limits<e_float>::infinity()
                                : -std::numeric_limits<e_float>::infinity());

    return *this;
  }

  if(isnan())
  {
    return *this;
  }

  if(isinf())
  {
    return (*this = ef::zero());
  }

  if(isone())
  {
    *this = ((!b_result_is_neg) ? ef::one() : -ef::one());

    return *this;
  }

  ::mpf_ui_div(my_rop, static_cast<unsigned long int>(1U), my_rop);

  return *this;
}

gmp::e_float& gmp::e_float::calculate_sqrt()
{
  // Compute the square root of *this.

  if(isneg() || !isfinite())
  {
    return (*this = std::numeric_limits<e_float>::quiet_NaN());
  }

  if(iszero() || isone())
  {
    return *this;
  }

  ::mpf_sqrt(my_rop, my_rop);

  return *this;
}

std::int32_t gmp::e_float::cmp(const e_float& v) const
{
  // Handle all non-finite cases.
  if((!isfinite()) || (!v.isfinite()))
  {
    // NaN can never equal NaN. Return an implementation-dependent
    // signed result. Also note that comparison of NaN with NaN
    // using operators greater-than or less-than is undefined.
    if(isnan() || v.isnan())
    {
      return (isnan() ? static_cast<std::int32_t>(1)
                      : static_cast<std::int32_t>(-1));
    }

    if(isinf() && v.isinf())
    {
      // Both *this and v are infinite. They are equal if they have the same sign.
      // Otherwise, *this is less than v if and only if *this is negative.
      return ((isneg() == v.isneg()) ? static_cast<std::int32_t>(0)
                                     : (isneg() ? static_cast<std::int32_t>(-1)
                                                : static_cast<std::int32_t>(+1)));
    }

    if(isinf())
    {
      // *this is infinite, but v is finite.
      // So negative infinite *this is less than any finite v.
      // Whereas positive infinite *this is greater than any finite v.
      return (isneg() ? static_cast<std::int32_t>(-1)
                      : static_cast<std::int32_t>(+1));
    }
    else
    {
      // *this is finite, and v is infinite.
      // So any finite *this is greater than negative infinite v.
      // Whereas any finite *this is less than positive infinite v.
      return (v.isneg() ? static_cast<std::int32_t>(+1)
                        : static_cast<std::int32_t>(-1));
    }
  }

  // And now handle all *finite* cases.
  if(iszero() && v.iszero())
  {
    return static_cast<std::int32_t>(0);
  }
  else
  {
    const int result = ::mpf_cmp(my_rop, v.my_rop);

    if     (result > 0) { return static_cast<std::int32_t>( 1); }
    else if(result < 0) { return static_cast<std::int32_t>(-1); }
    else                { return static_cast<std::int32_t>( 0); }
  }
}

bool gmp::e_float::iszero() const
{
  return (::mpf_sgn(my_rop) == 0);
}

bool gmp::e_float::isone() const
{
  // Check if the value of *this is identically 1 or very close to 1.
  return (isint() && (cmp(ef::one()) == static_cast<std::int32_t>(0)));
}

bool gmp::e_float::isint() const
{
  // Check if the value of *this is pure integer or very close to pure integer.
  return (::mpf_integer_p(my_rop) != 0);
}

bool gmp::e_float::isneg() const
{
  if(isinf())
  {
    return (my_fpclass == ef_inf_neg);
  }
  else
  {
    return (::mpf_sgn(my_rop) < 0);
  }
}

const gmp::e_float& gmp::e_float::my_value_nan() const
{
  static const e_float val_qnan(ef_NaN);

  return val_qnan;
}

const gmp::e_float& gmp::e_float::my_value_inf() const
{
  static const e_float val_inf(ef_inf_pos);

  return val_inf;
}

e_float& gmp::e_float::operator=(const e_float& v)
{
  if(this != &v)
  {
    my_fpclass   = v.my_fpclass;
    my_prec_elem = v.my_prec_elem;

    ::mpf_set         (my_rop, v.my_rop);
    ::mpf_set_prec_raw(my_rop, static_cast<unsigned long>(static_cast<std::uint64_t>(static_cast<double>(my_prec_elem) / local::value_log2)));
  }

  return *this;
}

// Move assignment operator.
e_float& gmp::e_float::operator=(e_float&& v)
{
  my_fpclass   = v.my_fpclass;
  my_prec_elem = v.my_prec_elem;

  ::mpf_set         (my_rop, v.my_rop);
  ::mpf_set_prec_raw(my_rop, static_cast<unsigned long>(static_cast<std::uint64_t>(static_cast<double>(my_prec_elem) / local::value_log2)));

  return *this;
}

void gmp::e_float::extract_parts(double& mantissa, std::int64_t& exponent) const
{
  const bool b_neg = isneg();

  long n2;
  const double d2    = ::mpf_get_d_2exp(&n2, (ef::fabs(*this)).my_rop);
  const double x_exp = static_cast<double>(static_cast<double>(n2) * local::value_log2);

  const double  x_exp_integer_part = static_cast<double>(static_cast<long>(x_exp));
  const double  x_exp_decimal_part = static_cast<double>(x_exp - x_exp_integer_part);

  double m = d2 * ::pow(10.0, x_exp_decimal_part);
  std::int64_t  e = static_cast<std::int64_t>(x_exp_integer_part);

  if(m < 1.0)
  {
    m *= 10.0;
    e -= static_cast<std::int64_t>(1);
  }

  mantissa = ((!b_neg) ? m : -m);
  exponent = e;
}

double gmp::e_float::extract_double() const
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

  const double dx = ::mpf_get_d(xx.my_rop);

  return ((!b_neg) ? dx : -dx);
}

long double gmp::e_float::extract_long_double() const
{
  // Returns the long double conversion of a e_float.

  const bool b_neg = isneg();

  // Check for non-normal e_float.
  if((!isfinite()))
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

  std::stringstream ss;

  ss << std::setprecision(static_cast<std::streamsize>(std::numeric_limits<long double>::digits10 + (2 + 1)))
     << std::scientific
     << *this;

  long double ld;
  ss >> ld;

  return ld;
}

signed long long gmp::e_float::extract_signed_long_long() const
{
  const bool b_neg = isneg();

  // Make a rounded copy.
  e_float xr = *this;

  if(isint())
  {
    ((!b_neg) ? xr += ef::half() : xr -= ef::half());
  }

  const e_float nx = ef::fabs(xr.extract_integer_part());

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
    return ((!b_neg) ? static_cast<signed long long>(+1)
                     : static_cast<signed long long>(-1));
  }

  // Extract a signed long long-type string from e_float.
  static const char c0 = static_cast<char>('\0');
  std::vector<char> str(64U, c0);
  mp_exp_t p10;

  const char* dummy_char =
    ::mpf_get_str(&str[0U],
                  &p10,
                  10,
                  str.size() - 1U,
                  nx.my_rop);

  static_cast<void>(dummy_char);

  std::string str_sll(static_cast<std::size_t>(p10), static_cast<char>('0'));

  std::copy(str.cbegin(),
            std::find(str.cbegin(), str.cend(), c0),
            str_sll.begin());

  // Get the signed long long result.
  const signed long long n = Util::numeric_cast<signed long long>(str_sll);

  return ((!b_neg) ? n : -n);
}

unsigned long long gmp::e_float::extract_unsigned_long_long() const
{
  if(isneg())
  {
    return static_cast<unsigned long long>(extract_signed_long_long());
  }

  // Make a rounded copy.
  e_float xr = *this;

  if(isint())
  {
    xr += ef::half();
  }

  const e_float nx = xr.extract_integer_part();

  if(nx > ef::unsigned_long_long_max())
  {
    return (std::numeric_limits<unsigned long long>::max)();
  }
  
  if(nx < ef::one())
  {
    return static_cast<unsigned long long>(0U);
  }

  if(nx.isone())
  {
    return static_cast<unsigned long long>(1U);
  }

  // Extract an unsigned long long-type string from e_float.
  static const char c0 = static_cast<char>('\0');
  std::vector<char> str(64U, c0);
  mp_exp_t p10;

  static_cast<void>(::mpf_get_str(&str[0], &p10, 10, str.size() - 1U, nx.my_rop));

  std::string str_ull(static_cast<std::size_t>(p10), static_cast<char>('0'));

  std::copy(str.cbegin(),
            std::find(str.cbegin(), str.cend(), c0),
            str_ull.begin());

  // Get the unsigned long long result.
  const unsigned long long n = Util::numeric_cast<unsigned long long>(str_ull);

  return n;
}

gmp::e_float gmp::e_float::extract_integer_part() const
{
  const bool b_neg = isneg();

  const e_float xx = ef::fabs(*this);

  e_float nx(xx);
  ::mpf_floor(nx.my_rop, xx.my_rop);

  return ((!b_neg) ? nx : -nx);
}

gmp::e_float gmp::e_float::extract_decimal_part() const
{
  const bool b_neg = isneg();

  const e_float xx = ef::fabs(*this);

  const e_float dx = xx - xx.extract_integer_part();

  return ((!b_neg) ? dx : -dx);
}

std::int64_t gmp::e_float::get_order_exact() const
{
  // Get the order-10 of the e_float. This is done using a partial
  // string extraction with 10 decimal digits.

  // Create a format string for 10-digits and scientific notation.
  std::string str_fmt = std::string("%.10Fe");

  // Get the ten digits.
  util::dynamic_array<char> buf(64U);

  static_cast<void>(gmp_sprintf(buf.data(), str_fmt.c_str(), my_rop));

  const std::string str = std::string(buf.data());

  // Extract the base-10 exponent.
  const std::size_t pos_letter_e = str.rfind(static_cast<char>('e'));

  const std::int64_t my_exp = ((pos_letter_e != std::string::npos) ? Util::numeric_cast<std::int64_t>(static_cast<const char* const>(str.c_str() + (pos_letter_e + 1U)))
                                                            : static_cast<std::int64_t>(0));

  return my_exp;
}

std::int64_t gmp::e_float::get_order_fast() const
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

    const double d2    = ::mpf_get_d_2exp(&n2, xx.my_rop);
    const double lg10x = static_cast<double>(log10(d2) + (static_cast<double>(n2) * local::value_log2));

    return ((lg10x < 0.0) ? static_cast<std::int64_t>(lg10x - 0.5)
                          : static_cast<std::int64_t>(lg10x + 0.5));
  }
}

void gmp::e_float::get_output_string(std::string& str, std::int64_t& the_exp, const std::size_t number_of_digits) const
{
  // Obtain the raw digits from the scientific notation string.
  // In other words, first obtain the string in scientific notation,
  // then reduce it to raw digits (perhaps this can be improved).

  static_cast<void>(the_exp);

  // Create a format string such as "%+.99Fe" in order to extract 100 digits
  // in scientific notation with the lowercase and noshowpos flags.
  const std::size_t the_number_of_digits_scientific = static_cast<std::size_t>((std::max)(number_of_digits, static_cast<std::size_t>(1U)) - static_cast<std::size_t>(1U));

  const std::string str_fmt = std::string("%.") + (Util::lexical_cast(the_number_of_digits_scientific) + "Fe");

  // Get the string representation of the e_float in scientific notation (lowercase, noshowpos).
  util::dynamic_array<char> buf(static_cast<std::size_t>(e_float::ef_max_digits10 + 32));

  static_cast<void>(gmp_sprintf(buf.data(), str_fmt.c_str(), my_rop));

  str = std::string(buf.data());

  // Erase the negative sign, if present.
  if(str.at(0U) == static_cast<char>('-'))
  {
    str.erase(str.cbegin(), str.cbegin() + 1U);
  }

  // Erase the exponent.
  const std::size_t pos_letter_e = str.rfind(static_cast<char>('e'));

  if(pos_letter_e != std::string::npos)
  {
    str.erase(str.cbegin() + pos_letter_e, str.cend());
  }

  // Erase the decimal point.
  const std::size_t pos_decimal_point = str.rfind(static_cast<char>('.'));

  if(pos_decimal_point != std::string::npos)
  {
    str.erase(str.cbegin() + pos_decimal_point, str.cbegin() + (pos_decimal_point + 1U));
  }
}

bool gmp::e_float::rd_string(const char* const s)
{
  std::string str(s);

  // Remove spaces and tabs
  static const char spc = static_cast<char>(' ');
  static const char tab = static_cast<char>('\t');

  str.erase(std::remove(str.begin(), str.end(), spc), str.end());
  str.erase(std::remove(str.begin(), str.end(), tab), str.end());

  // Get possible + sign and remove it
  
  if(   (!str.empty())
     &&   str.at(static_cast<std::size_t>(0U)) == static_cast<char>('+')
    )
  {
    str.erase(static_cast<std::size_t>(0U),
              static_cast<std::size_t>(1U));
  }

  // Get possible - sign and remove it
  
  bool b_negate = false;

  if(   (!str.empty())
     &&   str.at(static_cast<std::size_t>(0U)) == static_cast<char>('-')
    )
  {
    b_negate = true;
    str.erase(static_cast<std::size_t>(0U),
              static_cast<std::size_t>(1U));
  }

  // Remove leading zeros for all input types
  while(   (!str.empty())
        &&   str.at(static_cast<std::size_t>(0U)) == static_cast<char>('0')
       )
  {
    str.erase(static_cast<std::size_t>(0U), static_cast<std::size_t>(1U));
  }

  // Scale a very long pure integer input string.
  // Convert to a string with a decimal point and exponent.

  const std::string::const_iterator it =
    std::find_if(str.cbegin(),
                 str.cend(),
                 [](const char& c) -> bool
                 {
                   return (   (c == static_cast<char>('e'))
                           || (c == static_cast<char>('E'))
                           || (c == static_cast<char>('.')));
                 });

  const bool is_pure_integer = (it == str.cend());

  bool b_scaled = false;

  if(is_pure_integer && (str.length() > static_cast<std::size_t>(ef::tolerance())))
  {
    b_scaled = true;

    const std::size_t exp = static_cast<std::size_t>(str.length() - static_cast<std::size_t>(1U));

    const std::string str_exp = "E" + Util::lexical_cast(exp);

    str = str.substr(static_cast<std::size_t>(0U),
                     static_cast<std::size_t>(static_cast<std::size_t>(ef::tolerance()) - 1U));

    str.insert(static_cast<std::size_t>(1U), ".");

    str += str_exp;
  }

  // Set the e_float value.
  const std::int32_t n_set_result = static_cast<std::int32_t>(::mpf_init_set_str(my_rop, str.c_str(), 10));

  if(b_negate)
  {
    negate();
  }

  return (n_set_result == static_cast<std::int32_t>(0));
}
