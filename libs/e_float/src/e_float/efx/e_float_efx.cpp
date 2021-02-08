
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

// *****************************************************************************
// Filename    : e_float_efx.cpp
// 
// Project     : Multiple precision mathematics
// 
// Date        : 28.02.2004
// 
// Description : Extended precision floating point data type, efx::e_float.
// 
// *****************************************************************************

#include <cmath>
#include <iomanip>

#include <boost/e_float/e_float_functions.hpp>
#include <boost/e_float/e_float_detail_karatsuba.hpp>
#include <boost/e_float/e_float_detail_fft.hpp>

#include "../../utility/util_lexical_cast.h"
#include "../../utility/util_numeric_cast.h"
#include "../../utility/util_noncopyable.h"

efx::e_float::e_float(const double mantissa,
                      const std::int64_t exponent) : my_data     (),
                                                     my_exp      (static_cast<std::int64_t>(0)),
                                                     my_neg      (false),
                                                     my_fpclass  (ef_finite),
                                                     my_prec_elem(ef_elem_number)
{
  // Create an e_float from mantissa and exponent.
  // This ctor does not maintain the full precision of double.

  const bool mantissa_is_iszero = (::fabs(mantissa) < ((std::numeric_limits<double>::min)() * (1.0 + std::numeric_limits<double>::epsilon())));

  if(mantissa_is_iszero)
  {
    operator=((exponent == static_cast<std::int64_t>(0)) ? ef::one() : ef::zero());
    return;
  }

  const bool b_neg = (mantissa < 0.0);

  double d = ((!b_neg) ? mantissa : -mantissa);
  std::int64_t  e = exponent;

  while(d > 10.0) { d /= 10.0; ++e; }
  while(d <  1.0) { d *= 10.0; --e; }

  std::int32_t shift = static_cast<std::int32_t>(e % static_cast<std::int32_t>(ef_elem_digits10));

  while(static_cast<std::int32_t>(shift-- % ef_elem_digits10) != static_cast<std::int32_t>(0))
  {
    d *= 10.0;
    --e;
  }

  my_exp = e;
  my_neg = b_neg;

  std::fill(my_data.begin(), my_data.end(), static_cast<array_type::value_type>(0));

  static const std::int32_t digit_ratio = static_cast<std::int32_t>(static_cast<std::int32_t>(std::numeric_limits<double>::digits10) / static_cast<std::int32_t>(ef_elem_digits10));
  static const std::int32_t digit_loops = static_cast<std::int32_t>(digit_ratio + static_cast<std::int32_t>(2));

  for(array_type::size_type i = static_cast<array_type::size_type>(0); i < static_cast<array_type::size_type>(digit_loops); i++)
  {
    std::uint32_t n = static_cast<std::uint32_t>(static_cast<std::uint64_t>(d));

    my_data[i]  = static_cast<array_type::value_type>(n);
    d          -= static_cast<double>(n);
    d          *= static_cast<double>(ef_elem_mask);
  }
}

efx::e_float::e_float(const char* const s) : my_data     (),
                                             my_exp      (static_cast<std::int64_t>(0)),
                                             my_neg      (false),
                                             my_fpclass  (ef_finite),
                                             my_prec_elem(ef_elem_number)
{
  if(!rd_string(s))
  {
    std::fill(my_data.begin(), my_data.end(), static_cast<array_type::value_type>(0U));

    my_exp     = static_cast<std::int64_t>(0);
    my_neg     = false;
    my_fpclass = ef_NaN;
  }
}

efx::e_float::e_float(const std::string& str) : my_data     (),
                                                my_exp      (static_cast<std::int64_t>(0)),
                                                my_neg      (false),
                                                my_fpclass  (ef_finite),
                                                my_prec_elem(ef_elem_number)
{
  if(!rd_string(str.c_str()))
  {
    std::fill(my_data.begin(), my_data.end(), static_cast<array_type::value_type>(0U));

    my_exp     = static_cast<std::int64_t>(0);
    my_neg     = false;
    my_fpclass = ef_NaN;
  }
}

void efx::e_float::from_long_double(const long double l)
{
  const bool b_neg = (l < static_cast<long double>(0.0L));

  if(!ef::isfinite(static_cast<double>(l)))
  {
    operator=(ef::isnan(static_cast<double>(l)) ? my_value_nan() : ((!b_neg) ? my_value_inf() : -my_value_inf()));

    return;
  }

  const long double my_ld = ((!b_neg) ? l : -l);

  if(my_ld < (std::numeric_limits<long double>::min)())
  {
    operator=(ef::zero());

    return;
  }

  const native_float_parts<long double> ld_parts(my_ld);

  // Create an e_float from the fractional part of the
  // mantissa expressed as an unsigned long long.
  from_unsigned_long_long(ld_parts.get_mantissa());

  // Scale the unsigned long long representation to the fractional
  // part of the long double and multiply with the base-2 exponent.
  const int p2 = ld_parts.get_exponent() - (std::numeric_limits<long double>::digits - 1);

  if(p2 != 0)
  {
    operator*=(ef::pow2(static_cast<std::int64_t>(p2)));
  }

  my_neg = b_neg;
}

std::uint32_t efx::e_float::mul_loop_uv(std::uint32_t* const u, const std::uint32_t* const v, const std::int32_t p)
{
  std::uint64_t carry = static_cast<std::uint64_t>(0U);

  for(std::int32_t j = static_cast<std::int32_t>(p - 1); j >= static_cast<std::int32_t>(0); j--)
  {
    std::uint64_t sum = carry;

    for(std::int32_t i = j; i >= static_cast<std::int32_t>(0); i--)
    {
      sum += static_cast<std::uint64_t>(u[j - i] * static_cast<std::uint64_t>(v[i]));
    }

    u[j]  = static_cast<std::uint32_t>(sum % static_cast<std::uint32_t>(ef_elem_mask));
    carry = static_cast<std::uint64_t>(sum / static_cast<std::uint32_t>(ef_elem_mask));
  }

  return static_cast<std::uint32_t>(carry);
}

void efx::e_float::mul_loop_fft(std::uint32_t* const u, const std::uint32_t* const v, const std::int32_t p)
{
  using ef::detail::fft::rfft_lanczos_template;

  // Determine the required FFT size,
  // where n_fft is constrained to be a power of two.
  std::uint32_t n_fft = 1U;

  for(unsigned i = 1U; i < 31U; ++i)
  {
    n_fft <<= 1U;

    // We now have the needed size (doubled).
    // The size is doubled in order to contain the multiplication result.
    // This is because we are performing (n * n -> 2n) multiplication.
    if(n_fft >= static_cast<std::uint32_t>(p * 2))
    {
      break;
    }
  }

  // Again, double the FFT size because only half-limbs
  // are used as points in the FFT arrays. Splitting
  // into half-limbs follows below. We use half-limbs
  // in order to reduce the point size of the FFTs
  // and thereby preserve precision to very large
  // array lengths.

  n_fft <<= 1U;

  // Allocate dynamic memory for the FFT result arrays.
  double* af = new double[n_fft];
  double* bf = new double[n_fft];

  for(std::uint32_t i = static_cast<std::uint32_t>(0U); i < static_cast<std::uint32_t>(p); ++i)
  {
    af[(i * 2U)]      = (u[i] / 10000U);
    af[(i * 2U) + 1U] = (u[i] % 10000U);

    bf[(i * 2U)]      = (v[i] / 10000U);
    bf[(i * 2U) + 1U] = (v[i] % 10000U);
  }

  std::fill(af + (p * 2), af + n_fft, 0.0);
  std::fill(bf + (p * 2), bf + n_fft, 0.0);

  // Perform forward FFTs on the data arrays a and b.
  switch(n_fft)
  {
    default:
    case   64U        : { rfft_lanczos_template<  64U        >::rfft(af); rfft_lanczos_template<  64U        >::rfft(bf); break; }
    case  128U        : { rfft_lanczos_template< 128U        >::rfft(af); rfft_lanczos_template< 128U        >::rfft(bf); break; }
    case  256U        : { rfft_lanczos_template< 256U        >::rfft(af); rfft_lanczos_template< 256U        >::rfft(bf); break; }
    case  512U        : { rfft_lanczos_template< 512U        >::rfft(af); rfft_lanczos_template< 512U        >::rfft(bf); break; }
    case 1024U        : { rfft_lanczos_template<1024U        >::rfft(af); rfft_lanczos_template<1024U        >::rfft(bf); break; }
    case 2048U        : { rfft_lanczos_template<2048U        >::rfft(af); rfft_lanczos_template<2048U        >::rfft(bf); break; }
    case 4096U        : { rfft_lanczos_template<4096U        >::rfft(af); rfft_lanczos_template<4096U        >::rfft(bf); break; }
    case (1ULL << 13U): { rfft_lanczos_template<(1ULL << 13U)>::rfft(af); rfft_lanczos_template<(1ULL << 13U)>::rfft(bf); break; }
    case (1ULL << 14U): { rfft_lanczos_template<(1ULL << 14U)>::rfft(af); rfft_lanczos_template<(1ULL << 14U)>::rfft(bf); break; }
    case (1ULL << 15U): { rfft_lanczos_template<(1ULL << 15U)>::rfft(af); rfft_lanczos_template<(1ULL << 15U)>::rfft(bf); break; }
    case (1ULL << 16U): { rfft_lanczos_template<(1ULL << 16U)>::rfft(af); rfft_lanczos_template<(1ULL << 16U)>::rfft(bf); break; }
    case (1ULL << 17U): { rfft_lanczos_template<(1ULL << 17U)>::rfft(af); rfft_lanczos_template<(1ULL << 17U)>::rfft(bf); break; }
    case (1ULL << 18U): { rfft_lanczos_template<(1ULL << 18U)>::rfft(af); rfft_lanczos_template<(1ULL << 18U)>::rfft(bf); break; }
    case (1ULL << 19U): { rfft_lanczos_template<(1ULL << 19U)>::rfft(af); rfft_lanczos_template<(1ULL << 19U)>::rfft(bf); break; }
    case (1ULL << 20U): { rfft_lanczos_template<(1ULL << 20U)>::rfft(af); rfft_lanczos_template<(1ULL << 20U)>::rfft(bf); break; }
    case (1ULL << 21U): { rfft_lanczos_template<(1ULL << 21U)>::rfft(af); rfft_lanczos_template<(1ULL << 21U)>::rfft(bf); break; }
    case (1ULL << 22U): { rfft_lanczos_template<(1ULL << 22U)>::rfft(af); rfft_lanczos_template<(1ULL << 22U)>::rfft(bf); break; }
    case (1ULL << 23U): { rfft_lanczos_template<(1ULL << 23U)>::rfft(af); rfft_lanczos_template<(1ULL << 23U)>::rfft(bf); break; }
    case (1ULL << 24U): { rfft_lanczos_template<(1ULL << 24U)>::rfft(af); rfft_lanczos_template<(1ULL << 24U)>::rfft(bf); break; }
    case (1ULL << 25U): { rfft_lanczos_template<(1ULL << 25U)>::rfft(af); rfft_lanczos_template<(1ULL << 25U)>::rfft(bf); break; }
    case (1ULL << 26U): { rfft_lanczos_template<(1ULL << 26U)>::rfft(af); rfft_lanczos_template<(1ULL << 26U)>::rfft(bf); break; }
    case (1ULL << 27U): { rfft_lanczos_template<(1ULL << 27U)>::rfft(af); rfft_lanczos_template<(1ULL << 27U)>::rfft(bf); break; }
  }

  // Perform the convolution of a and b in the transform space.
  // This does, in fact, execute the actual multiplication of (a * b).
  af[0U] *= bf[0U];
  af[1U] *= bf[1U];

  for(std::uint32_t j = static_cast<std::uint32_t>(2U); j < n_fft; j += 2U)
  {
    const double tmp_aj = af[j];

    af[j + 0U] = (tmp_aj * bf[j + 0U]) - (af[j + 1U] * bf[j + 1U]);
    af[j + 1U] = (tmp_aj * bf[j + 1U]) + (af[j + 1U] * bf[j + 0U]);
  }

  // Perform the reverse FFT on the result of the convolution.
  switch(n_fft)
  {
    default:
    case   64U        : { rfft_lanczos_template<  64U        , false, double>::rfft(af); break; }
    case  128U        : { rfft_lanczos_template< 128U        , false, double>::rfft(af); break; }
    case  256U        : { rfft_lanczos_template< 256U        , false, double>::rfft(af); break; }
    case  512U        : { rfft_lanczos_template< 512U        , false, double>::rfft(af); break; }
    case 1024U        : { rfft_lanczos_template<1024U        , false, double>::rfft(af); break; }
    case 2048U        : { rfft_lanczos_template<2048U        , false, double>::rfft(af); break; }
    case 4096U        : { rfft_lanczos_template<4096U        , false, double>::rfft(af); break; }
    case (1ULL << 13U): { rfft_lanczos_template<(1ULL << 13U), false, double>::rfft(af); break; }
    case (1ULL << 14U): { rfft_lanczos_template<(1ULL << 14U), false, double>::rfft(af); break; }
    case (1ULL << 15U): { rfft_lanczos_template<(1ULL << 15U), false, double>::rfft(af); break; }
    case (1ULL << 16U): { rfft_lanczos_template<(1ULL << 16U), false, double>::rfft(af); break; }
    case (1ULL << 17U): { rfft_lanczos_template<(1ULL << 17U), false, double>::rfft(af); break; }
    case (1ULL << 18U): { rfft_lanczos_template<(1ULL << 18U), false, double>::rfft(af); break; }
    case (1ULL << 19U): { rfft_lanczos_template<(1ULL << 19U), false, double>::rfft(af); break; }
    case (1ULL << 20U): { rfft_lanczos_template<(1ULL << 20U), false, double>::rfft(af); break; }
    case (1ULL << 21U): { rfft_lanczos_template<(1ULL << 21U), false, double>::rfft(af); break; }
    case (1ULL << 22U): { rfft_lanczos_template<(1ULL << 22U), false, double>::rfft(af); break; }
    case (1ULL << 23U): { rfft_lanczos_template<(1ULL << 23U), false, double>::rfft(af); break; }
    case (1ULL << 24U): { rfft_lanczos_template<(1ULL << 24U), false, double>::rfft(af); break; }
    case (1ULL << 25U): { rfft_lanczos_template<(1ULL << 25U), false, double>::rfft(af); break; }
    case (1ULL << 26U): { rfft_lanczos_template<(1ULL << 26U), false, double>::rfft(af); break; }
    case (1ULL << 27U): { rfft_lanczos_template<(1ULL << 27U), false, double>::rfft(af); break; }
  }

  // Release the carries and re-combine the low and high parts.
  // This sets the integral data elements in the big number
  // to the result of multiplication.
  std::uint64_t carry = static_cast<std::uint64_t>(0U);

  for(std::uint32_t j = static_cast<std::uint32_t>((p * 2) - 2); static_cast<std::int32_t>(j) >= static_cast<std::int32_t>(0); j -= 2U)
  {
          double        xaj = af[j] / (n_fft / 2);
    const std::uint64_t xlo = static_cast<std::uint64_t>(xaj + 0.5) + carry;
    carry                   = static_cast<std::uint64_t>(xlo / static_cast<std::uint32_t>(10000U));
    const std::uint32_t nlo = static_cast<std::uint32_t>(xlo - static_cast<std::uint64_t>(carry * static_cast<std::uint32_t>(10000U)));

                        xaj = ((j != static_cast<std::int32_t>(0)) ? (af[j - 1U] / (n_fft / 2)) : 0.0);
    const std::uint64_t xhi = static_cast<std::uint64_t>(xaj + 0.5) + carry;
    carry                   = static_cast<std::uint64_t>(xhi / static_cast<std::uint32_t>(10000U));
    const std::uint32_t nhi = static_cast<std::uint32_t>(xhi - static_cast<std::uint64_t>(carry * static_cast<std::uint32_t>(10000U)));

    u[(j / 2U)] = static_cast<std::uint32_t>(static_cast<std::uint32_t>(nhi * static_cast<std::uint32_t>(10000U)) + nlo);
  }

  // De-allocate the dynamic memory for the FFT result arrays.
  delete [] af;
  delete [] bf;
}

std::uint32_t efx::e_float::mul_loop_n(std::uint32_t* const u, std::uint32_t n, const std::int32_t p)
{
  std::uint64_t carry = static_cast<std::uint64_t>(0U);

  // Multiplication loop.
  for(std::int32_t j = static_cast<std::int32_t>(p - 1); j >= static_cast<std::int32_t>(0); j--)
  {
    const std::uint64_t t = static_cast<std::uint64_t>(carry + static_cast<std::uint64_t>(u[j] * static_cast<std::uint64_t>(n)));
    carry                 = static_cast<std::uint64_t>(t / static_cast<std::uint32_t>(ef_elem_mask));
    u[j]                  = static_cast<std::uint32_t>(t - static_cast<std::uint64_t>(static_cast<std::uint32_t>(ef_elem_mask) * static_cast<std::uint64_t>(carry)));
  }

  return static_cast<std::uint32_t>(carry);
}

std::uint32_t efx::e_float::div_loop_n(std::uint32_t* const u, std::uint32_t n, const std::int32_t p)
{
  std::uint64_t prev = static_cast<std::uint64_t>(0U);

  for(std::int32_t j = static_cast<std::int32_t>(0); j < p; j++)
  {
    const std::uint64_t t = static_cast<std::uint64_t>(u[j] + static_cast<std::uint64_t>(prev * static_cast<std::uint32_t>(ef_elem_mask)));
    u[j]                  = static_cast<std::uint32_t>(t / n);
    prev                  = static_cast<std::uint64_t>(t - static_cast<std::uint64_t>(n * static_cast<std::uint64_t>(u[j])));
  }

  return static_cast<std::uint32_t>(prev);
}

efx::e_float& efx::e_float::operator+=(const e_float& v)
{
  if(isnan())
  {
    return *this;
  }

  if(isinf())
  {
    if(v.isinf() && (isneg() != v.isneg()))
    {
      *this = std::numeric_limits<e_float>::quiet_NaN();
    }

    return *this;
  }

  if(iszero())
  {
    return operator=(v);
  }

  // Get the offset for the add/sub operation.
  static const std::int64_t max_delta_exp = static_cast<std::int64_t>((ef_elem_number - 1) * ef_elem_digits10);

  const std::int64_t ofs_exp = static_cast<std::int64_t>(my_exp - v.my_exp);

  // Check if the operation is out of range, requiring special handling.
  if(v.iszero() || (ofs_exp > max_delta_exp))
  {
    // Result is *this unchanged since v is negligible compared to *this.
    return *this;
  }
  else if(ofs_exp < -max_delta_exp)
  {
    // Result is *this = v since *this is negligible compared to v.
    return operator=(v);
  }

  // Do the add/sub operation.
  // TBD: Eliminate the temporary storage array n_data.

  array_type::iterator       p_u    =   my_data.begin();
  array_type::const_iterator p_v    = v.my_data.cbegin();
  bool                       b_copy = false;
  const std::int32_t         ofs    = static_cast<std::int32_t>(static_cast<std::int32_t>(ofs_exp) / ef_elem_digits10);
  array_type                 n_data;

  if(my_neg == v.my_neg)
  {
    // Add v to *this, where the data array of either *this or v
    // might have to be treated with a positive, negative or zero offset.
    // The result is stored in *this. The data are added one element
    // at a time, each element with carry.
    if(ofs >= static_cast<std::int32_t>(0))
    {
      std::copy(v.my_data.cbegin(),
                v.my_data.cend() - static_cast<std::ptrdiff_t>(ofs),
                n_data.begin() + static_cast<std::ptrdiff_t>(ofs));

      std::fill(n_data.begin(),
                n_data.begin() + static_cast<std::ptrdiff_t>(ofs),
                static_cast<array_type::value_type>(0));

      p_v = n_data.begin();
    }
    else
    {
      std::copy(my_data.cbegin(),
                my_data.cend()     - static_cast<std::ptrdiff_t>(-ofs),
                n_data.begin() + static_cast<std::ptrdiff_t>(-ofs));

      std::fill(n_data.begin(),
                n_data.begin() + static_cast<std::ptrdiff_t>(-ofs),
                static_cast<array_type::value_type>(0));

      p_u = n_data.begin();
      b_copy = true;
    }

    // Addition algorithm
    std::uint32_t carry = static_cast<std::uint32_t>(0U);

    for(std::int32_t j = static_cast<std::int32_t>(ef_elem_number - static_cast<std::int32_t>(1)); j >= static_cast<std::int32_t>(0); j--)
    {
      std::uint32_t t = static_cast<std::uint32_t>(static_cast<std::uint32_t>(p_u[j] + p_v[j]) + carry);
      carry           = t / static_cast<std::uint32_t>(ef_elem_mask);
      p_u[j]          = static_cast<std::uint32_t>(t - static_cast<std::uint32_t>(carry * static_cast<std::uint32_t>(ef_elem_mask)));
    }

    if(b_copy)
    {
      my_data = n_data;
      my_exp  = v.my_exp;
    }
    
    // There needs to be a carry into the element -1 of the array data
    if(carry != static_cast<std::uint32_t>(0U))
    {
      std::copy_backward(my_data.cbegin(),
                         my_data.cend() - static_cast<std::size_t>(1U),
                         my_data.end());

      my_data[0U] = carry;

      my_exp += static_cast<std::int64_t>(ef_elem_digits10);
    }
  }
  else
  {
    // Subtract v from *this, where the data array of either *this or v
    // might have to be treated with a positive, negative or zero offset.
    if(       (ofs >  static_cast<std::int32_t>(0))
       || (   (ofs == static_cast<std::int32_t>(0))
           && (cmp_data(v.my_data) > static_cast<std::int32_t>(0))))
    {
      // In this case, |u| > |v| and ofs is positive.
      // Copy the data of v, shifted down to a lower value
      // into the data array m_n. Set the operand pointer p_v
      // to point to the copied, shifted data m_n.
      std::copy(v.my_data.cbegin(),
                v.my_data.cend()  - static_cast<std::ptrdiff_t>(ofs),
                n_data.begin() + static_cast<std::ptrdiff_t>(ofs));

      std::fill(n_data.begin(),
                n_data.begin() + static_cast<std::ptrdiff_t>(ofs),
                static_cast<array_type::value_type>(0));

      p_v = n_data.begin();
    }
    else
    {
      if(ofs != static_cast<std::int32_t>(0))
      {
        // In this case, |u| < |v| and ofs is negative.
        // Shift the data of u down to a lower value.
        std::copy_backward(my_data.cbegin(),
                           my_data.cend() - static_cast<std::ptrdiff_t>(-ofs),
                           my_data.end());

        std::fill(my_data.begin(),
                  my_data.begin() + static_cast<std::ptrdiff_t>(-ofs),
                  static_cast<array_type::value_type>(0));
      }

      // Copy the data of v into the data array n_data.
      // Set the u-pointer p_u to point to m_n and the
      // operand pointer p_v to point to the shifted
      // data m_data.
      n_data = v.my_data;
      p_u    = n_data.begin();
      p_v    = my_data.begin();
      b_copy = true;
    }

    std::int32_t j;

    // Subtraction algorithm
    std::int32_t borrow = static_cast<std::int32_t>(0);

    for(j = static_cast<std::int32_t>(ef_elem_number - static_cast<std::int32_t>(1)); j >= static_cast<std::int32_t>(0); j--)
    {
      std::int32_t t = static_cast<std::int32_t>(static_cast<std::int32_t>(  static_cast<std::int32_t>(p_u[j])
                                                      - static_cast<std::int32_t>(p_v[j])) - borrow);

      // Underflow? Borrow?
      if(t < static_cast<std::int32_t>(0))
      {
        // Yes, underflow and borrow
        t     += static_cast<std::int32_t>(ef_elem_mask);
        borrow = static_cast<std::int32_t>(1);
      }
      else
      {
        borrow = static_cast<std::int32_t>(0);
      }

      p_u[j] = static_cast<std::uint32_t>(static_cast<std::uint32_t>(t) % static_cast<std::uint32_t>(ef_elem_mask));
    }

    if(b_copy)
    {
      my_data = n_data;
      my_exp  = v.my_exp;
      my_neg  = v.my_neg;
    }

    // Is it necessary to justify the data?
    const array_type::const_iterator first_nonzero_elem =
      std::find_if(my_data.cbegin(),
                   my_data.cend(),
                   [](const std::uint32_t& d) -> bool
                   {
                     return (d != static_cast<std::uint32_t>(0U));
                   });

    if(first_nonzero_elem != my_data.cbegin())
    {
      if(first_nonzero_elem == my_data.cend())
      {
        // This result of the subtraction is exactly zero.
        // Reset the sign and the exponent.
        my_neg = false;
        my_exp = static_cast<std::int64_t>(0);
      }
      else
      {
        // Justify the data
        const std::ptrdiff_t sj =
          static_cast<std::ptrdiff_t>(first_nonzero_elem - my_data.cbegin());

        std::copy(my_data.cbegin() + static_cast<std::ptrdiff_t>(sj),
                  my_data.cend(),
                  my_data.begin());

        std::fill(my_data.end() - static_cast<std::ptrdiff_t>(sj),
                  my_data.end(),
                  static_cast<array_type::value_type>(0));

        my_exp -= static_cast<std::int64_t>(sj * static_cast<std::ptrdiff_t>(ef_elem_digits10));
      }
    }
  }

  // Check for underflow.
  if(iszero()) { return (*this = ef::zero()); }

  // Check for overflow.
  if(   (my_exp >= std::numeric_limits<e_float>::max_exponent10)
     && (ef::fabs(*this) > (std::numeric_limits<e_float>::max)())
    )
  {
    const bool b_result_is_neg = my_neg;

    *this = ((!b_result_is_neg) ?  std::numeric_limits<e_float>::infinity()
                                : -std::numeric_limits<e_float>::infinity());
  }

  return *this;
}

efx::e_float& efx::e_float::operator-=(const e_float& v)
{
  // Use *this - v = -(-*this + v).
  return (negate().operator+=(v)).negate();
}

efx::e_float& efx::e_float::operator*=(const e_float& v)
{
  // Evaluate the sign of the result.
  const bool b_result_is_neg = (my_neg != v.my_neg);

  // Artificially set the sign of the result to be positive.
  my_neg = false;

  // Handle special cases like zero, inf and NaN.
  const bool b_u_is_inf  =   isinf();
  const bool b_v_is_inf  = v.isinf();
  const bool b_u_is_zero =   iszero();
  const bool b_v_is_zero = v.iszero();

  if(   (isnan()    || v.isnan())
     || (b_u_is_inf && b_v_is_zero)
     || (b_v_is_inf && b_u_is_zero)
    )
  {
    return (*this = std::numeric_limits<e_float>::quiet_NaN());
  }

  if(b_u_is_inf || b_v_is_inf)
  {
    *this = ((!b_result_is_neg) ?  std::numeric_limits<e_float>::infinity()
                                : -std::numeric_limits<e_float>::infinity());

    return *this;
  }

  if(b_u_is_zero || b_v_is_zero)
  {
    return (*this = ef::zero());
  }

  // Check for overflow or underflow.
  const bool u_exp_is_neg = (  my_exp < static_cast<std::int64_t>(0));
  const bool v_exp_is_neg = (v.my_exp < static_cast<std::int64_t>(0));

  if(u_exp_is_neg == v_exp_is_neg)
  {
    // Get the unsigned base-10 exponents of *this and v and...
    const std::int64_t u_exp = ((!u_exp_is_neg) ?   my_exp : static_cast<std::int64_t>(  -my_exp));
    const std::int64_t v_exp = ((!v_exp_is_neg) ? v.my_exp : static_cast<std::int64_t>(-v.my_exp));

    // Check the range of the upcoming multiplication.
    const bool b_result_is_out_of_range = (v_exp >= static_cast<std::int64_t>(ef_max_exp10 - u_exp));

    if(b_result_is_out_of_range)
    {
      if(u_exp_is_neg)
      {
        *this = ef::zero();
      }
      else
      {
        *this = ((!b_result_is_neg) ?  std::numeric_limits<e_float>::infinity()
                                    : -std::numeric_limits<e_float>::infinity());
      }

      return *this;
    }
  }

  // Set the exponent of the result.
  my_exp += v.my_exp;

  const std::int32_t prec_for_multiply     = (std::min)(my_prec_elem, v.my_prec_elem);
  const std::int32_t digits10_for_multiply = static_cast<std::int32_t>(prec_for_multiply * ef_elem_digits10);

  // Note: Karatsuba multiplication is not used for intermediate digit counts.
  // Consider implementing Karatsuba multiplication for intermediate digit counts.

  if(digits10_for_multiply < static_cast<std::int32_t>(5000))
  {
    // Use school multiplication.
    const std::uint32_t carry = mul_loop_uv(my_data.data(), v.my_data.data(), prec_for_multiply);

    // Handle a potential carry.
    if(carry != static_cast<std::uint32_t>(0U))
    {
      my_exp += static_cast<std::int64_t>(ef_elem_digits10);

      // Shift the result of the multiplication one element to the right.
      std::copy_backward(my_data.cbegin(),
                         my_data.cbegin() + static_cast<std::ptrdiff_t>(my_prec_elem - static_cast<std::int32_t>(1)),
                         my_data.begin()  + static_cast<std::ptrdiff_t>(my_prec_elem));

      my_data.front() = static_cast<std::uint32_t>(carry);
    }
  }
  else
  {
    // Use FFT-based multiplication.
    mul_loop_fft(my_data.data(), v.my_data.data(), static_cast<std::int32_t>(prec_for_multiply));

    // Adjust the exponent because of the internal scaling of the FFT multiplication.
    my_exp += static_cast<std::int64_t>(ef_elem_digits10);

    // Check for justify
    if(my_data.front() == static_cast<std::uint32_t>(0U))
    {
      // Justify the data.
      std::copy(my_data.cbegin() + 1,
                my_data.cbegin() + (std::min)(ef_elem_number, (std::int32_t) (my_prec_elem + 1)),
                my_data.begin());

      my_data.back() = static_cast<std::uint32_t>(0U);

      // Adjust the exponent accordingly.
      my_exp -= static_cast<std::int64_t>(ef_elem_digits10);
    }
  }

  // Set the sign of the result.
  my_neg = b_result_is_neg;

  return *this;
}

efx::e_float& efx::e_float::operator/=(const e_float& v)
{
  const bool u_and_v_are_finite_and_identical =
    (   isfinite()
     && (my_fpclass == v.my_fpclass)
     && (my_exp     == v.my_exp)
     && (cmp_data(v.my_data) == static_cast<std::int32_t>(0)));

  if(u_and_v_are_finite_and_identical)
  {
    *this = ef::one();

    if(my_neg != v.my_neg)
    {
      negate();
    }

    return *this;
  }
  else
  {
    operator*=(e_float(v).calculate_inv());
  }

  return *this;
}

efx::e_float& efx::e_float::add_unsigned_long_long(const unsigned long long n)
{
  // Non-optimized addition of unsigned long long.
  return operator+=(e_float(n));
}

efx::e_float& efx::e_float::sub_unsigned_long_long(const unsigned long long n)
{
  // Non-optimized subtraction of unsigned long long.
  return operator-=(e_float(n));
}

efx::e_float& efx::e_float::mul_unsigned_long_long(const unsigned long long n)
{
  // Multiply *this with a constant unsigned long long.

  // Evaluate the sign of the result.
  const bool b_neg = my_neg;

  // Artificially set the sign of the result to be positive.
  my_neg = false;

  // Handle special cases like zero, inf and NaN.
  const bool b_u_is_inf  = isinf();
  const bool b_n_is_zero = (n == static_cast<std::int32_t>(0));

  if(isnan() || (b_u_is_inf && b_n_is_zero))
  {
    return (*this = std::numeric_limits<e_float>::quiet_NaN());
  }

  if(b_u_is_inf)
  {
    *this = ((!b_neg) ?  std::numeric_limits<e_float>::infinity()
                      : -std::numeric_limits<e_float>::infinity());

    return *this;
  }

  if(iszero() || b_n_is_zero)
  {
    // Multiplication by zero.
    return (*this = ef::zero());
  }

  if(n >= static_cast<unsigned long long>(ef_elem_mask))
  {
    my_neg = b_neg;

    return operator*=(e_float(n));
  }

  if(n == static_cast<unsigned long long>(1U))
  {
    my_neg = b_neg;

    return *this;
  }

  // Set up the multiplication loop.
  const std::uint32_t nn    = static_cast<std::uint32_t>(n);
  const std::uint32_t carry = mul_loop_n(my_data.data(), nn, my_prec_elem);

  // Handle the carry and adjust the exponent.
  if(carry != static_cast<std::uint32_t>(0U))
  {
    my_exp += static_cast<std::int64_t>(ef_elem_digits10);

    // Shift the result of the multiplication one element to the right.
    std::copy_backward(my_data.cbegin(),
                       my_data.cbegin() + static_cast<std::ptrdiff_t>(my_prec_elem - 1),
                       my_data.begin()  + static_cast<std::ptrdiff_t>(my_prec_elem));

    my_data.front() = static_cast<std::uint32_t>(carry);
  }

  // Set the sign.
  my_neg = b_neg;

  return *this;
}

efx::e_float& efx::e_float::div_unsigned_long_long(const unsigned long long n)
{
  // Divide *this by a constant unsigned long long.

  // Evaluate the sign of the result.
  const bool b_neg = my_neg;

  // Artificially set the sign of the result to be positive.
  my_neg = false;

  // Handle special cases like zero, inf and NaN.
  if(isnan())
  {
    return *this;
  }

  if(isinf())
  {
    *this = ((!b_neg) ?  std::numeric_limits<e_float>::infinity()
                      : -std::numeric_limits<e_float>::infinity());

    return *this;
  }

  if(n == static_cast<unsigned long long>(0U))
  {
    // Divide by 0.
    if(iszero())
    {
      return (*this = std::numeric_limits<e_float>::quiet_NaN());
    }
    else
    {
      *this = ((!isneg()) ?  std::numeric_limits<e_float>::infinity()
                          : -std::numeric_limits<e_float>::infinity());

      return *this;
    }
  }

  if(iszero())
  {
    return *this;
  }

  if(n >= static_cast<unsigned long long>(ef_elem_mask))
  {
    my_neg = b_neg;

    return operator/=(e_float(n));
  }

  const std::uint32_t nn = static_cast<std::uint32_t>(n);

  if(nn > static_cast<std::uint32_t>(1U))
  {
    // Do the division loop.
    const std::uint32_t prev = div_loop_n(my_data.data(), nn, my_prec_elem);

    // Determine if one leading zero is in the result data.
    if(my_data[0] == static_cast<std::uint32_t>(0U))
    {
      // Adjust the exponent
      my_exp -= static_cast<std::int64_t>(ef_elem_digits10);

      // Shift result of the division one element to the left.
      std::copy(my_data.cbegin() + static_cast<std::ptrdiff_t>(1),
                my_data.cbegin() + static_cast<std::ptrdiff_t>(my_prec_elem - 1),
                my_data.begin());

      const array_type::size_type ip = static_cast<array_type::size_type>(my_prec_elem - 1);

      my_data[ip] = static_cast<array_type::value_type>(static_cast<std::uint64_t>(prev * static_cast<std::uint64_t>(ef_elem_mask)) / nn);
    }
  }

  // Check for underflow.
  if(iszero())
  {
    return (*this = ef::zero());
  }

  // Set the sign of the result.
  my_neg = b_neg;

  return *this; 
}

efx::e_float& efx::e_float::calculate_inv()
{
  // Compute the inverse of *this.
  const bool b_neg = my_neg;

  my_neg = false;

  // Handle special cases like zero, inf and NaN.
  if(iszero())
  {
    *this = ((!b_neg) ? +std::numeric_limits<e_float>::infinity()
                      : -std::numeric_limits<e_float>::infinity());

    return *this;
  }

  if(isnan())
  {
    return *this;
  }

  if(isinf())
  {
    return (*this = ef::zero());
  }

  if(isone())
  {
    *this = ((!b_neg) ? ef::one() : -ef::one());

    return *this;
  }

  // Use the original value of *this for iteration below.
  e_float x(*this);

  // Generate the initial estimate using division.
  // Extract the mantissa and exponent for a "manual"
  // computation of the estimate.
  double       dd;
  std::int64_t ne;

  x.extract_parts(dd, ne);

  const std::int32_t original_prec_elem = my_prec_elem;

  // Do the inverse estimate using double precision estimates of mantissa and exponent.
  operator=(e_float(1.0 / dd, -ne));

  // Compute the inverse of *this. Quadratically convergent Newton-Raphson iteration
  // is used. During the iterative steps, the precision of the calculation is limited
  // to the minimum required in order to minimize the run-time.

  static const std::int32_t double_digits10_minus_a_few = static_cast<std::int32_t>(static_cast<std::int32_t>(std::numeric_limits<double>::digits10) - static_cast<std::int32_t>(3));

  for(std::int32_t digits = double_digits10_minus_a_few; digits <= static_cast<std::int32_t>(ef::tolerance()); digits *= static_cast<std::int32_t>(2))
  {
    // Adjust precision of the terms.
      precision(static_cast<std::int32_t>(digits * 2) + 10);
    x.precision(static_cast<std::int32_t>(digits * 2) + 10);

    // Next iteration.
    operator=(*this * (ef::two() - (*this * x)));
  }

  my_neg = b_neg;

  my_prec_elem = original_prec_elem;

  return *this;
}

efx::e_float& efx::e_float::calculate_sqrt()
{
  // Compute the square root of *this.

  if(isneg() || (!isfinite()))
  {
    return (*this = std::numeric_limits<e_float>::quiet_NaN());
  }

  if(iszero() || isone())
  {
    return *this;
  }

  // Use the original value of *this for iteration below.
  e_float x(*this);

  // Generate the initial estimate using division.
  // Extract the mantissa and exponent for a "manual"
  // computation of the estimate.
  double       dd;
  std::int64_t ne;

  extract_parts(dd, ne);

  // Force the exponent to be an even multiple of two.
  if((ne % static_cast<std::int64_t>(2)) != static_cast<std::int64_t>(0))
  {
    ++ne;
    dd /= 10.0;
  }

  using std::sqrt;

  // Setup the iteration.
  // Estimate the square root using simple manipulations.
  const double sqd = sqrt(dd);

  const std::int32_t original_prec_elem = my_prec_elem;

  *this = e_float(sqd, static_cast<std::int64_t>(ne / static_cast<std::int64_t>(2)));

  // Estimate 1.0 / (2.0 * x0) using simple manipulations.
  e_float vi(0.5 / sqd, static_cast<std::int64_t>(-ne / static_cast<std::int64_t>(2)));

  // Compute the square root of x. Coupled Newton iteration
  // as described in "Pi Unleashed" is used. During the
  // iterative steps, the precision of the calculation is
  // limited to the minimum required in order to minimize
  // the run-time.
  //
  // Book references:
  // http://www.jjj.de/pibook/pibook.html
  // http://www.amazon.com/exec/obidos/tg/detail/-/3540665722/qid=1035535482/sr=8-7/ref=sr_8_7/104-3357872-6059916?v=glance&n=507846

  static const std::int32_t double_digits10_minus_a_few = static_cast<std::int32_t>(static_cast<std::int32_t>(std::numeric_limits<double>::digits10) - static_cast<std::int32_t>(3));

  for(std::int32_t digits = double_digits10_minus_a_few; digits <= static_cast<std::int32_t>(ef::tolerance()); digits *= static_cast<std::int32_t>(2))
  {
    // Adjust precision of the terms.
    const std::int32_t new_prec = static_cast<std::int32_t>(digits * 2) + 10;

       precision(new_prec);
    vi.precision(new_prec);

    // Next iteration of vi
    vi += vi * (-((*this * vi) * static_cast<std::int32_t>(2)) + ef::one());

    // Next iteration of *this
    const e_float iteration_term(vi * (-((*this) * (*this)) + x));

    *this += iteration_term;

    const std::int64_t order_check = order() - iteration_term.order();

    if(   (digits      > static_cast<std::int32_t>(ef::tolerance() / 4))
       && (order_check > static_cast<std::int64_t>(ef::tolerance() / 2))
      )
    {
      break;
    }
  }

  my_prec_elem = original_prec_elem;

  return *this;
}

std::int32_t efx::e_float::cmp_data(const array_type& vd) const
{
  // Compare the data of *this with those of v.
  //         Return +1 for *this > v
  //                 0 for *this = v
  //                -1 for *this < v

  const std::pair<array_type::const_iterator,
                  array_type::const_iterator> mismatch_pair =
    std::mismatch(my_data.cbegin(), my_data.cend(), vd.cbegin());

  const bool is_equal = ((mismatch_pair.first == my_data.cend()) && (mismatch_pair.second == vd.cend()));

  if(is_equal)
  {
    return static_cast<std::int32_t>(0);
  }
  else
  {
    return ((*mismatch_pair.first > *mismatch_pair.second) ? static_cast<std::int32_t>(1) : static_cast<std::int32_t>(-1));
  }
}

std::int32_t efx::e_float::cmp(const e_float& v) const
{
  // Compare v with *this.
  //         Return +1 for *this > v
  //                 0 for *this = v
  //                -1 for *this < v

  // Handle all non-finite cases.
  if((!isfinite()) || (!v.isfinite()))
  {
    // NaN can never equal NaN. Return an implementation-dependent
    // signed result. Also note that comparison of NaN with NaN
    // using operators greater-than or less-than is undefined.
    if(isnan() || v.isnan())
    {
      return (isnan() ? static_cast<std::int32_t>(1) : static_cast<std::int32_t>(-1));
    }

    if(isinf() && v.isinf())
    {
      // Both *this and v are infinite. They are equal if they have the same sign.
      // Otherwise, *this is less than v if and only if *this is negative.
      return ((my_neg == v.my_neg)
               ? static_cast<std::int32_t>(0)
               : (my_neg ? static_cast<std::int32_t>(-1) : static_cast<std::int32_t>(1)));
    }

    if(isinf())
    {
      // *this is infinite, but v is finite.
      // So negative infinite *this is less than any finite v.
      // Whereas positive infinite *this is greater than any finite v.
      return (isneg() ? static_cast<std::int32_t>(-1) : static_cast<std::int32_t>(1));
    }
    else
    {
      // *this is finite, and v is infinite.
      // So any finite *this is greater than negative infinite v.
      // Whereas any finite *this is less than positive infinite v.
      return (v.my_neg ? static_cast<std::int32_t>(1) : static_cast<std::int32_t>(-1));
    }
  }

  // And now handle all *finite* cases.
  if(iszero())
  {
    // The value of *this is zero and v is either zero or non-zero.
    return (v.iszero() ? static_cast<std::int32_t>(0)
                       : (v.my_neg ? static_cast<std::int32_t>(1) : static_cast<std::int32_t>(-1)));
  }
  else if(v.iszero())
  {
    // The value of v is zero and *this is non-zero.
    return (my_neg ? static_cast<std::int32_t>(-1) : static_cast<std::int32_t>(1));
  }
  else
  {
    // Both *this and v are non-zero.

    if(my_neg != v.my_neg)
    {
      // The signs are different.
      return (my_neg ? static_cast<std::int32_t>(-1) : static_cast<std::int32_t>(1));
    }
    else if(my_exp != v.my_exp)
    {
      // The signs are the same and the exponents are different.
      const std::int32_t val_cmp_exp = ((my_exp < v.my_exp) ? static_cast<std::int32_t>(1) : static_cast<std::int32_t>(-1));

      return (my_neg ? val_cmp_exp : static_cast<std::int32_t>(-val_cmp_exp));
    }
    else
    {
      // The signs are the same and the exponents are the same.
      // Compare the data.
      const std::int32_t val_cmp_data = cmp_data(v.my_data);

      return ((!my_neg) ? val_cmp_data : static_cast<std::int32_t>(-val_cmp_data));
    }
  }
}

bool efx::e_float::iszero() const
{
  return ((my_fpclass == ef_finite) && (my_data[0U] == static_cast<std::uint32_t>(0U)));
}

bool efx::e_float::isone() const
{
  // Check if the value of *this is identically 1 or very close to 1.

  const bool not_negative_and_is_finite = ((!my_neg) && isfinite());

  if(not_negative_and_is_finite)
  {
    if((my_data[0U] == static_cast<std::uint32_t>(1U)) && (my_exp == static_cast<std::int64_t>(0)))
    {
      const array_type::const_iterator it_non_zero =
        std::find_if(my_data.cbegin(),
                     my_data.cend(),
                     [](const std::uint32_t& d) -> bool
                     {
                       return (d != static_cast<std::uint32_t>(0U));
                     });

      return (it_non_zero == my_data.cend());
    }
    else if((my_data[0U] == static_cast<std::uint32_t>(ef_elem_mask - 1)) && (my_exp == static_cast<std::int64_t>(-ef_elem_digits10)))
    {
      const array_type::const_iterator it_non_nine =
        std::find_if(my_data.cbegin(),
                     my_data.cend(),
                     [](const std::uint32_t& d) -> bool
                     {
                       return (d != static_cast<std::uint32_t>(e_float::ef_elem_mask - 1));
                     });

      return (it_non_nine == my_data.cend());
    }
  }

  return false;
}

bool efx::e_float::isint() const
{
  if(my_fpclass != ef_finite) { return false; }

  if(iszero())
  {
    return true;
  }

  if(my_exp < static_cast<std::int64_t>(0))
  {
    // Here, we have |*this| < 1, so *this can not be int.
    return false;
  }

  const array_type::size_type offset_decimal_part = static_cast<array_type::size_type>(my_exp / ef_elem_digits10) + 1U;

  if(offset_decimal_part >= static_cast<array_type::size_type>(ef_elem_number))
  {
    // The number is too large to resolve the integer part.
    // It considered to be a pure integer.
    return true;
  }

  array_type::const_iterator it_non_zero =
    std::find_if(my_data.cbegin() + static_cast<std::ptrdiff_t>(offset_decimal_part),
                 my_data.cend(),
                 [](const std::uint32_t& d) -> bool
                 {
                   return (d != static_cast<std::uint32_t>(0U));
                 });

  return (it_non_zero == my_data.cend());
}

void efx::e_float::extract_parts(double& mantissa, std::int64_t& exponent) const
{
  // Extract the approximate parts mantissa and base-10 exponent from the input e_float value x.

  // Extracts the mantissa and exponent.
  exponent = my_exp;

  std::uint32_t p10  = static_cast<std::uint32_t>(1U);
  std::uint32_t test = my_data[0U];

  for(;;)
  {
    test /= static_cast<std::uint32_t>(10U);

    if(test == static_cast<std::uint32_t>(0U))
    {
      break;
    }

    p10 *= static_cast<std::uint32_t>(10U);

    ++exponent;
  }

  mantissa =     static_cast<double>(my_data[0])
             +  (static_cast<double>(my_data[1]) / static_cast<double>(ef_elem_mask))
             + ((static_cast<double>(my_data[2]) / static_cast<double>(ef_elem_mask)) / static_cast<double>(ef_elem_mask));

  mantissa /= static_cast<double>(p10);

  if(my_neg)
  {
    mantissa = -mantissa;
  }
}

double efx::e_float::extract_double() const
{
  // Returns the double conversion of a e_float.

  // Check for non-normal e_float.
  if((!isfinite()))
  {
    if(isnan())
    {
      return std::numeric_limits<double>::quiet_NaN();
    }
    else
    {
      return ((!my_neg) ?  std::numeric_limits<double>::infinity()
                        : -std::numeric_limits<double>::infinity());
    }
  }

  const e_float xx(ef::fabs(*this));

  // Check for zero e_float.
  if(iszero() || (xx < ef::double_min()))
  {
    return 0.0;
  }

  // Check if e_float exceeds the maximum of double.
  if(xx > ef::double_max())
  {
    return ((!my_neg) ?  std::numeric_limits<double>::infinity()
                      : -std::numeric_limits<double>::infinity());
  }

  std::stringstream ss;

  ss << std::setprecision(static_cast<std::streamsize>(std::numeric_limits<double>::digits10 + (2 + 1)))
     << std::scientific
     << *this;

  double d;

  ss >> d;

  return d;
}

long double efx::e_float::extract_long_double() const
{
  // Returns the long double conversion of a e_float.

  // Check for non-normal e_float.
  if((!isfinite()))
  {
    if(isnan())
    {
      return std::numeric_limits<long double>::quiet_NaN();
    }
    else
    {
      return ((!my_neg) ?  std::numeric_limits<long double>::infinity()
                        : -std::numeric_limits<long double>::infinity());
    }
  }

  const e_float xx(ef::fabs(*this));

  // Check for zero e_float.
  if(iszero() || (xx < ef::long_double_min()))
  {
    return 0.0L;
  }

  // Check if e_float exceeds the maximum of double.
  if(xx > ef::long_double_max())
  {
    return ((!my_neg) ?  std::numeric_limits<long double>::infinity()
                      : -std::numeric_limits<long double>::infinity());
  }

  std::stringstream ss;

  ss << std::setprecision(static_cast<std::streamsize>(std::numeric_limits<long double>::digits10 + (2 + 1)))
     << std::scientific
     << *this;

  long double ld;

  ss >> ld;

  return ld;
}

signed long long efx::e_float::extract_signed_long_long() const
{
  // Extracts a signed long long from *this.
  // If (x > maximum of signed long long) or (x < minimum of signed long long),
  // then the maximum or minimum of signed long long is returned accordingly.

  if(my_exp < static_cast<std::int64_t>(0))
  {
    return static_cast<signed long long>(0);
  }

  const bool b_neg = isneg();

  unsigned long long val;

  if((!b_neg) && (*this > ef::signed_long_long_max()))
  {
    return (std::numeric_limits<signed long long>::max)();
  }
  else if(b_neg &&  (*this < ef::signed_long_long_min()))
  {
    return (std::numeric_limits<signed long long>::min)();
  }
  else
  {
    // Extract the data into an unsigned long long value.
    const e_float xn(ef::fabs(extract_integer_part()));

    val = static_cast<unsigned long long>(xn.my_data[0]);

    const std::int32_t imax = (std::min)(static_cast<std::int32_t>(static_cast<std::int32_t>(xn.my_exp) / ef_elem_digits10), static_cast<std::int32_t>(ef_elem_number - static_cast<std::int32_t>(1)));

    for(array_type::size_type i = static_cast<array_type::size_type>(1); i <= static_cast<array_type::size_type>(imax); ++i)
    {
      val *= static_cast<unsigned long long>(ef_elem_mask);
      val += static_cast<unsigned long long>(xn.my_data[i]);
    }
  }

  return ((!b_neg) ? static_cast<signed long long>(val) : static_cast<signed long long>(-static_cast<signed long long>(val)));
}

unsigned long long efx::e_float::extract_unsigned_long_long() const
{
  // Extracts an unsigned long long from *this.
  // If x exceeds the maximum of unsigned long long,
  // then the maximum of unsigned long long is returned.
  // If x is negative, then the unsigned long long cast of
  // the signed long long extracted value is returned.

  if(isneg())
  {
    return static_cast<unsigned long long>(extract_signed_long_long());
  }

  if(my_exp < static_cast<std::int64_t>(0))
  {
    return static_cast<unsigned long long>(0U);
  }

  const e_float xn(extract_integer_part());

  unsigned long long val;

  if(xn > ef::unsigned_long_long_max())
  {
    return (std::numeric_limits<unsigned long long>::max)();
  }
  else
  {
    // Extract the data into an unsigned long long value.
    val = static_cast<unsigned long long>(xn.my_data[0]);

    const std::int32_t imax =
      (std::min)(static_cast<std::int32_t>(static_cast<std::int32_t>(xn.my_exp) / ef_elem_digits10), static_cast<std::int32_t>(ef_elem_number - static_cast<std::int32_t>(1)));

    for(array_type::size_type i = static_cast<array_type::size_type>(1); i <= static_cast<array_type::size_type>(imax); ++i)
    {
      val *= static_cast<unsigned long long>(ef_elem_mask);
      val += static_cast<unsigned long long>(xn.my_data[i]);
    }
  }

  return val;
}

efx::e_float efx::e_float::extract_integer_part() const
{
  // Compute the signed integer part of x.

  if(!isfinite())
  {
    return *this;
  }

  if(my_exp < static_cast<std::int64_t>(0))
  {
    // The absolute value of the number is smaller than 1.
    // Thus the integer part is zero.
    return ef::zero();
  }
  else if(my_exp >= static_cast<std::int64_t>(std::numeric_limits<e_float>::digits10 - 1))
  {
    // The number is too large to resolve the integer part.
    // Thus it is already a pure integer part.
    return *this;
  }

  // Make a local copy.
  e_float x = *this;

  // Clear out the decimal portion
  const std::ptrdiff_t first_clear = (static_cast<std::ptrdiff_t>(x.my_exp) / static_cast<std::ptrdiff_t>(ef_elem_digits10)) + 1;
  const std::ptrdiff_t last_clear  =  static_cast<std::ptrdiff_t>(ef_elem_number);

  std::fill(x.my_data.begin() + first_clear,
            x.my_data.begin() + last_clear,
            static_cast<array_type::value_type>(0U));

  return x;
}

efx::e_float efx::e_float::extract_decimal_part() const
{
  // Compute the signed decimal part of x.

  if(!isfinite())
  {
    return *this;
  }

  if(iszero())
  {
    return ef::zero();
  }

  if(my_exp < static_cast<std::int64_t>(0))
  {
    // The absolute value of the number is smaller than 1.
    // Thus it is already a pure decimal part.
    return *this;
  }
  else if(my_exp >= static_cast<std::int64_t>(std::numeric_limits<e_float>::digits10 - 1))
  {
    // The number is too large to have a decimal part.
    // Thus the decimal part is zero.
    return ef::zero();
  }

  e_float x = *this;

  const std::ptrdiff_t first_copy = static_cast<std::ptrdiff_t>((static_cast<std::ptrdiff_t>(x.my_exp) / static_cast<std::ptrdiff_t>(ef_elem_digits10)) + 1);
  const std::ptrdiff_t last_copy  = static_cast<std::ptrdiff_t>(ef_elem_number);

  std::copy(x.my_data.cbegin() + first_copy,
            x.my_data.cbegin() + last_copy,
            x.my_data.begin());

  const std::ptrdiff_t first_clear = static_cast<std::ptrdiff_t>(ef_elem_number - first_copy);
  const std::ptrdiff_t last_clear  = static_cast<std::ptrdiff_t>(ef_elem_number);

  std::fill(x.my_data.begin() + first_clear,
            x.my_data.begin() + last_clear,
            static_cast<array_type::value_type>(0U));

  // Is it necessary to justify the data?
  const array_type::const_iterator first_nonzero_elem =
    std::find_if(x.my_data.cbegin(),
                 x.my_data.cend(),
                 [](const std::uint32_t& d) -> bool
                 {
                   return (d != static_cast<std::uint32_t>(0U));
                 });

  std::ptrdiff_t sj = static_cast<std::ptrdiff_t>(0);

  if(first_nonzero_elem != x.my_data.cbegin())
  {
    if(first_nonzero_elem == x.my_data.cend())
    {
      // The decimal part is exactly zero.
      // Reset the sign and the exponent.
      x.my_neg = false;
      x.my_exp = static_cast<std::int64_t>(0);
    }
    else
    {
      // Justify the data
      sj = static_cast<std::ptrdiff_t>(first_nonzero_elem - x.my_data.cbegin());

      std::copy(x.my_data.cbegin() + sj,
                x.my_data.cend(),
                x.my_data.begin());

      std::fill(x.my_data.begin() + static_cast<std::ptrdiff_t>(ef_elem_number - sj),
                x.my_data.end(),
                static_cast<array_type::value_type>(0U));
    }
  }

  x.my_exp -= static_cast<std::int64_t>((first_copy + sj) * static_cast<std::ptrdiff_t>(ef_elem_digits10));

  return x;
}

const efx::e_float& efx::e_float::my_value_nan() const
{
  static const e_float val_qnan(ef_NaN);

  return val_qnan;
}

const efx::e_float& efx::e_float::my_value_inf() const
{
  static const e_float val_inf(ef_inf);

  return val_inf;
}

std::int64_t efx::e_float::get_order_fast() const
{
  if((!isfinite()) || (my_data[0] == static_cast<std::uint32_t>(0U)))
  {
    return static_cast<std::int64_t>(0);
  }
  else
  {
    using std::log;

    const double dx = log10(static_cast<double>(my_data[0])) + (std::numeric_limits<double>::epsilon() * 0.9);

    return static_cast<std::int64_t>(my_exp + static_cast<std::int64_t>(static_cast<std::int32_t>(dx)));
  }
}

void efx::e_float::get_output_string(std::string& str, std::int64_t& the_exp, const std::size_t number_of_digits) const
{
  // Determine the number of elements needed to provide the requested digits from e_float.
  const std::size_t number_of_elements = (std::min)(static_cast<std::size_t>((number_of_digits / static_cast<std::size_t>(ef_elem_digits10)) + 2U),
                                                    static_cast<std::size_t>(ef_elem_number));

  // Extract the remaining digits from e_float after the decimal point.
  str = Util::lexical_cast(my_data[0]);

  // Extract all of the digits from e_float, beginning with the first data element.
  for(std::size_t i = static_cast<std::size_t>(1U); i < number_of_elements; i++)
  {
    std::stringstream ss;

    ss << std::setw(static_cast<std::streamsize>(ef_elem_digits10))
       << std::setfill(static_cast<char>('0'))
       << my_data[(typename array_type::size_type) i];

    str += ss.str();
  }

  // Cut the output to the size of the precision.
  if(str.length() > number_of_digits)
  {
    // Get the digit after the last needed digit for rounding
    const std::uint32_t round = static_cast<std::uint32_t>(static_cast<std::uint32_t>(str.at(number_of_digits)) - static_cast<std::uint32_t>('0'));

    // Truncate the string
    str = str.substr(static_cast<std::size_t>(0U), number_of_digits);

    if(round >= static_cast<std::uint32_t>(5U))
    {
      std::size_t ix = static_cast<std::size_t>(str.length() - 1U);

      // Every trailing 9 must be rounded up
      while(ix && (static_cast<std::int32_t>(str.at(ix)) - static_cast<std::int32_t>('0') == static_cast<std::int32_t>(9)))
      {
        str.at(ix) = static_cast<char>('0');
        --ix;
      }

      if(!ix)
      {
        // There were nothing but trailing nines.
        if(static_cast<std::int32_t>(static_cast<std::int32_t>(str.at(ix)) - static_cast<std::int32_t>(0x30)) == static_cast<std::int32_t>(9))
        {
          // Increment up to the next order and adjust exponent.
          str.at(ix) = static_cast<char>('1');
          ++the_exp;
        }
        else
        {
          // Round up this digit.
          ++str.at(ix);
        }
      }
      else
      {
        // Round up the last digit.
        ++str[ix];
      }
    }
  }
}

bool efx::e_float::rd_string(const char* const s)
{
  std::string str(s);

  // Get a possible exponent and remove it.
  my_exp = static_cast<std::int64_t>(0);

  std::size_t pos;

  if(   ((pos = str.find('e')) != std::string::npos)
     || ((pos = str.find('E')) != std::string::npos)
    )
  {
    // Remove the exponent part from the string.
    my_exp = Util::numeric_cast<std::int64_t>(static_cast<const char* const>(str.c_str() + (pos + 1U)));

    str = str.substr(static_cast<std::size_t>(0U), pos);
  }

  // Get a possible +/- sign and remove it.
  my_neg = false;

  if((pos = str.find(static_cast<char>('-'))) != std::string::npos)
  {
    my_neg = true;

    str.erase(pos, static_cast<std::size_t>(1U));
  }

  if((pos = str.find(static_cast<char>('+'))) != std::string::npos)
  {
    str.erase(pos, static_cast<std::size_t>(1U));
  }

  // Remove leading zeros for all input types.
  const std::string::const_iterator fwd_it_leading_zero =
    std::find_if(str.cbegin(),
                 str.cend(),
                 [](const char& c) -> bool
                 {
                   return (c != static_cast<char>('0'));
                 });

  if(fwd_it_leading_zero != str.cbegin())
  {
    if(fwd_it_leading_zero == str.cend())
    {
      // The string contains nothing but leading zeros.
      // This string represents zero.
      operator=(ef::zero());

      return true;
    }
    else
    {
      str.erase(str.cbegin(), fwd_it_leading_zero);
    }
  }

  // Put the input string into the standard e_float input form
  // aaa.bbbbE+/-n, where aa has 1...ef_elem_digits10, bbbb has an
  // even multiple of ef_elem_digits10 which are possibly zero padded
  // on the right-end, and n is a signed 32-bit integer which is an
  // even multiple of ef_elem_digits10.

  // Find a possible decimal point.
  pos = str.find(static_cast<char>('.'));

  if(pos != std::string::npos)
  {
    // Remove all trailing insignificant zeros.
    const std::string::const_reverse_iterator rit_non_zero =
      std::find_if(str.crbegin(),
                   str.crend(),
                   [](const char& c) -> bool
                   {
                     return (c != static_cast<char>('0'));
                   });

    if(rit_non_zero != str.crbegin())
    {
      const std::string::difference_type ofs =   static_cast<std::string::difference_type>(str.length())
                                               - std::distance<std::string::const_reverse_iterator>(str.crbegin(), rit_non_zero);

      str.erase(str.cbegin() + ofs, str.cend());
    }

    // Check if the input is identically zero.
    if(str == std::string("."))
    {
      operator=(ef::zero());
      return true;
    }

    // Remove leading significant zeros just after the decimal point
    // and adjust the exponent accordingly.
    // Note that the while-loop operates only on strings of the form ".000abcd..."
    // and peels away the zeros just after the decimal point.
    if(str.at(static_cast<std::size_t>(0U)) == static_cast<char>('.'))
    {
      const std::string::const_iterator it_non_zero =
        std::find_if(str.cbegin() + 1U,
                     str.cend(),
                     [](const char& c) -> bool
                     {
                       return (c != static_cast<char>('0'));
                     });

      std::size_t delta_exp = static_cast<std::size_t>(0U);

      if(str.at(static_cast<std::size_t>(1U)) == static_cast<char>('0'))
      {
        delta_exp = static_cast<std::size_t>(it_non_zero - (str.cbegin() + 1U));
      }

      // Bring one single digit into the mantissa and adjust exponent accordingly.
      str.erase(str.cbegin(), it_non_zero);

      str.insert(static_cast<std::size_t>(1U), ".");

      my_exp -= static_cast<std::int64_t>(delta_exp + 1U);
    }
  }
  else
  {
    // Input string has no decimal point: Append decimal point.
    str.append(".");
  }

  // Shift the decimal point such that the exponent is an even multiple of ef_elem_digits10.
        std::ptrdiff_t n_shift   = static_cast<std::ptrdiff_t>(0);
  const std::ptrdiff_t n_exp_rem = static_cast<std::ptrdiff_t>(my_exp % static_cast<std::int64_t>(ef_elem_digits10));

  if((my_exp % static_cast<std::int64_t>(ef_elem_digits10)) != static_cast<std::int64_t>(0))
  {
    n_shift = ((my_exp < static_cast<std::int64_t>(0))
                ? static_cast<std::ptrdiff_t>(n_exp_rem + static_cast<std::ptrdiff_t>(ef_elem_digits10))
                : static_cast<std::ptrdiff_t>(n_exp_rem));
  }

  // Make sure that there are enough digits for the decimal point shift.
  pos = str.find(static_cast<char>('.'));

  std::ptrdiff_t pos_plus_one = static_cast<std::ptrdiff_t>(pos + 1);

  if((static_cast<std::ptrdiff_t>(str.length()) - pos_plus_one) < n_shift)
  {
    const std::ptrdiff_t sz = static_cast<std::ptrdiff_t>(n_shift - (static_cast<std::ptrdiff_t>(str.length()) - pos_plus_one));

    str.append(std::string(static_cast<std::string::size_type>(sz), static_cast<char>('0')));
  }

  // Do the decimal point shift.
  if(n_shift != static_cast<std::ptrdiff_t>(0))
  {
    str.insert(static_cast<std::string::size_type>(pos_plus_one + n_shift), ".");

    str.erase(pos, static_cast<std::ptrdiff_t>(1U));

    my_exp -= static_cast<std::int64_t>(n_shift);
  }

  // Cut the size of the mantissa to <= ef_elem_digits10.
  pos          = str.find(static_cast<char>('.'));
  pos_plus_one = static_cast<std::ptrdiff_t>(pos + 1U);

  if(pos > static_cast<std::ptrdiff_t>(ef_elem_digits10))
  {
    const std::int32_t n_pos         = static_cast<std::int32_t>(pos);
    const std::int32_t n_rem_is_zero = ((static_cast<std::int32_t>(n_pos % ef_elem_digits10) == static_cast<std::int32_t>(0)) ? static_cast<std::int32_t>(1) : static_cast<std::int32_t>(0));
    const std::int32_t n             = static_cast<std::int32_t>(static_cast<std::int32_t>(n_pos / ef_elem_digits10) - n_rem_is_zero);
    
    str.insert(static_cast<std::size_t>(static_cast<std::int32_t>(n_pos - static_cast<std::int32_t>(n * ef_elem_digits10))), ".");

    str.erase(static_cast<std::string::size_type>(pos_plus_one), static_cast<std::size_t>(1U));

    my_exp += static_cast<std::int64_t>(static_cast<std::int64_t>(n) * static_cast<std::int64_t>(ef_elem_digits10));
  }

  // Pad the decimal part such that its value is an even
  // multiple of ef_elem_digits10.
  pos          = str.find(static_cast<char>('.'));
  pos_plus_one = static_cast<std::ptrdiff_t>(pos + 1);

  const std::int32_t n_dec = static_cast<std::int32_t>(static_cast<std::int32_t>(str.length() - 1U) - static_cast<std::int32_t>(pos));
  const std::int32_t n_rem = static_cast<std::int32_t>(n_dec % ef_elem_digits10);
        std::int32_t n_cnt = ((n_rem != static_cast<std::int32_t>(0)) ? static_cast<std::int32_t>(ef_elem_digits10 - n_rem)
                                                        : static_cast<std::int32_t>(0));

  if(n_cnt != static_cast<std::int32_t>(0))
  {
    str.append(static_cast<std::string::size_type>(n_cnt), static_cast<char>('0'));
  }

  // Truncate decimal part if it is too long.
  const std::ptrdiff_t max_dec = static_cast<std::ptrdiff_t>((ef_elem_number - 1) * ef_elem_digits10);

  if(static_cast<std::ptrdiff_t>(str.length() - pos) > max_dec)
  {
    str = str.substr(static_cast<std::string::size_type>(0),
                     static_cast<std::string::size_type>(pos_plus_one + max_dec));
  }

  // Now the input string has the standard e_float input form.
  // (See the comment above.)

  // Set all the data elements to 0.
  std::fill(my_data.begin(), my_data.end(), static_cast<array_type::value_type>(0));

  // Extract the data.

  // First get the digits to the left of the decimal point...
  my_data[static_cast<array_type::size_type>(0U)] =
    Util::numeric_cast<array_type::value_type>(str.substr(static_cast<std::ptrdiff_t>(0), pos));

  // ...then get the remaining digits to the right of the decimal point.
  const std::string::difference_type i_end = ((static_cast<std::string::difference_type>(str.length()) - pos_plus_one) / static_cast<std::string::difference_type>(ef_elem_digits10));

  for(std::string::difference_type i = static_cast<std::string::difference_type>(0); i < i_end; ++i)
  {
    const std::string::const_iterator it =   str.cbegin()
                                           + static_cast<std::string::difference_type>(pos_plus_one)
                                           + (i * static_cast<std::string::difference_type>(ef_elem_digits10));

    const array_type::size_type i1 = static_cast<array_type::size_type>(i + 1);

    const std::string str_i1(it,
                             it + static_cast<std::string::difference_type>(ef_elem_digits10));

    my_data[i1] = Util::numeric_cast<array_type::value_type>(str_i1);
  }

  // Check for overflow...
  if(my_exp > std::numeric_limits<e_float>::max_exponent10)
  {
    const bool b_result_is_neg = my_neg;

    *this = ((!b_result_is_neg) ?  std::numeric_limits<e_float>::infinity()
                                : -std::numeric_limits<e_float>::infinity());
  }

  // ...and check for underflow.
  if(my_exp <= std::numeric_limits<e_float>::min_exponent10)
  {
    if(my_exp == std::numeric_limits<e_float>::min_exponent10)
    {
      // Check for identity with the minimum value.
      e_float test = *this;

      test.my_exp = static_cast<std::int64_t>(0);

      if(test.isone())
      {
        *this = ef::zero();
      }
    }
    else
    {
      *this = ef::zero();
    }
  }

  return true;
}
