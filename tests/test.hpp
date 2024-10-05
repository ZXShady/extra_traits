#ifndef TEST_HPP
#define TEST_HPP


#include <cstdio>
#include <typeinfo>

template<typename T, typename U>
constexpr bool is_equal(T t, U u)
{
  return t == static_cast<T>(u);
}
#define INT_CONST(...)     static_assert(is_equal(__VA_ARGS__), #__VA_ARGS__)
#define STATIC_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#define IS_SAME(...)       STATIC_ASSERT(std::is_same<__VA_ARGS__>::value)


#endif // !TEST_HPP
