
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef GAMMA_UTIL_2008_01_10_H_
  #define GAMMA_UTIL_2008_01_10_H_
  
  #include <e_float/e_float.h>

  namespace GammaUtil
  {
    void GammaOfPlusXMinusX(const e_float& x, e_float& gamma_plus_x, e_float& gamma_minus_x);
  }
  
#endif // GAMMA_UTIL_2008_01_10_H_
