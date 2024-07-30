#include "test.hpp"

STATIC_ASSERT(!is_bounded_array<void>::value);
STATIC_ASSERT(!is_bounded_array<int>::value);
STATIC_ASSERT(!is_bounded_array<int*>::value);
STATIC_ASSERT(!is_bounded_array<int&>::value);

STATIC_ASSERT(is_bounded_array<int[1]>::value);
STATIC_ASSERT(is_bounded_array<const int[1 << 16]>::value);
STATIC_ASSERT(is_bounded_array<const volatile int[0 ? 0 : !!!!5]>::value);

STATIC_ASSERT(is_bounded_array<int[100]>::value);
STATIC_ASSERT(!is_bounded_array<int[]>::value);

STATIC_ASSERT(!is_bounded_array<const int[]>::value);
STATIC_ASSERT(!is_bounded_array<const volatile int[]>::value);

STATIC_ASSERT(!is_bounded_array<const int(&&)[][42]>::value);
STATIC_ASSERT(!is_bounded_array<int(*&)[]>::value);
STATIC_ASSERT(!is_bounded_array<int (&&)[1]>::value);

STATIC_ASSERT(!is_bounded_array<auto(*)()->int(&)[5]>::value);
