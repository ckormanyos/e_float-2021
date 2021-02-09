
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

// Automatically generated file
#include <array>

#include <e_float/e_float_complex.h>
#include <e_float/e_float_functions.h>

#include "../test_case_real.h"

namespace test
{
  namespace real
  {
    class TestCase_case_00011_various_elem_math : public TestCaseReal
    {
    public:
      TestCase_case_00011_various_elem_math() { }
      virtual ~TestCase_case_00011_various_elem_math() { }
    private:
      virtual const std::string& name() const
      {
        static const std::string str("TestCase_case_00011_various_elem_math");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.clear();
        data.push_back(ef::floor(ef::pi()));
        data.push_back(ef::ceil (ef::pi()));
        data.push_back(ef::floor(-100 - ef::euler_gamma()));
        data.push_back(ef::ceil (-100 - ef::euler_gamma()));
        data.push_back(e_float(ef::to_int32(e_float("1e9"))));
        data.push_back(e_float(ef::to_int64(e_float("1e18"))));
        data.push_back(e_float(ef::to_int32(e_float("1e29"))));
        data.push_back(e_float(ef::to_int64(e_float("1e29"))));
        data.push_back(e_float(ef::to_int32(ef::complex<e_float>(ef::pi(), ef::euler_gamma()).real())));
        data.push_back(e_float(ef::to_int64(ef::complex<e_float>(ef::pi(), ef::euler_gamma()).real())));
      }
      virtual const std::vector<e_float>& control_data() const
      {
        static const std::array<e_float, 10U> a =
        {{
           e_float("3"),
           e_float("4"),
           e_float("-101"),
           e_float("-100"),
           e_float("1000000000"),
           e_float("1000000000000000000"),
           e_float("2147483647"),
           e_float("9223372036854775807"),
           e_float("3"),
           e_float("3"),
        }};
        static const std::vector<e_float> v(a.cbegin(), a.cend());
        return v;
      }
    };

    bool test_case_00011_various_elem_math(const bool b_write_output)
    {
      return TestCase_case_00011_various_elem_math().execute(b_write_output);
    }
  }
}
