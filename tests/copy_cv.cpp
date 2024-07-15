#include "test.hpp"

#define COPY_CV(from, to) IS_SAME(copy_cv_t<int from, char to>, type_identity_t<char> to)

#define empty /**/


// clang-format off

COPY_CV(empty, empty);
COPY_CV(empty, const);
COPY_CV(empty, volatile);
COPY_CV(empty, const volatile);


COPY_CV(const, const);
COPY_CV(const, const);
COPY_CV(const, const volatile);
COPY_CV(const, const volatile);

COPY_CV(volatile, volatile);
COPY_CV(volatile, volatile);
COPY_CV(volatile, const volatile);
COPY_CV(volatile, const volatile);

COPY_CV(const volatile, const volatile);
COPY_CV(const volatile, const volatile);
COPY_CV(const volatile, const volatile);
COPY_CV(const volatile, const volatile);

COPY_CV(empty         , &);
COPY_CV(const         , &);
COPY_CV(volatile      , &);
COPY_CV(const volatile, &);

COPY_CV(empty         , const&);
COPY_CV(const         , const&);
COPY_CV(volatile      , const&);
COPY_CV(const volatile, const&);

COPY_CV(empty         , volatile&);
COPY_CV(const         , volatile&);
COPY_CV(volatile      , volatile&);
COPY_CV(const volatile, volatile&);

COPY_CV(empty         , const volatile&);
COPY_CV(const         , const volatile&);
COPY_CV(volatile      , const volatile&);
COPY_CV(const volatile, const volatile&);

COPY_CV(empty         , &&);
COPY_CV(const         , &&);
COPY_CV(volatile      , &&);
COPY_CV(const volatile, &&);

COPY_CV(empty         , const&&);
COPY_CV(const         , const&&);
COPY_CV(volatile      , const&&);
COPY_CV(const volatile, const&&);

COPY_CV(empty         , volatile&&);
COPY_CV(const         , volatile&&);
COPY_CV(volatile      , volatile&&);
COPY_CV(const volatile, volatile&&);

COPY_CV(empty         , const volatile&&);
COPY_CV(const         , const volatile&&);
COPY_CV(volatile      , const volatile&&);
COPY_CV(const volatile, const volatile&&);

COPY_CV(&, empty);
COPY_CV(&, const);
COPY_CV(&, volatile);
COPY_CV(&, const volatile);

COPY_CV(const&, empty);
COPY_CV(const&, const);
COPY_CV(const&, volatile);
COPY_CV(const&, const volatile);

COPY_CV(volatile&, empty);
COPY_CV(volatile&, const);
COPY_CV(volatile&, volatile);
COPY_CV(volatile&, const volatile);

COPY_CV(const volatile&, empty);
COPY_CV(const volatile&, const);
COPY_CV(const volatile&, volatile);
COPY_CV(const volatile&, const volatile);

COPY_CV(&&, empty);
COPY_CV(&&, const);
COPY_CV(&&, volatile);
COPY_CV(&&, const volatile);

COPY_CV(const&&, empty);
COPY_CV(const&&, const);
COPY_CV(const&&, volatile);
COPY_CV(const&&, const volatile);

COPY_CV(volatile&&, empty);
COPY_CV(volatile&&, const);
COPY_CV(volatile&&, volatile);
COPY_CV(volatile&&, const volatile);

COPY_CV(const volatile&&, empty);
COPY_CV(const volatile&&, const);
COPY_CV(const volatile&&, volatile);
COPY_CV(const volatile&&, const volatile);

// clang-format on