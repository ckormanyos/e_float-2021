
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <algorithm>

#include <e_float/e_float_functions.h>
#include <e_float/detail/e_float_detail_pown_template.h>

#include <functions/tables/tables.h>

e_float ef::bernoulli(const std::uint32_t n)
{
  if(static_cast<std::uint32_t>(n % static_cast<std::uint32_t>(2U)) != static_cast<std::uint32_t>(0U))
  {
    return (n == static_cast<std::uint32_t>(1U) ? -ef::half() : ef::zero());
  }
  else
  {
    static const std::size_t sz_A000367 = Tables::A000367().size();
    static const std::size_t sz_A002445 = Tables::A002445().size();
    static const std::size_t sz_max     = (std::min)(sz_A000367, sz_A002445);

    const std::size_t n_half = static_cast<std::size_t>(n / static_cast<std::uint32_t>(2U));

    if(n_half < sz_max)
    {
      return Tables::A000367()[n_half]() / Tables::A002445()[n_half]();
    }
    else
    {
      // Do a loop calculation for higher numbered Bernoulli numbers.
      // See Abramowitz & Stegun 23.1.18, page 805, for x = 0.
      // See Computation of Special Functions, Zhang & Jin, 1.1.16, page 5.

      e_float sum = ef::one();

      // TBD: Check the power of two using logs and floating point math to see
      //      if the loop is even necessary.

      for(std::int32_t k = static_cast<std::int32_t>(2); k < ef::max_iteration(); k++)
      {
        const e_float one_over_k = ef::one() / k;
        const e_float term       = ef::detail::pown_template(one_over_k, static_cast<std::int64_t>(n));
        
        if(term.order() < -ef::tolerance())
        {
          break;
        }

        sum += term;
      }

      const bool b_neg = static_cast<std::uint32_t>(static_cast<std::uint32_t>(n / static_cast<std::uint32_t>(2U)) & static_cast<std::uint32_t>(1U)) == static_cast<std::uint32_t>(0U);

      const e_float factor = ((ef::factorial(n) / ef::detail::pown_template(ef::two_pi(), static_cast<std::int64_t>(n))) * static_cast<std::int32_t>(2));
      const e_float bn     = sum * factor;

      return ((!b_neg) ? bn : -bn);
    }
  }
}

void ef::bernoulli_table(std::vector<e_float>& bn, const std::uint32_t n)
{
  // See reference "Computing Bernoulli and Tangent Numbers", Richard P. Brent.
  // Also see "Modern Computer Arithmetic", Richard P. Brent and Paul Zimmermann,
  // Cambridge University Press, 2010, 237 pp.

  const std::uint32_t nn = (((n % static_cast<std::uint32_t>(2)) != static_cast<std::uint32_t>(0U)) ? static_cast<std::uint32_t>(n + 1U) : n);

  const std::int32_t m = static_cast<std::int32_t>(nn / static_cast<std::uint32_t>(2U));

  std::vector<e_float> tangent_numbers(static_cast<std::vector<e_float>::size_type>(m + 1));

  tangent_numbers[0U] = ef::zero();
  tangent_numbers[1U] = ef::one();

  for(std::int32_t k = static_cast<std::int32_t>(2); k <= m; k++)
  {
    tangent_numbers[static_cast<std::size_t>(k)] = tangent_numbers[static_cast<std::size_t>(k - 1)] * static_cast<std::int32_t>(k - static_cast<std::int32_t>(1));
  }

  for(std::int32_t k = static_cast<std::int32_t>(2); k <= m; k++)
  {
    for(std::int32_t j = k; j <= m; j++)
    {
      const std::int32_t j_minus_k = static_cast<std::int32_t>(j - k);

      tangent_numbers[static_cast<std::size_t>(j)] =   (tangent_numbers[static_cast<std::size_t>(j - 1)] * j_minus_k)
                                                     + (tangent_numbers[static_cast<std::size_t>(j)] * static_cast<std::int32_t>(j_minus_k + static_cast<std::int32_t>(2)));
    }
  }

  e_float two_pow_two_m(4);

  bn.clear();
  bn.resize(static_cast<std::vector<e_float>::size_type>(nn + static_cast<std::uint32_t>(1U)));

  for(std::int32_t i = static_cast<std::int32_t>(1); i < static_cast<std::int32_t>(tangent_numbers.size()); i++)
  {
    const std::int32_t two_i = static_cast<std::int32_t>(static_cast<std::int32_t>(2) * i);

    const e_float b = (tangent_numbers[static_cast<std::size_t>(i)] * two_i) / ((two_pow_two_m * two_pow_two_m) - two_pow_two_m);

    const bool  b_neg = (static_cast<std::int32_t>(two_i % static_cast<std::int32_t>(4)) == static_cast<std::int32_t>(0));

    bn[static_cast<std::size_t>(2 * i)] = ((!b_neg) ? b : -b);

    two_pow_two_m *= static_cast<std::int32_t>(4);
  }

  bn[0U] =  ef::one();
  bn[1U] = -ef::half();
}
