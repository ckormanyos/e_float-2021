//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef E_FLOAT_DETAIL_POWN_TEMPLATE_2017_08_23_HPP_
  #define E_FLOAT_DETAIL_POWN_TEMPLATE_2017_08_23_HPP_

  #include <cstdint>

  namespace ef { namespace detail {

  // *****************************************************************************
  // Function    : template<typename T> T pown_template(const T& d, const std::int64_t p)
  // 
  // Description : Template function for computing an object d of typename T
  //               raised to the power of std::int64_t p, for p positive or negative.
  //               Binary splitting of the power is used. The resulting
  //               computational complexity scales with O[log2(|p|)].
  // 
  // *****************************************************************************
  template<typename T>
  T pown_template(const T& t, const std::int64_t p)
  {
    // Compute the pure power of typename T t^p. Binary splitting of the power is
    // used. The resulting computational complexity is proportional to O[log2(|p|)].

    if     (p <  static_cast<std::int64_t>(0)) { return T(1) / pown_template(t, -p); }
    else if(p == static_cast<std::int64_t>(0)) { return T(1); }
    else if(p == static_cast<std::int64_t>(1)) { return t; }
    else if(p == static_cast<std::int64_t>(2)) { return (t * t); }
    else if(p == static_cast<std::int64_t>(3)) { return (t * t) * t; }
    else if(p == static_cast<std::int64_t>(4)) { const T t2(t * t); return (t2 * t2); }
    else
    {
      bool has_binary_power = (static_cast<std::int64_t>(p % 2) != static_cast<std::int64_t>(0));

      // The variable tn stores the binary powers of t.
      T result(has_binary_power ? t : T(1U));
      T tn    (t);

      std::int64_t p2 = p;

      while((p2 /= 2) != static_cast<std::int64_t>(0))
      {
        // Square tn for each binary power.
        // TBD: Is it faster (or better) to use the ladder method?
        tn *= tn;

        has_binary_power = (static_cast<std::int64_t>(p2 % 2) != static_cast<std::int64_t>(0));

        if(has_binary_power)
        {
          // Multiply the result with each binary power contained in the exponent.
          result *= tn;
        }
      }

      return result;
    }
  }

  } } // namespace ef::detail

#endif // E_FLOAT_DETAIL_POWN_TEMPLATE_2017_08_23_HPP_
