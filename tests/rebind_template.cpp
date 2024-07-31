#include "test.hpp"
#include <memory> // std::allocator

using FloatAllocator = rebind_template_t<std::allocator<int>, float>;

template<typename T,typename U>
struct TwoArgs {};

using Rebound = typename rebind_template<TwoArgs<int,float>,char,wchar_t>::type;
{T, 0}

IS_SAME(FloatAllocator, std::allocator<float>);
IS_SAME(Rebound, TwoArgs<char,wchar_t>);


