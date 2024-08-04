#ifndef ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_ACCESSORS_HPP
#define ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_ACCESSORS_HPP

#include "impl/xmacros.hpp"

namespace zxshady {
namespace tmp {

  ZXSHADY_XMACRO_HAS_UNARY_OPERATOR(dereference, *);


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
    template<typename U>
    static auto member_check(U&& u) -> decltype(ZXSHADY_FWD(u).operator->(), std::true_type{});
    static auto member_check(...) -> std::false_type;
  public:
    static constexpr bool free       = false;
    static constexpr bool member     = decltype(has_operator_arrow::member_check(std::declval<T>()))::value;
    static constexpr bool overloaded = member;
    using norefT                     = typename std::remove_reference<T>::type;
    using noarrT                     = typename std::remove_extent<typename std::remove_pointer<norefT>::type>::type;

    static constexpr bool value = member ||
      ((std::is_class<noarrT>::value || std::is_union<noarrT>::value) &&
       (std::is_pointer<norefT>::value || std::is_array<norefT>::value));
  };


#ifdef __cpp_variable_templates
  

  template<typename T>
  constexpr bool has_operator_dereference_v = has_operator_dereference<T>::value;
  
  template<typename T>
  constexpr bool has_operator_arrow_v = has_operator_arrow<T>::value;
  

  #ifdef __cpp_multidimensional_subscript
  template<typename T, typename... Indices>
  constexpr bool has_operator_subscript_v = has_operator_subscript<T, Indices...>::value;
  #else
  template<typename T, typename Index>
  constexpr bool has_operator_subscript_v = has_operator_subscript<T, Index>::value;
  #endif
#endif

} // namespace tmp
} // namespace zxshady

#endif // ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_ACCESSORS_HPP