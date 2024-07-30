#include "../test.hpp"
#include <zxshady/extra_traits/has_operators.hpp>
struct member {
  void operator+(member) {}
};

struct free {};
void operator+(struct free, struct free) {}

struct deleted_member {
  void operator+(deleted_member) = delete;
};

struct deleted_free {};
void operator+(deleted_free, deleted_free) = delete;

struct member_l {
  void operator+(member_l&) & {}
};

struct free_l {};
void operator+(free_l&, free_l&) {}

STATIC_ASSERT(has_operator_plus<member>::value);
STATIC_ASSERT(has_operator_plus<struct free>::value);

STATIC_ASSERT(has_operator_plus<member>::member);
STATIC_ASSERT(has_operator_plus<struct free>::free);

STATIC_ASSERT(!has_operator_plus<member>::free);
STATIC_ASSERT(!has_operator_plus<struct free>::member);

STATIC_ASSERT(has_operator_plus<member_l&>::value);
STATIC_ASSERT(has_operator_plus<free_l&>::value);

STATIC_ASSERT(has_operator_plus<member_l&>::member);
STATIC_ASSERT(has_operator_plus<free_l&>::free);

STATIC_ASSERT(!has_operator_plus<member_l&>::free);
STATIC_ASSERT(!has_operator_plus<free_l&>::member);

STATIC_ASSERT(!has_operator_plus<member_l&&>::value);
STATIC_ASSERT(!has_operator_plus<free_l&&>::value);

STATIC_ASSERT(!has_operator_plus<member_l&&>::member);
STATIC_ASSERT(!has_operator_plus<free_l&&>::free);

STATIC_ASSERT(!has_operator_plus<member_l&&>::free);
STATIC_ASSERT(!has_operator_plus<free_l&&>::member);


STATIC_ASSERT(!has_operator_plus<deleted_member>::value);
STATIC_ASSERT(!has_operator_plus<deleted_free>::value);
