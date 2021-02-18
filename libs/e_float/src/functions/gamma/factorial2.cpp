
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <e_float/e_float_functions.h>

#include <functions/tables/tables.h>

namespace Factorial2_Series
{
  e_float AtInfinity(const std::int32_t n);
}

e_float Factorial2_Series::AtInfinity(const std::int32_t n)
{
  const bool n_is_even = static_cast<std::int32_t>(n % static_cast<std::int32_t>(2)) == static_cast<std::int32_t>(0U);

  if(n_is_even)
  {
    const std::uint32_t n_half = static_cast<std::uint32_t>(static_cast<std::uint32_t>(n) / static_cast<std::uint32_t>(2));

    return ef::pow2(static_cast<std::int64_t>(n_half)) * ef::factorial(n_half);
  }
  else
  {
    const std::int32_t n_plus_one = static_cast<std::int32_t>(static_cast<std::int32_t>(n) + static_cast<std::int32_t>(1));

    return ef::factorial(static_cast<std::uint32_t>(n_plus_one)) / ef::factorial2(n_plus_one);
  }
}

e_float ef::factorial2(const std::int32_t n)
{
  const bool n_is_neg  = (n < static_cast<std::int32_t>(0));

  if(!n_is_neg)
  {
    return (static_cast<std::size_t>(n) < Tables::A006882().size()) ? Tables::A006882()[static_cast<std::size_t>(n)]()
                                                                    : Factorial2_Series::AtInfinity(n);
  }
  else
  {
    if(n == static_cast<std::int32_t>(-1))
    {
      return ef::one();
    }

    const std::int32_t nn        = (!n_is_neg ? n : static_cast<std::int32_t>(-n));
    const bool  n_is_even = (static_cast<std::int32_t>(nn % static_cast<std::int32_t>(2)) == static_cast<std::int32_t>(0U));

    if(n_is_even)
    {
      return std::numeric_limits<e_float>::quiet_NaN();
    }
    else
    {
      // Double factorial for negative odd integers.
      const std::int32_t n_minus_one_over_two = static_cast<std::int32_t>(static_cast<std::int32_t>(nn - static_cast<std::int32_t>(1)) / static_cast<std::int32_t>(2));
      const bool  b_negate             = static_cast<std::int32_t>(n_minus_one_over_two % static_cast<std::int32_t>(2)) != static_cast<std::int32_t>(0);

      const e_float f2 = ef::one() / ef::factorial2(static_cast<std::int32_t>(nn - static_cast<std::int32_t>(2)));

      return (!b_negate ? f2 : -f2);
    }
  }
}
