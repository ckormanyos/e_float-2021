//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Implement templates for an extended complex class and
// its associated functions. These are intended to be used
// with both user-defined types as well as built-in float,
// double and long double.

#ifndef E_FLOAT_COMPLEX_2017_08_23_HPP_
  #define E_FLOAT_COMPLEX_2017_08_23_HPP_

  #include <algorithm>
  #include <array>
  #include <cmath>
  #include <istream>
  #include <ostream>
  #include <regex>
  #include <sstream>
  #include <string>

  #include <boost/e_float/e_float.hpp>
  #include <boost/e_float/e_float_functions.hpp>
  #include <boost/e_float/e_float_detail_pown_template.hpp>

  namespace ef
  {
    // Forward declarations.

    // Class template extended_complex::complex<T>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.2.

    template<typename T>
    class complex;

    // Class template specializations of ef::complex<T>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.3.

    template<>
    class complex<float>;

    template<>
    class complex<double>;

    template<>
    class complex<long double>;

    template<>
    class complex<e_float>;

    template<typename T,
             typename char_type,
             typename traits_type>
    std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>& c__my_istream, complex<T>& c__my_z);

    template<typename T,
             typename char_type,
             typename traits_type>
    std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>& c__my_ostream, const complex<T>& c__my_z);

    // Non-member operations for ef::complex<T>.
    // see also ISO/IEC 14882:2011 Sect. 26.4.6.

    // Unary +/- operators.
    template<typename T> complex<T> operator+(const complex<T>&);
    template<typename T> complex<T> operator-(const complex<T>&);

    // Global add, sub, mul, div operators.
    template<typename T> complex<T> operator+(const complex<T>&, const complex<T>&);
    template<typename T> complex<T> operator-(const complex<T>&, const complex<T>&);
    template<typename T> complex<T> operator*(const complex<T>&, const complex<T>&);
    template<typename T> complex<T> operator/(const complex<T>&, const complex<T>&);

    template<typename T> complex<T> operator+(const complex<T>&, const T&);
    template<typename T> complex<T> operator-(const complex<T>&, const T&);
    template<typename T> complex<T> operator*(const complex<T>&, const T&);
    template<typename T> complex<T> operator/(const complex<T>&, const T&);

    template<typename T> complex<T> operator+(const T&, const complex<T>&);
    template<typename T> complex<T> operator-(const T&, const complex<T>&);
    template<typename T> complex<T> operator*(const T&, const complex<T>&);
    template<typename T> complex<T> operator/(const T&, const complex<T>&);

    // Equality and inequality operators.
    template<typename T> bool operator==(const complex<T>&, const complex<T>&);
    template<typename T> bool operator==(const complex<T>&, const T&);
    template<typename T> bool operator==(const T&,          const complex<T>&);

    template<typename T> bool operator!=(const complex<T>&, const complex<T>&);
    template<typename T> bool operator!=(const complex<T>&, const T&);
    template<typename T> bool operator!=(const T&,          const complex<T>&);

    // I/O stream operators.
    template<typename T, typename char_type, typename traits_type>
    std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>&, complex<T>&);

    template<typename T, typename char_type, typename traits_type>
    std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>&, const complex<T>&);

    // Value operations for extended_complex::complex<T>.
    // Similar to ISO/IEC 14882:2011 Sect. 26.4.7.

    template<typename T> T          real (const complex<T>&);
    template<typename T> T          imag (const complex<T>&);

    template<typename T> T          abs  (const complex<T>&);
    template<typename T> T          arg  (const complex<T>&);
    template<typename T> T          norm (const complex<T>&);

    template<typename T> complex<T> conj (const complex<T>&);
    template<typename T> complex<T> proj (const complex<T>&);
    template<typename T> complex<T> polar(const T&, const T& = T(0U));

    // Elementary transcendental functions for ef::complex<T>.
    // see also ISO/IEC 14882:2011 Sect. 26.4.8.

    template<typename T> complex<T> acos (const complex<T>&);
    template<typename T> complex<T> asin (const complex<T>&);
    template<typename T> complex<T> atan (const complex<T>&);
    template<typename T> complex<T> asinh(const complex<T>&);
    template<typename T> complex<T> acosh(const complex<T>&);
    template<typename T> complex<T> atanh(const complex<T>&);

    template<typename T> complex<T> cos  (const complex<T>&);
    template<typename T> complex<T> cosh (const complex<T>&);
    template<typename T> complex<T> exp  (const complex<T>&);
    template<typename T> complex<T> log  (const complex<T>&);
    template<typename T> complex<T> log10(const complex<T>&);

    template<typename T> complex<T> pow  (const complex<T>&, std::int64_t);
    template<typename T> complex<T> pow  (const complex<T>&, const T&);
    template<typename T> complex<T> pow  (const complex<T>&, const complex<T>&);
    template<typename T> complex<T> pow  (const T&, const complex<T>&);

    template<typename T> complex<T> sin  (const complex<T>&);
    template<typename T> complex<T> sinh (const complex<T>&);
    template<typename T> complex<T> sqrt (const complex<T>&);
    template<typename T> complex<T> tan  (const complex<T>&);
    template<typename T> complex<T> tanh (const complex<T>&);

    // Class template ef::complex<T>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.2.

    template<typename T>
    class complex
    {
    public:
      typedef T value_type;

      complex(const value_type& c__my_x = value_type(),
              const value_type& c__my_y = value_type()) : c__my_re(c__my_x),
                                                         c__my_im(c__my_y) { }

      complex(const complex& c__my_z) : c__my_re(c__my_z.real()),
                                        c__my_im(c__my_z.imag()) { }

      template<typename X>
      complex(const complex<X>& c__my_z) : c__my_re(static_cast<value_type>(c__my_z.real())),
                                           c__my_im(static_cast<value_type>(c__my_z.imag())) { }

      value_type real() const { return c__my_re; }
      value_type imag() const { return c__my_im; }

      void real(value_type c__my_x) { c__my_re = c__my_x; }
      void imag(value_type c__my_y) { c__my_im = c__my_y; }

      complex& operator=(const value_type& c__my_other_x)
      {
        c__my_re = c__my_other_x;
        c__my_im = value_type(0U);

        return *this;
      }

      complex& operator+=(const value_type& c__my_x)
      {
        c__my_re += c__my_x;

        return *this;
      }

      complex& operator-=(const value_type& c__my_x)
      {
        c__my_re -= c__my_x;

        return *this;
      }

      complex& operator*=(const value_type& c__my_x)
      {
        c__my_re *= c__my_x;
        c__my_im *= c__my_x;

        return *this;
      }

      complex& operator/=(const value_type& c__my_x)
      {
        c__my_re /= c__my_x;
        c__my_im /= c__my_x;

        return *this;
      }

      complex& operator=(const complex& c__my_other_z)
      {
        if(this != &c__my_other_z)
        {
          c__my_re = c__my_other_z.c__my_re;
          c__my_im = c__my_other_z.c__my_im;
        }

        return *this;
      }

      template<typename X>
      complex& operator=(const complex<X>& c__my_other_z)
      {
        c__my_re = static_cast<value_type>(c__my_other_z.c__my_re);
        c__my_im = static_cast<value_type>(c__my_other_z.c__my_im);

        return *this;
      }

      template<typename X>
      complex& operator+=(const complex<X>& c__my_z)
      {
        c__my_re += static_cast<value_type>(c__my_z.c__my_re);
        c__my_im += static_cast<value_type>(c__my_z.c__my_im);

        return *this;
      }

      template<typename X>
      complex& operator-=(const complex<X>& c__my_z)
      {
        if(this == &c__my_z)
        {
          c__my_re = value_type(0);
          c__my_im = value_type(0);
        }
        else
        {
          c__my_re -= static_cast<value_type>(c__my_z.c__my_re);
          c__my_im -= static_cast<value_type>(c__my_z.c__my_im);
        }

        return *this;
      }

      template<typename X>
      complex& operator*=(const complex<X>& c__my_z)
      {
        const value_type __tmp_re(c__my_re);

        if(this == &c__my_z)
        {
          c__my_re = (__tmp_re * __tmp_re) - (c__my_im * c__my_im);
          c__my_im = (__tmp_re * c__my_im) * 2U;
        }
        else
        {
          c__my_re = (__tmp_re * c__my_z.c__my_re) - (c__my_im * c__my_z.c__my_im);
          c__my_im = (__tmp_re * c__my_z.c__my_im) + (c__my_im * c__my_z.c__my_re);
        }

        return *this;
      }

      template<typename X>
      complex& operator/=(const complex<X>& c__my_z)
      {
        if(this == &c__my_z)
        {
          c__my_re = value_type(1);
          c__my_im = value_type(0);
        }
        else
        {
          if(fabs(c__my_z.real()) < fabs(c__my_z.imag()))
          {
            const value_type c__my_c_over_d = c__my_z.real() / c__my_z.imag();

            const value_type c__my_denominator = (c__my_z.real() * c__my_c_over_d) + c__my_z.imag();

            const value_type c__my_tmp_re(c__my_re);

            c__my_re = ((c__my_tmp_re * c__my_c_over_d) + c__my_im)     / c__my_denominator;
            c__my_im = ((c__my_im     * c__my_c_over_d) - c__my_tmp_re) / c__my_denominator;
          }
          else
          {
            const value_type c__my_d_over_c = c__my_z.imag() / c__my_z.real();

            const value_type c__my_denominator = (c__my_z.imag() * c__my_d_over_c) + c__my_z.real();

            const value_type c__my_tmp_re(c__my_re);

            c__my_re = (( c__my_im     * c__my_d_over_c) + c__my_tmp_re) / c__my_denominator;
            c__my_im = ((-c__my_tmp_re * c__my_d_over_c) + c__my_im)     / c__my_denominator;
          }
        }

        return *this;
      }

    private:
      value_type c__my_re;
      value_type c__my_im;
    };


    // Specialization of class template ef::complex<float>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.3.

    template<>
    class complex<float>
    {
    public:
      typedef float value_type;

      complex(float c__my_x = float(),
              float c__my_y = float()) : c__my_re(c__my_x),
                                         c__my_im(c__my_y) { }

      explicit complex(const complex<double>&);
      explicit complex(const complex<long double>&);

      float real() const { return c__my_re; }
      float imag() const { return c__my_im; }

      void real(float c__my_x) { c__my_re = c__my_x; }
      void imag(float c__my_y) { c__my_im = c__my_y; }

      complex& operator=(float c__my_other_x)
      {
        c__my_re = c__my_other_x;
        c__my_im = 0.0F;

        return *this;
      }

      complex& operator+=(float c__my_x)
      {
        c__my_re += c__my_x;

        return *this;
      }

      complex& operator-=(float c__my_x)
      {
        c__my_re -= c__my_x;

        return *this;
      }

      complex& operator*=(float c__my_x)
      {
        c__my_re *= c__my_x;
        c__my_im *= c__my_x;

        return *this;
      }

      complex& operator/=(float c__my_x)
      {
        c__my_re /= c__my_x;
        c__my_im /= c__my_x;

        return *this;
      }

      complex& operator=(const complex& c__my_other_z)
      {
        if(this != &c__my_other_z)
        {
          c__my_re = c__my_other_z.c__my_re;
          c__my_im = c__my_other_z.c__my_im;
        }

        return *this;
      }

      template<typename X>
      complex& operator=(const complex<X>& c__my_other_z)
      {
        c__my_re = static_cast<float>(c__my_other_z.c__my_re);
        c__my_im = static_cast<float>(c__my_other_z.c__my_im);

        return *this;
      }

      template<typename X>
      complex& operator+=(const complex<X>& c__my_z)
      {
        c__my_re += static_cast<float>(c__my_z.c__my_re);
        c__my_im += static_cast<float>(c__my_z.c__my_im);

        return *this;
      }

      template<typename X>
      complex& operator-=(const complex<X>& c__my_z)
      {
        c__my_re -= static_cast<float>(c__my_z.c__my_re);
        c__my_im -= static_cast<float>(c__my_z.c__my_im);

        return *this;
      }

      template<typename X>
      complex& operator*=(const complex<X>& c__my_z)
      {
        const float __tmp_re(c__my_re);

        if(this == &c__my_z)
        {
          c__my_re = (__tmp_re * __tmp_re) - (c__my_im * c__my_im);
          c__my_im = (__tmp_re * c__my_im) * 2.0F;
        }
        else
        {
          c__my_re = (__tmp_re * c__my_z.c__my_re) - (c__my_im * c__my_z.c__my_im);
          c__my_im = (__tmp_re * c__my_z.c__my_im) + (c__my_im * c__my_z.c__my_re);
        }

        return *this;
      }

      template<typename X>
      complex& operator/=(const complex<X>& c__my_z)
      {
        if(this == &c__my_z)
        {
          c__my_re = 1.0F;
          c__my_im = 0.0F;
        }
        else
        {
          using std::fabs;

          if(fabs(c__my_z.real()) < fabs(c__my_z.imag()))
          {
            const float c__my_c_over_d = c__my_z.real() / c__my_z.imag();

            const float c__my_denominator = (c__my_z.real() * c__my_c_over_d) + c__my_z.imag();

            const float c__my_tmp_re(c__my_re);

            real(((c__my_tmp_re * c__my_c_over_d) + c__my_im)     / c__my_denominator);
            imag(((c__my_im     * c__my_c_over_d) - c__my_tmp_re) / c__my_denominator);
          }
          else
          {
            const float c__my_d_over_c = c__my_z.imag() / c__my_z.real();

            const float c__my_denominator = (c__my_z.imag() * c__my_d_over_c) + c__my_z.real();

            const float c__my_tmp_re(c__my_re);

            real((( c__my_im     * c__my_d_over_c) + c__my_tmp_re) / c__my_denominator);
            imag(((-c__my_tmp_re * c__my_d_over_c) + c__my_im)     / c__my_denominator);
          }
        }

        return *this;
      }

    private:
      float c__my_re;
      float c__my_im;
    };


    // Specialization of class template ef::complex<double>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.3.

    template<>
    class complex<double>
    {
    public:
      typedef double value_type;

      complex(double c__my_x = double(),
              double c__my_y = double()) : c__my_re(c__my_x),
                                           c__my_im(c__my_y) { }

      complex(const complex<float>& c__my_f) : c__my_re(double(c__my_f.real())),
                                               c__my_im(double(c__my_f.imag())) { }

      explicit complex(const complex<long double>&);

      double real() const { return c__my_re; }
      double imag() const { return c__my_im; }

      void real(double c__my_x) { c__my_re = c__my_x; }
      void imag(double c__my_y) { c__my_im = c__my_y; }

      complex& operator=(double c__my_other_x)
      {
        c__my_re = c__my_other_x;
        c__my_im = 0.0;

        return *this;
      }

      complex& operator+=(double c__my_x)
      {
        c__my_re += c__my_x;

        return *this;
      }

      complex& operator-=(double c__my_x)
      {
        c__my_re -= c__my_x;

        return *this;
      }

      complex& operator*=(double c__my_x)
      {
        c__my_re *= c__my_x;
        c__my_im *= c__my_x;

        return *this;
      }

      complex& operator/=(double c__my_x)
      {
        c__my_re /= c__my_x;
        c__my_im /= c__my_x;

        return *this;
      }

      complex& operator=(const complex& c__my_other_z)
      {
        if(this != &c__my_other_z)
        {
          c__my_re = c__my_other_z.c__my_re;
          c__my_im = c__my_other_z.c__my_im;
        }

        return *this;
      }

      template<typename X>
      complex& operator=(const complex<X>& c__my_other_z)
      {
        c__my_re = static_cast<double>(c__my_other_z.c__my_re);
        c__my_im = static_cast<double>(c__my_other_z.c__my_im);

        return *this;
      }

      template<typename X>
      complex& operator+=(const complex<X>& c__my_z)
      {
        c__my_re += static_cast<double>(c__my_z.c__my_re);
        c__my_im += static_cast<double>(c__my_z.c__my_im);

        return *this;
      }

      template<typename X>
      complex& operator-=(const complex<X>& c__my_z)
      {
        c__my_re -= static_cast<double>(c__my_z.c__my_re);
        c__my_im -= static_cast<double>(c__my_z.c__my_im);

        return *this;
      }

      template<typename X>
      complex& operator*=(const complex<X>& c__my_z)
      {
        const double __tmp_re(c__my_re);

        if(this == &c__my_z)
        {
          c__my_re = (__tmp_re * __tmp_re) - (c__my_im * c__my_im);
          c__my_im = (__tmp_re * c__my_im) * 2.0;
        }
        else
        {
          c__my_re = (__tmp_re * c__my_z.c__my_re) - (c__my_im * c__my_z.c__my_im);
          c__my_im = (__tmp_re * c__my_z.c__my_im) + (c__my_im * c__my_z.c__my_re);
        }

        return *this;
      }

      template<typename X>
      complex& operator/=(const complex<X>& c__my_z)
      {
        if(this == &c__my_z)
        {
          c__my_re = 1.0;
          c__my_im = 0.0;
        }
        else
        {
          using std::fabs;

          if(fabs(c__my_z.real()) < fabs(c__my_z.imag()))
          {
            const double c__my_c_over_d = c__my_z.real() / c__my_z.imag();

            const double c__my_denominator = (c__my_z.real() * c__my_c_over_d) + c__my_z.imag();

            const double c__my_tmp_re(c__my_re);

            real(((c__my_tmp_re * c__my_c_over_d) + c__my_im)     / c__my_denominator);
            imag(((c__my_im     * c__my_c_over_d) - c__my_tmp_re) / c__my_denominator);
          }
          else
          {
            const double c__my_d_over_c = c__my_z.imag() / c__my_z.real();

            const double c__my_denominator = (c__my_z.imag() * c__my_d_over_c) + c__my_z.real();

            const double c__my_tmp_re(c__my_re);

            real((( c__my_im     * c__my_d_over_c) + c__my_tmp_re) / c__my_denominator);
            imag(((-c__my_tmp_re * c__my_d_over_c) + c__my_im)     / c__my_denominator);
          }
        }

        return *this;
      }

    private:
      double c__my_re;
      double c__my_im;
    };

    // Specialization of class template extended_complex::complex<long double>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.3.

    template<>
    class complex<long double>
    {
    public:
      typedef long double value_type;

      complex(value_type c__my_x = (value_type()),
              value_type c__my_y = (value_type())) : c__my_re(c__my_x),
                                                     c__my_im(c__my_y) { }

      complex(const complex<float>& c__my_f) : c__my_re(static_cast<value_type>(c__my_f.real())),
                                               c__my_im(static_cast<value_type>(c__my_f.imag())) { }

      complex(const complex<double>& c__my_d) : c__my_re(static_cast<value_type>(c__my_d.real())),
                                                c__my_im(static_cast<value_type>(c__my_d.imag())) { }

      value_type real() const { return c__my_re; }
      value_type imag() const { return c__my_im; }

      void real(value_type c__my_x) { c__my_re = c__my_x; }
      void imag(value_type c__my_y) { c__my_im = c__my_y; }

      complex& operator=(value_type c__my_other_x)
      {
        c__my_re = c__my_other_x;
        c__my_im = 0.0L;

        return *this;
      }

      complex& operator+=(value_type c__my_x)
      {
        c__my_re += c__my_x;

        return *this;
      }

      complex& operator-=(value_type c__my_x)
      {
        c__my_re -= c__my_x;

        return *this;
      }

      complex& operator*=(value_type c__my_x)
      {
        c__my_re *= c__my_x;
        c__my_im *= c__my_x;

        return *this;
      }

      complex& operator/=(value_type c__my_x)
      {
        c__my_re /= c__my_x;
        c__my_im /= c__my_x;

        return *this;
      }

      complex& operator=(const complex& c__my_other_z)
      {
        if(this != &c__my_other_z)
        {
          c__my_re = c__my_other_z.c__my_re;
          c__my_im = c__my_other_z.c__my_im;
        }

        return *this;
      }

      template<typename X>
      complex& operator=(const complex<X>& c__my_other_z)
      {
        c__my_re = static_cast<value_type>(c__my_other_z.c__my_re);
        c__my_im = static_cast<value_type>(c__my_other_z.c__my_im);

        return *this;
      }

      template<typename X>
      complex& operator+=(const complex<X>& c__my_z)
      {
        c__my_re += static_cast<value_type>(c__my_z.c__my_re);
        c__my_im += static_cast<value_type>(c__my_z.c__my_im);

        return *this;
      }

      template<typename X>
      complex& operator-=(const complex<X>& c__my_z)
      {
        c__my_re -= static_cast<value_type>(c__my_z.c__my_re);
        c__my_im -= static_cast<value_type>(c__my_z.c__my_im);

        return *this;
      }

      template<typename X>
      complex& operator*=(const complex<X>& c__my_z)
      {
        const value_type __tmp_re(c__my_re);

        if(this == &c__my_z)
        {
          c__my_re = (__tmp_re * __tmp_re) - (c__my_im * c__my_im);
          c__my_im = (__tmp_re * c__my_im) * 2.0L;
        }
        else
        {
          c__my_re = (__tmp_re * c__my_z.c__my_re) - (c__my_im * c__my_z.c__my_im);
          c__my_im = (__tmp_re * c__my_z.c__my_im) + (c__my_im * c__my_z.c__my_re);
        }

        return *this;
      }

      template<typename X>
      complex& operator/=(const complex<X>& c__my_z)
      {
        if(this == &c__my_z)
        {
          c__my_re = 1.0L;
          c__my_im = 0.0L;
        }
        else
        {
          using std::fabs;

          if(fabs(c__my_z.real()) < fabs(c__my_z.imag()))
          {
            const value_type c__my_c_over_d = c__my_z.real() / c__my_z.imag();

            const value_type c__my_denominator = (c__my_z.real() * c__my_c_over_d) + c__my_z.imag();

            const value_type c__my_tmp_re(c__my_re);

            real(((c__my_tmp_re * c__my_c_over_d) + c__my_im)     / c__my_denominator);
            imag(((c__my_im     * c__my_c_over_d) - c__my_tmp_re) / c__my_denominator);
          }
          else
          {
            const value_type c__my_d_over_c = c__my_z.imag() / c__my_z.real();

            const value_type c__my_denominator = (c__my_z.imag() * c__my_d_over_c) + c__my_z.real();

            const value_type c__my_tmp_re(c__my_re);

            real((( c__my_im     * c__my_d_over_c) + c__my_tmp_re) / c__my_denominator);
            imag(((-c__my_tmp_re * c__my_d_over_c) + c__my_im)     / c__my_denominator);
          }
        }

        return *this;
      }

    private:
      value_type c__my_re;
      value_type c__my_im;
    };

    // These constructors are located here because they need to be
    // implemented after the template specializations have been declared.

    inline complex<float >::complex(const complex<double>&      c__my_d) : c__my_re(float (c__my_d.real())), c__my_im(float (c__my_d.imag())) { }
    inline complex<float >::complex(const complex<long double>& c__my_l) : c__my_re(float (c__my_l.real())), c__my_im(float (c__my_l.imag())) { }
    inline complex<double>::complex(const complex<long double>& c__my_l) : c__my_re(double(c__my_l.real())), c__my_im(double(c__my_l.imag())) { }

    // Non-member operations for ef::complex<T>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.6.

    // Unary +/- operators.
    template<typename T> complex<T> operator+(const complex<T>& c__my_u) { return c__my_u; }
    template<typename T> complex<T> operator-(const complex<T>& c__my_u) { return complex<T>(-c__my_u.real(), -c__my_u.imag()); }

    // Global add, sub, mul, div operators.
    template<typename T> complex<T> operator+(const complex<T>& c__my_u, const complex<T>& c__my_v) { return complex<T>(c__my_u.real() + c__my_v.real(), c__my_u.imag() + c__my_v.imag()); }
    template<typename T> complex<T> operator-(const complex<T>& c__my_u, const complex<T>& c__my_v) { return complex<T>(c__my_u.real() - c__my_v.real(), c__my_u.imag() - c__my_v.imag()); }

    template<typename T> complex<T> operator*(const complex<T>& c__my_u, const complex<T>& c__my_v)
    {
      return complex<T>((c__my_u.real() * c__my_v.real()) - (c__my_u.imag() * c__my_v.imag()),
                        (c__my_u.real() * c__my_v.imag()) + (c__my_u.imag() * c__my_v.real()));
    }

    template<typename T> complex<T> operator/(const complex<T>& c__my_u, const complex<T>& c__my_v)
    {
      using std::fabs;

      complex<T> c__my_result;

      if(fabs(c__my_v.real()) < fabs(c__my_v.imag()))
      {
        const T c__my_c_over_d = c__my_v.real() / c__my_v.imag();

        const T c__my_denominator = (c__my_v.real() * c__my_c_over_d) + c__my_v.imag();

        c__my_result = complex<T>(((c__my_u.real() * c__my_c_over_d) + c__my_u.imag()) / c__my_denominator,
                                  ((c__my_u.imag() * c__my_c_over_d) - c__my_u.real()) / c__my_denominator);
      }
      else
      {
        const T c__my_d_over_c = c__my_v.imag() / c__my_v.real();

        const T c__my_denominator = (c__my_v.imag() * c__my_d_over_c) + c__my_v.real();

        c__my_result = complex<T>((( c__my_u.imag() * c__my_d_over_c) + c__my_u.real()) / c__my_denominator,
                                  ((-c__my_u.real() * c__my_d_over_c) + c__my_u.imag()) / c__my_denominator);
      }

      return c__my_result;
    }

    template<typename T> complex<T> operator+(const complex<T>& c__my_u, const T& c__my_v)  { return complex<T>(c__my_u.real() + c__my_v, c__my_u.imag()); }
    template<typename T> complex<T> operator-(const complex<T>& c__my_u, const T& c__my_v)  { return complex<T>(c__my_u.real() - c__my_v, c__my_u.imag()); }
    template<typename T> complex<T> operator*(const complex<T>& c__my_u, const T& c__my_v)  { return complex<T>(c__my_u.real() * c__my_v, c__my_u.imag() * c__my_v); }
    template<typename T> complex<T> operator/(const complex<T>& c__my_u, const T& c__my_v)  { return complex<T>(c__my_u.real() / c__my_v, c__my_u.imag() / c__my_v); }

    template<typename T> complex<T> operator+(const T& c__my_u, const complex<T>& c__my_v) { return complex<T>(c__my_u + c__my_v.real(), c__my_v.imag()); }
    template<typename T> complex<T> operator-(const T& c__my_u, const complex<T>& c__my_v) { return complex<T>(c__my_u - c__my_v.real(), -c__my_v.imag()); }
    template<typename T> complex<T> operator*(const T& c__my_u, const complex<T>& c__my_v) { return complex<T>(c__my_u * c__my_v.real(), c__my_u * c__my_v.imag()); }

    template<typename T> complex<T> operator/(const T& c__my_u, const complex<T>& c__my_v)
    {
      using std::fabs;

      complex<T> c__my_result;

      if(fabs(c__my_v.real()) < fabs(c__my_v.imag()))
      {
        const T c__my_c_over_d = c__my_v.real() / c__my_v.imag();

        const T c__my_denominator = (c__my_v.real() * c__my_c_over_d) + c__my_v.imag();

        c__my_result = complex<T>(( c__my_u * c__my_c_over_d) / c__my_denominator,
                                   -c__my_u                  / c__my_denominator);
      }
      else
      {
        const T c__my_d_over_c = c__my_v.imag() / c__my_v.real();

        const T c__my_denominator = (c__my_v.imag() * c__my_d_over_c) + c__my_v.real();

        c__my_result = complex<T>( c__my_u                   / c__my_denominator,
                                 (-c__my_u * c__my_d_over_c) / c__my_denominator);
      }

      return c__my_result;
    }

    // Equality and inequality operators.
    template<typename T> bool operator==(const complex<T>& c__my_u, const complex<T>& c__my_v) { return ((c__my_u.real() == c__my_v.real()) && (c__my_u.imag() == c__my_v.imag())); }
    template<typename T> bool operator==(const complex<T>& c__my_u, const T&          c__my_v) { return ((c__my_u.real() == c__my_v)        && (c__my_u.imag() == T(0))); }
    template<typename T> bool operator==(const T&          c__my_u, const complex<T>& c__my_v) { return ((c__my_u == c__my_v.real())        && (c__my_v.imag() == T(0))); }

    template<typename T> bool operator!=(const complex<T>& c__my_u, const complex<T>& c__my_v) { return ((c__my_u.real() != c__my_v.real()) || (c__my_u.imag() != c__my_v.imag())); }
    template<typename T> bool operator!=(const complex<T>& c__my_u, const T&          c__my_v) { return ((c__my_u.real() != c__my_v)        || (c__my_u.imag() != T(0))); }
    template<typename T> bool operator!=(const T&          c__my_u, const complex<T>& c__my_v) { return ((c__my_u != c__my_v.real())        || (c__my_v.imag() != T(0))); }

    // I/O stream operators.
    template<typename T, typename char_type, typename traits_type>
    std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>& c__my_istream, complex<T>& c__my_z)
    {
      // Parse an (extended) complex number of any of the forms u, (u) or (u,v).

      const std::array<std::regex, 3U> c__my_regexes =
      {{
        // A regular expression for an (extended) complex number of the form (u,v).
        std::regex(  std::string("\\({1}")                             // One open parentheses.
                   + std::string("([\\+\\-]{0,1}[0-9]*\\.*[0-9]*)")    // Possible +-, decimal point and digits 0-9.
                   + std::string("([eE]{0,1}[\\+\\-]{0,1}[0-9]*)")     // Possible exponent field.
                   + std::string("\\,{1}")                             // One comma character.
                   + std::string("([\\+\\-]{0,1}[0-9]*\\.*[0-9]*)")    // Possible +-, decimal point and digits 0-9.
                   + std::string("([eE]{0,1}[\\+\\-]{0,1}[0-9]*)")     // Possible exponent field.
                   + std::string("\\){1}")),                           // One close parentheses.

        // A regular expression for an (extended) complex number of the form (u).
        std::regex(  std::string("\\({1}")                             // One open parentheses.
                   + std::string("([\\+\\-]{0,1}[0-9]*\\.*[0-9]*)")    // Possible +-, decimal point and digits 0-9.
                   + std::string("([eE]{0,1}[\\+\\-]{0,1}[0-9]*)")     // Possible exponent field.
                   + std::string("\\){1}")),                           // One close parentheses.

        // A regular expression for an (extended) complex number of the form u.
        std::regex(  std::string("([\\+\\-]{0,1}[0-9]*\\.*[0-9]*)")    // Possible +-, decimal point and digits 0-9.
                   + std::string("([eE]{0,1}[\\+\\-]{0,1}[0-9]*)"))    // Possible exponent field.
      }};

      T c__my_real_input(0U);
      T c__my_imag_input(0U);

      bool c__my_input_has_error = false;

      std::string c__my_input_str;

      c__my_istream >> c__my_input_str;

      std::match_results<std::string::const_iterator> c__my_mr;

      auto c__my_it_regex_match =
        std::find_if(c__my_regexes.cbegin(),
                     c__my_regexes.cend(),
                     [&c__my_input_str, &c__my_mr](const std::regex& c__my_rx) -> bool
                     {
                       return std::regex_match(c__my_input_str, c__my_mr, c__my_rx);
                     });

      if(c__my_it_regex_match == c__my_regexes.cend())
      {
        // The input does not match any of the regular expressions.
        // Set the error flag and take no other action.

        c__my_input_has_error = true;
      }
      else if(c__my_it_regex_match == c__my_regexes.cbegin())
      {
        // The input matches __the_regexes[0U], corresponding to the form (u,v).
        // This represents a complex number real and imaginary parts.

        // Rule out erroneous match of invalid mantissa or exponent parts.
        const std::string c__my_str1(c__my_mr[1U]);
        const std::string c__my_str2(c__my_mr[2U]);
        const std::string c__my_str3(c__my_mr[3U]);
        const std::string c__my_str4(c__my_mr[4U]);

        const std::string c__my_decimal_digits("0123456789");

        const bool c__my_str1_has_error = ((c__my_str1.length() != std::size_t(0U)) && (c__my_str1.find_first_of(c__my_decimal_digits) == std::string::npos));
        const bool c__my_str2_has_error = ((c__my_str2.length() != std::size_t(0U)) && (c__my_str2.find_first_of(c__my_decimal_digits) == std::string::npos));
        const bool c__my_str3_has_error = ((c__my_str3.length() != std::size_t(0U)) && (c__my_str3.find_first_of(c__my_decimal_digits) == std::string::npos));
        const bool c__my_str4_has_error = ((c__my_str4.length() != std::size_t(0U)) && (c__my_str4.find_first_of(c__my_decimal_digits) == std::string::npos));

        if(c__my_str1_has_error || c__my_str2_has_error || c__my_str3_has_error || c__my_str4_has_error)
        {
          c__my_input_has_error = true;
        }
        else
        {
          // Extract the real part of the complex number.
          {
            std::stringstream c__my_stringstream;

            c__my_stringstream << c__my_mr[1U] << c__my_mr[2U];
            c__my_stringstream >> c__my_real_input;
          }

          // Extract the imaginary part of the complex number.
          {
            std::stringstream c__my_stringstream;

            c__my_stringstream << c__my_mr[3U] << c__my_mr[4U];
            c__my_stringstream >> c__my_imag_input;
          }
        }
      }
      else if(   (c__my_it_regex_match == (c__my_regexes.cbegin() + 1U))
              || (c__my_it_regex_match == (c__my_regexes.cbegin() + 2U)))
      {
        // The input matches the_regexes[1U] or the_regexes[2U],
        // corresponding to either of the forms (u) or u.
        // This represents a pure real complex number.

        // Rule out erroneous match of invalid mantissa or exponent parts.
        const std::string c__my_str1(c__my_mr[1U]);
        const std::string c__my_str2(c__my_mr[2U]);

        const std::string c__my_decimal_digits("0123456789");

        if(   ((c__my_str1.length() != std::size_t(0U)) && (c__my_str1.find_first_of(c__my_decimal_digits) == std::string::npos))
           || ((c__my_str2.length() != std::size_t(0U)) && (c__my_str2.find_first_of(c__my_decimal_digits) == std::string::npos)))
        {
          c__my_input_has_error = true;
        }
        else
        {
          // Extract the real part of the complex number.
          std::stringstream c__my_stringstream;

          c__my_stringstream << c__my_mr[1U] << c__my_mr[2U];
          c__my_stringstream >> c__my_real_input;

          c__my_imag_input = T(0U);
        }
      }

      if(c__my_input_has_error)
      {
        // Error case: Restore the characters in the input stream
        // and set the fail bit in the input stream.
        std::for_each(c__my_input_str.cbegin(),
                      c__my_input_str.cend(),
                      [&c__my_istream](const char& c__my_c)
                      {
                        c__my_istream.putback(c__my_c);
                      });

        c__my_istream.setstate(std::ios_base::failbit);
      }
      else
      {
        c__my_z = complex<T>(c__my_real_input, c__my_imag_input);
      }

      return c__my_istream;
    }

    template<class T, class char_type, class traits_type>
    std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>& c__my_ostream, const complex<T>& c__my_z)
    {
      std::basic_ostringstream<char_type, traits_type> c__my_tmp_ostream;

      c__my_tmp_ostream.flags    (c__my_ostream.flags());
      c__my_tmp_ostream.imbue    (c__my_ostream.getloc());
      c__my_tmp_ostream.precision(c__my_ostream.precision());

      c__my_tmp_ostream << '('
                       << c__my_z.real()
                       << ','
                       << c__my_z.imag()
                       << ')';

      return (c__my_ostream << c__my_tmp_ostream.str());
    }

    // Value operations for ef::complex<T>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.7.

    template<typename T> T real(const complex<T>& c__my_z) { return c__my_z.real(); }
    template<typename T> T imag(const complex<T>& c__my_z) { return c__my_z.imag(); }

    template<typename T> T abs (const complex<T>& c__my_z) { using std::sqrt;  return sqrt(norm(c__my_z)); }
    template<typename T> T arg (const complex<T>& c__my_z) { using std::atan2; return atan2(c__my_z.imag(), c__my_z.real()); }

    template<typename T> T norm(const complex<T>& c__my_z)
    {
      using std::fabs;

      T c__my_result;

      if(fabs(c__my_z.real()) < fabs(c__my_z.imag()))
      {
        const T c__my_a_over_b = c__my_z.real() / c__my_z.imag();

        c__my_result = (c__my_z.imag() * c__my_z.imag()) * (T(1U) + (c__my_a_over_b * c__my_a_over_b));
      }
      else
      {
        const T c__my_b_over_a = c__my_z.imag() / c__my_z.real();

        c__my_result = (c__my_z.real() * c__my_z.real()) * (T(1U) + (c__my_b_over_a * c__my_b_over_a));
      }

      return c__my_result;
    }

    template<typename T> complex<T> conj(const complex<T>& c__my_z)
    {
      return complex<T>(-c__my_z.imag(), c__my_z.real());
    }

    template<typename T> complex<T> proj(const complex<T>& c__my_z)
    {
      const T __denominator_half((norm(c__my_z) + T(1U)) / 2U);

      return complex<T>(c__my_z.real() / __denominator_half,
                        c__my_z.imag() / __denominator_half);
    }

    template<typename T> complex<T> polar(const T& c__my_rho, const T& c__my_theta)
    {
      using std::cos;
      using std::sin;

      return complex<T>(c__my_rho * cos(c__my_theta), c__my_rho * sin(c__my_theta));
    }

    // Elementary transcendental functions for ef::complex<T>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.8.

    template<typename T> complex<T> acos(const complex<T>& c__my_z)
    {
      using std::asin;

      return T(asin(T(1U))) - asin(c__my_z);
    }

    template<typename T> complex<T> asin(const complex<T>& c__my_z)
    {
      return -conj(log(conj(c__my_z) + sqrt(T(1U) - (c__my_z * c__my_z))));
    }

    template<typename T> complex<T> atan(const complex<T>& c__my_z)
    {
      const complex<T> __z_conj = conj(c__my_z);

      complex<T> z__result = conj(log(T(1) - __z_conj) - log(T(1) + __z_conj));

      z__result.real(z__result.real() / 2U);
      z__result.imag(z__result.imag() / 2U);

      return z__result;
    }

    template<typename T> complex<T> acosh(const complex<T>& c__my_z)
    {
      const complex<T> __zp(c__my_z.real() + T(1U), c__my_z.imag());
      const complex<T> __zm(c__my_z.real() - T(1U), c__my_z.imag());

      return log(c__my_z + (__zp * sqrt(__zm / __zp)));
    }

    template<typename T> complex<T> asinh(const complex<T>& c__my_z)
    {
      return log(c__my_z + sqrt(T(1U) + (c__my_z * c__my_z)));
    }

    template<typename T> complex<T> atanh(const complex<T>& c__my_z)
    {
      complex<T> z__result = (log(T(1U) + c__my_z) - log(T(1U) - c__my_z));

      z__result.real(z__result.real() / 2U);
      z__result.imag(z__result.imag() / 2U);

      return z__result;
    }

    template<typename T> complex<T> cos(const complex<T>& c__my_z)
    {
      using std::cos;
      using std::cosh;
      using std::sin;
      using std::sinh;

      return complex<T>(   cos(c__my_z.real()) * cosh(c__my_z.imag()),
                        - (sin(c__my_z.real()) * sinh(c__my_z.imag())));
    }

    template<typename T> complex<T> cosh(const complex<T>& c__my_z)
    {
      using std::cos;
      using std::cosh;
      using std::sin;
      using std::sinh;

      return complex<T>(cos(c__my_z.imag()) * cosh(c__my_z.real()),
                        sin(c__my_z.imag()) * sinh(c__my_z.real()));
    }

    template<typename T> complex<T> exp(const complex<T>& c__my_z)
    {
      using std::cos;
      using std::exp;
      using std::sin;

      return complex<T>(cos(c__my_z.imag()), sin(c__my_z.imag())) * T(exp(c__my_z.real()));
    }

    template<typename T> complex<T> log(const complex<T>& c__my_z)
    {
      using std::atan2;
      using std::log;

      const T c__my_real_part(log(norm(c__my_z)) / 2U);
      const T c__my_imag_part(atan2(c__my_z.imag(), c__my_z.real()));

      return complex<T>(c__my_real_part, c__my_imag_part);
    }

    template<typename T> complex<T> log10(const complex<T>& c__my_z)
    {
      using std::log;

      return log(c__my_z) / T(log(T(10)));
    }

    template<typename T> complex<T> pow(const complex<T>& c__my_z, int c__my_pn)
    {
      if     (c__my_pn <  0) { return  T(1U) / pow(c__my_z, -c__my_pn); }
      else if(c__my_pn == 0) { return  complex<T>(T(1U)); }
      else if(c__my_pn == 1) { return  c__my_z; }
      else if(c__my_pn == 2) { return  c__my_z * c__my_z; }
      else if(c__my_pn == 3) { return (c__my_z * c__my_z) * c__my_z; }
      else if(c__my_pn == 4) { const complex<T> c__my_z2(c__my_z * c__my_z); return (c__my_z2 * c__my_z2); }
      else
      {
        // The variable xn stores the binary powers of c__my_z.
        complex<T> c__my_result(((c__my_pn % 2U) != 0U) ? c__my_z : complex<T>(T(1U)));
        complex<T> c__my_xn      (c__my_z);

        unsigned int c__my_p2 = static_cast<unsigned int>(c__my_pn);

        while((c__my_p2 /= 2U) != 0U)
        {
          // Square xn for each binary power.
          c__my_xn *= c__my_xn;

          const bool c__my_p2_has_binary_power = ((c__my_p2 % 2U) != 0U);

          if(c__my_p2_has_binary_power)
          {
            // Multiply the result with each binary power contained in the exponent.
            c__my_result *= c__my_xn;
          }
        }

        return c__my_result;
      }
    }

    template<typename T> complex<T> pow(const complex<T>& c__my_z, const T& c__my_a)
    {
      return exp(c__my_a * log(c__my_z));
    }

    template<typename T> complex<T> pow(const complex<T>& c__my_z, const complex<T>& c__my_a)
    {
      return exp(c__my_a * log(c__my_z));
    }

    template<typename T> complex<T> pow(const T& c__my_z, const complex<T>& c__my_a)
    {
      using std::log;

      return exp(c__my_a * T(log(c__my_z)));
    }

    template<typename T> complex<T> sin(const complex<T>& c__my_z)
    {
      using std::cos;
      using std::cosh;
      using std::sin;
      using std::sinh;

      return complex<T>(sin(c__my_z.real()) * cosh(c__my_z.imag()),
                        cos(c__my_z.real()) * sinh(c__my_z.imag()));
    }

    template<typename T> complex<T> sinh(const complex<T>& c__my_z)
    {
      using std::cos;
      using std::cosh;
      using std::sin;
      using std::sinh;

      return complex<T>(cos (c__my_z.imag()) * sinh(c__my_z.real()),
                        cosh(c__my_z.real()) * sin (c__my_z.imag()));
    }

    template<typename T> complex<T> sqrt(const complex<T>& c__my_z)
    {
      using std::fabs;
      using std::sqrt;

      // Use the following:
      // sqrt(z) = (s, zi / 2s)       for zr >= 0
      //           (|zi| / 2s, +-s)   for zr <  0
      // where s = sqrt{ [ |zr| + sqrt(zr^2 + zi^2) ] / 2 },
      // and the +- sign is the same as the sign of zi.

      const bool __real_part_is_neg(c__my_z.real() < T(0U));
      const T    __real_part_fabs  ((__real_part_is_neg == false) ? c__my_z.real() : -c__my_z.real());
      const T    __s_part          (sqrt((__real_part_fabs + abs(c__my_z)) / 2U));

      if(__real_part_is_neg == false)
      {
        return complex<T>(__s_part,
                          c__my_z.imag() / (__s_part * 2U));
      }
      else
      {
        const bool __imag_part_is_neg(c__my_z.imag() < T(0U));
        const T    __imag_part_fabs  ((__imag_part_is_neg == false) ? c__my_z.imag() : -c__my_z.imag());

        return complex<T>( __imag_part_fabs / (__s_part * 2U),
                         ((__imag_part_is_neg == false) ? __s_part : -__s_part));
      }
    }

    template<typename T> complex<T> tan(const complex<T>& c__my_z)
    {
      return sin(c__my_z) / cos(c__my_z);
    }

    template<typename T> complex<T> tanh(const complex<T>& c__my_z)
    {
      return sinh(c__my_z) / cosh(c__my_z);
    }

    // Now we begin the specialization of ef::complex<e_float>

    // Template specializations of unary +/- operators
    // for ef::complex<ef::e_float>.
    template<> inline complex<e_float> operator+(const complex<e_float>&);
    template<> inline complex<e_float> operator-(const complex<e_float>&);

    // Template specializations of global add, sub, mul, div operators
    // for ef::complex<ef::e_float>.
    template<> inline complex<e_float> operator+(const complex<e_float>&, const complex<e_float>&);
    template<> inline complex<e_float> operator-(const complex<e_float>&, const complex<e_float>&);
    template<> inline complex<e_float> operator*(const complex<e_float>&, const complex<e_float>&);
    template<> inline complex<e_float> operator/(const complex<e_float>&, const complex<e_float>&);

    template<> inline complex<e_float> operator+(const complex<e_float>&, const e_float&);
    template<> inline complex<e_float> operator-(const complex<e_float>&, const e_float&);
    template<> inline complex<e_float> operator*(const complex<e_float>&, const e_float&);
    template<> inline complex<e_float> operator/(const complex<e_float>&, const e_float&);

    template<> inline complex<e_float> operator+(const e_float&, const complex<e_float>&);
    template<> inline complex<e_float> operator-(const e_float&, const complex<e_float>&);
    template<> inline complex<e_float> operator*(const e_float&, const complex<e_float>&);
    template<> inline complex<e_float> operator/(const e_float&, const complex<e_float>&);

    // Template specializations of equality and inequality operators
    // for ef::complex<ef::e_float>.
    template<> inline bool operator==(const complex<e_float>&, const complex<e_float>&);
    template<> inline bool operator==(const complex<e_float>&, const e_float&);
    template<> inline bool operator==(const e_float&,          const complex<e_float>&);
    template<> inline bool operator!=(const complex<e_float>&, const complex<e_float>&);
    template<> inline bool operator!=(const complex<e_float>&, const e_float&);
    template<> inline bool operator!=(const e_float&,          const complex<e_float>&);

    // Template specializations of elementary and transcendental functions
    // for ef::complex<ef::e_float>.
    template<> inline e_float          real(const complex<e_float>&);
    template<> inline e_float          imag(const complex<e_float>&);

    template<> inline e_float          abs (const complex<e_float>&);
    template<> inline e_float          arg (const complex<e_float>&);
    template<> inline e_float          norm(const complex<e_float>&);

    template<> inline complex<e_float> conj (const complex<e_float>&);
    template<> inline complex<e_float> proj (const complex<e_float>&);
    template<> inline complex<e_float> polar(const e_float&, const e_float&);

    template<> inline complex<e_float> acos (const complex<e_float>&);
    template<> inline complex<e_float> asin (const complex<e_float>&);
    template<> inline complex<e_float> atan (const complex<e_float>&);
    template<> inline complex<e_float> asinh(const complex<e_float>&);
    template<> inline complex<e_float> acosh(const complex<e_float>&);
    template<> inline complex<e_float> atanh(const complex<e_float>&);

    template<> inline complex<e_float> cos  (const complex<e_float>&);
    template<> inline complex<e_float> cosh (const complex<e_float>&);
    template<> inline complex<e_float> exp  (const complex<e_float>&);
    template<> inline complex<e_float> log  (const complex<e_float>&);
    template<> inline complex<e_float> log10(const complex<e_float>&);

    template<> inline complex<e_float> pow  (const complex<e_float>&, std::int64_t);
    template<> inline complex<e_float> pow  (const complex<e_float>&, const e_float&);
    template<> inline complex<e_float> pow  (const complex<e_float>&, const complex<e_float>&);
    template<> inline complex<e_float> pow  (const e_float&,          const complex<e_float>&);

    template<> inline complex<e_float> sin  (const complex<e_float>&);
    template<> inline complex<e_float> sinh (const complex<e_float>&);
    template<> inline complex<e_float> sqrt (const complex<e_float>&);
    template<> inline complex<e_float> tan  (const complex<e_float>&);
    template<> inline complex<e_float> tanh (const complex<e_float>&);

    // Template specializations of I/O stream operators for ef::complex<e_float>.
    template<typename char_type, typename traits_type>
    std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>&, complex<e_float>&);

    template<typename char_type, typename traits_type>
    std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>&, const complex<e_float>&);

    // Specialization of class template ef::complex<ef::e_float>.
    // see also ISO/IEC 14882:2011 Sect. 26.4.3.

    template<>
    class complex<e_float>
    {
    public:
      typedef e_float value_type;

      template<typename IntegralType,
               typename std::enable_if<(std::is_integral<IntegralType>::value == true)>::type const* = nullptr>
      explicit complex(const IntegralType n) : c__my_re(n),
                                               c__my_im(ef::zero()) { }

      template<typename FloatingPointType,
               typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true)>::type const* = nullptr>
      explicit complex(const FloatingPointType f) : c__my_re(f),
                                                    c__my_im(ef::zero()) { }

      complex(const e_float& c__my_x = e_float(),
              const e_float& c__my_y = e_float()) : c__my_re(c__my_x),
                                                   c__my_im(c__my_y) { }

      complex(const complex& c__my_z) : c__my_re(c__my_z.real()),
                                       c__my_im(c__my_z.imag()) { }

      e_float real() const { return c__my_re; }
      e_float imag() const { return c__my_im; }

      void real(e_float c__my_x) { c__my_re = c__my_x; }
      void imag(e_float c__my_y) { c__my_im = c__my_y; }

      complex& operator=(const e_float& c__my_other_x)
      {
        c__my_re  = c__my_other_x;
        c__my_im  = ef::zero();

        return *this;
      }

      complex& operator+=(const e_float& v)
      {
        c__my_re += v;

        return *this;
      }

      complex& operator-=(const e_float& v)
      {
        c__my_re -= v;

        return *this;
      }

      complex& operator*=(const e_float& v)
      {
        c__my_re *= v;
        c__my_im *= v;

        return *this;
      }

      complex& operator/=(const e_float& v)
      {
        c__my_re /= v;
        c__my_im /= v;

        return *this;
      }

      complex& operator=(const complex& c__my_other_z)
      {
        if(this != &c__my_other_z)
        {
          c__my_re = c__my_other_z.c__my_re;
          c__my_im = c__my_other_z.c__my_im;
        }

        return *this;
      }

      template<typename X>
      complex& operator+=(const complex<X>& c__my_z)
      {
        c__my_re += c__my_z.c__my_re;
        c__my_im += c__my_z.c__my_im;

        return *this;
      }

      template<typename X>
      complex& operator-=(const complex<X>& c__my_z)
      {
        if(this == &c__my_z)
        {
          c__my_re = ef::zero();
          c__my_im = ef::zero();
        }
        else
        {
          c__my_re -= static_cast<e_float>(c__my_z.c__my_re);
          c__my_im -= static_cast<e_float>(c__my_z.c__my_im);
        }

        return *this;
      }

      template<typename X>
      complex& operator*=(const complex<X>& c__my_z)
      {
        const e_float __tmp_re(c__my_re);

        if(this == &c__my_z)
        {
          c__my_re = (__tmp_re * __tmp_re) - (c__my_im * c__my_im);
          c__my_im = (__tmp_re * c__my_im) * 2U;
        }
        else
        {
          c__my_re = (__tmp_re * c__my_z.c__my_re) - (c__my_im * c__my_z.c__my_im);
          c__my_im = (__tmp_re * c__my_z.c__my_im) + (c__my_im * c__my_z.c__my_re);
        }

        return *this;
      }

      template<typename X>
      complex& operator/=(const complex<X>& c__my_z)
      {
        if(this == &c__my_z)
        {
          c__my_re = ef::one ();
          c__my_im = ef::zero();
        }
        else
        {
          const e_float one_over_denom(norm(c__my_z).calculate_inv());

          const e_float tmp_re(c__my_re);

          c__my_re = ((tmp_re  * c__my_z.c__my_re) + (c__my_im * c__my_z.c__my_im)) * one_over_denom;
          c__my_im = ((c__my_im * c__my_z.c__my_re) - (tmp_re  * c__my_z.c__my_im)) * one_over_denom;
        }

        return *this;
      }

      // Operators with integer.
      template<typename IntegralType,
               typename std::enable_if<   (std::is_integral<IntegralType>::value == true)
                                       && (std::is_unsigned<IntegralType>::value == false)>::type const* = nullptr>
      complex& operator+=(const IntegralType n)
      {
        c__my_re.add_signed_long_long(n);

        return *this;
      }

      template<typename IntegralType,
               typename std::enable_if<   (std::is_integral<IntegralType>::value == true)
                                       && (std::is_unsigned<IntegralType>::value == true)>::type const* = nullptr>
      complex& operator+=(const IntegralType n)
      {
        c__my_re.add_unsigned_long_long(n);

        return *this;
      }

      template<typename IntegralType,
               typename std::enable_if<   (std::is_integral<IntegralType>::value == true)
                                       && (std::is_unsigned<IntegralType>::value == false)>::type const* = nullptr>
      complex& operator-=(const IntegralType n)
      {
        c__my_re.sub_signed_long_long(n);

        return *this;
      }

      template<typename IntegralType,
               typename std::enable_if<   (std::is_integral<IntegralType>::value == true)
                                       && (std::is_unsigned<IntegralType>::value == true)>::type const* = nullptr>
      complex& operator-=(const IntegralType n)
      {
        c__my_re.sub_unsigned_long_long(n);

        return *this;
      }

      template<typename IntegralType,
               typename std::enable_if<   (std::is_integral<IntegralType>::value == true)
                                       && (std::is_unsigned<IntegralType>::value == false)>::type const* = nullptr>
      complex& operator*=(const IntegralType n)
      {
        c__my_re.mul_signed_long_long(n);
        c__my_im.mul_signed_long_long(n);

        return *this;
      }

      template<typename IntegralType,
               typename std::enable_if<   (std::is_integral<IntegralType>::value == true)
                                       && (std::is_unsigned<IntegralType>::value == true)>::type const* = nullptr>
      complex& operator*=(const IntegralType n)
      {
        c__my_re.mul_unsigned_long_long(n);
        c__my_im.mul_unsigned_long_long(n);

        return *this;
      }

      template<typename IntegralType,
               typename std::enable_if<   (std::is_integral<IntegralType>::value == true)
                                       && (std::is_unsigned<IntegralType>::value == false)>::type const* = nullptr>
      complex& operator/=(const IntegralType n)
      {
        c__my_re.div_signed_long_long(n);
        c__my_im.div_signed_long_long(n);

        return *this;
      }

      template<typename IntegralType,
               typename std::enable_if<   (std::is_integral<IntegralType>::value == true)
                                       && (std::is_unsigned<IntegralType>::value == true)>::type const* = nullptr>
      complex& operator/=(const IntegralType n)
      {
        c__my_re.div_unsigned_long_long(n);
        c__my_im.div_unsigned_long_long(n);

        return *this;
      }

    private:
      e_float c__my_re;
      e_float c__my_im;
    };

    // Non-member operations for ef::complex<T>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.6.

    // Unary +/- operators.
    template<> inline complex<e_float> operator+(const complex<e_float>& c__my_u) { return complex<e_float>(c__my_u); }
    template<> inline complex<e_float> operator-(const complex<e_float>& c__my_u) { return complex<e_float>(-c__my_u.real(), -c__my_u.imag()); }

    // Global binary add, sub, mul, div of complex op complex.
    template<> inline complex<e_float> operator+(const complex<e_float>& c__my_u, const complex<e_float>& c__my_v) { return complex<e_float>(c__my_u) += c__my_v; }
    template<> inline complex<e_float> operator-(const complex<e_float>& c__my_u, const complex<e_float>& c__my_v) { return complex<e_float>(c__my_u) -= c__my_v; }
    template<> inline complex<e_float> operator*(const complex<e_float>& c__my_u, const complex<e_float>& c__my_v) { return complex<e_float>(c__my_u) *= c__my_v; }
    template<> inline complex<e_float> operator/(const complex<e_float>& c__my_u, const complex<e_float>& c__my_v) { return complex<e_float>(c__my_u) /= c__my_v; }

    // Global binary add, sub, mul, div of complex op e_float.
    template<> inline complex<e_float> operator+(const complex<e_float>& c__my_u, const e_float& c__my_v) { return complex<e_float>(c__my_u.real() + c__my_v, c__my_u.imag()); }
    template<> inline complex<e_float> operator-(const complex<e_float>& c__my_u, const e_float& c__my_v) { return complex<e_float>(c__my_u.real() - c__my_v, c__my_u.imag()); }
    template<> inline complex<e_float> operator*(const complex<e_float>& c__my_u, const e_float& c__my_v) { return complex<e_float>(c__my_u.real() * c__my_v, c__my_u.imag() * c__my_v); }
    template<> inline complex<e_float> operator/(const complex<e_float>& c__my_u, const e_float& c__my_v) { return complex<e_float>(c__my_u.real() / c__my_v, c__my_u.imag() / c__my_v); }

    // Global binary add, sub, mul, div of e_float op complex.
    template<> inline complex<e_float> operator+(const e_float& c__my_u, const complex<e_float>& c__my_v) { return complex<e_float>(c__my_u + c__my_v.real(),  c__my_v.imag()); }
    template<> inline complex<e_float> operator-(const e_float& c__my_u, const complex<e_float>& c__my_v) { return complex<e_float>(c__my_u - c__my_v.real(), -c__my_v.imag()); }
    template<> inline complex<e_float> operator*(const e_float& c__my_u, const complex<e_float>& c__my_v) { return complex<e_float>(c__my_v.real() * c__my_u, c__my_v.imag() * c__my_u); }
    template<> inline complex<e_float> operator/(const e_float& c__my_u, const complex<e_float>& c__my_v)
    {
      const e_float c__my_v_norm(norm(c__my_v));

      return complex<e_float>(  (c__my_u * c__my_v.real()) / c__my_v_norm,
                              - (c__my_u * c__my_v.imag()) / c__my_v_norm);
    }

    template<> inline bool operator==(const complex<e_float>& c__my_u, const complex<e_float>& c__my_v) { return ((c__my_u.real() == c__my_v.real()) && (c__my_u.imag() == c__my_v.imag())); }
    template<> inline bool operator==(const complex<e_float>& c__my_u, const e_float         & c__my_v) { return ((c__my_u.real() == c__my_v)        && (c__my_u.imag() == e_float(0U))); }
    template<> inline bool operator==(const e_float&          c__my_u, const complex<e_float>& c__my_v) { return ((c__my_u == c__my_v.real())        && (c__my_v.imag() == e_float(0U))); }
    template<> inline bool operator!=(const complex<e_float>& c__my_u, const complex<e_float>& c__my_v) { return ((c__my_u.real() != c__my_v.real()) || (c__my_u.imag() != c__my_v.imag())); }
    template<> inline bool operator!=(const complex<e_float>& c__my_u, const e_float         & c__my_v) { return ((c__my_u.real() != c__my_v)        || (c__my_u.imag() != e_float(0U))); }
    template<> inline bool operator!=(const e_float&          c__my_u, const complex<e_float>& c__my_v) { return ((c__my_u != c__my_v.real())        || (c__my_v.imag() != e_float(0U))); }

    template<> inline e_float real(const complex<e_float>& c__my_z) { return c__my_z.real(); }
    template<> inline e_float imag(const complex<e_float>& c__my_z) { return c__my_z.imag(); }

    template<> inline e_float abs (const complex<e_float>& c__my_z) { return sqrt((c__my_z.real() * c__my_z.real()) + (c__my_z.imag() * c__my_z.imag())); }
    template<> inline e_float arg (const complex<e_float>& c__my_z) { return atan2(c__my_z.imag(), c__my_z.real()); }
    template<> inline e_float norm(const complex<e_float>& c__my_z) { return (c__my_z.real() * c__my_z.real()) + (c__my_z.imag() * c__my_z.imag()); }

    template<> inline complex<e_float> conj(const complex<e_float>& c__my_z)
    {
      return complex<e_float>(-c__my_z.imag(), c__my_z.real());
    }

    template<> inline complex<e_float> proj(const complex<e_float>& c__my_z)
    {
      const e_float two_over_denom((norm(c__my_z) + ef::one()).calculate_inv() * 2U);

      return complex<e_float>(c__my_z.real() * two_over_denom,
                              c__my_z.imag() * two_over_denom);
    }

    template<> inline complex<e_float> polar(const e_float& c__my_rho, const e_float& c__my_theta)
    {
      const e_float c__my_s = sin(c__my_theta);
      const e_float c__my_c = cos(c__my_theta);

      return complex<e_float>(c__my_rho * c__my_c, c__my_rho * c__my_s);
    }

    template<> inline complex<e_float> acos(const complex<e_float>& c__my_z)
    {
      return complex<e_float>(ef::pi_half()) - asin(c__my_z);
    }

    template<> inline complex<e_float> asin(const complex<e_float>& c__my_z)
    {
      return -conj(log(conj(c__my_z) + sqrt(ef::one() - (c__my_z * c__my_z))));
    }

    template<> inline complex<e_float> atan(const complex<e_float>& c__my_z)
    {
      const complex<e_float> c__my_z_conj(conj(c__my_z));

      const complex<e_float> c__my_pre_result(log(ef::one() - c__my_z_conj) - log(ef::one() + c__my_z_conj));

      return complex<e_float>(-c__my_pre_result.imag() / 2U,
                               c__my_pre_result.real() / 2U);
    }

    template<> inline complex<e_float> acosh(const complex<e_float>& c__my_z)
    {
      const complex<e_float> c__my_zp = c__my_z + ef::one();
      const complex<e_float> c__my_zm = c__my_z - ef::one();

      return log(c__my_z + (c__my_zp * sqrt(c__my_zm / c__my_zp)));
    }

    template<> complex<e_float> asinh(const complex<e_float>& c__my_z)
    {
      return log(c__my_z + sqrt((c__my_z * c__my_z) + ef::one()));
    }

    template<> inline complex<e_float> atanh(const complex<e_float>& c__my_z)
    {
      const complex<e_float> c__my_pre_result(  log(ef::one() + c__my_z)
                                             - log(ef::one() - c__my_z));

      return complex<e_float>(c__my_pre_result.real() / 2U,
                              c__my_pre_result.imag() / 2U);
    }

    template<> inline complex<e_float> cos(const complex<e_float>& c__my_z)
    {
      e_float c__my_sin_x  = sin (c__my_z.real());
      e_float c__my_cos_x  = cos (c__my_z.real());
      e_float c__my_sinh_y = sinh(c__my_z.imag());
      e_float c__my_cosh_y = cosh(c__my_z.imag());

      return complex<e_float>(c__my_cos_x * c__my_cosh_y, -(c__my_sin_x * c__my_sinh_y));
    }

    template<> inline complex<e_float> cosh(const complex<e_float>& c__my_z)
    {
      e_float c__my_sin_y  = sin (c__my_z.imag());
      e_float c__my_cos_y  = cos (c__my_z.imag());
      e_float c__my_sinh_x = sinh(c__my_z.real());
      e_float c__my_cosh_x = cosh(c__my_z.real());

      return complex<e_float>(c__my_cos_y * c__my_cosh_x, c__my_sin_y * c__my_sinh_x);
    }

    template<> inline complex<e_float> exp(const complex<e_float>& c__my_z)
    {
      e_float c__my_sin_y  = sin (c__my_z.imag());
      e_float c__my_cos_y  = cos (c__my_z.imag());

      return complex<e_float>(c__my_cos_y, c__my_sin_y) * e_float(ef::exp(c__my_z.real()));
    }

    template<> inline complex<e_float> log(const complex<e_float>& c__my_z)
    {
      using std::atan2;
      using std::log;

      const e_float c__my_real_part(ef::log(norm(c__my_z)) / 2U);
      const e_float c__my_imag_part(ef::atan2(c__my_z.imag(), c__my_z.real()));

      return complex<e_float>(c__my_real_part, c__my_imag_part);
    }

    template<> inline complex<e_float> log10(const complex<e_float>& c__my_z)
    {
      return log(c__my_z) / ln10();
    }

    template<> inline complex<e_float> pow(const complex<e_float>& c__my_z, std::int64_t c__my_pn)
    {
      return ef::detail::pown_template<complex<e_float>>(c__my_z, c__my_pn);
    }

    template<> inline complex<e_float> pow(const complex<e_float>& c__my_z, const e_float& c__my_a)
    {
      return exp(c__my_a * log(c__my_z));
    }

    template<> inline complex<e_float> pow(const complex<e_float>& c__my_z, const complex<e_float>& c__my_a)
    {
      return exp(c__my_a * log(c__my_z));
    }

    template<> inline complex<e_float> pow(const e_float& c__my_z, const complex<e_float>& c__my_a)
    {
      return exp(c__my_a * log(c__my_z));
    }

    template<> inline complex<e_float> sin(const complex<e_float>& c__my_z)
    {
      e_float c__my_sin_x  = sin (c__my_z.real());
      e_float c__my_cos_x  = cos (c__my_z.real());
      e_float c__my_sinh_y = sinh(c__my_z.imag());
      e_float c__my_cosh_y = cosh(c__my_z.imag());

      return complex<e_float>(c__my_sin_x * c__my_cosh_y, c__my_cos_x * c__my_sinh_y);
    }

    template<> inline complex<e_float> sinh(const complex<e_float>& c__my_z)
    {
      e_float c__my_sin_y  = sin (c__my_z.imag());
      e_float c__my_cos_y  = cos (c__my_z.imag());
      e_float c__my_sinh_x = sinh(c__my_z.real());
      e_float c__my_cosh_x = cosh(c__my_z.real());

      return complex<e_float>(c__my_cos_y * c__my_sinh_x, c__my_cosh_x * c__my_sin_y);
    }

    template<> inline complex<e_float> sqrt(const complex<e_float>& c__my_z)
    {
      using std::sqrt;

      // Use the following:
      // sqrt(z) = (s, zi / 2s)       for zr >= 0
      //           (|zi| / 2s, +-s)   for zr <  0
      // where s = sqrt{ [ |zr| + sqrt(zr^2 + zi^2) ] / 2 },
      // and the +- sign is the same as the sign of zi.

      const bool c__my_real_part_is_neg(c__my_z.real() < 0U);

      const e_float c__my_real_part_fabs((c__my_real_part_is_neg == false) ? c__my_z.real() : -c__my_z.real());
      const e_float c__my_sqrt_part     (ef::sqrt((c__my_real_part_fabs + abs(c__my_z)) / 2U));

      if(c__my_real_part_is_neg == false)
      {
        return complex<e_float>(c__my_sqrt_part,
                                c__my_z.imag() / (c__my_sqrt_part * 2U));
      }
      else
      {
        const bool c__my_imag_part_is_neg(c__my_z.imag() < 0U);

        const e_float c__my_imag_part_fabs((c__my_imag_part_is_neg == false) ? c__my_z.imag() : -c__my_z.imag());

        return complex<e_float>( c__my_imag_part_fabs / (c__my_sqrt_part * 2U),
                               ((c__my_imag_part_is_neg == false) ? c__my_sqrt_part : -c__my_sqrt_part));
      }
    }

    template<> inline complex<e_float> tan(const complex<e_float>& c__my_z)
    {
      e_float c__my_sin_x  = sin (c__my_z.real());
      e_float c__my_cos_x  = cos (c__my_z.real());
      e_float c__my_sinh_y = sinh(c__my_z.imag());
      e_float c__my_cosh_y = cosh(c__my_z.imag());

      const complex<e_float> c__my_s(c__my_sin_x * c__my_cosh_y,   c__my_cos_x * c__my_sinh_y);
      const complex<e_float> c__my_c(c__my_cos_x * c__my_cosh_y, -(c__my_sin_x * c__my_sinh_y));

      return c__my_s / c__my_c;
    }

    template<> inline complex<e_float> tanh(const complex<e_float>& c__my_z)
    {
      e_float c__my_sin_y  = sin (c__my_z.imag());
      e_float c__my_cos_y  = cos (c__my_z.imag());
      e_float c__my_sinh_x = sinh(c__my_z.real());
      e_float c__my_cosh_x = cosh(c__my_z.real());

      const complex<e_float> c__my_sh(c__my_cos_y * c__my_sinh_x, c__my_cosh_x * c__my_sin_y);
      const complex<e_float> c__my_ch(c__my_cos_y * c__my_cosh_x, c__my_sin_y  * c__my_sinh_x);

      return c__my_sh / c__my_ch;
    }

    // Template specialized I/O stream operators.
    template<typename char_type, typename traits_type>
    std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>& c__my_istream, complex<e_float>& c__my_z)
    {
      // Parse an (extended) complex number of any of the forms u, (u) or (u,v).

      const std::array<std::regex, 3U> c__my_regexes =
      {{
        // A regular expression for an (extended) complex number of the form (u,v).
        std::regex(  std::string("\\({1}")                             // One open parentheses.
                    + std::string("([\\+\\-]{0,1}[0-9]*\\.*[0-9]*)")    // Possible +-, decimal point and digits 0-9.
                    + std::string("([eE]{0,1}[\\+\\-]{0,1}[0-9]*)")     // Possible exponent field.
                    + std::string("\\,{1}")                             // One comma character.
                    + std::string("([\\+\\-]{0,1}[0-9]*\\.*[0-9]*)")    // Possible +-, decimal point and digits 0-9.
                    + std::string("([eE]{0,1}[\\+\\-]{0,1}[0-9]*)")     // Possible exponent field.
                    + std::string("\\){1}")),                           // One close parentheses.

        // A regular expression for an (extended) complex number of the form (u).
        std::regex(  std::string("\\({1}")                             // One open parentheses.
                    + std::string("([\\+\\-]{0,1}[0-9]*\\.*[0-9]*)")    // Possible +-, decimal point and digits 0-9.
                    + std::string("([eE]{0,1}[\\+\\-]{0,1}[0-9]*)")     // Possible exponent field.
                    + std::string("\\){1}")),                           // One close parentheses.

        // A regular expression for an (extended) complex number of the form u.
        std::regex(  std::string("([\\+\\-]{0,1}[0-9]*\\.*[0-9]*)")    // Possible +-, decimal point and digits 0-9.
                    + std::string("([eE]{0,1}[\\+\\-]{0,1}[0-9]*)"))    // Possible exponent field.
      }};

      e_float c__my_real_input(0U);
      e_float c__my_imag_input(0U);

      bool c__my_input_has_error = false;

      std::string c__my_input_str;

      c__my_istream >> c__my_input_str;

      std::match_results<std::string::const_iterator> c__my_mr;

      auto c__my_it_regex_match =
        std::find_if(c__my_regexes.cbegin(),
                     c__my_regexes.cend(),
                     [&c__my_input_str, &c__my_mr](const std::regex& c__my_rx) -> bool
                     {
                       return std::regex_match(c__my_input_str, c__my_mr, c__my_rx);
                     });

      if(c__my_it_regex_match == c__my_regexes.cend())
      {
        // The input does not match any of the regular expressions.
        // Set the error flag and take no other action.

        c__my_input_has_error = true;
      }
      else if(c__my_it_regex_match == c__my_regexes.cbegin())
      {
        // The input matches __the_regexes[0U], corresponding to the form (u,v).
        // This represents a complex number real and imaginary parts.

        // Rule out erroneous match of invalid mantissa or exponent parts.
        const std::string c__my_str1(c__my_mr[1U]);
        const std::string c__my_str2(c__my_mr[2U]);
        const std::string c__my_str3(c__my_mr[3U]);
        const std::string c__my_str4(c__my_mr[4U]);

        const std::string c__my_decimal_digits("0123456789");

        const bool c__my_str1_has_error = ((c__my_str1.length() != std::size_t(0U)) && (c__my_str1.find_first_of(c__my_decimal_digits) == std::string::npos));
        const bool c__my_str2_has_error = ((c__my_str2.length() != std::size_t(0U)) && (c__my_str2.find_first_of(c__my_decimal_digits) == std::string::npos));
        const bool c__my_str3_has_error = ((c__my_str3.length() != std::size_t(0U)) && (c__my_str3.find_first_of(c__my_decimal_digits) == std::string::npos));
        const bool c__my_str4_has_error = ((c__my_str4.length() != std::size_t(0U)) && (c__my_str4.find_first_of(c__my_decimal_digits) == std::string::npos));

        if(c__my_str1_has_error || c__my_str2_has_error || c__my_str3_has_error || c__my_str4_has_error)
        {
          c__my_input_has_error = true;
        }
        else
        {
          // Extract the real part of the complex number.
          std::stringstream c__my_stringstream;

          c__my_stringstream << c__my_mr[1U] << c__my_mr[2U];
          c__my_stringstream >> c__my_real_input;

          c__my_stringstream.str(std::string());
          c__my_stringstream.clear();

          // Extract the imaginary part of the complex number.

          c__my_stringstream << c__my_mr[3U] << c__my_mr[4U];
          c__my_stringstream >> c__my_imag_input;
        }
      }
      else if(   (c__my_it_regex_match == (c__my_regexes.cbegin() + 1U))
              || (c__my_it_regex_match == (c__my_regexes.cbegin() + 2U)))
      {
        // The input matches the_regexes[1U] or the_regexes[2U],
        // corresponding to either of the forms (u) or u.
        // This represents a complex number having only
        // a pure real part.

        // Rule out erroneous match of invalid mantissa or exponent parts.
        const std::string c__my_str1(c__my_mr[1U]);
        const std::string c__my_str2(c__my_mr[2U]);

        const std::string c__my_decimal_digits("0123456789");

        if(   ((c__my_str1.length() != std::size_t(0U)) && (c__my_str1.find_first_of(c__my_decimal_digits) == std::string::npos))
           || ((c__my_str2.length() != std::size_t(0U)) && (c__my_str2.find_first_of(c__my_decimal_digits) == std::string::npos)))
        {
          c__my_input_has_error = true;
        }
        else
        {
          // Extract the real part of the complex number.
          std::stringstream c__my_stringstream;

          c__my_stringstream << c__my_mr[1U] << c__my_mr[2U];
          c__my_stringstream >> c__my_real_input;

          c__my_imag_input = T(0U);
        }
      }

      if(c__my_input_has_error)
      {
        // Error case: Restore the characters in the input stream
        // and set the fail bit in the input stream.
        std::for_each(c__my_input_str.cbegin(),
                      c__my_input_str.cend(),
                      [&c__my_istream](const char& c__my_c)
                      {
                        c__my_istream.putback(c__my_c);
                      });

        c__my_istream.setstate(std::ios_base::failbit);
      }
      else
      {
        c__my_z = complex<T>(c__my_real_input, c__my_imag_input);
      }

      return c__my_istream;
    }

    template<typename char_type, typename traits_type>
    std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>& c__my_ostream, const complex<e_float>& c__my_z)
    {
      std::basic_ostringstream<char_type, traits_type> c__my_tmp_ostream;

      c__my_tmp_ostream.flags    (c__my_ostream.flags());
      c__my_tmp_ostream.imbue    (c__my_ostream.getloc());
      c__my_tmp_ostream.precision(c__my_ostream.precision());

      c__my_tmp_ostream << '('
                       << c__my_z.real()
                       << ','
                       << c__my_z.imag()
                       << ')';

      return (c__my_ostream << c__my_tmp_ostream.str());
    }

    #if defined(_MSC_VER) && (_MSC_VER <= 1800)
    #else
    inline complex<float>       operator""if(long double c__my_imag_literal)        { return complex<float>      {0.0F, static_cast<float>      (c__my_imag_literal)}; }
    inline complex<double>      operator""i (long double c__my_imag_literal)        { return complex<double>     {0.0,  static_cast<double>     (c__my_imag_literal)}; }
    inline complex<long double> operator""il(long double c__my_imag_literal)        { return complex<long double>{0.0L, static_cast<long double>(c__my_imag_literal)}; }

    inline complex<float>       operator""if(unsigned long long c__my_imag_literal) { return complex<float>      {0.0F, static_cast<float>      (c__my_imag_literal)}; }
    inline complex<double>      operator""i (unsigned long long c__my_imag_literal) { return complex<double>     {0.0,  static_cast<double>     (c__my_imag_literal)}; }
    inline complex<long double> operator""il(unsigned long long c__my_imag_literal) { return complex<long double>{0.0L, static_cast<long double>(c__my_imag_literal)}; }
    #endif
  } // namespace ef

#endif // E_FLOAT_COMPLEX_2017_08_23_HPP_
