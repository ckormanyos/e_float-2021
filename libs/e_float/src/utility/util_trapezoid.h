
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef UTIL_TRAPEZOID_2008_09_06_H_
  #define UTIL_TRAPEZOID_2008_09_06_H_

  #include <limits>

  #include "util_ranged_function_operation.h"
  #include "util_lexical_cast.h"
  #include "util_numeric_cast.h"

  namespace Util
  {
    template<typename T>
    class RecursiveTrapezoidRule : public RangedFunctionOperation<T>
    {
    public:
      virtual ~RecursiveTrapezoidRule() { }

    protected:
      RecursiveTrapezoidRule(const T& lo, const T& hi, const T& tol) : RangedFunctionOperation<T>(lo, hi, tol) { }

      static const T& my_tol()
      {
        static const std::string str_tol("1E-" + Util::lexical_cast(std::numeric_limits<T>::digits10 / 2));
        static const T val(Util::numeric_cast<T>(str_tol));
        return val;
      }

    private:
      virtual T my_operation() const
      {
        std::int32_t n = static_cast<std::int32_t>(1);

        T a = RangedFunctionOperation<T>::xlo;
        T b = RangedFunctionOperation<T>::xhi;
        T h = (b - a) / T(n);
        
        static const T one  = T(1);
        static const T half = T(0.5);

        T I = (Function<T>::function(a) + Function<T>::function(b)) * (h * half);

        for(std::int32_t k = static_cast<std::int32_t>(0); k < static_cast<std::int32_t>(31); k++)
        {
          h *= half;

          const T I0 = I;

          T sum(0);

          for(std::int32_t j = static_cast<std::int32_t>(1); j <= n; j++)
          {
            sum += Function<T>::function(a + (T((j * 2) - 1) * h));
          }

          I = (I0 * half) + (h * sum);

          const T ratio = I0 / I;
          const T delta = ((ratio > one) ? (ratio - one) : (one - ratio));

          if((k > static_cast<std::int32_t>(3)) && (delta < RangedFunctionOperation<T>::eps))
          {
            FunctionOperation<T>::op_ok = true;
            break;
          }

          n = n * 2;
        }

        return I;
      }
    };
  }

#endif // UTIL_TRAPEZOID_2008_09_06_H_
