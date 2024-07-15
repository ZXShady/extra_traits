#include "test.hpp"
#define Int(x) std::integral_constant<int,x>


INT_CONST(negation<Int(42) >::value, false);
INT_CONST(negation<Int(0) >::value, true);

