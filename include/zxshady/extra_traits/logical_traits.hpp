#ifndef ZXSHADY_EXTRA_TRAITS_LOGICAL_TRAITS_HPP
#define ZXSHADY_EXTRA_TRAITS_LOGICAL_TRAITS_HPP

#include "standard_library_features.hpp"
#include <type_traits>
namespace zxshady {
namespace tmp {

#ifdef __cpp_fold_expressions
  template<typename... Traits>
  using and_ = bool_constant<(!!Traits::value && ...)>;
  template<typename... Traits>
  using or_ = bool_constant<(!!Traits::value || ...)>;

#else
  template<typename... Traits>
  using and_ = std::is_same<integer_sequence<bool, !!Traits::value...>, integer_sequence<bool, (!!Traits::value || true)...>>;

  template<typename... Traits>
  using or_ = negation<std::is_same<integer_sequence<bool, !!Traits::value...>, integer_sequence<bool, (!!Traits::value && false)...>>>;
#endif

#ifdef __cpp_variable_templates

  template<typename... Traits>
  constexpr bool and_v =
  #ifdef __cpp_fold_expressions
    (!!Traits::value && ...);
  #else
    and_<Traits...>::value;
  #endif // __cpp_fold_expressions
  template<typename... Traits>
  constexpr bool or_v =
  #ifdef __cpp_fold_expressions
    (!!Traits::value || ...);
  #else
    or_<Traits::value...>::value;
  #endif // __cpp_fold_expressions
#endif
} // namespace tmp
} // namespace zxshady


#endif // ZXSHADY_EXTRA_TRAITS_LOGICAL_TRAITS_HPP
