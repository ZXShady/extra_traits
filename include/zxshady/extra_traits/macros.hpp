#ifndef ZXSHADY_EXTRA_TRAITS_MACROS_HPP
#define ZXSHADY_EXTRA_TRAITS_MACROS_HPP

#include <type_traits>

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

#define ZXFWD(x) static_cast<decltype(x)&&>(x)
#define ZXMOV(x) static_cast<typename ::std::remove_reference<decltype(x)>::type&&>(x)

#endif // !ZXSHADY_EXTRA_TRAITS_MACROS_HPP
