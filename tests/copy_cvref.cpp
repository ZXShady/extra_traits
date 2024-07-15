/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License,
Version 1.0. (See accompanying file LICENSE_1_0.txt
or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include "test.hpp"

template<typename F,typename T>
using copy_cvref_r = copy_cvref_t<T,F>;

IS_SAME(copy_cvref_r<int, char>, int);
IS_SAME(copy_cvref_r<int, const char>, const int);
IS_SAME(copy_cvref_r<int, volatile char>, volatile int);
IS_SAME(copy_cvref_r<int, const volatile char>, const volatile int);
IS_SAME(copy_cvref_r<int, char&>, int&);
IS_SAME(copy_cvref_r<int, const char&>, const int&);
IS_SAME(copy_cvref_r<int, volatile char&>, volatile int&);
IS_SAME(copy_cvref_r<int, const volatile char&>, const volatile int&);

IS_SAME(copy_cvref_r<const int, char>, const int);
IS_SAME(copy_cvref_r<const int, const char>, const int);
IS_SAME(copy_cvref_r<const int, volatile char>, const volatile int);
IS_SAME(copy_cvref_r<const int, const volatile char>, const volatile int);
IS_SAME(copy_cvref_r<const int, char&>, const int&);
IS_SAME(copy_cvref_r<const int, const char&>, const int&);
IS_SAME(copy_cvref_r<const int, volatile char&>, const volatile int&);
IS_SAME(copy_cvref_r<const int, const volatile char&>, const volatile int&);

IS_SAME(copy_cvref_r<volatile int, char>, volatile int);
IS_SAME(copy_cvref_r<volatile int, const char>, const volatile int);
IS_SAME(copy_cvref_r<volatile int, volatile char>, volatile int);
IS_SAME(copy_cvref_r<volatile int, const volatile char>, const volatile int);
IS_SAME(copy_cvref_r<volatile int, char&>, volatile int&);
IS_SAME(copy_cvref_r<volatile int, const char&>, const volatile int&);
IS_SAME(copy_cvref_r<volatile int, volatile char&>, volatile int&);
IS_SAME(copy_cvref_r<volatile int, const volatile char&>, const volatile int&);

IS_SAME(copy_cvref_r<const volatile int, char>, const volatile int);
IS_SAME(copy_cvref_r<const volatile int, const char>, const volatile int);
IS_SAME(copy_cvref_r<const volatile int, volatile char>, const volatile int);
IS_SAME(copy_cvref_r<const volatile int, const volatile char>, const volatile int);
IS_SAME(copy_cvref_r<const volatile int, char&>, const volatile int&);
IS_SAME(copy_cvref_r<const volatile int, const char&>, const volatile int&);
IS_SAME(copy_cvref_r<const volatile int, volatile char&>, const volatile int&);
IS_SAME(copy_cvref_r<const volatile int, const volatile char&>, const volatile int&);

IS_SAME(copy_cvref_r<int&, char>, int&);
IS_SAME(copy_cvref_r<int&, const char>, const int&);
IS_SAME(copy_cvref_r<int&, volatile char>, volatile int&);
IS_SAME(copy_cvref_r<int&, const volatile char>, const volatile int&);
IS_SAME(copy_cvref_r<int&, char&>, int&);
IS_SAME(copy_cvref_r<int&, const char&>, const int&);
IS_SAME(copy_cvref_r<int&, volatile char&>, volatile int&);
IS_SAME(copy_cvref_r<int&, const volatile char&>, const volatile int&);

IS_SAME(copy_cvref_r<const int&, char>, const int&);
IS_SAME(copy_cvref_r<const int&, const char>, const int&);
IS_SAME(copy_cvref_r<const int&, volatile char>, const volatile int&);
IS_SAME(copy_cvref_r<const int&, const volatile char>, const volatile int&);
IS_SAME(copy_cvref_r<const int&, char&>, const int&);
IS_SAME(copy_cvref_r<const int&, const char&>, const int&);
IS_SAME(copy_cvref_r<const int&, volatile char&>, const volatile int&);
IS_SAME(copy_cvref_r<const int&, const volatile char&>, const volatile int&);

IS_SAME(copy_cvref_r<volatile int&, char>, volatile int&);
IS_SAME(copy_cvref_r<volatile int&, const char>, const volatile int&);
IS_SAME(copy_cvref_r<volatile int&, volatile char>, volatile int&);
IS_SAME(copy_cvref_r<volatile int&, const volatile char>, const volatile int&);
IS_SAME(copy_cvref_r<volatile int&, char&>, volatile int&);
IS_SAME(copy_cvref_r<volatile int&, const char&>, const volatile int&);
IS_SAME(copy_cvref_r<volatile int&, volatile char&>, volatile int&);
IS_SAME(copy_cvref_r<volatile int&, const volatile char&>,const volatile int&);

IS_SAME(copy_cvref_r<const volatile int&, char>, const volatile int&);
IS_SAME(copy_cvref_r<const volatile int&, const char>, const volatile int&);
IS_SAME(copy_cvref_r<const volatile int&, volatile char>, const volatile int&);
IS_SAME(copy_cvref_r<const volatile int&, const volatile char>, const volatile int&);
IS_SAME(copy_cvref_r<const volatile int&, char&>, const volatile int&);
IS_SAME(copy_cvref_r<const volatile int&, const char&>, const volatile int&);
IS_SAME(copy_cvref_r<const volatile int&, volatile char&>, const volatile int&);
IS_SAME(copy_cvref_r<const volatile int&, const volatile char&>, const volatile int&);

IS_SAME(copy_cvref_r<int, char&&>, int&&);
IS_SAME(copy_cvref_r<int, const char&&>, const int&&);
IS_SAME(copy_cvref_r<int, volatile char&&>, volatile int&&);
IS_SAME(copy_cvref_r<int, const volatile char&&>, const volatile int&&);

IS_SAME(copy_cvref_r<const int, char&&>, const int&&);
IS_SAME(copy_cvref_r<const int, const char&&>, const int&&);
IS_SAME(copy_cvref_r<const int, volatile char&&>, const volatile int&&);
IS_SAME(copy_cvref_r<const int, const volatile char&&>, const volatile int&&);

IS_SAME(copy_cvref_r<volatile int, char&&>, volatile int&&);
IS_SAME(copy_cvref_r<volatile int, const char&&>, const volatile int&&);
IS_SAME(copy_cvref_r<volatile int, volatile char&&>, volatile int&&);
IS_SAME(copy_cvref_r<volatile int, const volatile char&&>, const volatile int&&);

IS_SAME(copy_cvref_r<const volatile int, char&&>, const volatile int&&);
IS_SAME(copy_cvref_r<const volatile int, const char&&>, const volatile int&&);
IS_SAME(copy_cvref_r<const volatile int, volatile char&&>, const volatile int&&);
IS_SAME(copy_cvref_r<const volatile int, const volatile char&&>, const volatile int&&);

IS_SAME(copy_cvref_r<int&, char&&>, int&);
IS_SAME(copy_cvref_r<int&, const char&&>, const int&);
IS_SAME(copy_cvref_r<int&, volatile char&&>, volatile int&);
IS_SAME(copy_cvref_r<int&, const volatile char&&>, const volatile int&);

IS_SAME(copy_cvref_r<const int&, char&&>, const int&);
IS_SAME(copy_cvref_r<const int&, const char&&>, const int&);
IS_SAME(copy_cvref_r<const int&, volatile char&&>, const volatile int&);
IS_SAME(copy_cvref_r<const int&, const volatile char&&>, const volatile int&);

IS_SAME(copy_cvref_r<volatile int&, char&&>, volatile int&);
IS_SAME(copy_cvref_r<volatile int&, const char&&>, const volatile int&);
IS_SAME(copy_cvref_r<volatile int&, volatile char&&>, volatile int&);
IS_SAME(copy_cvref_r<volatile int&, const volatile char&&>,const volatile int&);

IS_SAME(copy_cvref_r<const volatile int&, char&&>, const volatile int&);
IS_SAME(copy_cvref_r<const volatile int&, const char&&>, const volatile int&);
IS_SAME(copy_cvref_r<const volatile int&, volatile char&&>, const volatile int&);
IS_SAME(copy_cvref_r<const volatile int&, const volatile char&&>, const volatile int&);

IS_SAME(copy_cvref_r<int&&, char>, int&&);
IS_SAME(copy_cvref_r<int&&, const char>, const int&&);
IS_SAME(copy_cvref_r<int&&, volatile char>, volatile int&&);
IS_SAME(copy_cvref_r<int&&, const volatile char>, const volatile int&&);
IS_SAME(copy_cvref_r<int&&, char&>, int&);
IS_SAME(copy_cvref_r<int&&, const char&>, const int&);
IS_SAME(copy_cvref_r<int&&, volatile char&>, volatile int&);
IS_SAME(copy_cvref_r<int&&, const volatile char&>, const volatile int&);
IS_SAME(copy_cvref_r<int&&, char&&>, int&&);
IS_SAME(copy_cvref_r<int&&, const char&&>, const int&&);
IS_SAME(copy_cvref_r<int&&, volatile char&&>, volatile int&&);
IS_SAME(copy_cvref_r<int&&, const volatile char&&>, const volatile int&&);

IS_SAME(copy_cvref_r<const int&&, char>, const int&&);
IS_SAME(copy_cvref_r<const int&&, const char>, const int&&);
IS_SAME(copy_cvref_r<const int&&, volatile char>, const volatile int&&);
IS_SAME(copy_cvref_r<const int&&, const volatile char>, const volatile int&&);
IS_SAME(copy_cvref_r<const int&&, char&>, const int&);
IS_SAME(copy_cvref_r<const int&&, const char&>, const int&);
IS_SAME(copy_cvref_r<const int&&, volatile char&>, const volatile int&);
IS_SAME(copy_cvref_r<const int&&, const volatile char&>, const volatile int&);
IS_SAME(copy_cvref_r<const int&&, char&&>, const int&&);
IS_SAME(copy_cvref_r<const int&&, const char&&>, const int&&);
IS_SAME(copy_cvref_r<const int&&, volatile char&&>, const volatile int&&);
IS_SAME(copy_cvref_r<const int&&, const volatile char&&>, const volatile int&&);

IS_SAME(copy_cvref_r<volatile int&&, char>, volatile int&&);
IS_SAME(copy_cvref_r<volatile int&&, const char>, const volatile int&&);
IS_SAME(copy_cvref_r<volatile int&&, volatile char>, volatile int&&);
IS_SAME(copy_cvref_r<volatile int&&, const volatile char>, const volatile int&&);
IS_SAME(copy_cvref_r<volatile int&&, char&>, volatile int&);
IS_SAME(copy_cvref_r<volatile int&&, const char&>, const volatile int&);
IS_SAME(copy_cvref_r<volatile int&&, volatile char&>, volatile int&);
IS_SAME(copy_cvref_r<volatile int&&, const volatile char&>,const volatile int&);
IS_SAME(copy_cvref_r<volatile int&&, char&&>, volatile int&&);
IS_SAME(copy_cvref_r<volatile int&&, const char&&>, const volatile int&&);
IS_SAME(copy_cvref_r<volatile int&&, volatile char&&>, volatile int&&);
IS_SAME(copy_cvref_r<volatile int&&, const volatile char&&>, const volatile int&&);

IS_SAME(copy_cvref_r<const volatile int&&, char>, const volatile int&&);
IS_SAME(copy_cvref_r<const volatile int&&, const char>, const volatile int&&);
IS_SAME(copy_cvref_r<const volatile int&&, volatile char>, const volatile int&&);
IS_SAME(copy_cvref_r<const volatile int&&, const volatile char>, const volatile int&&);
IS_SAME(copy_cvref_r<const volatile int&&, char&>, const volatile int&);
IS_SAME(copy_cvref_r<const volatile int&&, const char&>, const volatile int&);
IS_SAME(copy_cvref_r<const volatile int&&, volatile char&>, const volatile int&);
IS_SAME(copy_cvref_r<const volatile int&&, const volatile char&>, const volatile int&);
IS_SAME(copy_cvref_r<const volatile int&&, char&&>, const volatile int&&);
IS_SAME(copy_cvref_r<const volatile int&&, const char&&>, const volatile int&&);
IS_SAME(copy_cvref_r<const volatile int&&, volatile char&&>, const volatile int&&);
IS_SAME(copy_cvref_r<const volatile int&&, const volatile char&&>, const volatile int&&);

