
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef GENERIC_FUNCTIONS_CONSTANTS_2011_06_18_H_
  #define GENERIC_FUNCTIONS_CONSTANTS_2011_06_18_H_

  #include <e_float/e_float_functions.h>

  namespace generic_functions
  {
    template<typename T> const T& pi         ();
    template<typename T> const T& ln2        ();
    template<typename T> const T& euler_gamma();

    template<> const float&       pi<float>      () { static const float val(3.14159265359f); return val; }
    template<> const double&      pi<double>     () { static const double val(3.1415926535897932384626433832795028841971693993751); return val; }
    template<> const long double& pi<long double>() { static const long double val(3.1415926535897932384626433832795028841971693993751); return val; }
    template<> const e_float&     pi<e_float>    () { return ef::pi(); }

    template<> const float&       ln2<float>      () { static const float val(0.693147180560f); return val; }
    template<> const double&      ln2<double>     () { static const double val(0.69314718055994530941723212145817656807550013436026); return val; }
    template<> const long double& ln2<long double>() { static const long double val(0.69314718055994530941723212145817656807550013436026); return val; }
    template<> const e_float&     ln2<e_float>    () { return ef::ln2(); }

    template<> const float&       euler_gamma<float>      () { static const float val(0.577215664902f); return val; }
    template<> const double&      euler_gamma<double>     () { static const double val(0.57721566490153286060651209008240243104215933593992); return val; }
    template<> const long double& euler_gamma<long double>() { static const long double val(0.57721566490153286060651209008240243104215933593992); return val; }
    template<> const e_float&     euler_gamma<e_float>    () { return ef::euler_gamma(); }

    template<typename T> const T& pi()
    {
      static bool is_init = false;

      static T val;

      if(!is_init)
      {
        is_init = true;

        // Compute pi using a quadratically convergent AGM method.
        // Caution: This is slow, in particular since the generic
        // square root implementation is slow.
        T a (1U);
        T bB(T(1U) / static_cast<std::int32_t>(2));
        T s (bB);
        T t (T(3U) / static_cast<std::int32_t>(8));

        for(std::int32_t k = static_cast<std::int32_t>(1); k < static_cast<std::int32_t>(64); k++)
        {
          bB   = generic_functions::sqrt<T>(bB);
          a   += bB;
          a   /= static_cast<std::int32_t>(2);
          val  = a;
          val *= a;
          bB   = val;
          bB  -= t;
          bB  *= static_cast<std::int32_t>(2);

          T iterate_term(bB);
          iterate_term -= val;
          iterate_term *= static_cast<std::int32_t>(1U << k);

          s  += iterate_term;

          std::int64_t  ne = static_cast<std::int64_t>(0);
          const double  dd = generic_functions::frexp10<T>(iterate_term, &ne);

          static_cast<void>(dd);

          // Test the significant digits of the last iteration change.
          // If the iteration change is small enough, then the calculation
          // of pi is finished.
          if(static_cast<int>(ne) < -std::numeric_limits<T>::digits10 / 2)
          {
            break;
          }

          t   = val;
          t  += bB;
          t  /= static_cast<std::int32_t>(4);
        }

        val += bB;
        val /= s;
      }

      // This is pi.
      return val;
    }

    template<typename T> const T& ln2()
    {
      static bool is_init = false;

      static T val;

      if(!is_init)
      {
        is_init = true;

        // ln2 = pi / [2m * AGM(1, 4 / 2^m)], where m is chosen such that m > n / 2
        // and n is the number of bits of precision required in the result.
        // Chose m > N / (2 * log10(2)), in other words m > N * 1.661,
        // where N is the number of decimal digits of precision.

        // Choose m > N * 1.661
        const std::int32_t m = static_cast<std::int32_t>(1.7 * static_cast<double>(std::numeric_limits<T>::digits10));

        // Set a0 = 1.
        // Set b0 = 4 / (2^m) = 1 / 2^(m - 2)
        T ak(1U);
        T bk = static_cast<std::int32_t>(4) / generic_functions::pown<T>(T(2), static_cast<std::int64_t>(m));

        for(std::int32_t k = static_cast<std::int32_t>(0); k < static_cast<std::int32_t>(64); k++)
        {
          const T a = ak;
          ak += bk;
          ak /= static_cast<std::int32_t>(2);
          bk *= a;
          bk  = generic_functions::sqrt<T>(bk);

          const T delta = ak - bk;

          // Check for the number of significant digits.
          if(   (k > static_cast<std::int32_t>(4))
             && (generic_functions::fabs<T>(delta) < (std::numeric_limits<T>::min)())
            )
          {
            break;
          }
        }

        // The iteration is finished.
        // Compute ln2 = pi / [2m * AGM(1, 4 / 2^m)].
        // Note that a = b = AGM(...).

        // Get pi, invert a and divide by 2m.
        val = generic_functions::pi<T>() / (ak * static_cast<std::int32_t>(static_cast<std::int32_t>(2) * m));
      }

      // This is ln2.
      return val;
    }

    template<typename T> const T& euler_gamma()
    {
      // TBD: Need a generic algorithm for Euler's gamma.
      // TBD: This is difficult without a precomputed value or binary splitting.
      // TBD: Consider Gauss' harmonic series.
      static const T val(0U);
      return val;
    }
  }

#endif // GENERIC_FUNCTIONS_CONSTANTS_2011_06_18_H_
