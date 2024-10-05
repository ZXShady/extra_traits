#ifndef ZXSHADY_EXTRA_TRAITS_STANDARD_LIBRARY_FEATURES
#define ZXSHADY_EXTRA_TRAITS_STANDARD_LIBRARY_FEATURES

#include "macros.hpp"

#include <type_traits>
#include <utility>


namespace zxshady {
namespace tmp {

#if __cplusplus >= 201402L || (defined(_MSVC_LANG) && _MSVC_LANG >= 201402L)

  using ::std::add_const_t;
  using ::std::add_cv_t;
  using ::std::add_volatile_t;

  using ::std::remove_const_t;
  using ::std::remove_cv_t;
  using ::std::remove_volatile_t;

  using ::std::add_pointer_t;
  using ::std::remove_pointer_t;

  using ::std::add_lvalue_reference_t;
  using ::std::add_rvalue_reference_t;

  using ::std::remove_reference_t;

  using ::std::remove_extent_t;

  using ::std::conditional_t;
#else
  template<typename T>
  using add_const_t = typename ::std::add_const<T>::type;
  template<typename T>
  using add_volatile_t = typename ::std::add_volatile<T>::type;
  template<typename T>
  using add_cv_t = typename ::std::add_cv<T>::type;

  template<typename T>
  using remove_const_t = typename ::std::remove_const<T>::type;
  template<typename T>
  using remove_volatile_t = typename ::std::remove_volatile<T>::type;
  template<typename T>
  using remove_cv_t = typename ::std::remove_cv<T>::type;

  template<typename T>
  using add_lvalue_reference_t = typename ::std::add_lvalue_reference<T>::type;
  template<typename T>
  using add_rvalue_reference_t = typename ::std::add_rvalue_reference<T>::type;

  template<typename T>
  using remove_reference_t = typename ::std::remove_reference<T>::type;

  template<typename T>
  using remove_extent_t = typename ::std::remove_extent<T>::type;

  template<typename T>
  using add_pointer_t = typename ::std::add_pointer<T>::type;

  template<typename T>
  using remove_pointer_t = typename ::std::remove_pointer<T>::type;


  template<bool B, typename T, typename F>
  using conditional_t = typename ::std::conditional<B, T, F>::type;

#endif

#ifdef __cpp_lib_remove_cvref

  using ::std::remove_cvref;
  using ::std::remove_cvref_t;

#else

  template<typename T>
  using remove_cvref = std::remove_cv<typename std::remove_reference<T>::type>;

  template<typename T>
  using remove_cvref_t = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

#endif

#ifdef __cpp_lib_is_null_pointer
  using ::std::is_null_pointer;
#else
  template<typename T>
  using is_null_pointer = ::std::is_same<std::nullptr_t, typename std::remove_cv<T>::type>;
#endif


#ifdef __cpp_lib_type_identity

  using ::std::type_identity;
  using ::std::type_identity_t;

#else

  template<typename T>
  struct type_identity {
    using type = T;
  };
  template<typename T>
  using type_identity_t = typename type_identity<T>::type;

#endif

#ifdef __cpp_lib_bool_constant
  using ::std::bool_constant;
#else
  template<bool B>
  using bool_constant = std::integral_constant<bool, B>;
#endif

#ifdef __cpp_lib_integer_sequence

  using ::std::index_sequence;
  using ::std::integer_sequence;
  using ::std::make_index_sequence;
  using ::std::make_integer_sequence;

#else // !defined(__cpp_lib_integer_sequence)

  // based on http://stackoverflow.com/a/17426611/410767 by Xeo
  template<typename Int, Int... Ints>
  struct integer_sequence {
    using value_type = Int;
    static constexpr std::size_t size() noexcept { return sizeof...(Ints); }
  };


  namespace details {
    // Merge two integer sequences, adding an offset to the right-hand side.
    template<typename Offset, typename Lhs, typename Rhs>
    struct merge;

    template<typename Int, Int Offset, Int... Lhs, Int... Rhs>
    struct merge<std::integral_constant<Int, Offset>, integer_sequence<Int, Lhs...>, integer_sequence<Int, Rhs...>> {
      using type = integer_sequence<Int, Lhs..., (Offset + Rhs)...>;
    };

    template<typename Int, typename N>
    struct log_make_sequence {
      using L = std::integral_constant<Int, N::value / 2>;
      using R = std::integral_constant<Int, N::value - L::value>;
      using type = typename merge<L, typename log_make_sequence<Int, L>::type, typename log_make_sequence<Int, R>::type>::type;
    };

    // An empty sequence.
    template<typename Int>
    struct log_make_sequence<Int, std::integral_constant<Int, 0>> {
      using type = integer_sequence<Int>;
    };

    // A single-element sequence.
    template<typename Int>
    struct log_make_sequence<Int, std::integral_constant<Int, 1>> {
      using type = integer_sequence<Int, 0>;
    };
  } // namespace details

  template<typename Int, Int N>
  using make_integer_sequence = typename details::log_make_sequence<Int, std::integral_constant<Int, N>>::type;

  template<std::size_t N>
  using make_index_sequence = make_integer_sequence<std::size_t, N>;

  template<std::size_t... Indices>
  using index_sequence = integer_sequence<std::size_t, Indices...>;


#endif // !defined(__cpp_lib_integer_sequence)

// is that another Compiler Bug with Microsoft Again???!
// yes.
// https://discord.com/channels/583251190591258624/583254410218700800/1263979538883416185
// :D
#if defined(__cpp_lib_logical_traits) && !(defined(_MSC_VER) && !(defined(__clang__) || defined(__INTEL_COMPILER)))
  using ::std::conjunction;
  using ::std::conjunction_v;
  using ::std::disjunction;
  using ::std::disjunction_v;
  using ::std::negation;
  using ::std::negation_v;
#else
  template<typename...>
  struct conjunction : std::true_type {};
  template<typename Trait>
  struct conjunction<Trait> : Trait {};
  template<typename Trait, typename... Traits>
  struct conjunction<Trait, Traits...> :
  ::std::conditional<static_cast<bool>(Trait::value), conjunction<Traits...>, Trait>::type {};

  template<typename...>
  struct disjunction : std::false_type {};
  template<typename Trait>
  struct disjunction<Trait> : Trait {};
  template<typename Trait, typename... Traits>
  struct disjunction<Trait, Traits...> :
  ::std::conditional<static_cast<bool>(Trait::value), Trait, disjunction<Traits...>>::type {};


  template<typename T>
  using negation = bool_constant<!T::value>;

  #if defined(__cpp_variable_templates)
  template<typename... Traits>
  constexpr bool disjunction_v = disjunction<Traits...>::value;

  template<typename... Traits>
  constexpr bool conjunction_v = conjunction<Traits...>::value;

  template<typename Trait>
  constexpr bool negation_v = !Trait::value;
  #endif
#endif // __cpp_lib_logical_traits


#ifdef __cpp_lib_void_t
  using ::std::void_t;
#else
  namespace details {
    template<typename...>
    struct make_void {
      using type = void;
    };
  } // namespace details
  template<typename... T>
  using void_t = typename details::make_void<T...>::type;
#endif // __cpp_lib_void_t


#ifdef __cpp_lib_is_scoped_enum
  using ::std::is_scoped_enum;
  using ::std::is_scoped_enum_v;
#else
  namespace details {
    template<bool /*is_enum*/, typename>
    struct is_scoped_enum : ::std::false_type {};
    template<typename Enum>
    struct is_scoped_enum<true, Enum> :
    negation<std::is_convertible<Enum, typename ::std::underlying_type<Enum>::type>> {};
  } // namespace details


  template<typename T>
  using is_scoped_enum = details::is_scoped_enum<std::is_enum<T>::value, T>;

  #if defined(__cpp_variable_templates)
  template<typename T>
  constexpr bool is_scoped_enum_v = is_scoped_enum<T>::value;
  #endif

#endif

#ifdef __cpp_lib_bounded_array_traits

  using ::std::is_bounded_array;
  using ::std::is_bounded_array_v;
  using ::std::is_unbounded_array;
  using ::std::is_unbounded_array_v;

#else

  template<typename>
  struct is_bounded_array : std::false_type {};
  template<typename T, std::size_t N>
  struct is_bounded_array<T[N]> : std::true_type {};

  template<typename>
  struct is_unbounded_array : std::false_type {};
  template<typename T>
  struct is_unbounded_array<T[]> : std::true_type {};

#endif


} // namespace tmp
} // namespace zxshady

#endif // !ZXSHADY_EXTRA_TRAITS_STANDARD_LIBRARY_FEATURES
