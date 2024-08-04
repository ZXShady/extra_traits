#ifndef ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_UNARY_PLUS_MINUS_HPP
#define ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_UNARY_PLUS_MINUS_HPP

#include "impl/xmacros.hpp"

namespace zxshady {
namespace tmp {

  ZXSHADY_XMACRO_HAS_UNARY_OPERATOR(unary_plus, +);
  ZXSHADY_XMACRO_HAS_UNARY_OPERATOR(unary_minus, -);

#ifdef __cpp_variable_templates
  template<typename T>
  constexpr bool has_operator_unary_minus_v = has_operator_unary_minus<T>::value;
  template<typename T>
  constexpr bool has_operator_unary_plus_v = has_operator_unary_plus<T>::value;
#endif
} // namespace tmp
} // namespace zxshady

#endif // ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_UNARY_PLUS_MINUS_HPP