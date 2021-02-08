#ifndef INDEPENDENT_ALGEBRA_TEST_BOOST_CPP_2020_10_17_H_
  #define INDEPENDENT_ALGEBRA_TEST_BOOST_CPP_2020_10_17_H_

  #include <iomanip>
  #include <sstream>

  #include <boost/multiprecision/cpp_bin_float.hpp>
  #include <boost/e_float/e_float.hpp>
  #include <test/independent_algebra_test/independent_algebra_test_base.h>

  namespace test { namespace independent_algebra {

  class independent_algebra_test_boost_cpp : public independent_algebra_test_base
  {
  public:
    using float_type =
      boost::multiprecision::number<boost::multiprecision::cpp_bin_float<E_FLOAT_DIGITS10 + 3>,
                                    boost::multiprecision::et_off>;

    float_type my_cpp_bin_float;

    independent_algebra_test_boost_cpp() : my_cpp_bin_float() { }

    independent_algebra_test_boost_cpp(const char* str)
      : independent_algebra_test_base(str),
        my_cpp_bin_float(str) { }

    virtual ~independent_algebra_test_boost_cpp() { }

    virtual void get_string(std::string& str) const
    {
      std::stringstream ss;

      ss << std::scientific
         << std::uppercase
         << std::setprecision(std::streamsize(std::numeric_limits<float_type>::digits10 + 1))
         << my_cpp_bin_float;

      str = ss.str();
    }
  };

  inline void eval_add(      independent_algebra_test_boost_cpp& result,
                       const independent_algebra_test_boost_cpp& a,
                       const independent_algebra_test_boost_cpp& b)
  {
    result.my_cpp_bin_float = a.my_cpp_bin_float + b.my_cpp_bin_float;
  }

  inline void eval_sub(      independent_algebra_test_boost_cpp& result,
                       const independent_algebra_test_boost_cpp& a,
                       const independent_algebra_test_boost_cpp& b)
  {
    result.my_cpp_bin_float = a.my_cpp_bin_float - b.my_cpp_bin_float;
  }

  inline void eval_mul(      independent_algebra_test_boost_cpp& result,
                       const independent_algebra_test_boost_cpp& a,
                       const independent_algebra_test_boost_cpp& b)
  {
    result.my_cpp_bin_float = a.my_cpp_bin_float * b.my_cpp_bin_float;
  }

  inline void eval_div(      independent_algebra_test_boost_cpp& result,
                       const independent_algebra_test_boost_cpp& a,
                       const independent_algebra_test_boost_cpp& b)
  {
    result.my_cpp_bin_float = a.my_cpp_bin_float / b.my_cpp_bin_float;
  }

  inline void eval_sqrt(      independent_algebra_test_boost_cpp& result,
                        const independent_algebra_test_boost_cpp& a)
  {
    result.my_cpp_bin_float = sqrt(a.my_cpp_bin_float);
  }

  } }

#endif // INDEPENDENT_ALGEBRA_TEST_BOOST_CPP_2020_10_17_H_
