
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef E_FLOAT_MPFR_PROTOS_2009_11_15_H_
  #define E_FLOAT_MPFR_PROTOS_2009_11_15_H_

  // Declare the types of MPFR.
  extern "C"
  {
    typedef unsigned long     mpfr_prec_t;
    typedef int               mpfr_sign_t;
    typedef long int          mp_exp_t;
    typedef unsigned long int mp_limb_t;

    #define mp_prec_t mpfr_prec_t
    #define mp_rnd_t  mpfr_rnd_t

    struct __mpfr_struct
    {
      __mpfr_struct() : _mpfr_prec(0UL),
                        _mpfr_sign(0),
                        _mpfr_exp (0L),
                        _mpfr_d   (nullptr) { }

      mpfr_prec_t _mpfr_prec;
      mpfr_sign_t _mpfr_sign;
      mp_exp_t    _mpfr_exp;
      mp_limb_t*  _mpfr_d;
    };

    typedef __mpfr_struct        mpfr_t[1U];
    typedef __mpfr_struct*       mpfr_ptr;
    typedef const __mpfr_struct* mpfr_srcptr;

    typedef enum
    {
      GMP_RNDNA   = -1,
      GMP_RNDN    =  0,
      GMP_RNDZ    =  1,
      GMP_RNDU    =  2,
      GMP_RNDD    =  3,
      GMP_RND_MAX =  4
    }
    mpfr_rnd_t;
  }

  // Wrap the function names of MPFR.
  extern "C"
  {
    #define MPFR_SIGN(x) ((x)->_mpfr_sign)

    void mpfr_init            (mpfr_ptr);
    void mpfr_set_default_prec(mpfr_prec_t);
    void mpfr_clear           (mpfr_ptr);

    int mpfr_set4    (mpfr_ptr, mpfr_srcptr, mpfr_rnd_t, int);
    #define mpfr_set(x, y, rnd) mpfr_set4((x), (y), (rnd), MPFR_SIGN(y))

    int  mpfr_set_ui (mpfr_ptr, unsigned long, mpfr_rnd_t);
    int  mpfr_set_d  (mpfr_ptr, double,        mpfr_rnd_t);
    int  mpfr_set_ld (mpfr_ptr, long double,   mpfr_rnd_t);
    void mpfr_set_inf(mpfr_t,   int);
    void mpfr_set_nan(mpfr_t);

    #define mpfr_init_set(x, y, rnd)     ( mpfr_init(x), static_cast<void>(mpfr_set   ((x), (y), (rnd))))
    #define mpfr_init_set_ui(x, i, rnd)  ( mpfr_init(x), static_cast<void>(mpfr_set_ui((x), (i), (rnd))))
    #define mpfr_init_set_d(x, d, rnd)   ( mpfr_init(x), static_cast<void>(mpfr_set_d((x), (d), (rnd))))
    #define mpfr_init_set_ld(x, ld, rnd) ( mpfr_init(x), static_cast<void>(mpfr_set_ld((x), (ld), (rnd))))
    int mpfr_init_set_str(mpfr_ptr, const char*, int, mpfr_rnd_t);

    int mpfr_add(mpfr_ptr, mpfr_srcptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_sub(mpfr_ptr, mpfr_srcptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_mul(mpfr_ptr, mpfr_srcptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_div(mpfr_ptr, mpfr_srcptr, mpfr_srcptr, mpfr_rnd_t);

    int mpfr_add_ui (mpfr_ptr, mpfr_srcptr, unsigned long int, mpfr_rnd_t);
    int mpfr_sub_ui (mpfr_ptr, mpfr_srcptr, unsigned long int, mpfr_rnd_t);
    int mpfr_mul_ui (mpfr_ptr, mpfr_srcptr, unsigned long int, mpfr_rnd_t);
    int mpfr_div_ui (mpfr_ptr, mpfr_srcptr, unsigned long int, mpfr_rnd_t);
    int mpfr_mul_2si(mpfr_t,   mpfr_t,        signed long int, mpfr_rnd_t);

    int mpfr_cmp3(mpfr_srcptr, mpfr_srcptr, int);
    int mpfr_neg (mpfr_ptr, mpfr_srcptr, mp_rnd_t);

    int mpfr_nan_p    (mpfr_srcptr);
    int mpfr_inf_p    (mpfr_srcptr);
    int mpfr_number_p (mpfr_srcptr);
    int mpfr_zero_p   (mpfr_srcptr);
    int mpfr_integer_p(mpfr_srcptr);
    int mpfr_sgn      (mpfr_srcptr);

    int mpfr_sprintf(char*, const char*, ...);

    double        mpfr_get_d     (mpfr_srcptr, mpfr_rnd_t);
    long double   mpfr_get_ld    (mpfr_srcptr, mpfr_rnd_t);
    unsigned long mpfr_get_si    (mpfr_srcptr, mpfr_rnd_t);
    double        mpfr_get_d_2exp(signed long int*, mpfr_srcptr, mpfr_rnd_t);
    char*         mpfr_get_str   (char*, mp_exp_t*, int, size_t, mpfr_srcptr, mpfr_rnd_t);

    int mpfr_floor(mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_sqrt (mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_cbrt (mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_root (mpfr_ptr, mpfr_srcptr, unsigned long int, mpfr_rnd_t);
    int mpfr_sin  (mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_cos  (mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_tan  (mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_asin (mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_acos (mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_atan (mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_sinh (mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_cosh (mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_tanh (mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_asinh(mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_acosh(mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_atanh(mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_exp  (mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_log  (mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_gamma(mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_zeta (mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_jn   (mpfr_ptr, long, mpfr_srcptr, mpfr_rnd_t);
    int mpfr_yn   (mpfr_ptr, long, mpfr_srcptr, mpfr_rnd_t);
  }

#endif // E_FLOAT_MPFR_PROTOS_2009_11_15_H_
