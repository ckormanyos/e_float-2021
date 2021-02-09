
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <e_float/e_float.h>
#include <e_float/e_float_complex.h>
#include <e_float/e_float_functions.h>

#include "test_case_base.h"

namespace test
{
  static bool compare_single_ef_value(std::string& str_result,
                                      const e_float& my_value,
                                      const e_float& control)
  {
    static const e_float the_epsilon = (std::min)(e_float("1E-25"), ef::pow(std::numeric_limits<e_float>::epsilon(), e_float(85) / 100));

    str_result.clear();

    // Ensure that the two real numbers are equal in the sense that
    // the difference between them is identically zero or that their
    // relative difference is less than the_epsilon. Recall that
    // std::numeric_limits<T>::epsilon() is defined as the smallest
    // number of a given type T which is distinguishable from 1.

    const bool ef_data_is_zero = ef::iszero(my_value);
    const bool ml_data_is_zero = ef::iszero(control);

    const e_float delta = ef::abs(my_value - control);

    if(!ef::isfinite(my_value))
    {
      // The result from e_float is not finite. The comparison failed.
      str_result = "Value is not finite";

      return false;
    }
    else if(ef::isneg(my_value) != ef::isneg(control))
    {
      // The sign of the result from e_float and the sign of the result from
      // the control test are different. The comparison failed.
      str_result = "Sign mismatch";

      return false;
    }
    else if(ef::iszero(delta))
    {
      // The two numbers are identical. This also includes the case for which
      // both numbers are equal to zero. The comparison succeeds.
      // The comparison succeeds.

      return true;
    }
    else if(ef_data_is_zero && (delta >= the_epsilon))
    {
      // The result from e_float is zero and the result from MathLink is non-zero.
      // The comparison fails if the result from the control test is equal to or
      // exceeds epsilon.
      str_result = "Mismatch zero with non-zero";

      return false;
    }
    else if(ef_data_is_zero && (delta < the_epsilon))
    {
      // The result from e_float is zero and the result from MathLink is non-zero,
      // but with absolute value less than epsilon.
      // The comparison succeeds.

      return true;
    }
    else if(ml_data_is_zero && (delta >= the_epsilon))
    {
      // The result from the control test is zero and the result from e_float is non-zero.
      // The comparison fails if the result from e_float is equal to or exceeds epsilon.
      str_result = "Mismatch non-zero with zero";

      return false;
    }
    else if(ml_data_is_zero && (delta < the_epsilon))
    {
      // The result from the control test is zero and the result from e_float is non-zero,
      // but with absolute value less than epsilon.
      // The comparison succeeds.

      return true;
    }
    else
    {
      const e_float abs_ef_data = ef::abs(my_value);
      const e_float abs_ml_data = ef::abs(control);

      const e_float delta_relative = delta / (std::min)(abs_ef_data, abs_ml_data);

      if(delta_relative > the_epsilon)
      {
        // The result from the control test is non-zero and the result from e_float is non-zero.
        // The comparison fails if the maximum relative difference is equal to or
        // exceeds epsilon.

        str_result = "Digit comparison failure";

        return false;
      }
      else
      {
        return true;
      }
    }
  }
}

bool test::compare_value(std::string& str_result,
                         const e_float& my_value,
                         const e_float& control)
{
  return compare_single_ef_value(str_result, my_value, control);
}

bool test::compare_value(std::string& str_result,
                         const ef::complex<e_float>& my_value,
                         const ef::complex<e_float>& control)
{
  std::string str_result_re;
  std::string str_result_im;

  const bool b_compare_re = compare_single_ef_value(str_result, my_value.real(), control.real());
  const bool b_compare_im = compare_single_ef_value(str_result, my_value.imag(), control.imag());

  if(!b_compare_re && !b_compare_im)
  {
    str_result = str_result_re + "\n" + str_result_im;

    return false;
  }
  else if(!b_compare_re)
  {
    str_result = str_result_re;

    return false;
  }
  else if(!b_compare_im)
  {
    str_result = str_result_im;

    return false;
  }
  else
  {
    return true;
  }
}
