#ifndef ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_RELATIONAL_HPP
#define ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_RELATIONAL_HPP
#include "impl/xmacros.hpp"

namespace zxshady {
namespace tmp {

  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(equal_to, ==);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(not_equal_to, !=);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(less, <);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(less_equal, <=);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(greater, >);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(greater_equal, >=);

#ifdef __cpp_variable_templates
  template<typename T, typename U = T>
  constexpr bool has_operator_equal_to_v = has_operator_equal_to<T, U>::value;
  template<typename T, typename U = T>
  constexpr bool has_operator_not_equal_to_v = has_operator_not_equal_to<T, U>::value;
  template<typename T, typename U = T>
  constexpr bool has_operator_less_v = has_operator_less<T, U>::value;
  template<typename T, typename U = T>
  constexpr bool has_operator_less_equal_v = has_operator_less_equal<T, U>::value;
  template<typename T, typename U = T>
  constexpr bool has_operator_greater_v = has_operator_greater<T, U>::value;
  template<typename T, typename U = T>
  constexpr bool has_operator_greater_equal_v = has_operator_greater_equal<T, U>::value;

#endif

} // namespace tmp
} // namespace zxshady

#endif // !ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_RELATIONAL_HPP