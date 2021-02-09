
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include <e_float/e_float.h>
#include <e_float/e_float_functions.h>
#include "../src/utility/util_timer.h"

#include "examples.h"

void examples::nr_001::basic_usage_real()
{
  // Print 21 values of the function gamma[(222/10) + k]
  // for 0 <= k < 21 to the standard output using e_float. Also compute the computation
  // time for the calculation using e_float in [ms].
  // A comparable Mathematica code is:
  // Timing[Table[N[Gamma[(222/10) + k], 100],{k, 0, 20, 1}]].

  const e_float v(222U / ef::ten());

  std::vector<e_float> values(static_cast<std::size_t>(21U));

  const Util::timer tm;

  for(std::int32_t k = static_cast<std::int32_t>(0); k < static_cast<std::int32_t>(values.size()); k++)
  {
    values[static_cast<std::size_t>(k)] = ef::gamma(v + k);
  }

  const double elapsed = tm.elapsed();

  std::cout << "Elapsed time: " << elapsed << "\n";

  const std::streamsize    original_prec = std::cout.precision(std::numeric_limits<e_float>::digits10);
  const std::ios::fmtflags original_flag = std::cout.setf(std::ios::showpos | std::ios::scientific);

  std::copy(values.cbegin(), values.cend(), std::ostream_iterator<e_float>(std::cout, "\n"));

  std::cout.precision(original_prec);
  std::cout.unsetf(std::ios::showpos | std::ios::scientific);
  std::cout.setf(original_flag);
}
