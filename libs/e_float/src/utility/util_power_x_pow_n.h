
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef UTIL_POWER_X_POW_N_2009_11_23_H_
  #define UTIL_POWER_X_POW_N_2009_11_23_H_

  namespace Util
  {
    template<typename T>
    inline T x_pow_n_template(const T& t, const std::int64_t p)
    {
      // Compute the pure power of typename T t^p. Binary splitting of the power is
      // used. The resulting computational complexity has the order of log2[abs(p)].

      if(p < static_cast<std::int64_t>(0))
      {
        return T(1) / x_pow_n_template(t, -p);
      }

      switch(p)
      {
        case static_cast<std::int64_t>(0):
          return T(1);

        case static_cast<std::int64_t>(1):
          return t;

        case static_cast<std::int64_t>(2):
          return t * t;

        case static_cast<std::int64_t>(3):
          return (t * t) * t;

        case static_cast<std::int64_t>(4):
        {
          const T tsq = t * t;
          return tsq * tsq;
        }

        default:
        {
          T value(t);
          std::int64_t n;

          for(n = static_cast<std::int64_t>(1); n <= static_cast<std::int64_t>(p / static_cast<std::int64_t>(2)); n *= static_cast<std::int64_t>(2))
          {
            value *= value;
          }

          const std::int64_t p_minus_n = static_cast<std::int64_t>(p - n);

          // Call the function recursively for computing the remaining power of n.
          return ((p_minus_n == static_cast<std::int64_t>(0)) ? value
                                                       : value * Util::x_pow_n_template(t, p_minus_n));
        }
      }
    }
  }

#endif // UTIL_POWER_X_POW_N_2009_11_23_H_
