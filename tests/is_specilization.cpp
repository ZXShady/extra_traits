#include "test.hpp"
#include <variant>
#include <optional>
#include <array>
#include <vector>
#if 0
STATIC_ASSERT(ZXSHADY_IS_SPECILIZALION_OF(std::variant, std::variant<int, float>)::value);
STATIC_ASSERT(ZXSHADY_IS_SPECILIZALION_OF(std::optional, std::optional<int>)::value);
static_assert(decltype(is_specilization<std::array>
              (std::declval<std::array<int, 5>>()))::value,
              "ZXSHADY_IS_SPECILIZALION_OF(std::array, std::array<int,5>)::value");
STATIC_ASSERT(ZXSHADY_IS_SPECILIZALION_OF(std::array, std::vector<int>)::value);
#endif