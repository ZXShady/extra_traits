cmake_minimum_required(VERSION 3.15.0)

add_executable(tests)

target_link_libraries(tests ZXShady::ExtraTraits)
if(MSVC)
  target_compile_options(tests PRIVATE /Za /permissive-)
endif()
target_compile_features(tests PRIVATE cxx_std_11)


target_sources(tests PRIVATE
  cast_const_away.cpp
  clone_cv.cpp
  clone_pointer.cpp
  clone_reference.cpp
  conjunction.cpp
  copy_all_extents.cpp
  copy_cv.cpp
  copy_cvref.cpp
  copy_pointer.cpp
  copy_reference.cpp
  copy_signedness.cpp
  disjunction.cpp
  # inherit_if.cpp
  is_bounded_array.cpp
  is_braces_constructible.cpp
  is_brackets_constructible.cpp
  is_explicitly_constructible.cpp
  # is_inheritable.cpp
  is_scoped_enum.cpp
  # is_specilization.cpp
  is_unbounded_array.cpp
  is_unscoped_enum.cpp
  # main.cpp
  negation.cpp
  # rebind_template.cpp
  remove_all_pointers.cpp
  remove_cvref.cpp
  type_list.cpp
  has_operator/plus.cpp
  test.hpp
)

