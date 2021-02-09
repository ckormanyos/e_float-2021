#include <ctime>
#include <random>

#include <e_float/e_float_functions.h>
#include <test/independent_algebra_test/independent_algebra_test.h>

std::ranlux24    test::independent_algebra::control::eng_sign    (std::clock());
std::minstd_rand test::independent_algebra::control::eng_exp     (std::clock());
std::mt19937     test::independent_algebra::control::eng_mantissa(std::clock());

bool test::independent_algebra::control::eval_eq(const independent_algebra_test_e_float&   a,
                                                 const independent_algebra_test_boost_cpp& b)
{
  std::string str_b;

  b.get_string(str_b);

  const e_float ef_b(str_b);

  const e_float ratio = ef::fabs(1 - ef::fabs(a.my_e_float / ef_b));

  static const e_float eps = std::numeric_limits<e_float>::epsilon() * 10;

  return (ratio < eps);
}

void test::independent_algebra::control::get_random_float_string(std::string& str,
                                                                 const bool do_seed_random_generators,
                                                                 const bool value_is_unsigned)
{
  if(do_seed_random_generators)
  {
    const std::clock_t s = std::clock();

    eng_sign.seed    (s);
    eng_exp.seed     (s);
    eng_mantissa.seed(s);
  }

  std::uniform_int_distribution<std::uint32_t> dst_sign    (UINT32_C(0), UINT32_C(1));
  std::uniform_int_distribution<std::uint32_t> dst_exp     (UINT32_C(0), (std::uint32_t) (((unsigned long long) E_FLOAT_DIGITS10 * 6ULL) / 10ULL));
  std::uniform_int_distribution<std::uint32_t> dst_mantissa(UINT32_C(0), UINT32_C(100000000) - UINT32_C(1));

  str = std::string();

  std::stringstream ss;

  std::uint32_t u;

  while(str.length() < std::string::size_type(std::numeric_limits<e_float>::digits10))
  {
    std::uint32_t u = dst_mantissa(eng_mantissa);

    ss << std::setw(8U) << std::setfill('0') << u;

    str += ss.str();

    ss.rdbuf()->str(std::string(""));
  }

  std::uint32_t u_sign = dst_sign(eng_sign);

  str += ((u_sign == 0U) ? "E+" : "E-");

  std::uint32_t u_exp = dst_exp(eng_exp);

  ss << u_exp;

  str += ss.str();

  ss.rdbuf()->str(std::string(""));

  u = dst_mantissa(eng_mantissa);

  ss << u;

  u_sign = dst_sign(eng_sign);

  str = (value_is_unsigned ? "" : ((u_sign == 0U) ? "" : "-")) + ss.str() + "." + str;
}
