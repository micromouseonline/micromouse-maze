cmake_minimum_required(VERSION 3.7)
project(micromouse-maze)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

#set(CMAKE_CXX_FLAGS " -std=gnu++0x")
#add_definitions(-std=gnu++0x)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 11)

set(COMMON_FLAGS " -Wall -Wextra ")
set(HEADER_COMMENTS 1)

set(CMAKE_C_FLAGS "${COMMON_FLAGS} ")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} ")
set(SOURCE_FILES
        main.cpp
        )
add_executable(libmaze_run
        ${SOURCE_FILES}
        )
add_executable(libmaze_runX
        ${SOURCE_FILES}
        )

# places to look for include files
include_directories(
        maze
        oldmaze
)

# adds in the CMakeLists files from these directories
add_subdirectory(maze)
add_subdirectory(tests)

# list the libraries needed by the target named
target_link_libraries(libmaze_run maze)

# before building, run astyle over all the sources to be sure
# the formatting is always consistent
add_custom_command(TARGET libmaze_run PRE_BUILD
        COMMENT "Pre build: reformat with astyle\n"
        COMMAND astyle -nrQ \"${PROJECT_SOURCE_DIR}/maze/*.cpp\"
        COMMAND astyle -nrQ \"${PROJECT_SOURCE_DIR}/maze/*.h\"
        )