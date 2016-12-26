cmake_minimum_required(VERSION 3.2)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)
project(optional.tests)

include(GetProjectFiles)
include(SetCompilerOptions)

set(OPTIONAL_TESTS_FILES)
get_project_files(OPTIONAL_TESTS_FILES)

add_executable(${PROJECT_NAME} ${OPTIONAL_TESTS_FILES})
set_compiler_options()

set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/optional/include
    ${CMAKE_SOURCE_DIR}/3rdparty/gtest/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE gtest)



