#ifndef TEST_HPP
  #define TEST_HPP

  
#include <cstdio>
#include <typeinfo>
#include <zxshady/extra_traits.hpp>

using namespace zxshady::tmp;

template<typename T, typename U>
constexpr bool is_equal(T t, U u)
{
  return t == static_cast<T>(u);
}
#define IS_SAME(...)       static_assert(std::is_same<__VA_ARGS__>::value, #__VA_ARGS__)
#define INT_CONST(...)     static_assert(is_equal(__VA_ARGS__), #__VA_ARGS__)
#define STATIC_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)


#endif // !TEST_HPP