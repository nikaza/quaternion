#cmake_policy(SET CMP0003 NEW)
cmake_minimum_required (VERSION 2.6)

# add the binary tree to the search path for include files
#include_directories ("${PROJECT_BINARY_DIR}/src/base")
#include_directories ("${PROJECT_SOURCE_DIR}/src/base")
set (QUATERNION_SOURCES
	Quaternion.cpp
)

set (QUATERNION_HEADERS
	Quaternion.h
)

add_library(quaternion ${QUATERNION_SOURCES})

#install(TARGETS quaternion
#        ARCHIVE
#        DESTINATION lib)

message(STATUS ${MSG_HEAD} "ALL_EXEC_LIBS =  ${ALL_EXEC_LIBS}")

if (BUILD_SHARED_LIBS)
  install(TARGETS quaternion
          LIBRARY DESTINATION lib)
else (BUILD_SHARED_LIBS)
  install(TARGETS quaternion
          ARCHIVE DESTINATION lib)
endif (BUILD_SHARED_LIBS)

install(FILES ${QUATERNION_HEADERS} DESTINATION include/quaternion)
