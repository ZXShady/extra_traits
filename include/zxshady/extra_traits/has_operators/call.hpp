#ifndef ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_CALL_HPP
#define ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_CALL_HPP

namespace zxshady {
namespace tmp {

  template<typename T, typename... Args>
  struct has_operator_call {
  private:
#ifdef __cpp_concepts
    static constexpr bool free       = false;
    static constexpr bool member     = requires(T t, Args... args) { ZXSHADY_FWD(t).operator()(ZXSHADY_FWD(args)...); };
    static constexpr bool overloaded = member;
    static constexpr bool value      = requires(T t, Args... args) { ZXSHADY_FWD(t)(ZXSHADY_FWD(args)...); };
#else
    using this_type = has_operator_call;
    template<typename U>
    static auto member_check(U&& u) -> decltype(ZXSHADY_FWD(u).operator()(std::declval<Args>()...), std::true_type{});
    static auto member_check(...) -> std::false_type;
    template<typename U>
    static auto check(U&& u) -> decltype(ZXSHADY_FWD(u)(std::declval<Args>()...), std::true_type{});
    static auto check(...) -> std::false_type;
  public:
    static constexpr bool free       = false;
    static constexpr bool member     = decltype(this_type::member_check(std::declval<T>))::value;
    static constexpr bool overloaded = member;
    static constexpr bool value      = decltype(this_type::check(std::declval<T>()))::value;
#endif
  };

#ifdef __cpp_variable_templates
  template<typename T, typename... Args>
  constexpr bool has_operator_call_v = has_operator_call<T, Args...>::value;
#endif

} // namespace tmp
} // namespace zxshady
#endif // !ZXSHADY_EXTRA_TRAITS_HAS_OPERATORS_CALL_HPP