
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <algorithm>

#include <e_float/e_float.h>
#include <utility/util_lexical_cast.h>

namespace ef
{
  e_float fabs(const e_float&);
}

namespace local
{
  typedef enum enum_os_float_field_type
  {
    os_float_field_scientific,
    os_float_field_fixed,
    os_float_field_none
  }
  os_float_field_type;

  void wr_string_scientific(std::string& str,
                            const std::int64_t the_exp,
                            const std::size_t os_precision,
                            const bool my_showpoint,
                            const bool my_uppercase,
                            const bool trim_trailing_zeros = false);

  void wr_string_fixed(std::string& str,
                       const std::int64_t the_exp,
                       const std::size_t os_precision,
                       const bool my_showpoint,
                       const bool trim_trailing_zeros = false);

  void special_handle_string_not_finite(std::string& str,
                                        const e_float& f,
                                        const bool my_showpos,
                                        const bool my_uppercase);

  void special_extend_string_to_precision(std::string& str, const std::size_t os_precision);
}

std::ostream& operator<<(std::ostream& os, const e_float_base& f)
{
  std::string str;

  f.wr_string(str, os);

  return (os << str);
}

std::istream& operator>>(std::istream& is, e_float_base& f)
{
  std::string str;

  static_cast<void>(is >> str);

  static_cast<void>(f.rd_string(str.c_str()));

  return is;
}

e_float_base::e_float_base() { }

e_float_base::~e_float_base() { }

int e_float_base::compare(const e_float& v) const
{
  const std::int32_t this_compare_result = cmp(v);

  return static_cast<int>(this_compare_result);
}

const e_float& e_float_base::my_value_max() const
{
  static const std::string str_max =   std::string("9." + std::string(static_cast<std::size_t>(ef_max_digits10), static_cast<char>('9')))
                                     + std::string("e+" + Util::lexical_cast(std::numeric_limits<e_float>::max_exponent10));

  static const e_float val_max(str_max);

  return val_max;
}

const e_float& e_float_base::my_value_min() const
{
  static const e_float val_min("1.0e" + Util::lexical_cast(std::numeric_limits<e_float>::min_exponent10));

  return val_min;
}

e_float& e_float_base::add_signed_long_long(const signed long long n)
{
  if(n < static_cast<signed long long>(0))
  {
    negate();
    add_unsigned_long_long(static_cast<unsigned long long>(-n));
    negate();
  }
  else
  {
    add_unsigned_long_long(static_cast<unsigned long long>(n));
  }

  return static_cast<e_float&>(*this);
}

e_float& e_float_base::sub_signed_long_long(const signed long long n)
{
  return add_signed_long_long(static_cast<signed long long>(-n));
}

e_float& e_float_base::mul_signed_long_long(const signed long long n)
{
  const bool b_neg = (n < static_cast<signed long long>(0));

  mul_unsigned_long_long((!b_neg) ? static_cast<unsigned long long>(n) : static_cast<unsigned long long>(-n));

  if(b_neg)
  {
    negate();
  }

  // Check for overflow.
  if(ef::fabs(static_cast<e_float&>(*this)) > (std::numeric_limits<e_float>::max)())
  {
    *this = ((!isneg()) ?  std::numeric_limits<e_float>::infinity()
                        : -std::numeric_limits<e_float>::infinity());
  }

  return static_cast<e_float&>(*this);
}

e_float& e_float_base::div_signed_long_long(const signed long long n)
{
  const bool b_neg = (n < static_cast<signed long long>(0));

  div_unsigned_long_long((!b_neg) ? static_cast<unsigned long long>(n) : static_cast<unsigned long long>(-n));

  if(b_neg)
  {
    negate();
  }

  return static_cast<e_float&>(*this);
}

void e_float_base::wr_string(std::string& str, std::ostream& os) const
{
  // Assess the format flags.
  const std::ios::fmtflags my_flags = os.flags();

  // Obtain the showpos flag.
  const bool my_showpos   = ((my_flags & std::ios::showpos)   != static_cast<std::ios::fmtflags>(0U));
  const bool my_uppercase = ((my_flags & std::ios::uppercase) != static_cast<std::ios::fmtflags>(0U));

  // Use special handling for non-finite numbers (inf and nan).
  if(!isfinite()) { local::special_handle_string_not_finite(str, static_cast<const e_float&>(*this), my_showpos, my_uppercase); return; }

  // Get the base-10 exponent.
  std::int64_t the_exp = get_order_exact();

  // Get the output stream's precision and limit it to max_digits10.
  // Erroneous zero or negative precision (theoretically impossible)
  // will be set to ostream's default precision.
  static const std::stringstream str_default;
  static const std::streamsize   prec_default = str_default.precision();

  const std::size_t os_precision  = ((os.precision() <= static_cast<std::streamsize>(0)) ? static_cast<std::size_t>(prec_default) : static_cast<std::size_t>(os.precision()));

  // Determine the kind of output format requested (scientific, fixed, none).
  local::os_float_field_type my_float_field;

  if     ((my_flags & std::ios::scientific) != static_cast<std::ios::fmtflags>(0U)) { my_float_field = local::os_float_field_scientific; }
  else if((my_flags & std::ios::fixed)      != static_cast<std::ios::fmtflags>(0U)) { my_float_field = local::os_float_field_fixed; }
  else { my_float_field = local::os_float_field_none; }

  bool use_scientific = false;
  bool use_fixed      = false;

  if     (my_float_field == local::os_float_field_scientific) { use_scientific = true; }
  else if(my_float_field == local::os_float_field_fixed)      { use_fixed      = true; }
  else // os_float_field_none
  {
    // Set up the range for dynamic detection of scientific notation.
    // If the exponent is less than -4 or larger than a precision-dependent
    // positive bound, then scientific notation is used.
    static const std::int64_t neg_bound_for_scientific_neg_exp = static_cast<std::int64_t>(-4);
           const std::int64_t min_bound_for_scientific_pos_exp = (std::max)(static_cast<std::int64_t>(os_precision), static_cast<std::int64_t>(prec_default));
           const std::int64_t pos_bound_for_scientific_pos_exp = (std::min)(static_cast<std::int64_t>(std::numeric_limits<e_float>::digits10), min_bound_for_scientific_pos_exp);

    if(   (the_exp <  neg_bound_for_scientific_neg_exp)
       || (the_exp >= pos_bound_for_scientific_pos_exp)
      )
    {
      use_scientific = true;
    }
    else
    {
      use_fixed = true;
    }
  }

  // Ascertain the number of digits requested from e_float.
  std::size_t the_number_of_digits_i_want_from_e_float = static_cast<std::size_t>(0U);

  const std::size_t max10_plus_one = static_cast<std::size_t>(std::numeric_limits<e_float>::max_digits10 + 1);

  if(use_scientific)
  {
    // The float-field is scientific. The number of digits is given by
    // (1 + the ostream's precision), not to exceed (max_digits10 + 1).
    const std::size_t prec_plus_one  = static_cast<std::size_t>(1U + os_precision);
    the_number_of_digits_i_want_from_e_float = (std::min)(max10_plus_one, prec_plus_one);
  }
  else if(use_fixed)
  {
    // The float-field is scientific. The number of all-digits depends
    // on the form of the number.

    if(the_exp >= static_cast<std::int64_t>(0))
    {
      // If the number is larger than 1 in absolute value, then the number of
      // digits is given by the width of the integer part plus the ostream's
      // precision, not to exceed (max_digits10 + 1).
      const std::size_t exp_plus_one = static_cast<std::size_t>(the_exp + 1);
      const std::size_t exp_plus_one_plus_my_precision = static_cast<std::size_t>(exp_plus_one + os_precision);

      the_number_of_digits_i_want_from_e_float = (std::min)(exp_plus_one_plus_my_precision, max10_plus_one);
    }
    else
    {
      const std::int64_t exp_plus_one = static_cast<std::int64_t>(the_exp + 1);
      const std::int64_t exp_plus_one_plus_my_precision = static_cast<std::int64_t>(exp_plus_one + static_cast<std::int64_t>(os_precision));

      the_number_of_digits_i_want_from_e_float = (std::min)(static_cast<std::size_t>((std::max)(exp_plus_one_plus_my_precision, static_cast<std::int64_t>(0))), max10_plus_one);
    }
  }

  // If the float field is not set, reduce the number of digits requested
  // from e_float such that it neither exceeds the ostream's precision
  // nor e_float's max_digits10.
  if(my_float_field == local::os_float_field_none)
  {
    const std::size_t max_digits = (std::min)(os_precision, static_cast<std::size_t>(std::numeric_limits<e_float>::max_digits10));
    the_number_of_digits_i_want_from_e_float = (std::min)(the_number_of_digits_i_want_from_e_float, max_digits);
  }

  // Extract the rounded output string with the desired number of digits.
  get_output_string(str, the_exp, the_number_of_digits_i_want_from_e_float);

  // Obtain additional format information.
  const bool my_showpoint  = ((my_flags & std::ios::showpoint)  != static_cast<std::ios::fmtflags>(0U));

  // Write the output string in the desired format.
  if     (my_float_field == local::os_float_field_scientific) { local::wr_string_scientific(str, the_exp, os_precision, my_showpoint, my_uppercase); }
  else if(my_float_field == local::os_float_field_fixed)      { local::wr_string_fixed     (str, the_exp, os_precision, my_showpoint); }
  else // os_float_field_none
  {
    (use_scientific ? local::wr_string_scientific(str, the_exp, os_precision, my_showpoint, my_uppercase, true)
                    : local::wr_string_fixed     (str, the_exp, os_precision, my_showpoint, true));
  }

  // Append the sign.
  if     (isneg())    { str.insert(static_cast<std::size_t>(0U), "-"); }
  else if(my_showpos) { str.insert(static_cast<std::size_t>(0U), "+"); }

  // Handle std::setw(...), std::setfill(...), std::left, std::right, std::internal.
  const std::size_t my_width = ((os.width() >= static_cast<std::streamsize>(0)) ? static_cast<std::size_t>(os.width())
                                                                                : static_cast<std::size_t>(0U));

  if(my_width > str.length())
  {
    // Get the number of fill characters.
    const std::size_t n_fill = static_cast<std::size_t>(my_width - str.length());

    // Left-justify is the exception, std::right and std::internal justify right.
    const bool my_left = ((my_flags & std::ios::left)  != static_cast<std::ios::fmtflags>(0U));

    // Justify left or right and insert the fill characters.
    str.insert((my_left ? str.cend() : str.cbegin()), n_fill, os.fill());
  }
}

void local::special_handle_string_not_finite(std::string& str,
                                             const e_float& f,
                                             const bool my_showpos,
                                             const bool my_uppercase)
{
  // Handle INF and NaN.
  if(f.isinf())
  {
    if(my_uppercase)
    {
      str = ((!f.isneg()) ? (my_showpos ? std::string("+INF") : std::string("INF")) : std::string("-INF"));
    }
    else
    {
      str = ((!f.isneg()) ? (my_showpos ? std::string("+inf") : std::string("inf")) : std::string("-inf"));
    }
  }
  else
  {
    str = (my_uppercase ? std::string("NAN") : std::string("nan"));
  }
}

void local::wr_string_scientific(std::string& str,
                                 const std::int64_t the_exp,
                                 const std::size_t os_precision,
                                 const bool my_showpoint,
                                 const bool my_uppercase,
                                 const bool trim_trailing_zeros)
{
  if(os_precision > static_cast<std::size_t>(str.length() - 1U))
  {
    // Zero-extend the string to the given precision if necessary.
    const std::size_t n_pad = static_cast<std::size_t>(os_precision - (str.length() - 1U));

    str.insert(str.cend(), n_pad, static_cast<char>('0'));
  }

  // Insert the decimal point.
  str.insert(static_cast<std::size_t>(1U), ".");

  // Trim the trailing zeros, where the trim-characteristics depend on the showpoint flag.
  if(trim_trailing_zeros)
  {
    const std::string::const_reverse_iterator rit_non_zero =
      std::find_if(str.crbegin(),
                    str.crend(),
                    [](const char& c) -> bool
                    {
                      return (c != static_cast<char>('0'));
                    });

    if(rit_non_zero != str.rbegin())
    {
      const std::ptrdiff_t ofs =   static_cast<std::ptrdiff_t>(str.length())
                                  - static_cast<std::ptrdiff_t>(rit_non_zero - str.crbegin());

      str.erase(str.cbegin() + ofs, str.cend());
    }
  }

  // Perform the final manipulations on the digits of the string.
  if(my_showpoint)
  {
    if(trim_trailing_zeros) { local::special_extend_string_to_precision(str, os_precision); }
  }
  else
  {
    // Remove the trailing decimal point if necessary.
    if(*(str.cend() - 1U) == static_cast<char>('.'))
    {
      str.erase(str.cend() - 1U, str.cend());
    }
  }

  // Append the exponent in uppercase or lower case, including its sign.
  const bool          b_exp_is_neg = (the_exp < static_cast<std::int64_t>(0));
  const std::uint64_t u_exp        = static_cast<std::uint64_t>(!b_exp_is_neg ? the_exp : static_cast<std::int64_t>(-the_exp));

  str += (my_uppercase ? "E" : "e");
  str += (b_exp_is_neg ? "-" : "+");

  std::string str_exp = Util::lexical_cast(static_cast<std::int64_t>(u_exp));

  // Format the exponent string to have a width that is an even multiple of three.
  const std::size_t str_exp_len      = str_exp.length();
  const std::size_t str_exp_len_mod3 = static_cast<std::size_t>(str_exp_len % 3U);
  const std::size_t str_exp_len_pad  = ((str_exp_len_mod3 != static_cast<std::size_t>(0U)) ? static_cast<std::size_t>(3U - (str_exp_len % 3U))
                                                                                            : static_cast<std::size_t>(0U));

  str += std::string(str_exp_len_pad, static_cast<char>('0'));
  str += str_exp;
}

void local::wr_string_fixed(std::string& str,
                            const std::int64_t the_exp,
                            const std::size_t os_precision,
                            const bool my_showpoint,
                            const bool trim_trailing_zeros)
{
  const std::size_t input_str_len = str.length();

  if(the_exp < static_cast<std::int64_t>(0))
  {
    // The number is less than one in magnitude. Insert the decimal
    // point using "0." as well as the needed number of leading zeros.
    const std::size_t minus_exp_minus_one = static_cast<std::size_t>(-the_exp - 1);
    const std::string str_zero_insert((std::min)(minus_exp_minus_one, os_precision), static_cast<char>('0'));

    const std::int64_t n_pad = static_cast<std::int64_t>(static_cast<std::int64_t>(os_precision) - static_cast<std::int64_t>(str.length() + str_zero_insert.length()));

    str.insert(0U, "0." + str_zero_insert);

    // Zero-extend the string to the given precision if necessary.
    if(n_pad > static_cast<std::int64_t>(0))
    {
      str.insert(str.cend(), static_cast<std::size_t>(n_pad), static_cast<char>('0'));
    }
  }
  else
  {
    // Insert the decimal point.
    const std::size_t my_exp_plus_one = static_cast<std::size_t>(the_exp + 1);

    // The number string is not large enough to hold the integer part of the number.
    // Zero extend the integer part of the string.
    if(input_str_len < my_exp_plus_one)
    {
      str.insert(str.cend(), static_cast<std::size_t>(my_exp_plus_one- str.length()), static_cast<char>('0'));
    }

    str.insert(my_exp_plus_one, ".");

    // Zero-extend the string to the given precision if necessary.
    const std::int64_t n_pad = static_cast<std::int64_t>(os_precision) - static_cast<std::int64_t>(static_cast<std::int64_t>(str.length() - 1U) - (the_exp + 1));

    if(n_pad > static_cast<std::int64_t>(0))
    {
      str.insert(str.cend(), static_cast<std::size_t>(n_pad), static_cast<char>('0'));
    }
  }

  // Trim the trailing zeros, where the trim-characteristics depend on the showpoint flag.
  if(trim_trailing_zeros)
  {
    const std::string::const_reverse_iterator rit_non_zero =
      std::find_if(str.crbegin(),
                    str.crend(),
                    [](const char& c) -> bool
                    {
                      return (c != static_cast<char>('0'));
                    });

    if(rit_non_zero != str.rbegin())
    {
      const std::ptrdiff_t ofs =   static_cast<std::ptrdiff_t>(str.length())
                                  - std::distance<std::string::const_reverse_iterator>(str.crbegin(), rit_non_zero);

      str.erase(str.cbegin() + ofs, str.cend());
    }
  }

  // Perform the final manipulations on the digits of the string.
  if(my_showpoint)
  {
    if(trim_trailing_zeros)
    {
      local::special_extend_string_to_precision(str, os_precision);
    }
  }
  else
  {
    // Remove the trailing decimal point if necessary.
    if(*(str.cend() - 1U) == static_cast<char>('.'))
    {
      str.erase(str.cend() - 1U, str.cend());
    }
  }
}

void local::special_extend_string_to_precision(std::string& str, const std::size_t os_precision)
{
  // This is the special case of showpoint in combination with
  // a non-fixed, non-scientific representation. The string has
  // to be zero extended such that the total width of its entire
  // non-zero part exactly equals the precision.

  // Check if the number is less than 1.
  if(   (str.at(static_cast<std::size_t>(0U)) == static_cast<char>('0'))
      && (str.at(static_cast<std::size_t>(1U)) == static_cast<char>('.'))
    )
  {
    if(str.length() == static_cast<std::size_t>(2U))
    {
      // This string represents zero and needs zero extension.
      str.insert(str.cend(), os_precision, static_cast<char>('0'));
    }
    else
    {
      // This is a non-zero decimal less than 1 that needs zero extension.
      const std::string::const_iterator it_non_zero =
        std::find_if(str.cbegin() + 2U,
                      str.cend(),
                      [](const char& c) -> bool
                      {
                        return (c != static_cast<char>('0'));
                      });

      const std::size_t len_non_zero_part = static_cast<std::size_t>(str.cend() - it_non_zero);

      const std::size_t u_pad = static_cast<std::size_t>(os_precision - len_non_zero_part);

      str.insert(str.cend(), u_pad, static_cast<char>('0'));
    }
  }
  else
  {
    // This is a number greater than or equal to 1 that needs zero extension.
    const std::size_t u_pad = static_cast<std::size_t>(os_precision - static_cast<std::size_t>(str.length() - static_cast<std::size_t>(1U)));

    str.insert(str.cend(), u_pad, static_cast<char>('0'));
  }
}

e_float e_float_base::my_own_ldexp        (const e_float&, int)                 { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_frexp        (const e_float&, int*)                { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_fmod         (const e_float&, const e_float&)      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_cbrt         (const e_float&)                      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_rootn        (const e_float&, const std::uint32_t) { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_exp          (const e_float&)                      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_log          (const e_float&)                      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_sin          (const e_float&)                      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_cos          (const e_float&)                      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_tan          (const e_float&)                      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_asin         (const e_float&)                      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_acos         (const e_float&)                      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_atan         (const e_float&)                      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_sinh         (const e_float&)                      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_cosh         (const e_float&)                      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_tanh         (const e_float&)                      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_asinh        (const e_float&)                      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_acosh        (const e_float&)                      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_atanh        (const e_float&)                      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_gamma        (const e_float&)                      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_riemann_zeta (const e_float&)                      { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_cyl_bessel_jn(const std::int32_t, const e_float&)  { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_own_cyl_bessel_yn(const std::int32_t, const e_float&)  { return std::numeric_limits<e_float>::quiet_NaN(); }
