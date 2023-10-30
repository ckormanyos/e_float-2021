///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2009 - 2023.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#ifndef UTIL_NUMERIC_CAST_2009_11_24_H
  #define UTIL_NUMERIC_CAST_2009_11_24_H

  #include <sstream>
  #include <string>
  #include <type_traits>

  namespace Util
  {
    template<typename T>
    inline T numeric_cast(const std::string& str)
    {
      constexpr bool numeric_cast_is_signed = std::numeric_limits<T>::is_signed;

      constexpr bool numeric_cast_is_small_type =
        (   (  numeric_cast_is_signed  && (std::numeric_limits<T>::digits <= 31))
         || ((!numeric_cast_is_signed) && (std::numeric_limits<T>::digits <= 32)));

      using value_type = typename std::conditional<numeric_cast_is_small_type,
                                                   typename std::conditional<numeric_cast_is_signed,
                                                                             std::int32_t,
                                                                             std::uint32_t>::type, T>::type;

      // This could be done with a variation of "baselexical_cast",
      // which is available in other projects such as wide-decimal.

      std::stringstream strm;

      strm << str;

      value_type t;
      strm >> t;

      return (T) t;
    }
  }

#endif // UTIL_NUMERIC_CAST_2009_11_24_H
