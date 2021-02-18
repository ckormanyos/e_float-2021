
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef UTIL_FUNCTION_OPERATION_2009_10_27_H_
  #define UTIL_FUNCTION_OPERATION_2009_10_27_H_

  #include <utility/util_function.h>

  namespace Util
  {
    template<typename T>
    class FunctionOperation : public Function<T>
    {
    public:
      virtual ~FunctionOperation() { }

      bool success() const { return op_ok; }
      T operation() const { return my_operation(); }

    protected:
      mutable bool op_ok;

      FunctionOperation() : op_ok(false) { }

      virtual T my_operation() const = 0;
    };
  }

#endif // UTIL_FUNCTION_OPERATION_2009_10_27_H_
