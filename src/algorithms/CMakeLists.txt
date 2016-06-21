cmake_minimum_required (VERSION 2.6)
cmake_policy(SET CMP0003 NEW)

# Add quaternion to the library list
set (QUATERNION_LIBS "quaternion" ${QUATERNION_LIBS})

# add the subfolders to the search path for include files
# (basically this will allow files in src/base to be included
# without a relative path (e.g. #include ../base/Quaternion.h) )
include_directories ("${PROJECT_BINARY_DIR}/src/base")
include_directories ("${PROJECT_SOURCE_DIR}/src/base")

set (QUATERNION_SOURCES
	main.cpp
)

add_executable(rotations ${QUATERNION_SOURCES})

# Link all libs to the executable
target_link_libraries(rotations "${QUATERNION_LIBS}")


install(FILES ${QUATERNION_HEADERS} DESTINATION include/quaternion)
install(TARGETS rotations DESTINATION bin)
