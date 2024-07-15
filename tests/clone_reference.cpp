#include "test.hpp"

#define CLONE_REFERENCE(from, to) IS_SAME(clone_reference_t<int from, char to>, type_identity_t<char> to)

#define empty /**/


// clang-format off

CLONE_REFERENCE(empty, empty);
CLONE_REFERENCE(const, const);
CLONE_REFERENCE(volatile, volatile);
CLONE_REFERENCE(const volatile, const volatile);

CLONE_REFERENCE(empty         , empty);
CLONE_REFERENCE(const         , empty);
CLONE_REFERENCE(volatile      , empty);
CLONE_REFERENCE(const volatile, empty);

CLONE_REFERENCE(empty         , const);
CLONE_REFERENCE(const         , const);
CLONE_REFERENCE(volatile      , const);
CLONE_REFERENCE(const volatile, const);

CLONE_REFERENCE(empty         , volatile);
CLONE_REFERENCE(const         , volatile);
CLONE_REFERENCE(volatile      , volatile);
CLONE_REFERENCE(const volatile, volatile);

CLONE_REFERENCE(empty         , const volatile);
CLONE_REFERENCE(const         , const volatile);
CLONE_REFERENCE(volatile      , const volatile);
CLONE_REFERENCE(const volatile, const volatile);

CLONE_REFERENCE(empty         ,empty);
CLONE_REFERENCE(const         ,empty);
CLONE_REFERENCE(volatile      ,empty);
CLONE_REFERENCE(const volatile,empty);

CLONE_REFERENCE(empty         , const);
CLONE_REFERENCE(const         , const);
CLONE_REFERENCE(volatile      , const);
CLONE_REFERENCE(const volatile, const);

CLONE_REFERENCE(empty         , volatile);
CLONE_REFERENCE(const         , volatile);
CLONE_REFERENCE(volatile      , volatile);
CLONE_REFERENCE(const volatile, volatile);

CLONE_REFERENCE(empty         , const volatile);
CLONE_REFERENCE(const         , const volatile);
CLONE_REFERENCE(volatile      , const volatile);
CLONE_REFERENCE(const volatile, const volatile);

CLONE_REFERENCE(&, &);
CLONE_REFERENCE(const&, &);
CLONE_REFERENCE(volatile&, &);
CLONE_REFERENCE(const volatile&, &);

CLONE_REFERENCE(&&, &&);
CLONE_REFERENCE(const&&, &&);
CLONE_REFERENCE(volatile&&, &&);
CLONE_REFERENCE(const volatile&&, &&);

// clang-format on