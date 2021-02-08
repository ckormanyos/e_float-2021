
//          Copyright Christopher Kormanyos 2014 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef PI_ALGOS_2014_08_06_H_
  #define PI_ALGOS_2014_08_06_H_

  #include <ostream>
  #include <boost/e_float/e_float.hpp>

  const e_float& calculate_pi                (const bool b_trace);
  const e_float& calculate_pi_borwein_cubic  (const bool b_trace);
  const e_float& calculate_pi_borwein_quartic(const bool b_trace);
  const e_float& calculate_pi_borwein_quintic(const bool b_trace);

  typedef const e_float& (*calculate_pi_pfn)(const bool);

  bool print_pi(calculate_pi_pfn pfn, std::ostream& os);

#endif // PI_ALGOS_2014_08_06_H_
