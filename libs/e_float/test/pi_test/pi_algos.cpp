
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include <e_float/e_float_functions.h>
#include <../test/pi_test/pi_algos.h>
#include <utility/util_timer.h>

// *****************************************************************************
// Function    : const e_float& calculate_pi(const bool b_trace)
//
// Description : Compute pi using the quadratically convergent Gauss AGM,
//               in particular the Schoenhage variant. For a description
//               of the algorithm see the book "Pi Unleashed", algorithm 16.149,
//               page 236.
//               If the input b_trace = true, then the calculation progress
//               will be output to cout.
//
//               Book references:
//               http://www.jjj.de/pibook/pibook.html
//               http://www.springer.com/gp/book/9783642567353
// 
// *****************************************************************************
const e_float& calculate_pi(const bool b_trace)
{
  using ef::fabs;
  using ef::frexp;
  using ef::sqrt;

  static bool is_init = false;

  static e_float val_pi;

  if(!is_init)
  {
    is_init = true;

    if(b_trace) { std::cout << "Calculating pi with Gaus AGM (Schoenhage variant).\n"; }

    e_float a (1U);
    e_float bB("0.5");
    e_float s (bB);
    e_float t ("0.375");

    // This loop is designed for a maximum of several million
    // decimal digits of pi. The index k should reach no higher
    // than about 25 or 30. After about 20 iterations, the precision
    // is about one million decimal digits.

    constexpr std::int32_t required_precision_half =
        static_cast<std::int32_t>(std::numeric_limits<e_float>::digits10 + 1)
      / static_cast<std::int32_t>(2);

    for(unsigned k = 0U; k < 64U; ++k)
    {
      a      += sqrt(bB);
      a      /= 2;
      val_pi  = a;
      val_pi *= a;
      bB      = val_pi;
      bB     -= t;
      bB     *= 2;

      e_float iterate_term(bB);

      iterate_term -= val_pi;
      iterate_term *= (1ULL << (k + 1U));

      s += iterate_term;

      // Test the number of precise digits from this iteration.
      // If it is there are enough precise digits, then the calculation
      // is finished.

      double       dd;
      std::int64_t e10;

      iterate_term.extract_parts(dd, e10);

      static_cast<void>(dd);

      const std::int64_t approximate_digits10_of_iteration_term = (std::max)(std::int64_t(0), std::int64_t(-e10));

      if(b_trace)
      {
        std::cout << "Approximate decimal digits of this iteration : "
                  << std::right
                  << std::setw(12)
                  << approximate_digits10_of_iteration_term
                  << '\n';
      }

      // Estimate the approximate decimal digits of this iteration term.
      // If we have attained about half of the total desired digits
      // with this iteration term, then the calculation is finished
      // because the change from the next iteration will be
      // insignificantly small.

      if((std::uint64_t) approximate_digits10_of_iteration_term > required_precision_half)
      {
        break;
      }

      t   = val_pi;
      t  += bB;
      t  /= 4;
    }

    if(b_trace) { std::cout << "Iteration loop done, compute inverse" << '\n'; }

    val_pi += bB;
    val_pi /= s;

    if(b_trace) { std::cout << "Pi calculation done" << '\n'; }
  }

  return val_pi;
}

// *****************************************************************************
// Function    : const e_float& calculate_pi_borwein_cubic(const bool b_trace)
// 
// Description : Compute pi using a cubically convergent iteration scheme.
//               See the book "Pi Unleashed", algorithm 16.151, page 237,
//               with slight corrections to the term r_(k+1)^2, which should be
//               multiplied by a_k.
//               If the input b_trace = true, then the calculation progress
//               will be output to cout.
// 
// *****************************************************************************
const e_float& calculate_pi_borwein_cubic(const bool b_trace)
{
  static bool is_init = false;

  static e_float val_pi(1U);

  if(!is_init)
  {
    is_init = true;

    if(b_trace) { std::cout << "Calculating pi with Borwein cubic.\n"; }

    val_pi.div_unsigned_long_long(3U);

    e_float sk((ef::sqrt(e_float(3U)) - ef::one()).div_unsigned_long_long(2U));

    std::uint64_t three_pow_k = 1;

    // Determine the requested precision of the upcoming iteration in units of digits10.
    constexpr std::int32_t required_precision_third =
        static_cast<std::int32_t>((std::numeric_limits<e_float>::digits10 * 2) + 3)
      / static_cast<std::int32_t>(6);

    for(std::int32_t k = static_cast<std::int32_t>(1); k < static_cast<std::int32_t>(40); ++k)
    {
      const e_float rk(((ef::one() + ef::cbrt(ef::one() - ((sk * sk) * sk)).mul_unsigned_long_long(2U)).calculate_inv()).mul_unsigned_long_long(3U));

      sk = (rk - ef::one()).div_unsigned_long_long(2U);

      const e_float rk_squared(rk * rk);

      const e_float previous_ak(val_pi);

      val_pi = (val_pi * rk_squared) - (rk_squared - ef::one()).mul_unsigned_long_long(three_pow_k);

      double       dd;
      std::int64_t e10;

      sk.extract_parts(dd, e10);

      static_cast<void>(dd);

      const std::int64_t approximate_digits10_of_iteration_term = (std::max)(std::int64_t(0), std::int64_t(-e10));

      if(b_trace)
      {
        std::cout << "Approximate decimal digits of this iteration : "
                  << std::right
                  << std::setw(12)
                  << approximate_digits10_of_iteration_term
                  << '\n';
      }

      // Test the significant digits of the last iteration change.
      // If there are enough significant digits, then the calculation
      // is finished.
      if(approximate_digits10_of_iteration_term >= required_precision_third)
      {
        break;
      }

      three_pow_k *= 3U;
    }

    if(b_trace) { std::cout << "Iteration loop done, compute inverse" << '\n'; }

    (void) val_pi.calculate_inv();

    if(b_trace) { std::cout << "Pi calculation done" << '\n'; }
  }

  return val_pi;
}

// *****************************************************************************
// Function    : const e_float& calculate_pi_borwein_quartic(const bool b_trace)
// 
// Description : Compute pi using a cubically convergent iteration scheme.
//               See the book "Pi Unleashed", algorithm 16.152, page 237.
//               If the input b_trace = true, then the calculation progress
//               will be output to cout.
// 
// *****************************************************************************
const e_float& calculate_pi_borwein_quartic(const bool b_trace)
{
  static bool is_init = false;

  static e_float val_pi(2U);

  if(!is_init)
  {
    is_init = true;

    if(b_trace) { std::cout << "Calculating pi with Borwein quartic.\n"; }

    // Temporarily use val_pi to store sqrt(2).
    val_pi.calculate_sqrt();

    e_float yk(val_pi - ef::one());
    val_pi = e_float(e_float(6U) - (val_pi * 4));

    std::uint64_t two_pow_2k_plus_3 = 8U;

    // Determine the requested precision of the upcoming iteration in units of digits10.
    constexpr std::int32_t required_precision_quarter =
        static_cast<std::int32_t>(std::numeric_limits<e_float>::digits10 + 2)
      / static_cast<std::int32_t>(4);

    for(std::int32_t k = static_cast<std::int32_t>(1); k < static_cast<std::int32_t>(24); ++k)
    {
      // Compute yk^4.
      const e_float yk_pow_four(ef::pow(yk, 4));

      // Compute 1 / [(1 - yk^4)^(1/4)].
      {
        const e_float one_minus_yk_pow_four_4th_root_inverse = ef::rootn_inverse(ef::one() - yk_pow_four, 4);

        yk =   (one_minus_yk_pow_four_4th_root_inverse - ef::one())
             / (one_minus_yk_pow_four_4th_root_inverse + ef::one());
      }

      double       dd;
      std::int64_t e10;

      yk.extract_parts(dd, e10);

      static_cast<void>(dd);

      const std::int64_t approximate_digits10_of_iteration_term = (std::max)(std::int64_t(0), std::int64_t(-e10));

      if(b_trace)
      {
        std::cout << "Approximate decimal digits of this iteration : "
                  << std::right
                  << std::setw(12)
                  << approximate_digits10_of_iteration_term
                  << '\n';
      }

      e_float one_plus_yk_squared(ef::one() + yk);

      one_plus_yk_squared *= one_plus_yk_squared;

      val_pi =   (val_pi * (one_plus_yk_squared * one_plus_yk_squared))
               - (yk * (one_plus_yk_squared - yk)).mul_unsigned_long_long(two_pow_2k_plus_3);

      // Test the significant digits of the last iteration change.
      // If there are enough significant digits, then the calculation
      // is finished.
      if(approximate_digits10_of_iteration_term >= required_precision_quarter)
      {
        break;
      }

      two_pow_2k_plus_3 *= 4U;
    }

    if(b_trace) { std::cout << "Iteration loop done, compute inverse" << '\n'; }

    (void) val_pi.calculate_inv();

    if(b_trace) { std::cout << "Pi calculation done" << '\n'; }
  }

  return val_pi;
}

// *****************************************************************************
// Function    : const e_float& calculate_pi_borwein_quintic(const bool b_trace)
// 
// Description : Compute pi using a quintically convergent iteration scheme.
//               See the book "Pi Unleashed", algorithm 16.153, page 237.
//               If the input b_trace = true, then the calculation progress
//               will be output to cout.
// 
// *****************************************************************************
const e_float& calculate_pi_borwein_quintic(const bool b_trace)
{
  static bool is_init = false;

  static e_float val_pi("0.5");

  if(!is_init)
  {
    is_init = true;

    if(b_trace) { std::cout << "Calculating pi with Borwein quintic.\n"; }

    std::uint64_t five_pow_k = 1U;

    const e_float local_five(5U);

    e_float sk((ef::sqrt(local_five) - ef::two()) * 5U);

    // Determine the requested precision of the upcoming iteration in units of digits10.
    constexpr std::int32_t required_precision_fifth =
        static_cast<std::int32_t>((std::numeric_limits<e_float>::digits10 * 2) + 5)
      / static_cast<std::int32_t>(10);

    for(std::int32_t k = static_cast<std::int32_t>(1); k < static_cast<std::int32_t>(24); ++k)
    {
      const e_float x          = (local_five / sk) - ef::one();
      const e_float x_squared  = x * x;
      const e_float y          = x_squared - (x * 2) + e_float(8U);
      const e_float one_over_z = ef::rootn_inverse((x * (y + ef::sqrt((y * y) - (x_squared * (x * 4))))) / 2U, 5);

      const e_float term = ((ef::one() / one_over_z) + (x * one_over_z) + ef::one());

      const e_float sk_squared(sk * sk);

      const e_float previous_ak(val_pi);

      val_pi =
         (sk_squared * val_pi)
      - (  ((sk_squared - local_five) / 2)
         +  ef::sqrt(sk * (sk_squared - (sk * 2) + local_five))) * five_pow_k;

      double       dd;
      std::int64_t e10;

      (val_pi - previous_ak).extract_parts(dd, e10);

      static_cast<void>(dd);

      const std::int64_t approximate_digits10_of_iteration_term = (std::max)(std::int64_t(0), std::int64_t(-e10));

      if(b_trace)
      {
        std::cout << "Approximate decimal digits of this iteration : "
                  << std::right
                  << std::setw(12)
                  << approximate_digits10_of_iteration_term
                  << '\n';
      }

      // Test the significant digits of the last iteration change.
      // If there are enough significant digits, then the calculation
      // is finished.
      if(approximate_digits10_of_iteration_term >= required_precision_fifth)
      {
        break;
      }

      sk = e_float(25U) / (sk * (term * term));

      five_pow_k *= 5U;
    }

    if(b_trace) { std::cout << "Iteration loop done, compute inverse" << '\n'; }

    (void) val_pi.calculate_inv();

    if(b_trace) { std::cout << "Pi calculation done" << '\n'; }
  }

  return val_pi;
}

// *****************************************************************************
// Function    : const e_float& calculate_pi_borwein_nonic(const bool b_trace)
// 
// Description : Compute pi using a nonically convergent iteration scheme.
//               See the book "Pi Unleashed", algorithm 16.154, page 238.
//               If the input b_trace = true, then the calculation progress
//               will be output to cout.
// 
// *****************************************************************************
const e_float& calculate_pi_borwein_nonic(const bool b_trace)
{
  static bool is_init = false;

  static e_float val_pi(ef::one() / 3U);

  if(!is_init)
  {
    is_init = true;

    if(b_trace) { std::cout << "Calculating pi with Borwein nonic.\n"; }

    e_float nine_pow_k = ef::one() / 3;

    e_float rk((ef::sqrt(e_float(3U)) - ef::one()) / 2);
    e_float sk(ef::cbrt(ef::one() - ef::pow(rk, 3)));

    // Determine the requested precision of the upcoming iteration in units of digits10.
    constexpr std::int32_t required_precision_ninth =
        static_cast<std::int32_t>((std::numeric_limits<e_float>::digits10 * 2) + 9)
      / static_cast<std::int32_t>(18);

    for(std::int32_t k = static_cast<std::int32_t>(1); k < static_cast<std::int32_t>(16); ++k)
    {
      const e_float t(ef::one() + (rk * 2));
      const e_float u(ef::cbrt((ef::one() + rk + (rk * rk)) * (rk * 9)));
      const e_float v((t * t) + (t * u) + (u * u));
      const e_float m(((ef::one() + sk + (sk * sk)) * 27) / v);

      const e_float previous_ak(val_pi);

      val_pi = (m * val_pi) + ((ef::one() - m) * nine_pow_k);

      double       dd;
      std::int64_t e10;

      (val_pi - previous_ak).extract_parts(dd, e10);

      static_cast<void>(dd);

      const std::int64_t approximate_digits10_of_iteration_term =
        ((k < 2) ? std::int64_t(0)
                 : (std::max)(std::int64_t(0), std::int64_t(-e10)));

      if(b_trace)
      {
        std::cout << "Approximate decimal digits of this iteration : "
                  << std::right
                  << std::setw(12)
                  << approximate_digits10_of_iteration_term
                  << '\n';
      }

      // Test the significant digits of the last iteration change.
      // If there are enough significant digits, then the calculation
      // is finished.
      if(approximate_digits10_of_iteration_term >= required_precision_ninth)
      {
        break;
      }

      sk = ef::pow(ef::one() - rk, 3) / ((t + (u * 2)) * v);
      rk = ef::cbrt(ef::one() - ef::pow(sk, 3));

      nine_pow_k *= 9;
    }

    if(b_trace) { std::cout << "Iteration loop done, compute inverse" << '\n'; }

    (void) val_pi.calculate_inv();

    if(b_trace) { std::cout << "Pi calculation done" << '\n'; }
  }

  return val_pi;
}

// *****************************************************************************
// Function    : const e_float& calculate_pi_borwein_hexadecimalic(const bool b_trace)
// 
// Description : Compute pi using a hexadecimalically convergent iteration scheme.
//               See paragraph 10 in http://www.pi314.net/eng/borwein.php.
//               If the input b_trace = true, then the calculation progress
//               will be output to cout.
// 
// *****************************************************************************
const e_float& calculate_pi_borwein_hexadecimalic(const bool b_trace)
{
  static bool is_init = false;

  static e_float val_pi(ef::one() / 3U);

  if(!is_init)
  {
    is_init = true;

    if(b_trace) { std::cout << "Calculating pi with Borwein hexadecimalic.\n"; }

    e_float sixteen_pow_k = e_float(4U);

    e_float sk(ef::sqrt(ef::two()) - ef::one());
    e_float rk(ef::rootn(ef::one() - ef::pow(sk, 4), 4));

    // Determine the requested precision of the upcoming iteration in units of digits10.
    constexpr std::int32_t required_precision_sixteenth =
        static_cast<std::int32_t>(std::numeric_limits<e_float>::digits10 + 8)
      / static_cast<std::int32_t>(16);

    for(std::int32_t k = static_cast<std::int32_t>(1); k < static_cast<std::int32_t>(16); ++k)
    {
      const e_float t (ef::one() + rk);
      const e_float u (ef::rootn((ef::one() + (rk * rk)) * (rk * 8), 4));
      const e_float m1(ef::pow((ef::one() + sk) / t, 4));
      const e_float m2(ef::pow(ef::one() / t, 4));

      const e_float previous_ak(val_pi);

      val_pi = ((m1 * val_pi) * 16) + (((ef::one() - (m2 * 12) - (m1 * 4)) * sixteen_pow_k) / 3);

      double       dd;
      std::int64_t e10;

      (val_pi - previous_ak).extract_parts(dd, e10);

      static_cast<void>(dd);

      const std::int64_t approximate_digits10_of_iteration_term = (std::max)(std::int64_t(0), std::int64_t(-e10));

      if(b_trace)
      {
        std::cout << "Approximate decimal digits of this iteration : "
                  << std::right
                  << std::setw(12)
                  << approximate_digits10_of_iteration_term
                  << '\n';
      }

      // Test the significant digits of the last iteration change.
      // If there are enough significant digits, then the calculation
      // is finished.
      if(approximate_digits10_of_iteration_term >= required_precision_sixteenth)
      {
        break;
      }

      sk = ef::pow(ef::one() - rk, 4) / (ef::pow(t + u, 2) * ((t * t) + (u * u)));
      rk = ef::rootn(ef::one() - ef::pow(sk, 4), 4);

      sixteen_pow_k *= 16;
    }

    if(b_trace) { std::cout << "Iteration loop done, compute inverse" << '\n'; }

    (void) val_pi.calculate_inv();

    if(b_trace) { std::cout << "Pi calculation done" << '\n'; }
  }

  return val_pi;
}

namespace
{
  template<typename float_type>
  std::ostream& report_pi_timing(std::ostream& os, const float elapsed, const std::string& str_name)
  {
    return os << "=================================================" << '\n'
              << "Computed "
              << static_cast<std::uint64_t>(std::numeric_limits<float_type>::digits10 - 1)
              << " digits of pi.\n"
              << str_name + "\n"
              << "Total computation time : "
              << std::fixed
              << std::setprecision(2)
              << elapsed
              << " seconds"
              << '\n'
              << "================================================="
              << '\n';
  }
}

bool print_pi(calculate_pi_pfn pfn, std::ostream& out_stream, const std::string& str_name)
{
  const Util::timer my_timer;

  std::cout << "start: " << str_name << std::endl;

  pfn(true);

  const float elapsed { float(my_timer.elapsed()) };

  std::cout << std::endl;

  report_pi_timing<e_float>(std::cout,  elapsed, str_name);
  report_pi_timing<e_float>(out_stream, elapsed, str_name);

  // Report that we are writing the output file.
  std::cout << std::endl;
  std::cout << "Writing the output file." << '\n';
  std::cout << std::endl;

  // Pipe value of pi into a stringstream object.
  std::stringstream ss;

  ss << std::setprecision(std::numeric_limits<e_float>::digits10)
     << pfn(false);

  // Extract the string value of pi.
  const std::string str_pi(ss.str());

  // Print pi using the following paramater-tunable format.

  // pi = 3.1415926535 8979323846 2643383279 5028841971 6939937510 : 50
  //        5820974944 5923078164 0628620899 8628034825 3421170679 : 100
  //        8214808651 3282306647 0938446095 5058223172 5359408128 : 150
  //        4811174502 8410270193 8521105559 6446229489 5493038196 : 200
  //        ...

  const char char_set_separator  [] = " ";
  const char char_group_separator[] = "\n";

  constexpr std::size_t digits_per_set   = 10U;
  constexpr std::size_t digits_per_line  = digits_per_set  * 10U;
  constexpr std::size_t digits_per_group = digits_per_line * 10U;

  const char line_end_delimiter_for_digits[] = ", // : ";

  // The digits after the decimal point are grouped
  // in sets of digits_per_set with digits_per_line
  // digits per line. The running-digit count is reported
  // at the end of each line.
  
  // The char_set_separator character string is inserted
  // between sets of digits. Between groups of lines,
  // we insert a char_group_separator character string
  // (which likely might be selected as a newline).

  // For a simple verification of 1,000,000 digits,
  // for example, go to Wolfram Alpha and ask:
  //   1000000th digit of Pi.
  // This prints out 50 digits of pi in the neighborhood
  // of a million digits, with the millionth digit in bold.

  std::string::size_type pos;

  if(   ((pos = str_pi.find(char('3'), 0U)) != std::string::npos)
     && ((pos = str_pi.find(char('.'), 1U)) != std::string::npos)
     && ((pos = str_pi.find(char('1'), 1U)) != std::string::npos))
  {
    ;
  }
  else
  {
    pos = 0U;
  }

  out_stream << "pi = " << str_pi.substr(0U, pos);

  const std::size_t digit_offset = pos;

  // Extract the digits after the decimal point in a loop.
  // Insert spaces, newlines and a running-digit count
  // in order to create a format for comfortable reading.

  bool all_output_streaming_is_finished = false;

  while(all_output_streaming_is_finished == false)
  {
    // Print a set of digits (i.e. having 10 digits per set).
    const std::string str_pi_substring(str_pi.substr(pos, digits_per_set));

    out_stream << str_pi_substring << char_set_separator;

    pos += (std::min)(std::string::size_type(digits_per_set),
                      str_pi_substring.length());

    const std::size_t number_of_digits(pos - digit_offset);

    // Check if all output streaming is finished.
    all_output_streaming_is_finished = (pos >= str_pi.length());

    if(all_output_streaming_is_finished)
    {
      // Write the final digit count.
      // Break from the printing loop.
      // Flush the output stream with std::endl.

      out_stream << line_end_delimiter_for_digits << number_of_digits << std::endl;
    }
    else
    {
      const bool this_line_is_finished =
        (std::size_t(number_of_digits % digits_per_line) == std::size_t(0U));

      if(this_line_is_finished)
      {
        // Print the running-digit count and start a new line.
        out_stream << line_end_delimiter_for_digits << number_of_digits << std::endl;

        const bool this_group_of_lines_is_finished =
          (std::size_t(number_of_digits % digits_per_group) == std::size_t(0U));

        if(this_group_of_lines_is_finished)
        {
          // Insert a character (which might be a blank line)
          // after a group of lines.
          out_stream << char_group_separator;
        }

        // Insert spaces at the start of the new line.
        out_stream << "       ";
      }
    }
  }

  const std::string str_pi_control_head("3.14159265358979323846264338327950");
  const std::string str_pi_control_tail(  "83996346460422090106105779458151");

  const bool result_head_is_ok = std::equal(str_pi.cbegin(),
                                            str_pi.cbegin() + std::string::difference_type(str_pi_control_head.length()),
                                            str_pi_control_head.cbegin());

  const bool result_tail_is_ok = std::equal(str_pi.cbegin() + std::string::difference_type(1000002UL - str_pi_control_tail.length()),
                                            str_pi.cbegin() + std::string::difference_type(1000002LL),
                                            str_pi_control_tail.cbegin());

  const bool result_is_ok = (result_head_is_ok && result_tail_is_ok);

  return result_is_ok;
}
