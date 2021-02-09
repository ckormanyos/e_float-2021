
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <e_float/e_float_functions.h>
#include <e_float/detail/e_float_detail_pown_template.h>

#include <functions/integer/prime_factors.h>
#include <utility/util_point.h>
#include <utility/util_power_j_pow_x.h>

namespace Util
{
  static e_float logn(const std::uint32_t n)
  {
    static std::map<std::uint32_t, e_float> ln_data;

    const std::map<std::uint32_t, e_float>::const_iterator it = ln_data.find(n);

    if(it == ln_data.cend())
    {
      const e_float ln = ef::log(e_float(n));

      ln_data[n] = ln;

      return ln;
    }
    else
    {
      return it->second;
    }
  }

  template<typename T> inline T j_pow_x_template(const std::uint32_t j, const T& x, std::map<std::uint32_t, T>& n_pow_x_prime_factor_map)
  {
    using ef::exp;
    using ef::imag;
    using ef::isint;
    using ef::iszero;
    using ef::real;

    std::deque<Util::point<std::uint32_t>> pf;

    ef::prime_factors(j, pf);

    T jpx = ef::one();

    for(std::size_t i = static_cast<std::size_t>(0U); i < pf.size(); i++)
    {
      T pf_pow_x;

      const std::uint32_t n = pf[i].x;
      const std::uint32_t p = pf[i].y;

      const typename std::map<std::uint32_t, T>::const_iterator it = n_pow_x_prime_factor_map.find(n);

      if(it == n_pow_x_prime_factor_map.cend())
      {
        // Compute n^x using exp[x * log(n)] and use the map data in the Zeta::logn(...).
        // Obtain the necessary integer logarithms from a table.
        if(iszero(imag(x)) && isint(real(x)))
        {
          const e_float rx = real(x);

          // Compute pure integer power for pure integer arguments.
          if((rx < ef::int64_max()) && (rx > ef::int64_min()))
          {
            pf_pow_x = ef::detail::pown_template(T(n), ef::to_int64(rx));
          }
          else
          {
            pf_pow_x = exp(x * Util::logn(n));
          }
        }
        else
        {
          pf_pow_x = exp(x * Util::logn(n));
        }

        n_pow_x_prime_factor_map[n] = pf_pow_x;
      }
      else
      {
        pf_pow_x = it->second;
      }

      // Do the power expansion.
      if     (p == static_cast<std::uint32_t>(1U)) { }
      else if(p == static_cast<std::uint32_t>(2U)) { pf_pow_x *=  pf_pow_x; }
      else if(p == static_cast<std::uint32_t>(3U)) { pf_pow_x *= (pf_pow_x * pf_pow_x); }
      else
      {
        pf_pow_x *= ef::detail::pown_template(pf_pow_x, static_cast<std::int64_t>(p - 1U));
      }

      jpx *= pf_pow_x;
    }

    return jpx;
  }
}

e_float    Util::j_pow_x(const std::uint32_t j, const e_float&    x, std::map<std::uint32_t, e_float>&    n_pow_x_prime_factor_map) { return Util::j_pow_x_template<e_float>   (j, x, n_pow_x_prime_factor_map); }
ef::complex<e_float> Util::j_pow_x(const std::uint32_t j, const ef::complex<e_float>& x, std::map<std::uint32_t, ef::complex<e_float>>& n_pow_x_prime_factor_map) { return Util::j_pow_x_template<ef::complex<e_float>>(j, x, n_pow_x_prime_factor_map); }
