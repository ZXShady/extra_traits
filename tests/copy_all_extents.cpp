#include "test.hpp"

#if 0
// "Currently not working as inteded"

IS_SAME(copy_all_extents_t<int[1], char[2]>, char[1][2]);

IS_SAME(copy_all_extents_t<int[], char>, char);

IS_SAME(copy_all_extents_t<int[1][5], char>, char);
IS_SAME(copy_all_extents_t<int[1], char[2]>, char[1][2]);

#endif