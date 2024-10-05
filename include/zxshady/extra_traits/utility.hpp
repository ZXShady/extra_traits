#ifndef ZXSHADY_EXTRA_TRAITS_UTILITY_HPP
#define ZXSHADY_EXTRA_TRAITS_UTILITY_HPP

#include "macros.hpp"
#include <type_traits>
#include "standard_library_features.hpp"

namespace zxshady {
namespace tmp {

  template<typename...>
  struct type_list;

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
  using index_c = std::integral_constant<std::size_t, Value>;

  template<typename T>
  using alignof_c = std::integral_constant<std::size_t, alignof(T)>;

  template<typename T>
  using sizeof_c = std::integral_constant<std::size_t, sizeof(T)>;

#ifdef __cpp_nontype_template_parameter_auto
  template<auto V>
  using constant = std::integral_constant<decltype(V), V>;
#endif

  template<typename...>
  struct empty_base {};

  template<typename... Ts>
  struct inherit_from : Ts... {};


  // final keyword to prevent mistakes of accidentaly inheriting from inherit_if
  // which is why this is not an alias template
  // and instead a class
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

  template<typename Trait>
  using t_ = typename Trait::type;

#ifdef __cpp_variable_templates

  template<typename Trait>
  constexpr bool v_ = Trait::value;

#endif


  template<typename T, typename U>
  using is_same_no_cv = ::std::is_same<typename ::std::remove_cv<T>::type, typename ::std::remove_cv<U>::type>;

  template<typename T, typename U>
  using is_same_no_cvref = ::std::is_same<remove_cvref_t<T>, remove_cvref_t<U>>;

  template<typename T>
  using is_class_type = bool_constant<::std::is_class<T>::value || ::std::is_union<T>::value>;


  template<typename T, bool = std::is_enum<T>::value>
  struct is_unscoped_enum : ::std::false_type {};

  template<typename Enum>
  struct is_unscoped_enum<Enum, true> : std::is_convertible<Enum, typename ::std::underlying_type<Enum>::type> {};


#ifdef __cpp_variable_templates
  template<typename T, typename U>
  constexpr bool is_same_no_cv_v = is_same_no_cv<T, U>::value;

  template<typename T, typename U>
  constexpr bool is_same_no_cvref_v = is_same_no_cvref<T, U>::value;

  template<typename T>
  constexpr bool is_class_type_v = is_class_type<T>::value;

  template<typename T>
  constexpr bool is_unscoped_enum_v = is_unscoped_enum<T>::value;
#endif // __cpp_variable_templates


  template<typename Enum>
  constexpr typename std::underlying_type<Enum>::type to_underlying(Enum e) noexcept
  {
    static_assert(std::is_enum<Enum>::value, "to_underlying only accept enum types!");
    return static_cast<typename std::underlying_type<Enum>::type>(e);
  }

  template<typename Integer, ZXSHADY_ENABLE_IF(std::is_integral<Integer>::value)>
  constexpr typename std::make_signed<Integer>::type to_signed(Integer value) noexcept
  {
    return static_cast<typename std::make_signed<Integer>::type>(value);
  }

  template<typename Integer, ZXSHADY_ENABLE_IF(std::is_integral<Integer>::value)>
  constexpr typename std::make_unsigned<Integer>::type to_unsigned(Integer value) noexcept
  {
    return static_cast<typename std::make_unsigned<Integer>::type>(value);
  }


  template<typename T>
  using is_character_type = bool_constant<std::is_same<char, typename std::remove_cv<T>::type>::value ||
                                          std::is_same<signed char, typename std::remove_cv<T>::type>::value ||
                                          std::is_same<unsigned char, typename std::remove_cv<T>::type>::value ||
                                          std::is_same<wchar_t, typename std::remove_cv<T>::type>::value ||
                                          std::is_same<char16_t, typename std::remove_cv<T>::type>::value ||
#if __cpp_char8_t
                                          std::is_same<char8_t, typename std::remove_cv<T>::type>::value ||
#endif
                                          std::is_same<char32_t, typename std::remove_cv<T>::type>::value>;

#ifdef __cpp_variable_templates
  template<typename T>
  constexpr bool is_character_type_v = std::is_same<char, typename std::remove_cv<T>::type>::value ||
    std::is_same<signed char, typename std::remove_cv<T>::type>::value ||
    std::is_same<unsigned char, typename std::remove_cv<T>::type>::value ||
    std::is_same<wchar_t, typename std::remove_cv<T>::type>::value ||
    std::is_same<char16_t, typename std::remove_cv<T>::type>::value ||
  #if __cpp_char8_t
    std::is_same<char8_t, typename std::remove_cv<T>::type>::value ||
  #endif
    std::is_same<char32_t, typename std::remove_cv<T>::type>::value;
#endif
  template<typename T>
  struct remove_lvalue_reference {
    using type = T;
  };
  template<typename T>
  struct remove_lvalue_reference<T&> {
    using type = T;
  };


  template<typename T>
  struct remove_rvalue_reference {
    using type = T;
  };

  template<typename T>
  struct remove_rvalue_reference<T&&> {
    using type = T;
  };

  template<typename T>
  using remove_lvalue_reference_t = typename remove_lvalue_reference<T>::type;

  template<typename T>
  using remove_rvalue_reference_t = typename remove_rvalue_reference<T>::type;

  template<typename T>
  using is_signed_integeral = bool_constant<!std::is_same<bool, typename std::remove_cv<T>::type>::value &&
                                            std::is_integral<T>::value && std::is_signed<T>::value>;
  template<typename T>
  using is_unsigned_integeral = bool_constant<!std::is_same<bool, typename std::remove_cv<T>::type>::value &&
                                              std::is_integral<T>::value && std::is_unsigned<T>::value>;


#ifdef __cpp_variable_templates
  template<typename T>
  constexpr bool is_signed_integeral_v = is_signed_integeral<T>::value;

  template<typename T>
  constexpr bool is_unsigned_integeral_v = is_unsigned_integeral<T>::value;
#endif


} // namespace tmp

} // namespace zxshady


#endif // !ZXSHADY_EXTRA_TRAITS_UTILITY_HPP
