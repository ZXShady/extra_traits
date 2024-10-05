#include "test.hpp"

#include <zxshady/extra_traits/utility.hpp>

enum Enum {
    V = 21
};

enum class EnumClass {
    V = 42
};

STATIC_ASSERT(!zxshady::tmp::is_unscoped_enum<void>::value);
STATIC_ASSERT(zxshady::tmp::is_unscoped_enum<Enum>::value);
STATIC_ASSERT(!zxshady::tmp::is_unscoped_enum<EnumClass>::value);

