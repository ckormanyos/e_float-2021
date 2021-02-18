//          Copyright Christopher Kormanyos 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iomanip>
#include <iostream>

// cd C:\Users\User\Documents\Ks\PC_Software\NumericalPrograms\ExtendedNumberTypes\e_float\libs\e_float\build

// g++ -Wall -Wextra -m64 -O3 -std=gnu++11 -DE_FLOAT_TYPE_EFX -I../../../libs/e_float/src -IC:/boost/modular_boost/boost/libs/multiprecision/include -IC:/boost/modular_boost/boost/libs/math/include -IC:/boost/boost_1_75_0 ../src/e_float/efx/e_float_efx.cpp ../src/e_float/e_float.cpp ../src/e_float/e_float_base.cpp ../src/functions/constants/constants.cpp ../src/functions/elementary/elementary_complex.cpp ../src/functions/elementary/elementary_hyper_g.cpp ../src/functions/elementary/elementary_math.cpp ../src/functions/elementary/elementary_trans.cpp ../src/functions/elementary/elementary_trig.cpp ../test_boost/test_boost.cpp ../test_boost/test_boost_real_concept.cpp ../test_boost/test_boost_sf.cpp -o test_boost.exe

extern bool test_boost_sf          ();
extern bool test_boost_real_concept();

int main()
{
  const bool test_boost_sf_is_ok = test_boost_sf();
  const bool test_boost_rc_is_ok = test_boost_real_concept();

  std::cout << "test_boost_sf_is_ok: " << std::boolalpha << test_boost_sf_is_ok << std::endl;
  std::cout << "test_boost_rc_is_ok: " << std::boolalpha << test_boost_rc_is_ok << std::endl;

  const bool result_is_ok = (test_boost_sf_is_ok && test_boost_rc_is_ok);

  return result_is_ok ? 0 : -1;
}
