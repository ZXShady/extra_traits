#include "test.hpp"

enum Enum {
  V = "hello world"[1]
};

enum class EnumClass {
  V = "meaning of life"[0]
};

STATIC_ASSERT(!is_scoped_enum<void>::value);
STATIC_ASSERT(!is_scoped_enum<Enum>::value);
STATIC_ASSERT(is_scoped_enum<EnumClass>::value);
