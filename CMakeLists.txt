cmake_minimum_required(VERSION 2.8)
project(LibMaze)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
#add_definitions(-std=c++11)
add_definitions(-std=gnu++0x)

set(SOURCE_FILES main.cpp)

add_executable(libmaze_test ${SOURCE_FILES})

# places to look for include files
include_directories(libmaze)

# adds in the CMakeLists files frmo these directories
add_subdirectory(libmaze)
add_subdirectory(tests)

target_link_libraries(libmaze_test libmaze)
