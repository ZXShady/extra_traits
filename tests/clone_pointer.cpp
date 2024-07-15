#include "test.hpp"


IS_SAME(clone_pointer_t<void, int*>, int);
IS_SAME(clone_pointer_t<void*const volatile, int*>, int*);
IS_SAME(clone_pointer_t<void, int*&>, int*&);
