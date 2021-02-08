
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef EXAMPLES_2010_01_02_H_
  #define EXAMPLES_2010_01_02_H_

  #include <boost/e_float/e_float_functions.hpp>

  namespace examples
  {
    namespace nr_001 { void basic_usage_real(); }
    namespace nr_002 { void basic_usage_imag(); }
    namespace nr_005 { e_float recursive_trapezoid_j0     (const e_float& x); }
    namespace nr_005 { e_float recursive_trapezoid_j0_test(); }
    namespace nr_008 { e_float gauss_laguerre_airy_ai(const e_float& x); }
    namespace nr_021 { void boost_bindings(); }
  }

#endif // EXAMPLES_2010_01_02_H_
