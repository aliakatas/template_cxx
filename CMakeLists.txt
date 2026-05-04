cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

cmake_policy(SET CMP0077 NEW)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(CompilerSelection)
include(CompilerSettings)

option(BUILD_DEBUG "Build with debug flags" OFF)

if(NOT DEFINED CMAKE_CXX_COMPILER)
    find_preferred_cxx_compiler()
endif()

project(example-project
    VERSION 0.1.0
    DESCRIPTION "Example project to use as template"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    if(BUILD_DEBUG)
        set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
    else()
        set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    if(NOT BUILD_DEBUG)
        message(STATUS "Setting BUILD_DEBUG=ON because CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
        set(BUILD_DEBUG ON CACHE BOOL "Build with debug flags" FORCE)
    endif()
endif()

find_package(Boost 1.70 REQUIRED COMPONENTS program_options)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.cxx")
if(NOT SOURCE_FILES)
    message(FATAL_ERROR "No source files found in ${SOURCE_DIR}")
endif()

configure_file("${INCLUDE_DIR}/appconfig.h.in" "${PROJECT_BINARY_DIR}/include/appconfig.h" @ONLY)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_BINARY_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options)

setup_target_compile_flags(${PROJECT_NAME})
setup_compiler_specific_options(${PROJECT_NAME})

