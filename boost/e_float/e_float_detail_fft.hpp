
//          Copyright Christopher Kormanyos 2013 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef E_FLOAT_DETAIL_FFT_2013_01_08_HPP_
  #define E_FLOAT_DETAIL_FFT_2013_01_08_HPP_

  #if defined(_MSC_VER)
    #pragma warning (disable:4127)
  #endif

  namespace ef { namespace detail { namespace fft {

  template<std::uint32_t NumPoints,
           std::uint32_t Order,
           typename float_type = double>
  struct template_sin
  {
  public:
    static float_type value()
    {
      // Note: the necessary values of the sine function
      // are all implemented as template specializations.
      return float_type(0.0L);
    }
  };

  // TBD: Use constexpr functions here, depending on availability.
  // Mathematica command: Table[N[Sin[Pi / (2^n)], 41], {n, 1, 31, 1}]
  template<typename float_type> struct template_sin<std::uint32_t(         1U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(0.0L); } };                                            // Pi
  template<typename float_type> struct template_sin<std::uint32_t(         2U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(1.0L); } };                                            // Pi / 2
  template<typename float_type> struct template_sin<std::uint32_t(         4U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(7.0710678118654752440084436210484903928484E-01L); } }; // Pi / 4
  template<typename float_type> struct template_sin<std::uint32_t(         8U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(3.8268343236508977172845998403039886676134E-01L); } }; // Pi / 8
  template<typename float_type> struct template_sin<std::uint32_t(        16U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(1.9509032201612826784828486847702224092769E-01L); } }; // Pi / 16
  template<typename float_type> struct template_sin<std::uint32_t(        32U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(9.8017140329560601994195563888641845861137E-02L); } }; // Pi / 32
  template<typename float_type> struct template_sin<std::uint32_t(        64U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(4.9067674327418014254954976942682658314745E-02L); } }; // Pi / 64
  template<typename float_type> struct template_sin<std::uint32_t(       128U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(2.4541228522912288031734529459282925065466E-02L); } }; // Pi / 128
  template<typename float_type> struct template_sin<std::uint32_t(1ULL <<  8U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(1.2271538285719926079408261951003212140372E-02L); } }; // Pi / 2^8
  template<typename float_type> struct template_sin<std::uint32_t(1ULL <<  9U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(6.1358846491544753596402345903725809170579E-03L); } }; // Pi / 2^9
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 10U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(3.0679567629659762701453654909198425189446E-03L); } }; // Pi / 2^10
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 11U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(1.5339801862847656123036971502640790799549E-03L); } }; // Pi / 2^11
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 12U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(7.6699031874270452693856835794857664314092E-04L); } }; // Pi / 2^12
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 13U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(3.8349518757139558907246168118138126339503E-04L); } }; // Pi / 2^13
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 14U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(1.9174759731070330743990956198900093346887E-04L); } }; // Pi / 2^14
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 15U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(9.5873799095977345870517210976476351187066E-05L); } }; // Pi / 2^15
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 16U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(4.7936899603066884549003990494658872746867E-05L); } }; // Pi / 2^16
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 17U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(2.3968449808418218729186577165021820094761E-05L); } }; // Pi / 2^17
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 18U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(1.1984224905069706421521561596988984804732E-05L); } }; // Pi / 2^18
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 19U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(5.9921124526424278428797118088908617299872E-06L); } }; // Pi / 2^19
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 20U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(2.9960562263346607504548128083570598118252E-06L); } }; // Pi / 2^20
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 21U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(1.4980281131690112288542788461553611206918E-06L); } }; // Pi / 2^21
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 22U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(7.4901405658471572113049856673065563715596E-07L); } }; // Pi / 2^22
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 23U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(3.7450702829238412390316917908463317739740E-07L); } }; // Pi / 2^23
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 24U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(1.8725351414619534486882457659356361712045E-07L); } }; // Pi / 2^24
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 25U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(9.3626757073098082799067286680885620193237E-08L); } }; // Pi / 2^25
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 26U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(4.6813378536549092695115518138540096959504E-08L); } }; // Pi / 2^26
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 27U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(2.3406689268274552759505493419034844037886E-08L); } }; // Pi / 2^27
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 28U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(1.1703344634137277181246213503238103798093E-08L); } }; // Pi / 2^28
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 29U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(5.8516723170686386908097901008341396943900E-09L); } }; // Pi / 2^29
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 30U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(2.9258361585343193579282304690689559020176E-09L); } }; // Pi / 2^30
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 31U), std::uint32_t(1U), float_type> { static float_type value() { return float_type(1.4629180792671596805295321618659637103743E-09L); } }; // Pi / 2^31

  template<typename float_type> struct template_sin<std::uint32_t(         1U), std::uint32_t(2U), float_type> { static float_type value() { return float_type(0.0L); } };
  template<typename float_type> struct template_sin<std::uint32_t(         2U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(         1U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(         4U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(         2U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(         8U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(         4U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(        16U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(         8U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(        32U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(        16U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(        64U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(        32U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(       128U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(        64U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL <<  8U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(       128U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL <<  9U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL <<  8U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 10U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL <<  9U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 11U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 10U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 12U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 11U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 13U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 12U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 14U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 13U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 15U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 14U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 16U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 15U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 17U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 16U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 18U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 17U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 19U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 18U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 20U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 19U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 21U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 20U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 22U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 21U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 23U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 22U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 24U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 23U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 25U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 24U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 26U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 25U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 27U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 26U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 28U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 27U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 29U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 28U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 30U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 29U), std::uint32_t(1U), float_type>::value(); } };
  template<typename float_type> struct template_sin<std::uint32_t(1ULL << 31U), std::uint32_t(2U), float_type> { static float_type value() { return template_sin<std::uint32_t(1ULL << 30U), std::uint32_t(1U), float_type>::value(); } };

  // TBD: Use constexpr functions here, depending on availability.
  template<const std::uint32_t N,
           const bool is_forward_fft,
           typename float_type>
  float_type const_unique_wp_real_init() { return (is_forward_fft ? +static_cast<float_type>(template_sin<N, 1U, long double>::value())
                                                                  : -static_cast<float_type>(template_sin<N, 1U, long double>::value())); }

  template<const std::uint32_t N,
           const bool is_forward_fft,
           typename float_type>
  float_type const_unique_wp_imag() { return (is_forward_fft ? +static_cast<float_type>(template_sin<N, 2U, long double>::value())
                                                             : -static_cast<float_type>(template_sin<N, 2U, long double>::value())); }

  template<const std::uint32_t N,
           const bool is_forward_fft,
           typename float_type>
  float_type const_unique_wp_real() { return float_type(float_type(-2.0L) * (  const_unique_wp_real_init<N, is_forward_fft, float_type>()
                                                                             * const_unique_wp_real_init<N, is_forward_fft, float_type>())); }

  template<const std::uint32_t N,
           const bool is_forward_fft = true,
           typename float_type = double>
  struct danielson_lanczos
  {
    static void apply(float_type* data)
    {
      danielson_lanczos<N / 2U, is_forward_fft, float_type>::apply(data);
      danielson_lanczos<N / 2U, is_forward_fft, float_type>::apply(data + N);

      float_type real_part = float_type(1.0L);
      float_type imag_part = float_type(0.0L);

      for(std::uint32_t i = static_cast<std::uint32_t>(0U); i < N; i += 2U)
      {
              float_type tmp_real = (real_part * data[i + (N + 0U)]) - (imag_part * data[i + (N + 1U)]);
        const float_type tmp_imag = (real_part * data[i + (N + 1U)]) + (imag_part * data[i + (N + 0U)]);

        data[i + (N + 0U)] = data[i + 0U] - tmp_real;
        data[i + (N + 1U)] = data[i + 1U] - tmp_imag;

        data[i + 0U] += tmp_real;
        data[i + 1U] += tmp_imag;

        tmp_real = real_part;

        real_part += (((tmp_real  * const_unique_wp_real<N, is_forward_fft, float_type>()) - (imag_part * const_unique_wp_imag<N, is_forward_fft, float_type>())));
        imag_part += (((imag_part * const_unique_wp_real<N, is_forward_fft, float_type>()) + (tmp_real  * const_unique_wp_imag<N, is_forward_fft, float_type>())));
      }
    }
  };

  template<const bool is_forward_fft,
           typename float_type>
  struct danielson_lanczos<2U, is_forward_fft, float_type>
  {
    static void apply(float_type* data)
    {
      const float_type tmp_real = data[2U]; 
      const float_type tmp_imag = data[3U]; 

      data[2U]  = data[0U] - tmp_real;
      data[3U]  = data[1U] - tmp_imag;
      data[0U] += tmp_real; 
      data[1U] += tmp_imag; 
    }
  };

  template<const bool is_forward_fft,
           typename float_type>
  struct danielson_lanczos<4U, is_forward_fft, float_type>
  {
    static void apply(float_type* data)
    {
      danielson_lanczos<2U, is_forward_fft, float_type>::apply(data);
      danielson_lanczos<2U, is_forward_fft, float_type>::apply(data + 4U);

      float_type tmp_real = data[4U];
      float_type tmp_imag = data[5U];

      data[4U] = data[0U] - tmp_real;
      data[5U] = data[1U] - tmp_imag;

      data[0U] += tmp_real;
      data[1U] += tmp_imag;

      const float_type real_part(const_unique_wp_real<4U, is_forward_fft, float_type>() + float_type(1.0L));
      const float_type imag_part(const_unique_wp_imag<4U, is_forward_fft, float_type>());

      tmp_real = (real_part * data[6U]) - (imag_part * data[7U]);
      tmp_imag = (real_part * data[7U]) + (imag_part * data[6U]);

      data[6U] = data[2U] - tmp_real;
      data[7U] = data[3U] - tmp_imag;

      data[2U] += tmp_real;
      data[3U] += tmp_imag;
    }
  };

  template<const std::uint32_t N,
           const bool is_forward_fft = true,
           typename float_type = double>
  struct fft_lanczos
  {
  public:
    static void fft(float_type* data)
    {
      bit_twiddle(data);

      danielson_lanczos<N, is_forward_fft, float_type>::apply(data);
    }

  private:
    static void bit_twiddle(float_type* data)
    {
      // TBD: Is there a way to improve the performance with metaprogramming here?
      // TBD: Or would metaprogramming here simply excessively load the compiler?

      std::uint32_t j = static_cast<std::uint32_t>(1U);

      for(std::uint32_t i = static_cast<std::uint32_t>(1U); i < static_cast<std::uint32_t>(N << 1U); i += 2U)
      {
        if(j > i)
        {
          std::swap(data[j - 1U], data[i - 1U]);
          std::swap(data[j],      data[i]);
        }

        std::uint32_t m = N;

        // TBD: Is it possible to simpliry this via metaprogramming and switch-case?
        while((m > static_cast<std::uint32_t>(1U)) && (j > m))
        {
          j  -= m;
          m >>= 1U;
        }

        j += m;
      }
    }
  };

  template<const std::uint32_t N,
           const bool is_forward_fft = true,
           typename float_type = double>
  struct rfft_lanczos_template
  {
    static void rfft(float_type* data)
    {
      if(is_forward_fft)
      {
        fft_lanczos<N / 2U, true, float_type>::fft(data);
      }

      float_type real_part(float_type(1.0L) + const_unique_wp_real<N, is_forward_fft, float_type>());
      float_type imag_part(const_unique_wp_imag<N, is_forward_fft, float_type>());

      for(std::uint32_t i = static_cast<std::uint32_t>(1U); i < static_cast<std::uint32_t>(N >> 2U); ++i)
      {
        const std::uint32_t i1 = static_cast<std::uint32_t>(i + i);
        const std::uint32_t i3 = static_cast<std::uint32_t>(N - i1);

        const std::uint32_t i2 = static_cast<std::uint32_t>(1U + i1);
        const std::uint32_t i4 = static_cast<std::uint32_t>(1U + i3);

        const float_type h1r = float_type(float_type(0.5L) * (data[i1] + data[i3]));
        const float_type h1i = float_type(float_type(0.5L) * (data[i2] - data[i4]));

        const float_type h2r = float_type(-(data[i2] + data[i4]) * (is_forward_fft ? float_type(-0.5L) : float_type(0.5L)));
        const float_type h2i = float_type(+(data[i1] - data[i3]) * (is_forward_fft ? float_type(-0.5L) : float_type(0.5L)));

        data[i1] = (+h1r + (real_part * h2r)) - (imag_part * h2i);
        data[i2] = (+h1i + (real_part * h2i)) + (imag_part * h2r);
        data[i3] = (+h1r - (real_part * h2r)) + (imag_part * h2i);
        data[i4] = (-h1i + (real_part * h2i)) + (imag_part * h2r);

        const float_type tmp_real = real_part;

        real_part += (((tmp_real  * const_unique_wp_real<N, is_forward_fft, float_type>()) - (imag_part * const_unique_wp_imag<N, is_forward_fft, float_type>())));
        imag_part += (((imag_part * const_unique_wp_real<N, is_forward_fft, float_type>()) + (tmp_real  * const_unique_wp_imag<N, is_forward_fft, float_type>())));
      }

      const float_type f0_tmp = data[0U];

      if(is_forward_fft)
      {
        data[0U] = f0_tmp + data[1U];
        data[1U] = f0_tmp - data[1U];
      }
      else
      {
        data[0U] = float_type(float_type(0.5L) * (f0_tmp + data[1U]));
        data[1U] = float_type(float_type(0.5L) * (f0_tmp - data[1U]));

        fft_lanczos<N / 2U, false, float_type>::fft(data);
      }
    }
  };
  } } } // namespace ef::detail::fft

#endif // E_FLOAT_DETAIL_FFT_2013_01_08_HPP_
