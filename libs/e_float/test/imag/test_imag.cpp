
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <iostream>

#include "test_imag.h"

namespace test
{
  namespace imag
   {
    bool test_case_02101_z_sin                    (const bool b_write_output);
    bool test_case_02102_z_cos                    (const bool b_write_output);
    bool test_case_02103_z_exp                    (const bool b_write_output);
    bool test_case_02104_z_log                    (const bool b_write_output);
    bool test_case_02105_z_sqrt                   (const bool b_write_output);
    bool test_case_02106_z_rootn                  (const bool b_write_output);
    bool test_case_02111_z_asin                   (const bool b_write_output);
    bool test_case_02112_z_acos                   (const bool b_write_output);
    bool test_case_02113_z_atan                   (const bool b_write_output);
    bool test_case_02114_z_various_trig           (const bool b_write_output);
    bool test_case_02115_z_various_elem_trans_log (const bool b_write_output);
    bool test_case_02116_z_various_elem           (const bool b_write_output);
    bool test_case_02121_z_sinh                   (const bool b_write_output);
    bool test_case_02122_z_cosh                   (const bool b_write_output);
    bool test_case_02123_z_tanh                   (const bool b_write_output);
    bool test_case_02124_z_asinh                  (const bool b_write_output);
    bool test_case_02125_z_acosh                  (const bool b_write_output);
    bool test_case_02126_z_atanh                  (const bool b_write_output);
    bool test_case_02201_z_gamma                  (const bool b_write_output);
    bool test_case_02202_z_gamma_medium_x         (const bool b_write_output);
    bool test_case_02901_z_zeta_small_x           (const bool b_write_output);
    bool test_case_02902_z_zeta_all_x             (const bool b_write_output);
    bool test_case_02903_z_zeta_neg_x             (const bool b_write_output);
    bool test_case_02911_z_zeta_crit_strip        (const bool b_write_output);
  }
}

bool test::imag::test_imag(const bool b_write_output)
{
  bool test_ok = true;

  test_ok &= test::imag::test_case_02101_z_sin                    (b_write_output);
  test_ok &= test::imag::test_case_02102_z_cos                    (b_write_output);
  test_ok &= test::imag::test_case_02103_z_exp                    (b_write_output);
  test_ok &= test::imag::test_case_02104_z_log                    (b_write_output);
  test_ok &= test::imag::test_case_02105_z_sqrt                   (b_write_output);
  test_ok &= test::imag::test_case_02106_z_rootn                  (b_write_output);
  test_ok &= test::imag::test_case_02111_z_asin                   (b_write_output);
  test_ok &= test::imag::test_case_02112_z_acos                   (b_write_output);
  test_ok &= test::imag::test_case_02113_z_atan                   (b_write_output);
  test_ok &= test::imag::test_case_02114_z_various_trig           (b_write_output);
  test_ok &= test::imag::test_case_02115_z_various_elem_trans_log (b_write_output);
  test_ok &= test::imag::test_case_02116_z_various_elem           (b_write_output);
  test_ok &= test::imag::test_case_02121_z_sinh                   (b_write_output);
  test_ok &= test::imag::test_case_02122_z_cosh                   (b_write_output);
  test_ok &= test::imag::test_case_02123_z_tanh                   (b_write_output);
  test_ok &= test::imag::test_case_02124_z_asinh                  (b_write_output);
  test_ok &= test::imag::test_case_02125_z_acosh                  (b_write_output);
  test_ok &= test::imag::test_case_02126_z_atanh                  (b_write_output);
  test_ok &= test::imag::test_case_02201_z_gamma                  (b_write_output);
  test_ok &= test::imag::test_case_02202_z_gamma_medium_x         (b_write_output);
  test_ok &= test::imag::test_case_02901_z_zeta_small_x           (b_write_output);
  test_ok &= test::imag::test_case_02902_z_zeta_all_x             (b_write_output);
  test_ok &= test::imag::test_case_02903_z_zeta_neg_x             (b_write_output);
  test_ok &= test::imag::test_case_02911_z_zeta_crit_strip        (b_write_output);

  return test_ok;
}
