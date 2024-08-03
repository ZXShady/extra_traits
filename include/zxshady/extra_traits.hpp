#ifndef ZXSHADY_EXTRA_TRAITS_HPP
#define ZXSHADY_EXTRA_TRAITS_HPP

#if !defined(__cpp_variadic_templates) || !defined(__cpp_alias_templates)

  #error This zxshady/extended_traits.hpp header requires variadic and alias templates supports.

#endif // !__cpp_variadic_templates


#include "extra_traits/has_operators.hpp"
#include "extra_traits/least_size_int.hpp"
#include "extra_traits/literals.hpp"
#include "extra_traits/logical_traits.hpp"
#include "extra_traits/macros.hpp"
#include "extra_traits/qualmanip.hpp"
#include "extra_traits/standard_library_features.hpp"
#include "extra_traits/type_list.hpp"

#include <new>
#include <type_traits>
#include <utility> // std::swap,std::make_index_sequence

#include <cstddef>


namespace zxshady {
namespace tmp {


  template<template<typename> class... UnaryPredicates>
  struct predicate_and {
    template<typename T>
    struct type : conjunction<UnaryPredicates<T>...> {};
  };

  template<template<typename> class... UnaryPredicates>
  struct predicate_or {
    template<typename T>
    struct type : disjunction<UnaryPredicates<T>...> {};
  };

  template<template<typename> class UnaryPredicate>
  struct predicate_not {
    template<typename T>
    struct type : negation<UnaryPredicate<T>> {};
  };

#define ZXSHADY_PREDICATE_NOT(...) predicate_not<__VA_ARGS__>::template type
#define ZXSHADY_PREDICATE_AND(...) predicate_and<__VA_ARGS__>::template type
#define ZXSHADY_PREDICATE_OR(...)  predicate_or<__VA_ARGS__>::template type

#ifdef __cpp_lib_as_const
  using ::std::as_const;
#else
  template<typename T>
  constexpr const T& as_const(const T& t) noexcept
  {
    return t;
  }

  template<typename T>
  void as_const(const T&&) = delete;
#endif

  template<typename T>
  constexpr T& cast_const_away(const T& t) noexcept
  {
    return const_cast<T&>(t);
  }
  template<typename T>
  constexpr T& cast_volatile_away(volatile T& t) noexcept
  {
    return const_cast<T&>(t);
  }

  template<typename T>
  void cast_const_away(const T&&) = delete;
  template<typename T>
  void cast_volatile_away(const T&&) = delete;

  template<typename T>
  constexpr T& as_lvalue(T&& t) noexcept
  {
    return static_cast<T&>(t);
  }

  template<typename T>
  constexpr volatile T& as_volatile(volatile T& t) noexcept
  {
    return t;
  }
  template<typename T>
  constexpr const volatile T& as_cv(const volatile T& t) noexcept
  {
    return t;
  }

  template<typename T>
  void as_volatile(const T&&) = delete;
  template<typename T>
  void as_cv(const T&&) = delete;


  // clang-format off
  template<typename T>
  using is_character_type = and_<
    std::is_same<char,typename std::remove_cv<T>::type>,
    std::is_same<signed char,typename std::remove_cv<T>::type>,
    std::is_same<unsigned char,typename std::remove_cv<T>::type>,
    std::is_same<wchar_t,typename std::remove_cv<T>::type>,
    std::is_same<char16_t,typename std::remove_cv<T>::type>,
    std::is_same<char32_t,typename std::remove_cv<T>::type>
#if __cpp_char8_t
      ,
      std::is_same<char8_t,typename std::remove_cv<T>::type>
#endif
  >;
  // clang-format on

  namespace details {
    template<typename... RebindWith, template<typename...> class Template, typename... TemplateArgs>
    Template<RebindWith...> rebind_template(const volatile Template<TemplateArgs...>&);

  } // namespace details

  template<typename Template, typename... RebindWith>
  struct rebind_template {
    using type = decltype(details::rebind_template<RebindWith...>(std::declval<Template>()));
  };

  template<typename Template, typename... RebindWith>
  using rebind_template_t = typename rebind_template<Template, RebindWith...>::type;

  namespace details {

    template<typename, typename, typename...>
    struct is_braces_constructible : std::false_type {};

    template<typename T, typename... Args>
    struct is_braces_constructible<decltype(::new T(::std::declval<Args>()...), void()), T, Args...> :
    public std::true_type {};

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


  namespace details {
    // BRACKETS
    template<typename T, typename... Args>
    T uniform_type_construction(std::false_type, Args&&... args) noexcept(noexcept(T{ZXSHADY_FWD(args)...}))
    {
      return T{ZXSHADY_FWD(args)...};
    }

    // BRACES
    template<typename T, typename... Args>
    T uniform_type_construction(std::true_type, Args&&... args) noexcept(noexcept(T(ZXSHADY_FWD(args)...)))
    {
      return T(ZXSHADY_FWD(args)...);
    }

    template<typename T, typename... Args>
    T* uniform_construct_at(std::false_type, void* p, Args&&... args) noexcept(noexcept(T{ZXSHADY_FWD(args)...}))
    {
      return ::new (p) T(ZXSHADY_FWD(args)...);
    }

    template<typename T, typename... Args>
    T* uniform_construct_at(std::true_type, void* p, Args&&... args) noexcept(noexcept(T{ZXSHADY_FWD(args)...}))
    {
      return ::new (p) T{ZXSHADY_FWD(args)...};
    }
  } // namespace details

  template<typename T,
           typename... Args,
           ZXSHADY_ENABLE_IF(is_brackets_constructible<T, Args...>::value || is_braces_constructible<T, Args...>::value)>
  T uniform_type_construction(Args&&... args)
  {
    return details::uniform_type_construction<T>(is_braces_constructible<T, Args...>{}, ZXSHADY_FWD(args)...);
  }

  template<typename T,
           typename... Args,
           ZXSHADY_ENABLE_IF(is_brackets_constructible<T, Args...>::value || is_braces_constructible<T, Args...>::value)>
  T* uniform_construct_at(T* where, Args&&... args)
  {
    static_assert(std::is_const<T>::value || std::is_volatile<T>::value, "T* cannot be const T* or volatile T*");
    return details::uniform_construct_at<T>(is_braces_constructible<T, Args...>{},
                                            static_cast<void*>(where),
                                            ZXSHADY_FWD(args)...);
  }


  namespace details {
    template<typename T>
    void implicit_constructibtility_test(T);

    template<typename /*always void*/, typename, typename...>
    struct is_implicitly_constructible : ::std::false_type {};

    template<typename T, typename... Args>
    struct is_implicitly_constructible<decltype(implicit_constructibtility_test<T>({std::declval<Args>()...})), T, Args...> :
    public std::true_type {};


    template<typename /*always void*/, typename, typename...>
    struct is_explicitly_constructible : ::std::false_type {};

    template<typename T>
    struct is_explicitly_constructible<decltype(implicit_constructibtility_test<T>(T())), T> : std::true_type {};

    template<typename T, typename Arg1>
    struct is_explicitly_constructible<decltype(static_cast<T>(std::declval<Arg1>())), T, Arg1> :
    public ::std::true_type {};

    template<typename T, typename... Args>
    struct is_explicitly_constructible<decltype(implicit_constructibtility_test<T>(T(std::declval<Args>()...))), T, Args...> :
    public std::true_type {};

  } // namespace details

  template<typename T, typename... Args>
  using is_implicitly_constructible = details::is_implicitly_constructible<void, T, Args...>;

  template<typename T>
  using is_implicitly_copy_constructible = is_implicitly_constructible<T, typename ::std::add_lvalue_reference<const T>::type>;

  template<typename T>
  using is_implicitly_move_constructible = is_implicitly_constructible<T, typename ::std::add_rvalue_reference<T>::type>;

  template<typename T>
  using is_implicitly_default_constructible = is_implicitly_constructible<T>;

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
  constexpr bool is_implicitly_constructible_v = is_implicitly_constructible<T, Args...>::value;

  template<typename T>
  constexpr bool is_implicitly_copy_constructible_v = is_implicitly_copy_constructible<T>::value;

  template<typename T>
  constexpr bool is_implicitly_move_constructible_v = is_implicitly_move_constructible<T>::value;

  template<typename T>
  constexpr bool is_implicitly_default_constructible_v = is_implicitly_default_constructible<T>::value;

  template<typename T, typename... Args>
  constexpr bool is_explicitly_constructible_v = is_explicitly_constructible<T, Args...>::value;

  template<typename T>
  constexpr bool is_explicitly_copy_constructible_v = is_explicitly_copy_constructible<T>::value;

  template<typename T>
  constexpr bool is_explicitly_move_constructible_v = is_explicitly_move_constructible<T>::value;

  template<typename T>
  constexpr bool is_explicitly_default_constructible_v = is_explicitly_default_constructible<T>::value;

#endif // __cpp_variable_templates


  // the && is to make it when calling it like this forward_like<int>(float); float will become an rvalue
  template<typename Like, typename T>
  constexpr copy_cvref_t<Like&&, T> forward_like(T&& t) noexcept
  {
    return static_cast<copy_cvref_t<Like&&, T>>(t);
  }

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

  template<typename Enum, typename OrType, bool = std::is_enum<Enum>::value>
  struct underlying_type_or {
    using type = OrType;
  };
  template<typename Enum, typename OrType>
  struct underlying_type_or<Enum, OrType, true> {
    using type = typename ::std::underlying_type<Enum>::type;
  };

  template<typename Enum, typename OrType>
  using underlying_type_or_t = typename underlying_type_or<Enum, OrType>::type;

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

  template<typename T, typename U>
  using has_same_qualifiers = bool_constant<std::is_const<T>::value == std::is_const<U>::value &&
                                            std::is_volatile<T>::value == std::is_volatile<U>::value>;


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

#if 0
  template<template<typename...> class Template, template<typename...> class TemplateArg, typename... Args>
  std::is_same<Template<Args...>, TemplateArg<Args...>> is_specilization(const TemplateArg<Args...>&);
  template<template<auto...> class Template, template<auto...> class TemplateArg, auto... Args>
  std::is_same<Template<Args...>, TemplateArg<Args...>> is_specilization(const volatile TemplateArg<Args...>&);
  
  template<template<typename,auto...> class Template, template<typename,auto...> class TemplateArg, typename Arg0,auto... Args>
  std::is_same<Template<Arg0,Args...>, TemplateArg<Arg0,Args...>> is_specilization(const volatile TemplateArg<Arg0,Args...>&);


  #define ZXSHADY_IS_SPECILIZALION_OF(Template, ...) decltype(is_specilization<Template>(std::declval<__VA_ARGS__>()))
#endif
} // namespace tmp
} // namespace zxshady

#endif
