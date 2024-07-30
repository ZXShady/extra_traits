#include "test.hpp"

#define Int(x) std::integral_constant<int,x>

STATIC_ASSERT(conjunction<Int(2), Int(5)>::value== 5);
STATIC_ASSERT(conjunction<Int(0), Int(2)>::value ==  0);

STATIC_ASSERT(conjunction<Int(2), Int(4), Int(8), Int(16), Int(32)>::value == 32);
STATIC_ASSERT(conjunction<Int(2), Int(4), Int(8), Int(0), Int(32)>::value == 0);

STATIC_ASSERT(conjunction<Int(21)>::value == 21);
STATIC_ASSERT(conjunction<>::value == true);
