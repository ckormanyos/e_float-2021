
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <e_float/e_float_functions.h>

#include "../../../src/utility/util_lexical_cast.h"
#include "../test_case_real.h"

namespace test
{
  namespace real
  {
    class TestCaseOverflowUnderflowBase : public TestCaseReal
    {
    protected:
      static const std::int32_t kmax = static_cast<std::int32_t>(10000);

      mutable bool my_test_result;

      TestCaseOverflowUnderflowBase() : my_test_result(false) { }

    private:

      virtual const std::vector<e_float>& control_data() const
      {
        static const std::vector<e_float> dummy(1U, ef::one());
        return dummy;
      }

    public:

      virtual ~TestCaseOverflowUnderflowBase() { }

      virtual bool execute(const bool b_write_output) const
      {
        std::cout << name() << " : ";

        std::vector<e_float> e_float_data;

        // Calculate the e_float test data.
        e_float_test(e_float_data);

        // Optionally write the e_float test data to an output file.
        if(b_write_output)
        {
          if(!write_output_file(e_float_data))
          {
            std::cout << "Can not write output: FAIL" << std::endl;
            return false;
          }
        }

        if(my_test_result)
        {
          std::cout << "Numerical compare OK: PASS"  << std::endl;
          return true;
        }
        else
        {
          std::cout << "Numerical compare not OK: FAIL"  << std::endl;
          return false;
        }
      }
    };

    class TestCase_case_00001_overflow_mul_x : public TestCaseOverflowUnderflowBase
    {
    public:
      TestCase_case_00001_overflow_mul_x() { }
      virtual ~TestCase_case_00001_overflow_mul_x() { }
    private:
      virtual const std::string& name() const
      {
        static const std::string str("TestCase_case_00001_overflow_mul_x");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.clear();

        e_float y = ef::googol() * ef::euler_gamma();

        data.push_back(y);

        std::int32_t k;
        for(k = static_cast<std::int32_t>(0); k < kmax; k++)
        {
          y *= y;

          data.push_back(y);

          if(ef::isinf(y))
          {
            break;
          }
        }

        my_test_result = (k > static_cast<std::int32_t>(1)) && (k < kmax);
      }
    };

    class TestCase_case_00002_underflow_mul_x : public TestCaseOverflowUnderflowBase
    {
    public:
      TestCase_case_00002_underflow_mul_x() { }
      virtual ~TestCase_case_00002_underflow_mul_x() { }
    private:
      virtual const std::string& name() const
      {
        static const std::string str("TestCase_case_00002_underflow_mul_x");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.clear();

        e_float y = ef::one() / (ef::googol() * ef::euler_gamma());

        data.push_back(y);

        std::int32_t k;
        for(k = static_cast<std::int32_t>(0); k < kmax; k++)
        {
          y *= y;

          data.push_back(y);

          const bool is_zero_or_lt_min = (ef::iszero(y) || (y < (std::numeric_limits<e_float>::min)()));

          if(is_zero_or_lt_min)
          {
            break;
          }
        }

        my_test_result = (k > static_cast<std::int32_t>(1)) && (k < kmax);
      }
    };

    class TestCase_case_00003_overflow_x_mul_by_n : public TestCaseOverflowUnderflowBase
    {
    public:
      TestCase_case_00003_overflow_x_mul_by_n() { }
      virtual ~TestCase_case_00003_overflow_x_mul_by_n() { }
    private:
      virtual const std::string& name() const
      {
        static const std::string str("TestCase_case_00003_overflow_x_mul_by_n");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.clear();

        e_float y = (std::numeric_limits<e_float>::max)() / static_cast<std::int32_t>(100);

        data.push_back(y);

        std::int32_t k;

        for(k = static_cast<std::int32_t>(0); k < kmax; k++)
        {
          y *= static_cast<std::int32_t>(7);

          data.push_back(y);

          if(ef::isinf(y))
          {
            break;
          }
        }

        my_test_result = (k > static_cast<std::int32_t>(1)) && (k < kmax);
      }
    };

    class TestCase_case_00004_underflow_x_div_by_n : public TestCaseOverflowUnderflowBase
    {
    public:
      TestCase_case_00004_underflow_x_div_by_n() { }
      virtual ~TestCase_case_00004_underflow_x_div_by_n() { }
    private:
      virtual const std::string& name() const
      {
        static const std::string str("TestCase_case_00004_underflow_x_div_by_n");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.clear();

        static const std::string str_tiny_exp = Util::lexical_cast(std::numeric_limits<e_float>::min_exponent10 + static_cast<std::int64_t>(2));
        static const std::string str_tiny = "1e" + str_tiny_exp;

        e_float y(str_tiny);

        data.push_back(y);

        std::int32_t k;
        for(k = static_cast<std::int32_t>(0); k < kmax; k++)
        {
          y /= static_cast<std::int32_t>(7);

          data.push_back(y);

          const bool is_zero_or_lt_min = (ef::iszero(y) || (y < (std::numeric_limits<e_float>::min)()));

          if(is_zero_or_lt_min)
          {
            break;
          }
        }

        my_test_result = (k > static_cast<std::int32_t>(1)) && (k < kmax);
      }
    };

    bool test_case_00001_overflow_mul_x (const bool b_write_output)
    {
      return TestCase_case_00001_overflow_mul_x().execute(b_write_output);
    }
    bool test_case_00002_underflow_mul_x(const bool b_write_output)
    {
      return TestCase_case_00002_underflow_mul_x().execute(b_write_output);
    }
    bool test_case_00003_overflow_x_mul_by_n(const bool b_write_output)
    {
      return TestCase_case_00003_overflow_x_mul_by_n().execute(b_write_output);
    }
    bool test_case_00004_underflow_x_div_by_n(const bool b_write_output)
    {
      return TestCase_case_00004_underflow_x_div_by_n().execute(b_write_output);
    }
  }
}
