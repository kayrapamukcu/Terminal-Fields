cmake_minimum_required(VERSION 3.26)
project(TerminalFields LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp")
add_executable(TerminalFields ${SOURCES})
target_link_libraries(TerminalFields sfml-system sfml-window sfml-graphics sfml-audio)
target_compile_features(TerminalFields PRIVATE cxx_std_17)

set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_BUILD_TYPE Release)

if (MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

if (WIN32)
    set_target_properties(TerminalFields PROPERTIES WIN32_EXECUTABLE YES)
endif()
