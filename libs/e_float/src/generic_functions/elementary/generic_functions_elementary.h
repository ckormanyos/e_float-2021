
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef GENERIC_FUNCTIONS_ELEMENTARY_2011_06_18_H_
  #define GENERIC_FUNCTIONS_ELEMENTARY_2011_06_18_H_

  #include <cmath>
  #include <regex>

  #include <boost/e_float/e_float_functions.hpp>

  namespace generic_functions
  {
    template<typename T> const T& pi (); // Forward declaration.
    template<typename T> const T& ln2(); // Forward declaration.

    template<typename T> double frexp10  (const T& x, std::int64_t* ptrexp10);
    template<typename T> T      sqrt     (const T& x);
    template<typename T> T      rootn    (const T& x, const std::int32_t p);
    template<typename T> T      log      (const T& x);
    template<typename T> bool   isneg    (const T& x);
    template<typename T> T      fabs     (const T& x);
    template<typename T> bool   iszero   (const T& x);
    template<typename T> bool   isone    (const T& x);
    template<typename T> bool   isfinite (const T& x);
    template<typename T> bool   small_arg(const T& x);

    template<typename T> bool isneg    (const T& x) { return (x < static_cast<std::int32_t>(0)); }
    template<typename T> T    fabs     (const T& x) { return (generic_functions::isneg<T>(x) ? -x : x); }
    template<typename T> bool iszero   (const T& x) { return (generic_functions::fabs<T>(x) < (std::numeric_limits<T>::min)() * 2); }
    template<typename T> bool isone    (const T& x) { return  generic_functions::iszero<T>(1 - x); }
    template<typename T> bool isfinite (const T& x) { static_cast<void>(x); return true; } // TBD: Devise a sensible test for isfinite.

    template<> float       sqrt<float>      (const float& x)       { return ::sqrtf(x); }
    template<> double      sqrt<double>     (const double& x)      { return ::sqrt(x); }
    template<> long double sqrt<long double>(const long double& x) { return ::sqrt(x); }
    template<> e_float     sqrt<e_float>    (const e_float& x)     { return ef::sqrt(x); }

    template<> float       rootn<float>      (const float& x,       const std::int32_t p) { return ::powf(x, static_cast<float>(p)); }
    template<> double      rootn<double>     (const double& x,      const std::int32_t p) { return ::pow(x, static_cast<double>(p)); }
    template<> long double rootn<long double>(const long double& x, const std::int32_t p) { return ::pow(x, static_cast<long double>(p)); }
    template<> e_float     rootn<e_float>    (const e_float& x,     const std::int32_t p) { return ef::rootn(x, p); }

    template<> float       log<float>      (const float& x)       { return ::logf(x); }
    template<> double      log<double>     (const double& x)      { return ::log(x); }
    template<> long double log<long double>(const long double& x) { return ::log(x); }
    template<> e_float     log<e_float>    (const e_float& x)     { return ef::log(x); }

    template<typename T> double frexp10(const T& x, std::int64_t* ptrexp10)
    {
      // Use string manipulations to obtain the base-10 mantissa and exponent.
      // Caution: This is slow. It is generic, but has poor performance.
      // Comment: Any dedicated effort to standardize MP would specify a fast kind of frexp.
      std::stringstream ss;
      ss << std::scientific
         << std::showpos
         << std::uppercase
         << std::setprecision(std::numeric_limits<double>::digits10 + 1)
         << x;

      std::string str;
      ss >> str;

      // Here is a regular expression for a double string created in an
      // std::ostream with std::scientific, std::showpos and std::uppercase.
      static const std::regex rx_double_scientific_showpos_upper("([+|-][1-9]{1}[.]{1}[0-9]+)[E]([+|-]{1}[0-9]+)");

      std::match_results<std::string::const_iterator> mr;

      const bool b_match = std::regex_match(str, mr, rx_double_scientific_showpos_upper);

      if(!b_match)
      {
        return false;
        // TBD: This is an impossible error condition.
        // TBD: Should we throw something?
      }

      ss.str("");
      ss.clear();
      ss << std::setprecision(std::numeric_limits<double>::digits10 + 1)
          << mr[1U].str();
      double mantissa;
      ss >> mantissa;

      ss.str("");
      ss.clear();
      ss << mr[2U].str();
      ss >> *ptrexp10;

      return mantissa;
    }

    template<typename T> T pown(const T& t, const std::int64_t p)
    {
      // Compute the pure power of typename T t^p. Binary splitting of the power is
      // used. The resulting computational complexity has the order of log2[abs(p)].

      if(p < static_cast<std::int64_t>(0))
      {
        return T(1U) / pown(t, -p);
      }

      switch(p)
      {
        case static_cast<std::int64_t>(0):
          return T(1);

        case static_cast<std::int64_t>(1):
          return t;

        case static_cast<std::int64_t>(2):
          return t * t;

        case static_cast<std::int64_t>(3):
          return (t * t) * t;

        case static_cast<std::int64_t>(4):
        {
          const T tsq = t * t;
          return tsq * tsq;
        }

        default:
        {
          T value(t);
          std::int64_t n;

          for(n = static_cast<std::int64_t>(1); n <= static_cast<std::int64_t>(p / static_cast<std::int64_t>(2)); n *= static_cast<std::int64_t>(2))
          {
            value *= value;
          }

          const std::int64_t p_minus_n = static_cast<std::int64_t>(p - n);

          // Call the function recursively for computing the remaining power of n.
          return ((p_minus_n == static_cast<std::int64_t>(0)) ? value
                                                       : value * generic_functions::pown<T>(t, p_minus_n));
        }
      }
    }

    template<typename T> T sqrt(const T& x)
    {
      if(generic_functions::isneg<T>(x) || (!generic_functions::isfinite<T>(x)))
      {
        return std::numeric_limits<T>::quiet_NaN();
      }

      if(generic_functions::iszero<T>(x) || generic_functions::isone<T>(x))
      {
        return x;
      }

      std::int64_t  ne = static_cast<std::int64_t>(0);
      double        dd = generic_functions::frexp10<T>(x, &ne);

      if(static_cast<std::int64_t>(ne % static_cast<std::int32_t>(2)) != static_cast<std::int64_t>(0U))
      {
        ne += 1;
        dd /= 10.0;
      }

      // Create the initial guess and first iteration using double and string manipulations.
      // Caution: This is slow. It is generic, but has poor performance.
      // Comment: Any dedicated effort to standardize MP would specify a fast kind of ldexp.
      const double sqd = ::sqrt(dd);

      std::stringstream ss;

      // Estimate the square root.
      ss << std::setprecision(std::numeric_limits<double>::digits10 + 1)
         << sqd
         << 'E'
         << (ne / 2);

      T result(ss.str());

      // Estimate 1.0 / (2.0 * x0).
      ss.str("");
      ss.clear();
      ss << std::setprecision(std::numeric_limits<double>::digits10 + 1)
         << (0.5 / sqd)
         << 'E'
         << (-ne / 2);

      T vi(ss.str());

      // Compute the square root of x using coupled Newton iteration.
      // Caution: This is slow because internal precision adjustments are not used.
      for(std::int32_t digits = std::numeric_limits<double>::digits10 - 1; digits <= std::numeric_limits<T>::digits10; digits *= 2)
      {
        // Next iteration of vi
        vi += vi * (-((result * vi) * static_cast<std::int32_t>(2)) + static_cast<std::int32_t>(1));

        // Next iteration of *this
        result += vi * (-(result * result) + x);
      }

      return result;
    }

    template<typename T> T rootn(const T& x, const std::int32_t p)
    {
      if(!generic_functions::isfinite<T>(x))
      {
        return std::numeric_limits<e_float>::quiet_NaN();
      }

      if(p < static_cast<std::int32_t>(0))
      {
        return generic_functions::rootn<T>(static_cast<std::int32_t>(1) / x, static_cast<std::int32_t>(-p));
      }

      if((p == static_cast<std::int32_t>(0)) || generic_functions::isneg(x))
      {
        return std::numeric_limits<e_float>::quiet_NaN();
      }
      else if(p == static_cast<std::int32_t>(1))
      {
        return x;
      }
      else if(p == static_cast<std::int32_t>(2))
      {
        return generic_functions::sqrt<T>(x);
      }

      // Compute the value of [1 / (rootn of x)] with n = p.

      // Generate the initial estimate using 1 / rootn.
      // Extract the mantissa and exponent for a "manual"
      // computation of the estimate.
      std::int64_t  ne = static_cast<std::int64_t>(0);
      double        dd = generic_functions::frexp10<T>(x, &ne);

      // Adjust exponent and mantissa such that ne is an even power of p.
      while(ne % static_cast<std::int64_t>(p))
      {
        ++ne;
        dd /= 10.0;
      }
  
      // Estimate the one over the root using simple manipulations.
      const double one_over_rtn_d = ::pow(dd, -1.0 / static_cast<double>(p));

      // Set the result equal to the initial guess.

      // Estimate the square root.
      std::stringstream ss;
      ss << std::setprecision(std::numeric_limits<double>::digits10 + 1)
         << one_over_rtn_d
         << 'E'
         << static_cast<std::int64_t>(-ne / p);

      T rtn(ss.str());

      // Compute the square root of x using coupled Newton iteration.
      // Caution: This is slow because internal precision adjustments are not used.
      for(std::int32_t digits = std::numeric_limits<double>::digits10 - 1; digits <= std::numeric_limits<T>::digits10; digits *= 2)
      {
        // Next iteration
        T term = (((-generic_functions::pown<T>(rtn, p) * x) + static_cast<std::int32_t>(1)) / p) + static_cast<std::int32_t>(1);
        rtn *= term;
      }

      return static_cast<std::int32_t>(1) / rtn;
    }

    template<typename T> bool small_arg(const T& x)
    {
      // Values less than the sixth root of epsilon are considered small.
      static const T val_small = generic_functions::rootn<T>(std::numeric_limits<T>::epsilon(), static_cast<std::int32_t>(6));
      return (generic_functions::fabs<T>(x) < val_small);
    }

    template<typename T> T log(const T& x)
    {
      if(generic_functions::iszero<T>(x) || generic_functions::isneg<T>(x))
      {
        return std::numeric_limits<T>::quiet_NaN();
      }
      else if(generic_functions::isone<T>(x))
      {
        return T(0U);
      }

      // For values less than 1 invert the argument and negate the result below.
      const bool b_neg = (x < T(1U));

      const T xx = ((!b_neg) ? x : static_cast<std::int32_t>(1) / x);

      // ln(x) = {pi / [2 * AGM(1, 4 / s)]} - m * ln2 where s = x * 2^m
      // and m is chosen such that s > 2^(n / 2) where n is the number
      // of bits of precision required in the result.
      // Chose m > N * 1.661 - ln(x) / ln(2), in other words m > N * 1.661 - ln(x) / ln(2),
      // where N is the required base-10 decimal digits of precision.

      // Here we simply select m > N * 1.661 (convenience).
      const std::int32_t m = static_cast<std::int32_t>(1.7 * static_cast<double>(std::numeric_limits<T>::digits10));

      T ak(1U);
      T bk = static_cast<std::int32_t>(4) / (xx * generic_functions::pown<T>(T(2), static_cast<std::int64_t>(m)));

      for(std::int32_t k = static_cast<std::int32_t>(0); k < static_cast<std::int32_t>(64); k++)
      {
        const T a   = ak;
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
      // Compute log(x) = {pi / [2 * AGM(1, 4 / 2^m)]} - (m * ln2)
      // Note that a = b = AGM(...)

      // Get pi, divide by 2 * a and Subtract m * ln2.
      const T val =   (generic_functions::pi<T>() / (ak * static_cast<std::int32_t>(2)))
                    - (generic_functions::ln2<T>() * m);

      return ((!b_neg) ? val : -val);
    }
  }

#endif // GENERIC_FUNCTIONS_ELEMENTARY_2011_06_18_H_
