#include "test.hpp"


IS_SAME(remove_all_pointers_t<int********>, int);
IS_SAME(remove_all_pointers_t<volatile int*const volatile**volatile**const***>,volatile int);
