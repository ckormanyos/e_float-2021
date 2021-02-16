//          Copyright Christopher Kormanyos 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iomanip>
#include <iostream>

#include <boost/math/concepts/real_type_concept.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/bindings/e_float.hpp>
#include <boost/multiprecision/number.hpp>

namespace local
{
  using big_float_type = boost::multiprecision::number<boost::math::ef::e_float,
                                                       boost::multiprecision::et_off>;
}

template <class T>
void test_extra(T)
{
   T t = 1;
   t   = abs(t);
   t   = abs(t * t);

   t = fabs(t);
   t = fabs(t * t);

   t = sqrt(t);
   t = sqrt(t * t);

   t = floor(t);
   t = floor(t * t);

   t = ceil(t);
   t = ceil(t * t);

   t = trunc(t);
   t = trunc(t * t);

   t = round(t);
   t = round(t * t);

   t = exp(t);
   t = exp(t * t);

   t = log(t);
   t = log(t * t);

   t = log10(t);
   t = log10(t * t);

   t = cos(t);
   t = cos(t * t);

   t = sin(t);
   t = sin(t * t);

   t = tan(t);
   t = tan(t * t);

   t = asin(t);
   t = asin(t * t);

   t = atan(t);
   t = atan(t * t);

   t = acos(t);
   t = acos(t * t);

   t = cosh(t);
   t = cosh(t * t);

   t = sinh(t);
   t = sinh(t * t);

   t = tanh(t);
   t = tanh(t * t);

   double dval = 2;
   t           = pow(t, t);
   t           = pow(t, t * t);
   t           = pow(t, dval);
   t           = pow(t * t, t);
   t           = pow(t * t, t * t);
   t           = pow(t * t, dval);
   t           = pow(dval, t);
   t           = pow(dval, t * t);

   t = atan2(t, t);
   t = atan2(t, t * t);
   t = atan2(t, dval);
   t = atan2(t * t, t);
   t = atan2(t * t, t * t);
   t = atan2(t * t, dval);
   t = atan2(dval, t);
   t = atan2(dval, t * t);

   t = fmod(t, t);
   t = fmod(t, t * t);
   t = fmod(t, dval);
   t = fmod(t * t, t);
   t = fmod(t * t, t * t);
   t = fmod(t * t, dval);
   t = fmod(dval, t);
   t = fmod(dval, t * t);

   typedef typename T::backend_type             backend_type;
   typedef typename backend_type::exponent_type exp_type;
   exp_type                                     e = 0;
   int                                          i = 0;

   t = ldexp(t, i);
   t = ldexp(t * t, i);
   t = ldexp(t, e);
   t = ldexp(t * t, e);

   t = frexp(t, &i);
   t = frexp(t * t, &i);
   t = frexp(t, &e);
   t = frexp(t * t, &e);

   t = scalbn(t, i);
   t = scalbn(t * t, i);
   t = scalbn(t, e);
   t = scalbn(t * t, e);

   t = logb(t);
   t = logb(t * t);
   e = ilogb(t);
   e = ilogb(t * t);
}

void foo()
{
  test_extra(local::big_float_type());
}

bool test_boost_real_concept()
{
  foo();

  BOOST_CONCEPT_ASSERT((boost::math::concepts::RealTypeConcept<local::big_float_type>));

  return true;
}
