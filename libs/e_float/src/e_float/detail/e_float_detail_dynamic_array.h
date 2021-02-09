
//          Copyright Christopher Kormanyos 1999 - 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef E_FLOAT_DETAIL_DYNAMIC_ARRAY_2014_08_11_HPP_
  #define E_FLOAT_DETAIL_DYNAMIC_ARRAY_2014_08_11_HPP_

  #include <memory>
  #include <utility/util_dynamic_array.h>

  namespace ef { namespace detail {

  template <typename MyType,
            const std::uint_fast32_t MySize,
            typename MyAlloc>
  class fixed_dynamic_array final : public util::dynamic_array<MyType, MyAlloc>
  {
  private:
    using base_class_type = util::dynamic_array<MyType, MyAlloc>;

  public:
    fixed_dynamic_array(const typename base_class_type::size_type       s  = MySize,
                        const typename base_class_type::value_type&     v = typename base_class_type::value_type(),
                        const typename base_class_type::allocator_type& a = typename base_class_type::allocator_type())
      : base_class_type(MySize, typename base_class_type::value_type(), a)
    {
      std::fill(base_class_type::begin(),
                base_class_type::begin() + (std::min)(MySize, (std::uint_fast32_t) s),
                v);
    }

    constexpr fixed_dynamic_array(const fixed_dynamic_array& other_array)
      : base_class_type((const base_class_type&) other_array) { }

    explicit fixed_dynamic_array(std::initializer_list<typename base_class_type::value_type> lst)
      : base_class_type(MySize)
    {
      std::copy(lst.begin(),
                lst.begin() + (std::min)((std::uint_fast32_t) lst.size(), MySize),
                base_class_type::begin());
    }

    constexpr fixed_dynamic_array(fixed_dynamic_array&& other_array)
      : base_class_type((base_class_type&&) other_array) { }

    fixed_dynamic_array& operator=(const fixed_dynamic_array& other_array)
    {
      base_class_type::operator=((const base_class_type&) other_array);

      return *this;
    }

    fixed_dynamic_array& operator=(fixed_dynamic_array&& other_array)
    {
      base_class_type::operator=((base_class_type&&) other_array);

      return *this;
    }

    virtual ~fixed_dynamic_array() = default;

    static constexpr typename base_class_type::size_type static_size()
    {
      return MySize;
    }
  };

  } } // namespace ef::detail

#endif // E_FLOAT_DETAIL_DYNAMIC_ARRAY_2014_08_11_HPP_
