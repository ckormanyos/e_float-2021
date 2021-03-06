
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <e_float/e_float_functions.h>

#include <functions/gamma/gamma_util.h>

void GammaUtil::GammaOfPlusXMinusX(const e_float& x, e_float& gamma_plus_x, e_float& gamma_minus_x)
{
  // Calculate gamma(x) and gamma(-x) without regard for the actual sign of x.
  // In other words, calculate gamma(abs(x)) and set the results appropriately
  // using the reflection formula.
  const bool    bo_x_isneg    =  ef::isneg(x);
  const e_float abs_x         =  ef::fabs(x);
  const e_float gamma_x_pos   =  ef::gamma(abs_x);
  const e_float gamma_x_neg   = -ef::pi() / ((abs_x * gamma_x_pos) * ef::sin(ef::pi() * abs_x));

  gamma_plus_x  =  bo_x_isneg ? gamma_x_neg : gamma_x_pos;
  gamma_minus_x =  bo_x_isneg ? gamma_x_pos : gamma_x_neg;
}
