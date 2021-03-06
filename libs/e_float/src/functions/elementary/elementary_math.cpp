
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <algorithm>
#include <cmath>

#include <e_float/e_float_functions.h>

std::int32_t ef::max_iteration() { return static_cast<std::int32_t>(10000); }
std::int64_t ef::tolerance    () { return static_cast<std::int64_t>(e_float::ef_max_digits10 + (e_float::ef_max_digits10 / 10)); }

bool         ef::isnan    (const e_float& x) { return x.isnan(); }
bool         ef::isfinite (const e_float& x) { return x.isfinite(); }
bool         ef::isinf    (const e_float& x) { return x.isinf(); }
bool         ef::isneg    (const double x)   { return (x < 0.0); }
bool         ef::isneg    (const e_float& x) { return x.isneg(); }
e_float      ef::abs      (const e_float& x) { return ef::fabs(x); }
e_float      ef::real     (const e_float& x) { return x; }
e_float      ef::imag     (const e_float&)   { return ef::zero(); }
bool         ef::ispos    (const double x)   { return (!isneg(x)); }
bool         ef::ispos    (const e_float& x) { return (!x.isneg()); }
bool         ef::isint    (const e_float& x) { return x.isint(); }
bool         ef::isone    (const double x)   { using std::fabs; return (fabs(1.0 - x) < (std::numeric_limits<double>::min)() * 2); }
bool         ef::isone    (const e_float& x) { return x.isone(); }
bool         ef::iszero   (const double x)   { using std::fabs; return (fabs(x) < (std::numeric_limits<double>::min)() * 2); }
bool         ef::iszero   (const e_float& x) { return x.iszero(); }
double       ef::to_double(const double& x)  { return x; }
std::int64_t ef::order_of (const double x)   { using std::log10; return static_cast<std::int64_t>(static_cast<std::int32_t>(log10(x))); }
std::int64_t ef::order_of (const e_float& x) { return x.order(); }

e_float ef::fabs(const e_float& x)
{
  return (x.isneg() ? e_float(x).negate() : x);
}

e_float ef::floor(const e_float& x)
{
  if(!ef::isfinite(x) || ef::isint(x)) { return x; }

  return (ef::isneg(x) ? ef::integer_part(x - ef::one())
                       : ef::integer_part(x));
}

e_float ef::ceil(const e_float& x)
{
  if(!ef::isfinite(x) || ef::isint(x)) { return x; }

  return (ef::isneg(x) ? ef::integer_part(x)
                       : ef::integer_part(x + ef::one()));
}

std::int32_t ef::sgn(const e_float& x)
{
  if(ef::iszero(x))
  {
    return static_cast<std::int32_t>(0);
  }
  else
  {
    return (ef::isneg(x) ? static_cast<std::int32_t>(-1) : static_cast<std::int32_t>(1));
  }
}

e_float ef::ldexp(const e_float& v, int e)
{
  return v * ef::pow2(e);
}

e_float ef::frexp(const e_float& v, int* expon)
{
  double d;
  std::int64_t i;

  v.extract_parts(d, i);

  *expon = static_cast<int>(i);

  return v * ef::pow2(static_cast<std::int64_t>(-i));
}

e_float ef::fmod(const e_float& v1, const e_float& v2)
{
  const e_float n = (ef::isneg(v1) ? ef::ceil(v1 / v2) : ef::floor(v1 / v2));

  return v1 - (n * v2);
}

bool ef::isfinite(const double x)
{
  using std::isfinite;

  return isfinite(x);
}

bool ef::isnan(const double x)
{
  using std::isnan;

  return isnan(x);
}

double ef::to_double(const e_float& x)              { return x.extract_double(); }

std::int64_t ef::to_int64(const double x)           { return static_cast<std::int64_t>(x); }
std::int64_t ef::to_int64(const e_float& x)         { return static_cast<std::int64_t>(x.extract_signed_long_long()); }

bool ef::isint(const double x)
{
  static const double delta = (std::numeric_limits<double>::min)() * 2.0;

  const double xx = ::fabs(x);

  if((xx - ::floor(xx)) < delta)
  {
    return true;
  }
  else if((::ceil(xx) - xx) < delta)
  {
    return true;
  }
  else
  {
    return false;
  }
}

std::int32_t ef::to_int32(const double x)
{
  const std::int64_t n32_max = static_cast<std::int64_t>((std::numeric_limits<std::int32_t>::max)());
  const std::int64_t n32_min = static_cast<std::int64_t>((std::numeric_limits<std::int32_t>::min)());

  const std::int64_t n64 = ef::to_int64(x);

  return static_cast<std::int32_t>((std::min)((std::max)(n64, n32_min), n32_max));
}

std::int32_t ef::to_int32(const e_float& x)
{
  const std::int64_t n32_max = static_cast<std::int64_t>((std::numeric_limits<std::int32_t>::max)());
  const std::int64_t n32_min = static_cast<std::int64_t>((std::numeric_limits<std::int32_t>::min)());

  const std::int64_t n64 = ef::to_int64(x);

  return static_cast<std::int32_t>((std::min)((std::max)(n64, n32_min), n32_max));
}

void ef::to_parts(const e_float& x, double& mantissa, std::int64_t& exponent)
{
  x.extract_parts(mantissa, exponent);
}

e_float ef::integer_part(const e_float& x)
{
  return x.extract_integer_part();
}

e_float ef::decimal_part(const e_float& x)
{
  return x.extract_decimal_part();
}

bool ef::small_arg(const double x)
{
  static const double one_sixth = 1.0 / 6.0;
  static const double small_tol = ::pow(std::numeric_limits<double>::epsilon(), one_sixth);

  return (::fabs(x) < small_tol);
}

bool ef::small_arg(const e_float& x)
{
  static const double       lim_d = static_cast<double>(static_cast<std::int32_t>(ef::tolerance())) / 10.0;
  static const std::int64_t lim   = (std::max)(static_cast<std::int64_t>(lim_d), static_cast<std::int64_t>(6));

  return (x.order() < static_cast<std::int64_t>(-lim));
}

bool ef::large_arg(const double x)
{
  using std::fabs;
  using std::pow;

  static const double one_sixth = 1.0 / 6.0;
  static const double small_tol = pow(std::numeric_limits<double>::epsilon(), one_sixth);
  static const double large_tol = 1.0 / small_tol;

  return (fabs(x) > large_tol);
}

bool ef::large_arg(const e_float& x)
{
  static const double       lim_d = static_cast<double>(static_cast<std::int32_t>(ef::tolerance())) / 10.0;
  static const std::int64_t lim   = (std::max)(static_cast<std::int64_t>(lim_d), static_cast<std::int64_t>(6));

  return (x.order() > lim);
}

//bool ef::large_arg(const ef::complex<e_float>& z) { return ef::large_arg(z.real()); }

bool ef::near_one(const double x)      { return ef::small_arg(::fabs(1.0 - x)); }
bool ef::near_one(const e_float& x)    { return ef::small_arg(ef::fabs(ef::one() - x)); }
//bool ef::near_one(const ef::complex<e_float>& z) { return ef::near_one(z.real()) && ef::iszero(z.imag()); }

bool ef::near_int(const double x)
{
  if(ef::isint(x))
  {
    return true;
  }
  else
  {
    const double xx = ::fabs(x);

    if(ef::small_arg(xx - ::floor(xx)))
    {
      return true;
    }
    else if(ef::small_arg(::ceil(xx) - xx))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

bool ef::near_int(const e_float& x)
{
  if(ef::isint(x))
  {
    return true;
  }
  else
  {
    const e_float xx = ef::fabs(x);

    if(ef::small_arg(xx - ef::floor(xx)))
    {
      return true;
    }
    else if(ef::small_arg(ef::ceil(xx) - xx))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

//bool ef::near_int(const ef::complex<e_float>& z)
//{
//  if(ef::isint(z))
//  {
//    return true;
//  }
//  else
//  {
//    return ef::iszero(z.imag()) && ef::near_int(z.real());
//  }
//}
