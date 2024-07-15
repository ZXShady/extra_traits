#include "test.hpp"
#define LIST int, char, wchar_t

using List = type_list<LIST>;

IS_SAME(List::reverse, type_list<wchar_t, char, int>);

IS_SAME(List::pop_back,type_list<int,char>);
IS_SAME(List::pop_front, type_list<char,wchar_t>);

IS_SAME(List::at<1>, char);
IS_SAME(List::at_or<5,void>, void);
IS_SAME(List::back, wchar_t);
IS_SAME(List::front, int);


IS_SAME(List::push_back<float>, type_list<LIST, float>);
IS_SAME(List::push_front<float>, type_list<float, LIST>);

IS_SAME(List::append<float,double>, type_list<LIST,float,double>);
IS_SAME(List::prepend<float, double>, type_list<float, double,LIST>);

IS_SAME(List::insert<1, void*, long>, type_list<int, void*, long, char, wchar_t>);

IS_SAME(List::erase<1>, type_list<int, wchar_t>);

IS_SAME(List::transform<std::add_const>, type_list<const int, const char, const wchar_t>);

STATIC_ASSERT(List::size == 3);
STATIC_ASSERT(!List::is_empty);

STATIC_ASSERT(List::find<char>() == 1);
STATIC_ASSERT(List::find<const char>() == static_cast<std::size_t>(-1));

STATIC_ASSERT(List::push_back<void*>::find_if<std::is_pointer>() == 3);

