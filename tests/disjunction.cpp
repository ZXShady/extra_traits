#include "test.hpp"

#define Int(x) std::integral_constant<int, x>

INT_CONST((disjunction<Int(2), Int(5)>::value), 2);
INT_CONST((disjunction<Int(0), Int(2)>::value), 2);

INT_CONST((disjunction<Int(2), Int(4), Int(8), Int(16), Int(32)>::value), 2);
INT_CONST((disjunction<Int(2), Int(4), Int(8), Int(0), Int(32)>::value), 2);

INT_CONST(disjunction<Int(21)>::value, 21);
INT_CONST(disjunction<>::value, false);
