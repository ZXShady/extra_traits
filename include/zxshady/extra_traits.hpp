#ifndef ZXSHADY_EXTRA_TRAITS_HPP
#define ZXSHADY_EXTRA_TRAITS_HPP

#if !defined(__cpp_variadic_templates) || !defined(__cpp_alias_templates)

  #error This zxshady/extended_traits.hpp header requires variadic and alias templates supports.

#endif // !__cpp_variadic_templates

#include "extra_traits/bind.hpp"
#include "extra_traits/casts.hpp"
#include "extra_traits/has_operators.hpp"
#include "extra_traits/is_brackets_braces_constructible.hpp"
#include "extra_traits/is_explicitly_constructible.hpp"
#include "extra_traits/is_implicitly_constructible.hpp"
#ifdef __cpp_nontype_template_parameter_auto
  #include "extra_traits/is_specialization_of.hpp"
#endif
#include "extra_traits/is_static_castable.hpp"
#include "extra_traits/least_size_int.hpp"
#include "extra_traits/literals.hpp"
#include "extra_traits/logical_predicates.hpp"
#include "extra_traits/logical_traits.hpp"
#include "extra_traits/macros.hpp"
#include "extra_traits/qualmanip.hpp"
#include "extra_traits/standard_library_features.hpp"
#include "extra_traits/type_list.hpp"
#include "extra_traits/uniform_type_construction.hpp"
#include "extra_traits/utility.hpp"

#endif