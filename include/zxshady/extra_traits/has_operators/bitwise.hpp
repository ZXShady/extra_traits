#ifndef ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_BITWISE_HPP
#define ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_BITWISE_HPP
#include "impl/xmacros.hpp"
namespace zxshady {
namespace tmp {

  ZXSHADY_XMACRO_HAS_UNARY_OPERATOR(complement, ~);

  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(bit_and, &);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(bit_and_assign, &=);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(bit_or, |);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(bit_or_assign, |=);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(bit_xor, ^);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(bit_xor_assign, ^=);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(left_shift, <<);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(left_shift_assign, <<=);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(right_shift, >>);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(right_shift_assign, >>=);
  

  #ifdef __cpp_variable_templates
  // clang-format off
  template<typename T>                 constexpr bool has_operator_complement_v = has_operator_complement<T>::value;
  template<typename T, typename U = T> constexpr bool has_operator_bit_and_v = has_operator_bit_and<T, U>::value;
  template<typename T, typename U = T> constexpr bool has_operator_bit_and_assign_v = has_operator_bit_and_assign<T, U>::value;
  template<typename T, typename U = T> constexpr bool has_operator_bit_or_v = has_operator_bit_or<T, U>::value;
  template<typename T, typename U = T> constexpr bool has_operator_bit_or_assign_v = has_operator_bit_or_assign<T, U>::value;
  template<typename T, typename U = T> constexpr bool has_operator_bit_xor_v = has_operator_bit_xor<T, U>::value;
  template<typename T, typename U = T> constexpr bool has_operator_bit_xor_assign_v = has_operator_bit_xor_assign<T, U>::value;
  template<typename T, typename U = T> constexpr bool has_operator_left_shift_v = has_operator_left_shift<T, U>::value;
  template<typename T, typename U = T> constexpr bool has_operator_left_shift_assign_v = has_operator_left_shift_assign<T, U>::value;
  template<typename T, typename U = T> constexpr bool has_operator_right_shift_v = has_operator_right_shift<T, U>::value;
  template<typename T, typename U = T> constexpr bool has_operator_right_shift_assign_v = has_operator_right_shift_assign<T, U>::value;
  // clang-format on
#endif
} // namespace tmp
} // namespace zxshady
#endif // ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_BITWISE_HPP