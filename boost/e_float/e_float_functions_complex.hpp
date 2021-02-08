
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef E_FLOAT_FUNCTIONS_COMPLEX_2017_08_23_HPP_
  #define E_FLOAT_FUNCTIONS_COMPLEX_2017_08_23_HPP_

  #include <cstdint>

  #include <boost/e_float/e_float_complex.hpp>

  namespace ef
  {
    complex<e_float> gamma       (const complex<e_float>& z);
    complex<e_float> pochhammer  (const complex<e_float>& z, const std::uint32_t n);
    complex<e_float> pochhammer  (const complex<e_float>& z, const complex<e_float>& a);
    complex<e_float> riemann_zeta(const complex<e_float>& s);
  }

#endif // E_FLOAT_FUNCTIONS_COMPLEX_2017_08_23_HPP_
