
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <iomanip>
#include <iostream>
#include <string>

#include <e_float/e_float.h>

#include <utility/util_timer.h>

// cd C:/Users/User/Documents/Ks/PC_Software/NumericalPrograms/ExtendedNumberTypes/e_float/libs/e_float/build
// make MP=efx rebuild

// Build locally for test on MinGW via command line
// cd C:\Users\User\Documents\Ks\PC_Software\NumericalPrograms\ExtendedNumberTypes\e_float\libs\e_float\build

// Build for E_FLOAT_TEST_PI_ALGOS_TESTS
// g++ -finline-functions -finline-limit=32 -march=native -mtune=native -O3 -Wall -Wextra -Wno-cast-function-type -std=c++11 -DE_FLOAT_TYPE_EFX -DE_FLOAT_TEST_PI_ALGOS_TESTS -I../../../libs/e_float/src @GCC_FilesPi.txt ../src/e_float/efx/e_float_efx.cpp -o e_float.exe

// Build for E_FLOAT_TEST_REAL_IMAG_TESTS
// g++ -finline-functions -finline-limit=32 -march=native -mtune=native -O3 -Wall -Wextra -Wno-cast-function-type -std=c++11 -DE_FLOAT_TYPE_EFX -DE_FLOAT_TEST_REAL_IMAG_TESTS -I../../../libs/e_float/src @GCC_FilesTest.txt ../src/e_float/efx/e_float_efx.cpp -o e_float.exe

#if defined(E_FLOAT_TEST_PI_ALGOS_TESTS)
#include <../test/pi_test/test_pi.h>
#endif

#if defined(E_FLOAT_TEST_REAL_IMAG_TESTS)
#include <../test/imag/test_imag.h>
#include <../test/real/test_real.h>

namespace
{
  bool test_real_imag()
  {
    const bool test_real_ok = test::real::test_real(true);
    const bool test_imag_ok = test::imag::test_imag(true);

    std::string str_real("Real test: ");
    std::string str_imag("Imag test: ");

    str_real += (test_real_ok ? "Passed: All tests OK." : "Failed: Not all tests OK.");
    str_imag += (test_imag_ok ? "Passed: All tests OK." : "Failed: Not all tests OK.");

    std::cout << str_real << std::endl;
    std::cout << str_imag << std::endl;

    const bool result_is_ok = (test_real_ok && test_imag_ok);

    return result_is_ok;
  }
}
#endif

int main()
{
  const Util::timer my_timer;

  #if defined(E_FLOAT_TEST_PI_ALGOS_TESTS)
  const bool result_is_ok = test::pi::test_pi();
  #endif

  #if defined(E_FLOAT_TEST_REAL_IMAG_TESTS)
  const bool result_is_ok = test_real_imag();
  #endif

  const double elapsed = my_timer.elapsed();

  std::cout << "Elapsed time: "
            << std::fixed
            << std::setprecision(2)
            << elapsed
            << " seconds"
            << std::endl;

  return (result_is_ok ? 0 : -1);
}
