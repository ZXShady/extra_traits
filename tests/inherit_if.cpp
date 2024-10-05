#include "test.hpp"
#include <zxshady/extra_traits/utility.hpp>

struct Base {
  char x[2];
};


template<bool Bool>
struct B : zxshady::tmp::inherit_if_t<Bool,Base> {};

STATIC_ASSERT(sizeof(B<true>) >= sizeof(Base));

STATIC_ASSERT(!(sizeof(B<false>) >= sizeof(Base)));