#include "test.hpp"

STATIC_ASSERT(!is_unbounded_array<void>::value);
STATIC_ASSERT(!is_unbounded_array<int>::value);
STATIC_ASSERT(!is_unbounded_array<int*>::value);
STATIC_ASSERT(!is_unbounded_array<int&>::value);
STATIC_ASSERT(!is_unbounded_array<int[2]>::value);
STATIC_ASSERT(!is_unbounded_array<const int[3]>::value);
STATIC_ASSERT(!is_unbounded_array<const volatile int[4]>::value);
STATIC_ASSERT(!is_unbounded_array<int[5][6]>::value);
STATIC_ASSERT(is_unbounded_array<int[]>::value);
STATIC_ASSERT(is_unbounded_array<const int[]>::value);
STATIC_ASSERT(is_unbounded_array<const volatile int[]>::value);
STATIC_ASSERT(is_unbounded_array<int[][7]>::value);
STATIC_ASSERT(!is_unbounded_array<int(&)[8]>::value);
STATIC_ASSERT(!is_unbounded_array<int(&&)[9]>::value);
