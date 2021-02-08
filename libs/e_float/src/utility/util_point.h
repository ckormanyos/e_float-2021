
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef UTIL_POINT_2009_10_27_H_
  #define UTIL_POINT_2009_10_27_H_

  namespace Util
  {
    template<typename T1,
             typename T2 = T1>
    struct point
    {
    public:
      T1 x;
      T2 y;

      point(const T1& X = T1(),
            const T2& Y = T2()) : x(X),
                                  y(Y) { }
    };

    template<typename T1,
             typename T2>
    inline bool operator<(const point<T1, T2>& left, const point<T1, T2>& right)
    {
      return (left.x < right.x);
    }
  }

#endif // UTIL_POINT_2009_10_27_H_
