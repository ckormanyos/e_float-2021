
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef UTIL_POWER_J_POW_X_2009_01_25_H_
  #define UTIL_POWER_J_POW_X_2009_01_25_H_

  #include <map>

  #include <boost/e_float/e_float_functions.hpp>
  #include <boost/e_float/e_float_complex.hpp>

  namespace Util
  {
    e_float    j_pow_x(const std::uint32_t j, const e_float&    x, std::map<std::uint32_t, e_float>&    n_pow_x_prime_factor_map);
    ef::complex<e_float> j_pow_x(const std::uint32_t j, const ef::complex<e_float>& x, std::map<std::uint32_t, ef::complex<e_float>>& n_pow_x_prime_factor_map);
  }

#endif // UTIL_POWER_J_POW_X_2009_01_25_H_
