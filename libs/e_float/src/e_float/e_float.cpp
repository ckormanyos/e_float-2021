
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <e_float/e_float.h>
#include <utility/util_lexical_cast.h>

// Global unary operators of e_float reference.
e_float operator+(const e_float& self) { return e_float(self); }
e_float operator-(const e_float& self) { e_float tmp(self); tmp.negate(); return tmp; }

// Global add/sub/mul/div of const e_float& with const e_float&.
e_float operator+(const e_float& u, const e_float& v) { return e_float(u) += v; }
e_float operator-(const e_float& u, const e_float& v) { return e_float(u) -= v; }
e_float operator*(const e_float& u, const e_float& v) { return e_float(u) *= v; }
e_float operator/(const e_float& u, const e_float& v) { return e_float(u) /= v; }

// Global comparison operators of const e_float& with const e_float&.
bool operator< (const e_float& u, const e_float& v) { return (u.cmp(v) <  static_cast<std::int32_t>(0)); }
bool operator<=(const e_float& u, const e_float& v) { return (u.cmp(v) <= static_cast<std::int32_t>(0)); }
bool operator==(const e_float& u, const e_float& v) { return (u.cmp(v) == static_cast<std::int32_t>(0)); }
bool operator!=(const e_float& u, const e_float& v) { return (u.cmp(v) != static_cast<std::int32_t>(0)); }
bool operator>=(const e_float& u, const e_float& v) { return (u.cmp(v) >= static_cast<std::int32_t>(0)); }
bool operator> (const e_float& u, const e_float& v) { return (u.cmp(v) >  static_cast<std::int32_t>(0)); }

const e_float& ef::value_nan() { static const e_float val = e_float().my_value_nan(); return val; }
const e_float& ef::value_inf() { static const e_float val = e_float().my_value_inf(); return val; }
const e_float& ef::value_max() { static const e_float val = e_float().my_value_max(); return val; }
const e_float& ef::value_min() { static const e_float val = e_float().my_value_min(); return val; }

const e_float& ef::value_eps()
{
  static const e_float val("1E-" + Util::lexical_cast(std::numeric_limits<e_float>::digits10 - 1));

  return val;
}

const e_float& ef::zero() { static const e_float val(0U);   return val; }
const e_float& ef::one () { static const e_float val(1U);   return val; }
const e_float& ef::half() { static const e_float val( { 50000000 }, -8 ); return val; }

constexpr bool                    std::numeric_limits<e_float>::is_specialized;
constexpr bool                    std::numeric_limits<e_float>::is_signed;
constexpr bool                    std::numeric_limits<e_float>::is_integer;
constexpr bool                    std::numeric_limits<e_float>::is_exact;
constexpr bool                    std::numeric_limits<e_float>::is_bounded;
constexpr bool                    std::numeric_limits<e_float>::is_modulo;
constexpr bool                    std::numeric_limits<e_float>::is_iec559;
constexpr int                     std::numeric_limits<e_float>::digits;
constexpr int                     std::numeric_limits<e_float>::digits10;
constexpr int                     std::numeric_limits<e_float>::max_digits10;
constexpr int                     std::numeric_limits<e_float>::min_exponent;
constexpr int                     std::numeric_limits<e_float>::min_exponent10;
constexpr int                     std::numeric_limits<e_float>::max_exponent;
constexpr int                     std::numeric_limits<e_float>::max_exponent10;
constexpr int                     std::numeric_limits<e_float>::radix;
constexpr std::float_round_style  std::numeric_limits<e_float>::round_style;
constexpr bool                    std::numeric_limits<e_float>::has_infinity;
constexpr bool                    std::numeric_limits<e_float>::has_quiet_NaN;
constexpr bool                    std::numeric_limits<e_float>::has_signaling_NaN;
constexpr std::float_denorm_style std::numeric_limits<e_float>::has_denorm;
constexpr bool                    std::numeric_limits<e_float>::has_denorm_loss;
constexpr bool                    std::numeric_limits<e_float>::traps;
constexpr bool                    std::numeric_limits<e_float>::tinyness_before;
