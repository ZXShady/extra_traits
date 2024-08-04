#ifndef ZXSHADY_EXTRA_TRAITS_LEAST_SIZE_INT_HPP
#define ZXSHADY_EXTRA_TRAITS_LEAST_SIZE_INT_HPP

#include <climits>
#include <cstdint>
#include <type_traits>

namespace zxshady {
namespace tmp {

  template<std::uint_least64_t N>
  struct least_size_uint {
    using type = typename std::conditional<
      (N <= UINT_LEAST8_MAX),
      std::uint_least8_t,
      typename std::conditional<
        (N <= UINT_LEAST16_MAX),
        std::uint_least16_t,
        typename std::conditional<(N <= UINT_LEAST32_MAX),
                                  std::uint_least32_t,
                                  typename std::conditional<(N <= UINT_LEAST64_MAX), std::uint_least64_t, void>::type>::type>::type>::type;
  };

  template<std::int_least64_t N>
  struct least_size_int {
  public:
    using type = typename std::make_signed<
      typename least_size_uint<static_cast<std::uint_least64_t>((N == INT_LEAST64_MIN) ? INT_LEAST64_MAX
                                                                 : (N < 0)             ? -N
                                                                                       : N)>::type>::type;
  };
  template<std::int_least64_t N>
  using least_size_int_t = typename least_size_int<N>::type; 

  template<std::uint_least64_t N>
  using least_size_uint_t = typename least_size_uint<N>::type;

} // namespace tmp
} // namespace zxshady


#endif // ZXSHADY_EXTRA_TRAITS_LEAST_SIZE_INT_HPP
