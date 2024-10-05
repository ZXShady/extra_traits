#include "test.hpp"
#include <zxshady/extra_traits/standard_library_features.hpp>


#define TRY_FOR(trait, qual1, qual2)          \
  IS_SAME(trait##_t<int qual1>, int qual2);   \
  IS_SAME(trait##_t<char qual1>, char qual2); \
  IS_SAME(trait##_t<unsigned int qual1>, unsigned int qual2)


#define empty

TRY_FOR(zxshady::tmp::remove_cvref, * const, *);
TRY_FOR(zxshady::tmp::remove_cvref, const&&, empty);
TRY_FOR(zxshady::tmp::remove_cvref, volatile&&, empty);
TRY_FOR(zxshady::tmp::remove_cvref, volatile const&&, empty);

TRY_FOR(zxshady::tmp::remove_cvref, const* const&&, const*);
TRY_FOR(zxshady::tmp::remove_cvref, volatile* const&&, volatile*);
TRY_FOR(zxshady::tmp::remove_cvref, volatile const* const&&, const volatile*);
