#include "test.hpp"

#include <zxshady/extra_traits/qualmanip.hpp>

#define COPY_REFERENCE(from, to,should) IS_SAME(zxshady::tmp::copy_reference_t<int from, char to>, char should)

#define empty /**/


// clang-format off

COPY_REFERENCE(empty, empty,empty);
COPY_REFERENCE(const, const,const);
COPY_REFERENCE(volatile, volatile,volatile);
COPY_REFERENCE(const volatile, const volatile,const volatile);

COPY_REFERENCE(empty         , empty,empty);
COPY_REFERENCE(const         , empty,empty);
COPY_REFERENCE(volatile      , empty,empty);
COPY_REFERENCE(const volatile, empty,empty);

COPY_REFERENCE(empty         , const,const);
COPY_REFERENCE(const         , const,const);
COPY_REFERENCE(volatile      , const,const);
COPY_REFERENCE(const volatile, const,const);

COPY_REFERENCE(empty         , volatile,volatile);
COPY_REFERENCE(const         , volatile,volatile);
COPY_REFERENCE(volatile      , volatile,volatile);
COPY_REFERENCE(const volatile, volatile,volatile);

COPY_REFERENCE(empty         , const volatile,const volatile);
COPY_REFERENCE(const         , const volatile,const volatile);
COPY_REFERENCE(volatile      , const volatile,const volatile);
COPY_REFERENCE(const volatile, const volatile,const volatile);

COPY_REFERENCE(&, &,&);
COPY_REFERENCE(&, &,&);
COPY_REFERENCE(&, &,&);
COPY_REFERENCE(&, &,&);

COPY_REFERENCE(const&,empty,&);
COPY_REFERENCE(const&,empty,&);
COPY_REFERENCE(const&,empty,&);
COPY_REFERENCE(const&,empty,&);

COPY_REFERENCE(volatile&, empty,&);
COPY_REFERENCE(volatile&, empty,&);
COPY_REFERENCE(volatile&, empty,&);
COPY_REFERENCE(volatile&, empty,&);

COPY_REFERENCE(const volatile&&, empty,&&);
COPY_REFERENCE(const volatile&&, empty,&&);
COPY_REFERENCE(const volatile&&, empty,&&);
COPY_REFERENCE(const volatile&&, empty,&&);

COPY_REFERENCE(&&,&, &);
COPY_REFERENCE(const&&,&,&);
COPY_REFERENCE(volatile&&, &,&);
COPY_REFERENCE(const volatile&&, &,&);

COPY_REFERENCE(&,&&, &);
COPY_REFERENCE(const&,&&,&);
COPY_REFERENCE(volatile&, &&,&);
COPY_REFERENCE(const volatile&, &&,&);

// clang-format on