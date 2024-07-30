#include "test.hpp"

struct Base {
  char x[2];
};


template<bool Bool>
struct B : inherit_if_t<Bool,Base> {};

STATIC_ASSERT(sizeof(B<true>) >= sizeof(Base));

STATIC_ASSERT(sizeof(B<false>) == 1);