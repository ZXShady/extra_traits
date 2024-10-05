#include "test.hpp"
#include <zxshady/extra_traits/is_brackets_braces_constructible.hpp>
struct S {
  S(int y) : x(y) {}
  S(std::initializer_list<int>) = delete;
  int& get() { return x; }
private:
  int x;
};

STATIC_ASSERT(zxshady::tmp::is_braces_constructible<S, int>::value);
STATIC_ASSERT(zxshady::tmp::is_braces_constructible<S, long>::value);

STATIC_ASSERT(!zxshady::tmp::is_braces_constructible<S, std::initializer_list<int>>::value);

STATIC_ASSERT(!zxshady::tmp::is_braces_constructible<S, const char*>::value);
STATIC_ASSERT(!zxshady::tmp::is_braces_constructible<S, std::nullptr_t>::value);

struct A {
  int x;
};

#ifdef __cpp_aggregate_paren_init
STATIC_ASSERT(zxshady::tmp::is_braces_constructible<A, int>::value);
STATIC_ASSERT(zxshady::tmp::is_braces_constructible<A, long>::value);
#else
STATIC_ASSERT(!zxshady::tmp::is_braces_constructible<A, int>::value);
STATIC_ASSERT(!zxshady::tmp::is_braces_constructible<A, long>::value);
#endif

STATIC_ASSERT(!zxshady::tmp::is_braces_constructible<A, const char*>::value);
STATIC_ASSERT(!zxshady::tmp::is_braces_constructible<A, std::nullptr_t>::value);
