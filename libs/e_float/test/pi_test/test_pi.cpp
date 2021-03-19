
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

#include <../test/pi_test/pi_algos.h>
#include <../test/pi_test/test_pi.h>

bool test::pi::test_pi()
{
  bool result_is_ok = false;

  std::ofstream out0("pi0.out");
  std::ofstream out1("pi1.out");
  std::ofstream out2("pi2.out");
  std::ofstream out3("pi3.out");
  std::ofstream out4("pi4.out");

  const bool output_files_are_open = (   out0.is_open()
                                      && out1.is_open()
                                      && out2.is_open()
                                      && out3.is_open()
                                      && out4.is_open());

  if(output_files_are_open)
  {
    calculate_pi_pfn pfn0 = calculate_pi;
    calculate_pi_pfn pfn1 = calculate_pi_borwein_cubic;
    calculate_pi_pfn pfn2 = calculate_pi_borwein_quartic;
    calculate_pi_pfn pfn3 = calculate_pi_borwein_quintic;
    calculate_pi_pfn pfn4 = calculate_pi_borwein_nonic;

    result_is_ok = true;

    result_is_ok &= print_pi(pfn0, out0);
    result_is_ok &= print_pi(pfn1, out1);
    result_is_ok &= print_pi(pfn2, out2);
    result_is_ok &= print_pi(pfn3, out3);
    result_is_ok &= print_pi(pfn4, out4);

    out0.close();
    out1.close();
    out2.close();
    out3.close();
    out4.close();
  }

  return result_is_ok;
}
