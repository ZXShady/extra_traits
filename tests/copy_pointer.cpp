#include "test.hpp"


IS_SAME(copy_pointer_t<void*, int>, int*);

IS_SAME(copy_pointer_t<void (*const)(), int[5]>, int (*)[5]);

IS_SAME(copy_pointer_t<void (*const)(), int&>, int*);
IS_SAME(copy_pointer_t<void (*const)(), int&&>, int*);

