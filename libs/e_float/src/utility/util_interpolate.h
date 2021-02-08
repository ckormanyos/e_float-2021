
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef UTIL_INTERPOLATE_2009_10_27_H_
  #define UTIL_INTERPOLATE_2009_10_27_H_

  #include <algorithm>
  #include <vector>

  #include "util_point.h"

  namespace Util
  {
    template<typename T1,
             typename T2 = T1>
    struct linear_interpolate
    {
      static T2 interpolate(const T1& x, const std::vector<Util::point<T1, T2>>& points)
      {
        if(points.empty())
        {
          return T2(0);
        }
        else if(x <= points.front().x || points.size() == static_cast<std::size_t>(1U))
        {
          return points.front().y;
        }
        else if(x >= points.back().x)
        {
          return points.back().y;
        }
        else
        {
          const Util::point<T1, T2> x_find(x);

          const typename std::vector<Util::point<T1, T2>>::const_iterator it =
            std::lower_bound(points.cbegin(),
                             points.cend(),
                             x_find);

          const T1 xn            = (it - 1U)->x;
          const T1 xnp1_minus_xn = it->x - xn;
          const T1 delta_x       = x - xn;
          const T2 yn            = (it - 1U)->y;
          const T2 ynp1_minus_yn = it->y - yn;

          return T2(yn + T2((delta_x * ynp1_minus_yn) / xnp1_minus_xn));
        }
      }
    };
  }

#endif // UTIL_INTERPOLATE_2009_10_27_H_
