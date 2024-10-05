#include "test.hpp"
#include <zxshady/extra_traits/standard_library_features.hpp>

#define Int(x) std::integral_constant<int, x>

INT_CONST(zxshady::tmp::disjunction<Int(2), Int(5)>::value, 2);
INT_CONST(zxshady::tmp::disjunction<Int(0), Int(2)>::value, 2);

INT_CONST(zxshady::tmp::disjunction<Int(2), Int(4), Int(8), Int(16), Int(32)>::value, 2);
INT_CONST(zxshady::tmp::disjunction<Int(2), Int(4), Int(8), Int(0), Int(32)>::value, 2);

INT_CONST(zxshady::tmp::disjunction<Int(21)>::value, 21);
INT_CONST(zxshady::tmp::disjunction<>::value, false);
