
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef TEST_CASE_REAL_2009_10_24_H_
  #define TEST_CASE_REAL_2009_10_24_H_

  #include <../test/test_case_base.h>

  namespace test
  {
    namespace real
    {
      class TestCaseReal : public TestCaseBase<e_float>
      {
      private:

        TestCaseReal(const TestCaseReal&);
        const TestCaseReal& operator=(const TestCaseReal&);

      protected:

        TestCaseReal() { }

      public:

        virtual ~TestCaseReal() { }
      };
    }
  }

#endif // TEST_CASE_REAL_2009_10_24_H_
