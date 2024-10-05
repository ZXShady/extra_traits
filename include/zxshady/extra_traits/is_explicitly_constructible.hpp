#ifndef ZXSHADY_EXTRA_TRAITS_IS_EXPLICITLY_CONSTRUCTIBLE_HPP
#define ZXSHADY_EXTRA_TRAITS_IS_EXPLICITLY_CONSTRUCTIBLE_HPP

#include "is_implicitly_constructible.hpp"
#include "standard_library_features.hpp"
#include <type_traits>

namespace zxshady {
namespace tmp {
  template<typename T, typename... Args>
  using is_explicitly_constructible = bool_constant<
    (!is_implicitly_constructible<T, Args...>::value && std::is_constructible<T, Args...>::value)
    //                                                  details::is_explicitly_constructible<void,T, Args...>::value
    || (sizeof...(Args) == 0 && !is_implicitly_copy_constructible<T>::value && !is_implicitly_move_constructible<T>::value)>;
  // if Args is empty (default constructor) and it is not implicitly copy nor move constructible
  //
  template<typename T>
  using is_explicitly_default_constructible = is_explicitly_constructible<T>;

  template<typename T>
  using is_explicitly_copy_constructible = is_explicitly_constructible<T, typename std::add_lvalue_reference<const T>::type>;

  template<typename T>
  using is_explicitly_move_constructible = is_explicitly_constructible<T, typename std::add_rvalue_reference<T>::type>;

#ifdef __cpp_variable_templates
  template<typename T, typename... Args>
  constexpr bool is_explicitly_constructible_v = is_explicitly_constructible<T, Args...>::value;

  template<typename T>
  constexpr bool is_explicitly_copy_constructible_v = is_explicitly_copy_constructible<T>::value;

  template<typename T>
  constexpr bool is_explicitly_move_constructible_v = is_explicitly_move_constructible<T>::value;

  template<typename T>
  constexpr bool is_explicitly_default_constructible_v = is_explicitly_default_constructible<T>::value;

#endif // __cpp_variable_templates


} // namespace tmp
} // namespace zxshady


#endif // !ZXSHADY_EXTRA_TRAITS_IS_EXPLICITLY_CONSTRUCTIBLE_HPP