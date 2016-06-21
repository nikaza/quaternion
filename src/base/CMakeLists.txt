cmake_minimum_required (VERSION 2.6)

# Define folder source code headers and implementation files
# Note: if they are not in here, they will not compile!
set (QUATERNION_SOURCES
	Quaternion.cpp
)
set (QUATERNION_HEADERS
	Quaternion.h
)
# End of folder *.h and *.cpp files

# Add quaternion library to the list
add_library(quaternion ${QUATERNION_SOURCES})

# Print library
message(STATUS ${MSG_HEAD} "ALL_EXEC_LIBS =  ${ALL_EXEC_LIBS}")

# We have different rules for handling the library, depending
# on whether it is static or dynamic (shared)
if (BUILD_SHARED_LIBS)
  install(TARGETS quaternion
          LIBRARY DESTINATION lib)
else (BUILD_SHARED_LIBS)
  install(TARGETS quaternion
          ARCHIVE DESTINATION lib)
endif (BUILD_SHARED_LIBS)

# Define install includes
install(FILES ${QUATERNION_HEADERS} DESTINATION include/quaternion)
