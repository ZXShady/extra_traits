
#include "test.hpp"

#include <zxshady/extra_traits/utility.hpp>


#ifdef __cpp_lib_is_final

union U {};

struct B0 {};
struct B1 final {};

STATIC_ASSERT(!zxshady::tmp::is_inheritable<U>::value);
STATIC_ASSERT(zxshady::tmp::is_inheritable<B0>::value);
STATIC_ASSERT(!zxshady::tmp::is_inheritable<B1>::value);

#endif