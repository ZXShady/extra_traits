#include "test.hpp"

#include <zxshady/extra_traits/bind.hpp>

#include <memory> // std::allocator

using FloatAllocator = zxshady::tmp::rebind_template_t<std::allocator<int>, float>;

template<typename T,typename U>
struct TwoArgs {};

using Rebound = typename zxshady::tmp::rebind_template<TwoArgs<int,float>,char,wchar_t>::type;

IS_SAME(FloatAllocator, std::allocator<float>);
IS_SAME(Rebound, TwoArgs<char,wchar_t>);


