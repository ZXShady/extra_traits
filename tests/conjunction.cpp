#include "test.hpp"

#define Int(x) std::integral_constant<int, x>

INT_CONST((conjunction<Int(2), Int(5)>::value), 5);
INT_CONST((conjunction<Int(0), Int(2)>::value), 0);

INT_CONST((conjunction<Int(2), Int(4), Int(8), Int(16), Int(32)>::value), 32);
INT_CONST((conjunction<Int(2), Int(4), Int(8), Int(0), Int(32)>::value), 0);

INT_CONST(conjunction<Int(21)>::value, 21);
INT_CONST(conjunction<>::value, true);
