cmake_minimum_required (VERSION 2.6)

# Set up includes - we want access to src/base for the quaternion library
include_directories ("${PROJECT_BINARY_DIR}/src/base")
include_directories ("${PROJECT_SOURCE_DIR}/src/base")

# Define folder source code headers and implementation files
# Note: if they are not in here, they will not compile!
set (QUATERNION_SOURCES
	unitTester.cpp
	QuaternionOperatorUT.cpp
)
set (QUATERNION_HEADERS
	QuaternionOperatorUT.h
)
# End of folder *.h and *.cpp files

# Add the init testing executable
#add_executable(unitTester EXCLUDE_FROM_ALL ${QUATERNION_SOURCES}) # Set this flag when we're a bit futher along in the project
add_executable(unitTester ${QUATERNION_SOURCES})
target_link_libraries(unitTester cppunit)

# Define install paths - this will go to bin/
install(TARGETS unitTester DESTINATION bin)

# Define install includes
install(FILES ${QUATERNION_HEADERS} DESTINATION include/quaternionUT)
