#include "test.hpp"

using List = type_list<int, char, wchar_t>;


STATIC_ASSERT(List::size == 3);
STATIC_ASSERT(!List::is_empty);
IS_SAME(List::reverse, type_list<wchar_t, char, int>);

IS_SAME(List::pop_back,type_list<int,char>);
IS_SAME(List::pop_front, type_list<char,wchar_t>);

IS_SAME(List::template at<1>, char);
IS_SAME(List::template at_or<5,void>, void);

IS_SAME(List::back, wchar_t);
IS_SAME(List::front, int);

IS_SAME(List::template slice<0>,type_list<int,char,wchar_t>);
IS_SAME(List::template slice<3>,type_list<>);
IS_SAME(List::template slice<2>, type_list<wchar_t>);

IS_SAME(List::template replace_at<0, void>, type_list<void,char, wchar_t>);
IS_SAME(List::template replace_at<1,void>, type_list<int,void,wchar_t>);
IS_SAME(List::template replace_at<2,void>, type_list<int,char,void>);

IS_SAME(List::template append<int, float>::template slice<2>, type_list<wchar_t, int, float>);

IS_SAME(List::template append<int, float>::template drop_first<2>, type_list<wchar_t, int, float>);
IS_SAME(List::template append<int, float>::template drop_last<2>, type_list<int,char,wchar_t>);

IS_SAME(List::template push_back<float>, type_list<int,char,wchar_t, float>);
IS_SAME(List::template push_front<float>, type_list<float,int, char, wchar_t>);

IS_SAME(List::template append<float, double>, type_list<int, char, wchar_t, float, double>);
IS_SAME(List::template prepend<float, double>, type_list<float, double, int, char, wchar_t>);
IS_SAME(List::template insert<1, void*, long>, type_list<int, void*, long, char, wchar_t>);

IS_SAME(List::template erase<1>, type_list<int, wchar_t>);
IS_SAME(List::template transform<std::add_const>, type_list<const int, const char, const wchar_t>);

using BigList = List::template append<const void*const,long int>;

IS_SAME(BigList::template slice<2>, type_list<wchar_t, const void*const, long>);

IS_SAME(BigList::template drop_first<2>, type_list<wchar_t, const void*const, long>);

IS_SAME(BigList::template drop_last<2>, type_list<int,char,wchar_t>);


STATIC_ASSERT(find<void*>(List::template push_back<void*>{}) == 3);
STATIC_ASSERT(find_if<ZXSHADY_BIND_TEMPLATE(std::is_same,void*)>(List{}) == std::size_t(-1));
STATIC_ASSERT(find_if<std::is_pointer>(List::template push_back<void*>{}) == 3);
STATIC_ASSERT(find_if<ZXSHADY_PREDICATE_NOT(std::is_pointer)>(List::template push_back<void*>{}) == 0);

STATIC_ASSERT(find<void,5>(List{}) == std::size_t(-1));

template<typename,typename>
struct Rename {};

IS_SAME(List::template erase<0>::template rename_to<Rename>,Rename<char,wchar_t>);
