#pragma once

#include <climits>
#include <type_traits>

namespace zxshady {
namespace tmp {

  namespace details {
    namespace literals {
      constexpr unsigned long long constexpr_pow(unsigned long long x, unsigned long long y, unsigned long long base = 1)
      {
        return y == 0 ? base : constexpr_pow(x, y - 1, base * x);
      }
    } // namespace literals
  }   // namespace details

  inline namespace literals {
    inline namespace constant_literals {
      template<char C, char... Cs>
      struct parse :
      std::integral_constant<unsigned long long,
                             (details::literals::constexpr_pow(10, sizeof...(Cs)) * parse<C>::value) + parse<Cs...>::value> {
      };

      template<char C>
      struct parse<C> : std::integral_constant<unsigned long long, C - '0'> {};

      template<char... Chars>
      constexpr std::integral_constant<unsigned long long, parse<Chars...>::value> operator""_c() noexcept
      {
        return {};
      }

    } // namespace constant_literals
  }   // namespace literals
} // namespace tmp
} // namespace zxshady
