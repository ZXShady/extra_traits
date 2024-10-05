#ifndef ZXSHADY_EXTRA_TRAITS_LOGICAL_TRAITS_HPP
#define ZXSHADY_EXTRA_TRAITS_LOGICAL_TRAITS_HPP

#include "standard_library_features.hpp"
#include <type_traits>
namespace zxshady {
namespace tmp {

#ifdef __cpp_fold_expressions
  template<bool... Bools>
  using and_ = bool_constant<(Bools && ...)>;
  template<bool... Bools>
  using or_ = bool_constant<(Bools || ...)>;

#else
  template<bool... Bools>
  using and_ = std::is_same<integer_sequence<bool,true, Bools...>, integer_sequence<bool, Bools...,true>>;

  template<bool... Bools>
  using or_ = negation<std::is_same<integer_sequence<bool, false,Bools...>, integer_sequence<bool, Bools...,false>>>;
#endif

#ifdef __cpp_variable_templates

  template<bool... Bools>
  constexpr bool and_v =
  #ifdef __cpp_fold_expressions
    (Bools && ...);
  #else
    and_<Bools...>::value;
  #endif // __cpp_fold_expressions
  template<bool... Bools>
  constexpr bool or_v =
  #ifdef __cpp_fold_expressions
    (Bools || ...);
  #else
    or_<Bools...>::value;
  #endif // __cpp_fold_expressions
#endif
} // namespace tmp
} // namespace zxshady


#endif // ZXSHADY_EXTRA_TRAITS_LOGICAL_TRAITS_HPP
