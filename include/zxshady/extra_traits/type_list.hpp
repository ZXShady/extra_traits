#ifndef ZXSHADY_EXTRA_TRAITS_TYPE_LIST_HPP
#define ZXSHADY_EXTRA_TRAITS_TYPE_LIST_HPP

#include "standard_library_features.hpp"
#include "utility.hpp"

#include <cstddef>

namespace zxshady {
namespace tmp {

  template<typename...>
  struct type_list;

  namespace details {
    namespace type_list {

      template<std::size_t Index, typename T>
      struct type_with_index {
        static constexpr std::size_t index = Index;
        using type                         = T;
      };

      // why not just return T
      // because if T is a const / volatile / cv qualified fundemintal type
      // it will drop the qualifiers
      // won't happen if it is a class type
      template<std::size_t Index, typename T>
      type_identity<T> get_type_by_index(type_with_index<Index, T>);

      struct at_index_out_of_bounds {};

      template<std::size_t>
      type_identity<at_index_out_of_bounds> get_type_by_index(...);


      template<typename... Ts, std::size_t... Is>
      inherit_from_all<type_with_index<Is, Ts>...> make_types_with_index(index_sequence<Is...>);

      template<std::size_t Index, typename TypesWithIndex>
      struct at_check_bounds {
        static_assert(Index != static_cast<std::size_t>(-1), "type_list::at<Index>. Index is out of bounds");
        using type = typename decltype(details::type_list::get_type_by_index<Index>(std::declval<TypesWithIndex>()))::type;
      };

      template<typename...>
      struct pop_front {
        using type = ::zxshady::tmp::type_list<>;
      };

      template<typename T, typename... Ts>
      struct pop_front<T, Ts...> {
        using type = ::zxshady::tmp::type_list<Ts...>;
      };

      template<typename, template<typename> class>
      struct erase_if;

      template<template<typename> class Predicate>
      struct erase_if<::zxshady::tmp::type_list<>, Predicate> {
        using type = ::zxshady::tmp::type_list<>;
      };

      template<typename T, template<typename> class Predicate>
      struct erase_if<::zxshady::tmp::type_list<T>, Predicate> {
        using type = typename std::conditional<!!Predicate<T>::value, ::zxshady::tmp::type_list<>, ::zxshady::tmp::type_list<T>>::type;
      };

      template<typename T, typename... Ts, template<typename> class Predicate>
      struct erase_if<::zxshady::tmp::type_list<T, Ts...>, Predicate> {
        using type = typename std::conditional<
          !!Predicate<T>::value,
          typename erase_if<::zxshady::tmp::type_list<Ts...>, Predicate>::type,
          typename erase_if<::zxshady::tmp::type_list<Ts...>, Predicate>::type::template push_front<T>>::type;
      };

      template<std::size_t Offset, typename List, std::size_t... Is>
      ::zxshady::tmp::type_list<typename List::template at<(Offset + Is)>...> slice(index_sequence<Is...>);


    } // namespace type_list
  }   // namespace details


  template<typename... Types>
  struct type_list {
    static constexpr std::size_t size     = sizeof...(Types);
    static constexpr std::size_t is_empty = (size == 0);
    using types_with_index                = decltype(details::type_list::make_types_with_index<Types...>(
      make_index_sequence<sizeof...(Types)>()));


    template<std::size_t Begin, std::size_t End = sizeof...(Types)>
    using slice = decltype(details::type_list::slice<Begin, type_list>(make_index_sequence<End - Begin>()));


    template<std::size_t Index>
    using at = typename details::type_list::at_check_bounds<(Index < size ? Index : static_cast<std::size_t>(-1)),
                                                            types_with_index>::type;


    template<std::size_t Index, typename OrType>
    using at_or = typename std::
      conditional<(Index < size), decltype(details::type_list::get_type_by_index<Index>(std::declval<types_with_index>())), OrType>::type;

    using front = at<0>;
    using back  = at<(is_empty ? 0 : size - 1)>;

    template<typename T>
    using push_back = type_list<Types..., T>;

    template<typename T>
    using push_front = type_list<T, Types...>;

    template<typename... Us>
    using append = type_list<Types..., Us...>;

    template<typename... Us>
    using prepend = type_list<Us..., Types...>;


    template<std::size_t... Is>
    static type_list<at<(size - Is - 1)>...> reverse_impl(index_sequence<Is...>);

    template<std::size_t... Is>
    static type_list<at<Is>...> pop_front_impl(index_sequence<Is...>);

    template<typename T, typename... Ts>
    static type_list<Ts...> pop_back_impl(const type_list<T, Ts...>&);

    using reverse = decltype(reverse_impl(make_index_sequence<size>()));

    using pop_front = typename details::type_list::pop_front<Types...>::type;

    using pop_back = decltype(pop_front_impl(make_index_sequence<(!is_empty ? size - 1 : 0)>()));

    template<std::size_t Count>
    using drop_first = slice<Count>;

    template<std::size_t Count>
    using drop_last = slice<0, size - Count>;

    template<std::size_t Index, typename T>
    using replace_at = decltype(slice<0, Index>{} + type_list<T>{});

    template<template<typename> class TransformTrait>
    using transform = type_list<typename TransformTrait<Types>::type...>;

    template<template<typename...> class To, typename... A1, typename... A2, typename... A3>
    static To<A1..., A2..., A3...> rename_to_impl(type_list<A1...>&&, type_list<A2...>&&, type_list<A3...>&&);


    template<template<typename...> class To, typename BeforeArgsTypeList = type_list<>, typename AfterArgsTypeList = type_list<>>
    using rename_to = decltype(rename_to_impl<To>(std::declval<BeforeArgsTypeList>(),
                                                  std::declval<type_list<Types...>>(),
                                                  std::declval<AfterArgsTypeList>()));


    template<typename... Us, std::size_t... FrontIs, std::size_t... BackIs>
    static type_list<at<FrontIs>..., Us..., at<(sizeof...(FrontIs) + BackIs)>...> insert_impl(index_sequence<FrontIs...>,
                                                                                              index_sequence<BackIs...>);
    //   0     1    2
    // int,short,char
    //
    template<std::size_t Pos, std::size_t... FrontIs, std::size_t... BackIs>
    static type_list<at<(FrontIs)>..., at<(sizeof...(FrontIs) + BackIs + 1)>...> erase_impl(index_sequence<FrontIs...>,
                                                                                            index_sequence<BackIs...>);






  public:
    // clang-format off
    template<std::size_t Pos,typename... Us>
    using insert = decltype(type_list::template insert_impl<Us...>(
            make_index_sequence<Pos>(),
            make_index_sequence<size - Pos>()
        ));
    // clang-format on

    template<std::size_t Pos, template<typename...> class UnaryPredicate, std::size_t... Is>
    static constexpr std::size_t find_impl(index_sequence<Is...>)
    {
      // explicitly using my version to work around MSVC BUG!
      // refer to standard_library_features.hpp
      return zxshady::tmp::disjunction<
               std::integral_constant<std::size_t, !!UnaryPredicate<at<(Pos + Is)>>::value ? (Pos + Is + 1) : 0>...>::value -
        1;
    }


    template<std::size_t Pos>
    using erase = decltype(erase_impl<Pos>(make_index_sequence<Pos>(), make_index_sequence<size - Pos - 1>()));

    template<template<typename> class UnaryPredicate>
    using erase_if = typename details::type_list::erase_if<type_list, UnaryPredicate>::type;
  };

  template<template<typename...> class UnaryPredicate, typename... Ts>
  constexpr bool all_of(type_list<Ts...>)
  {
#if defined(__cpp_fold_expressions)
    return (UnaryPredicate<Ts>::value && ...);
#else
    return conjunction<UnaryPredicate<Ts>...>::value;
#endif
  }

  template<template<typename...> class UnaryPredicate, typename... Ts>
  constexpr bool any_of(type_list<Ts...>)
  {
#if defined(__cpp_fold_expressions)
    return (UnaryPredicate<Ts>::value || ...);
#else
    return disjunction<UnaryPredicate<Ts>...>::value;
#endif
  }

  template<typename Find, std::size_t Pos = 0, typename... Ts>
  constexpr std::size_t find(type_list<Ts...>) noexcept
  {
    return type_list<Ts...>::template find_impl<Pos,ZXSHADY_BIND_TEMPLATE(std::is_same, Find)>(
      make_index_sequence<sizeof...(Ts) - Pos>());
  }

  template<template<typename...> class UnaryPredicate, std::size_t Pos = 0, typename... Ts>
  constexpr std::size_t find_if(type_list<Ts...>) noexcept
  {
    return type_list<Ts...>::template find_impl<Pos, UnaryPredicate>(make_index_sequence<sizeof...(Ts) - Pos>());
  }


  template<typename T, typename... Ts>
  constexpr bool contains(type_list<Ts...>)
  {
#if defined(__cpp_fold_expressions)
    return (std::is_same<T, Ts>::value || ...);
#else
    return disjunction<std::is_same<T, Ts>...>::value;
#endif
  }

  template<typename... Ts, typename... Us>
  type_list<Ts..., Us...> operator+(type_list<Ts...>, type_list<Us...>);

} // namespace tmp
} // namespace zxshady


#endif // !defined(ZXSHADY_EXTRA_TRAITS_TYPE_LIST_HPP)
