cmake_minimum_required(VERSION 2.8)

set(CMAKE_LEGACY_CYGWIN_WIN32 0)
#set(CMAKE_CXX_FLAGS " -std=gnu++0x")
add_definitions(-std=gnu++0x)


project(libmaze)

set(HEADER_FILES
        list.h
        maze.h
        mazeflooder.h
        mazepathfinder.h
        mazeprinter.h
        mazereader.h
        mazesearcher.h)

set (SOURCE_FILES
        list.c
        maze.c
        mazeflooder.c
        mazepathfinder.c
        mazeprinter.c
        mazereader.c
        mazesearcher.c
        )

add_library(libmaze
        STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES})