cmake_minimum_required (VERSION 2.6) # Define minimum CMake version
cmake_policy(SET CMP0003 NEW) 		 # Set CMake policy
project (Quaternion CXX) 			 # Also sets variables such as PROJECT_BINARY_DIR

# Set version number
set (Quaternion_VERSION_MAJOR 1)
set (Quaternion_VERSION_MINOR 0)

# Don't install in /usr/local/
set (QUATERNION_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install" CACHE PATH 
    "Dir. where Quaternion will be installed. Defaults to current dir.")
set(CMAKE_INSTALL_PREFIX ${QUATERNION_INSTALL_PREFIX} CACHE INTERNAL 
    "Install path prefix, prepended onto install directories.")

# Set C++ flags depending on compiler
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  message("-- Using g++ compiler")
  set (CMAKE_CXX_FLAGS "-O3 -std=c++14 -fopenmp ${CMAKE_CXX_FLAGS}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")  
  message("-- Using CLang compiler")
  set (CMAKE_CXX_FLAGS "-O3 -std=c++14 -fopenmp=libiomp5 ${CMAKE_CXX_FLAGS}")
endif ()

# add the binary tree to the search path for include files
include_directories("${PROJECT_BINARY_DIR}")

# Add source directories
include_directories ("${PROJECT_SOURCE_DIR}/src")
add_subdirectory (src/base)
add_subdirectory (src/algorithms)

#include_directories ("${PROJECT_SOURCE_DIR}/src/base")
