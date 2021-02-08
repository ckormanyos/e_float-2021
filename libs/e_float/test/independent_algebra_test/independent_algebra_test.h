#ifndef INDEPENDENT_ALGEBRA_TEST_2020_10_17_H_
  #define INDEPENDENT_ALGEBRA_TEST_2020_10_17_H_

  #include <iostream>
  #include <random>

  #include <boost/e_float/e_float_functions.hpp>
  #include <test/independent_algebra_test/independent_algebra_test_e_float.h>
  #include <test/independent_algebra_test/independent_algebra_test_boost_cpp.h>

  namespace test { namespace independent_algebra {

  struct control
  {
    static std::ranlux24    eng_sign;
    static std::minstd_rand eng_exp;
    static std::mt19937     eng_mantissa;

    static bool eval_eq(const independent_algebra_test_e_float&   a,
                        const independent_algebra_test_boost_cpp& b);

    static void get_random_float_string(std::string& str,
                                        const bool do_seed_random_generators = false,
                                        const bool value_is_unsigned = false);
  };

  template<const std::uint32_t CountN,
           const std::uint32_t RoundN,
           typename IndependentAlgebraTestControlType>
  bool independent_algebra_test_add()
  {
    using independent_algebra_test_control_type = IndependentAlgebraTestControlType;
    const std::uint32_t count = CountN;
    const std::uint32_t round = RoundN;

    bool result_is_ok = true;

    std::string str_a;
    std::string str_b;

    std::uint32_t i;
    std::uint32_t j;

    for(i = 0U; i < round && result_is_ok; ++i)
    {
      for(j = 0U; j < count && result_is_ok; ++j)
      {
        test::independent_algebra::control::get_random_float_string(str_a, j == 0U);
        independent_algebra_test_control_type                       a_ctrl(str_a.c_str());
        test::independent_algebra::independent_algebra_test_e_float a_ef  (str_a.c_str());

        test::independent_algebra::control::get_random_float_string(str_b);
        independent_algebra_test_control_type                       b_ctrl(str_b.c_str());
        test::independent_algebra::independent_algebra_test_e_float b_ef  (str_b.c_str());

        independent_algebra_test_control_type                       result_ctrl;
        test::independent_algebra::independent_algebra_test_e_float result_ef;

        eval_add(result_ctrl, a_ctrl, b_ctrl);
        eval_add(result_ef,   a_ef,   b_ef);

        result_is_ok &= test::independent_algebra::control::eval_eq(result_ef, result_ctrl);
      }

      std::cout << "independent_algebra_test_add() round: " << i << ", result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
    }

    return ((i == round) && (j == count));
  }

  template<const std::uint32_t CountN,
           const std::uint32_t RoundN,
           typename IndependentAlgebraTestControlType>
  bool independent_algebra_test_sub()
  {
    using independent_algebra_test_control_type = IndependentAlgebraTestControlType;
    const std::uint32_t count = CountN;
    const std::uint32_t round = RoundN;

    bool result_is_ok = true;

    std::string str_a;
    std::string str_b;

    std::uint32_t i;
    std::uint32_t j;

    for(i = 0U; i < round && result_is_ok; ++i)
    {
      for(j = 0U; j < count && result_is_ok; ++j)
      {
        test::independent_algebra::control::get_random_float_string(str_a, j == 0U);
        independent_algebra_test_control_type                       a_ctrl(str_a.c_str());
        test::independent_algebra::independent_algebra_test_e_float a_ef  (str_a.c_str());

        test::independent_algebra::control::get_random_float_string(str_b);
        independent_algebra_test_control_type                       b_ctrl(str_b.c_str());
        test::independent_algebra::independent_algebra_test_e_float b_ef  (str_b.c_str());

        independent_algebra_test_control_type                       result_ctrl;
        test::independent_algebra::independent_algebra_test_e_float result_ef;

        eval_sub(result_ctrl, a_ctrl, b_ctrl);
        eval_sub(result_ef,   a_ef,   b_ef);

        result_is_ok &= test::independent_algebra::control::eval_eq(result_ef, result_ctrl);
      }

      std::cout << "independent_algebra_test_sub() round: " << i << ", result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
    }

    return ((i == round) && (j == count));
  }

  template<const std::uint32_t CountN,
           const std::uint32_t RoundN,
           typename IndependentAlgebraTestControlType>
  bool independent_algebra_test_mul()
  {
    using independent_algebra_test_control_type = IndependentAlgebraTestControlType;
    const std::uint32_t count = CountN;
    const std::uint32_t round = RoundN;

    bool result_is_ok = true;

    std::string str_a;
    std::string str_b;

    std::uint32_t i;
    std::uint32_t j;

    for(i = 0U; i < round && result_is_ok; ++i)
    {
      for(j = 0U; j < count && result_is_ok; ++j)
      {
        test::independent_algebra::control::get_random_float_string(str_a, j == 0U);
        independent_algebra_test_control_type                       a_ctrl(str_a.c_str());
        test::independent_algebra::independent_algebra_test_e_float a_ef  (str_a.c_str());

        test::independent_algebra::control::get_random_float_string(str_b);
        independent_algebra_test_control_type                       b_ctrl(str_b.c_str());
        test::independent_algebra::independent_algebra_test_e_float b_ef  (str_b.c_str());

        independent_algebra_test_control_type                       result_ctrl;
        test::independent_algebra::independent_algebra_test_e_float result_ef;

        eval_mul(result_ctrl, a_ctrl, b_ctrl);
        eval_mul(result_ef,   a_ef,   b_ef);

        result_is_ok &= test::independent_algebra::control::eval_eq(result_ef, result_ctrl);
      }

      std::cout << "independent_algebra_test_mul() round: " << i << ", result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
    }

    return ((i == round) && (j == count));
  }

  template<const std::uint32_t CountN,
           const std::uint32_t RoundN,
           typename IndependentAlgebraTestControlType>
  bool independent_algebra_test_div()
  {
    using independent_algebra_test_control_type = IndependentAlgebraTestControlType;
    const std::uint32_t count = CountN;
    const std::uint32_t round = RoundN;

    bool result_is_ok = true;

    std::string str_a;
    std::string str_b;

    std::uint32_t i;
    std::uint32_t j;

    for(i = 0U; i < round && result_is_ok; ++i)
    {
      for(j = 0U; j < count && result_is_ok; ++j)
      {
        test::independent_algebra::control::get_random_float_string(str_a, j == 0U);
        independent_algebra_test_control_type                       a_ctrl(str_a.c_str());
        test::independent_algebra::independent_algebra_test_e_float a_ef  (str_a.c_str());

        test::independent_algebra::control::get_random_float_string(str_b);
        independent_algebra_test_control_type                       b_ctrl(str_b.c_str());
        test::independent_algebra::independent_algebra_test_e_float b_ef  (str_b.c_str());

        independent_algebra_test_control_type                       result_ctrl;
        test::independent_algebra::independent_algebra_test_e_float result_ef;

        eval_div(result_ctrl, a_ctrl, b_ctrl);
        eval_div(result_ef,   a_ef,   b_ef);

        result_is_ok &= test::independent_algebra::control::eval_eq(result_ef, result_ctrl);
      }

      std::cout << "independent_algebra_test_div() round: " << i << ", result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
    }

    return ((i == round) && (j == count));
  }

  template<const std::uint32_t CountN,
           const std::uint32_t RoundN,
           typename IndependentAlgebraTestControlType>
  bool independent_algebra_test_sqrt()
  {
    using independent_algebra_test_control_type = IndependentAlgebraTestControlType;
    const std::uint32_t count = CountN;
    const std::uint32_t round = RoundN;

    bool result_is_ok = true;

    std::string str_a;
    std::string str_b;

    std::uint32_t i;
    std::uint32_t j;

    for(i = 0U; i < round && result_is_ok; ++i)
    {
      for(j = 0U; j < count && result_is_ok; ++j)
      {
        test::independent_algebra::control::get_random_float_string(str_a, j == 0U, true);
        independent_algebra_test_control_type                       a_ctrl(str_a.c_str());
        test::independent_algebra::independent_algebra_test_e_float a_ef  (str_a.c_str());

        independent_algebra_test_control_type                       result_ctrl;
        test::independent_algebra::independent_algebra_test_e_float result_ef;

        eval_sqrt(result_ctrl, a_ctrl);
        eval_sqrt(result_ef,   a_ef);

        result_is_ok &= test::independent_algebra::control::eval_eq(result_ef, result_ctrl);
      }

      std::cout << "independent_algebra_test_sqrt() round: " << i << ", result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
    }

    return ((i == round) && (j == count));
  }

  } }

#endif // INDEPENDENT_ALGEBRA_TEST_2020_10_17_H_
