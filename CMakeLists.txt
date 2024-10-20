cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

# Fetch SFML
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Fetch the core library
FetchContent_Declare(core
    GIT_REPOSITORY https://github.com/Project-Code-Chess-Engine/core.git
)
FetchContent_MakeAvailable(core)

# Fetch Discord RPC SDK
FetchContent_Declare(discord-rpc
    GIT_REPOSITORY https://github.com/discord/discord-rpc.git
    GIT_TAG master  # Change to a specific release tag if needed
)
FetchContent_MakeAvailable(discord-rpc)

# Copy assets to the binary directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Include directories for your project
include_directories(include)

# Include directories for Discord RPC
include_directories(${discord-rpc_SOURCE_DIR}/include)

# Gather source files
file(GLOB_RECURSE SOURCES "src/main.cpp")

# Create the executable
add_executable(main ${SOURCES})

# Link against SFML libraries
target_link_libraries(main PRIVATE sfml-graphics sfml-audio)

# Link against the core library
target_link_libraries(main PRIVATE core)

# Link against Discord RPC
target_link_libraries(main PRIVATE discord-rpc)

# Set C++ standard
target_compile_features(main PRIVATE cxx_std_17)

# Handle OpenAL DLL copying on Windows
if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
