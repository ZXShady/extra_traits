#include "test.hpp"

#include <zxshady/extra_traits/is_specialization_of.hpp>

#include <array>
#include <cstdint>
#include <deque>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <set>
#include <stack>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

template<typename, auto...>
struct TypeWithAutos;

template<auto, typename...>
struct AutoWithTypes;
#define CATCAT(x, y) x##y
#define CAT(x, y)    CATCAT(x, y)


#define dependant(T, ...)                                                              \
  auto CAT(_lol, __LINE__) = [](auto x) {                                              \
    STATIC_ASSERT(ZXSHADY_IS_SPECIALIZATION_OF(typename decltype(x)::type,T)::value); \
    return 0;                                                                          \
  }(std::type_identity<__VA_ARGS__>())
#define dependant_not(T, ...)                                                           \
  auto CAT(_lol, __LINE__) = [](auto x) {                                               \
    STATIC_ASSERT(!ZXSHADY_IS_SPECIALIZATION_OF(typename decltype(x)::type,T)::value); \
    return 0;                                                                           \
  }(std::type_identity<__VA_ARGS__>())


dependant(TypeWithAutos, TypeWithAutos<int, 1, 2, 3, 4>);
dependant_not(AutoWithTypes, TypeWithAutos<int, 1, 2, 3, 4>);

dependant(AutoWithTypes, AutoWithTypes<1, int, char, long>);
dependant_not(TypeWithAutos, AutoWithTypes<1, int, char, long>);

dependant(std::array, std::array<int, 5>);
dependant(std::vector, std::vector<double>);

dependant_not(std::tuple, std::pair<int, double>);
dependant(std::map, std::map<int, int>);

dependant_not(std::set, std::vector<int>);
dependant(std::optional, std::optional<float>);
dependant_not(std::variant, std::optional<int>);
dependant(std::unique_ptr, std::unique_ptr<int>);
dependant_not(std::shared_ptr, std::array<int, 5>);
dependant(std::shared_ptr, std::shared_ptr<int>);
dependant_not(std::array, std::vector<int>);
dependant(std::deque, std::deque<int>);
dependant_not(std::priority_queue, std::stack<int>);
dependant(std::queue, std::queue<int>);
dependant_not(std::stack, std::queue<int>);
dependant(std::stack, std::stack<int>);
dependant_not(std::unordered_map, std::map<int, int>);
dependant(std::unordered_set, std::unordered_set<int>);
dependant_not(std::multimap, std::unordered_map<int, int>);
