
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef PRIME_FACTORS_2011_06_23_H_
  #define PRIME_FACTORS_2011_06_23_H_

  #include <deque>

  #include "../../utility/util_point.h"

  namespace ef
  {
    void prime_factors(const std::uint32_t n, std::deque<Util::point<std::uint32_t>>& pf);
  }

#endif // PRIME_FACTORS_2011_06_23_H_
