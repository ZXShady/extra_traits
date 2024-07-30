#ifndef ZXSHADY_EXTRA_TRAITS_MACROS_HPP
#define ZXSHADY_EXTRA_TRAITS_MACROS_HPP

#include <type_traits>

#ifndef ZXSHADY_INLINE_VAR
#ifdef __cpp_inline_variables
#define ZXSHADY_INLINE_VAR inline
#else
#define ZXSHADY_INLINE_VAR
#endif
#endif

#ifdef __cpp_concepts
namespace zxshady {
namespace tmp {
  namespace details {

    template<typename, bool B>
    concept c_must_be_true = B;
  } // namespace details
} // namespace tmp
} // namespace zxshady
  #define ZXSHADY_ENABLE_IF(...) ::zxshady::tmp::details::c_must_be_true<(__VA_ARGS__)> = void
#else
  #define ZXSHADY_ENABLE_IF(...) typename ::std::enable_if<(__VA_ARGS__), int>::type = 0
#endif

#define ZXSHADY_FWD(x) static_cast<decltype(x)&&>(x)
#define ZXSHADY_MOV(x) static_cast<typename ::std::remove_reference<decltype(x)>::type&&>(x)

#ifdef __cpp_variable_templates
  #define ZXCREATE_VAR_SHORTCUT_ARG(name, arg_name) \
    template<typename arg_name>                     \
    constexpr bool name##_v = name<arg_name>::value
  #define ZXCREATE_VAR_SHORTCUT_ARGS(name, args_name) \
    template<typename... args_name>                   \
    constexpr bool name##_v = name<args_name...>::value

#else
  #define ZXCREATE_VAR_SHORTCUT_ARG(name, arg_name)   static_assert(true, "")
  #define ZXCREATE_VAR_SHORTCUT_ARGS(name, args_name) static_assert(true, "")

#endif // __cpp_variable_templates

#endif // !ZXSHADY_EXTRA_TRAITS_MACROS_HPP
