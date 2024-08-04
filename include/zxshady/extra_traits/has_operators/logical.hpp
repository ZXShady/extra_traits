#ifndef ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_LOGICAL_HPP
#define ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_LOGICAL_HPP

#include "impl/xmacros.hpp"

namespace zxshady {
namespace tmp {

  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(logical_and, &&);
  ZXSHADY_XMACRO_HAS_UNARY_OPERATOR(logical_not, !);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(logical_or, ||);

#ifdef __cpp_variable_templates
  template<typename T, typename U = T>
  constexpr bool has_operator_logical_and_v = has_operator_logical_and<T, U>::value;
  template<typename T>
  constexpr bool has_operator_logical_not_v = has_operator_logical_not<T>::value;
  template<typename T, typename U = T>
  constexpr bool has_operator_logical_or_v = has_operator_logical_or<T, U>::value;
#endif
} // namespace tmp
} // namespace zxshady

#endif // ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_LOGICAL_HPP