## e_float-2021
Multiple precision floating point (legacy project) derived work from e_float

This work is based on an earlier work:\
C.M. Kormanyos, _Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations_,\
in [ACM TOMS (37) 4, February 2011](https://doi.acm.org/10.1145/1916461.1916469)

## Description

e_float-2021 implements multiple-precision floating-point
data types in modern C++11. Three versions are supported
in three individual build configurations. There is a native,
portable decimal float type called `efx::e_float`.
There are also wrapped versions
for [GMP](https://gmplib.org/)
and [MPFR](https://www.mpfr.org)
called `gmp::e_float` and `mpfr::e_float`, respectively.

e_float-2021 is derived from the original work mentioned above.
In this derived work, the code has been updated to conform with
C++11, 14, 17, 20. The code has been modernized and a dedicated
effort has been made to keep it
compatible with C++ language evolution.
Certain special function tests have been removed
retaining just a core of the most essential key functions
and tests in e_float-2021.

For the _efx_ version (which is a decimal floating point implementation),
a naive FFT brings the digit range up to a million decimal digits or more.
This digit range was not available to the _efx_ version at the time
of the original e_float paper.
The _gmp_ and _mpfr_ versions support high digit counts natively
from their wrapped libraries.

## Building

Build in Linux or MacOS with GNUmake.
  - Open a terminal in the directory  [./libs/e_float/build](./libs/e_float/build).
  - The terminal should be located directly in [./libs/e_float/build](./libs/e_float/build) for the paths to work out (be found by the upcoming build).
  - Identify the [Makefile](./libs/e_float/build/Makefile).
  - Execute `make` with the command below (or similar with other supported options).

```
make MP=efx TYP_TOOLSET=g++ TYP_STD=c++11 TYP_TEST=E_FLOAT_TEST_REAL_IMAG_TESTS rebuild
```

Build in Microsoft Visual Studio
  - Identify the `e_float` sln-project file [./libs/e_float/build/e_float.sln](./libs/e_float/build/e_float.sln).
  - Rebuild the configuration `x64-release-efx`, as shown in the [build image](./images/e_float_in_vs.jpg).

## History

The e_float project influenced the concept and creation
of [Boost.Multiprecision](https://www.boost.org/doc/libs/1_75_0/libs/multiprecision/doc/html/index.html).
After the publication of the e_float paper in TOMS,
the code was essentially evaluated as to how it
wrapped and implemented certain big number backends.
This was adopted for the partial early design of `cpp_dec_float`
in Boost.Multiprecision. As Boost.Multiprecision progressed,
the original rudimentary concept motivated partially from e_float
was entirely re-implemented, strengthened and extended
for Boost's novel, flexible, header-only template design
having its own frontend/backend concept.

## Legacy

e_float-2021 remains supported in order to provide historical
and legacy insight into the early origins of a work that influenced
Boost.Multiprecision. The algorithms and implementation methods
in e_float-2021 may also provide guidance and practical implementation advice
regarding how to deal with big floating-point implementations
within the context of modern C++.
