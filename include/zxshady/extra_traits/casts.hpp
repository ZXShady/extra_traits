#ifndef ZXSHADY_EXTRA_TRAITS_CASTS_HPP
  #define ZXSHADY_EXTRA_TRAITS_CASTS_HPP

  #include <utility>

namespace zxshady {
	namespace tmp {
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

// Note Dangerous Function should be only used in templates magic
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


	}
}

#endif // ZXSHADY_EXTRA_TRAITS_CASTS_HPP