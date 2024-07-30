# project
cmake_minimum_required(VERSION 3.22.0)
project(extra_traits LANGUAGES CXX)

# target
if(POLICY CMP0128)
    cmake_policy(SET CMP0128 NEW)
endif()

set(INCS "")
file(GLOB_RECURSE INCS "include/*.hpp")

add_library(zxshady_extra_traits INTERFACE ${INCS})
add_library(ZXShady::ExtraTraits ALIAS zxshady_extra_traits)

target_include_directories(zxshady_extra_traits INTERFACE
    include
)



option(ZXSHADY_EXTRA_TRAITS_BUILD_TESTS "Static tests for this type traits library" OFF)

if(ZXSHADY_EXTRA_TRAITS_BUILD_TESTS)
  add_subdirectory(tests)
endif()
