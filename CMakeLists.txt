cmake_minimum_required (VERSION 2.6) # Define minimum CMake version
cmake_policy(SET CMP0003 NEW)        # Set CMake policy
project (Quaternion CXX)             # Also sets variables such as PROJECT_BINARY_DIR and PROJECT_SOURCE_DIR

# Set version number
set (Quaternion_VERSION_MAJOR 1)
set (Quaternion_VERSION_MINOR 0)

# Get OS information. The project currently only builds on Linux
if (CMAKE_SYSTEM_NAME MATCHES "Windows")
	message(FATAL_ERROR "Project requires Linux OS")
endif()
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	message("-- Detected Linux OS, proceeding with build")
endif()

# Option to build shared or static libraries
# ==========================================
OPTION(BUILD_SHARED_LIBS "Build Quaternion with shared libraries." ON)
# On Unix systems, dynamic libraries are searched for in a system-defined 
# list of directories, so we need to set the shared lib install rpath
if (${BUILD_SHARED_LIBS})
     set(CMAKE_INSTALL_RPATH 
        ${CMAKE_INSTALL_RPATH}:${CMAKE_INSTALL_PREFIX}/lib)
endif()
# ==========================================

# Don't install in /usr/local/
set (QUATERNION_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install" CACHE PATH 
    "Dir. where Quaternion will be installed. Defaults to current dir.")
set(CMAKE_INSTALL_PREFIX ${QUATERNION_INSTALL_PREFIX} CACHE INTERNAL 
    "Install path prefix, prepended onto install directories.")

# Set C++ flags depending on compiler, and detect compiler versions
# Currently only supports CLang and gcc
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  message("-- Using g++ compiler")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.9")
    message(FATAL_ERROR "Project requires gcc>=4.9")
  endif()
  set (CMAKE_CXX_FLAGS "-O3 -std=c++14 -fopenmp ${CMAKE_CXX_FLAGS}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")  
  message("-- Using CLang compiler")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.7")
    message(FATAL_ERROR "Project requires clang>=3.7")
  endif()
    #message(FATAL_ERROR "Project currently only builds with gcc due to cppunit not linking properly with CLang")
  set (CMAKE_CXX_FLAGS "-stdlib=libstdc++ -O3 -std=c++14  -fopenmp=libiomp5 ${CMAKE_CXX_FLAGS}")
endif ()

# add the binary tree to the search path for include files
include_directories("${PROJECT_BINARY_DIR}")

# Add source directories and subdirectories
include_directories ("${PROJECT_SOURCE_DIR}/src")
add_subdirectory (src/base)
add_subdirectory (src/algorithms)
add_subdirectory (src/testing)

# End of file
