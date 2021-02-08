
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <algorithm>

#include <boost/e_float/e_float_functions.hpp>

#include "prime_factors.h"

namespace Primes
{
  std::deque<std::uint32_t>& Data();

  static bool IsPrimeFactor(std::uint32_t& np, const std::uint32_t p)
  {
    const std::uint32_t q = static_cast<std::uint32_t>(np / p);
    const std::uint32_t r = static_cast<std::uint32_t>(np - static_cast<std::uint32_t>(q * p));

    const bool is_prime_factor = (r == static_cast<std::uint32_t>(0U));

    if(is_prime_factor)
    {
      np = q;
    }
    
    return is_prime_factor;
  }

  static void Factors(const std::uint32_t n, std::deque<Util::point<std::uint32_t>>& pf)
  {
    // Compute the prime factors of the unsigned integer n. Use the divide algorithm of
    // "The Art of Computer Programming Volume 2 Semi-numerical Algorithms Third Edition",
    // Donald Knuth (Algorithm A, Chapter 4.5.4, page 380 and pages 378-417).
    static const std::size_t sz = Data().size();

    pf.clear();

    const std::uint32_t sqrt_n = static_cast<std::uint32_t>(static_cast<std::uint64_t>(::sqrt(static_cast<double>(n)) + 0.5));

    std::uint32_t np = n;

    for(std::size_t i = static_cast<std::size_t>(0U); i < sz; i++)
    {
      const std::uint32_t p = Data()[i];

      if(IsPrimeFactor(np, p))
      {
        Util::point<std::uint32_t> ip(p, static_cast<std::uint32_t>(1U));

        while(IsPrimeFactor(np, p))
        {
          ++ip.y;
        }

        pf.push_back(ip);
      }

      if(static_cast<std::uint32_t>(np / p) <= p)
      {
        pf.push_back(Util::point<std::uint32_t>(np, static_cast<std::uint32_t>(1U)));

        break;
      }

      if((np == static_cast<std::uint32_t>(1U)) || (p >= sqrt_n))
      {
        break;
      }
    }
  }
}

void ef::prime_factors(const std::uint32_t n, std::deque<Util::point<std::uint32_t>>& pf)
{
  // Factor the input integer into a list of primes. For small inputs less than 10,000
  // use the tabulated prime factors list. Calculate the prime factors for larger inputs
  // above 10,000.
  static std::vector<std::deque<Util::point<std::uint32_t>>> prime_factors_list;

  if(prime_factors_list.empty())
  {
    // Generate a table of the sets of the first 10,000 integer prime factorizations.
    prime_factors_list.resize(static_cast<std::size_t>(10000U));

    prime_factors_list[static_cast<std::size_t>(0U)] = std::deque<Util::point<std::uint32_t>>(static_cast<std::size_t>(1U), Util::point<std::uint32_t>(static_cast<std::uint32_t>(0U), static_cast<std::uint32_t>(1U)));
    prime_factors_list[static_cast<std::size_t>(1U)] = std::deque<Util::point<std::uint32_t>>(static_cast<std::size_t>(1U), Util::point<std::uint32_t>(static_cast<std::uint32_t>(1U), static_cast<std::uint32_t>(1U)));
    prime_factors_list[static_cast<std::size_t>(2U)] = std::deque<Util::point<std::uint32_t>>(static_cast<std::size_t>(1U), Util::point<std::uint32_t>(static_cast<std::uint32_t>(2U), static_cast<std::uint32_t>(1U)));
    prime_factors_list[static_cast<std::size_t>(3U)] = std::deque<Util::point<std::uint32_t>>(static_cast<std::size_t>(1U), Util::point<std::uint32_t>(static_cast<std::uint32_t>(3U), static_cast<std::uint32_t>(1U)));

    static const std::uint32_t n_five = static_cast<std::uint32_t>(5U);

    std::deque<std::uint32_t>::const_iterator it_next_prime =
      std::find(Primes::Data().cbegin(),
                Primes::Data().cend(),
                n_five);

    for(std::size_t i = static_cast<std::size_t>(4U); i < prime_factors_list.size(); i++)
    {
      if((it_next_prime != Primes::Data().cend()) && (static_cast<std::uint32_t>(i) == *it_next_prime))
      {
        ++it_next_prime;

        prime_factors_list[i] =
          std::deque<Util::point<std::uint32_t>>(static_cast<std::size_t>(1U),
                                                 Util::point<std::uint32_t>(static_cast<std::uint32_t>(i),
                                                 static_cast<std::uint32_t>(1U)));
      }
      else
      {
        Primes::Factors(static_cast<std::uint32_t>(i), prime_factors_list[i]);
      }
    }
  }

  if(static_cast<std::size_t>(n) < prime_factors_list.size())
  {
    pf = prime_factors_list[static_cast<std::size_t>(n)];
  }
  else
  {
    Primes::Factors(n, pf);
  }
}
