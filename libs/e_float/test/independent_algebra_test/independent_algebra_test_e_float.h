#ifndef INDEPENDENT_ALGEBRA_TEST_E_FLOAT_2020_10_17_H_
  #define INDEPENDENT_ALGEBRA_TEST_E_FLOAT_2020_10_17_H_

  #include <iomanip>
  #include <sstream>

  #include <e_float/e_float.h>
  #include <test/independent_algebra_test/independent_algebra_test_base.h>

  namespace test { namespace independent_algebra {

  class independent_algebra_test_e_float : public independent_algebra_test_base
  {
  public:
    using float_type = e_float;

    float_type my_e_float;

    independent_algebra_test_e_float() : my_e_float() { }

    independent_algebra_test_e_float(const char* str)
      : independent_algebra_test_base(str),
        my_e_float(str) { }

    virtual ~independent_algebra_test_e_float() { }

    virtual void get_string(std::string& str) const
    {
      std::stringstream ss;

      ss << std::scientific
         << std::uppercase
         << std::setprecision(std::streamsize(std::numeric_limits<float_type>::digits10 + 1))
         << my_e_float;

      str = ss.str();
    }
  };

  inline void eval_add(      independent_algebra_test_e_float& result,
                       const independent_algebra_test_e_float& a,
                       const independent_algebra_test_e_float& b)
  {
    result.my_e_float = a.my_e_float + b.my_e_float;
  }

  inline void eval_sub(      independent_algebra_test_e_float& result,
                       const independent_algebra_test_e_float& a,
                       const independent_algebra_test_e_float& b)
  {
    result.my_e_float = a.my_e_float - b.my_e_float;
  }

  inline void eval_mul(      independent_algebra_test_e_float& result,
                       const independent_algebra_test_e_float& a,
                       const independent_algebra_test_e_float& b)
  {
    result.my_e_float = a.my_e_float * b.my_e_float;
  }

  inline void eval_div(      independent_algebra_test_e_float& result,
                       const independent_algebra_test_e_float& a,
                       const independent_algebra_test_e_float& b)
  {
    result.my_e_float = a.my_e_float / b.my_e_float;
  }

  inline void eval_sqrt(      independent_algebra_test_e_float& result,
                        const independent_algebra_test_e_float& a)
  {
    result.my_e_float = ef::sqrt(a.my_e_float);
  }

  } }

#endif // INDEPENDENT_ALGEBRA_TEST_E_FLOAT_2020_10_17_H_
