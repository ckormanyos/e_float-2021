//          Copyright Christopher Kormanyos 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/math/bindings/e_float.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/multiprecision/number.hpp>

// cd C:\Users\User\Documents\Ks\PC_Software\NumericalPrograms\ExtendedNumberTypes\e_float\libs\e_float\build

// g++ -Wall -Wextra -m64 -O3 -std=gnu++11 -DE_FLOAT_TYPE_EFX -I../../../libs/e_float/src -IC:/boost/modular_boost/boost/libs/multiprecision/include -IC:/boost/modular_boost/boost/libs/math/include -IC:/boost/boost_1_75_0 ../src/e_float/efx/e_float_efx.cpp ../src/e_float/e_float.cpp ../src/e_float/e_float_base.cpp ../src/functions/constants/constants.cpp ../src/functions/elementary/elementary_complex.cpp ../src/functions/elementary/elementary_hyper_g.cpp ../src/functions/elementary/elementary_math.cpp ../src/functions/elementary/elementary_trans.cpp ../src/functions/elementary/elementary_trig.cpp ../test_boost/test_boost.cpp -o test_boost.exe

namespace local
{
  using big_float_type = boost::multiprecision::number<boost::math::ef::e_float, boost::multiprecision::et_off>;

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
  FloatingPointType hypergeometric_2f1_regularized(const FloatingPointType& a,
                                                   const FloatingPointType& b,
                                                   const FloatingPointType& c,
                                                   const FloatingPointType& x)
  {
    return hypergeometric_2f1(a, b, c, x) / boost::math::tgamma(c);
  }

  template<typename FloatingPointType>
  FloatingPointType pochhammer(const FloatingPointType& x,
                               const FloatingPointType& a)
  {
    return boost::math::tgamma(x + a) / boost::math::tgamma(x);
  }

  template<typename FloatingPointType>
  FloatingPointType legendre_pvu(const FloatingPointType& v,
                                 const FloatingPointType& u,
                                 const FloatingPointType& x)
  {
    using std::pow;

    // See also the third series representation provided in:
    // https://functions.wolfram.com/HypergeometricFunctions/LegendreP2General/06/01/04/

    const FloatingPointType u_half       = u / 2U;
    const FloatingPointType one_minus_x  = 1U - x;
    const FloatingPointType one_minus_mu = 1U - u;

    const FloatingPointType tgamma_term    = boost::math::tgamma(one_minus_mu);
    const FloatingPointType h2f1_reg_term  = hypergeometric_2f1_regularized(FloatingPointType(-v),
                                                                            FloatingPointType(1U + v),
                                                                            one_minus_mu,
                                                                            FloatingPointType(one_minus_x / 2U));

    return (pow(1U + x, u_half) * h2f1_reg_term) / pow(one_minus_x, u_half);
  }

  template<typename FloatingPointType>
  FloatingPointType legendre_qvu(const FloatingPointType& v,
                                 const FloatingPointType& u,
                                 const FloatingPointType& x)
  {
    using std::cos;
    using std::pow;
    using std::sin;

    // See also the third series representation provided in:
    // https://functions.wolfram.com/HypergeometricFunctions/LegendreQ2General/06/01/02/

    const FloatingPointType u_pi     = u * boost::math::constants::pi<FloatingPointType>();
    const FloatingPointType sin_u_pi = sin(u_pi);
    const FloatingPointType cos_u_pi = cos(u_pi);

    const FloatingPointType one_minus_x          = 1U - x;
    const FloatingPointType one_plus_x           = 1U + x;
    const FloatingPointType u_half               = u / 2U;
    const FloatingPointType one_minus_x_over_two = one_minus_x / 2U;

    const FloatingPointType one_plus_x_over_one_minus_x_pow_u_half = pow(one_plus_x / one_minus_x, u_half);

    const FloatingPointType v_plus_one =  v + 1U;

    const FloatingPointType h2f1_1 = hypergeometric_2f1_regularized(FloatingPointType(-v), v_plus_one, FloatingPointType(1U - u), one_minus_x_over_two);
    const FloatingPointType h2f1_2 = hypergeometric_2f1_regularized(FloatingPointType(-v), v_plus_one, FloatingPointType(1U + u), one_minus_x_over_two);

    const FloatingPointType term1 = (h2f1_1 * one_plus_x_over_one_minus_x_pow_u_half) * cos_u_pi;
    const FloatingPointType term2 = (h2f1_2 / one_plus_x_over_one_minus_x_pow_u_half) * pochhammer(FloatingPointType(v_plus_one - u), FloatingPointType(u * 2U));

    return (boost::math::constants::half_pi<FloatingPointType>() * (term1 - term2)) / sin_u_pi;
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

  const local::big_float_type lpvu = local::legendre_pvu(local::big_float_type(local::big_float_type(1U) / 3),
                                                         local::big_float_type(local::big_float_type(1U) / 7),
                                                         x);

  const local::big_float_type lqvu = local::legendre_qvu(local::big_float_type(local::big_float_type(1U) / 3),
                                                         local::big_float_type(local::big_float_type(1U) / 7),
                                                         x);

  // N[LegendreP[1/3, 1/7, 2, 789/1000], 104]
  const local::big_float_type control_lpvu
  {
    "0.99315918549340645725680897933376572969241094126736434178747245976770375217673830111149222182128969080027"
  };

  // N[LegendreQ[1/3, 1/7, 2, 789/1000], 104]
  const local::big_float_type control_lqvu
  {
    "0.18027013586354735033576549475861160812128148962186378344662781978695122523958952227406954299821460356031"
  };

  std::cout << std::setprecision(std::numeric_limits<local::big_float_type>::digits10) << lpvu         << std::endl;
  std::cout << std::setprecision(std::numeric_limits<local::big_float_type>::digits10) << control_lpvu << std::endl;
  std::cout << std::setprecision(std::numeric_limits<local::big_float_type>::digits10) << lqvu         << std::endl;
  std::cout << std::setprecision(std::numeric_limits<local::big_float_type>::digits10) << control_lqvu << std::endl;

  using std::fabs;

  const local::big_float_type closeness_lpvu = fabs(1 - (lpvu / control_lpvu));
  const local::big_float_type closeness_lqvu = fabs(1 - (lqvu / control_lqvu));

  const bool result_lpvu_is_ok = (closeness_lpvu < (std::numeric_limits<local::big_float_type>::epsilon() * UINT32_C(10000000)));
  const bool result_lqvu_is_ok = (closeness_lqvu < (std::numeric_limits<local::big_float_type>::epsilon() * UINT32_C(10000000)));

  const bool result_is_ok = (result_lpvu_is_ok && result_lqvu_is_ok);

  return result_is_ok;
}

bool test_boost_sf()
{
  const bool test_tgamma___is_ok = test___tgamma();
  const bool test_legendre_is_ok = test_legendre();

  std::cout << "test_tgamma___is_ok: " << std::boolalpha << test_tgamma___is_ok << std::endl;
  std::cout << "test_legendre_is_ok: " << std::boolalpha << test_legendre_is_ok << std::endl;

  const bool result_is_ok = (test_tgamma___is_ok && test_legendre_is_ok);

  return result_is_ok;
}
