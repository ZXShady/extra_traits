
#include "test.hpp"

#include <zxshady/extra_traits/is_implicitly_constructible.hpp>
#include <zxshady/extra_traits/is_explicitly_constructible.hpp>


struct Explicit {
  explicit Explicit() {}
  explicit Explicit(int) {}
  explicit Explicit(int,int) {}
  explicit Explicit(const Explicit&){}
  explicit Explicit(Explicit&&) {}
};

struct Implicit {
  Implicit() {}
  Implicit(int) {}
  Implicit(int,int) {}
  Implicit(const Implicit&) {}
  Implicit(Implicit&&) {}
};
using E = Explicit;
using I = Implicit;

STATIC_ASSERT(zxshady::tmp::is_explicitly_constructible<E>::value);
STATIC_ASSERT(zxshady::tmp::is_explicitly_constructible<E,int>::value);
STATIC_ASSERT(zxshady::tmp::is_explicitly_constructible<E, int,int>::value);
STATIC_ASSERT(zxshady::tmp::is_explicitly_constructible<E,const E&>::value);
STATIC_ASSERT(zxshady::tmp::is_explicitly_constructible<E,E&&>::value);
STATIC_ASSERT(zxshady::tmp::is_explicitly_default_constructible<E>::value);
STATIC_ASSERT(zxshady::tmp::is_explicitly_copy_constructible<E>::value);
STATIC_ASSERT(zxshady::tmp::is_explicitly_move_constructible<E>::value);

STATIC_ASSERT(!zxshady::tmp::is_implicitly_constructible<E>::value);
STATIC_ASSERT(!zxshady::tmp::is_implicitly_constructible<E, int>::value);
STATIC_ASSERT(!zxshady::tmp::is_implicitly_constructible<E, const E&>::value);
STATIC_ASSERT(!zxshady::tmp::is_implicitly_constructible<E, E&&>::value);
STATIC_ASSERT(!zxshady::tmp::is_implicitly_default_constructible<E>::value);
STATIC_ASSERT(!zxshady::tmp::is_implicitly_copy_constructible<E>::value);
STATIC_ASSERT(!zxshady::tmp::is_implicitly_move_constructible<E>::value);

STATIC_ASSERT(!zxshady::tmp::is_explicitly_constructible<I>::value);
STATIC_ASSERT(!zxshady::tmp::is_explicitly_constructible<I, int>::value);
STATIC_ASSERT(!zxshady::tmp::is_explicitly_constructible<I, const I&>::value);
STATIC_ASSERT(!zxshady::tmp::is_explicitly_constructible<I, I&&>::value);
STATIC_ASSERT(!zxshady::tmp::is_explicitly_default_constructible<I>::value);
STATIC_ASSERT(!zxshady::tmp::is_explicitly_copy_constructible<I>::value);
STATIC_ASSERT(!zxshady::tmp::is_explicitly_move_constructible<I>::value);

STATIC_ASSERT(zxshady::tmp::is_implicitly_constructible<I>::value);
STATIC_ASSERT(zxshady::tmp::is_implicitly_constructible<I, int>::value);
STATIC_ASSERT(zxshady::tmp::is_implicitly_constructible<I, const I&>::value);
STATIC_ASSERT(zxshady::tmp::is_implicitly_constructible<I, I&&>::value);
STATIC_ASSERT(zxshady::tmp::is_implicitly_default_constructible<I>::value);
STATIC_ASSERT(zxshady::tmp::is_implicitly_copy_constructible<I>::value);
STATIC_ASSERT(zxshady::tmp::is_implicitly_move_constructible<I>::value);
