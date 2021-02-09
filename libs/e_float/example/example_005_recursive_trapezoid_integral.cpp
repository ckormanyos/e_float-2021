
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <e_float/e_float.h>
#include <e_float/e_float_functions.h>

#include <utility/util_lexical_cast.h>
#include <utility/util_trapezoid.h>

#include "examples.h"

namespace examples
{
  namespace nr_005
  {
    template<typename T>
    class RecursiveTrapezoidJ0 : public Util::RecursiveTrapezoidRule<T>
    {
    public:
      RecursiveTrapezoidJ0(const T& z) : Util::RecursiveTrapezoidRule<T>(T(0), my_pi(), Util::RecursiveTrapezoidRule<T>::my_tol()),
                                         my_z(z) { }

      virtual ~RecursiveTrapezoidJ0() { }

    private:
      const T my_z;

      static const T& my_pi()
      {
        using ef::pi;
        static const T val_pi(pi());
        return val_pi;
      }

      virtual T my_function(const T& x) const
      {
        using ef::sin;
        using ef::cos;
        using ef::sin;
        using ef::cos;

        return cos(my_z * sin(x));
      }
    };
  }
}

e_float examples::nr_005::recursive_trapezoid_j0(const e_float& x)
{
  const RecursiveTrapezoidJ0<e_float> rtj0(x);

  return rtj0.operation() / ef::pi();
}

e_float examples::nr_005::recursive_trapezoid_j0_test()
{
  static const e_float x = 12 + ef::euler_gamma();

  // 0.159173271527357802204942501548038871253206194372493130822680934787563497893037328740164393597568252301865702570378398880860682236726100409919853153743915268717088574854150606158611519229030326608759564180402494636294191302749371577318193634102221248421334625284874694275641406259808758076594337465967547049811084362150113968020614293285415572403059940356307102311258141429281724728658633984360051908653556842543007612635514367876428092574416984146400
  return recursive_trapezoid_j0(x);
}
