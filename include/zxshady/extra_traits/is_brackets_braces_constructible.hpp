#ifndef ZXSHADY_EXTRA_TRAITS_IS_BRACKETS_BRACES_CONSTRUCIBLE_HPP
#define ZXSHADY_EXTRA_TRAITS_IS_BRACKETS_BRACES_CONSTRUCIBLE_HPP

#include <utility>
#include "standard_library_features.hpp"
#include <new> // placement new

namespace zxshady {
namespace tmp {
  namespace details {

    template<typename, typename, typename...>
    struct is_braces_constructible : std::false_type {};

    template<typename T, typename... Args>
    struct is_braces_constructible<decltype(::new T(::std::declval<Args>()...), void()), T, Args...> : std::true_type {};

    template<typename, typename, typename...>
    struct is_nothrow_braces_constructible : std::false_type {};

    template<typename T, typename... Args>
    struct is_nothrow_braces_constructible<decltype(::new T(::std::declval<Args>()...), void()), T, Args...> :
    bool_constant<noexcept(T(::std::declval<Args>()...))> {};

    template<typename, typename, typename...>
    struct is_brackets_constructible : std::false_type {};

    template<typename T, typename... Args>
    struct is_brackets_constructible<decltype(T{::std::declval<Args>()...}, void()), T, Args...> :
    public ::std::true_type {};

    template<typename, typename, typename...>
    struct is_nothrow_brackets_constructible : std::false_type {};

    template<typename T, typename... Args>
    struct is_nothrow_brackets_constructible<decltype(T{::std::declval<Args>()...}, void()), T, Args...> :
    bool_constant<noexcept(T{::std::declval<Args>()...})> {};

  } // namespace details

  template<typename T, typename... Args>
  using is_braces_constructible = details::is_braces_constructible<void, T, Args...>;

  template<typename T, typename... Args>
  using is_nothrow_braces_constructible = details::is_nothrow_braces_constructible<void, T, Args...>;

  template<typename T, typename... Args>
  using is_brackets_constructible = details::is_brackets_constructible<void, T, Args...>;

  template<typename T, typename... Args>
  using is_nothrow_brackets_constructible = details::is_nothrow_brackets_constructible<void, T, Args...>;

#ifdef __cpp_variable_templates

  template<typename T, typename... Args>
  constexpr bool is_braces_constructible_v = is_braces_constructible<T, Args...>::value;

  template<typename T, typename... Args>
  constexpr bool is_nothrow_braces_constructible_v = is_nothrow_braces_constructible<T, Args...>::value;

  template<typename T, typename... Args>
  constexpr bool is_brackets_constructible_v = is_brackets_constructible<T, Args...>::value;

  template<typename T, typename... Args>
  constexpr bool is_nothrow_brackets_constructible_v = is_nothrow_brackets_constructible<T, Args...>::value;

#endif // __cpp_variable_templates

} // namespace tmp
} // namespace zxshady

#endif // !ZXSHADY_EXTRA_TRAITS_IS_BRACKETS_BRACES_CONSTRUCIBLE_HPP
