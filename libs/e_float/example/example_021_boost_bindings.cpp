#include <iomanip>
#include <iostream>

#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/cbrt.hpp>
#include <boost/math/special_functions/gamma.hpp>

#include <boost/multiprecision/e_float_backend.hpp>

#include "examples.h"

typedef boost::multiprecision::number<boost::multiprecision::e_float_backend<100>,
                                      boost::multiprecision::et_off>
e_float_type;

void examples::nr_021::boost_bindings()
{
  const e_float_type y(char(1));
  const e_float_type x(3.0L);
  const e_float_type z(y / x);

  const e_float_type a(z);

  const e_float_type lg_max = log((std::numeric_limits<e_float_type>::max)());
  const e_float_type eps    = std::numeric_limits<e_float_type>::epsilon();

  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << e_float_type(0.5F)                 << std::endl;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << z                                  << std::endl;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << sin  (z)                           << std::endl;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << floor(e_float_type(1.5F))          << std::endl;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << ceil (e_float_type(1.5F))          << std::endl;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << sqrt (e_float_type(2))             << std::endl;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << boost::math::cbrt(e_float_type(2)) << std::endl;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << exp  (z)                           << std::endl;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << atan2(y, x)                        << std::endl;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << atan (z)                           << std::endl;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << log  (e_float_type(2))             << std::endl;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << lg_max                             << std::endl;

  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << eps                    << std::endl;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << sqrt(eps)              << std::endl;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << boost::math::cbrt(eps) << std::endl;

  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << boost::math::tgamma(e_float_type(0.5F))          << std::endl;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << sqrt(boost::math::constants::pi<e_float_type>()) << std::endl;

  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << boost::math::cyl_bessel_j(e_float_type(1) / 7, e_float_type(2.5F))  << std::endl;

  int nexp;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << frexp(e_float_type(2), &nexp) << std::endl;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10) << ldexp(e_float_type(1), 2)     << std::endl;

  std::cout << std::boolalpha << (x < y) << std::endl;
  std::cout << std::boolalpha << (y > x) << std::endl;

  std::cout << std::boolalpha << (lg_max > (std::numeric_limits<std::int64_t>::max)()) << std::endl;
  std::cout << std::boolalpha << (lg_max > (std::numeric_limits<std::int64_t>::min)()) << std::endl;

  const e_float_type a3(("33." + std::string(std::size_t(std::numeric_limits<e_float_type>::digits10 - 2), char('3')) + std::string(16U, char('4'))).c_str());
  const e_float_type b3(e_float_type(100U) / 3);

  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10 + 4) << a3 << std::endl;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10 + 4) << b3 << std::endl;

  std::cout << std::boolalpha << (a3 == b3) << std::endl;
  std::cout << std::boolalpha << (a3 >  b3) << std::endl;
  std::cout << std::boolalpha << (a3 <  b3) << std::endl;

  const e_float_type c3(("33." + std::string(120U, char('3'))).c_str());
  const e_float_type d3(e_float_type(100U) / 3);

  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10 + 4) << c3 << std::endl;
  std::cout << std::setprecision(std::numeric_limits<e_float_type>::digits10 + 4) << d3 << std::endl;

  std::cout << std::boolalpha << (c3 == d3) << std::endl;
  std::cout << std::boolalpha << (c3 >  d3) << std::endl;
  std::cout << std::boolalpha << (c3 <  d3) << std::endl;
}
