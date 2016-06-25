cmake_minimum_required (VERSION 2.6)

# Set up includes - we want access to src/base for the quaternion library
include_directories ("${PROJECT_BINARY_DIR}/src/base")
include_directories ("${PROJECT_SOURCE_DIR}/src/base")

# Define folder source code headers and implementation files
# Note: if they are not in here, they will not compile!
set (QUATERNION_SOURCES
	unitTester.cpp
)
# End of folder *.h and *.cpp files

# Add the init testing executable
add_executable(unitTester ${QUATERNION_SOURCES})
target_link_libraries(unitTester quaternion)

# Define install paths - this will go to bin/
install(TARGETS unitTester DESTINATION bin)

# Define install includes (there are none in this case, as we don't have any headers)
#install(FILES ${QUATERNION_HEADERS} DESTINATION include/quaternionUT)
