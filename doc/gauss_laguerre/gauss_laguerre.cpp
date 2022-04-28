#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>

#include <boost/math/special_functions/cbrt.hpp>
#include <boost/math/special_functions/airy.hpp>
#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/tools/roots.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

namespace gauss_laguerre_abscissas_and_weights
{
  namespace detail
  {
    template<typename result_type>
    boost::math::tuple<result_type, result_type, result_type>
    my_generalized_laguerre_its_predecessor_and_its_derivative(const int n,
                                                               const result_type& alpha,
                                                               const result_type& x)
    {
      // Perform the generalized Laguerre recursion.
      result_type p_minus_one(1);
      result_type p_minus_2(0);

      for(unsigned j = 0U; j <= unsigned(n); ++j)
      {
        const result_type p_minus_3(p_minus_2);
        p_minus_2 = p_minus_one;

        const unsigned j_plus_one     = j + 1U;
        const unsigned two_j_plus_one = j + j_plus_one;

        p_minus_one = (((two_j_plus_one + (alpha - x)) * p_minus_2) - ((j + alpha) * p_minus_3)) / j_plus_one;
      }

      const result_type my_laguerre_derivative(((n * p_minus_one) - ((n + alpha) * p_minus_2)) / x);

      return boost::math::tuple<result_type, result_type, result_type>(p_minus_2, p_minus_one, my_laguerre_derivative);
    }

    template<typename result_type, const unsigned N_LAGUERRE>
    result_type equation_tricomi_extended(const result_type& am, const result_type& alpha)
    {
      // Return an estimate of the m'th root of a generalized Laguerre
      // polynomial using an extended Tricomi-type expansion.
      const result_type v                     ((result_type(N_LAGUERRE) * 4U) + (alpha * 2U) + 2);
      const result_type v_pow_third           (boost::math::cbrt(v));
      const result_type v_pow_minus_two_thirds(result_type(1) / (v_pow_third * v_pow_third));

      const result_type am_squared (am * am);
      const result_type am_pow_four(am_squared * am_squared);

      const result_type term9 =  (((result_type(15152.0) / 3031875UL) * (am_pow_four * am))
                                + ((result_type(1088.0) / 121275UL) * am_squared)) * result_type(1.25992104989487316476721);
      const result_type term7 =  (((result_type(16.0) / 1575U) * am)
                                + ((result_type(92.0) / 7875U) * am_pow_four)) * result_type(1.58740105196819947475171);
      const result_type term5 =   ((result_type(11.0) / 35U) - (alpha * alpha))
                                - ((result_type(12.0) / 175U) * (am_squared * am));
      const result_type term3 = am_squared * result_type(0.503968419957949265906884);
      const result_type term1 = am * result_type(1.58740105196819947475171);

      return v * (((((                         - term9
                      * v_pow_minus_two_thirds + term7)
                      * v_pow_minus_two_thirds + term5)
                      * v_pow_minus_two_thirds + term3)
                      * v_pow_minus_two_thirds + term1)
                      * v_pow_minus_two_thirds + result_type(1));
    }

    template<typename result_type, const unsigned N_LAGUERRE>
    result_type equation_bessel_j0_approx(const result_type& j0m, const result_type& alpha)
    {
      // Return an estimate of the m'th root of a generalized Laguerre
      // polynomial using an expansion in the roots of J0.
      const result_type v((result_type(N_LAGUERRE) * 4U) + (alpha * 2U) + 2);
      const result_type j0m_squared(j0m * j0m);

      return (j0m_squared / v) * (result_type(1) + ((j0m_squared - 2) / (v * v * 3U)));
    }
  }
}

namespace gauss_laguerre_abscissas_and_weights
{
  template<typename result_type, const unsigned N_LAGUERRE>
  void generate(std::vector<result_type>& abscissas,
                std::vector<result_type>& weights,
                const result_type& alpha = result_type(0))
  {
    // Generate estimates for the abscissas (i.e., the roots xi of Ln).
    std::vector<result_type> abscissa_estimates(N_LAGUERRE);

    const unsigned cutoff = static_cast<unsigned>((abscissa_estimates.size() / 2U) - 1U);
    unsigned m_root = 0U;

    std::for_each(abscissa_estimates.begin(),
                  abscissa_estimates.end(),
                  [&alpha, &cutoff, &m_root](result_type& this_root_estimate)
    {
      typedef result_type local_result_type;

        // Take the Tricomi results for the early roots and the
        // asymptotic Airy-type results for the late roots.
        this_root_estimate =
          ((m_root < cutoff)
            ? detail::equation_bessel_j0_approx<result_type, N_LAGUERRE>(boost::math::cyl_bessel_j_zero(result_type(0), unsigned(m_root + 1U)),         alpha)
            : detail::equation_tricomi_extended<result_type, N_LAGUERRE>(boost::math::airy_ai_zero     (result_type(0), unsigned(N_LAGUERRE - m_root)), alpha));

        ++m_root;
    });

    // We now have estimates of the abscissas. Calculate the abscissas
    // and weights to full precision using Newton-Raphson iteration.
    abscissas.clear();
    abscissas.resize(N_LAGUERRE);

    weights.clear();
    weights.resize(N_LAGUERRE);

    result_type previous_root_estimate(0);

    for(std::vector<result_type>::size_type count = 0U; count < abscissa_estimates.size(); ++count)
    {
      // Get the estimate of this root (the abscissa).
      const result_type this_root_estimate = abscissa_estimates[count];

      // Establish the range for the root finding.
      const result_type delta((this_root_estimate - previous_root_estimate) / 2U);

      previous_root_estimate = this_root_estimate;

      // Select the maximum allowed iterations, being at least 32.
      boost::uintmax_t number_of_iterations = (std::max)(32, int(std::numeric_limits<result_type>::digits10));

      // Select the desired number of binary digits of precision.
      // Account for the radix of number representations having non-two radix!
      const int my_digits2 = int(float(std::numeric_limits<result_type>::digits)
                                  * (  std::log(float(std::numeric_limits<result_type>::radix))
                                    / std::log(2.0F)));

      // Define subroutine-local mimics for the necessary template parameters.
      typedef result_type local_result_type;
      const int my_n_laguerre(N_LAGUERRE);
      const local_result_type my_alpha(alpha);
      boost::math::tuple<result_type, result_type, result_type> my_laguerres;

      // Perform the generalized Legendre root-finding using
      // Newton-Raphson iteration from Boost.Math.
      const result_type lnm =
        boost::math::tools::newton_raphson_iterate(
            [&my_n_laguerre, &my_alpha, &my_laguerres](const local_result_type& xi) -> boost::math::tuple<local_result_type, local_result_type>
            {
              my_laguerres =
                detail::my_generalized_laguerre_its_predecessor_and_its_derivative<local_result_type>(my_n_laguerre,
                                                                                                      my_alpha,
                                                                                                      xi);

              return
                boost::math::tuple<local_result_type, local_result_type>(boost::math::get<0>(my_laguerres),
                                                                          boost::math::get<2>(my_laguerres));
            },
            local_result_type(this_root_estimate),
            local_result_type(this_root_estimate - delta),
            local_result_type(this_root_estimate + delta),
            my_digits2,
            number_of_iterations);

      static_cast<void>(number_of_iterations);

      abscissas[count] = lnm;

      const int n_plus_one(my_n_laguerre + 1U);

      const local_result_type laguerre_n_plus_one(boost::math::get<1>(my_laguerres));

      weights[count] = ((lnm / (laguerre_n_plus_one * laguerre_n_plus_one)) / n_plus_one) / n_plus_one;
    }

/*
       const bool alpha_is_zero = (   (alpha > -std::numeric_limits<result_type>::epsilon())
                                   && (alpha < +std::numeric_limits<result_type>::epsilon()));


       if(alpha_is_zero)
       {
         return result_type(-1) / ((d * N) * rooti.poly_p2()));
       }
       else
       {
         const e_float norm_g = ef::gamma(alpha + N) / ef::factorial(static_cast<UINT32>(N - static_cast<INT32>(1)));
         wi.push_back(-norm_g / ((d * N) * rooti.poly_p2()));
       }
*/
  }
}

template<typename abscissas_iterator,
         typename weights_iterator,
         typename function_type,
         typename result_type>
result_type gauss_laguerre_quadrature(function_type function,
                                      abscissas_iterator abscissas_first,
                                      abscissas_iterator abscissas_last,
                                      weights_iterator weights_first,
                                      result_type dummy)
{
  std::size_t count = std::distance(abscissas_first, abscissas_last);

  result_type sum(0);

  for(std::size_t i = 0U; i < count; ++i)
  {
    const result_type fi = function(*(abscissas_first + i));
    const result_type wi = *(weights_first + i);

    sum += (fi * wi);
  }

  return sum;
}

using std::sqrt;
using std::exp;

int main(int, char**)
{
  typedef boost::multiprecision::cpp_dec_float<50> mp_backend;
  typedef boost::multiprecision::number<mp_backend, boost::multiprecision::et_off> mp_type;
  typedef mp_type float_type;

  std::vector<float_type> abscissas;
  std::vector<float_type> weights;

  // Generate Gauss-Laguerre abscissas and weights.
  // Use  72 coefficients for  50 digits.
  // Use 136 coefficients for 100 digits.
  // Use 200 coefficients for 200 digits.
  // Use 400 coefficients for 300 digits.
  gauss_laguerre_abscissas_and_weights::generate<float_type, 24U>(abscissas, weights, float_type(0));

  std::cout.precision(std::numeric_limits<float_type>::digits10);

  std::cout << "Abscissas" << std::endl << std::endl;

  std::copy(abscissas.begin(),
            abscissas.end(),
            std::ostream_iterator<mp_type>(std::cout, "\n"));

  std::cout << "Weights" << std::endl << std::endl;

  std::copy(weights.begin(),
            weights.end(),
            std::ostream_iterator<mp_type>(std::cout, "\n"));
/*
  static const float_type gamma_five_sixths("1.1287870299081259612609010902588420133267874416647554517520835143337705109875039870554009044384097574651414895632092190032153001729173859324259075926435937047406251883625786073902264067770947161343479804032184370920318132558529534388950980545214237496211505603650295768508721789931986675254357421442232878277247366281981674795944091591205039186141350573400691924852380789937290356700150344797693714826");

  const float_type x = float_type(19) / 7U;

  const float_type zeta                    = ((sqrt(x) * x) * 2U) / 3U;
  const float_type zeta_times_48           = zeta * 48U;
  const float_type zeta_times_48_pow_sixth = sqrt(boost::math::cbrt(zeta_times_48));
  const float_type factor                  = (boost::math::constants::root_pi<float_type>() * zeta_times_48_pow_sixth) * (exp(zeta) * gamma_five_sixths);

  float_type ai = gauss_laguerre_quadrature(
    [&zeta, &factor](const float_type& t) -> float_type
    {
      const float_type one_over_zeta = float_type(1) / zeta;

      return float_type(1) / (factor * sqrt(boost::math::cbrt(float_type(2) + (t * one_over_zeta))));
    },
    abscissas.begin(),
    abscissas.end(),
    weights.begin(),
    float_type(0U));

  std::cout.precision(std::numeric_limits<float_type>::digits10);

  std::cout << ai << std::endl << std::endl;
  std::cout << boost::math::airy_ai(x) << std::endl;
*/
}
