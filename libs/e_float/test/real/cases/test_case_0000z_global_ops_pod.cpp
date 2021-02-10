
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <iomanip>
#include <limits>
#include <sstream>
#include <string>

#include <e_float/e_float.h>
#include <e_float/e_float_functions.h>
#include <../test/real/test_case_real.h>
#include <utility/util_lexical_cast.h>

namespace local
{
  template<typename CheckType,
           typename ControlType>
  bool check_minimax_of_type()
  {
    const e_float the_value_min((std::numeric_limits<CheckType>::min)());
    const e_float the_value_max((std::numeric_limits<CheckType>::max)());

    std::stringstream ss;

    ss << static_cast<ControlType>((std::numeric_limits<CheckType>::min)());

    const std::string str_min(ss.str());

    ss.clear();
    ss.str("");

    ss << static_cast<ControlType>((std::numeric_limits<CheckType>::max)());

    const std::string str_max(ss.str());

    return (   (the_value_min == e_float(str_min))
            && (the_value_max == e_float(str_max)));
  }
}

namespace test
{
  namespace real
  {
    class TestCaseGlobalOpsPodBase : public TestCaseReal
    {
    protected:
      mutable bool my_test_result;

      TestCaseGlobalOpsPodBase() : my_test_result(false) { }

    private:
      virtual const std::vector<e_float>& control_data() const
      {
        static const std::vector<e_float> dummy(1U, ef::one());
        return dummy;
      }

    public:
      virtual ~TestCaseGlobalOpsPodBase() { }

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

    class TestCase_case_00009_global_ops_pod_equate : public TestCaseGlobalOpsPodBase
    {
    public:
      TestCase_case_00009_global_ops_pod_equate() { }
      virtual ~TestCase_case_00009_global_ops_pod_equate() { }

    private:
      virtual const std::string& name() const
      {
        static const std::string str("TestCase_case_00009_global_ops_pod_equate");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.clear();

        my_test_result = true;

        my_test_result &= (std::numeric_limits< char  >::is_signed ? local::check_minimax_of_type< char,     signed long long>()
                                                                   : local::check_minimax_of_type< char,   unsigned long long>());
        my_test_result &= (std::numeric_limits<wchar_t>::is_signed ? local::check_minimax_of_type<wchar_t,   signed long long>()
                                                                   : local::check_minimax_of_type<wchar_t, unsigned long long>());

        my_test_result &= local::check_minimax_of_type<  signed char,      signed long long>();
        my_test_result &= local::check_minimax_of_type<  signed short,     signed long long>();
        my_test_result &= local::check_minimax_of_type<  signed int,       signed long long>();
        my_test_result &= local::check_minimax_of_type<  signed long,      signed long long>();
        my_test_result &= local::check_minimax_of_type<  signed long long, signed long long>();

        my_test_result &= local::check_minimax_of_type<unsigned char,      unsigned long long>();
        my_test_result &= local::check_minimax_of_type<unsigned short,     unsigned long long>();
        my_test_result &= local::check_minimax_of_type<unsigned int,       unsigned long long>();
        my_test_result &= local::check_minimax_of_type<unsigned long,      unsigned long long>();
        my_test_result &= local::check_minimax_of_type<unsigned long long, unsigned long long>();

        e_float x(123U); // Initialize x with something.

        // Reassign x to some floating-point POD values and check some equalities.
        x = 4.0f;  my_test_result &= (x == e_float(4U));
        x = 4.0;   my_test_result &= (x == e_float(4U));
        x = 4.0L;  my_test_result &= (x == e_float(4U));

        my_test_result &= (e_float(0.0f) == ef::zero());
        my_test_result &= (e_float(0.0)  == ef::zero());
        my_test_result &= (e_float(0.0L) == ef::zero());
      }
    };

    class TestCase_case_00010_global_ops_pod_operations : public TestCaseGlobalOpsPodBase
    {
    public:
      TestCase_case_00010_global_ops_pod_operations() { }
      virtual ~TestCase_case_00010_global_ops_pod_operations() { }

    private:
      virtual const std::string& name() const
      {
        static const std::string str("TestCase_case_00010_global_ops_pod_operations");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.clear();

        my_test_result = true;

        my_test_result &= (+ef::four() == +4.0f);
        my_test_result &= (-ef::four() == -4.0f);
        my_test_result &= (+ef::four() == +4.0);
        my_test_result &= (-ef::four() == -4.0);
        my_test_result &= (+ef::four() == +4.0L);
        my_test_result &= (-ef::four() == -4.0L);

        my_test_result &= (e_float(11.1f) == e_float("11.1000003814697265625"));
        my_test_result &= (e_float(11.1)  == e_float("11.0999999999999996447286321199499070644378662109375"));

        my_test_result &= (+ef::pi() > +3.14f);
        my_test_result &= (-ef::pi() < -3.14f);
        my_test_result &= (+ef::pi() > +3.14);
        my_test_result &= (-ef::pi() < -3.14);
        my_test_result &= (+ef::pi() > +3.14L);
        my_test_result &= (-ef::pi() < -3.14L);

        my_test_result &= (static_cast<float>      (0.5f) < ef::euler_gamma());
        my_test_result &= (static_cast<double>     (0.5)  < ef::euler_gamma());
        my_test_result &= (static_cast<long double>(0.5L) < ef::euler_gamma());

        my_test_result &= (e_float(static_cast<char>('1')) == static_cast<char>(0x31));
        my_test_result &= (e_float(static_cast<char>('2')) >  static_cast<char>('1'));
        my_test_result &= (e_float(static_cast<char>('1')) <  static_cast<char>('2'));
        my_test_result &= (e_float(static_cast<char>('2')) <= static_cast<char>('2'));
        my_test_result &= (e_float(static_cast<char>('2')) >= static_cast<char>('2'));
        my_test_result &= (3.14 != ef::pi());

        my_test_result &= (e_float("1e1000") > (std::numeric_limits<unsigned long long>::max)());
        my_test_result &= (ef::zero() == 0);
        my_test_result &= (std::numeric_limits<e_float>::epsilon() > 0);

        my_test_result &= ((ef::one() * 4.0) == 4);
        my_test_result &= ((4.0 * ef::one()) == 4);

        my_test_result &= (std::numeric_limits<e_float>::quiet_NaN() != 0);
        my_test_result &= (std::numeric_limits<e_float>::quiet_NaN() != ef::one());
        my_test_result &= (std::numeric_limits<e_float>::quiet_NaN() != std::numeric_limits<e_float>::quiet_NaN());

        static const e_float huge("1e+12345678");
        static const e_float tiny("1e-12345678");

        my_test_result &= (huge < +std::numeric_limits<e_float>::infinity());
        my_test_result &= (tiny > -std::numeric_limits<e_float>::infinity());
        my_test_result &= (+std::numeric_limits<e_float>::infinity() == (+1 / ef::zero()));
        my_test_result &= (-std::numeric_limits<e_float>::infinity() == (-1 / ef::zero()));
        my_test_result &= (-std::numeric_limits<e_float>::infinity() != +std::numeric_limits<e_float>::infinity());
        my_test_result &= (+std::numeric_limits<e_float>::infinity() >  -std::numeric_limits<e_float>::infinity());
        my_test_result &= (-std::numeric_limits<e_float>::infinity() <  +std::numeric_limits<e_float>::infinity());

        float       f;
        double      d;
        long double l;

        f = static_cast<float> (huge.extract_long_double());
        d = static_cast<double>(huge.extract_long_double());
        l =                     huge.extract_long_double();

        my_test_result &= (f  == std::numeric_limits<float>::infinity());
        my_test_result &= (d  == std::numeric_limits<double>::infinity());
        my_test_result &= (static_cast<double>(l) == std::numeric_limits<double>::infinity()); // Workaround : Cast to double for GCC on MinGW32.

        f = static_cast<float> (tiny.extract_long_double());
        d = static_cast<double>(tiny.extract_long_double());
        l =                     tiny.extract_long_double();

        my_test_result &= (f == 0.0F);
        my_test_result &= (d == 0.0);
        my_test_result &= (l == 0.0L);

        static const e_float min_value("1e" + Util::lexical_cast(std::numeric_limits<e_float>::min_exponent10));

        my_test_result &= ((std::numeric_limits<e_float>::min)() == min_value);
        my_test_result &= ((std::numeric_limits<e_float>::min)() != 0);
        my_test_result &= ((std::numeric_limits<e_float>::min)() != ef::zero());
        my_test_result &= (0 != (std::numeric_limits<e_float>::min)());
        my_test_result &= (ef::zero() != (std::numeric_limits<e_float>::min)());
        my_test_result &= (0 < +(std::numeric_limits<e_float>::min)());
        my_test_result &= (0 > -(std::numeric_limits<e_float>::min)());

        static const e_float a_little_more_than_min_value("1e" + Util::lexical_cast(std::numeric_limits<e_float>::min_exponent10 + static_cast<std::int64_t>(1)));

        my_test_result &= (a_little_more_than_min_value != 0);
        my_test_result &= (a_little_more_than_min_value > (std::numeric_limits<e_float>::min)());
      }
    };

    bool test_case_00009_global_ops_pod_equate(const bool b_write_output)
    {
      return TestCase_case_00009_global_ops_pod_equate().execute(b_write_output);
    }
    bool test_case_00010_global_ops_pod_operations(const bool b_write_output)
    {
      return TestCase_case_00010_global_ops_pod_operations().execute(b_write_output);
    }
  }
}
