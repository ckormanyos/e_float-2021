
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <iostream>

#include "test_real.h"

namespace test
{
  namespace real
  {
    bool test_case_00001_overflow_mul_x                (const bool b_write_output);
    bool test_case_00002_underflow_mul_x               (const bool b_write_output);
    bool test_case_00003_overflow_x_mul_by_n           (const bool b_write_output);
    bool test_case_00004_underflow_x_div_by_n          (const bool b_write_output);
    bool test_case_00006_write_os_floatfield_fixed     (const bool b_write_output);
    bool test_case_00007_write_os_floatfield_scientific(const bool b_write_output);
    bool test_case_00008_write_os_floatfield_not_set   (const bool b_write_output);
    bool test_case_00009_global_ops_pod_equate         (const bool b_write_output);
    bool test_case_00010_global_ops_pod_operations     (const bool b_write_output);
    bool test_case_00011_various_elem_math             (const bool b_write_output);
    bool test_case_00021_bernoulli                     (const bool b_write_output);
    bool test_case_00051_factorial                     (const bool b_write_output);
    bool test_case_00052_factorial2                    (const bool b_write_output);
    bool test_case_00071_various_int_func              (const bool b_write_output);
    bool test_case_00101_sin                           (const bool b_write_output);
    bool test_case_00102_cos                           (const bool b_write_output);
    bool test_case_00103_exp                           (const bool b_write_output);
    bool test_case_00104_log                           (const bool b_write_output);
    bool test_case_00105_sqrt                          (const bool b_write_output);
    bool test_case_00106_rootn                         (const bool b_write_output);
    bool test_case_00111_sin_small_x                   (const bool b_write_output);
    bool test_case_00112_cos_x_near_pi_half            (const bool b_write_output);
    bool test_case_00113_atan_x_small_to_large         (const bool b_write_output);
    bool test_case_00114_various_trig                  (const bool b_write_output);
    bool test_case_00115_various_elem_trans            (const bool b_write_output);
    bool test_case_00121_sinh                          (const bool b_write_output);
    bool test_case_00122_cosh                          (const bool b_write_output);
    bool test_case_00123_tanh                          (const bool b_write_output);
    bool test_case_00124_asinh                         (const bool b_write_output);
    bool test_case_00125_acosh                         (const bool b_write_output);
    bool test_case_00126_atanh                         (const bool b_write_output);
    bool test_case_00201_gamma                         (const bool b_write_output);
    bool test_case_00202_gamma_medium_x                (const bool b_write_output);
    bool test_case_00203_gamma_small_x                 (const bool b_write_output);
    bool test_case_00204_gamma_tiny_x                  (const bool b_write_output);
    bool test_case_00205_gamma_near_neg_n              (const bool b_write_output);
    bool test_case_00221_various_gamma_func            (const bool b_write_output);
    bool test_case_00901_zeta_small_x                  (const bool b_write_output);
    bool test_case_00902_zeta_all_x                    (const bool b_write_output);
    bool test_case_00903_zeta_neg_x                    (const bool b_write_output);
  }
}

bool test::real::test_real(const bool b_write_output)
{
  bool test_ok = true;

  test_ok &= test::real::test_case_00001_overflow_mul_x                (b_write_output);
  test_ok &= test::real::test_case_00002_underflow_mul_x               (b_write_output);
  test_ok &= test::real::test_case_00003_overflow_x_mul_by_n           (b_write_output);
  test_ok &= test::real::test_case_00004_underflow_x_div_by_n          (b_write_output);
  test_ok &= test::real::test_case_00006_write_os_floatfield_fixed     (b_write_output);
  test_ok &= test::real::test_case_00007_write_os_floatfield_scientific(b_write_output);
  test_ok &= test::real::test_case_00008_write_os_floatfield_not_set   (b_write_output);
  test_ok &= test::real::test_case_00009_global_ops_pod_equate         (b_write_output);
  test_ok &= test::real::test_case_00010_global_ops_pod_operations     (b_write_output);
  test_ok &= test::real::test_case_00011_various_elem_math             (b_write_output);
  test_ok &= test::real::test_case_00021_bernoulli                     (b_write_output);
  test_ok &= test::real::test_case_00051_factorial                     (b_write_output);
  test_ok &= test::real::test_case_00052_factorial2                    (b_write_output);
  test_ok &= test::real::test_case_00071_various_int_func              (b_write_output);
  test_ok &= test::real::test_case_00101_sin                           (b_write_output);
  test_ok &= test::real::test_case_00102_cos                           (b_write_output);
  test_ok &= test::real::test_case_00103_exp                           (b_write_output);
  test_ok &= test::real::test_case_00104_log                           (b_write_output);
  test_ok &= test::real::test_case_00105_sqrt                          (b_write_output);
  test_ok &= test::real::test_case_00106_rootn                         (b_write_output);
  test_ok &= test::real::test_case_00111_sin_small_x                   (b_write_output);
  test_ok &= test::real::test_case_00112_cos_x_near_pi_half            (b_write_output);
  test_ok &= test::real::test_case_00113_atan_x_small_to_large         (b_write_output);
  test_ok &= test::real::test_case_00114_various_trig                  (b_write_output);
  test_ok &= test::real::test_case_00115_various_elem_trans            (b_write_output);
  test_ok &= test::real::test_case_00121_sinh                          (b_write_output);
  test_ok &= test::real::test_case_00122_cosh                          (b_write_output);
  test_ok &= test::real::test_case_00123_tanh                          (b_write_output);
  test_ok &= test::real::test_case_00124_asinh                         (b_write_output);
  test_ok &= test::real::test_case_00125_acosh                         (b_write_output);
  test_ok &= test::real::test_case_00126_atanh                         (b_write_output);
  test_ok &= test::real::test_case_00201_gamma                         (b_write_output);
  test_ok &= test::real::test_case_00202_gamma_medium_x                (b_write_output);
  test_ok &= test::real::test_case_00203_gamma_small_x                 (b_write_output);
  test_ok &= test::real::test_case_00204_gamma_tiny_x                  (b_write_output);
  test_ok &= test::real::test_case_00205_gamma_near_neg_n              (b_write_output);
  test_ok &= test::real::test_case_00221_various_gamma_func            (b_write_output);
  test_ok &= test::real::test_case_00901_zeta_small_x                  (b_write_output);
  test_ok &= test::real::test_case_00902_zeta_all_x                    (b_write_output);
  test_ok &= test::real::test_case_00903_zeta_neg_x                    (b_write_output);

  return test_ok;
}
