#include "test.hpp"
#include <zxshady/extra_traits/qualmanip.hpp>

IS_SAME(zxshady::tmp::clone_pointer_t<void, int*>, int);
IS_SAME(zxshady::tmp::clone_pointer_t<void*const volatile, int*>, int*);
IS_SAME(zxshady::tmp::clone_pointer_t<void, int*&>, int*&);
