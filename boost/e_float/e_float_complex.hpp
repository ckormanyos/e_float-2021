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

      complex(const value_type& __my_x = value_type(),
              const value_type& __my_y = value_type()) : __my_re(__my_x),
                                                         __my_im(__my_y) { }

      complex(const complex& __my_z) : __my_re(__my_z.real()),
                                       __my_im(__my_z.imag()) { }

      template<typename X>
      complex(const complex<X>& __my_z) : __my_re(static_cast<value_type>(__my_z.real())),
                                          __my_im(static_cast<value_type>(__my_z.imag())) { }

      value_type real() const { return __my_re; }
      value_type imag() const { return __my_im; }

      void real(value_type __my_x) { __my_re = __my_x; }
      void imag(value_type __my_y) { __my_im = __my_y; }

      complex& operator=(const value_type& __my_other_x)
      {
        __my_re = __my_other_x;
        __my_im = value_type(0U);

        return *this;
      }

      complex& operator+=(const value_type& __my_x)
      {
        __my_re += __my_x;

        return *this;
      }

      complex& operator-=(const value_type& __my_x)
      {
        __my_re -= __my_x;

        return *this;
      }

      complex& operator*=(const value_type& __my_x)
      {
        __my_re *= __my_x;
        __my_im *= __my_x;

        return *this;
      }

      complex& operator/=(const value_type& __my_x)
      {
        __my_re /= __my_x;
        __my_im /= __my_x;

        return *this;
      }

      complex& operator=(const complex& __my_other_z)
      {
        if(this != &__my_other_z)
        {
          __my_re = __my_other_z.__my_re;
          __my_im = __my_other_z.__my_im;
        }

        return *this;
      }

      template<typename X>
      complex& operator=(const complex<X>& __my_other_z)
      {
        __my_re = static_cast<value_type>(__my_other_z.__my_re);
        __my_im = static_cast<value_type>(__my_other_z.__my_im);

        return *this;
      }

      template<typename X>
      complex& operator+=(const complex<X>& __my_z)
      {
        __my_re += static_cast<value_type>(__my_z.__my_re);
        __my_im += static_cast<value_type>(__my_z.__my_im);

        return *this;
      }

      template<typename X>
      complex& operator-=(const complex<X>& __my_z)
      {
        if(this == &__my_z)
        {
          __my_re = value_type(0);
          __my_im = value_type(0);
        }
        else
        {
          __my_re -= static_cast<value_type>(__my_z.__my_re);
          __my_im -= static_cast<value_type>(__my_z.__my_im);
        }

        return *this;
      }

      template<typename X>
      complex& operator*=(const complex<X>& __my_z)
      {
        const value_type __tmp_re(__my_re);

        if(this == &__my_z)
        {
          __my_re = (__tmp_re * __tmp_re) - (__my_im * __my_im);
          __my_im = (__tmp_re * __my_im) * 2U;
        }
        else
        {
          __my_re = (__tmp_re * __my_z.__my_re) - (__my_im * __my_z.__my_im);
          __my_im = (__tmp_re * __my_z.__my_im) + (__my_im * __my_z.__my_re);
        }

        return *this;
      }

      template<typename X>
      complex& operator/=(const complex<X>& __my_z)
      {
        if(this == &__my_z)
        {
          __my_re = value_type(1);
          __my_im = value_type(0);
        }
        else
        {
          if(fabs(__my_z.real()) < fabs(__my_z.imag()))
          {
            const value_type __my_c_over_d = __my_z.real() / __my_z.imag();

            const value_type __my_denominator = (__my_z.real() * __my_c_over_d) + __my_z.imag();

            const value_type __my_tmp_re(__my_re);

            __my_re = ((__my_tmp_re * __my_c_over_d) + __my_im)     / __my_denominator;
            __my_im = ((__my_im     * __my_c_over_d) - __my_tmp_re) / __my_denominator;
          }
          else
          {
            const value_type __my_d_over_c = __my_z.imag() / __my_z.real();

            const value_type __my_denominator = (__my_z.imag() * __my_d_over_c) + __my_z.real();

            const value_type __my_tmp_re(__my_re);

            __my_re = (( __my_im     * __my_d_over_c) + __my_tmp_re) / __my_denominator;
            __my_im = ((-__my_tmp_re * __my_d_over_c) + __my_im)     / __my_denominator;
          }
        }

        return *this;
      }

    private:
      value_type __my_re;
      value_type __my_im;
    };


    // Specialization of class template ef::complex<float>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.3.

    template<>
    class complex<float>
    {
    public:
      typedef float value_type;

      complex(float __my_x = float(),
              float __my_y = float()) : __my_re(__my_x),
                                        __my_im(__my_y) { }

      explicit complex(const complex<double>&);
      explicit complex(const complex<long double>&);

      float real() const { return __my_re; }
      float imag() const { return __my_im; }

      void real(float __my_x) { __my_re = __my_x; }
      void imag(float __my_y) { __my_im = __my_y; }

      complex& operator=(float __my_other_x)
      {
        __my_re = __my_other_x;
        __my_im = 0.0F;

        return *this;
      }

      complex& operator+=(float __my_x)
      {
        __my_re += __my_x;

        return *this;
      }

      complex& operator-=(float __my_x)
      {
        __my_re -= __my_x;

        return *this;
      }

      complex& operator*=(float __my_x)
      {
        __my_re *= __my_x;
        __my_im *= __my_x;

        return *this;
      }

      complex& operator/=(float __my_x)
      {
        __my_re /= __my_x;
        __my_im /= __my_x;

        return *this;
      }

      complex& operator=(const complex& __my_other_z)
      {
        if(this != &__my_other_z)
        {
          __my_re = __my_other_z.__my_re;
          __my_im = __my_other_z.__my_im;
        }

        return *this;
      }

      template<typename X>
      complex& operator=(const complex<X>& __my_other_z)
      {
        __my_re = static_cast<float>(__my_other_z.__my_re);
        __my_im = static_cast<float>(__my_other_z.__my_im);

        return *this;
      }

      template<typename X>
      complex& operator+=(const complex<X>& __my_z)
      {
        __my_re += static_cast<float>(__my_z.__my_re);
        __my_im += static_cast<float>(__my_z.__my_im);

        return *this;
      }

      template<typename X>
      complex& operator-=(const complex<X>& __my_z)
      {
        __my_re -= static_cast<float>(__my_z.__my_re);
        __my_im -= static_cast<float>(__my_z.__my_im);

        return *this;
      }

      template<typename X>
      complex& operator*=(const complex<X>& __my_z)
      {
        const float __tmp_re(__my_re);

        if(this == &__my_z)
        {
          __my_re = (__tmp_re * __tmp_re) - (__my_im * __my_im);
          __my_im = (__tmp_re * __my_im) * 2.0F;
        }
        else
        {
          __my_re = (__tmp_re * __my_z.__my_re) - (__my_im * __my_z.__my_im);
          __my_im = (__tmp_re * __my_z.__my_im) + (__my_im * __my_z.__my_re);
        }

        return *this;
      }

      template<typename X>
      complex& operator/=(const complex<X>& __my_z)
      {
        if(this == &__my_z)
        {
          __my_re = 1.0F;
          __my_im = 0.0F;
        }
        else
        {
          using std::fabs;

          if(fabs(__my_z.real()) < fabs(__my_z.imag()))
          {
            const float __my_c_over_d = __my_z.real() / __my_z.imag();

            const float __my_denominator = (__my_z.real() * __my_c_over_d) + __my_z.imag();

            const float __my_tmp_re(__my_re);

            real(((__my_tmp_re * __my_c_over_d) + __my_im)     / __my_denominator);
            imag(((__my_im     * __my_c_over_d) - __my_tmp_re) / __my_denominator);
          }
          else
          {
            const float __my_d_over_c = __my_z.imag() / __my_z.real();

            const float __my_denominator = (__my_z.imag() * __my_d_over_c) + __my_z.real();

            const float __my_tmp_re(__my_re);

            real((( __my_im     * __my_d_over_c) + __my_tmp_re) / __my_denominator);
            imag(((-__my_tmp_re * __my_d_over_c) + __my_im)     / __my_denominator);
          }
        }

        return *this;
      }

    private:
      float __my_re;
      float __my_im;
    };


    // Specialization of class template ef::complex<double>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.3.

    template<>
    class complex<double>
    {
    public:
      typedef double value_type;

      complex(double __my_x = double(),
              double __my_y = double()) : __my_re(__my_x),
                                          __my_im(__my_y) { }

      complex(const complex<float>& __my_f) : __my_re(double(__my_f.real())),
                                              __my_im(double(__my_f.imag())) { }

      explicit complex(const complex<long double>&);

      double real() const { return __my_re; }
      double imag() const { return __my_im; }

      void real(double __my_x) { __my_re = __my_x; }
      void imag(double __my_y) { __my_im = __my_y; }

      complex& operator=(double __my_other_x)
      {
        __my_re = __my_other_x;
        __my_im = 0.0;

        return *this;
      }

      complex& operator+=(double __my_x)
      {
        __my_re += __my_x;

        return *this;
      }

      complex& operator-=(double __my_x)
      {
        __my_re -= __my_x;

        return *this;
      }

      complex& operator*=(double __my_x)
      {
        __my_re *= __my_x;
        __my_im *= __my_x;

        return *this;
      }

      complex& operator/=(double __my_x)
      {
        __my_re /= __my_x;
        __my_im /= __my_x;

        return *this;
      }

      complex& operator=(const complex& __my_other_z)
      {
        if(this != &__my_other_z)
        {
          __my_re = __my_other_z.__my_re;
          __my_im = __my_other_z.__my_im;
        }

        return *this;
      }

      template<typename X>
      complex& operator=(const complex<X>& __my_other_z)
      {
        __my_re = static_cast<double>(__my_other_z.__my_re);
        __my_im = static_cast<double>(__my_other_z.__my_im);

        return *this;
      }

      template<typename X>
      complex& operator+=(const complex<X>& __my_z)
      {
        __my_re += static_cast<double>(__my_z.__my_re);
        __my_im += static_cast<double>(__my_z.__my_im);

        return *this;
      }

      template<typename X>
      complex& operator-=(const complex<X>& __my_z)
      {
        __my_re -= static_cast<double>(__my_z.__my_re);
        __my_im -= static_cast<double>(__my_z.__my_im);

        return *this;
      }

      template<typename X>
      complex& operator*=(const complex<X>& __my_z)
      {
        const double __tmp_re(__my_re);

        if(this == &__my_z)
        {
          __my_re = (__tmp_re * __tmp_re) - (__my_im * __my_im);
          __my_im = (__tmp_re * __my_im) * 2.0;
        }
        else
        {
          __my_re = (__tmp_re * __my_z.__my_re) - (__my_im * __my_z.__my_im);
          __my_im = (__tmp_re * __my_z.__my_im) + (__my_im * __my_z.__my_re);
        }

        return *this;
      }

      template<typename X>
      complex& operator/=(const complex<X>& __my_z)
      {
        if(this == &__my_z)
        {
          __my_re = 1.0;
          __my_im = 0.0;
        }
        else
        {
          using std::fabs;

          if(fabs(__my_z.real()) < fabs(__my_z.imag()))
          {
            const double __my_c_over_d = __my_z.real() / __my_z.imag();

            const double __my_denominator = (__my_z.real() * __my_c_over_d) + __my_z.imag();

            const double __my_tmp_re(__my_re);

            real(((__my_tmp_re * __my_c_over_d) + __my_im)     / __my_denominator);
            imag(((__my_im     * __my_c_over_d) - __my_tmp_re) / __my_denominator);
          }
          else
          {
            const double __my_d_over_c = __my_z.imag() / __my_z.real();

            const double __my_denominator = (__my_z.imag() * __my_d_over_c) + __my_z.real();

            const double __my_tmp_re(__my_re);

            real((( __my_im     * __my_d_over_c) + __my_tmp_re) / __my_denominator);
            imag(((-__my_tmp_re * __my_d_over_c) + __my_im)     / __my_denominator);
          }
        }

        return *this;
      }

    private:
      double __my_re;
      double __my_im;
    };

    // Specialization of class template extended_complex::complex<long double>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.3.

    template<>
    class complex<long double>
    {
    public:
      typedef long double value_type;

      complex(long double __my_x = (long double()),
              long double __my_y = (long double())) : __my_re(__my_x),
                                                      __my_im(__my_y) { }

      complex(const complex<float>& __my_f) : __my_re(static_cast<long double>(__my_f.real())),
                                              __my_im(static_cast<long double>(__my_f.imag())) { }

      complex(const complex<double>& __my_d) : __my_re(static_cast<long double>(__my_d.real())),
                                               __my_im(static_cast<long double>(__my_d.imag())) { }

      long double real() const { return __my_re; }
      long double imag() const { return __my_im; }

      void real(long double __my_x) { __my_re = __my_x; }
      void imag(long double __my_y) { __my_im = __my_y; }

      complex& operator=(long double __my_other_x)
      {
        __my_re = __my_other_x;
        __my_im = 0.0L;

        return *this;
      }

      complex& operator+=(long double __my_x)
      {
        __my_re += __my_x;

        return *this;
      }

      complex& operator-=(long double __my_x)
      {
        __my_re -= __my_x;

        return *this;
      }

      complex& operator*=(long double __my_x)
      {
        __my_re *= __my_x;
        __my_im *= __my_x;

        return *this;
      }

      complex& operator/=(long double __my_x)
      {
        __my_re /= __my_x;
        __my_im /= __my_x;

        return *this;
      }

      complex& operator=(const complex& __my_other_z)
      {
        if(this != &__my_other_z)
        {
          __my_re = __my_other_z.__my_re;
          __my_im = __my_other_z.__my_im;
        }

        return *this;
      }

      template<typename X>
      complex& operator=(const complex<X>& __my_other_z)
      {
        __my_re = static_cast<long double>(__my_other_z.__my_re);
        __my_im = static_cast<long double>(__my_other_z.__my_im);

        return *this;
      }

      template<typename X>
      complex& operator+=(const complex<X>& __my_z)
      {
        __my_re += static_cast<long double>(__my_z.__my_re);
        __my_im += static_cast<long double>(__my_z.__my_im);

        return *this;
      }

      template<typename X>
      complex& operator-=(const complex<X>& __my_z)
      {
        __my_re -= static_cast<long double>(__my_z.__my_re);
        __my_im -= static_cast<long double>(__my_z.__my_im);

        return *this;
      }

      template<typename X>
      complex& operator*=(const complex<X>& __my_z)
      {
        const long double __tmp_re(__my_re);

        if(this == &__my_z)
        {
          __my_re = (__tmp_re * __tmp_re) - (__my_im * __my_im);
          __my_im = (__tmp_re * __my_im) * 2.0L;
        }
        else
        {
          __my_re = (__tmp_re * __my_z.__my_re) - (__my_im * __my_z.__my_im);
          __my_im = (__tmp_re * __my_z.__my_im) + (__my_im * __my_z.__my_re);
        }

        return *this;
      }

      template<typename X>
      complex& operator/=(const complex<X>& __my_z)
      {
        if(this == &__my_z)
        {
          __my_re = 1.0L;
          __my_im = 0.0L;
        }
        else
        {
          using std::fabs;

          if(fabs(__my_z.real()) < fabs(__my_z.imag()))
          {
            const long double __my_c_over_d = __my_z.real() / __my_z.imag();

            const long double __my_denominator = (__my_z.real() * __my_c_over_d) + __my_z.imag();

            const long double __my_tmp_re(__my_re);

            real(((__my_tmp_re * __my_c_over_d) + __my_im)     / __my_denominator);
            imag(((__my_im     * __my_c_over_d) - __my_tmp_re) / __my_denominator);
          }
          else
          {
            const long double __my_d_over_c = __my_z.imag() / __my_z.real();

            const long double __my_denominator = (__my_z.imag() * __my_d_over_c) + __my_z.real();

            const long double __my_tmp_re(__my_re);

            real((( __my_im     * __my_d_over_c) + __my_tmp_re) / __my_denominator);
            imag(((-__my_tmp_re * __my_d_over_c) + __my_im)     / __my_denominator);
          }
        }

        return *this;
      }

    private:
      long double __my_re;
      long double __my_im;
    };

    // These constructors are located here because they need to be
    // implemented after the template specializations have been declared.

    inline complex<float >::complex(const complex<double>&      __my_d) : __my_re(float (__my_d.real())), __my_im(float (__my_d.imag())) { }
    inline complex<float >::complex(const complex<long double>& __my_l) : __my_re(float (__my_l.real())), __my_im(float (__my_l.imag())) { }
    inline complex<double>::complex(const complex<long double>& __my_l) : __my_re(double(__my_l.real())), __my_im(double(__my_l.imag())) { }

    // Non-member operations for ef::complex<T>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.6.

    // Unary +/- operators.
    template<typename T> complex<T> operator+(const complex<T>& __my_u) { return __my_u; }
    template<typename T> complex<T> operator-(const complex<T>& __my_u) { return complex<T>(-__my_u.real(), -__my_u.imag()); }

    // Global add, sub, mul, div operators.
    template<typename T> complex<T> operator+(const complex<T>& __my_u, const complex<T>& __my_v) { return complex<T>(__my_u.real() + __my_v.real(), __my_u.imag() + __my_v.imag()); }
    template<typename T> complex<T> operator-(const complex<T>& __my_u, const complex<T>& __my_v) { return complex<T>(__my_u.real() - __my_v.real(), __my_u.imag() - __my_v.imag()); }

    template<typename T> complex<T> operator*(const complex<T>& __my_u, const complex<T>& __my_v)
    {
      return complex<T>((__my_u.real() * __my_v.real()) - (__my_u.imag() * __my_v.imag()),
                        (__my_u.real() * __my_v.imag()) + (__my_u.imag() * __my_v.real()));
    }

    template<typename T> complex<T> operator/(const complex<T>& __my_u, const complex<T>& __my_v)
    {
      using std::fabs;

      complex<T> __my_result;

      if(fabs(__my_v.real()) < fabs(__my_v.imag()))
      {
        const T __my_c_over_d = __my_v.real() / __my_v.imag();

        const T __my_denominator = (__my_v.real() * __my_c_over_d) + __my_v.imag();

        __my_result = complex<T>(((__my_u.real() * __my_c_over_d) + __my_u.imag()) / __my_denominator,
                                 ((__my_u.imag() * __my_c_over_d) - __my_u.real()) / __my_denominator);
      }
      else
      {
        const T __my_d_over_c = __my_v.imag() / __my_v.real();

        const T __my_denominator = (__my_v.imag() * __my_d_over_c) + __my_v.real();

        __my_result = complex<T>((( __my_u.imag() * __my_d_over_c) + __my_u.real()) / __my_denominator,
                                 ((-__my_u.real() * __my_d_over_c) + __my_u.imag()) / __my_denominator);
      }

      return __my_result;
    }

    template<typename T> complex<T> operator+(const complex<T>& __my_u, const T& __my_v)  { return complex<T>(__my_u.real() + __my_v, __my_u.imag()); }
    template<typename T> complex<T> operator-(const complex<T>& __my_u, const T& __my_v)  { return complex<T>(__my_u.real() - __my_v, __my_u.imag()); }
    template<typename T> complex<T> operator*(const complex<T>& __my_u, const T& __my_v)  { return complex<T>(__my_u.real() * __my_v, __my_u.imag() * __my_v); }
    template<typename T> complex<T> operator/(const complex<T>& __my_u, const T& __my_v)  { return complex<T>(__my_u.real() / __my_v, __my_u.imag() / __my_v); }

    template<typename T> complex<T> operator+(const T& __my_u, const complex<T>& __my_v) { return complex<T>(__my_u + __my_v.real(), __my_v.imag()); }
    template<typename T> complex<T> operator-(const T& __my_u, const complex<T>& __my_v) { return complex<T>(__my_u - __my_v.real(), -__my_v.imag()); }
    template<typename T> complex<T> operator*(const T& __my_u, const complex<T>& __my_v) { return complex<T>(__my_u * __my_v.real(), __my_u * __my_v.imag()); }

    template<typename T> complex<T> operator/(const T& __my_u, const complex<T>& __my_v)
    {
      using std::fabs;

      complex<T> __my_result;

      if(fabs(__my_v.real()) < fabs(__my_v.imag()))
      {
        const T __my_c_over_d = __my_v.real() / __my_v.imag();

        const T __my_denominator = (__my_v.real() * __my_c_over_d) + __my_v.imag();

        __my_result = complex<T>(( __my_u * __my_c_over_d) / __my_denominator,
                                  -__my_u                  / __my_denominator);
      }
      else
      {
        const T __my_d_over_c = __my_v.imag() / __my_v.real();

        const T __my_denominator = (__my_v.imag() * __my_d_over_c) + __my_v.real();

        __my_result = complex<T>(  __my_u                  / __my_denominator,
                                 (-__my_u * __my_d_over_c) / __my_denominator);
      }

      return __my_result;
    }

    // Equality and inequality operators.
    template<typename T> bool operator==(const complex<T>& __my_u, const complex<T>& __my_v) { return ((__my_u.real() == __my_v.real()) && (__my_u.imag() == __my_v.imag())); }
    template<typename T> bool operator==(const complex<T>& __my_u, const T&          __my_v) { return ((__my_u.real() == __my_v)        && (__my_u.imag() == T(0))); }
    template<typename T> bool operator==(const T&          __my_u, const complex<T>& __my_v) { return ((__my_u == __my_v.real())        && (__my_v.imag() == T(0))); }

    template<typename T> bool operator!=(const complex<T>& __my_u, const complex<T>& __my_v) { return ((__my_u.real() != __my_v.real()) || (__my_u.imag() != __my_v.imag())); }
    template<typename T> bool operator!=(const complex<T>& __my_u, const T&          __my_v) { return ((__my_u.real() != __my_v)        || (__my_u.imag() != T(0))); }
    template<typename T> bool operator!=(const T&          __my_u, const complex<T>& __my_v) { return ((__my_u != __my_v.real())        || (__my_v.imag() != T(0))); }

    // I/O stream operators.
    template<typename T, typename char_type, typename traits_type>
    std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>& __my_istream, complex<T>& __my_z)
    {
      // Parse an (extended) complex number of any of the forms u, (u) or (u,v).

      const std::array<std::regex, 3U> __my_regexes =
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

      T __my_real_input(0U);
      T __my_imag_input(0U);

      bool __my_input_has_error = false;

      std::string __my_input_str;

      __my_istream >> __my_input_str;

      std::match_results<std::string::const_iterator> __my_mr;

      auto __my_it_regex_match =
        std::find_if(__my_regexes.cbegin(),
                     __my_regexes.cend(),
                     [&__my_input_str, &__my_mr](const std::regex& __my_rx) -> bool
                     {
                       return std::regex_match(__my_input_str, __my_mr, __my_rx);
                     });

      if(__my_it_regex_match == __my_regexes.cend())
      {
        // The input does not match any of the regular expressions.
        // Set the error flag and take no other action.

        __my_input_has_error = true;
      }
      else if(__my_it_regex_match == __my_regexes.cbegin())
      {
        // The input matches __the_regexes[0U], corresponding to the form (u,v).
        // This represents a complex number real and imaginary parts.

        // Rule out erroneous match of invalid mantissa or exponent parts.
        const std::string __my_str1(__my_mr[1U]);
        const std::string __my_str2(__my_mr[2U]);
        const std::string __my_str3(__my_mr[3U]);
        const std::string __my_str4(__my_mr[4U]);

        const std::string __my_decimal_digits("0123456789");

        const bool __my_str1_has_error = ((__my_str1.length() != std::size_t(0U)) && (__my_str1.find_first_of(__my_decimal_digits) == std::string::npos));
        const bool __my_str2_has_error = ((__my_str2.length() != std::size_t(0U)) && (__my_str2.find_first_of(__my_decimal_digits) == std::string::npos));
        const bool __my_str3_has_error = ((__my_str3.length() != std::size_t(0U)) && (__my_str3.find_first_of(__my_decimal_digits) == std::string::npos));
        const bool __my_str4_has_error = ((__my_str4.length() != std::size_t(0U)) && (__my_str4.find_first_of(__my_decimal_digits) == std::string::npos));

        if(__my_str1_has_error || __my_str2_has_error || __my_str3_has_error || __my_str4_has_error)
        {
          __my_input_has_error = true;
        }
        else
        {
          // Extract the real part of the complex number.
          {
            std::stringstream __my_stringstream;

            __my_stringstream << __my_mr[1U] << __my_mr[2U];
            __my_stringstream >> __my_real_input;
          }

          // Extract the imaginary part of the complex number.
          {
            std::stringstream __my_stringstream;

            __my_stringstream << __my_mr[3U] << __my_mr[4U];
            __my_stringstream >> __my_imag_input;
          }
        }
      }
      else if(   (__my_it_regex_match == (__my_regexes.cbegin() + 1U))
              || (__my_it_regex_match == (__my_regexes.cbegin() + 2U)))
      {
        // The input matches the_regexes[1U] or the_regexes[2U],
        // corresponding to either of the forms (u) or u.
        // This represents a pure real complex number.

        // Rule out erroneous match of invalid mantissa or exponent parts.
        const std::string __my_str1(__my_mr[1U]);
        const std::string __my_str2(__my_mr[2U]);

        const std::string __my_decimal_digits("0123456789");

        if(   ((__my_str1.length() != std::size_t(0U)) && (__my_str1.find_first_of(__my_decimal_digits) == std::string::npos))
           || ((__my_str2.length() != std::size_t(0U)) && (__my_str2.find_first_of(__my_decimal_digits) == std::string::npos)))
        {
          __my_input_has_error = true;
        }
        else
        {
          // Extract the real part of the complex number.
          std::stringstream __my_stringstream;

          __my_stringstream << __my_mr[1U] << __my_mr[2U];
          __my_stringstream >> __my_real_input;

          __my_imag_input = T(0U);
        }
      }

      if(__my_input_has_error)
      {
        // Error case: Restore the characters in the input stream
        // and set the fail bit in the input stream.
        std::for_each(__my_input_str.cbegin(),
                      __my_input_str.cend(),
                      [&__my_istream](const char& __my_c)
                      {
                        __my_istream.putback(__my_c);
                      });

        __my_istream.setstate(std::ios_base::failbit);
      }
      else
      {
        __my_z = complex<T>(__my_real_input, __my_imag_input);
      }

      return __my_istream;
    }

    template<class T, class char_type, class traits_type>
    std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>& __my_ostream, const complex<T>& __my_z)
    {
      std::basic_ostringstream<char_type, traits_type> __my_tmp_ostream;

      __my_tmp_ostream.flags    (__my_ostream.flags());
      __my_tmp_ostream.imbue    (__my_ostream.getloc());
      __my_tmp_ostream.precision(__my_ostream.precision());

      __my_tmp_ostream << '('
                       << __my_z.real()
                       << ','
                       << __my_z.imag()
                       << ')';

      return (__my_ostream << __my_tmp_ostream.str());
    }

    // Value operations for ef::complex<T>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.7.

    template<typename T> T real(const complex<T>& __my_z) { return __my_z.real(); }
    template<typename T> T imag(const complex<T>& __my_z) { return __my_z.imag(); }

    template<typename T> T abs (const complex<T>& __my_z) { using std::sqrt;  return sqrt(norm(__my_z)); }
    template<typename T> T arg (const complex<T>& __my_z) { using std::atan2; return atan2(__my_z.imag(), __my_z.real()); }

    template<typename T> T norm(const complex<T>& __my_z)
    {
      using std::fabs;

      T __my_result;

      if(fabs(__my_z.real()) < fabs(__my_z.imag()))
      {
        const T __my_a_over_b = __my_z.real() / __my_z.imag();

        __my_result = (__my_z.imag() * __my_z.imag()) * (T(1U) + (__my_a_over_b * __my_a_over_b));
      }
      else
      {
        const T __my_b_over_a = __my_z.imag() / __my_z.real();

        __my_result = (__my_z.real() * __my_z.real()) * (T(1U) + (__my_b_over_a * __my_b_over_a));
      }

      return __my_result;
    }

    template<typename T> complex<T> conj(const complex<T>& __my_z)
    {
      return complex<T>(-__my_z.imag(), __my_z.real());
    }

    template<typename T> complex<T> proj(const complex<T>& __my_z)
    {
      const T __denominator_half((norm(__my_z) + T(1U)) / 2U);

      return std::complex<T>(__my_z.real() / __denominator_half,
                             __my_z.imag() / __denominator_half);
    }

    template<typename T> complex<T> polar(const T& __my_rho, const T& __my_theta)
    {
      using std::cos;
      using std::sin;

      return complex<T>(__my_rho * cos(__my_theta), __my_rho * sin(__my_theta));
    }

    // Elementary transcendental functions for ef::complex<T>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.8.

    template<typename T> complex<T> acos(const complex<T>& __my_z)
    {
      using std::asin;

      return T(asin(T(1U))) - asin(__my_z);
    }

    template<typename T> complex<T> asin(const complex<T>& __my_z)
    {
      return -conj(log(conj(__my_z) + sqrt(T(1U) - (__my_z * __my_z))));
    }

    template<typename T> complex<T> atan(const complex<T>& __my_z)
    {
      const complex<T> __z_conj = conj(__my_z);

      complex<T> __result = conj(log(T(1) - __z_conj) - log(T(1) + __z_conj));

      __result.real(__result.real() / 2U);
      __result.imag(__result.imag() / 2U);

      return __result;
    }

    template<typename T> complex<T> acosh(const complex<T>& __my_z)
    {
      const complex<T> __zp(__my_z.real() + T(1U), __my_z.imag());
      const complex<T> __zm(__my_z.real() - T(1U), __my_z.imag());

      return log(__my_z + (__zp * sqrt(__zm / __zp)));
    }

    template<typename T> complex<T> asinh(const complex<T>& __my_z)
    {
      return log(__my_z + sqrt(T(1U) + (__my_z * __my_z)));
    }

    template<typename T> complex<T> atanh(const complex<T>& __my_z)
    {
      complex<T> __result = (log(T(1U) + __my_z) - log(T(1U) - __my_z));

      __result.real(__result.real() / 2U);
      __result.imag(__result.imag() / 2U);

      return __result;
    }

    template<typename T> complex<T> cos(const complex<T>& __my_z)
    {
      using std::cos;
      using std::cosh;
      using std::sin;
      using std::sinh;

      return complex<T>(   cos(__my_z.real()) * cosh(__my_z.imag()),
                        - (sin(__my_z.real()) * sinh(__my_z.imag())));
    }

    template<typename T> complex<T> cosh(const complex<T>& __my_z)
    {
      using std::cos;
      using std::cosh;
      using std::sin;
      using std::sinh;

      return complex<T>(cos(__my_z.imag()) * cosh(__my_z.real()),
                        sin(__my_z.imag()) * sinh(__my_z.real()));
    }

    template<typename T> complex<T> exp(const complex<T>& __my_z)
    {
      using std::cos;
      using std::exp;
      using std::sin;

      return complex<T>(cos(__my_z.imag()), sin(__my_z.imag())) * T(exp(__my_z.real()));
    }

    template<typename T> complex<T> log(const complex<T>& __my_z)
    {
      using std::atan2;
      using std::log;

      const T __my_real_part(log(norm(__my_z)) / 2U);
      const T __my_imag_part(atan2(__my_z.imag(), __my_z.real()));

      return complex<T>(__my_real_part, __my_imag_part);
    }

    template<typename T> complex<T> log10(const complex<T>& __my_z)
    {
      using std::log;

      return log(__my_z) / T(log(T(10)));
    }

    template<typename T> complex<T> pow(const complex<T>& __my_z, int __my_pn)
    {
      if     (__my_pn <  0) { return  T(1U) / pow(__my_z, -__my_pn); }
      else if(__my_pn == 0) { return  complex<T>(T(1U)); }
      else if(__my_pn == 1) { return  __my_z; }
      else if(__my_pn == 2) { return  __my_z * __my_z; }
      else if(__my_pn == 3) { return (__my_z * __my_z) * __my_z; }
      else if(__my_pn == 4) { const complex<T> __my_z2(__my_z * __my_z); return (__my_z2 * __my_z2); }
      else
      {
        // The variable xn stores the binary powers of __my_z.
        complex<T> __my_result(((__my_pn % 2U) != 0U) ? __my_z : complex<T>(T(1U)));
        complex<T> __my_xn      (__my_z);

        unsigned int __my_p2 = static_cast<unsigned int>(__my_pn);

        while((__my_p2 /= 2U) != 0U)
        {
          // Square xn for each binary power.
          __my_xn *= __my_xn;

          const bool __my_p2_has_binary_power = ((__my_p2 % 2U) != 0U);

          if(__my_p2_has_binary_power)
          {
            // Multiply the result with each binary power contained in the exponent.
            __my_result *= __my_xn;
          }
        }

        return __my_result;
      }
    }

    template<typename T> complex<T> pow(const complex<T>& __my_z, const T& __my_a)
    {
      return exp(__my_a * log(__my_z));
    }

    template<typename T> complex<T> pow(const complex<T>& __my_z, const complex<T>& __my_a)
    {
      return exp(__my_a * log(__my_z));
    }

    template<typename T> complex<T> pow(const T& __my_z, const complex<T>& __my_a)
    {
      using std::log;

      return exp(__my_a * T(log(__my_z)));
    }

    template<typename T> complex<T> sin(const complex<T>& __my_z)
    {
      using std::cos;
      using std::cosh;
      using std::sin;
      using std::sinh;

      return complex<T>(sin(__my_z.real()) * cosh(__my_z.imag()),
                        cos(__my_z.real()) * sinh(__my_z.imag()));
    }

    template<typename T> complex<T> sinh(const complex<T>& __my_z)
    {
      using std::cos;
      using std::cosh;
      using std::sin;
      using std::sinh;

      return complex<T>(cos (__my_z.imag()) * sinh(__my_z.real()),
                        cosh(__my_z.real()) * sin (__my_z.imag()));
    }

    template<typename T> complex<T> sqrt(const complex<T>& __my_z)
    {
      using std::fabs;
      using std::sqrt;

      // Use the following:
      // sqrt(z) = (s, zi / 2s)       for zr >= 0
      //           (|zi| / 2s, +-s)   for zr <  0
      // where s = sqrt{ [ |zr| + sqrt(zr^2 + zi^2) ] / 2 },
      // and the +- sign is the same as the sign of zi.

      const bool __real_part_is_neg(__my_z.real() < T(0U));
      const T    __real_part_fabs  ((__real_part_is_neg == false) ? __my_z.real() : -__my_z.real());
      const T    __s_part          (sqrt((__real_part_fabs + abs(__my_z)) / 2U));

      if(__real_part_is_neg == false)
      {
        return complex<T>(__s_part,
                          __my_z.imag() / (__s_part * 2U));
      }
      else
      {
        const bool __imag_part_is_neg(__my_z.imag() < T(0U));
        const T    __imag_part_fabs  ((__imag_part_is_neg == false) ? __my_z.imag() : -__my_z.imag());

        return complex<T>( __imag_part_fabs / (__s_part * 2U),
                         ((__imag_part_is_neg == false) ? __s_part : -__s_part));
      }
    }

    template<typename T> complex<T> tan(const complex<T>& __my_z)
    {
      return sin(__my_z) / cos(__my_z);
    }

    template<typename T> complex<T> tanh(const complex<T>& __my_z)
    {
      return sinh(__my_z) / cosh(__my_z);
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
      explicit complex(const IntegralType n) : __my_re(n),
                                               __my_im(ef::zero()) { }

      template<typename FloatingPointType,
               typename std::enable_if<(std::is_floating_point<FloatingPointType>::value == true)>::type const* = nullptr>
      explicit complex(const FloatingPointType f) : __my_re(f),
                                                    __my_im(ef::zero()) { }

      complex(const e_float& __my_x = e_float(),
              const e_float& __my_y = e_float()) : __my_re(__my_x),
                                                   __my_im(__my_y) { }

      complex(const complex& __my_z) : __my_re(__my_z.real()),
                                       __my_im(__my_z.imag()) { }

      e_float real() const { return __my_re; }
      e_float imag() const { return __my_im; }

      void real(e_float __my_x) { __my_re = __my_x; }
      void imag(e_float __my_y) { __my_im = __my_y; }

      complex& operator=(const e_float& __my_other_x)
      {
        __my_re  = __my_other_x;
        __my_im  = ef::zero();

        return *this;
      }

      complex& operator+=(const e_float& v)
      {
        __my_re += v;

        return *this;
      }

      complex& operator-=(const e_float& v)
      {
        __my_re -= v;

        return *this;
      }

      complex& operator*=(const e_float& v)
      {
        __my_re *= v;
        __my_im *= v;

        return *this;
      }

      complex& operator/=(const e_float& v)
      {
        __my_re /= v;
        __my_im /= v;

        return *this;
      }

      complex& operator=(const complex& __my_other_z)
      {
        if(this != &__my_other_z)
        {
          __my_re = __my_other_z.__my_re;
          __my_im = __my_other_z.__my_im;
        }

        return *this;
      }

      template<typename X>
      complex& operator+=(const complex<X>& __my_z)
      {
        __my_re += __my_z.__my_re;
        __my_im += __my_z.__my_im;

        return *this;
      }

      template<typename X>
      complex& operator-=(const complex<X>& __my_z)
      {
        if(this == &__my_z)
        {
          __my_re = ef::zero();
          __my_im = ef::zero();
        }
        else
        {
          __my_re -= static_cast<e_float>(__my_z.__my_re);
          __my_im -= static_cast<e_float>(__my_z.__my_im);
        }

        return *this;
      }

      template<typename X>
      complex& operator*=(const complex<X>& __my_z)
      {
        const e_float __tmp_re(__my_re);

        if(this == &__my_z)
        {
          __my_re = (__tmp_re * __tmp_re) - (__my_im * __my_im);
          __my_im = (__tmp_re * __my_im) * 2U;
        }
        else
        {
          __my_re = (__tmp_re * __my_z.__my_re) - (__my_im * __my_z.__my_im);
          __my_im = (__tmp_re * __my_z.__my_im) + (__my_im * __my_z.__my_re);
        }

        return *this;
      }

      template<typename X>
      complex& operator/=(const complex<X>& __my_z)
      {
        if(this == &__my_z)
        {
          __my_re = ef::one ();
          __my_im = ef::zero();
        }
        else
        {
          const e_float one_over_denom(norm(__my_z).calculate_inv());

          const e_float tmp_re(__my_re);

          __my_re = ((tmp_re  * __my_z.__my_re) + (__my_im * __my_z.__my_im)) * one_over_denom;
          __my_im = ((__my_im * __my_z.__my_re) - (tmp_re  * __my_z.__my_im)) * one_over_denom;
        }

        return *this;
      }

      // Operators with integer.
      template<typename IntegralType,
               typename std::enable_if<   (std::is_integral<IntegralType>::value == true)
                                       && (std::is_unsigned<IntegralType>::value == false)>::type const* = nullptr>
      complex& operator+=(const IntegralType n)
      {
        __my_re.add_signed_long_long(n);

        return *this;
      }

      template<typename IntegralType,
               typename std::enable_if<   (std::is_integral<IntegralType>::value == true)
                                       && (std::is_unsigned<IntegralType>::value == true)>::type const* = nullptr>
      complex& operator+=(const IntegralType n)
      {
        __my_re.add_unsigned_long_long(n);

        return *this;
      }

      template<typename IntegralType,
               typename std::enable_if<   (std::is_integral<IntegralType>::value == true)
                                       && (std::is_unsigned<IntegralType>::value == false)>::type const* = nullptr>
      complex& operator-=(const IntegralType n)
      {
        __my_re.sub_signed_long_long(n);

        return *this;
      }

      template<typename IntegralType,
               typename std::enable_if<   (std::is_integral<IntegralType>::value == true)
                                       && (std::is_unsigned<IntegralType>::value == true)>::type const* = nullptr>
      complex& operator-=(const IntegralType n)
      {
        __my_re.sub_unsigned_long_long(n);

        return *this;
      }

      template<typename IntegralType,
               typename std::enable_if<   (std::is_integral<IntegralType>::value == true)
                                       && (std::is_unsigned<IntegralType>::value == false)>::type const* = nullptr>
      complex& operator*=(const IntegralType n)
      {
        __my_re.mul_signed_long_long(n);
        __my_im.mul_signed_long_long(n);

        return *this;
      }

      template<typename IntegralType,
               typename std::enable_if<   (std::is_integral<IntegralType>::value == true)
                                       && (std::is_unsigned<IntegralType>::value == true)>::type const* = nullptr>
      complex& operator*=(const IntegralType n)
      {
        __my_re.mul_unsigned_long_long(n);
        __my_im.mul_unsigned_long_long(n);

        return *this;
      }

      template<typename IntegralType,
               typename std::enable_if<   (std::is_integral<IntegralType>::value == true)
                                       && (std::is_unsigned<IntegralType>::value == false)>::type const* = nullptr>
      complex& operator/=(const IntegralType n)
      {
        __my_re.div_signed_long_long(n);
        __my_im.div_signed_long_long(n);

        return *this;
      }

      template<typename IntegralType,
               typename std::enable_if<   (std::is_integral<IntegralType>::value == true)
                                       && (std::is_unsigned<IntegralType>::value == true)>::type const* = nullptr>
      complex& operator/=(const IntegralType n)
      {
        __my_re.div_unsigned_long_long(n);
        __my_im.div_unsigned_long_long(n);

        return *this;
      }

    private:
      e_float __my_re;
      e_float __my_im;
    };

    // Non-member operations for ef::complex<T>.
    // See also ISO/IEC 14882:2011 Sect. 26.4.6.

    // Unary +/- operators.
    template<> inline complex<e_float> operator+(const complex<e_float>& __my_u) { return complex<e_float>(__my_u); }
    template<> inline complex<e_float> operator-(const complex<e_float>& __my_u) { return complex<e_float>(-__my_u.real(), -__my_u.imag()); }

    // Global binary add, sub, mul, div of complex op complex.
    template<> inline complex<e_float> operator+(const complex<e_float>& __my_u, const complex<e_float>& __my_v) { return complex<e_float>(__my_u) += __my_v; }
    template<> inline complex<e_float> operator-(const complex<e_float>& __my_u, const complex<e_float>& __my_v) { return complex<e_float>(__my_u) -= __my_v; }
    template<> inline complex<e_float> operator*(const complex<e_float>& __my_u, const complex<e_float>& __my_v) { return complex<e_float>(__my_u) *= __my_v; }
    template<> inline complex<e_float> operator/(const complex<e_float>& __my_u, const complex<e_float>& __my_v) { return complex<e_float>(__my_u) /= __my_v; }

    // Global binary add, sub, mul, div of complex op e_float.
    template<> inline complex<e_float> operator+(const complex<e_float>& __my_u, const e_float& __my_v) { return complex<e_float>(__my_u.real() + __my_v, __my_u.imag()); }
    template<> inline complex<e_float> operator-(const complex<e_float>& __my_u, const e_float& __my_v) { return complex<e_float>(__my_u.real() - __my_v, __my_u.imag()); }
    template<> inline complex<e_float> operator*(const complex<e_float>& __my_u, const e_float& __my_v) { return complex<e_float>(__my_u.real() * __my_v, __my_u.imag() * __my_v); }
    template<> inline complex<e_float> operator/(const complex<e_float>& __my_u, const e_float& __my_v) { return complex<e_float>(__my_u.real() / __my_v, __my_u.imag() / __my_v); }

    // Global binary add, sub, mul, div of e_float op complex.
    template<> inline complex<e_float> operator+(const e_float& __my_u, const complex<e_float>& __my_v) { return complex<e_float>(__my_u + __my_v.real(),  __my_v.imag()); }
    template<> inline complex<e_float> operator-(const e_float& __my_u, const complex<e_float>& __my_v) { return complex<e_float>(__my_u - __my_v.real(), -__my_v.imag()); }
    template<> inline complex<e_float> operator*(const e_float& __my_u, const complex<e_float>& __my_v) { return complex<e_float>(__my_v.real() * __my_u, __my_v.imag() * __my_u); }
    template<> inline complex<e_float> operator/(const e_float& __my_u, const complex<e_float>& __my_v)
    {
      const e_float __my_v_norm(norm(__my_v));

      return complex<e_float>(  (__my_u * __my_v.real()) / __my_v_norm,
                              - (__my_u * __my_v.imag()) / __my_v_norm);
    }

    template<> inline bool operator==(const complex<e_float>& __my_u, const complex<e_float>& __my_v) { return ((__my_u.real() == __my_v.real()) && (__my_u.imag() == __my_v.imag())); }
    template<> inline bool operator==(const complex<e_float>& __my_u, const e_float         & __my_v) { return ((__my_u.real() == __my_v)        && (__my_u.imag() == e_float(0U))); }
    template<> inline bool operator==(const e_float&          __my_u, const complex<e_float>& __my_v) { return ((__my_u == __my_v.real())        && (__my_v.imag() == e_float(0U))); }
    template<> inline bool operator!=(const complex<e_float>& __my_u, const complex<e_float>& __my_v) { return ((__my_u.real() != __my_v.real()) || (__my_u.imag() != __my_v.imag())); }
    template<> inline bool operator!=(const complex<e_float>& __my_u, const e_float         & __my_v) { return ((__my_u.real() != __my_v)        || (__my_u.imag() != e_float(0U))); }
    template<> inline bool operator!=(const e_float&          __my_u, const complex<e_float>& __my_v) { return ((__my_u != __my_v.real())        || (__my_v.imag() != e_float(0U))); }

    template<> inline e_float real(const complex<e_float>& __my_z) { return __my_z.real(); }
    template<> inline e_float imag(const complex<e_float>& __my_z) { return __my_z.imag(); }

    template<> inline e_float abs (const complex<e_float>& __my_z) { return sqrt((__my_z.real() * __my_z.real()) + (__my_z.imag() * __my_z.imag())); }
    template<> inline e_float arg (const complex<e_float>& __my_z) { return atan2(__my_z.imag(), __my_z.real()); }
    template<> inline e_float norm(const complex<e_float>& __my_z) { return (__my_z.real() * __my_z.real()) + (__my_z.imag() * __my_z.imag()); }

    template<> inline complex<e_float> conj(const complex<e_float>& __my_z)
    {
      return complex<e_float>(-__my_z.imag(), __my_z.real());
    }

    template<> inline complex<e_float> proj(const complex<e_float>& __my_z)
    {
      const e_float two_over_denom((norm(__my_z) + ef::one()).calculate_inv() * 2U);

      return complex<e_float>(__my_z.real() * two_over_denom,
                              __my_z.imag() * two_over_denom);
    }

    template<> inline complex<e_float> polar(const e_float& __my_rho, const e_float& __my_theta)
    {
      const e_float __my_s = sin(__my_theta);
      const e_float __my_c = cos(__my_theta);

      return complex<e_float>(__my_rho * __my_c, __my_rho * __my_s);
    }

    template<> inline complex<e_float> acos(const complex<e_float>& __my_z)
    {
      return complex<e_float>(ef::pi_half()) - asin(__my_z);
    }

    template<> inline complex<e_float> asin(const complex<e_float>& __my_z)
    {
      return -conj(log(conj(__my_z) + sqrt(ef::one() - (__my_z * __my_z))));
    }

    template<> inline complex<e_float> atan(const complex<e_float>& __my_z)
    {
      const complex<e_float> __my_z_conj(conj(__my_z));

      const complex<e_float> __my_pre_result(log(ef::one() - __my_z_conj) - log(ef::one() + __my_z_conj));

      return complex<e_float>(-__my_pre_result.imag() / 2U,
                               __my_pre_result.real() / 2U);
    }

    template<> inline complex<e_float> acosh(const complex<e_float>& __my_z)
    {
      const complex<e_float> __my_zp = __my_z + ef::one();
      const complex<e_float> __my_zm = __my_z - ef::one();

      return log(__my_z + (__my_zp * sqrt(__my_zm / __my_zp)));
    }

    template<> complex<e_float> asinh(const complex<e_float>& __my_z)
    {
      return log(__my_z + sqrt((__my_z * __my_z) + ef::one()));
    }

    template<> inline complex<e_float> atanh(const complex<e_float>& __my_z)
    {
      const complex<e_float> __my_pre_result(  log(ef::one() + __my_z)
                                             - log(ef::one() - __my_z));

      return complex<e_float>(__my_pre_result.real() / 2U,
                              __my_pre_result.imag() / 2U);
    }

    template<> inline complex<e_float> cos(const complex<e_float>& __my_z)
    {
      e_float __my_sin_x  = sin (__my_z.real());
      e_float __my_cos_x  = cos (__my_z.real());
      e_float __my_sinh_y = sinh(__my_z.imag());
      e_float __my_cosh_y = cosh(__my_z.imag());

      return complex<e_float>(__my_cos_x * __my_cosh_y, -(__my_sin_x * __my_sinh_y));
    }

    template<> inline complex<e_float> cosh(const complex<e_float>& __my_z)
    {
      e_float __my_sin_y  = sin (__my_z.imag());
      e_float __my_cos_y  = cos (__my_z.imag());
      e_float __my_sinh_x = sinh(__my_z.real());
      e_float __my_cosh_x = cosh(__my_z.real());

      return complex<e_float>(__my_cos_y * __my_cosh_x, __my_sin_y * __my_sinh_x);
    }

    template<> inline complex<e_float> exp(const complex<e_float>& __my_z)
    {
      e_float __my_sin_y  = sin (__my_z.imag());
      e_float __my_cos_y  = cos (__my_z.imag());

      return complex<e_float>(__my_cos_y, __my_sin_y) * e_float(ef::exp(__my_z.real()));
    }

    template<> inline complex<e_float> log(const complex<e_float>& __my_z)
    {
      using std::atan2;
      using std::log;

      const e_float __my_real_part(ef::log(norm(__my_z)) / 2U);
      const e_float __my_imag_part(ef::atan2(__my_z.imag(), __my_z.real()));

      return complex<e_float>(__my_real_part, __my_imag_part);
    }

    template<> inline complex<e_float> log10(const complex<e_float>& __my_z)
    {
      return log(__my_z) / ln10();
    }

    template<> inline complex<e_float> pow(const complex<e_float>& __my_z, std::int64_t __my_pn)
    {
      return ef::detail::pown_template<complex<e_float>>(__my_z, __my_pn);
    }

    template<> inline complex<e_float> pow(const complex<e_float>& __my_z, const e_float& __my_a)
    {
      return exp(__my_a * log(__my_z));
    }

    template<> inline complex<e_float> pow(const complex<e_float>& __my_z, const complex<e_float>& __my_a)
    {
      return exp(__my_a * log(__my_z));
    }

    template<> inline complex<e_float> pow(const e_float& __my_z, const complex<e_float>& __my_a)
    {
      return exp(__my_a * log(__my_z));
    }

    template<> inline complex<e_float> sin(const complex<e_float>& __my_z)
    {
      e_float __my_sin_x  = sin (__my_z.real());
      e_float __my_cos_x  = cos (__my_z.real());
      e_float __my_sinh_y = sinh(__my_z.imag());
      e_float __my_cosh_y = cosh(__my_z.imag());

      return complex<e_float>(__my_sin_x * __my_cosh_y, __my_cos_x * __my_sinh_y);
    }

    template<> inline complex<e_float> sinh(const complex<e_float>& __my_z)
    {
      e_float __my_sin_y  = sin (__my_z.imag());
      e_float __my_cos_y  = cos (__my_z.imag());
      e_float __my_sinh_x = sinh(__my_z.real());
      e_float __my_cosh_x = cosh(__my_z.real());

      return complex<e_float>(__my_cos_y * __my_sinh_x, __my_cosh_x * __my_sin_y);
    }

    template<> inline complex<e_float> sqrt(const complex<e_float>& __my_z)
    {
      using std::sqrt;

      // Use the following:
      // sqrt(z) = (s, zi / 2s)       for zr >= 0
      //           (|zi| / 2s, +-s)   for zr <  0
      // where s = sqrt{ [ |zr| + sqrt(zr^2 + zi^2) ] / 2 },
      // and the +- sign is the same as the sign of zi.

      const bool __my_real_part_is_neg(__my_z.real() < 0U);

      const e_float __my_real_part_fabs((__my_real_part_is_neg == false) ? __my_z.real() : -__my_z.real());
      const e_float __my_sqrt_part     (ef::sqrt((__my_real_part_fabs + abs(__my_z)) / 2U));

      if(__my_real_part_is_neg == false)
      {
        return complex<e_float>(__my_sqrt_part,
                                __my_z.imag() / (__my_sqrt_part * 2U));
      }
      else
      {
        const bool __my_imag_part_is_neg(__my_z.imag() < 0U);

        const e_float __my_imag_part_fabs((__my_imag_part_is_neg == false) ? __my_z.imag() : -__my_z.imag());

        return complex<e_float>( __my_imag_part_fabs / (__my_sqrt_part * 2U),
                               ((__my_imag_part_is_neg == false) ? __my_sqrt_part : -__my_sqrt_part));
      }
    }

    template<> inline complex<e_float> tan(const complex<e_float>& __my_z)
    {
      e_float __my_sin_x  = sin (__my_z.real());
      e_float __my_cos_x  = cos (__my_z.real());
      e_float __my_sinh_y = sinh(__my_z.imag());
      e_float __my_cosh_y = cosh(__my_z.imag());

      const complex<e_float> __my_s(__my_sin_x * __my_cosh_y,   __my_cos_x * __my_sinh_y);
      const complex<e_float> __my_c(__my_cos_x * __my_cosh_y, -(__my_sin_x * __my_sinh_y));

      return __my_s / __my_c;
    }

    template<> inline complex<e_float> tanh(const complex<e_float>& __my_z)
    {
      e_float __my_sin_y  = sin (__my_z.imag());
      e_float __my_cos_y  = cos (__my_z.imag());
      e_float __my_sinh_x = sinh(__my_z.real());
      e_float __my_cosh_x = cosh(__my_z.real());

      const complex<e_float> __my_sh(__my_cos_y * __my_sinh_x, __my_cosh_x * __my_sin_y);
      const complex<e_float> __my_ch(__my_cos_y * __my_cosh_x, __my_sin_y  * __my_sinh_x);

      return __my_sh / __my_ch;
    }

    // I/O stream operators.
    template<typename char_type, typename traits_type>
    std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>& __my_istream, complex<e_float>& __my_z)
    {
      // Parse an (extended) complex number of any of the forms u, (u) or (u,v).

      const std::array<std::regex, 3U> __my_regexes =
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

      e_float __my_real_input(0U);
      e_float __my_imag_input(0U);

      bool __my_input_has_error = false;

      std::string __my_input_str;

      __my_istream >> __my_input_str;

      std::match_results<std::string::const_iterator> __my_mr;

      auto __my_it_regex_match =
        std::find_if(__my_regexes.cbegin(),
                     __my_regexes.cend(),
                     [&__my_input_str, &__my_mr](const std::regex& __my_rx) -> bool
                     {
                       return std::regex_match(__my_input_str, __my_mr, __my_rx);
                     });

      if(__my_it_regex_match == __my_regexes.cend())
      {
        // The input does not match any of the regular expressions.
        // Set the error flag and take no other action.

        __my_input_has_error = true;
      }
      else if(__my_it_regex_match == __my_regexes.cbegin())
      {
        // The input matches __the_regexes[0U], corresponding to the form (u,v).
        // This represents a complex number real and imaginary parts.

        // Rule out erroneous match of invalid mantissa or exponent parts.
        const std::string __my_str1(__my_mr[1U]);
        const std::string __my_str2(__my_mr[2U]);
        const std::string __my_str3(__my_mr[3U]);
        const std::string __my_str4(__my_mr[4U]);

        const std::string __my_decimal_digits("0123456789");

        const bool __my_str1_has_error = ((__my_str1.length() != std::size_t(0U)) && (__my_str1.find_first_of(__my_decimal_digits) == std::string::npos));
        const bool __my_str2_has_error = ((__my_str2.length() != std::size_t(0U)) && (__my_str2.find_first_of(__my_decimal_digits) == std::string::npos));
        const bool __my_str3_has_error = ((__my_str3.length() != std::size_t(0U)) && (__my_str3.find_first_of(__my_decimal_digits) == std::string::npos));
        const bool __my_str4_has_error = ((__my_str4.length() != std::size_t(0U)) && (__my_str4.find_first_of(__my_decimal_digits) == std::string::npos));

        if(__my_str1_has_error || __my_str2_has_error || __my_str3_has_error || __my_str4_has_error)
        {
          __my_input_has_error = true;
        }
        else
        {
          // Extract the real part of the complex number.
          std::stringstream __my_stringstream;

          __my_stringstream << __my_mr[1U] << __my_mr[2U];
          __my_stringstream >> __my_real_input;

          __my_stringstream.str(std::string());
          __my_stringstream.clear();

          // Extract the imaginary part of the complex number.

          __my_stringstream << __my_mr[3U] << __my_mr[4U];
          __my_stringstream >> __my_imag_input;
        }
      }
      else if(   (__my_it_regex_match == (__my_regexes.cbegin() + 1U))
              || (__my_it_regex_match == (__my_regexes.cbegin() + 2U)))
      {
        // The input matches the_regexes[1U] or the_regexes[2U],
        // corresponding to either of the forms (u) or u.
        // This represents a complex number having only
        // a pure real part.

        // Rule out erroneous match of invalid mantissa or exponent parts.
        const std::string __my_str1(__my_mr[1U]);
        const std::string __my_str2(__my_mr[2U]);

        const std::string __my_decimal_digits("0123456789");

        if(   ((__my_str1.length() != std::size_t(0U)) && (__my_str1.find_first_of(__my_decimal_digits) == std::string::npos))
           || ((__my_str2.length() != std::size_t(0U)) && (__my_str2.find_first_of(__my_decimal_digits) == std::string::npos)))
        {
          __my_input_has_error = true;
        }
        else
        {
          // Extract the real part of the complex number.
          std::stringstream __my_stringstream;

          __my_stringstream << __my_mr[1U] << __my_mr[2U];
          __my_stringstream >> __my_real_input;

          __my_imag_input = T(0U);
        }
      }

      if(__my_input_has_error)
      {
        // Error case: Restore the characters in the input stream
        // and set the fail bit in the input stream.
        std::for_each(__my_input_str.cbegin(),
                      __my_input_str.cend(),
                      [&__my_istream](const char& __my_c)
                      {
                        __my_istream.putback(__my_c);
                      });

        __my_istream.setstate(std::ios_base::failbit);
      }
      else
      {
        __my_z = complex<T>(__my_real_input, __my_imag_input);
      }

      return __my_istream;
    }

    template<typename char_type, typename traits_type>
    std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>& __my_ostream, const complex<e_float>& __my_z)
    {
      std::basic_ostringstream<char_type, traits_type> __my_tmp_ostream;

      __my_tmp_ostream.flags    (__my_ostream.flags());
      __my_tmp_ostream.imbue    (__my_ostream.getloc());
      __my_tmp_ostream.precision(__my_ostream.precision());

      __my_tmp_ostream << '('
                       << __my_z.real()
                       << ','
                       << __my_z.imag()
                       << ')';

      return (__my_ostream << __my_tmp_ostream.str());
    }

    #if defined(_MSC_VER) && (_MSC_VER <= 1800)
    #else
    inline complex<float>       operator""if(long double __my_imag_literal)        { return complex<float>      {0.0F, static_cast<float>      (__my_imag_literal)}; }
    inline complex<double>      operator""i (long double __my_imag_literal)        { return complex<double>     {0.0,  static_cast<double>     (__my_imag_literal)}; }
    inline complex<long double> operator""il(long double __my_imag_literal)        { return complex<long double>{0.0L, static_cast<long double>(__my_imag_literal)}; }

    inline complex<float>       operator""if(unsigned long long __my_imag_literal) { return complex<float>      {0.0F, static_cast<float>      (__my_imag_literal)}; }
    inline complex<double>      operator""i (unsigned long long __my_imag_literal) { return complex<double>     {0.0,  static_cast<double>     (__my_imag_literal)}; }
    inline complex<long double> operator""il(unsigned long long __my_imag_literal) { return complex<long double>{0.0L, static_cast<long double>(__my_imag_literal)}; }
    #endif
  } // namespace ef

#endif // E_FLOAT_COMPLEX_2017_08_23_HPP_
