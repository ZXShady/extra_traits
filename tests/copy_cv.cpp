#include "test.hpp"
#include <zxshady/extra_traits/qualmanip.hpp>

#define COPY_CV(from, to, should) IS_SAME(zxshady::tmp::copy_cv_t<int from, char to>,zxshady::tmp::type_identity_t<char> should)

#define empty /**/


// clang-format off


COPY_CV(empty, empty         ,empty);
COPY_CV(empty, const         ,const);
COPY_CV(empty, volatile      ,volatile);
COPY_CV(empty, const volatile,const volatile);


COPY_CV(const         , empty,const);
COPY_CV(volatile      , empty,volatile);
COPY_CV(const volatile, empty,const volatile);

COPY_CV(const, empty         ,const);
COPY_CV(const, const         ,const);
COPY_CV(const, volatile      ,const volatile);
COPY_CV(const, const volatile,const volatile);


COPY_CV(volatile, empty         ,volatile);
COPY_CV(volatile, const         ,const volatile);
COPY_CV(volatile, volatile      ,volatile);
COPY_CV(volatile, const volatile,const volatile);

COPY_CV(const volatile, empty         ,const volatile);
COPY_CV(const volatile, const         ,const volatile);
COPY_CV(const volatile, volatile      ,const volatile);
COPY_CV(const volatile, const volatile,const volatile);


COPY_CV(empty         , &,&);
COPY_CV(const         , &,&);
COPY_CV(volatile      , &,&);
COPY_CV(const volatile, &,&);

COPY_CV(empty         , const&,const&);
COPY_CV(const         , const&,const&);
COPY_CV(volatile      , const&,const&);
COPY_CV(const volatile, const&,const&);

COPY_CV(empty         , volatile&,volatile&);
COPY_CV(const         , volatile&,volatile&);
COPY_CV(volatile      , volatile&,volatile&);
COPY_CV(const volatile, volatile&,volatile&);

COPY_CV(empty         , const volatile&,const volatile&);
COPY_CV(const         , const volatile&,const volatile&);
COPY_CV(volatile      , const volatile&,const volatile&);
COPY_CV(const volatile, const volatile&,const volatile&);

COPY_CV(empty         , &&,&&);
COPY_CV(const         , &&,&&);
COPY_CV(volatile      , &&,&&);
COPY_CV(const volatile, &&,&&);

COPY_CV(empty         , const&&,const&&);
COPY_CV(const         , const&&,const&&);
COPY_CV(volatile      , const&&,const&&);
COPY_CV(const volatile, const&&,const&&);

COPY_CV(empty         , volatile&&,volatile&&);
COPY_CV(const         , volatile&&,volatile&&);
COPY_CV(volatile      , volatile&&,volatile&&);
COPY_CV(const volatile, volatile&&,volatile&&);

COPY_CV(empty         , const volatile&&,const volatile&&);
COPY_CV(const         , const volatile&&,const volatile&&);
COPY_CV(volatile      , const volatile&&,const volatile&&);
COPY_CV(const volatile, const volatile&&,const volatile&&);

COPY_CV(&, empty         ,empty);
COPY_CV(&, const         ,const);
COPY_CV(&, volatile      ,volatile);
COPY_CV(&, const volatile,const volatile);

COPY_CV(const&, empty         ,empty);
COPY_CV(const&, const         ,const);
COPY_CV(const&, volatile      ,volatile);
COPY_CV(const&, const volatile,const volatile);

COPY_CV(volatile&, empty         ,empty);
COPY_CV(volatile&, const         ,const);
COPY_CV(volatile&, volatile      ,volatile);
COPY_CV(volatile&, const volatile,const volatile);

COPY_CV(const volatile&, empty         ,empty);
COPY_CV(const volatile&, const         ,const);
COPY_CV(const volatile&, volatile      ,volatile);
COPY_CV(const volatile&, const volatile,const volatile);

COPY_CV(&&, empty         ,empty);
COPY_CV(&&, const         ,const);
COPY_CV(&&, volatile      ,volatile);
COPY_CV(&&, const volatile,const volatile);

COPY_CV(const&&, empty         ,empty);
COPY_CV(const&&, const         ,const);
COPY_CV(const&&, volatile      ,volatile);
COPY_CV(const&&, const volatile,const volatile);

COPY_CV(volatile&&, empty         ,empty);
COPY_CV(volatile&&, const         ,const);
COPY_CV(volatile&&, volatile      ,volatile);
COPY_CV(volatile&&, const volatile,const volatile);

COPY_CV(const volatile&&, empty         ,empty);
COPY_CV(const volatile&&, const         ,const);
COPY_CV(const volatile&&, volatile      ,volatile);
COPY_CV(const volatile&&, const volatile,const volatile);


COPY_CV(&,               &,&);
COPY_CV(const&,          &,&);
COPY_CV(volatile&,       &,&);
COPY_CV(const volatile&, &,&);

COPY_CV(&,               const&,const&);
COPY_CV(const&,          const&,const&);
COPY_CV(volatile&,       const&,const&);
COPY_CV(const volatile&, const&,const&);

COPY_CV(&,               volatile&,volatile&);
COPY_CV(const&,          volatile&,volatile&);
COPY_CV(volatile&,       volatile&,volatile&);
COPY_CV(const volatile&, volatile&,volatile&);

COPY_CV(&,               const volatile&,const volatile&);
COPY_CV(const&,          const volatile&,const volatile&);
COPY_CV(volatile&,       const volatile&,const volatile&);
COPY_CV(const volatile&, const volatile&,const volatile&);


COPY_CV(&&,               &,&);
COPY_CV(const&&,          &,&);
COPY_CV(volatile&&,       &,&);
COPY_CV(const volatile&&, &,&);

COPY_CV(&&,               const&,const&);
COPY_CV(const&&,          const&,const&);
COPY_CV(volatile&&,       const&,const&);
COPY_CV(const volatile&&, const&,const&);

COPY_CV(&&,               volatile&,volatile&);
COPY_CV(const&&,          volatile&,volatile&);
COPY_CV(volatile&&,       volatile&,volatile&);
COPY_CV(const volatile&&, volatile&,volatile&);

COPY_CV(&&,               const volatile&,const volatile&);
COPY_CV(const&&,          const volatile&,const volatile&);
COPY_CV(volatile&&,       const volatile&,const volatile&);
COPY_CV(const volatile&&, const volatile&,const volatile&);


COPY_CV(&&,               &&,&&);
COPY_CV(const&&,          &&,&&);
COPY_CV(volatile&&,       &&,&&);
COPY_CV(const volatile&&, &&,&&);

COPY_CV(&&,               const&&,const&&);
COPY_CV(const&&,          const&&,const&&);
COPY_CV(volatile&&,       const&&,const&&);
COPY_CV(const volatile&&, const&&,const&&);

COPY_CV(&&,               volatile&&,volatile&&);
COPY_CV(const&&,          volatile&&,volatile&&);
COPY_CV(volatile&&,       volatile&&,volatile&&);
COPY_CV(const volatile&&, volatile&&,volatile&&);

COPY_CV(&&,               const volatile&&,const volatile&&);
COPY_CV(const&&,          const volatile&&,const volatile&&);
COPY_CV(volatile&&,       const volatile&&,const volatile&&);
COPY_CV(const volatile&&, const volatile&&,const volatile&&);





// clang-format on