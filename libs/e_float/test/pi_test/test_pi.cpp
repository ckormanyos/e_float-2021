
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

#include <e_float/e_float.h>

#include "pi_algos.h"
#include "test_pi.h"

bool test::pi::test_pi()
{
  bool result_is_ok = false;

  std::ofstream out("pi.out");

  if(out.is_open())
  {
    calculate_pi_pfn pfn = calculate_pi;
    //calculate_pi_pfn pfn = calculate_pi_borwein_cubic;
    //calculate_pi_pfn pfn = calculate_pi_borwein_quartic;
    //calculate_pi_pfn pfn = calculate_pi_borwein_quintic;

    result_is_ok = print_pi(pfn, out);

    out.close();
  }

  return result_is_ok;
}
