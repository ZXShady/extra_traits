#ifndef ZXSHADY_EXTRA_TRAITS_UTILITY_HPP
#define ZXSHADY_EXTRA_TRAITS_UTILITY_HPP

#include "macros.hpp"
#include <type_traits>

namespace zxshady {
namespace tmp {

  template<typename...>
  struct always_false : ::std::false_type {};

  template<typename...>
  struct always_true : ::std::true_type {};

  template<std::size_t Index, typename T>
  struct type_with_index {
    static constexpr std::size_t index = Index;
    using type                         = T;
  };

#ifdef __cpp_variable_templates

  template<typename... Ts>
  constexpr bool false_v = always_false<Ts...>::value;

  template<typename... Ts>
  constexpr bool true_v = always_false<Ts...>::value;

#endif // __cpp_variable_templates

  template<typename T, typename...>
  using type_t = T;

  template<std::size_t Value>
  using index_constant = std::integral_constant<std::size_t, Value>;

  template<typename T>
  using alignof_constant = std::integral_constant<std::size_t,alignof(T)>;

  template<typename T>
  using sizeof_constant = std::integral_constant<std::size_t, sizeof(T)>;

  #ifdef __cpp_nontype_template_parameter_auto
  template<auto V>
  using constant = std::integral_constant<decltype(V), V>;
#endif


  template<typename...>
  struct empty_base {};

  template<typename... Ts>
  struct inherit_from : Ts... {};

  

  template<template<typename...> class Template, typename... BoundArgs>
  struct bind_template {
    template<typename... Args>
    struct type : Template<BoundArgs..., Args...> {};
  };

#define ZXSHADY_BIND_TEMPLATE(...) ::zxshady::tmp::bind_template<__VA_ARGS__>::template type

  template<bool B, typename T>
  struct inherit_if final : std::conditional<B, T, empty_base<T>> {};

  template<bool B, typename T>
  using inherit_if_t = typename std::conditional<B, T, empty_base<T>>::type;

#ifdef __cpp_lib_is_final
  template<typename T>
  using is_inheritable = bool_constant<!std::is_final<T>::value && std::is_class<T>::value>;
  #ifdef __cpp_variable_templates
  template<typename T>
  constexpr bool is_inheritable_v = is_inheritable<T>::value;
  #endif
#endif

} // namespace tmp

} // namespace zxshady


#endif // !ZXSHADY_EXTRA_TRAITS_UTILITY_HPP
