#ifndef ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_RELATIONAL_HPP
#define ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_RELATIONAL_HPP

#include "impl/xmacros.hpp"

namespace zxshady {
namespace tmp {

  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(plus, +);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(plus_assign, +=);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(minus, -);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(minus_assign, -=);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(modulus, %);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(modulus_assign, %=);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(multiply, *);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(multiply_assign, *=);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(divide, /);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(divide_assign, /=);

#ifdef __cpp_variable_templates
  template<typename T, typename U = T>
  constexpr bool has_operator_plus_v = has_operator_plus<T, U>::value;
  template<typename T, typename U = T>
  constexpr bool has_operator_plus_assign_v = has_operator_plus_assign<T, U>::value;
  template<typename T, typename U = T>
  constexpr bool has_operator_minus_v = has_operator_minus<T, U>::value;
  template<typename T, typename U = T>
  constexpr bool has_operator_minus_assign_v = has_operator_minus_assign<T, U>::value;
  template<typename T, typename U = T>
  constexpr bool has_operator_modulus_v = has_operator_modulus<T, U>::value;
  template<typename T, typename U = T>
  constexpr bool has_operator_modulus_assign_v = has_operator_modulus_assign<T, U>::value;
  template<typename T, typename U = T>
  constexpr bool has_operator_multiply_v = has_operator_multiply<T, U>::value;
  template<typename T, typename U = T>
  constexpr bool has_operator_multiply_assign_v = has_operator_multiply_assign<T, U>::value;
  template<typename T, typename U = T>
  constexpr bool has_operator_divide_v = has_operator_divide<T, U>::value;
  template<typename T, typename U = T>
  constexpr bool has_operator_divide_assign_v = has_operator_divide_assign<T, U>::value;
#endif

} // namespace tmp
} // namespace zxshady

#endif // !ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_RELATIONAL_HPP