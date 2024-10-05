#include "test.hpp"

#include <zxshady/extra_traits/qualmanip.hpp>

IS_SAME(zxshady::tmp::remove_all_pointers_t<int********>, int);
IS_SAME(zxshady::tmp::remove_all_pointers_t<volatile int*const volatile**volatile**const***>,volatile int);
IS_SAME(zxshady::tmp::remove_all_pointers_t<int (*)()>, int());
