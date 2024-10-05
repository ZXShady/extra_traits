#include "test.hpp"
#include <zxshady/extra_traits/type_list.hpp>
#include <zxshady/extra_traits/logical_predicates.hpp>

using zxshady::tmp::type_list;

using List = zxshady::tmp::type_list<int, char, wchar_t>;


STATIC_ASSERT(List::size == 3);
STATIC_ASSERT(!List::is_empty);
IS_SAME(List::reverse, zxshady::tmp::type_list<wchar_t, char, int>);

IS_SAME(List::pop_back, zxshady::tmp::type_list<int, char>);
IS_SAME(List::pop_front, zxshady::tmp::type_list<char, wchar_t>);

IS_SAME(List::template at<1>, char);
IS_SAME(List::template at_or<5, void>, void);

IS_SAME(List::back, wchar_t);
IS_SAME(List::front, int);

IS_SAME(List::template slice<0>, zxshady::tmp::type_list<int, char, wchar_t>);
IS_SAME(List::template slice<3>, zxshady::tmp::type_list<>);
IS_SAME(List::template slice<2>, zxshady::tmp::type_list<wchar_t>);

IS_SAME(List::template replace_at<0, void>, zxshady::tmp::type_list<void, char, wchar_t>);
IS_SAME(List::template replace_at<1, void>, zxshady::tmp::type_list<int, void, wchar_t>);
IS_SAME(List::template replace_at<2, void>, zxshady::tmp::type_list<int, char, void>);

IS_SAME(decltype(List{} + type_list<int, float>{})::template slice<2>, type_list<wchar_t, int, float>);

IS_SAME(decltype(List{} + type_list<int, float>{})::template drop_first<2>, type_list<wchar_t, int, float>);
IS_SAME(decltype(List{} + type_list<int, float>{})::template drop_last<2>, type_list<int, char, wchar_t>);

IS_SAME(decltype(List{} + type_list<float>{}), type_list<int, char, wchar_t, float>);
IS_SAME(decltype(type_list<float>{} + List{}), type_list<float, int, char, wchar_t>);

IS_SAME(decltype(List{} + type_list<float, double>{}), type_list<int, char, wchar_t, float, double>);
IS_SAME(decltype(type_list<float, double>{} + List{}), type_list<float, double, int, char, wchar_t>);
IS_SAME(List::template insert<1, void*, long>, type_list<int, void*, long, char, wchar_t>);

IS_SAME(List::template erase<1>, type_list<int, wchar_t>);
IS_SAME(List::template transform<std::add_const>, type_list<const int, const char, const wchar_t>);

using BigList = decltype(List{} + type_list<const void* const, long int>{});

IS_SAME(BigList::template slice<2>, type_list<wchar_t, const void* const, long>);

IS_SAME(BigList::template drop_first<2>, type_list<wchar_t, const void* const, long>);

IS_SAME(BigList::template drop_last<2>, type_list<int, char, wchar_t>);


STATIC_ASSERT(find<void*>(List{} + type_list<void*>{}) == 3);
STATIC_ASSERT(find_if<zxshady::tmp::bind_front<std::is_same, void*>::template invoke>(List{}) == std::size_t(-1));
STATIC_ASSERT(find_if<std::is_pointer>(List{} + type_list<void*>{}) == 3);
STATIC_ASSERT(find_if<zxshady::tmp::predicate_not<std::is_pointer>::template invoke>(List{} + type_list<void*>{}) == 0);

STATIC_ASSERT(find<void, 5>(List{}) == std::size_t(-1));

IS_SAME(zxshady::tmp::type_list_repeat_n<5, int>, type_list<int, int, int, int, int>);
IS_SAME(zxshady::tmp::type_list_repeat_n<0, int>, type_list<>);
IS_SAME(zxshady::tmp::type_list_repeat_n<1, int>, type_list<int>);

template<typename, typename>
struct Rename {};

IS_SAME(List::template erase<0>::template rename_to<Rename>, Rename<char, wchar_t>);
