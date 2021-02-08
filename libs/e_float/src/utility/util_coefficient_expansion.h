
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef UTIL_COEFFICIENT_EXPANSION_2009_11_23_H_
  #define UTIL_COEFFICIENT_EXPANSION_2009_11_23_H_

  namespace Util
  {
    template<typename T1,
             typename T2 = T1>
    struct coefficient_expansion
    {
    public:
      coefficient_expansion(const T1& expand,
                            const T2& init = one_t2()) : x_expand      (expand),
                                                         x_expand_pow_k(init) { }

      T1 operator()(const T1& sum, const T2& ck)
      {
        const T1 ck_x_pow_k(ck * x_expand_pow_k);

        x_expand_pow_k *= x_expand;

        return sum + ck_x_pow_k;
      }

    private:
      const T1 x_expand;
            T1 x_expand_pow_k;

      coefficient_expansion& operator=(const coefficient_expansion&) = delete;

      static const T2& one_t2()
      {
        static const T2 val_t2(1);
        return val_t2;
      }
    };
  }

#endif // UTIL_COEFFICIENT_EXPANSION_2009_11_23_H_
