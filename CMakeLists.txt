cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
cmake_policy(VERSION 3.18.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(ibex VERSION 0.1.0 LANGUAGES C CXX)

set(IBEX_BUILD_COMMANDLINE_TOOL false CACHE BOOL "Whether to build the commandline tool.")

# Add Library
add_library("${PROJECT_NAME}" STATIC
    src/ibex/ibex.cpp
    src/ibex/ibex.hpp
)
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src>
)

# Add command line tool
if(IBEX_BUILD_COMMANDLINE_TOOL)
    add_executable(ibex-cli ibex-cli.cpp)
    target_link_libraries(ibex-cli PRIVATE "${PROJECT_NAME}")
endif()

# Testing
set(IBEX_BUILD_UNIT_TESTS false CACHE BOOL "Whether to build the unit tests.")
if (IBEX_BUILD_UNIT_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    add_subdirectory(tests)
endif()
