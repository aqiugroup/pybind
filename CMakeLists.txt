# project sayhi
project(sayhi LANGUAGES CXX)
cmake_minimum_required(VERSION 3.4)
enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# for configure_package_config_file
include(CMakePackageConfigHelpers)


# --------------------------------------
# options

# default build type release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel)
endif()

# python python wrapper
option(SAYHI_BUILD_PYTHON_PACKAGE "Build wrapper for Python package" OFF)

# shared or static lib
option(SAYHI_BUILD_SHARED_LIB "Build shared lib if ON, static lib if OFF" ON)


# --------------------------------------
# configuration conflict

# python wrapper cannot be compiled with static lib, since static lib is compiled without -fPIC
if(SAYHI_BUILD_PYTHON_PACKAGE AND NOT SAYHI_BUILD_SHARED_LIB)
  message(FATAL_ERROR "Python wrapper cannot be compiled with static lib" )
endif()

# --------------------------------------
# default compiler flags

# GNU gcc
if(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wextra")
  
# Clang
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wextra")

# Visual stdio
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # use math macro
  add_definitions("-D _USE_MATH_DEFINES")
endif()


# --------------------------------------
# code
# include_directories(BEFORE ${PROJECT_BINARY_DIR}) # So we can include generated config header files

# add current path as include dir
# search local before seach sys path
include_directories(BEFORE ${PROJECT_SOURCE_DIR})

# source code
add_subdirectory(sayhi)

# unit tests, TODO : chiu
# add_subdirectory(tests)

# C++ examples
add_subdirectory(examples/cpp)


# --------------------------------------
# summary

message(STATUS "===============================================================")
message(STATUS "                Configurations for sayhi                    ")

# lib
message(STATUS " ")
if(SAYHI_BUILD_SHARED_LIB)
  message(STATUS "  Library type                Shared")
else()
  message(STATUS "  Library type                Static")
endif()
message(STATUS "  Install path                ${CMAKE_INSTALL_PREFIX}")

# complier
message(STATUS " ")
message(STATUS "  Compiler type               ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  Compiler version            ${CMAKE_CXX_COMPILER_VERSION}")

