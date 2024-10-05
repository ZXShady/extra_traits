#ifndef ZXSHADY_EXTRA_TRAITS_LOGICAL_PREDICATES_HPP
#define ZXSHADY_EXTRA_TRAITS_LOGICAL_PREDICATES_HPP
#endif // !ZXSHADY_EXTRA_TRAITS_LOGICAL_PREDICATES_HPP


#include "macros.hpp"

namespace zxshady {
namespace tmp {

  template<template<typename> class... UnaryPredicates>
  struct predicate_and {
    template<typename T>
    struct invoke : conjunction<UnaryPredicates<T>...> {};
  };

  template<template<typename> class... UnaryPredicates>
  struct predicate_or {
    template<typename T>
    struct invoke : disjunction<UnaryPredicates<T>...> {};
  };

  template<template<typename> class UnaryPredicate>
  struct predicate_not {
    template<typename T>
    struct invoke : negation<UnaryPredicate<T>> {};
  };

} // namespace tmp
} // namespace zxshady