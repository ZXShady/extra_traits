#ifndef ZXSHADY_EXTRA_TRAITS_UNIFORM_TYPE_CONSTRUCTION_HPP
#define ZXSHADY_EXTRA_TRAITS_UNIFORM_TYPE_CONSTRUCTION_HPP

#include "is_brackets_braces_constructible.hpp"
#include "macros.hpp"
#include <new>

namespace zxshady {
namespace tmp {

  namespace details {
    // BRACKETS
    template<typename T, typename... Args>
    T uniform_type_construction(std::false_type, Args&&... args) noexcept(noexcept(T{ZXFWD(args)...}))
    {
      return T{ZXFWD(args)...};
    }

    // BRACES
    template<typename T, typename... Args>
    T uniform_type_construction(std::true_type, Args&&... args) noexcept(noexcept(T(ZXFWD(args)...)))
    {
      return T(ZXFWD(args)...);
    }

    template<typename T, typename... Args>
    T* uniform_construct_at(std::false_type, void* p, Args&&... args) noexcept(noexcept(T{ZXFWD(args)...}))
    {
      return ::new (p) T(ZXFWD(args)...);
    }

    template<typename T, typename... Args>
    T* uniform_construct_at(std::true_type, void* p, Args&&... args) noexcept(noexcept(T{ZXFWD(args)...}))
    {
      return ::new (p) T{ZXFWD(args)...};
    }
  } // namespace details

  template<typename T,
           typename... Args,
           ZXSHADY_ENABLE_IF(is_brackets_constructible<T, Args...>::value || is_braces_constructible<T, Args...>::value)>
  T uniform_type_construction(Args&&... args)
  {
    return details::uniform_type_construction<T>(is_braces_constructible<T, Args...>{}, ZXFWD(args)...);
  }

  template<typename T,
           typename... Args,
           ZXSHADY_ENABLE_IF(is_brackets_constructible<T, Args...>::value || is_braces_constructible<T, Args...>::value)>
  T* uniform_construct_at(T* where, Args&&... args)
  {
    static_assert(std::is_const<T>::value || std::is_volatile<T>::value, "T* cannot be const T* or volatile T*");
    return details::uniform_construct_at<T>(is_braces_constructible<T, Args...>{}, static_cast<void*>(where), ZXFWD(args)...);
  }
} // namespace tmp
} // namespace zxshady

#endif // ! ZXSHADY_EXTRA_TRAITS_UNIFORM_TYPE_CONSTRUCTION_HPP