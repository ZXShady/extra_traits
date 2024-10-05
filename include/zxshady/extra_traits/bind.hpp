#ifndef ZXSHADY_EXTRA_TRAITS_BIND_HPP
#define ZXSHADY_EXTRA_TRAITS_BIND_HPP

#include "standard_library_features.hpp"

namespace zxshady {
namespace tmp {


  template<template<typename...> class Template, typename... BoundArgs>
  struct bind_front {
    template<typename... Args>
    struct invoke : Template<BoundArgs..., Args...> {};
  };

  template<template<typename...> class Template, typename... BoundArgs>
  struct bind_back {
    template<typename... Args>
    struct invoke : Template<Args..., BoundArgs...> {};
  };

  namespace details {
    template<typename... RebindWith, template<typename...> class Template, typename... TemplateArgs>
    Template<RebindWith...> rebind_template(const Template<TemplateArgs...>&);
  } // namespace details

  template<typename Template, typename... RebindWith>
  using rebind_template_t =  decltype(details::rebind_template<RebindWith...>(std::declval<Template>()));

  template<typename Template, typename... RebindWith>
  using rebind_template = type_identity<rebind_template_t<Template,RebindWith...>>;

} // namespace tmp
} // namespace zxshady

#endif // !ZXSHADY_EXTRA_TRAITS_BIND_HPP