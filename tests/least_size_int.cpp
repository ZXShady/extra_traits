#include "test.hpp"
#include <cstdint>
#include <climits>

#include <zxshady/extra_traits/least_size_int.hpp>

IS_SAME(zxshady::tmp::least_size_uint_t<UINT_LEAST8_MAX>, std::uint_least8_t);
IS_SAME(zxshady::tmp::least_size_uint_t<UINT_LEAST16_MAX>, std::uint_least16_t);
IS_SAME(zxshady::tmp::least_size_uint_t<UINT_LEAST32_MAX>, std::uint_least32_t);
IS_SAME(zxshady::tmp::least_size_uint_t<UINT_LEAST64_MAX>, std::uint_least64_t);


IS_SAME(zxshady::tmp::least_size_int_t<INT_LEAST8_MIN>, std::int_least8_t);
IS_SAME(zxshady::tmp::least_size_int_t<INT_LEAST16_MIN>, std::int_least16_t);
IS_SAME(zxshady::tmp::least_size_int_t<INT_LEAST32_MIN>, std::int_least32_t);
IS_SAME(zxshady::tmp::least_size_int_t<INT_LEAST64_MIN>, std::int_least64_t);
IS_SAME(zxshady::tmp::least_size_int_t<INT_LEAST8_MAX>, std::int_least8_t);
IS_SAME(zxshady::tmp::least_size_int_t<INT_LEAST16_MAX>, std::int_least16_t);
IS_SAME(zxshady::tmp::least_size_int_t<INT_LEAST32_MAX>, std::int_least32_t);
IS_SAME(zxshady::tmp::least_size_int_t<INT_LEAST64_MAX>, std::int_least64_t);
