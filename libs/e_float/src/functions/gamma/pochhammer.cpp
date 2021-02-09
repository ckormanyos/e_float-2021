
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <e_float/e_float_complex.h>
#include <e_float/e_float_functions.h>
#include <e_float/e_float_functions_complex.h>

namespace Pochhammer_Series
{
  template<typename T,
           typename TR>
  T Pochhammer_Template(const T& x, const std::uint32_t n)
  {
    using ef::real;
    using ef::real;
    using ef::gamma;
    using ef::gamma;
    using ef::one;

    if(n == static_cast<std::uint32_t>(0U))
    {
      return one();
    }
    else if(n == static_cast<std::uint32_t>(1U))
    {
      return x;
    }
    else
    {
      if(n < static_cast<std::uint32_t>(50U))
      {
        T val (x);
        T term(x);

        for(std::uint32_t i = static_cast<std::uint32_t>(1U); i < n; i++)
        {
          term += TR(1U);

          val *= term;
        }

        return val;
      }
      else
      {
        const TR nr(n);

        return gamma(x + nr) / gamma(x);
      }
    }
  }
}

e_float ef::pochhammer(const e_float& x, const std::uint32_t n)
{
  return Pochhammer_Series::Pochhammer_Template<e_float, e_float>(x, n);
}

ef::complex<e_float> ef::pochhammer(const ef::complex<e_float>& x, const std::uint32_t n)
{
  return Pochhammer_Series::Pochhammer_Template<ef::complex<e_float>, e_float>(x, n);
}

e_float ef::pochhammer(const e_float& x, const e_float& a)
{
  return ef::gamma(x + a) / ef::gamma(x);
}

ef::complex<e_float> ef::pochhammer(const ef::complex<e_float>& z, const ef::complex<e_float>& a)
{
  return ef::gamma(z + a) / ef::gamma(z);
}

