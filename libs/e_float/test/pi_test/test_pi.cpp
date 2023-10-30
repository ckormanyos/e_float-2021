
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
#include <string>

#include <e_float/e_float.h>

#include <../test/pi_test/pi_algos.h>
#include <../test/pi_test/test_pi.h>

bool test::pi::test_pi()
{
  using str_name_array_type         = std::array<std::string, 6U>;
  using ofstream_array_type         = std::array<std::ofstream, std::tuple_size<str_name_array_type>::value>;
  using calculate_pi_pfn_array_type = std::array<calculate_pi_pfn, std::tuple_size<str_name_array_type>::value>;

  str_name_array_type names =
  {{
    std::string("pi.out"),
    std::string("pi_borwein_cubic.out"),
    std::string("pi_borwein_quartic.out"),
    std::string("pi_borwein_quintic.out"),
    std::string("pi_borwein_nonic.out"),
    std::string("pi_borwein_hexadecimalic.out")
  }};

  ofstream_array_type out =
  {{
    std::ofstream(names[0U].c_str()),
    std::ofstream(names[1U].c_str()),
    std::ofstream(names[2U].c_str()),
    std::ofstream(names[3U].c_str()),
    std::ofstream(names[4U].c_str()),
    std::ofstream(names[5U].c_str())
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
    bool result_pi_calculations_is_ok = true;

    for(std::size_t j = 0U; (result_pi_calculations_is_ok && (j < pfn.size())); ++j)
    {
      const std::string str_name_j = names[j].substr(0U, names[j].find(char('.')));

      result_pi_calculations_is_ok &= print_pi(pfn[j], out[j], str_name_j);

      out[j].close();
    }

    result_is_ok &= result_pi_calculations_is_ok;
  }

  return result_is_ok;
}
