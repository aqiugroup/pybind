# project sayhi
cmake_policy(SET CMP0048 NEW)
# cmake_policy(SET CMP0127 OLD)
project(sayhi LANGUAGES CXX)
cmake_minimum_required(VERSION 3.4)

enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# for configure_package_config_file，主要是为了打包自己的package
include(CMakePackageConfigHelpers)

#######################################
# 1 options
#######################################
# default build type release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel)
endif()

# enable optional dependencies
# use DEBUG
option(SAYHI_WITH_DEBUG "Enable/Disable DEBUG" ON)
# 假设不清理编译空间的话，可以用下面的命令调试
# set(SAYHI_WITH_DEBUG ON CACHE BOOL "Enable/Disable DEBUG" FORCE)

# python python wrapper
# option不能在CMakeLists.txt中修改，只有第一次生效；相反可以通过命令行设置
# cmake.. -DSAYHI_BUILD_PYTHON_PACKAGE=ON
option(SAYHI_BUILD_PYTHON_PACKAGE "Build wrapper for Python package" OFF)
# 假设不清理编译空间的话，可以用下面的命令调试
# set(SAYHI_BUILD_PYTHON_PACKAGE ON CACHE BOOL "Build wrapper for Python package" FORCE)

# shared or static lib
# option不能在CMakeLists.txt中修改，只有第一次生效；相反可以通过命令行设置
# cmake.. -DSAYHI_BUILD_SHARED_LIB=ON
option(SAYHI_BUILD_SHARED_LIB "Build shared lib if ON, static lib if OFF" ON)
# 假设不清理编译空间的话，可以用下面的命令调试
# set(SAYHI_BUILD_SHARED_LIB ON CACHE BOOL "Build shared lib if ON, static lib if OFF" FORCE)


#######################################
# 2 configuration conflict
#######################################

# python wrapper cannot be compiled with static lib, since static lib is compiled without -fPIC
if(SAYHI_BUILD_PYTHON_PACKAGE AND NOT SAYHI_BUILD_SHARED_LIB)
  message(FATAL_ERROR "Python wrapper cannot be compiled with static lib" )
endif()

#######################################
# 3 default compiler flags
#######################################

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

#######################################
# 4 dependencies
#######################################

# libraries linked to
set(SAYHI_ADDITIONAL_LIBRARIES)

# mandatory dependency: Eigen3
message(STATUS "Search Dependency: Eigen3")
find_package(Eigen3 REQUIRED 3.3.0)
include_directories(AFTER ${EIGEN3_INCLUDE_DIR})

# --------------------------------------
# optional dependency: DEBUG
if(SAYHI_WITH_DEBUG)
    set(SAYHI_USE_DEBUG 1) # this will go into config.h
else()
    set(SAYHI_USE_DEBUG 0) # this will go into config.h
endif()

# ######################################
# 5 code
# ######################################
# source code list
set(SAYHI_SRCS)

# Generate and install config and dllexport files : config.h.in 主要是为了在cpp等源文件中使用宏开关
configure_file("${PROJECT_NAME}/config.h.in" "${PROJECT_NAME}/config.h")
list(APPEND SAYHI_SRCS "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/config.h")
include_directories(BEFORE ${PROJECT_BINARY_DIR}) # So we can include generated config header files
install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/config.h" DESTINATION "include/${PROJECT_NAME}")

# add current path as include dir
# search local before seach sys path
include_directories(BEFORE ${PROJECT_SOURCE_DIR})

# source code ： 核心代码
add_subdirectory(sayhi)

# unit tests, TODO: chiu，单元测试
# add_subdirectory(tests)

# C++ examples ： 范例
add_subdirectory(examples/cpp)

#######################################
# 6 python module
#######################################

if(SAYHI_BUILD_PYTHON_PACKAGE)

  # clone git submodule
  find_package(Git QUIET)
  if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    message(STATUS "git submodule update: pybind11")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
      message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
  endif()

  # python wrapper compile and install
  add_subdirectory(python)
endif()

#######################################
# 7 summary
#######################################

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

# python
message(STATUS " ")
if(SAYHI_BUILD_PYTHON_PACKAGE)
  message(STATUS "  Python package              Yes")
  message(STATUS "  Python version              ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}")
  message(STATUS "  Python executable           ${PYTHON_EXECUTABLE}")
else()
  message(STATUS "  Python package              No")
endif()
