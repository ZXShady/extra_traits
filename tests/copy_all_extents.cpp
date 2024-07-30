#include "test.hpp"

IS_SAME(copy_all_extents_t<int[1], char[2]>, char[1][2]);

using T = int[1];
using U = T[2];

static_assert(std::is_same<U, int[2][1]>::value, "std::is_same<U, int[1][2]>::value");