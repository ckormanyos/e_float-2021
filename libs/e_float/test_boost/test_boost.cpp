//          Copyright Christopher Kormanyos 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iomanip>
#include <iostream>

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/bindings/e_float.hpp>
#include <boost/multiprecision/number.hpp>

// cd C:\Users\User\Documents\Ks\PC_Software\NumericalPrograms\ExtendedNumberTypes\e_float\libs\e_float\build

// g++ -Wall -Wextra -pedantic -m64 -O3 -DE_FLOAT_TYPE_EFX -I../../../ -I../../../libs/e_float/src -IC:/boost/mborland_math/include -IC:/boost/boost_1_75_0 ../src/e_float/efx/e_float_efx.cpp ../src/e_float/e_float.cpp ../src/e_float/e_float_base.cpp ../src/functions/constants/constants.cpp ../src/functions/elementary/elementary_complex.cpp ../src/functions/elementary/elementary_hyper_g.cpp ../src/functions/elementary/elementary_math.cpp ../src/functions/elementary/elementary_trans.cpp ../src/functions/elementary/elementary_trig.cpp ../test_boost/test_boost.cpp -o test_boost.exe

namespace
{
  using big_float_type = boost::multiprecision::number<boost::math::ef::e_float,
                                                       boost::multiprecision::et_off>;
}

int main()
{
  const big_float_type x(0.5F);

  const big_float_type g = boost::math::tgamma(x);

  const big_float_type sqrt_pi = boost::math::constants::root_pi<big_float_type>();

  const big_float_type ratio = g / sqrt_pi;
  const big_float_type delta = fabs(1 - ratio);

  const bool result_is_ok = delta < std::numeric_limits<big_float_type>::epsilon() * 10U;

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;

  return result_is_ok ? 0 : -1;
}
