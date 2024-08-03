#include "test.hpp"
#include <zxshady/extra_traits/logical_traits.hpp>

#define Int(x) std::integral_constant<int,x>

STATIC_ASSERT(or_<Int(0), Int(1)>::value);
STATIC_ASSERT(or_<Int(1)>::value);
STATIC_ASSERT(!or_<Int(0)>::value);
STATIC_ASSERT(!or_<>::value);

STATIC_ASSERT(and_<Int(2), Int(5)>::value);
STATIC_ASSERT(!and_<Int(0), Int(2)>::value);
STATIC_ASSERT(and_<Int(2), Int(4), Int(8), Int(16), Int(32)>::value);
STATIC_ASSERT(!and_<Int(2), Int(4), Int(8), Int(0), Int(32)>::value);
STATIC_ASSERT(and_<Int(21)>::value);
STATIC_ASSERT(and_<>::value);
