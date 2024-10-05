#include "test.hpp"
#include <zxshady/extra_traits/qualmanip.hpp>


IS_SAME(zxshady::tmp::copy_pointer_t<void*, int>, int*);

IS_SAME(zxshady::tmp::copy_pointer_t<void (*const)(), int[5]>, int (*)[5]);

IS_SAME(zxshady::tmp::copy_pointer_t<void (*const)(), int&>, int*);
IS_SAME(zxshady::tmp::copy_pointer_t<void (*const)(), int&&>, int*);

