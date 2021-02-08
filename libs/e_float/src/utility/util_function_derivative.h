
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef UTIL_FUNCTION_DERIVATIVE_2009_11_17_H_
  #define UTIL_FUNCTION_DERIVATIVE_2009_11_17_H_

  #include <sstream>
  #include <string>

  #include "util_function_operation.h"
  #include "util_lexical_cast.h"
  #include "util_numeric_cast.h"

  namespace Util
  {
    template<typename T>
    class FunctionDerivative final : public FunctionOperation<T>
    {
    public:
      virtual ~FunctionDerivative() { }

    protected:
      const T my_x;
      const T my_dx;

      FunctionDerivative(const T& x, const T& dx = my_tol()) : my_x(x), my_dx(dx) { }

      virtual T my_operation() const
      {
        FunctionOperation<T>::op_ok = true;

        // Compute the function derivative using a three point
        // central difference rule of O(dx^6).
        const T dx1 = my_dx;
        const T dx2 = dx1 * static_cast<std::int32_t>(2);
        const T dx3 = dx1 * static_cast<std::int32_t>(3);

        const T m1 = (function(my_x + dx1) - function(my_x - dx1)) / static_cast<std::int32_t>(2);
        const T m2 = (function(my_x + dx2) - function(my_x - dx2)) / static_cast<std::int32_t>(4);
        const T m3 = (function(my_x + dx3) - function(my_x - dx3)) / static_cast<std::int32_t>(6);

        const T fifteen_m1 = static_cast<std::int32_t>(15) * m1;
        const T six_m2     = static_cast<std::int32_t>( 6) * m2;
        const T ten_dx1    = static_cast<std::int32_t>(10) * dx1;

        return ((fifteen_m1 - six_m2) + m3) / ten_dx1;
      }

    private:
      static const T& my_tol()
      {
        // Set the default tolerance to be approximately 10^[-(digits10 * 1.15)/5].
        static const double      tx = (static_cast<double>(std::numeric_limits<T>::digits10) * 1.15) / 5.0;
        static const std::size_t tn = static_cast<std::size_t>(tx + 0.5);

        static const std::string str_tol("1E-" + Util::lexical_cast(tn));
        static const T val_tol(Util::numeric_cast<T>(str_tol));

        return val_tol;
      }
    };
  }

#endif // UTIL_FUNCTION_DERIVATIVE_2009_11_17_H_
