#ifndef ZXSHADY_EXTRA_TRAITS_QUALMANIP_HPP
#define ZXSHADY_EXTRA_TRAITS_QUALMANIP_HPP

#include "standard_library_features.hpp"
#include <type_traits>

namespace zxshady {
namespace tmp {


  template<typename T>
  struct remove_all_pointers :
  std::conditional<std::is_pointer<T>::value, remove_all_pointers<remove_pointer_t<T>>, type_identity<T>>::type {};

  template<typename T>
  using remove_all_pointers_t = typename remove_all_pointers<T>::type;


  // from paper p1016
  // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1016r0.pdf
  template<typename From, typename To>
  using copy_const = std::conditional<std::is_const<From>::value, const To, To>;

  template<typename From, typename To>
  using copy_const_t = typename copy_const<From, To>::type;

  template<typename From, typename To>
  using clone_const = copy_const<From, typename std::remove_const<To>::type>;

  template<typename From, typename To>
  using clone_const_t = typename clone_const<From, To>::type;

  template<typename From, typename To>
  using copy_volatile = std::conditional<std::is_volatile<From>::value, volatile To, To>;

  template<typename From, typename To>
  using copy_volatile_t = typename copy_volatile<From, To>::type;

  template<typename From, typename To>
  using clone_volatile = copy_volatile<From, typename std::remove_volatile<To>::type>;

  template<typename From, typename To>
  using clone_volatile_t = typename clone_volatile<From, To>::type;

  template<typename From, typename To>
  using copy_cv = copy_const<From, copy_volatile_t<From, To>>;

  template<typename From, typename To>
  using copy_cv_t = typename copy_cv<From, To>::type;

  template<typename From, typename To>
  using clone_cv = copy_cv<From, typename std::remove_cv<To>::type>;

  template<typename From, typename To>
  using clone_cv_t = typename clone_cv<From, To>::type;

  template<typename From, typename To>
  using copy_reference = std::conditional<!std::is_reference<From>::value,
                                          To,
                                          typename std::conditional<std::is_lvalue_reference<From>::value,
                                                                    typename std::add_lvalue_reference<To>::type,
                                                                    typename std::add_rvalue_reference<To>::type>::type>;
  template<typename From, typename To>
  using copy_reference_t = typename copy_reference<From, To>::type;

  template<typename From, typename To>
  using clone_reference = copy_reference<From, remove_reference_t<To>>;

  template<typename From, typename To>
  using clone_reference_t = typename clone_reference<From, To>::type;

  template<typename From, typename To>
  using copy_cvref = copy_reference<From, copy_reference_t<To, copy_cv_t<remove_reference_t<From>, remove_reference_t<To>>>>;

  template<typename From, typename To>
  using copy_cvref_t = typename copy_cvref<From, To>::type;

  template<typename From, typename To>
  using clone_cvref = copy_cvref<From, remove_cvref_t<To>>;

  template<typename From, typename To>
  using clone_cvref_t = typename clone_cvref<From, To>::type;

  template<typename From, typename To>
  using copy_pointer = std::conditional<std::is_pointer<From>::value, typename std::add_pointer<To>::type, To>;

  template<typename From, typename To>
  using copy_pointer_t = typename copy_pointer<From, To>::type;

  template<typename From, typename To>
  using clone_pointer = copy_pointer<From, typename std::remove_pointer<To>::type>;

  template<typename From, typename To>
  using clone_pointer_t = typename clone_pointer<From, To>::type;

  template<typename From, typename To>
  struct copy_all_pointers :
  public std::conditional<std::is_pointer<From>::value,
                          copy_all_pointers<typename std::remove_pointer<From>::type, typename std::add_pointer<To>::type>,
                          type_identity<To>>::type {};

  template<typename From, typename To>
  using copy_all_pointers_t = typename copy_all_pointers<From, To>::type;

  template<typename From, typename To>
  using clone_all_pointers = copy_all_pointers<From, remove_all_pointers_t<To>>;

  template<typename From, typename To>
  using clone_all_pointers_t = typename clone_all_pointers<From, To>::type;

  template<typename From, typename To>
  struct copy_extent {
    static_assert(std::extent<From, 0>::value != 0 && std::extent<To, 0>::value != 0,
                  "To shall not be an array of unknown bound along its"
                  "\nfirst dimension if From is an array of unknown bound along its"
                  "\nfirst dimension.");

    using type = typename std::conditional<
      !std::is_array<From>::value,
      To,
      typename std::conditional<(std::rank<From>::value != 0 && std::extent<From, 0>::value != 0),
                                To[std::extent<From, 0>::value != 0 ? std::extent<From, 0>::value : 1],
                                // the ternary conditional is to prevent To[0] since there is no short circuiting in std::conditional
                                To[]>::type>::type;
  };

  template<typename From, typename To>
  using copy_extent_t = typename copy_extent<From, To>::type;

  template<typename From, typename To>
  struct copy_all_extents :
  std::conditional<(std::rank<From>::value > 0),
                   copy_all_extents<typename std::remove_extent<From>::type, typename copy_extent<From, To>::type>,
                   type_identity<To>>::type {};

  template<typename From, typename To>
  using copy_all_extents_t = typename copy_all_extents<From, To>::type;

  template<typename From, typename To>
  using clone_all_extents = copy_all_extents<From, typename std::remove_all_extents<To>::type>;

  template<typename From, typename To>
  using clone_all_extents_t = copy_all_extents_t<From, typename std::remove_all_extents<To>::type>;

  template<typename From, typename To>
  struct copy_signedness {
    static_assert(std::is_enum<To>::value || std::is_integral<To>::value, "To must be an enum or integral type");
    static_assert(std::is_enum<From>::value || std::is_integral<From>::value, "From must be an enum or integral type");
    static_assert(!std::is_same<typename std::remove_cv<To>::type, bool>::value,
                  "To must not be a possibility cv qualified 'bool'");
    static_assert(!std::is_same<typename std::remove_cv<From>::type, bool>::value,
                  "From must not be a possibility cv qualified 'bool'");

    using type = typename std::conditional<
      std::is_same<From, typename std::make_signed<From>::type>::value,
      typename std::make_signed<To>::type,
      typename std::conditional<std::is_same<From, typename std::make_unsigned<From>::type>::value,
                                typename std::make_unsigned<To>::type,
                                To>::type>::type;
  };

  template<typename From, typename To>
  using copy_signedness_t = typename copy_signedness<From, To>::type;


  template<typename Like, typename T>
  constexpr copy_cvref_t<Like&&, T> forward_like(T&& t) noexcept
  {
    return static_cast<copy_cvref_t<Like&&, T>>(t);
  }

  template<typename T, typename U>
  using has_same_qualifiers = bool_constant<std::is_const<T>::value == std::is_const<U>::value &&
                                            std::is_volatile<T>::value == std::is_volatile<U>::value>;

} // namespace tmp
} // namespace zxshady

#endif
