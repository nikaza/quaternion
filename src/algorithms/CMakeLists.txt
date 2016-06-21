cmake_minimum_required (VERSION 2.6)

# Add quaternion library to the library list
set (QUATERNION_LIBS "quaternion" ${QUATERNION_LIBS})

# add the subfolders to the search path for include files
# (basically this will allow files in src/base to be included
# without a relative path (e.g. #include ../base/Quaternion.h) )
include_directories ("${PROJECT_BINARY_DIR}/src/base")
include_directories ("${PROJECT_SOURCE_DIR}/src/base")

# Define the project files in this folder which we want to include
# in this build. We can have many versions of this for different 
# executables
set (QUATERNION_SOURCES
	main.cpp
)

# Add the executable
add_executable(rotations ${QUATERNION_SOURCES})

# Link all QUATERNION_LIBS to the executable
target_link_libraries(rotations "${QUATERNION_LIBS}")

# Configure install settings (puts "rotations" in "bin")
install(TARGETS rotations DESTINATION bin)
