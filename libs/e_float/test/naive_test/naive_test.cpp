//! \file
// naive_test.cpp

// Copyright Paul A. Bristow 2011.
// Copyright Christopher Kormanyos 2011.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Really naive test of using e_float.

#define BOOST_TEST_MAIN
#define BOOST_LIB_DIAGNOSTIC "on"// Show library file details.
// Linking to lib file: libboost_unit_test_framework-vc100-mt-gd-1_48.lib  (trunk at Jul 11)

//  #define E_FLOAT_DIGITS10 50 as command line using MSVC or in jamfile (but needs b2 -a option?)

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::dec;
using std::hex;
using std::boolalpha;
using std::scientific;
using std::fixed;
using std::defaultfloat;
using std::showpos;
using std::showpoint;

#include <iomanip>
using std::setprecision;
using std::setw;
#include <string>
using std::string;
#include <sstream>
//using std::istringstream;
//using std::ostringstream

#include <boost/test/unit_test.hpp> // Enhanced for unit_test framework autolink.
#include <boost/test/floating_point_comparison.hpp>

#include <boost/e_float/e_float.hpp>
#include <boost/e_float/e_float_constants.hpp>

//Macros to Check using manips output expected string result, for example:
// CHECK_OUT(hex << showbase << setw(10) << i, "       0xf")
// CHECK_OUT(scientific << setw(20) << d, "       1.234568e+001");

// Compare a output with expected result. 
#define CHECK_OUT(manips, result)\
{ \
  std::ostringstream oss;\
  oss << manips;\
  BOOST_CHECK_EQUAL(oss.str(), result);\
}

#define  CHECK_LENGTH(manips, result)\
{\
  BOOST_CHECK_EQUAL(oss.str().length(), strlen(result));\
}\

// Compare results of reading string in,
#define  CHECK_IN(in, value)\
{\
  e_float r;\
  std::istringstream iss(in);\
  iss >> r;\
  BOOST_CHECK_CLOSE_FRACTION(r, value, std::numeric_limits<e_float>::epsilon());\
} // #define  CHECK_IN(in, value, sd, df, types)

// CHECK_OUT_IN Output via manips, and read back in, check is same. 'Loopback'.
#define  CHECK_OUT_IN(manips, result, value)\
{\
  std::stringstream ss;\
  ss << manips;\
  BOOST_CHECK_EQUAL(ss.str(), result);\
  e_float r;\
  ss >> r;\
  BOOST_CHECK_CLOSE_FRACTION(r, value, std::numeric_limits<e_float>::epsilon());\
}// #define  CHECK_OUT_IN(manips, result)


// Must #define E_FLOAT_TYPE_EFX; in project properties.

// Note: exact double means exactly representable as double, for example: 0.5,
// but NOT 0.1.
// Integral may be an integer or a double having an integral value.

BOOST_AUTO_TEST_CASE(e_float_test_template)
{ // These are just examples of using Boost.Test.
  // Need to be removed when no longer helpful.
  BOOST_TEST_MESSAGE("Test Boost.e_float"); // Only appears if command line has --log_level="message"

  string m = "Test with ";
  m+= __FILE__;
  m+= " edited ";
  m += __TIMESTAMP__ ".\n"; 
  BOOST_TEST_MESSAGE(m);
  BOOST_CHECK(true);
  BOOST_CHECK_EQUAL(1, 1);
  BOOST_CHECK_NE(1, -1);
  BOOST_CHECK_CLOSE_FRACTION(1.0, 1.0+std::numeric_limits<double>::epsilon(), std::numeric_limits<double>::epsilon());
  double d = 123.456789;
  // cout << scientific << d << endl; //  Outputs: "1.234568e+003"
  CHECK_OUT(d, "123.457"); // Default. == << std::defaultfloat
  CHECK_OUT(defaultfloat << d, "123.457"); // Default. == << std::defaultfloat
  string ddef = "123.457"; // default float output.
  CHECK_OUT(d, ddef); // Default. == << std::defaultfloat
  CHECK_OUT(defaultfloat << d, ddef); // Default. == << std::defaultfloat
  CHECK_OUT(scientific << d, "1.234568e+002");
  CHECK_OUT(fixed << d, "123.456789");
  int m1 = -1; // negative variable.
  CHECK_OUT(m1, "-1"); //  negative constant. 
  CHECK_OUT(hex << m1, "ffffffff"); // with hex manipulator.
  // Checking input with inline.
  e_float r;
  std::istringstream iss("123.456");
  iss >> r;
  BOOST_CHECK_CLOSE_FRACTION(r, e_float("123.456"), std::numeric_limits<e_float>::epsilon());
  BOOST_CHECK_EQUAL(r, e_float("123.456")); // Also works
  // Repeat same test using CHECK_IN macro defined above.
  CHECK_IN("123.456", e_float("123.456"));
  
  //CHECK_IN("123.456", e_float(123.456)); // Mistaken conversion from less accurate double.
  // Fails r{123.456} and e_float(123.456){123.4560000000000030695446184836328029632568359375}
  // differ by more than 1e-49.

  // CHECK_OUT_IN Output via manips, and read back in, check is same. 'Loopback'.
  // #define  CHECK_OUT_IN(manips, result, value)
  { // Integer example.
    int i = 255;
    std::string result = "ff";
    int value = 255;
    std::stringstream ss;
    ss << hex << i;
    BOOST_CHECK_EQUAL(ss.str(), result);
    int read;
    ss >> read;
    BOOST_CHECK_EQUAL(read, value);
  }
  { // double example
    double w = 123.456;
    std::string result = "123.456000";
    double value = 123.456;
    std::stringstream ss;
    ss << std::fixed << w;
    //cout << ss.str() << endl;
    BOOST_CHECK_EQUAL(ss.str(), result);
    double read;
    ss >> read;
    BOOST_CHECK_EQUAL(read, value);
    BOOST_CHECK_CLOSE_FRACTION(read, value, std::numeric_limits<double>::epsilon());
  }
  { // e_float example
    e_float w("123.456");
    std::string result = "123.456000";  // double result was "123.456000";
    e_float value("123.456");
    std::stringstream ss;
    ss << std::fixed << w;
    //cout << ss.str() << endl;
    BOOST_CHECK_EQUAL(ss.str(), result);
    e_float read;
    ss >> read;
    BOOST_CHECK_EQUAL(read, value);
    BOOST_CHECK_CLOSE_FRACTION(read, value, std::numeric_limits<e_float>::epsilon());

    CHECK_OUT_IN(std::fixed << w, result, value);
  }

} // BOOST_AUTO_TEST_CASE(e_float_template)

BOOST_AUTO_TEST_CASE(e_float_test_macros)
{ // Check some macro values.
  // 
  BOOST_CHECK_EQUAL(E_FLOAT_DIGITS10, 50); // Assumes we are testing at 50 digits, NOT the default.
} // BOOST_AUTO_TEST_CASE(e_float_test_macros)


BOOST_AUTO_TEST_CASE(e_float_test_ios)
{ // Check some IOS defaults.
  BOOST_CHECK_EQUAL(cout.precision(), 6);
  std::ostringstream oss;
  BOOST_CHECK_EQUAL(oss.precision(), 6);
  }

BOOST_AUTO_TEST_CASE(e_float_test_input)
{ // 
  BOOST_TEST_MESSAGE("Test Boost.e_float input."); 

   CHECK_IN("2", e_float("2"));
   CHECK_IN("-2", e_float("-2"));
   CHECK_IN("+2", e_float("+2"));
   CHECK_IN("-2.", e_float("-2."));

   CHECK_IN("123.456", e_float("123.456"));
   CHECK_IN("0.0123456", e_float("0.0123456"));
   CHECK_IN("1e-6", e_float("1e-6"));
   CHECK_IN("-1e-6", e_float("-1e-6"));
} // BOOST_AUTO_TEST_CASE(e_float_test_input)

BOOST_AUTO_TEST_CASE(e_float_test_output)
{ // 

  BOOST_TEST_MESSAGE("Test Boost.e_float output."); 

  double double_four = 4.;

  cout << "cout << showpoint << double_four outputs: " << showpoint << double_four << endl;
  cout << "cout << setprecision(17) << showpoint << double_four  outputs: " << setprecision(17) << showpoint << double_four << endl;

  e_float my_float;
  e_float e_four(4); // Note integer value.
  e_float e_m1(-1); // Note integer value.


  my_float = e_float(2) +  e_float(2); // OK
  BOOST_CHECK_EQUAL(my_float, e_four);

  double d_four(4.); // 
  CHECK_OUT(d_four, "4"); // Default is no decimal point.
  CHECK_OUT(defaultfloat << d_four, "4"); // Default is no decimal point.
  CHECK_OUT(std::showpos << d_four, "+4"); // OK 

  CHECK_OUT(e_four, "4"); // No decimal point.
  CHECK_OUT(defaultfloat << e_four, "4"); // No decimal point.
  CHECK_OUT(std::showpos << e_four, "+4"); // Expect +

  // http://www.cplusplus.com/reference/iostream/manipulators/setprecision/ says
  // On the default floating-point notation,
  // the precision field specifies the maximum number of meaningful digits to display in total
  // counting both those before and those after the decimal point.
  // Notice that it is not a minimum and therefore it does not pad the displayed number 
  // with trailing zeros if the number can be displayed with less digits than the precision.

  // In both the fixed and scientific notations, the precision field specifies exactly
  // how many digits to display after the decimal point, even if this includes trailing decimal zeros.
  // The number of digits before the decimal point does not matter in this case.

  CHECK_OUT(std::showpoint << d_four, "4.00000"); // Should be 4. - no + and 6-1 = 5 trailing zeros.
  CHECK_OUT(defaultfloat<< setprecision(4) << std::showpoint << d_four, "4.000"); // Should be 4. - no + and 4-1 = 3 trailing zeros.
  CHECK_OUT(setprecision(4) << std::showpoint << d_four, "4.000"); // Should be 4. - no + and 4-1 = 3 trailing zeros.
  CHECK_OUT(setprecision(10) << std::showpoint << d_four, "4.000000000"); // Should be 4. - no + and 10-1 = 9 trailing zeros.
  CHECK_OUT(setprecision(std::numeric_limits<double>::max_digits10) << std::showpoint << d_four, "4.0000000000000000"); // Should be 4. with 17-1 = 16 trailing zeros.
  // Is specify fixed for floatfield, the number of digits of precision is the number after the decimal point,
  // so the number of trailing zeros is increased by one in this case.
  CHECK_OUT(fixed << setprecision(4) << std::showpoint << d_four, "4.0000"); // Should be 4. and 4 trailing zeros.
  CHECK_OUT(scientific << setprecision(4) << std::showpoint << d_four, "4.0000e+000"); // Should be 4. and 4 trailing zeros, and exponent.

  // e_float tests.

  CHECK_OUT(std::showpoint << e_four, "4.00000"); // Should be 4.0000 as double.
  CHECK_OUT(setprecision(std::numeric_limits<e_float>::max_digits10) << std::showpoint << e_four, "4."); // Should be 4. and max_digits10-1 = 49 trailing zeros.
  CHECK_OUT(fixed << setprecision(std::numeric_limits<e_float>::max_digits10) << std::showpoint << e_four, "4.000000000000000000000000000000000000000000000000000"); // Should be 4. and max_digits10 = 51 trailing zeros.
  CHECK_OUT(scientific << setprecision(std::numeric_limits<e_float>::max_digits10) << std::showpoint << e_four, "4.000000000000000000000000000000000000000000000000000e+000"); // Should be 4. and max_digits10 = 51 trailing zeros.

  CHECK_OUT(std::showpos << std::showpoint << d_four, "+4.00000"); // Should be +4. and 6 digits including 5 trailing zeros.
  CHECK_OUT(std::showpos << std::showpoint << e_four, "+4."); // Should be +4. and E_FLOAT_DIGITS10, E_FLOAT_DIGITS10-1 trailing zeros.

  CHECK_OUT(scientific << e_four, "4.000000e+000"); // 6 trailing zeros & 3 exponent digits.
  CHECK_OUT(fixed << e_four, "4.000000"); // // 6 trailing zeros.
  CHECK_OUT(defaultfloat << e_four, "4"); //
  CHECK_OUT(defaultfloat << e_m1, "-1"); // 

  CHECK_OUT(defaultfloat << e_m1, "-1"); // 
  CHECK_OUT(fixed << e_m1, "-1.000000"); // Default precision 6
  CHECK_OUT(scientific << e_m1, "-1.000000e+000"); // Default precision 6, and 3 exponent digits.

  double d_fifth = 1./5.;
  // defaultfloat
  CHECK_OUT(showpoint << setprecision(1) << d_fifth, "0.2"); 
  CHECK_OUT(setprecision(1) << ef::fifth(), "0.2");  // 
  // fixed << showpos << showpoint << setprecision(n) should give a total of n (precision) digits after decimal point.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(1) << ef::fifth(), "+0.2"); // 1 digits after decimal point, so no trailing zeros.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(2) << ef::fifth(), "+0.20"); // 1 digit after decimal point, 1 trailing zero.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(10) << ef::fifth(), "+0.2000000000"); // 1 digit after decimal point, 9 trailing zeros.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(20) << ef::fifth(), "+0.20000000000000000000");  // 1 digit after decimal point, 19 trailing zeros.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(50) << ef::fifth(), "+0.20000000000000000000000000000000000000000000000000");  // 1 digit after decimal point, 50-1 trailing zeros.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(std::numeric_limits<e_float>::max_digits10) << ef::fifth(), "+0.200000000000000000000000000000000000000000000000000");  // 50 trailing zeros.

  double pi = 3.14159265358979323846264338327950288419716939937511;
  CHECK_OUT(fixed << showpos << showpoint << setprecision(2) << pi, "+3.14"); // 2 digits after decimal point.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(3) << pi, "+3.142"); // 3 digits after decimal point.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(6) << pi, "+3.141593"); // 6 digits after decimal point.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(10) << pi, "+3.1415926536"); // 10 digits after decimal point.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(11) << pi, "+3.14159265359"); // 11 digits after decimal point.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(12) << pi, "+3.141592653590"); // 12 digits after decimal point.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(20) << pi, "+3.14159265358979310000"); // setprecision(20) more than max_digits10 (17!) so 4 trailing zeros.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(std::numeric_limits<double>::max_digits10) << pi, "+3.14159265358979310"); // max_digits10.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(std::numeric_limits<double>::digits10) << pi, "+3.141592653589793"); // digits10 'guaranteed' no noisy digits.

  // With showpoint for decimal point and trailing zeros.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(2) << ef::pi(), "+3.14"); // 2 digits after decimal point.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(3) << ef::pi(), "+3.142"); // 3 digits after decimal point.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(6) << ef::pi(), "+3.141593"); // 6 digits after decimal point.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(10) << ef::pi(), "+3.1415926536"); // 10 digits after decimal point.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(20) << ef::pi(), "+3.14159265358979323846"); // 20 digits after decimal point.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(50) << ef::pi(), "+3.14159265358979323846264338327950288419716939937511"); // 50 digits after decimal point.
  CHECK_OUT(fixed << showpos << showpoint << setprecision(std::numeric_limits<e_float>::max_digits10) << ef::pi(), "+3.141592653589793238462643383279502884197169399375106");  // 50 +1 digits after decimal point.

  // Fixed without showpoint for decimal point and trailing zeros, and negative.
  CHECK_OUT(fixed << setprecision(2) << -ef::pi(), "-3.14"); // 
  CHECK_OUT(fixed << setprecision(3) << -ef::pi(), "-3.142"); //
  CHECK_OUT(fixed << setprecision(6) << -ef::pi(), "-3.141593"); // 
  CHECK_OUT(fixed << setprecision(10) << -ef::pi(), "-3.1415926536"); // 
  CHECK_OUT(fixed << setprecision(11) << -ef::pi(), "-3.14159265359"); // 
  CHECK_OUT(fixed << setprecision(12) << -ef::pi(), "-3.141592653590"); // 


  CHECK_OUT(fixed << setprecision(20) << -ef::pi(), "-3.14159265358979323846"); 
  CHECK_OUT(fixed << setprecision(50) << -ef::pi(), "-3.14159265358979323846264338327950288419716939937511"); 
  CHECK_OUT(fixed << setprecision(std::numeric_limits<e_float>::max_digits10) << -ef::pi(), "-3.141592653589793238462643383279502884197169399375106"); 

} // BOOST_AUTO_TEST_CASE(e_float_test_output)

BOOST_AUTO_TEST_CASE(e_float_test_int_arith)
{ // 

  BOOST_TEST_MESSAGE("Test Boost.e_float integer arithmetic."); 

  e_float my_float;
  e_float e_four(4); // Note integer value.
  BOOST_CHECK_EQUAL(my_float, my_float); // OK

  my_float = e_float(2) +  e_float(2); // OK

  BOOST_CHECK_EQUAL(my_float, e_four);
} // BOOST_AUTO_TEST_CASE(e_float_test_int_arith)


BOOST_AUTO_TEST_CASE(e_float_test_float_arith)
{ // 

  BOOST_TEST_MESSAGE("Test Boost.e_float float arithmetic.");
  const e_float eps = std::numeric_limits<e_float>::epsilon();
  //cout << " std::numeric_limits<e_float>::epsilon() " << eps << endl; // Ugly TODO.
  // std::numeric_limits<e_float>::epsilon() 1.000000000e-0000000000000000049 for digits = 50

  BOOST_CHECK(std::numeric_limits<e_float>::is_specialized); // Must be specialized for e_float.

  BOOST_CHECK(!std::numeric_limits<e_float>::is_iec559); // iec559 == IEEE754 (or ieee854 or IEEE754r?).
  // Must NOT claim IEEE754 because that is a binary radix.

  BOOST_CHECK_EQUAL(e_float(2), e_float(2)); // Constructed from two ints.
  BOOST_CHECK_EQUAL(e_float(2), e_float(2.)); // Constructed from one int and exact double.
  BOOST_CHECK_EQUAL(e_float(2.), e_float(2)); // Constructed from one int and exact double.
  BOOST_CHECK_EQUAL(e_float(2.), e_float(2.)); // Constructed from two integral value doubles.
  BOOST_CHECK_EQUAL(e_float(0.5), e_float(0.5)); // Constructed from two exact doubles.

  const e_float e_float_max = ef::value_max(); // e_float 


  e_float my_float;
  BOOST_CHECK_EQUAL(my_float, static_cast<e_float>(0));
  BOOST_CHECK_EQUAL(my_float, my_float); // OK
  my_float = e_float(2.2) +  e_float(2.2);

  e_float e_four(4.4); // Construct from double.
  BOOST_CHECK_EQUAL(my_float, e_four); // OK

  cout << " difference  my_float - e_four = " << my_float - e_four << endl;
  //  difference  my_float - e_four = 0
 
  e_float e_diff;
  e_diff = my_float - e_four;

  cout << " difference  my_float - e_four = " << e_diff << endl;
  cout << "  e_float(0.0) = " << e_float(0.0) << endl; // 
  cout << "  e_float(0) = " << e_float(0) << endl; // 0 = Phew!

  BOOST_CHECK_EQUAL(e_diff, e_float(static_cast<std::int32_t>(0.0)));
  BOOST_CHECK_EQUAL(e_diff, e_float(0.0));
  BOOST_CHECK_EQUAL(e_diff, e_float(0.0));
  BOOST_CHECK_EQUAL(e_diff, ef::zero());
  BOOST_CHECK_EQUAL(my_float - e_four, ef::zero());

  BOOST_CHECK_CLOSE_FRACTION(my_float, e_four, eps);

  BOOST_CHECK_NE(e_float(2), e_float(2.1)); // Different values - expect to fail.

  BOOST_CHECK_EQUAL(e_float(0.5), ef::half()); // Compare e_float constant.
  BOOST_CHECK_EQUAL(ef::half(), e_float(0.5));  // Compare other way.
  // BOOST_CHECK_EQUAL(ef::half(), 0.5);  // Compare with exact double. Warning C4244 and fails
  BOOST_CHECK_EQUAL(e_float(0.5), e_float(1)/static_cast<std::int32_t>(2));  // 
  
// Compare exact double.

} // BOOST_AUTO_TEST_CASE(e_float_test_float_arith)

BOOST_AUTO_TEST_CASE(e_float_test_numeric_limits)
{ 
  BOOST_CHECK(E_FLOAT_TYPE_EFX);
  BOOST_CHECK_EQUAL(E_FLOAT_TYPE_EFX, 1);
  BOOST_TEST_MESSAGE("Test Boost.e_float numeric_limits.");

  BOOST_CHECK(std::numeric_limits<e_float>::is_specialized); // Must be specialized for e_float.
  BOOST_CHECK(std::numeric_limits<e_float>::is_signed); // Must be signed for e_float.

  BOOST_CHECK(!std::numeric_limits<e_float>::traps); 

  BOOST_CHECK(!std::numeric_limits<e_float>::tinyness_before); 
  BOOST_CHECK(!std::numeric_limits<e_float>::is_modulo); 
  BOOST_CHECK(std::numeric_limits<e_float>::has_infinity); 
  BOOST_CHECK(std::numeric_limits<e_float>::has_quiet_NaN); 
  BOOST_CHECK(!std::numeric_limits<e_float>::has_signaling_NaN); 
  BOOST_CHECK(!std::numeric_limits<e_float>::has_denorm_loss); 

  // BOOST_CHECK(!std::numeric_limits<e_float>::float_denorm_style, 0); // TODO
  
  BOOST_CHECK(!std::numeric_limits<e_float>::is_iec559); // iec559 == IEEE754 (or ieee854 or IEEE754r?).
  // Must NOT claim IEEE754 because that has a binary radix.
  BOOST_CHECK(!std::numeric_limits<e_float>::is_integer); // Is floating point!
  BOOST_CHECK(!std::numeric_limits<e_float>::is_exact); // Is floating point!

  BOOST_CHECK_EQUAL(std::numeric_limits<e_float>::digits, E_FLOAT_DIGITS10);
  BOOST_CHECK_EQUAL(std::numeric_limits<e_float>::radix, 10); // radix = 10
  BOOST_CHECK_EQUAL(std::numeric_limits<e_float>::digits10, E_FLOAT_DIGITS10); // Same because is decimal.
  BOOST_CHECK_EQUAL(std::numeric_limits<e_float>::max_digits10, E_FLOAT_DIGITS10+1); // One noisy digit.

  BOOST_CHECK_EQUAL(std::numeric_limits<double>::epsilon(), static_cast<double>(2.2204460492503131e-016)  );
  //  Just to check it works for double. 

  //BOOST_CHECK_EQUAL(std::numeric_limits<e_float>::epsilon(), static_cast<e_float>(1e-49)  ); // E_FLOAT_DIGITS10 = 50
  // [1.00000000000000000000000000000000000000000000000000e-0000000000000000049 != 9.99999999999999936399465612583852251549992142478035e-0000000000000000050]

  BOOST_CHECK_EQUAL(std::numeric_limits<e_float>::epsilon(), static_cast<e_float>("1e-49")  ); // E_FLOAT_DIGITS10 = 50

  BOOST_CHECK_EQUAL(std::numeric_limits<e_float>::round_error(),  static_cast<e_float>(0.5));
  // TODO formulae for these...
  BOOST_CHECK_EQUAL(std::numeric_limits<e_float>::min_exponent, -9223372036854775795);
  BOOST_CHECK_EQUAL(std::numeric_limits<e_float>::max_exponent, +9223372036854775795);
  BOOST_CHECK_EQUAL(std::numeric_limits<e_float>::min_exponent10, -3063937869882635616);
  BOOST_CHECK_EQUAL(std::numeric_limits<e_float>::max_exponent10, +3063937869882635616);

  BOOST_CHECK_EQUAL((std::numeric_limits<e_float>::min)(), e_float("1.0e-3063937869882635616"));
  BOOST_CHECK_EQUAL((std::numeric_limits<e_float>::max)(), e_float("1.0e+3063937869882635616"));

  // BOOST_CHECK_EQUAL((std::numeric_limits<e_float>::lowest)(), 0);
  // A finite value x such that there is no other finite value y where y < x.

  // Double versions for comparison
  BOOST_CHECK_EQUAL((std::numeric_limits<double>::lowest)(), -1.7976931348623157e+308);
  BOOST_CHECK_EQUAL((std::numeric_limits<double>::min)(), 2.2250738585072014e-308);
  BOOST_CHECK_EQUAL((std::numeric_limits<double>::denorm_min)(), 4.9406564584124654e-324);

  //BOOST_CHECK_EQUAL((std::numeric_limits<e_float>::denorm_min)(), 0); // TODO

 // BOOST_CHECK_EQUAL(std::numeric_limits<e_float>::quiet_NaN(),"NaN");
  //BOOST_CHECK_EQUAL(-std::numeric_limits<e_float>::quiet_NaN(),"NaN");

  //BOOST_CHECK_EQUAL(std::numeric_limits<e_float>::infinity(), "INF");
  //BOOST_CHECK_EQUAL(-std::numeric_limits<e_float>::infinity(), "INF");
  
} // BOOST_AUTO_TEST_CASE(e_float_test_numeric_limits)

BOOST_AUTO_TEST_CASE(e_float_test_constants)
{ // 
  BOOST_CHECK_EQUAL(ef::one(), e_float(1)); // Integer.
  BOOST_CHECK_EQUAL(ef::one_minus(), e_float(-1)); // Negative Integer.

  BOOST_CHECK_EQUAL(ef::half(), e_float(0.5)); // Exactly representable as double.
  BOOST_CHECK_EQUAL(ef::sixteenth(), e_float(0.0625)); // Exactly representable as double.

  //BOOST_CHECK_EQUAL(ef::tenth(), e_float(0.1)); // NOT exactly representable as double.
  //   naive_test.cpp(319): error in "e_float_test_constants": check ef::tenth() == e_float(0.1) failed [0.1 != 0.100000000000000005551115123125782702118158340454102]
  BOOST_CHECK_EQUAL(ef::tenth(), e_float("0.1")); // OK, exactly representable as e_float.

  double my_pi = 3.141592653589793238462643383279502884197169399375105820974944;
  cout <<"double pi = " << setprecision(std::numeric_limits<double>::max_digits10) << my_pi << endl; // 3.1415926535897931
  e_float pi_as_double("3.1415926535897931");
  cout << "pi_as_double = " <<  pi_as_double  << endl; // 3.1415926535897931

  BOOST_CHECK_NE(ef::pi(), e_float(my_pi)); // From pi with only double accuracy.
  // [ 3.141592653589793238462643383279502884197169399375106 != 
  //   3.141592653589793115997963468544185161590576171875 ]
  //       differ here  ^  as expected at 17th decimal place.
  // 1st is accurate, the 2nd is the expected truncated from double (in)accurate version.

  BOOST_CHECK_NE(ef::pi(), pi_as_double); 
  // [ 3.141592653589793238462643383279502884197169399375106
  //!= 3.1415926535897931]
  // Loss of accuracy at 17th reported correctly, unlike when explicit in BOOST_CHECK_EQUAL macro parameter.

  cout << "e_float(3.1459.....) " << e_float(3.141592653589793238462643383279502884197169399375105820974944) << endl;
  //  e_float(3.1459.....) differs at 17th!  3.141592653589793115997963468544185161590576171875

  // BOOST_CHECK_CLOSE_FRACTION(ef::pi(), pi_as_double, std::numeric_limits<e_float>::epsilon() ); // Fails as expected.
  BOOST_CHECK_CLOSE_FRACTION(ef::pi(), pi_as_double, std::numeric_limits<double>::epsilon() ); // OK with bigger double tolerance.

  //BOOST_CHECK_EQUAL(ef::pi(), e_float("3.141592653589793238462643383279502884197169399375105820974944")); // More than 50 == E_FLOAT_DIGITS10 fails as expected.
  BOOST_CHECK_CLOSE_FRACTION(ef::pi(), e_float("3.141592653589793238462643383279502884197169399375105820974944"), std::numeric_limits<e_float>::epsilon() ); // OK with e_float tolerance.

  //BOOST_CHECK_EQUAL(ef::pi(), e_float("3.141592653589793238462643383279502884197169399375106")); //
  // 3.141592653589793238462643383279502884197169399375106  !=
  // 3.141592653589793238462643383279502884197169399375106]
  // which is apparent nonsense, but is actually as expected?
   BOOST_CHECK_CLOSE_FRACTION(ef::pi(), e_float("3.141592653589793238462643383279502884197169399375106"), std::numeric_limits<e_float>::epsilon()); //


  BOOST_CHECK_EQUAL(ef::pi(), e_float("3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196")); // 


  //double ddd = 1/2;  // easy but BIG mistake  0!
  //double ddd = 1./2;  // 0.5 as expected.



} // BOOST_AUTO_TEST_CASE(e_float_test_constants)
//3.14159265358979323846264338327950288419716939937511
//3.14159265358979323846264338327950288419716939937511
//3.141592653589793238462643383279502884197169399375105820974944
//3.141592653589793115997963468544185161590576171875
//                 ^ differs from double at 17th digit.
