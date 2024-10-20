cmake_minimum_required(VERSION 3.10)

# Project name
project(MySFMLProject)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set SFML directory paths (only necessary if SFML is not installed globally)
set(SFML_DIR "C:/Users/24namankwah/Desktop/SFML/SFML-2.6.1/lib/cmake/SFML")

# Find SFML package and components
find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

# Include the SFML headers
include_directories("C:/Users/24namankwah/Desktop/SFML/SFML-2.6.1/include")

# Specify the source files
set(SOURCE_FILES 
    src/main.cpp 
)

# Add the executable
add_executable(my_sfml_program ${SOURCE_FILES})

# Set the output directory for the executable
set_target_properties(my_sfml_program PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/output"
)

# Link SFML libraries using the SFML:: targets provided by find_package
target_link_libraries(my_sfml_program PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

# Add a custom target to run the executable immediately after the build
add_custom_target(run
    COMMAND my_sfml_program
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/output"
    DEPENDS my_sfml_program
    COMMENT "Building and running my_sfml_program..."
)
