
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <boost/e_float/e_float.hpp>
#include "../utility/util_lexical_cast.h"

const e_float& ef::value_nan() { static const e_float val = e_float().my_value_nan(); return val; }
const e_float& ef::value_inf() { static const e_float val = e_float().my_value_inf(); return val; }
const e_float& ef::value_max() { static const e_float val = e_float().my_value_max(); return val; }
const e_float& ef::value_min() { static const e_float val = e_float().my_value_min(); return val; }

const e_float& ef::value_eps()
{
  static const e_float val("1E-" + Util::lexical_cast(std::numeric_limits<e_float>::digits10 - 1));

  return val;
}

const e_float& ef::zero() { static const e_float val(0U);    return val; }
const e_float& ef::one () { static const e_float val(1U);    return val; }
const e_float& ef::half() { static const e_float val("0.5"); return val; }

#if defined(__GNUC__)
  const bool                    std::numeric_limits<e_float>::is_specialized;
  const bool                    std::numeric_limits<e_float>::is_signed;
  const bool                    std::numeric_limits<e_float>::is_integer;
  const bool                    std::numeric_limits<e_float>::is_exact;
  const bool                    std::numeric_limits<e_float>::is_bounded;
  const bool                    std::numeric_limits<e_float>::is_modulo;
  const bool                    std::numeric_limits<e_float>::is_iec559;
  const int                     std::numeric_limits<e_float>::digits;
  const int                     std::numeric_limits<e_float>::digits10;
  const int                     std::numeric_limits<e_float>::max_digits10;
  const std::int64_t                   std::numeric_limits<e_float>::min_exponent;
  const std::int64_t                   std::numeric_limits<e_float>::min_exponent10;
  const std::int64_t                   std::numeric_limits<e_float>::max_exponent;
  const std::int64_t                   std::numeric_limits<e_float>::max_exponent10;
  const int                     std::numeric_limits<e_float>::radix;
  const std::float_round_style  std::numeric_limits<e_float>::round_style;
  const bool                    std::numeric_limits<e_float>::has_infinity;
  const bool                    std::numeric_limits<e_float>::has_quiet_NaN;
  const bool                    std::numeric_limits<e_float>::has_signaling_NaN;
  const std::float_denorm_style std::numeric_limits<e_float>::has_denorm;
  const bool                    std::numeric_limits<e_float>::has_denorm_loss;
  const bool                    std::numeric_limits<e_float>::traps;
  const bool                    std::numeric_limits<e_float>::tinyness_before;
#endif // __GNUC__
