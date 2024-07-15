#include "test.hpp"

enum Enum {
    V = 21
};

enum class EnumClass {
    V = 42
};

STATIC_ASSERT(!is_unscoped_enum<void>::value);
STATIC_ASSERT(is_unscoped_enum<Enum>::value);
STATIC_ASSERT(!is_unscoped_enum<EnumClass>::value);

