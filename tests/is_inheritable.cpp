
#include "test.hpp"

#ifdef __cpp_lib_is_final

union U {
};

struct B0 {};
struct B1 final {};

STATIC_ASSERT(!is_inheritable<U>::value);
STATIC_ASSERT(is_inheritable<B0>::value);
STATIC_ASSERT(!is_inheritable<B1>::value);

#endif