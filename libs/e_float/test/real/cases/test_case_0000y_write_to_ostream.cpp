
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <sstream>
#include <string>
#include <iomanip>

#include <e_float/e_float_functions.h>

#include "../../../src/utility/util_lexical_cast.h"

#include "../test_case_real.h"

namespace
{
  std::string make_pi_string(const std::size_t number_of_digits)
  {
    // 1100 digits of pi
    static const std::string str =
      std::string("3.")
    + std::string("1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679")
    + std::string("8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196")
    + std::string("4428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273")
    + std::string("7245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094")
    + std::string("3305727036575959195309218611738193261179310511854807446237996274956735188575272489122793818301194912")
    + std::string("9833673362440656643086021394946395224737190702179860943702770539217176293176752384674818467669405132")
    + std::string("0005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235")
    + std::string("4201995611212902196086403441815981362977477130996051870721134999999837297804995105973173281609631859")
    + std::string("5024459455346908302642522308253344685035261931188171010003137838752886587533208381420617177669147303")
    + std::string("5982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989")
    + std::string("3809525720106548586327886593615338182796823030195203530185296899577362259941389124972177528347913152")
    ;

    std::string str_pi(str.cbegin(), str.cbegin() + static_cast<std::ptrdiff_t>(number_of_digits + 3));

    const bool b_round_up = (*(str_pi.cend() - 1U) >= static_cast<char>('5'));
    str_pi.erase(str_pi.cend() - 1U, str_pi.cend());

    if(b_round_up)
    {
      std::string::iterator it = str_pi.end() - 1U;

      bool b_break = false;

      while(!b_break)
      {
        if(*it == static_cast<char>('9'))
        {
          *it = static_cast<char>('0');
        }
        else
        {
          *it = static_cast<char>(*it + static_cast<char>(1));
          b_break = true;
        }

        --it;
      }
    }

    return str_pi;
  }

  const std::size_t& default_prec()
  {
    static std::stringstream the_ss;
    static const std::size_t the_default_prec = static_cast<std::size_t>(the_ss.precision());
    return the_default_prec;
  }
}

namespace test
{
  namespace real
  {
    class TestCaseWriteToOstreamBase : public TestCaseReal
    {
    protected:

      mutable bool my_test_result;

      TestCaseWriteToOstreamBase() : my_test_result(false) { }

    private:

      virtual const std::vector<e_float>& control_data() const
      {
        static const std::vector<e_float> dummy(1U, ef::one());
        return dummy;
      }

    public:

      virtual ~TestCaseWriteToOstreamBase() { }

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

    class TestCase_case_00006_write_os_floatfield_fixed : public TestCaseWriteToOstreamBase
    {
    public:
      TestCase_case_00006_write_os_floatfield_fixed() { }
      virtual ~TestCase_case_00006_write_os_floatfield_fixed() { }
    private:
      virtual const std::string& name() const
      {
        static const std::string str("TestCase_case_00006_write_os_floatfield_fixed");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.clear();

        my_test_result = true;

        std::string str;
        std::stringstream ss;

        ss << std::fixed << std::showpos << std::showpoint << std::setprecision(0) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        std::string str_pi = std::string("+") + ::make_pi_string(::default_prec());
        my_test_result &= (str == str_pi);
        ss.clear();
        ss.str("");

        ss << std::fixed << std::showpos << std::showpoint << std::setprecision(1) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("+3.1"));
        ss.clear();
        ss.str("");

        ss << std::fixed << std::showpos << std::showpoint << std::setprecision(2) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("+3.14"));
        ss.clear();
        ss.str("");

        ss << std::fixed << std::showpos << std::showpoint << std::setprecision(10) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("+3.1415926536"));
        ss.clear();
        ss.str("");

        ss << std::fixed << std::showpos << std::showpoint << std::setprecision(20) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("+3.14159265358979323846"));
        ss.clear();
        ss.str("");

        ss << std::fixed << std::showpos << std::showpoint << std::setprecision(std::numeric_limits<e_float>::digits10) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        str_pi = ::make_pi_string(static_cast<std::size_t>(std::numeric_limits<e_float>::digits10));
        my_test_result &= (str == (std::string("+") + str_pi));
        ss.clear();
        ss.str("");

        ss << std::fixed << std::showpos << std::showpoint << std::setprecision(1000) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        str_pi = ::make_pi_string(static_cast<std::size_t>(std::numeric_limits<e_float>::max_digits10));
        const std::string str_zero_fill(1002U - str_pi.length(), static_cast<char>('0'));
        my_test_result &= (str == (std::string("+") + (str_pi + str_zero_fill)));
        ss.clear();
        ss.str("");

        ss << std::fixed << std::showpos << std::showpoint << std::setprecision(29) << ef::pi() / e_float("1e10");
        str = ss.str();
        data.push_back(e_float(str));
        str_pi = ::make_pi_string(static_cast<std::size_t>(19U));
        str_pi.erase(str_pi.cbegin() + 1U);
        my_test_result &= (str == (std::string("+0.") + (std::string(9U, static_cast<char>('0')) + str_pi)));
        ss.clear();
        ss.str("");

        // Note the negative sign.
        ss << std::fixed << std::showpos << std::showpoint << std::setprecision(19) << -ef::pi() * e_float("1e10");
        str = ss.str();
        data.push_back(e_float(str));
        str_pi = ::make_pi_string(static_cast<std::size_t>(29U));
        str_pi.erase(str_pi.cbegin() + 1U);
        str_pi.insert(str_pi.cbegin() + 11U, 1U, static_cast<char>('.'));
        my_test_result &= (str == (std::string("-") + str_pi));
        ss.clear();
        ss.str("");

        // Test right-justify and fill.
        ss << std::fixed << std::noshowpos << std::showpoint << std::setprecision(20) << std::setw(100) << std::setfill(static_cast<char>('$')) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        static const std::string str_dollar(static_cast<std::size_t>(78U), static_cast<char>('$'));
        my_test_result &= (str == (str_dollar + std::string("3.14159265358979323846")));
        ss.clear();
        ss.str("");

        // Test left-justify and fill.
        ss << std::fixed << std::noshowpos << std::showpoint << std::setprecision(20) << std::setw(100) << std::setfill(static_cast<char>('*')) << std::left << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        static const std::string str_star(static_cast<std::size_t>(78U), static_cast<char>('*'));
        my_test_result &= (str == (std::string("3.14159265358979323846") + str_star));
        ss.clear();
        ss.str("");
      }
    };

    class TestCase_case_00007_write_os_floatfield_scientific : public TestCaseWriteToOstreamBase
    {
    public:
      TestCase_case_00007_write_os_floatfield_scientific() { }
      virtual ~TestCase_case_00007_write_os_floatfield_scientific() { }
    private:
      virtual const std::string& name() const
      {
        static const std::string str("TestCase_case_00007_write_os_floatfield_scientific");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.clear();

        my_test_result = true;

        std::string str;
        std::stringstream ss;

        ss << std::scientific << std::showpos << std::showpoint << std::setprecision(1) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("+3.1e+000"));
        ss.clear();
        ss.str("");

        ss << std::scientific << std::showpos << std::showpoint << std::setprecision(2) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("+3.14e+000"));
        ss.clear();
        ss.str("");

        ss << std::scientific << std::showpos << std::showpoint << std::setprecision(20) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("+3.14159265358979323846e+000"));
        ss.clear();
        ss.str("");

        ss << std::scientific << std::showpos << std::showpoint << std::setprecision(std::numeric_limits<e_float>::digits10) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        std::string str_pi = ::make_pi_string(static_cast<std::size_t>(std::numeric_limits<e_float>::digits10));
        my_test_result &= (str == (std::string("+") + (str_pi + std::string("e+000"))));
        ss.clear();
        ss.str("");

        ss << std::scientific << std::showpos << std::showpoint << std::setprecision(1000) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        str_pi = ::make_pi_string(static_cast<std::size_t>(std::numeric_limits<e_float>::max_digits10));
        const std::string str_zero_fill(1002U - str_pi.length(), static_cast<char>('0'));
        my_test_result &= (str == (std::string("+") + ((str_pi + str_zero_fill) + std::string("e+000"))));
        ss.clear();
        ss.str("");

        ss << std::scientific << std::showpos << std::showpoint << std::setprecision(20) << ef::pi() * e_float("1e43");
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("+3.14159265358979323846e+043"));
        ss.clear();
        ss.str("");

        // Note negative sign.
        ss << std::scientific << std::showpos << std::showpoint << std::setprecision(20) << -ef::pi() * e_float("1e-43");
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("-3.14159265358979323846e-043"));
        ss.clear();
        ss.str("");

        // Note uppercase.
        ss << std::scientific << std::showpos << std::showpoint << std::uppercase << std::setprecision(20) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("+3.14159265358979323846E+000"));
        ss.clear();
        ss.str("");
      }
    };

    class TestCase_case_00008_write_os_floatfield_not_set : public TestCaseWriteToOstreamBase
    {
    public:
      TestCase_case_00008_write_os_floatfield_not_set() { }
      virtual ~TestCase_case_00008_write_os_floatfield_not_set() { }
    private:
      virtual const std::string& name() const
      {
        static const std::string str("TestCase_case_00008_write_os_floatfield_not_set");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.clear();

        my_test_result = true;

        std::string str;
        std::stringstream ss;

        ss << ef::zero();
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("0"));
        ss.clear();
        ss.str("");

        ss << ef::one_minus();
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("-1"));
        ss.clear();
        ss.str("");

        ss << ef::ten();
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("10"));
        ss.clear();
        ss.str("");

        ss << std::showpoint << ef::ten();
        str = ss.str();
        data.push_back(e_float(str));
        static const std::string str_10 =   std::string("10.")
                                          + std::string(static_cast<std::size_t>(default_prec() - 2U), static_cast<char>('0'));
        my_test_result &= (str == str_10);
        ss.clear();
        ss.str("");

        ss << std::showpoint << e_float("1e1000");
        str = ss.str();
        data.push_back(e_float(str));
        static const std::string str_1e1000 =   (std::string("1.")
                                              +  std::string(static_cast<std::size_t>(default_prec() - 1U), static_cast<char>('0')))
                                              +  std::string("e+001000");
        my_test_result &= (str == str_1e1000);
        ss.clear();
        ss.str("");

        ss << std::showpoint << e_float("1e" + Util::lexical_cast(default_prec()));
        str = ss.str();
        data.push_back(e_float(str));
        static const std::string str_1ePrec =   (std::string("1.")
                                              +  std::string(static_cast<std::size_t>(default_prec() - 1U), static_cast<char>('0')))
                                              + (std::string("e+00")
                                              +  Util::lexical_cast(default_prec()));
        my_test_result &= (str == str_1ePrec);
        ss.clear();
        ss.str("");

        ss << std::showpoint << e_float("1e" + Util::lexical_cast(default_prec() - 1U));
        str = ss.str();
        data.push_back(e_float(str));
        static const std::string str_1ePm1 =    (std::string("1")
                                              +  std::string(static_cast<std::size_t>(default_prec() - 1U), static_cast<char>('0')))
                                              +  std::string(".");
        my_test_result &= (str == str_1ePm1);
        ss.clear();
        ss.str("");

        ss << std::noshowpoint;

        ss << e_float(100000000000ULL); // 10^11
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("1e+011"));
        ss.clear();
        ss.str("");

        ss << std::showpoint << ef::googol();
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("1.00000e+100"));
        ss.clear();
        ss.str("");

        ss << std::noshowpoint << ef::googol();
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("1e+100"));
        ss.clear();
        ss.str("");

        ss << std::noshowpoint << (static_cast<std::int32_t>(1) / ef::googol());
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("1e-100"));
        ss.clear();
        ss.str("");

        ss << e_float("1e1234");
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("1e+001234"));
        ss.clear();
        ss.str("");

        ss << std::showpoint << ef::eight();
        str = ss.str();
        data.push_back(e_float(str));
        static const std::string str_8_point_zeros =   std::string("8.")
                                                     + std::string(static_cast<std::size_t>(default_prec() - 1U), static_cast<char>('0'));
        my_test_result &= (str == str_8_point_zeros);
        ss.clear();
        ss.str("");

        ss << std::showpoint << -ef::eight();
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == ("-" + str_8_point_zeros));
        ss.clear();
        ss.str("");

        ss << std::noshowpoint << ef::eight();
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("8"));
        ss.clear();
        ss.str("");

        ss << std::noshowpos << std::noshowpoint << std::setprecision(0) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        std::string str_pi = ::make_pi_string(::default_prec() - 1U);
        my_test_result &= (str == str_pi);
        ss.clear();
        ss.str("");

        ss << std::noshowpos << std::noshowpoint << std::setprecision(0) << (ef::pi() * static_cast<std::int32_t>(100));
        str = ss.str();
        data.push_back(e_float(str));
        str_pi = ::make_pi_string(::default_prec() - 1U);
        str_pi.erase(str_pi.cbegin() + 1U, str_pi.cbegin() + 2U);
        str_pi.insert(str_pi.cbegin() + 3U, static_cast<std::size_t>(1U), static_cast<char>('.'));
        my_test_result &= (str == str_pi);
        ss.clear();
        ss.str("");

        ss << std::showpos << std::showpoint << std::setprecision(1) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("+3."));
        ss.clear();
        ss.str("");

        ss << std::showpos << std::showpoint << std::setprecision(20) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        my_test_result &= (str == std::string("+3.1415926535897932385"));
        ss.clear();
        ss.str("");

        ss << std::showpos << std::showpoint << std::setprecision(1000) << ef::pi();
        str = ss.str();
        data.push_back(e_float(str));
        str_pi = std::string("+") + ::make_pi_string(static_cast<std::size_t>(std::numeric_limits<e_float>::max_digits10 - 1));
        static const std::string str_zero_fill(static_cast<std::size_t>(1000 - std::numeric_limits<e_float>::max_digits10), static_cast<char>('0'));
        str_pi += str_zero_fill;
        my_test_result &= (str == str_pi);
        ss.clear();
        ss.str("");
      }
    };

    bool test_case_00006_write_os_floatfield_fixed(const bool b_write_output)
    {
      return TestCase_case_00006_write_os_floatfield_fixed().execute(b_write_output);
    }
    bool test_case_00007_write_os_floatfield_scientific(const bool b_write_output)
    {
      return TestCase_case_00007_write_os_floatfield_scientific().execute(b_write_output);
    }
    bool test_case_00008_write_os_floatfield_not_set(const bool b_write_output)
    {
      return TestCase_case_00008_write_os_floatfield_not_set().execute(b_write_output);
    }
  }
}
