#ifndef ZXSHADY_EXTRA_TRAITS_TYPE_LIST_HPP
#define ZXSHADY_EXTRA_TRAITS_TYPE_LIST_HPP

#include "standard_library_features.hpp"
#include <cstddef>

namespace zxshady {
namespace tmp {

  namespace details {
    struct internal_dummy_tag;
  } // namespace details

  template<typename... Types>
  struct type_list {
  public:
    static constexpr std::size_t size     = sizeof...(Types);
    static constexpr std::size_t is_empty = (size == 0);

  private:
    template<std::size_t Index, typename, typename... Ts>
    struct at_no_bounds_check_impl {
      using type = typename at_no_bounds_check_impl<Index - 1, Ts...>::type;
    };
    template<typename T, typename... Ts>
    struct at_no_bounds_check_impl<0, T, Ts...> {
      using type = T;
    };

    template<std::size_t Index, typename... Ts>
    struct at_bounds_check {
      static_assert(Index < size, "Index out of bounds.");
      using type = typename at_no_bounds_check_impl<Index, Ts...>::type;
    };
  public:
    template<std::size_t Index>
    using at = typename at_bounds_check<Index, Types...>::type;

    template<std::size_t Index, typename OrType>
    using at_or = typename conditional_t<(Index < size), at_no_bounds_check_impl<Index, Types...>, type_identity<OrType>>::type;

    using front = at<0>;
    using back  = at<size - 1>;

  private:
    template<typename, typename... Ts>
    struct pop_front_impl {
      using type = type_list<Ts...>;
    };
    struct pop_back_impl {
      template<std::size_t... Is>
      static type_list<at<Is>...> indexes(index_sequence<Is...>);

      using type = decltype(indexes(make_index_sequence<sizeof...(Types) - 1>()));
    };

    struct reverse_impl {
      template<std::size_t... Is>
      static type_list<at<(sizeof...(Types) - Is - 1)>...> indexes(index_sequence<Is...>);

      using type = decltype(indexes(make_index_sequence<sizeof...(Types)>()));
    };
  public:
    template<typename T>
    using push_back = type_list<Types..., T>;

    template<typename T>
    using push_front = type_list<T, Types...>;

    template<typename... Us>
    using append = type_list<Types..., Us...>;

    template<typename... Us>
    using prepend = type_list<Us..., Types...>;

    using pop_front = typename pop_front_impl<Types...>::type;

    using pop_back = typename pop_back_impl::type;

    template<template<typename> class TransformTrait>
    using transform = type_list<typename TransformTrait<Types>::type...>;

    using reverse = typename reverse_impl::type;

  private:
    template<std::size_t Pos, template<typename...> class Predicate, typename... Args, std::size_t... Is>
    static constexpr std::size_t find_impl(index_sequence<Is...>)
    {
      // doing a multiplciation since if you learn some boolean algebra
      // bool * value
      // if bool is false (0)
      // then value is 0
      // if bool is true
      // then value is same
      // now we are adding to Pos and Is 1 to not make them false
      // then subtracting 1 in the end
      // so if all of them was false it will be the npos
      return disjunction<std::integral_constant<std::size_t, !!Predicate<at<Is>, Args...>::value * (Pos + Is + 1)>...>::value -
        1;
    }

    template<typename... Us, std::size_t... FrontIs, std::size_t... BackIs>
    static type_list<at<FrontIs>..., Us..., at<(sizeof...(FrontIs) + BackIs)>...> insert_impl(index_sequence<FrontIs...>,
                                                                                              index_sequence<BackIs...>);
    //   0     1    2
    // int,short,char
    // 
    template<std::size_t Pos,std::size_t... FrontIs, std::size_t... BackIs>
    static type_list<
        at<(FrontIs)>...
,        at<(sizeof...(FrontIs) + BackIs + 1)>...> 
        erase_impl(index_sequence<FrontIs...>,
                                                                                      index_sequence<BackIs...>);

  public:
    // clang-format off
    template<std::size_t Pos,typename... Us>
    using insert = decltype(insert_impl<Us...>(
            make_index_sequence<Pos>(),
            make_index_sequence<size - Pos>()
        ));
    // clang-format on
    template<typename Find, std::size_t Pos = 0>
    static constexpr std::size_t find() noexcept
    {
      return find_impl<Pos, std::is_same, Find>(make_index_sequence<size - Pos>());
    }

    template<template<typename> class UnaryTrait, std::size_t Pos = 0>
    static constexpr std::size_t find_if() noexcept
    {
      return find_impl<Pos, UnaryTrait>(make_index_sequence<size - Pos>());
    }


    template<typename T>
    static constexpr bool contains()
    {
      return disjunction<std::is_same<T, Types...>>::value;
    }

    template<std::size_t Pos>
    using erase = decltype(erase_impl<Pos>(make_index_sequence<Pos>(),
                           make_index_sequence<size - Pos - 1>()));
  
};

} // namespace tmp
} // namespace zxshady


#endif // !defined(ZXSHADY_EXTRA_TRAITS_TYPE_LIST_HPP)