cmake_minimum_required(VERSION 3.15.0)
include(CheckCXXCompilerFlag)

add_executable(tests)

target_link_libraries(tests ZXShady::ExtraTraits)
target_compile_features(tests PRIVATE cxx_std_20)

if(MSVC)
  target_compile_options(tests PRIVATE /Za /permissive-)
endif()

if(MSVC)
  target_compile_options(tests PRIVATE /W4)
else()
  target_compile_options(tests PRIVATE -Wall -Wextra -Wconversion -Wpedantic)
endif()




set(SRCS 
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
  logical_traits.cpp
  inherit_if.cpp
  is_bounded_array.cpp
  is_braces_constructible.cpp
  is_brackets_constructible.cpp
  is_explicitly_constructible.cpp
  is_inheritable.cpp
  is_scoped_enum.cpp
  is_unbounded_array.cpp
  is_unscoped_enum.cpp

  main.cpp
  negation.cpp
  rebind_template.cpp
  remove_all_pointers.cpp
  remove_cvref.cpp
  type_list.cpp
  least_size_int.cpp
  has_operator/plus.cpp
  test.hpp
)

if(${CMAKE_CXX_STANDARD} GREATER_EQUAL 17)
	list(APPEND SRCS is_specialization_of.cpp)
endif()

target_sources(tests PRIVATE
	${SRCS}
)

