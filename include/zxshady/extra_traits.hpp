#ifndef ZXSHADY_EXTRA_TRAITS_HPP
#define ZXSHADY_EXTRA_TRAITS_HPP

#include "extra_traits/macros.hpp"
#include "extra_traits/standard_library_features.hpp"
#include "extra_traits/type_list.hpp"
#include "extra_traits/has_operators.hpp"

#include <new>
#include <type_traits>
#include <utility> // std::swap,std::make_index_sequence

#include <cstddef>

#if !defined(__cpp_variadic_templates) || !defined(__cpp_alias_templates)

  #error This zxshady/extended_traits.hpp header requires variadic and alias templates supports.

#endif // !__cpp_variadic_templates


namespace zxshady {
namespace tmp {

  template<typename T>
  struct remove_all_pointers :
  public std::conditional<std::is_pointer<T>::value, remove_all_pointers<remove_pointer_t<T>>, type_identity<T>>::type {};

  template<typename T>
  using remove_all_pointers_t = typename remove_all_pointers<T>::type;


  template<typename T>
  constexpr const T& as_const(T& t) noexcept
  {
    return t;
  }
  template<typename T>
  void as_const(const T&&) = delete;

  template<typename T>
  constexpr T& as_lvalue(T&& t) noexcept
  {
    return (t);
  }

  template<typename T>
  constexpr volatile T& as_volatile(T& t) noexcept
  {
    return t;
  }
  template<typename T>
  constexpr const volatile T& as_cv(T& t) noexcept
  {
    return t;
  }

  template<typename T>
  void as_volatile(const T&&) = delete;
  template<typename T>
  void as_cv(const T&&) = delete;

  template<typename...>
  struct always_false : public ::std::false_type {};
  ZXCREATE_VAR_SHORTCUT_ARGS(always_false, Ts);

  template<typename...>
  struct always_true : public ::std::true_type {};
  ZXCREATE_VAR_SHORTCUT_ARGS(always_true, Ts);


  template<std::size_t Value>
  using index_constant = std::integral_constant<std::size_t, Value>;


  template<typename T, T... Vs>
  struct nontype_list {
    static constexpr ::std::size_t size() noexcept { return sizeof...(Vs); }
  };

#ifdef __cpp_nontype_template_parameter_auto

  template<auto... Vs>
  struct auto_list {
    static constexpr std::size_t size() noexcept { return sizeof...(Vs); }
  };

#endif


  namespace details {
    template<typename... RebindWith, template<typename...> class Template, typename... TemplateArgs>
    Template<RebindWith...> rebind_template(Template<TemplateArgs...>);

  } // namespace details

  template<typename Template, typename... RebindWith>
  struct rebind_template {
    using type = decltype(details::rebind_template<RebindWith...>(std::declval<Template>()));
  };

  template<typename Template, typename... RebindWith>
  using rebind_template_t = typename rebind_template<Template, RebindWith...>::type;

  namespace details {

    template<typename, typename, typename...>
    struct is_braces_constructible : public std::false_type {};

    template<typename T, typename... Args>
    struct is_braces_constructible<decltype(::new T(::std::declval<Args>()...), void()), T, Args...> :
    public std::true_type {};

    template<typename, typename, typename...>
    struct is_nothrow_braces_constructible : public std::false_type {};

    template<typename T, typename... Args>
    struct is_nothrow_braces_constructible<decltype(::new T(::std::declval<Args>()...), void()), T, Args...> :
    bool_constant<noexcept(T(::std::declval<Args>()...))> {};

    template<typename, typename, typename...>
    struct is_brackets_constructible : public std::false_type {};

    template<typename T, typename... Args>
    struct is_brackets_constructible<decltype(::new T{::std::declval<Args>()...}, void()), T, Args...> :
    public ::std::true_type {};

    template<typename, typename, typename...>
    struct is_nothrow_brackets_constructible : public std::false_type {};

    template<typename T, typename... Args>
    struct is_nothrow_brackets_constructible<decltype(::new T{::std::declval<Args>()...}, void()), T, Args...> :
    bool_constant<noexcept(::new T{::std::declval<Args>()...})> {};

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
  constexpr bool is_nothrow_braces_constructible = is_nothrow_braces_constructible<T, Args...>::value;

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
    void test_implicit_construction(T);

    template<typename /*always void*/, typename, typename...>
    struct is_implicitly_constructible : public ::std::false_type {};

    template<typename T, typename... Args>
    struct is_implicitly_constructible<
        decltype(::zxshady::tmp::details::test_implicit_construction<T>({std::declval<Args>()...})), T, Args...> :
    public std::true_type {};

    
    template<typename /*always void*/, typename, typename...>
    struct is_explicitly_constructible : public ::std::false_type {};

    template<typename T, typename... Args>
    struct is_explicitly_constructible<decltype(::zxshady::tmp::details::test_implicit_construction<T>(
        T(std::declval<Args>()...))), T, Args...> :
    public std::true_type {};

  } // namespace details

  template<typename T, typename... Args>
  using is_implicitly_constructible = details::is_implicitly_constructible<void, T, Args...>;

  template<typename T>
  using is_implicitly_copy_constructible = is_implicitly_constructible<T, typename std::add_lvalue_reference<const T>::type>;

  template<typename T>
  using is_implicitly_move_constructible = is_implicitly_constructible<T, typename std::add_rvalue_reference<T>::type>;

  template<typename T>
  using is_implicitly_default_constructible = is_implicitly_constructible<T>;

  template<typename T, typename... Args>
  using is_explicitly_constructible = bool_constant<!is_implicitly_constructible<T, Args...>::value &&
      std::is_constructible<T,Args...>::value
 //                                                  details::is_explicitly_constructible<void,T, Args...>::value 
      || (sizeof...(Args) == 0 && !is_implicitly_copy_constructible<T>::value &&
        !is_implicitly_move_constructible<T>::value)
  >; // if Args is empty (default constructor) and it is not implicitly copy nor move constructible

  template<typename T>
  using is_explicitly_default_constructible = is_explicitly_constructible<T>;

  template<typename T>
  using is_explicitly_copy_constructible = is_explicitly_constructible<T, typename std::add_lvalue_reference<const T>::type>;

  template<typename T>
  using is_explicitly_move_constructible = is_explicitly_constructible<T, typename std::add_rvalue_reference<T>::type>;


#ifdef __cpp_variable_templates
  template<typename T, typename... Args>
  constexpr bool is_implicitly_constructible_v = is_implicitly_constructible<T, Args...>::value;

  template<typename T, typename... Args>
  constexpr bool is_implicitly_copy_constructible_v = is_implicitly_copy_constructible<T, Args...>::value;

  template<typename T, typename... Args>
  constexpr bool is_implicitly_move_constructible_v = is_implicitly_move_constructible<T, Args...>::value;

  template<typename T, typename... Args>
  constexpr bool is_implicitly_default_constructible_v = is_implicitly_default_constructible<T, Args...>::value;

  template<typename T, typename... Args>
  constexpr bool is_explicitly_constructible_v = is_explicitly_constructible<T, Args...>::value;

  template<typename T, typename... Args>
  constexpr bool is_explicitly_copy_constructible_v = is_explicitly_copy_constructible<T, Args...>::value;

  template<typename T, typename... Args>
  constexpr bool is_explicitly_move_constructible_v = is_explicitly_move_constructible<T, Args...>::value;

  template<typename T, typename... Args>
  constexpr bool is_explicitly_default_constructible_v = is_explicitly_default_constructible<T, Args...>::value;

#endif // __cpp_variable_templates


#define XCREATE_ALIAS(name)            \
  template<typename From, typename To> \
  using name##_t = typename name<From, To>::type


  // from paper p1016
  // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1016r0.pdf
  template<typename From, typename To>
  using copy_const = std::conditional<std::is_const<From>::value, const To, To>;
  XCREATE_ALIAS(copy_const);
  template<typename From, typename To>
  using clone_const = copy_const<From, typename std::remove_const<To>::type>;
  XCREATE_ALIAS(clone_const);

  template<typename From, typename To>
  using copy_volatile = std::conditional<std::is_volatile<From>::value, volatile To, To>;
  XCREATE_ALIAS(copy_volatile);

  template<typename From, typename To>
  using clone_volatile = copy_volatile<From, typename std::remove_volatile<To>::type>;
  XCREATE_ALIAS(clone_volatile);

  template<typename From, typename To>
  using copy_cv = copy_const<From, copy_volatile_t<From, To>>;
  XCREATE_ALIAS(copy_cv);

  template<typename From, typename To>
  using clone_cv = copy_cv<From, typename std::remove_cv<To>::type>;
  XCREATE_ALIAS(clone_cv);

  template<typename From, typename To>
  using copy_reference = std::conditional<!std::is_reference<From>::value,
                                          To,
                                          typename std::conditional<std::is_lvalue_reference<From>::value,
                                                                    typename std::add_lvalue_reference<To>::type,
                                                                    typename std::add_rvalue_reference<To>::type>::type>;
  XCREATE_ALIAS(copy_reference);

  template<typename From, typename To>
  using clone_reference = copy_reference<From, remove_reference_t<To>>;
  XCREATE_ALIAS(clone_reference);

  template<typename From, typename To>
  using copy_cvref = copy_reference<From, copy_reference_t<To, copy_cv_t<remove_reference_t<From>, remove_reference_t<To>>>>;
  XCREATE_ALIAS(copy_cvref);

  template<typename From, typename To>
  using clone_cvref = copy_cvref<From, remove_cvref_t<To>>;
  XCREATE_ALIAS(clone_cvref);

  template<typename From, typename To>
  using copy_pointer = std::conditional<std::is_pointer<From>::value, typename std::add_pointer<To>::type, To>;
  XCREATE_ALIAS(copy_pointer);

  template<typename From, typename To>
  using clone_pointer = copy_pointer<From, typename std::remove_pointer<To>::type>;
  XCREATE_ALIAS(clone_pointer);

  template<typename From, typename To>
  struct copy_all_pointers :
  public std::conditional<std::is_pointer<From>::value,
                          copy_all_pointers<typename std::remove_pointer<From>::type, typename std::add_pointer<To>::type>,
                          type_identity<To>>::type {};

  XCREATE_ALIAS(copy_all_pointers);

  template<typename From, typename To>
  using clone_all_pointers = copy_all_pointers<From, remove_all_pointers_t<To>>;
  XCREATE_ALIAS(clone_all_pointers);

  template<typename From, typename To>
  struct copy_extent {
    using type = typename std::conditional<
      std::is_array<From>::value,
      typename std::conditional<std::extent<From>::value != 0,
                                To[std::extent<From>::value != 0 ? std::extent<From>::value : 1],
                                // the ternary conditional is to prevent To[0] since there is no short circuiting in std::conditional
                                To[]>::type,
      To>::type;
  };
  XCREATE_ALIAS(copy_extent);
#undef XCREATE_ALIAS

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
  using is_signed_integer = bool_constant<std::is_integral<T>::value && std::is_signed<T>::value>;
  template<typename T>
  using is_unsigned_integer = bool_constant<std::is_integral<T>::value && std::is_unsigned<T>::value>;


  ZXCREATE_VAR_SHORTCUT_ARG(is_signed_integer, T);
  ZXCREATE_VAR_SHORTCUT_ARG(is_unsigned_integer, T);


  namespace details {
    template<bool, typename, typename OrType>
    struct underlying_type_or {
      using type = OrType;
    };
    template<typename Enum, typename OrType>
    struct underlying_type_or<true, Enum, OrType> {
      using type = typename ::std::underlying_type<Enum>::type;
    };
  } // namespace details
  template<typename Enum, typename OrType>
  using underlying_type_or = details::underlying_type_or<std::is_enum<Enum>::value, Enum, OrType>;

  template<typename Enum, typename OrType>
  using underlying_type_or_t = typename details::underlying_type_or<std::is_enum<Enum>::value, Enum, OrType>::type;

  template<typename T, typename U>
  using is_same_no_cv = ::std::is_same<typename ::std::remove_cv<T>::type, typename ::std::remove_cv<U>::type>;
  ZXCREATE_VAR_SHORTCUT_ARG(is_same_no_cv, T);

  template<typename T, typename U>
  using is_same_no_cvref = ::std::is_same<remove_cvref_t<T>, remove_cvref_t<U>>;
  ZXCREATE_VAR_SHORTCUT_ARG(is_same_no_cvref, T);

  template<typename T>
  using is_class_like = bool_constant<::std::is_class<T>::value || ::std::is_union<T>::value>;
  ZXCREATE_VAR_SHORTCUT_ARG(is_class_like, T);

  namespace details {
    template<bool /*is_enum*/, typename>
    struct is_unscoped_enum : public ::std::false_type {};
    template<typename Enum>
    struct is_unscoped_enum<true, Enum> :
    public std::is_convertible<Enum, typename ::std::underlying_type<Enum>::type> {};
  } // namespace details

  template<typename T>
  using is_unscoped_enum = details::is_unscoped_enum<std::is_enum<T>::value, T>;

  ZXCREATE_VAR_SHORTCUT_ARG(is_unscoped_enum, T);

} // namespace tmp
} // namespace zxshady

#undef ZXCREATE_VAR_SHORTCUT_ARG
#undef ZXCREATE_VAR_SHORTCUT_ARGS

#endif
