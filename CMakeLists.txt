cmake_minimum_required(VERSION 3.2)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)
project(optional.project)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/cmake-modules)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(BUILD_GTEST ON)
set(BUILD_GMOCK OFF)

add_subdirectory("${CMAKE_SOURCE_DIR}/tests")
add_subdirectory("${CMAKE_SOURCE_DIR}/3rdparty/gtest")
