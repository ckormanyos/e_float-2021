
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef UTIL_FIND_ROOT_BASE_2009_10_31_H_
  #define UTIL_FIND_ROOT_BASE_2009_10_31_H_

  #include <utility/util_ranged_function_operation.h>

  namespace Util
  {
    template<typename T>
    class FindRootBase : public RangedFunctionOperation<T>
    {
    public:
      virtual ~FindRootBase() { }

    protected:
      FindRootBase(const T& lo,
                   const T& hi,
                   const T& tol) : RangedFunctionOperation<T>(lo, hi, tol) { }
    };
  }

#endif // UTIL_FIND_ROOT_BASE_2009_10_31_H_
