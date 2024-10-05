#include "test.hpp"

#include <zxshady/extra_traits/qualmanip.hpp>

#define CLONE_REFERENCE(from, to, should) IS_SAME(zxshady::tmp::clone_reference_t<int from, char to>, zxshady::tmp::type_identity_t<char> should)

#define empty /**/


// clang-format off


CLONE_REFERENCE(empty, empty         ,empty);
CLONE_REFERENCE(empty, const         ,const);
CLONE_REFERENCE(empty, volatile      ,volatile);
CLONE_REFERENCE(empty, const volatile,const volatile);


CLONE_REFERENCE(const         , empty,empty);
CLONE_REFERENCE(volatile      , empty,empty);
CLONE_REFERENCE(const volatile, empty,empty);

CLONE_REFERENCE(const, empty         ,empty);
CLONE_REFERENCE(const, const         ,const);
CLONE_REFERENCE(const, volatile      ,volatile);
CLONE_REFERENCE(const, const volatile,const volatile);


CLONE_REFERENCE(volatile, empty         ,empty);
CLONE_REFERENCE(volatile, const         ,const);
CLONE_REFERENCE(volatile, volatile      ,volatile);
CLONE_REFERENCE(volatile, const volatile,const volatile);

CLONE_REFERENCE(const volatile, empty         ,empty);
CLONE_REFERENCE(const volatile, const         ,const);
CLONE_REFERENCE(const volatile, volatile      ,volatile);
CLONE_REFERENCE(const volatile, const volatile,const volatile);


CLONE_REFERENCE(empty         , &,empty);
CLONE_REFERENCE(const         , &,empty);
CLONE_REFERENCE(volatile      , &,empty);
CLONE_REFERENCE(const volatile, &,empty);

CLONE_REFERENCE(empty         , const&,const);
CLONE_REFERENCE(const         , const&,const);
CLONE_REFERENCE(volatile      , const&,const);
CLONE_REFERENCE(const volatile, const&,const);

CLONE_REFERENCE(empty         , volatile&,volatile);
CLONE_REFERENCE(const         , volatile&,volatile);
CLONE_REFERENCE(volatile      , volatile&,volatile);
CLONE_REFERENCE(const volatile, volatile&,volatile);

CLONE_REFERENCE(empty         , const volatile&,const volatile);
CLONE_REFERENCE(const         , const volatile&,const volatile);
CLONE_REFERENCE(volatile      , const volatile&,const volatile);
CLONE_REFERENCE(const volatile, const volatile&,const volatile);

CLONE_REFERENCE(empty         , &&,empty);
CLONE_REFERENCE(const         , &&,empty);
CLONE_REFERENCE(volatile      , &&,empty);
CLONE_REFERENCE(const volatile, &&,empty);

CLONE_REFERENCE(empty         , const&&,const);
CLONE_REFERENCE(const         , const&&,const);
CLONE_REFERENCE(volatile      , const&&,const);
CLONE_REFERENCE(const volatile, const&&,const);

CLONE_REFERENCE(empty         , volatile&&,volatile);
CLONE_REFERENCE(const         , volatile&&,volatile);
CLONE_REFERENCE(volatile      , volatile&&,volatile);
CLONE_REFERENCE(const volatile, volatile&&,volatile);

CLONE_REFERENCE(empty         , const volatile&&,const volatile);
CLONE_REFERENCE(const         , const volatile&&,const volatile);
CLONE_REFERENCE(volatile      , const volatile&&,const volatile);
CLONE_REFERENCE(const volatile, const volatile&&,const volatile);

CLONE_REFERENCE(&, empty         ,&);
CLONE_REFERENCE(&, const         ,const&);
CLONE_REFERENCE(&, volatile      ,volatile&);
CLONE_REFERENCE(&, const volatile,const volatile&);

CLONE_REFERENCE(const&, empty         ,&);
CLONE_REFERENCE(const&, const         ,const&);
CLONE_REFERENCE(const&, volatile      ,volatile&);
CLONE_REFERENCE(const&, const volatile,const volatile&);

CLONE_REFERENCE(volatile&, empty         ,&);
CLONE_REFERENCE(volatile&, const         ,const&);
CLONE_REFERENCE(volatile&, volatile      ,volatile&);
CLONE_REFERENCE(volatile&, const volatile,const volatile&);

CLONE_REFERENCE(const volatile&, empty         ,&);
CLONE_REFERENCE(const volatile&, const         ,const&);
CLONE_REFERENCE(const volatile&, volatile      ,volatile&);
CLONE_REFERENCE(const volatile&, const volatile,const volatile&);

CLONE_REFERENCE(&&, empty         ,&&);
CLONE_REFERENCE(&&, const         ,const&&);
CLONE_REFERENCE(&&, volatile      ,volatile&&);
CLONE_REFERENCE(&&, const volatile,const volatile&&);

CLONE_REFERENCE(const&&, empty         ,&&);
CLONE_REFERENCE(const&&, const         ,const&&);
CLONE_REFERENCE(const&&, volatile      ,volatile&&);
CLONE_REFERENCE(const&&, const volatile,const volatile&&);

CLONE_REFERENCE(volatile&&, empty         ,&&);
CLONE_REFERENCE(volatile&&, const         ,const&&);
CLONE_REFERENCE(volatile&&, volatile      ,volatile&&);
CLONE_REFERENCE(volatile&&, const volatile,const volatile&&);

CLONE_REFERENCE(const volatile&&, empty         ,&&);
CLONE_REFERENCE(const volatile&&, const         ,const&&);
CLONE_REFERENCE(const volatile&&, volatile      ,volatile&&);
CLONE_REFERENCE(const volatile&&, const volatile,const volatile&&);


CLONE_REFERENCE(&,               &,&);
CLONE_REFERENCE(const&,          &,&);
CLONE_REFERENCE(volatile&,       &,&);
CLONE_REFERENCE(const volatile&, &,&);

CLONE_REFERENCE(&,               const&,const&);
CLONE_REFERENCE(const&,          const&,const&);
CLONE_REFERENCE(volatile&,       const&,const&);
CLONE_REFERENCE(const volatile&, const&,const&);

CLONE_REFERENCE(&,               volatile&,volatile&);
CLONE_REFERENCE(const&,          volatile&,volatile&);
CLONE_REFERENCE(volatile&,       volatile&,volatile&);
CLONE_REFERENCE(const volatile&, volatile&,volatile&);

CLONE_REFERENCE(&,              const volatile&,const volatile&);
CLONE_REFERENCE(const&,         const volatile&,const volatile&);
CLONE_REFERENCE(volatile&,      const volatile&,const volatile&);
CLONE_REFERENCE(const volatile&,const volatile&,const volatile&);

CLONE_REFERENCE(&,               &&,&);
CLONE_REFERENCE(const&,          &&,&);
CLONE_REFERENCE(volatile&,       &&,&);
CLONE_REFERENCE(const volatile&, &&,&);

CLONE_REFERENCE(&,               const&&,const&);
CLONE_REFERENCE(const&,          const&&,const&);
CLONE_REFERENCE(volatile&,       const&&,const&);
CLONE_REFERENCE(const volatile&, const&&,const&);

CLONE_REFERENCE(&,               volatile&&,volatile&);
CLONE_REFERENCE(const&,          volatile&&,volatile&);
CLONE_REFERENCE(volatile&,       volatile&&,volatile&);
CLONE_REFERENCE(const volatile&, volatile&&,volatile&);

CLONE_REFERENCE(&,              const volatile&&,const volatile&);
CLONE_REFERENCE(const&,         const volatile&&,const volatile&);
CLONE_REFERENCE(volatile&,      const volatile&&,const volatile&);
CLONE_REFERENCE(const volatile&,const volatile&&,const volatile&);

CLONE_REFERENCE(&&,               &,&&);
CLONE_REFERENCE(const&&,          &,&&);
CLONE_REFERENCE(volatile&&,       &,&&);
CLONE_REFERENCE(const volatile&&, &,&&);

CLONE_REFERENCE(&&,               const&,const&&);
CLONE_REFERENCE(const&&,          const&,const&&);
CLONE_REFERENCE(volatile&&,       const&,const&&);
CLONE_REFERENCE(const volatile&&, const&,const&&);

CLONE_REFERENCE(&&,               volatile&,volatile&&);
CLONE_REFERENCE(const&&,          volatile&,volatile&&);
CLONE_REFERENCE(volatile&&,       volatile&,volatile&&);
CLONE_REFERENCE(const volatile&&, volatile&,volatile&&);

CLONE_REFERENCE(&&,              const volatile&,const volatile&&);
CLONE_REFERENCE(const&&,         const volatile&,const volatile&&);
CLONE_REFERENCE(volatile&&,      const volatile&,const volatile&&);
CLONE_REFERENCE(const volatile&&,const volatile&,const volatile&&);

// clang-format on