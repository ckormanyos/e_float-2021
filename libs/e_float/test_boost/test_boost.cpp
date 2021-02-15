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

// g++ -Wall -Wextra -m64 -O3 -std=gnu++11 -DE_FLOAT_TYPE_EFX -I../../../libs/e_float/src -IC:/boost/modular_boost/boost/libs/multiprecision/include -IC:/boost/modular_boost/boost/libs/math/include -IC:/boost/boost_1_75_0 ../src/e_float/efx/e_float_efx.cpp ../src/e_float/e_float.cpp ../src/e_float/e_float_base.cpp ../src/functions/constants/constants.cpp ../src/functions/elementary/elementary_complex.cpp ../src/functions/elementary/elementary_hyper_g.cpp ../src/functions/elementary/elementary_math.cpp ../src/functions/elementary/elementary_trans.cpp ../src/functions/elementary/elementary_trig.cpp ../test_boost/test_boost.cpp -o test_boost.exe

namespace local
{
  using big_float_type = boost::multiprecision::number<boost::math::ef::e_float,
                                                       boost::multiprecision::et_off>;

  template<typename FloatingPointType>
  FloatingPointType hypergeometric_2f1(const FloatingPointType& a,
                                       const FloatingPointType& b,
                                       const FloatingPointType& c,
                                       const FloatingPointType& x)
  {
    // Compute the series representation of hypergeometric_2f1
    // taken from Abramowitz and Stegun 15.1.1.
    // There are no checks on input range or parameter boundaries.

    FloatingPointType x_pow_n_div_n_fact(x);
    FloatingPointType pochham_a         (a);
    FloatingPointType pochham_b         (b);
    FloatingPointType pochham_c         (c);
    FloatingPointType ap                (a);
    FloatingPointType bp                (b);
    FloatingPointType cp                (c);

    FloatingPointType h2f1 = 1 + (((pochham_a * pochham_b) / pochham_c) * x_pow_n_div_n_fact);

    const FloatingPointType tol = std::numeric_limits<FloatingPointType>::epsilon() * x;

    // Series expansion of hyperg_2f1(a, b; c; x).
    for(std::int32_t n = INT32_C(2); n < INT32_C(100000); ++n)
    {
      x_pow_n_div_n_fact *= x;
      x_pow_n_div_n_fact /= n;

      pochham_a *= ++ap;
      pochham_b *= ++bp;
      pochham_c *= ++cp;

      const FloatingPointType term = ((pochham_a * pochham_b) / pochham_c) * x_pow_n_div_n_fact;

      using std::fabs;

      if((n > 11) && (fabs(term) < tol))
      {
        break;
      }

      h2f1 += term;
    }

    return h2f1;
  }

  template<typename FloatingPointType>
  FloatingPointType legendre_p2(const FloatingPointType& v,
                                const FloatingPointType& u,
                                const FloatingPointType& x)
  {
    using std::pow;

    // See also the third series representation provided in:
    // https://functions.wolfram.com/HypergeometricFunctions/LegendreP2General/06/01/04/

    const FloatingPointType u_half       = u / 2U;
    const FloatingPointType one_minus_x  = 1U - x;
    const FloatingPointType one_minus_mu = 1U - u;

    const FloatingPointType tgamma_term  = boost::math::tgamma(one_minus_mu);
    const FloatingPointType h2f1_term    = hypergeometric_2f1(-v,
                                                              1U + v,
                                                              one_minus_mu,
                                                              one_minus_x / 2U);

    return     (pow(1U + x,      u_half) * h2f1_term)
             / (pow(one_minus_x, u_half) * tgamma_term);
  }
}

bool test___tgamma()
{
  const local::big_float_type x(0.5F);

  const local::big_float_type g       = boost::math::tgamma(x);
  const local::big_float_type sqrt_pi = boost::math::constants::root_pi<local::big_float_type>();

  std::cout << std::setprecision(std::numeric_limits<local::big_float_type>::digits10) << g       << std::endl;
  std::cout << std::setprecision(std::numeric_limits<local::big_float_type>::digits10) << sqrt_pi << std::endl;

  const local::big_float_type ratio = g / sqrt_pi;
  const local::big_float_type delta = fabs(1 - ratio);

  const bool result_is_ok = delta < std::numeric_limits<local::big_float_type>::epsilon() * 10U;

  return result_is_ok;
}

bool test_legendre()
{
  const local::big_float_type x = local::big_float_type(UINT32_C(789)) / 1000U;

  // Compute some values of the Legendre function of the second kind
  // on the real axis within the unit circle.

  // N[LegendreP[1/3, 1/7, 2, 789/1000], 1001]
  const local::big_float_type lp2 = local::legendre_p2(local::big_float_type(1U) / 3,
                                                       local::big_float_type(1U) / 7,
                                                       x);

  const local::big_float_type control
  {
    "0."
    "9931591854934064572568089793337657296924109412673643417874724597677037521767383011114922218212896908"
    "0027"
  };

  std::cout << std::setprecision(std::numeric_limits<local::big_float_type>::digits10) << lp2     << std::endl;
  std::cout << std::setprecision(std::numeric_limits<local::big_float_type>::digits10) << control << std::endl;

  using std::fabs;

  const local::big_float_type closeness = fabs(1 - (lp2 / control));

  const bool result_is_ok = closeness < (std::numeric_limits<local::big_float_type>::epsilon() * UINT32_C(10000000));

  return result_is_ok;
}

int main()
{
  const bool test_tgamma___is_ok = test___tgamma();
  const bool test_legendre_is_ok = test_legendre();

  std::cout << "test_tgamma___is_ok: " << std::boolalpha << test_tgamma___is_ok << std::endl;
  std::cout << "test_legendre_is_ok: " << std::boolalpha << test_legendre_is_ok << std::endl;

  const bool result_is_ok = (test_tgamma___is_ok && test_legendre_is_ok);

  return result_is_ok ? 0 : -1;
}
