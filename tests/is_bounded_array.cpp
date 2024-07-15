/*
Copyright 2018 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License,
Version 1.0. (See accompanying file LICENSE_1_0.txt
or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
#include "test.hpp"

STATIC_ASSERT(!is_bounded_array<void>::value);
STATIC_ASSERT(!is_bounded_array<int>::value);
STATIC_ASSERT(!is_bounded_array<int*>::value);
STATIC_ASSERT(!is_bounded_array<int&>::value);
STATIC_ASSERT(is_bounded_array<int[2]>::value);
STATIC_ASSERT(is_bounded_array<const int[3]>::value);
STATIC_ASSERT(is_bounded_array<const volatile int[4]>::value);
STATIC_ASSERT(is_bounded_array<int[5][6]>::value);
STATIC_ASSERT(!is_bounded_array<int[]>::value);
STATIC_ASSERT(!is_bounded_array<const int[]>::value);
STATIC_ASSERT(!is_bounded_array<const volatile int[]>::value);
STATIC_ASSERT(!is_bounded_array<int[][7]>::value);
STATIC_ASSERT(!is_bounded_array<int(&)[8]>::value);
STATIC_ASSERT(!is_bounded_array<int (&&)[9]>::value);
