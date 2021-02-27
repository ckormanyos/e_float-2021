
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <array>
#include <map>
#include <numeric>
#include <vector>

#include <e_float/e_float_functions.h>
#include <e_float/detail/e_float_detail_pown_template.h>

#include <utility/util_lexical_cast.h>

namespace ElementaryTrans_Series
{
  static e_float rootn_inv(const e_float& x, const std::int32_t p);
}

e_float ef::pow2(const std::int64_t p)
{
  if     (p <  -1) { return ef::pow(e_float( { UINT32_C(50000000) }, -8 ), -p); }
  else if(p == -1) { return e_float( { UINT32_C(50000000) }, -8 ); }
  else if(p ==  0) { return e_float( { UINT32_C(1) } ); }
  else if(p ==  1) { return e_float( { UINT32_C(2) } ); }
  else             { return ef::pow(e_float(2U), p); }
}

static e_float ElementaryTrans_Series::rootn_inv(const e_float& x, const std::int32_t p)
{
  // Compute the value of [1 / (rootn of x)] with n = p.

  // Generate the initial estimate using 1 / rootn.
  // Extract the mantissa and exponent for a "manual"
  // computation of the estimate.
  double        dd;
  std::int64_t  ne;

  ef::to_parts(x, dd, ne);

  // Adjust exponent and mantissa such that ne is an even power of p.
  while(ne % static_cast<std::int64_t>(p))
  {
    ++ne;
    dd /= 10.0;
  }
  
  // Estimate the one over the root using simple manipulations.
  const double one_over_rtn_d = ::pow(dd, -1.0 / static_cast<double>(p));

  // Set the result equal to the initial guess.
  e_float result(one_over_rtn_d, static_cast<std::int64_t>(-ne / p));

  static const std::int32_t double_digits10_minus_a_few = static_cast<std::int32_t>(static_cast<std::int32_t>(std::numeric_limits<double>::digits10) - static_cast<std::int32_t>(3));

  for(std::int32_t digits = double_digits10_minus_a_few; digits <= static_cast<std::int32_t>(ef::tolerance()); digits *= static_cast<std::int32_t>(2))
  {
    // Adjust precision of the terms.
    const std::int32_t new_prec = static_cast<std::int32_t>(digits * 2) + 10;

    result.precision(new_prec);

    // Perform the next iteration.
    e_float term = (((-ef::detail::pown_template(result, p) * x) + ef::one()) / p) + ef::one();

    term.precision(new_prec);

    result *= term;
  
  }

  result.precision(static_cast<std::int32_t>(ef::tolerance()));

  return result;
}

e_float ef::inv (const e_float& x) { return e_float(x).calculate_inv(); }
e_float ef::sqrt(const e_float& x) { return e_float(x).calculate_sqrt(); }

e_float ef::cbrt(const e_float& x)
{
  return ef::rootn(x, static_cast<std::int32_t>(3));
}

e_float ef::rootn(const e_float& x, const std::int32_t p)
{
  if(!ef::isfinite(x))
  {
    return std::numeric_limits<e_float>::quiet_NaN();
  }

  if(p < static_cast<std::int32_t>(0))
  {
    return ef::rootn(ef::one() / x, static_cast<std::int32_t>(-p));
  }

  if((p == static_cast<std::int32_t>(0)) || ef::isneg(x))
  {
    return std::numeric_limits<e_float>::quiet_NaN();
  }
  else if(p == static_cast<std::int32_t>(1))
  {
    return x;
  }
  else if(p == static_cast<std::int32_t>(2))
  {
    return ef::sqrt(x);
  }
  else if((p == static_cast<std::int32_t>(3)) && x.i_have_my_own_cbrt())
  {
    return e_float::my_own_cbrt(x);
  }

  const e_float rtn =  (x.i_have_my_own_rootn() ? e_float::my_own_rootn(x, static_cast<std::uint32_t>(p))
                                                : ElementaryTrans_Series::rootn_inv(x, p).calculate_inv());

  return rtn;
}

e_float ef::rootn_inverse(const e_float& x, const std::int32_t p)
{
  if(ef::isfinite(x) == false)
  {
    return std::numeric_limits<e_float>::quiet_NaN();
  }

  if(p < static_cast<std::int32_t>(0))
  {
    return detail::pown_template(x, static_cast<std::int32_t>(-p));
  }

  if((p == static_cast<std::int32_t>(0)) || ef::isneg(x))
  {
    return std::numeric_limits<e_float>::quiet_NaN();
  }
  else if(p == static_cast<std::int32_t>(1))
  {
    return x;
  }
  else if(p == static_cast<std::int32_t>(2))
  {
    return ef::one() / ef::sqrt(x);
  }

  const e_float rtn_inv =  (x.i_have_my_own_rootn() ? ef::one() / e_float::my_own_rootn(x, static_cast<std::uint32_t>(p))
                                                    : ElementaryTrans_Series::rootn_inv(x, p));

  return rtn_inv;
}

e_float ef::exp(const e_float& x)
{
  if(x.i_have_my_own_exp())
  {
    return e_float::my_own_exp(x);
  }

  // Handle special arguments.
  if(ef::isnan(x))
  {
    return std::numeric_limits<e_float>::quiet_NaN();
  }

  if(ef::isinf(x))
  {
    return ((!ef::isneg(x)) ? std::numeric_limits<e_float>::infinity() : ef::zero());
  }

  if(ef::iszero(x) || (x.order() < -ef::tolerance()))
  {
    return ef::one();
  }

  // Get local copy of argument and force it to be positive.
  const bool bo_x_is_neg = ef::isneg(x);

  const e_float xx = ((!bo_x_is_neg) ? x : -x);

  // Check the range of the argument.
  static const e_float maximum_arg_for_exp = std::numeric_limits<e_float>::max_exponent;

  if(xx > maximum_arg_for_exp)
  {
    // Overflow / underflow
    return ((!bo_x_is_neg) ? std::numeric_limits<e_float>::infinity() : ef::zero());
  }

  // Check for pure-integer arguments which can be either signed or unsigned.
  if(ef::isint(x))
  {
    return ef::detail::pown_template(ef::e(), ef::to_int64(x));
  }

  // The algorithm for exp has been taken from MPFUN.
  // exp(t) = [ (1 + r + r^2/2! + r^3/3! + r^4/4! ...)^p2 ] * 2^n
  // where p2 is a power of 2 such as 2048, r = t_prime / p2, and
  // t_prime = t - n*ln2, with n chosen to minimize the absolute
  // value of t_prime. In the resulting Taylor series, which is
  // implemented as a hypergeometric function, |r| is bounded by
  // ln2 / p2. For small arguments, no scaling is done.

  const bool b_scale = (xx.order() > static_cast<std::int64_t>(-4));

  // Compute the exponential series of the (possibly) scaled argument.
  e_float exp_series;

  if(b_scale)
  {
    // Compute 1 / ln2 as a warm-cached constant value.
    static const e_float one_over_ln2 = ef::one() / ef::ln2();

    const e_float nf = ef::integer_part(xx * one_over_ln2);

    // The scaling is 2^11 = 2048.
    const std::int32_t p2 = static_cast<std::int32_t>(std::uint32_t(1U) << 11);

    exp_series = ef::detail::pown_template(ef::hypergeometric_0f0((xx - (nf * ef::ln2())) / p2), static_cast<std::int64_t>(p2)) * ef::pow2(ef::to_int64(nf));
  }
  else
  {
    exp_series = ef::hypergeometric_0f0(xx);
  }

  return ((!bo_x_is_neg) ? exp_series : (ef::one() / exp_series));
}

namespace Log_Series
{
  static e_float AtOne(const e_float& x)
  {
    // This subroutine computes the series representation of Log[1 + x]
    // for small x without losing precision.

    // http://functions.wolfram.com/ElementaryFunctions/Log/26/01/01/

    return x * ef::hypergeometric_2f1( ef::one(), ef::one(), ef::two(), -x);
  }
}

e_float ef::log(const e_float& x)
{
  // Handle special arguments.
  if(ef::isnan(x) || ef::isneg(x) || ef::isinf(x))
  {
    return std::numeric_limits<e_float>::quiet_NaN();
  }

  if(x.i_have_my_own_log())
  {
    return e_float::my_own_log(x);
  }

  if(ef::iszero(x))
  {
    return -std::numeric_limits<e_float>::infinity();
  }

  if(ef::isone(x))
  {
    return ef::zero();
  }

  // Make a local copy
  e_float xx = x;

  // Compute the delta of the argument compared to one.
  const e_float x_minus_one  = xx - ef::one();

  if(ef::near_one(xx))
  {
    return Log_Series::AtOne(x_minus_one);
  }

  // For large arguments, the value will be broken into two parts
  // in order to facilitate the convergence of the Newton iteration.
  const bool b_correction = (   (xx.order() > static_cast<std::int64_t>(+1000))
                             || (xx.order() < static_cast<std::int64_t>(-1000)));

  e_float correction;

  if(b_correction)
  {
    // The argument xx is of the form a * 10^b.
    // It will be broken into two parts: log(a) + b * log(10).
    const bool b_neg_exp = xx.order() < static_cast<std::int64_t>(0);

    // Remove a large power of ten from the argument. But be sure to leave the argument
    // large enough (or small enough) to avoid entering the near-one range.
    const std::int64_t n_order   = xx.order();
    const std::int64_t n_exp     = !b_neg_exp ? n_order : -n_order;
    const std::int64_t delta_exp = static_cast<std::int64_t>(n_exp - static_cast<std::int64_t>(8));

    // Convert the scaling power of ten to a string and subsequently to an e_float.
    const e_float ef_delta_exp("1E" + Util::lexical_cast(delta_exp));

    !b_neg_exp ? xx /= ef_delta_exp : xx *= ef_delta_exp;

    correction  = ef::ln10() * e_float(delta_exp);

    if(b_neg_exp)
    {
      correction = -correction;
    }
  }

  using std::fabs;
  using std::log;
  using std::log10;
  using std::pow;

  // Generate the initial estimate using double precision log combined with
  // the exponent for a "manual" computation of the initial iteration estimate.

  static const double lg10_d = log(10.0);

  static const std::int64_t n32_min = static_cast<std::int64_t>((std::numeric_limits<std::int32_t>::min)());
  static const std::int64_t n32_max = static_cast<std::int64_t>((std::numeric_limits<std::int32_t>::max)());

  // computation of the estimate.
  double        dd;
  std::int64_t  ne;
  ef::to_parts(xx, dd, ne);

  const double nd =
    ((ne < static_cast<std::int64_t>(0)) ? static_cast<double>(static_cast<std::int32_t>((std::max)(ne, n32_min)))
                                         : static_cast<double>(static_cast<std::int32_t>((std::min)(ne, n32_max))));

  const double dlog = log(dd) + (nd * lg10_d);

  const double d10  = ((!ef::iszero(dlog)) ? log10(fabs(dlog)) + 0.5 : 0.0);

  const std::int64_t  p10  =  (ef::ispos(dlog)  ? static_cast<std::int64_t>(d10) : static_cast<std::int64_t>(-d10));

  e_float log_val   = ((!ef::iszero(dlog)) ? e_float(dlog / pow(10.0, static_cast<double>(static_cast<std::int32_t>(p10))), p10)
                      : x_minus_one);

  // Newton-Raphson iteration
  static const std::int32_t double_digits10_minus_one = static_cast<std::int32_t>(static_cast<std::int32_t>(std::numeric_limits<double>::digits10) - static_cast<std::int32_t>(1));

  for(std::int32_t digits = double_digits10_minus_one; digits <= static_cast<std::int32_t>(ef::tolerance()); digits *= static_cast<std::int32_t>(2))
  {
    // Adjust precision of the terms.
    log_val.precision(static_cast<std::int32_t>(digits * static_cast<std::int32_t>(2)));
         xx.precision(static_cast<std::int32_t>(digits * static_cast<std::int32_t>(2)));

    const e_float exp_minus_log = ef::exp(-log_val);

    log_val += (xx * exp_minus_log) - ef::one();
  }

  return ((!b_correction) ? log_val : log_val + correction);
}

e_float ef::log10(const e_float& x)                   { return ef::log(x) / ef::ln10(); }
e_float ef::loga (const e_float& a, const e_float& x) { return ef::log(x) / ef::log(a); }
e_float ef::log1p(const e_float& x)                   { return Log_Series::AtOne(x); }

e_float ef::log1p1m2(const e_float& x)
{
  // This subroutine calculates the series representation of (1/2) Log[(1 + x) / (1 - x)]
  // for small x without losing precision.

  if(!ef::isfinite(x))
  {
    return x;
  }

  if((x <= ef::one_minus()) || (x >= ef::one()))
  {
    return std::numeric_limits<e_float>::quiet_NaN();
  }

  // for values of x near one.
  const e_float x2 = x * x;
        e_float xn = x;

  e_float sum = xn;

  // Series representation of (1/2) Log[(1 + x) / (1 - x)] as given in
  // Schaum's Outlines: Mathematical Handbook of Formulas and Tables,
  // Second Edition, equation 22.8, page 136.
  for(std::int32_t n = static_cast<std::int32_t>(3); n < ef::max_iteration(); n += static_cast<std::int32_t>(2))
  {
    xn *= x2;

    const e_float term = xn / n;

    if(n > static_cast<std::int32_t>(20))
    {
      const std::int64_t order_check = static_cast<std::int64_t>(term.order() - sum.order());

      if(order_check < -ef::tolerance())
      {
        break;
      }
    }

    sum += term;
  }

  return sum;
}

e_float ef::pow(const e_float& x, const e_float& a)
{
  if((ef::isfinite(x) == false) || ef::isone(a))
  {
    return x;
  }

  if(ef::iszero(x))
  {
    return ef::one();
  }
  
  if(ef::iszero(a))
  {
    return ef::one();
  }

  const bool bo_a_isint = ef::isint(a);

  if(ef::isneg(x) && !bo_a_isint)
  {
    return std::numeric_limits<e_float>::quiet_NaN();
  }

  if(a <= ef::one_minus())
  {
    return ef::one() / ef::pow(x, -a);
  }

  const e_float      a_int = ef::integer_part(a);
  const std::int64_t an    = ef::to_int64(a_int);
  const e_float      da    = a - a_int;

  if(bo_a_isint)
  {
    return ef::detail::pown_template(x, an);
  }

  static const e_float nine_tenths = ef::nine() / static_cast<std::int32_t>(10);

  if(ef::ispos(x) && (x > ef::tenth()) && (x < nine_tenths))
  {
    if(ef::small_arg(a))
    {
      // Series expansion for small a.
      return ef::hypergeometric_0f0(a * ef::log(x));
    }
    else
    {
      // Series expansion for moderately sized x. Note that for large power of a,
      // the power of the integer part of a is calculated using the pown function.
      return ((an != static_cast<std::int64_t>(0)) ? ef::hypergeometric_1f0(-da, ef::one() - x) * ef::detail::pown_template(x, an)
                                                   : ef::hypergeometric_1f0( -a, ef::one() - x));
    }
  }
  else
  {
    // Series expansion for pow(x, a). Note that for large power of a, the power
    // of the integer part of a is calculated using the pown function.
    return ((an != static_cast<std::int64_t>(0)) ? ef::exp(da * ef::log(x)) * ef::detail::pown_template(x, an)
                                                 : ef::exp( a * ef::log(x)));
  }
}

e_float ef::pow(const e_float& b, const std::int64_t p)
{
  // Calculate (b ^ p).

  using floating_point_type = e_float;

  floating_point_type result;

  if     (p <  0) { result = 1 / pow(b, -p); }
  else if(p == 0) { result = floating_point_type(1U); }
  else if(p == 1) { result = b; }
  else if(p == 2) { result = b; result *= b; }
  else if(p == 3) { result = b * b; result *= b; }
  else if(p == 4) { result = b * b; result *= result; }
  else
  {
    result = floating_point_type(1U);

    floating_point_type y(b);

    for(std::uint64_t p_local = (std::uint64_t) p; p_local != 0U; p_local >>= 1U)
    {
      if((p_local & 1U) != 0U)
      {
        result *= y;
      }

      y *= y;
    }
  }

  return result;
}

e_float ef::sinh(const e_float& x)
{
  if(x.i_have_my_own_sinh())
  {
    return e_float::my_own_sinh(x);
  }

  if(!ef::isfinite(x))
  {
    return x;
  }

  e_float s;
  ef::sinhcosh(x, &s, static_cast<e_float*>(0U));
  return s;
}

e_float ef::cosh(const e_float& x)
{
  if(x.i_have_my_own_cosh())
  {
    return e_float::my_own_cosh(x);
  }

  if(ef::isfinite(x) == false)
  {
    return x;
  }

  e_float c;
  ef::sinhcosh(x, static_cast<e_float*>(0U), &c);
  return c;
}

void ef::sinhcosh(const e_float& x, e_float* const p_sinh, e_float* const p_cosh)
{
  if((ef::isfinite(x) == false) || ((p_sinh == nullptr) && (p_cosh == nullptr)))
  {
    return;
  }
  
  if(ef::iszero(x))
  {
    if(p_sinh != nullptr)
    {
      *p_sinh = ef::zero();
    }

    if(p_cosh != nullptr)
    {
      *p_cosh = ef::one();
    }

    return;
  }

  const e_float e_px = ef::exp(x);
  const e_float e_mx = ef::one() / e_px;

  if(p_sinh != nullptr) { *p_sinh  = (e_px - e_mx) / static_cast<std::int32_t>(2); }
  if(p_cosh != nullptr) { *p_cosh  = (e_px + e_mx) / static_cast<std::int32_t>(2); }
}

e_float ef::tanh(const e_float& x)
{
  if(x.i_have_my_own_tanh())
  {
    return e_float::my_own_tanh(x);
  }

  e_float c, s;
  ef::sinhcosh(x, &s, &c);
  return s * c.calculate_inv();
}

e_float ef::asinh(const e_float& x)
{
  if(x.i_have_my_own_asinh())
  {
    return e_float::my_own_asinh(x);
  }

  if(!ef::isfinite(x))
  {
    return std::numeric_limits<e_float>::quiet_NaN();
  }

  if(ef::iszero(x))
  {
    return ef::zero();
  }
  else
  {
    const e_float value = ef::log(ef::fabs(x) + ef::sqrt((x * x) + ef::one()));

    return ((ef::isneg(x) == false) ? value : -value);
  }
}

e_float ef::acosh(const e_float& x)
{
  if(x.i_have_my_own_acosh())
  {
    return e_float::my_own_acosh(x);
  }

  if(ef::isfinite(x) == false)
  {
    return std::numeric_limits<e_float>::quiet_NaN();
  }

  if(ef::isneg(x) || x < ef::one())
  {
    return std::numeric_limits<e_float>::quiet_NaN();
  }

  if(ef::isone(x))
  {
    return ef::one();
  }

  const e_float x_minus_one = x - ef::one();

  if(ef::small_arg(x_minus_one))
  {
    return   (ef::sqrt2() * ef::sqrt(x_minus_one))
           *  ef::hypergeometric_2f1( ef::half(),
                                      ef::half(),
                                      ef::three_half(),
                                     -x_minus_one / static_cast<std::int32_t>(2));
  }
  else
  {
    return ef::log(x + ef::sqrt((x * x) - ef::one()));
  }
}

e_float ef::atanh(const e_float& x)
{
  if(x.i_have_my_own_atanh())
  {
    return e_float::my_own_atanh(x);
  }

  if(!ef::isfinite(x))
  {
    return x;
  }

  const e_float xx = ef::fabs(x);
  
  if(xx >= ef::one())
  {
    return std::numeric_limits<e_float>::quiet_NaN();
  }

  const e_float value = (ef::small_arg(x) ?  ef::log1p1m2(x)
                                          : (ef::log((ef::one() + x) / (ef::one() - x)) / static_cast<std::int32_t>(2)));

  return ((!ef::isneg(xx)) ? value : -value);
}
