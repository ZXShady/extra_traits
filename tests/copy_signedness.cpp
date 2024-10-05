#include "test.hpp"
#include <zxshady/extra_traits/qualmanip.hpp>

#define COPY_SIGNEDNESS(from, to, should) IS_SAME(zxshady::tmp::copy_signedness_t<from int, to long>, should long)

COPY_SIGNEDNESS(signed, unsigned, signed);
COPY_SIGNEDNESS(signed, signed, signed);
COPY_SIGNEDNESS(unsigned, signed, unsigned);
COPY_SIGNEDNESS(unsigned, signed, unsigned);


IS_SAME(zxshady::tmp::copy_signedness_t<char, signed>, signed int);
IS_SAME(zxshady::tmp::copy_signedness_t<char, unsigned>, unsigned int);
IS_SAME(zxshady::tmp::copy_signedness_t<char, int>, signed int);
