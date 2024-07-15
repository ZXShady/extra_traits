#include "test.hpp"

#define CLONE_CV(from, to) IS_SAME(clone_cv_t<int from, char to>, type_identity_t<char> to)

#define empty /**/


// clang-format off

CLONE_CV(empty, empty);
CLONE_CV(const, const);
CLONE_CV(volatile, volatile);
CLONE_CV(const volatile, const volatile);

CLONE_CV(empty         , &);
CLONE_CV(const         , &);
CLONE_CV(volatile      , &);
CLONE_CV(const volatile, &);

CLONE_CV(empty         , const&);
CLONE_CV(const         , const&);
CLONE_CV(volatile      , const&);
CLONE_CV(const volatile, const&);

CLONE_CV(empty         , volatile&);
CLONE_CV(const         , volatile&);
CLONE_CV(volatile      , volatile&);
CLONE_CV(const volatile, volatile&);

CLONE_CV(empty         , const volatile&);
CLONE_CV(const         , const volatile&);
CLONE_CV(volatile      , const volatile&);
CLONE_CV(const volatile, const volatile&);

CLONE_CV(empty         , &&);
CLONE_CV(const         , &&);
CLONE_CV(volatile      , &&);
CLONE_CV(const volatile, &&);

CLONE_CV(empty         , const&&);
CLONE_CV(const         , const&&);
CLONE_CV(volatile      , const&&);
CLONE_CV(const volatile, const&&);

CLONE_CV(empty         , volatile&&);
CLONE_CV(const         , volatile&&);
CLONE_CV(volatile      , volatile&&);
CLONE_CV(const volatile, volatile&&);

CLONE_CV(empty         , const volatile&&);
CLONE_CV(const         , const volatile&&);
CLONE_CV(volatile      , const volatile&&);
CLONE_CV(const volatile, const volatile&&);

CLONE_CV(&, empty);
CLONE_CV(const&, empty);
CLONE_CV(volatile&, empty);
CLONE_CV(const volatile&, empty);

CLONE_CV(&&, empty);
CLONE_CV(const&&, empty);
CLONE_CV(volatile&&, empty);
CLONE_CV(const volatile&&, empty);

// clang-format on