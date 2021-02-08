
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef UTIL_ALTERNATING_SUM_2010_01_11_H_
  #define UTIL_ALTERNATING_SUM_2010_01_11_H_

  namespace Util
  {
    template<typename T1,
             typename T2 = T1>
    struct alternating_sum
    {
    public:
      alternating_sum(const bool b_neg = false, const T2& init = T2(0)) : b_neg_term(b_neg),
                                                                          initial   (init) { }
                                                                          
      T1 operator()(const T1& sum, const T2& ck)
      {
        const T1 the_sum = (!b_neg_term ? (sum + ck) : (sum - ck));
        b_neg_term = !b_neg_term;
        return the_sum + initial;
      }

    private:
      bool b_neg_term;
      const T2 initial;

      const alternating_sum& operator=(const alternating_sum&);
    };
  }

#endif // UTIL_ALTERNATING_SUM_2010_01_11_H_
