
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef UTIL_FUNCTION_2009_10_27_H_
  #define UTIL_FUNCTION_2009_10_27_H_

  #include <utility/util_noncopyable.h>

  namespace Util
  {
    template<typename T>
    class Function : private noncopyable
    {
    public:
      virtual ~Function() { }

      T function(const T& x) const { return my_function(x); }

    protected:
      Function() { }

    private:
      virtual T my_function(const T&) const = 0;
    };
  }

#endif // UTIL_FUNCTION_2009_10_27_H_
