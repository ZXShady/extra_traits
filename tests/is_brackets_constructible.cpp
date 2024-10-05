#include "test.hpp"

#include <zxshady/extra_traits/is_brackets_braces_constructible.hpp>

struct S {
  S(int y) : x(y)
  {
  }
  S(std::initializer_list<int>) = delete;
  int& get() { return x; }
private:
  int x;
};

STATIC_ASSERT(!zxshady::tmp::is_brackets_constructible<S, int>::value);
STATIC_ASSERT(!zxshady::tmp::is_brackets_constructible<S, long>::value);

STATIC_ASSERT(!zxshady::tmp::is_brackets_constructible<S, const char*>::value);
STATIC_ASSERT(!zxshady::tmp::is_brackets_constructible<S, std::nullptr_t>::value);

struct A {
  int x;
};

STATIC_ASSERT(zxshady::tmp::is_brackets_constructible<A, int>::value);
STATIC_ASSERT(zxshady::tmp::is_brackets_constructible<A, long>::value);

STATIC_ASSERT(!zxshady::tmp::is_brackets_constructible<A, const char*>::value);
STATIC_ASSERT(!zxshady::tmp::is_brackets_constructible<A, std::nullptr_t>::value);
