#include "test.hpp"
#include <zxshady/extra_traits/qualmanip.hpp>

#define COPY_CVREF(from, to, should) IS_SAME(zxshady::tmp::copy_cvref_t<int from, char to>, zxshady::tmp::type_identity_t<char> should)

#define empty /**/


// clang-format off


COPY_CVREF(empty, empty         ,empty);
COPY_CVREF(empty, const         ,const);
COPY_CVREF(empty, volatile      ,volatile);
COPY_CVREF(empty, const volatile,const volatile);


COPY_CVREF(const         , empty,const);
COPY_CVREF(volatile      , empty,volatile);
COPY_CVREF(const volatile, empty,const volatile);

COPY_CVREF(const, empty         ,const);
COPY_CVREF(const, const         ,const);
COPY_CVREF(const, volatile      ,const volatile);
COPY_CVREF(const, const volatile,const volatile);


COPY_CVREF(volatile, empty         ,volatile);
COPY_CVREF(volatile, const         ,const volatile);
COPY_CVREF(volatile, volatile      ,volatile);
COPY_CVREF(volatile, const volatile,const volatile);

COPY_CVREF(const volatile, empty         ,const volatile);
COPY_CVREF(const volatile, const         ,const volatile);
COPY_CVREF(const volatile, volatile      ,const volatile);
COPY_CVREF(const volatile, const volatile,const volatile);


COPY_CVREF(empty         , &,&);
COPY_CVREF(const         , &,const&);
COPY_CVREF(volatile      , &,volatile&);
COPY_CVREF(const volatile, &,const volatile&);

COPY_CVREF(empty         , const&,const&);
COPY_CVREF(const         , const&,const&);
COPY_CVREF(volatile      , const&,const volatile&);
COPY_CVREF(const volatile, const&,const volatile&);

COPY_CVREF(empty         , volatile&,volatile&);
COPY_CVREF(const         , volatile&,const volatile&);
COPY_CVREF(volatile      , volatile&,volatile&);
COPY_CVREF(const volatile, volatile&,const volatile&);

COPY_CVREF(empty         , const volatile&,const volatile&);
COPY_CVREF(const         , const volatile&,const volatile&);
COPY_CVREF(volatile      , const volatile&,const volatile&);
COPY_CVREF(const volatile, const volatile&,const volatile&);

COPY_CVREF(empty         , &&,&&);
COPY_CVREF(const         , &&,const&&);
COPY_CVREF(volatile      , &&,volatile&&);
COPY_CVREF(const volatile, &&,const volatile&&);

COPY_CVREF(empty         , const&&,const&&);
COPY_CVREF(const         , const&&,const&&);
COPY_CVREF(volatile      , const&&,const volatile&&);
COPY_CVREF(const volatile, const&&,const volatile&&);

COPY_CVREF(empty         , volatile&&,volatile&&);
COPY_CVREF(const         , volatile&&,const volatile&&);
COPY_CVREF(volatile      , volatile&&,volatile&&);
COPY_CVREF(const volatile, volatile&&,const volatile&&);

COPY_CVREF(empty         , const volatile&&,const volatile&&);
COPY_CVREF(const         , const volatile&&,const volatile&&);
COPY_CVREF(volatile      , const volatile&&,const volatile&&);
COPY_CVREF(const volatile, const volatile&&,const volatile&&);

COPY_CVREF(&, empty         ,&);
COPY_CVREF(&, const         ,const&);
COPY_CVREF(&, volatile      ,volatile&);
COPY_CVREF(&, const volatile,const volatile&);

COPY_CVREF(const&, empty         ,const&);
COPY_CVREF(const&, const         ,const&);
COPY_CVREF(const&, volatile      ,const volatile&);
COPY_CVREF(const&, const volatile,const volatile&);

COPY_CVREF(volatile&, empty         ,volatile&);
COPY_CVREF(volatile&, const         ,const volatile&);
COPY_CVREF(volatile&, volatile      ,volatile&);
COPY_CVREF(volatile&, const volatile,const volatile&);

COPY_CVREF(const volatile&, empty         ,const volatile&);
COPY_CVREF(const volatile&, const         ,const volatile&);
COPY_CVREF(const volatile&, volatile      ,const volatile&);
COPY_CVREF(const volatile&, const volatile,const volatile&);

COPY_CVREF(&&, empty         ,&&);
COPY_CVREF(&&, const         ,const&&);
COPY_CVREF(&&, volatile      ,volatile&&);
COPY_CVREF(&&, const volatile,const volatile&&);

COPY_CVREF(const&&, empty         ,const &&);
COPY_CVREF(const&&, const         ,const&&);
COPY_CVREF(const&&, volatile      ,const volatile&&);
COPY_CVREF(const&&, const volatile,const volatile&&);

COPY_CVREF(volatile&&, empty         ,volatile&&);
COPY_CVREF(volatile&&, const         ,const volatile&&);
COPY_CVREF(volatile&&, volatile      ,volatile&&);
COPY_CVREF(volatile&&, const volatile,const volatile&&);

COPY_CVREF(const volatile&&, empty         ,const volatile&&);
COPY_CVREF(const volatile&&, const         ,const volatile&&);
COPY_CVREF(const volatile&&, volatile      ,const volatile&&);
COPY_CVREF(const volatile&&, const volatile,const volatile&&);


COPY_CVREF(&,               &,&);
COPY_CVREF(const&,          &,const&);
COPY_CVREF(volatile&,       &,volatile&);
COPY_CVREF(const volatile&, &,const volatile&);

COPY_CVREF(&,               const&,const&);
COPY_CVREF(const&,          const&,const&);
COPY_CVREF(volatile&,       const&,const volatile&);
COPY_CVREF(const volatile&, const&,const volatile&);

COPY_CVREF(&,               volatile&,volatile&);
COPY_CVREF(const&,          volatile&,const volatile&);
COPY_CVREF(volatile&,       volatile&,volatile&);
COPY_CVREF(const volatile&, volatile&,const volatile&);

COPY_CVREF(&,              const volatile&,const volatile&);
COPY_CVREF(const&,         const volatile&,const volatile&);
COPY_CVREF(volatile&,      const volatile&,const volatile&);
COPY_CVREF(const volatile&,const volatile&,const volatile&);

COPY_CVREF(&,               &&,&);
COPY_CVREF(const&,          &&,const&);
COPY_CVREF(volatile&,       &&,volatile&);
COPY_CVREF(const volatile&, &&,const volatile&);

COPY_CVREF(&,               const&&,const&);
COPY_CVREF(const&,          const&&,const&);
COPY_CVREF(volatile&,       const&&,const volatile&);
COPY_CVREF(const volatile&, const&&,const volatile&);

COPY_CVREF(&,               volatile&&,volatile&);
COPY_CVREF(const&,          volatile&&,const volatile&);
COPY_CVREF(volatile&,       volatile&&,volatile&);
COPY_CVREF(const volatile&, volatile&&,const volatile&);

COPY_CVREF(&,              const volatile&&,const volatile&);
COPY_CVREF(const&,         const volatile&&,const volatile&);
COPY_CVREF(volatile&,      const volatile&&,const volatile&);
COPY_CVREF(const volatile&,const volatile&&,const volatile&);



COPY_CVREF(&&,               &,&);
COPY_CVREF(const&&,          &,const&);
COPY_CVREF(volatile&&,       &,volatile&);
COPY_CVREF(const volatile&&, &,const volatile&);

COPY_CVREF(&&,               const&,const&);
COPY_CVREF(const&&,          const&,const&);
COPY_CVREF(volatile&&,       const&,const volatile&);
COPY_CVREF(const volatile&&, const&,const volatile&);

COPY_CVREF(&&,               volatile&,volatile&);
COPY_CVREF(const&&,          volatile&,const volatile&);
COPY_CVREF(volatile&&,       volatile&,volatile&);
COPY_CVREF(const volatile&&, volatile&,const volatile&);

COPY_CVREF(&&,              const volatile&,const volatile&);
COPY_CVREF(const&&,         const volatile&,const volatile&);
COPY_CVREF(volatile&&,      const volatile&,const volatile&);
COPY_CVREF(const volatile&&,const volatile&,const volatile&);

// clang-format on