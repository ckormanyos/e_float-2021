// f2c.h  --  Standard Fortran to C header file
// Modified by Chris for improved portability.

// barf  [ba:rf]  2.  "He suggested using FORTRAN, and everybody barfed."
// - From The Shogakukan DICTIONARY OF NEW ENGLISH (Second edition)

#ifndef F2C_INCLUDE
  #define F2C_INCLUDE

  typedef long int integer;
  typedef unsigned long int uinteger;
  typedef char* address;
  typedef short int shortint;
  typedef float real;
  typedef double doublereal;
  typedef struct struct_complex { real r, i; } complex;
  typedef struct struct_doublecomplex { doublereal r, i; } doublecomplex;
  typedef long int logical;
  typedef short int shortlogical;
  typedef char logical1;
  typedef char integer1;
  typedef signed long long longint;     // Adjust for signed integer*8
  typedef unsigned long long ulongint;  // Adjust for unsigned integer*8
  #define qbit_clear(a,b)  ((a) & ~((ulongint)1 << (b)))
  #define qbit_set(a,b)  ((a) |  ((ulongint)1 << (b)))

  #define TRUE_ (1)
  #define FALSE_ (0)

  // Extern is for use with -E
  #ifndef Extern
  #define Extern extern
  #endif

  // I/O stuff
  typedef long int flag;
  typedef long int ftnlen;
  typedef long int ftnint;

  // external read, write
  typedef struct struct_clist
  {
    flag cierr;
    ftnint ciunit;
    flag ciend;
    char* cifmt;
    ftnint cirec;
  }
  cilist;

  // internal read, write
  typedef struct struct_icilist
  {
    flag   icierr;
    char*  iciunit;
    flag   iciend;
    char*  icifmt;
    ftnint icirlen;
    ftnint icirnum;
  }
  icilist;

  // open
  typedef struct struct_olist
  {
    flag   oerr;
    ftnint ounit;
    char*  ofnm;
    ftnlen ofnmlen;
    char*  osta;
    char*  oacc;
    char*  ofm;
    ftnint orl;
    char*  oblnk;
  }
  olist;

  // close
  typedef struct struct_cllist
  {
    flag   cerr;
    ftnint cunit;
    char*  csta;
  }
  cllist;

  // rewind, backspace, endfile
  typedef struct struct_alist
  {
    flag   aerr;
    ftnint aunit;
  }
  alist;

  // inquire
  typedef struct struct_inlist
  {
    flag     inerr;
    ftnint   inunit;
    char*    infile;
    ftnlen   infilen;
    ftnint*  inex;  // parameters in standard's order
    ftnint*  inopen;
    ftnint*  innum;
    ftnint*  innamed;
    char*    inname;
    ftnlen   innamlen;
    char*    inacc;
    ftnlen   inacclen;
    char*    inseq;
    ftnlen   inseqlen;
    char *   indir;
    ftnlen   indirlen;
    char*    infmt;
    ftnlen   infmtlen;
    char*    inform;
    ftnint   informlen;
    char*    inunf;
    ftnlen   inunflen;
    ftnint*  inrecl;
    ftnint*  innrec;
    char*    inblank;
    ftnlen   inblanklen;
  }
  inlist;

  #define VOID void

  typedef union union_Multitype
  {
    // for multiple entry points
    integer1      g;
    shortint      h;
    integer       i;
    //longint       j;
    real          r;
    doublereal    d;
    complex       c;
    doublecomplex z;
  }
  Multitype;

  typedef struct struct_Vardesc
  {
    // for Namelist
    char*   name;
    char*   addr;
    ftnlen* dims;
    int     type;
  }
  Vardesc;

  typedef struct struct_Namelist
  {
    char*     name;
    Vardesc** vars;
    int       nvars;
  }
  Namelist;

  #define abs(x) ((x) >= 0 ? (x) : -(x))
  #define dabs(x) (doublereal)abs(x)
  #ifndef min
  #define min(a,b) ((a) <= (b) ? (a) : (b))
  #endif
  #ifndef max
  #define max(a,b) ((a) >= (b) ? (a) : (b))
  #endif
  #define dmin(a,b) (doublereal)min(a,b)
  #define dmax(a,b) (doublereal)max(a,b)
  #define bit_test(a,b)  ((a) >> (b) & 1)
  #define bit_clear(a,b)  ((a) & ~((uinteger)1 << (b)))
  #define bit_set(a,b)  ((a) |  ((uinteger)1 << (b)))

  // procedure parameter types for -A and -C++

  #define F2C_proc_par_types 1

  #ifdef __cplusplus
    typedef int (*U_fp)(...);          // Unknown procedure type
    typedef shortint (*J_fp)(...);
    typedef integer (*I_fp)(...);
    typedef real (*R_fp)(...);
    typedef doublereal (*D_fp)(...), (*E_fp)(...);
    typedef VOID (*C_fp)(...);         // Complex
    typedef VOID (*Z_fp)(...);         // Double Complex
    typedef logical (*L_fp)(...);
    typedef shortlogical (*K_fp)(...);
    typedef VOID (*H_fp)(...);         // Character
    typedef int (*S_fp)(...);          // Subroutine
  #else
    typedef int  (*U_fp)();            // Unknown procedure type
    typedef shortint (*J_fp)();
    typedef integer (*I_fp)();
    typedef real (*R_fp)();
    typedef doublereal (*D_fp)(), (*E_fp)();
    typedef  VOID (*C_fp)();           // Complex
    typedef  VOID (*Z_fp)();           // Double Complex
    typedef logical (*L_fp)();
    typedef shortlogical (*K_fp)();
    typedef  VOID (*H_fp)();           // Character
    typedef  int (*S_fp)();            // Subroutine
  #endif

  // E_fp is for real functions when -R is not specified
  typedef VOID C_f;        // complex function
  typedef VOID H_f;        // character function
  typedef VOID Z_f;        // double complex function
  typedef doublereal E_f;  // real function with -R not specified

  // undef any lower-case symbols that your C compiler predefines, e.g.:

  #ifndef Skip_f2c_Undefs
    #undef cray
    #undef gcos
    #undef mc68010
    #undef mc68020
    #undef mips
    #undef pdp11
    #undef sgi
    #undef sparc
    #undef sun
    #undef sun2
    #undef sun3
    #undef sun4
    #undef u370
    #undef u3b
    #undef u3b2
    #undef u3b5
    #undef unix
    #undef vax
  #endif

#endif // F2C_INCLUDE
