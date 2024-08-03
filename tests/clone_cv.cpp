#include "test.hpp"

#define CLONE_CV(from, to, should) IS_SAME(clone_cv_t<int from, char to>, type_identity_t<char> should)

#define empty /**/


// clang-format off


CLONE_CV(empty, empty         ,empty);
CLONE_CV(empty, const         ,empty);
CLONE_CV(empty, volatile      ,empty);
CLONE_CV(empty, const volatile,empty);


CLONE_CV(const         , empty,const);
CLONE_CV(volatile      , empty,volatile);
CLONE_CV(const volatile, empty,const volatile);

CLONE_CV(const, empty         ,const);
CLONE_CV(const, const         ,const);
CLONE_CV(const, volatile      ,const);
CLONE_CV(const, const volatile,const);


CLONE_CV(volatile, empty         ,volatile);
CLONE_CV(volatile, const         ,volatile);
CLONE_CV(volatile, volatile      ,volatile);
CLONE_CV(volatile, const volatile,volatile);

CLONE_CV(const volatile, empty         ,const volatile);
CLONE_CV(const volatile, const         ,const volatile);
CLONE_CV(const volatile, volatile      ,const volatile);
CLONE_CV(const volatile, const volatile,const volatile);


CLONE_CV(empty         , &,&);
CLONE_CV(const         , &,&);
CLONE_CV(volatile      , &,&);
CLONE_CV(const volatile, &,&);

CLONE_CV(empty         , const&,const&);
CLONE_CV(const         , const&,const&);
CLONE_CV(volatile      , const&,const&);
CLONE_CV(const volatile, const&,const&);

CLONE_CV(empty         , volatile&,volatile&);
CLONE_CV(const         , volatile&,volatile&);
CLONE_CV(volatile      , volatile&,volatile&);
CLONE_CV(const volatile, volatile&,volatile&);

CLONE_CV(empty         , const volatile&,const volatile&);
CLONE_CV(const         , const volatile&,const volatile&);
CLONE_CV(volatile      , const volatile&,const volatile&);
CLONE_CV(const volatile, const volatile&,const volatile&);

CLONE_CV(empty         , &&,&&);
CLONE_CV(const         , &&,&&);
CLONE_CV(volatile      , &&,&&);
CLONE_CV(const volatile, &&,&&);

CLONE_CV(empty         , const&&,const&&);
CLONE_CV(const         , const&&,const&&);
CLONE_CV(volatile      , const&&,const&&);
CLONE_CV(const volatile, const&&,const&&);

CLONE_CV(empty         , volatile&&,volatile&&);
CLONE_CV(const         , volatile&&,volatile&&);
CLONE_CV(volatile      , volatile&&,volatile&&);
CLONE_CV(const volatile, volatile&&,volatile&&);

CLONE_CV(empty         , const volatile&&,const volatile&&);
CLONE_CV(const         , const volatile&&,const volatile&&);
CLONE_CV(volatile      , const volatile&&,const volatile&&);
CLONE_CV(const volatile, const volatile&&,const volatile&&);

CLONE_CV(&, empty         ,empty);
CLONE_CV(&, const         ,empty);
CLONE_CV(&, volatile      ,empty);
CLONE_CV(&, const volatile,empty);

CLONE_CV(const&, empty         ,empty);
CLONE_CV(const&, const         ,empty);
CLONE_CV(const&, volatile      ,empty);
CLONE_CV(const&, const volatile,empty);

CLONE_CV(volatile&, empty         ,empty);
CLONE_CV(volatile&, const         ,empty);
CLONE_CV(volatile&, volatile      ,empty);
CLONE_CV(volatile&, const volatile,empty);

CLONE_CV(const volatile&, empty         ,empty);
CLONE_CV(const volatile&, const         ,empty);
CLONE_CV(const volatile&, volatile      ,empty);
CLONE_CV(const volatile&, const volatile,empty);

CLONE_CV(&&, empty         ,empty);
CLONE_CV(&&, const         ,empty);
CLONE_CV(&&, volatile      ,empty);
CLONE_CV(&&, const volatile,empty);

CLONE_CV(const&&, empty         ,empty);
CLONE_CV(const&&, const         ,empty);
CLONE_CV(const&&, volatile      ,empty);
CLONE_CV(const&&, const volatile,empty);

CLONE_CV(volatile&&, empty         ,empty);
CLONE_CV(volatile&&, const         ,empty);
CLONE_CV(volatile&&, volatile      ,empty);
CLONE_CV(volatile&&, const volatile,empty);

CLONE_CV(const volatile&&, empty         ,empty);
CLONE_CV(const volatile&&, const         ,empty);
CLONE_CV(const volatile&&, volatile      ,empty);
CLONE_CV(const volatile&&, const volatile,empty);


CLONE_CV(&,               &,&);
CLONE_CV(const&,          &,&);
CLONE_CV(volatile&,       &,&);
CLONE_CV(const volatile&, &,&);

CLONE_CV(const&, & , &);
CLONE_CV(const&, & , &);
CLONE_CV(const&, & , &);
CLONE_CV(const&, & , &);

CLONE_CV(volatile&, & , &);
CLONE_CV(volatile&, & , &);
CLONE_CV(volatile&, & , &);
CLONE_CV(volatile&, & , &);

CLONE_CV(const volatile&, & , &);
CLONE_CV(const volatile&, & , &);
CLONE_CV(const volatile&, & , &);
CLONE_CV(const volatile&, & , &);

CLONE_CV(&&, &&,&&);
CLONE_CV(const&&, &&,&&);
CLONE_CV(volatile&&, &&,&&);
CLONE_CV(const volatile&&, &&,&&);

CLONE_CV(&&,               const&&,const&&);
CLONE_CV(const&&,          const&&,const&&);
CLONE_CV(volatile&&,       const&&,const&&);
CLONE_CV(const volatile&&, const&&,const&&);

CLONE_CV(&&,               volatile&&,volatile&&);
CLONE_CV(const&&,          volatile&&,volatile&&);
CLONE_CV(volatile&&,       volatile&&,volatile&&);
CLONE_CV(const volatile&&, volatile&&,volatile&&);

CLONE_CV(&&,               const volatile&&,const volatile&&);
CLONE_CV(const&&,          const volatile&&,const volatile&&);
CLONE_CV(volatile&&,       const volatile&&,const volatile&&);
CLONE_CV(const volatile&&, const volatile&&,const volatile&&);


// clang-format on