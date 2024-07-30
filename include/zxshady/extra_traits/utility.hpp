#ifndef ZXSHADY_EXTRA_TRAITS_UTILITY_HPP
#define ZXSHADY_EXTRA_TRAITS_UTILITY_HPP

#include "macros.hpp"

namespace zxshady {
namespace tmp {

  template<typename...>
  struct always_false : public ::std::false_type {};

  template<typename...>
  struct always_true : public ::std::true_type {};


#ifdef __cpp_variable_templates

  template<typename... Ts>
  ZXSHADY_INLINE_VAR constexpr bool false_v = always_false<Ts...>::value;

  template<typename... Ts>
  ZXSHADY_INLINE_VAR constexpr bool true_v = always_false<Ts...>::value;

#endif // __cpp_variable_templates

  template<typename T, typename...>
  using type_t = T;

  template<typename...>
  struct empty_base {};

  template<typename... Ts>
  struct inherit_from_all : public Ts... {};

  template<template<typename...> class Template, typename... BoundArgs>
  struct bind_template {
    template<typename... Args>
    struct type : public Template<BoundArgs..., Args...> {};
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
