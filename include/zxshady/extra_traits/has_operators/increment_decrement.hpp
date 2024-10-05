#ifndef ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_INCREMENT_DECREMENT_HPP
#define ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_INCREMENT_DECREMENT_HPP

#include "impl/xmacros.hpp"

#ifdef __cpp_concepts
  #define ZXSHADY_XMACRO_HAS_POST_INC_DEC_OPERATOR(op_name, op_symbol)                             \
    template<typename T>                                                                           \
    struct has_operator_##op_name {                                                                \
      static constexpr bool free       = requires(T t) { operator op_symbol(ZXFWD(t), 0); }; \
      static constexpr bool member     = requires(T t) { ZXFWD(t).operator op_symbol(0); };  \
      static constexpr bool overloaded = free || member;                                           \
      static constexpr bool value      = requires(T t) { ZXFWD(t) op_symbol; };              \
    }
#else
  #define ZXSHADY_XMACRO_HAS_POST_INC_DEC_OPERATOR(op_name, op_symbol)                                \
    template<typename T>                                                                              \
    struct has_operator_##op_name {                                                                   \
      using this_type = has_operator_##op_name;                                                       \
      template<typename U>                                                                            \
      static auto member_check(U&& u) -> decltype(u.operator op_symbol(0), std::true_type{});         \
      static auto member_check(...) -> std::false_type;                                               \
      template<typename U>                                                                            \
      static auto free_check(U&& u) -> decltype(operator op_symbol(u, 0), std::true_type{});          \
      static auto free_check(...) -> std::false_type;                                                 \
      template<typename U>                                                                            \
      static auto           check(U&& u) -> decltype(u op_symbol, std::true_type{});                  \
      static auto           check(...) -> std::false_type;                                            \
      static constexpr bool free       = decltype(this_type::free_check(std::declval<T>()))::value;   \
      static constexpr bool member     = decltype(this_type::member_check(std::declval<T>()))::value; \
      static constexpr bool overloaded = member || free;                                              \
      static constexpr bool value      = decltype(this_type::check(std::declval<T>()))::value;        \
    }
#endif

namespace zxshady {
namespace tmp {

  ZXSHADY_XMACRO_HAS_POST_INC_DEC_OPERATOR(post_increment, ++);
  ZXSHADY_XMACRO_HAS_POST_INC_DEC_OPERATOR(post_decrement, --);
  ZXSHADY_XMACRO_HAS_UNARY_OPERATOR(pre_decrement, --);
  ZXSHADY_XMACRO_HAS_UNARY_OPERATOR(pre_increment, ++);


#ifdef __cpp_variable_templates

  template<typename T>
  constexpr bool has_operator_post_increment_v = has_operator_post_increment<T>::value;
  template<typename T>
  constexpr bool has_operator_post_decrement_v = has_operator_post_decrement<T>::value;
  template<typename T>
  constexpr bool has_operator_pre_decrement_v = has_operator_pre_decrement<T>::value;
  template<typename T>
  constexpr bool has_operator_pre_increment_v = has_operator_pre_increment<T>::value;

#endif
} // namespace tmp
} // namespace zxshady


#endif // ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_INCREMENT_DECREMENT_HPP