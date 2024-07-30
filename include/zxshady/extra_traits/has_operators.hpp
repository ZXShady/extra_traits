#ifndef ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_HPP
#define ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_HPP

#include "macros.hpp"
#include <type_traits>
#include <utility> // std::declval

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

  #define ZXSHADY_XMACRO_HAS_POST_INC_DEC_OPERATOR(op_name, op_symbol)                             \
    template<typename T>                                                                           \
    struct has_operator_##op_name {                                                                \
      static constexpr bool free       = requires(T t) { operator op_symbol(ZXSHADY_FWD(t), 0); }; \
      static constexpr bool member     = requires(T t) { ZXSHADY_FWD(t).operator op_symbol(0); };  \
      static constexpr bool overloaded = free || member;                                           \
      static constexpr bool value      = requires(T t) { ZXSHADY_FWD(t) op_symbol; };              \
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

#endif // __cpp_concepts

namespace zxshady {
namespace tmp {


  ZXSHADY_XMACRO_HAS_POST_INC_DEC_OPERATOR(post_increment, ++);
  ZXSHADY_XMACRO_HAS_POST_INC_DEC_OPERATOR(post_decrement, --);
  ZXSHADY_XMACRO_HAS_UNARY_OPERATOR(pre_decrement, --);
  ZXSHADY_XMACRO_HAS_UNARY_OPERATOR(pre_increment, ++);
  ZXSHADY_XMACRO_HAS_UNARY_OPERATOR(dereference, *);

  ZXSHADY_XMACRO_HAS_UNARY_OPERATOR(negate, -);
  ZXSHADY_XMACRO_HAS_UNARY_OPERATOR(complement, ~);
  ZXSHADY_XMACRO_HAS_UNARY_OPERATOR(unary_minus, -);
  ZXSHADY_XMACRO_HAS_UNARY_OPERATOR(unary_plus, +);

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

  // logical
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(logical_and, &&);
  ZXSHADY_XMACRO_HAS_UNARY_OPERATOR(logical_not, !);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(logical_or, ||);

  
  // arithematic
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
  // relational
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(equal_to, ==);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(not_equal_to, !=);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(less, <);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(less_equal, <=);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(greater, >);
  ZXSHADY_XMACRO_HAS_BINARY_OPERATOR(greater_equal, >=);

  //delete_operator
  //new_operator
#ifdef __cpp_multidimensional_subscript
  template<typename T, typename... Indices>
  struct has_operator_subscript {
  private:
    using this_type = has_operator_subscript;
    template<typename U = T>
    static auto member_check(U&& u, Indices&&... indices)
      -> decltype(ZXSHADY_FWD(u).operator[](ZXSHADY_FWD(indices)...), std::true_type{});
    static auto member_check(...) -> std::false_type;
    template<typename U = T>
    static auto check(U&& u, Indices&&... indices) -> decltype(ZXSHADY_FWD(u)[ZXSHADY_FWD(indices)...], std::true_type{});
    static auto check(...) -> std::false_type;

  public:
    static constexpr bool free = false;
    static constexpr bool member = decltype(this_type::member_check(std::declval<T>(), std::declval<Indices>()...))::value;
    static constexpr bool overloaded = member;
    static constexpr bool value      = decltype(this_type::check(std::declval<T>(), std::declval<Indices>()...))::value;
  };
#else
  template<typename T, typename Index>
  struct has_operator_subscript {
  private:
    using this_type = has_operator_subscript;
    template<typename U = T>
    static auto member_check(U&& u, Index&& index)
      -> decltype(ZXSHADY_FWD(u).operator[](ZXSHADY_FWD(index)), std::true_type{});
    static auto member_check(...) -> std::false_type;
    template<typename U = T>
    static auto check(U&& u, Index&& index) -> decltype(ZXSHADY_FWD(u)[ZXSHADY_FWD(index)], std::true_type{});
    static auto check(...) -> std::false_type;

  public:
    static constexpr bool free   = false;
    static constexpr bool member = decltype(this_type::member_check(std::declval<T>(), std::declval<Index>()))::value;
    static constexpr bool overloaded = member;
    static constexpr bool value      = decltype(this_type::check(std::declval<T>(), std::declval<Index>()))::value;
  };
#endif // __cpp_multidimensional_subscript

  template<typename T>
  struct has_operator_arrow {
  private:
    using this_type = has_operator_arrow;
    template<typename U>
    static auto member_check(U&& u) -> decltype(ZXSHADY_FWD(u).operator->(), std::true_type{});
    static auto member_check(...) -> std::false_type;
  public:
    static constexpr bool free       = false;
    static constexpr bool member     = decltype(this_type::member_check(std::declval<T>()))::value;
    static constexpr bool overloaded = member;
    using norefT                     = typename std::remove_reference<T>::type;
    using noarrT                     = typename std::remove_extent<typename std::remove_pointer<norefT>::type>::type;

    static constexpr bool value = member ||
      ((std::is_class<noarrT>::value || std::is_union<noarrT>::value) &&
       (std::is_pointer<norefT>::value || std::is_array<norefT>::value));
  };

  template<typename T, typename... Args>
  struct has_operator_call {
  private:
    using this_type = has_operator_call;
    template<typename U>
    static auto member_check(U&& u) -> decltype(ZXSHADY_FWD(u).operator()(std::declval<Args>()...), std::true_type{});
    static auto member_check(...) -> std::false_type;
    template<typename U>
    static auto check(U&& u) -> decltype(ZXSHADY_FWD(u)(std::declval<Args>()...), std::true_type{});
    static auto check(...) -> std::false_type;
  public:
    static constexpr bool free       = false;
    static constexpr bool member     = decltype(this_type::member_check(std::declval<T>))::value;
    static constexpr bool overloaded = member;
    static constexpr bool value      = decltype(this_type::check(std::declval<T>()))::value;
  };


#ifdef __cpp_variable_templates
  #define MACRO_P(name)                  \
    template<typename T, typename U = T> \
    constexpr bool has_operator_##name##_v = has_operator_##name<T, U>::value
  #define MACRO_P_UNARY(name) \
    template<typename T>      \
    constexpr bool has_operator_##name##_v = has_operator_##name<T>::value;
  MACRO_P_UNARY(post_increment);
  MACRO_P_UNARY(post_decrement);
  MACRO_P_UNARY(pre_decrement);
  MACRO_P_UNARY(pre_increment);
  MACRO_P_UNARY(dereference);

  MACRO_P_UNARY(negate);
  MACRO_P_UNARY(complement);
  MACRO_P_UNARY(unary_minus);
  MACRO_P_UNARY(unary_plus);

  MACRO_P(bit_and);
  MACRO_P(bit_and_assign);
  MACRO_P(bit_or);
  MACRO_P(bit_or_assign);
  MACRO_P(bit_xor);
  MACRO_P(bit_xor_assign);
  MACRO_P(left_shift);
  MACRO_P(left_shift_assign);
  MACRO_P(right_shift);
  MACRO_P(right_shift_assign);

  // logical
  MACRO_P(logical_and);
  MACRO_P_UNARY(logical_not);
  MACRO_P(logical_or);

  // arithematic
  MACRO_P(plus);
  MACRO_P(plus_assign);
  MACRO_P(minus);
  MACRO_P(minus_assign);
  MACRO_P(modulus);
  MACRO_P(modulus_assign);
  MACRO_P(multiply);
  MACRO_P(multiply_assign);
  MACRO_P(divide);
  MACRO_P(divide_assign);
  // relational
  MACRO_P(equal_to);
  MACRO_P(not_equal_to);
  MACRO_P(less);
  MACRO_P(less_equal);
  MACRO_P(greater);
  MACRO_P(greater_equal);

  MACRO_P_UNARY(arrow)
  #ifdef __cpp_multidimensional_subscript
  template<typename T, typename... Indices>
  constexpr bool has_operator_subscript_v = has_operator_subscript<T, Indices...>::value;
  #elif defined(__cpp_variable_templates)
  template<typename T, typename Index>
  constexpr bool has_operator_subscript_v = has_operator_subscript<T, Index>::value;
  #endif
  
  template<typename T, typename... Args>
  constexpr bool has_operator_call_v = has_operator_call<T, Args...>::value;

  #undef MACRO_P_UNARY
  #undef MACRO_P
  #undef ZXSHADY_INDEXES_1044


#endif // __cpp_variable_templates

} // namespace tmp
} // namespace zxshady

#endif // !ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_HPP
