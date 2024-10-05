#ifndef ZXSHADY_EXTRA_TRAITS_IS_STATIC_CASTABLE_HPP
#define ZXSHADY_EXTRA_TRAITS_IS_STATIC_CASTABLE_HPP

#include <type_traits>
#include <utility>

namespace zxshady {
namespace tmp {

  template<typename From, typename To, typename = void>
  struct is_static_castable : std::false_type {};

  template<typename From, typename To>
  struct is_static_castable<From, To, decltype(void(static_cast<To>(std::declval<From>())))> : std::true_type {};


#ifdef __cpp_variable_templates
  template<typename From, typename To>
  constexpr bool is_static_castable_v = is_static_castable<From, To>::value;
#endif // __cpp_variable_templates

} // namespace tmp
} // namespace zxshady


#endif // !ZXSHADY_EXTRA_TRAITS_IS_STATIC_CASTABLE_HPP