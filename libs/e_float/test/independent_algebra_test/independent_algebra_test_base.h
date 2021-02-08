#ifndef INDEPENDENT_ALGEBRA_TEST_BASE_2020_10_17_H_
  #define INDEPENDENT_ALGEBRA_TEST_BASE_2020_10_17_H_

  #include <cstdint>
  #include <string>

  namespace test { namespace independent_algebra {

  class independent_algebra_test_base
  {
  public:
    virtual ~independent_algebra_test_base() { }

    virtual void get_string(std::string& p) const = 0;

  protected:
    independent_algebra_test_base() { }

    independent_algebra_test_base(const char* str) { }
  };

  } }

#endif // INDEPENDENT_ALGEBRA_TEST_BASE_2020_10_17_H_
