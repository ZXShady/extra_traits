#include "test.hpp"

#include <zxshady/extra_traits/standard_library_features.hpp>

#define Int(x) std::integral_constant<int,x>



INT_CONST(zxshady::tmp::negation<Int(42)>::value, false);
INT_CONST(zxshady::tmp::negation<Int(0)>::value, true);

