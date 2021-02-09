
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iterator>

#include <e_float/e_float_functions.h>

namespace Primes
{
  struct Inserter final
  {
  public:
    static const std::size_t start_index = static_cast<std::size_t>(2U);

    explicit Inserter(std::deque<std::uint32_t>& sequence)
      : count  (static_cast<std::uint32_t>(start_index)),
        back_it(std::back_inserter(sequence)) { }

    void operator()(const bool& bo_is_not_prime) const
    {
      const bool bo_is_prime = (!bo_is_not_prime);

      if(bo_is_prime)
      {
        *back_it = count;
      }

      ++count;
    }

  private:
    mutable std::uint32_t                                        count;
    mutable std::back_insert_iterator<std::deque<std::uint32_t>> back_it;
  };

  void Generator(const std::uint32_t n, std::deque<std::uint32_t>& primes_data)
  {
    // Establish the range of the prime number calculation. Use an approximation
    // related to the prime number theorem to obtain the value of the maximum prime
    // number or a minimum of at least 100. Also be sure to limit this range to
    // within the upper limit of std::uint32_t.

    static const std::uint32_t min_hundred = static_cast<std::uint32_t>(100U);
    static const double        xmax        = static_cast<double>((std::numeric_limits<std::uint32_t>::max)());

    const std::uint32_t N     = (std::max)(min_hundred, n);
    const double xn           = static_cast<double>(N);
    const double logn         = std::log(xn);
    const double loglogn      = std::log(logn);
    const double top          = xn * (((logn + loglogn) - 1.0) + ((static_cast<double>(1.8) * loglogn) / logn));
    const double        xlim  = (std::min)(top, xmax);
    const std::uint32_t nlim  = static_cast<std::uint32_t>(static_cast<std::uint64_t>(xlim));
    const std::uint32_t limit = (std::max)(n, nlim);

    // Use a sieve algorithm to generate a boolean table representation of the primes.

    std::vector<bool> sieve(static_cast<std::size_t>(limit), false);

    std::uint32_t i = static_cast<std::uint32_t>(Primes::Inserter::start_index);
    std::uint32_t i2;

    while((i2 = static_cast<std::uint32_t>(i * i)) < limit)
    {
      if(sieve[i] == false)
      {
        for(std::uint32_t j = i2; j < limit; j = static_cast<std::uint32_t>(j + i))
        {
          sieve[j] = true;
        }
      }

      ++i;
    }

    // Extract the prime numbers into the data table by inserting them from the sieve.
    primes_data.clear();

    std::for_each(sieve.cbegin() + Primes::Inserter::start_index,
                  sieve.cend(),
                  Primes::Inserter(primes_data));

    primes_data.resize(static_cast<std::size_t>(n), UINT32_C(0));
  }

  std::deque<std::uint32_t>& Data()
  {
    // Create a static data table of primes and return a reference to it.
    static std::deque<std::uint32_t> primes;

    if(primes.empty())
    {
      // Select a maximum count of prime numbers to be stored
      // in the data table. This number is selected such that
      // the value of the highest prime will slightly exceed
      // 0x10000 (decimal 65,536). This number is significant
      // because it is the maximum value which needs to be tested
      // while computing the prime factors of unsigned 32-bit integers,
      // as done in the subroutine Factors(...).

      Primes::Generator(static_cast<std::uint32_t>(6550U), primes);
    }

    return primes;
  }
}

void ef::prime(const std::uint32_t n, std::deque<std::uint32_t>& primes)
{
  // For small values of n less than the size of the prime data table,
  // the primes can be copied from the data table. For large values of n,
  // the primes must be generated.

  if(n < static_cast<std::uint32_t>(Primes::Data().size()))
  {
    primes.assign(Primes::Data().cbegin(),
                  Primes::Data().cbegin() + static_cast<std::ptrdiff_t>(n));
  }
  else
  {
    Primes::Generator(n, primes);
  }
}
