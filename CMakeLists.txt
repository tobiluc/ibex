cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
cmake_policy(VERSION 3.18.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(ibex VERSION 0.1.0 LANGUAGES C CXX)

# Allow big files for gnu compiler
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")
endif()

include(FetchContent)

#================================================
# Check if standalone or within other project
#================================================
if( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
    set(IBEX_STANDALONE_BUILD TRUE)
    message("Configuring IBEX as standalone project...")
else()
    set(IBEX_STANDALONE_BUILD FALSE)
    message("Configuring IBEX inside another cmake project...")
endif()

if(IBEX_STANDALONE_BUILD)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Build/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Build/lib")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Build/lib")
endif()

#================================================
# CMake Finders
#================================================
if(IBEX_STANDALONE_BUILD)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
else()
    set(_my_cmake_module_path "${CMAKE_CURRENT_LIST_DIR}/cmake")
    set(CMAKE_MODULE_PATH "${_my_cmake_module_path};${CMAKE_MODULE_PATH}" CACHE STRING "CMake module path" FORCE)
endif()

#================================================
# Add Library
#================================================
add_library("${PROJECT_NAME}" STATIC
    src/ibex/ibex.hpp
    src/ibex/ibex.cpp
)
include_directories (${INCLUDE_DIRS})

#=======================
# Add command line tool
#=======================
if(IBEX_STANDALONE_BUILD)
    add_executable(ibex_cli ibex-cli.cpp)
    target_link_libraries(ibex_cli PRIVATE "${PROJECT_NAME}")
endif()

#=========================
# Define what to include
#=========================
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src>
)

#=========================
# Testing
#=========================
set(IBEX_BUILD_UNIT_TESTS true CACHE BOOL "Whether to build the unit tests.")
if (IBEX_STANDALONE_BUILD AND IBEX_BUILD_UNIT_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    add_subdirectory(tests)
endif()
