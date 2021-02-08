
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef UTIL_NONCOPYABLE_2009_03_30_H_
  #define UTIL_NONCOPYABLE_2009_03_30_H_

  // Taken (and slightly modified) from boost.
  namespace Util
  {
    class noncopyable
    {
    protected:
       noncopyable() { }
      ~noncopyable() { }

    private:  // emphasize the following members are private
      noncopyable(const noncopyable&) = delete;
      const noncopyable& operator=(const noncopyable&) = delete;
    };
  }

#endif // UTIL_NONCOPYABLE_2009_03_30_H_
