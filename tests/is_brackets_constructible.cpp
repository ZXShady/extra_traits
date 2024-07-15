#include "test.hpp"

struct S {
  S(int) {}
  S(std::initializer_list<int>) = delete;
private:
  int x;
};

STATIC_ASSERT(!is_brackets_constructible<S, int>::value);
STATIC_ASSERT(!is_brackets_constructible<S, long>::value);

STATIC_ASSERT(!is_brackets_constructible<S, const char*>::value);
STATIC_ASSERT(!is_brackets_constructible<S, std::nullptr_t>::value);

struct A {
  int x;
};

STATIC_ASSERT(is_brackets_constructible<A, int>::value);
STATIC_ASSERT(is_brackets_constructible<A, long>::value);

STATIC_ASSERT(!is_brackets_constructible<A, const char*>::value);
STATIC_ASSERT(!is_brackets_constructible<A, std::nullptr_t>::value);
