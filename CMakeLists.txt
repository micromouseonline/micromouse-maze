cmake_minimum_required(VERSION 2.8)
project(maze)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

#add_definitions(-std=gnu++0x)

set(SOURCE_FILES main.cpp maze/MazeFiler.cpp maze/MazeFiler.h)
add_executable(libmaze_run ${SOURCE_FILES} maze/MazeFiler.cpp maze/MazeFiler.h)

# places to look for include files
include_directories(maze)

# adds in the CMakeLists files from these directories
add_subdirectory(maze)
add_subdirectory(tests)

# list the libraries needed by the target named
target_link_libraries(libmaze_run maze)
