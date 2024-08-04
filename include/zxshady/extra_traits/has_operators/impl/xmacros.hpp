#ifndef ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_XMACROS_HPP
#define ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_XMACROS_HPP

#include "../../macros.hpp"

#ifdef __cpp_concepts

  #define ZXSHADY_XMACRO_HAS_UNARY_OPERATOR(op_name, op_symbol)                                  \
    template<typename T>                                                                         \
    struct has_operator_##op_name {                                                              \
      static constexpr bool free       = requires(T t) { operator op_symbol(ZXSHADY_FWD(t)); };  \
      static constexpr bool member     = requires(T t) { ZXSHADY_FWD(t).operator op_symbol(); }; \
      static constexpr bool overloaded = free || member;                                         \
      static constexpr bool value      = requires(T t) { op_symbol ZXSHADY_FWD(t); };            \
    }
  #define ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(op_name, op_symbol)                                                     \
    template<typename T, typename U = T>                                                                             \
    struct has_operator_##op_name {                                                                                  \
      static constexpr bool free       = requires(T t, U u) { operator op_symbol(ZXSHADY_FWD(t), ZXSHADY_FWD(u)); }; \
      static constexpr bool member     = requires(T t, U u) { ZXSHADY_FWD(t).operator op_symbol(ZXSHADY_FWD(u)); };  \
      static constexpr bool overloaded = free || member;                                                             \
      static constexpr bool value      = requires(T t, U u) { ZXSHADY_FWD(t) op_symbol ZXSHADY_FWD(u); };            \
    }



#else

  #define ZXSHADY_XMACRO_HAS_UNARY_OPERATOR(op_name, op_symbol)                                           \
    template<typename T>                                                                                  \
    struct has_operator_##op_name {                                                                       \
      using this_type = has_operator_##op_name;                                                           \
      template<typename U>                                                                                \
      static auto member_check(U&& u) -> decltype(ZXSHADY_FWD(u).operator op_symbol(), std::true_type{}); \
      static auto member_check(...) -> std::false_type;                                                   \
      template<typename U>                                                                                \
      static auto free_check(U&& u) -> decltype(operator op_symbol(ZXSHADY_FWD(u)), std::true_type{});    \
      static auto free_check(...) -> std::false_type;                                                     \
      template<typename U>                                                                                \
      static auto           check(U&& u) -> decltype(op_symbol ZXSHADY_FWD(u), std::true_type{});         \
      static auto           check(...) -> std::false_type;                                                \
      static constexpr bool free       = decltype(this_type::free_check(std::declval<T>()))::value;       \
      static constexpr bool member     = decltype(this_type::member_check(std::declval<T>()))::value;     \
      static constexpr bool overloaded = member || free;                                                  \
      static constexpr bool value      = decltype(this_type::check(std::declval<T>()))::value;            \
    }


  #define ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(op_name, op_symbol)                                                         \
    template<typename T, typename U = T>                                                                                 \
    struct has_operator_##op_name {                                                                                      \
      using this_type = has_operator_##op_name;                                                                          \
      template<typename L, typename R>                                                                                   \
      static auto member_check(L&& l, R&& r)                                                                             \
        -> decltype(ZXSHADY_FWD(l).operator op_symbol(ZXSHADY_FWD(r)), std::true_type{});                                \
      static auto member_check(...) -> std::false_type;                                                                  \
      template<typename L, typename R>                                                                                   \
      static auto free_check(L&& l, R&& r)                                                                               \
        -> decltype(operator op_symbol(ZXSHADY_FWD(l), ZXSHADY_FWD(r)), std::true_type{});                               \
      static auto free_check(...) -> std::false_type;                                                                    \
      template<typename L, typename R>                                                                                   \
      static auto           check(L&& l, R&& r) -> decltype(ZXSHADY_FWD(l) op_symbol ZXSHADY_FWD(r), std::true_type{});  \
      static auto           check(...) -> std::false_type;                                                               \
      static constexpr bool free       = decltype(this_type::free_check(std::declval<T>(), std::declval<U>()))::value;   \
      static constexpr bool member     = decltype(this_type::member_check(std::declval<T>(), std::declval<U>()))::value; \
      static constexpr bool overloaded = member || free;                                                                 \
      static constexpr bool value      = decltype(this_type::check(std::declval<T>(), std::declval<U>()))::value;        \
    } // namespace tmp

#endif // __cpp_concepts

#endif // !ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_XMACROS_HPP