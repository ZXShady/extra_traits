#ifndef ZXSHADY_EXTRA_TRAITS_IS_IMPLICITLY_CONSTRUCTIBLE_HPP
#define ZXSHADY_EXTRA_TRAITS_IS_IMPLICITLY_CONSTRUCTIBLE_HPP

#include <type_traits>


namespace zxshady {
namespace tmp {
  namespace details {
    template<typename /*always void*/, typename, typename...>
    struct is_implicitly_constructible : ::std::false_type {};

    template<typename T, typename... Args>
    struct is_implicitly_constructible<decltype(std::declval<void (*)(T)>()({std::declval<Args>()...})), T, Args...> :
    std::true_type {};

  } // namespace details


  template<typename T, typename... Args>
  using is_implicitly_constructible = details::is_implicitly_constructible<void, T, Args...>;

  template<typename T>
  using is_implicitly_copy_constructible = is_implicitly_constructible<T, typename ::std::add_lvalue_reference<const T>::type>;

  template<typename T>
  using is_implicitly_move_constructible = is_implicitly_constructible<T, typename ::std::add_rvalue_reference<T>::type>;

  template<typename T>
  using is_implicitly_default_constructible = is_implicitly_constructible<T>;

#ifdef __cpp_variable_templates
  template<typename T, typename... Args>
  constexpr bool is_implicitly_constructible_v = is_implicitly_constructible<T, Args...>::value;

  template<typename T>
  constexpr bool is_implicitly_copy_constructible_v = is_implicitly_copy_constructible<T>::value;

  template<typename T>
  constexpr bool is_implicitly_move_constructible_v = is_implicitly_move_constructible<T>::value;

  template<typename T>
  constexpr bool is_implicitly_default_constructible_v = is_implicitly_default_constructible<T>::value;
#endif

} // namespace tmp
} // namespace zxshady


#endif // !ZXSHADY_EXTRA_TRAITS_IS_IMPLICITLY_CONSTRUCTIBLE_HPP