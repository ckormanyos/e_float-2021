
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <algorithm>
#include <array>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

#include <e_float/e_float.h>

#include <../test/pi_test/pi_algos.h>
#include <../test/pi_test/test_pi.h>

bool test::pi::test_pi()
{
  using ofstream_array_type         = std::array<std::ofstream, 6U>;
  using calculate_pi_pfn_array_type = std::array<calculate_pi_pfn, std::tuple_size<ofstream_array_type>::value>;

  ofstream_array_type out =
  {{
    std::ofstream("pi.out"),
    std::ofstream("pi_borwein_cubic.out"),
    std::ofstream("pi_borwein_quartic.out"),
    std::ofstream("pi_borwein_quintic.out"),
    std::ofstream("pi_borwein_nonic.out"),
    std::ofstream("pi_borwein_hexadecimalic.out")
  }};

  const calculate_pi_pfn_array_type pfn =
  {{
    calculate_pi,
    calculate_pi_borwein_cubic,
    calculate_pi_borwein_quartic,
    calculate_pi_borwein_quintic,
    calculate_pi_borwein_nonic,
    calculate_pi_borwein_hexadecimalic
  }};

  bool result_is_ok =
    std::all_of
    (
      out.cbegin(),
      out.cend(),
      [](const std::ofstream& of) -> bool
      {
        return of.is_open();
      }
    );

  if(result_is_ok)
  {
    std::size_t index = 0U;

    const bool result_pi_calculations_is_ok =
      std::all_of
      (
        pfn.cbegin(),
        pfn.cend(),
        [&out, &index](const calculate_pi_pfn& pf) -> bool
        {
          const bool b_ok = print_pi(pf, out[index]);

          out[index].close();

          ++index;

          return b_ok;
        }
      );

    result_is_ok &= result_pi_calculations_is_ok;
  }

  return result_is_ok;
}
