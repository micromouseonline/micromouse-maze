cmake_minimum_required(VERSION 2.8)

set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_CXX_FLAGS " -std=gnu++0x")
add_definitions(-std=gnu++0x)


project(maze)

set(HEADER_FILES
        maze.h
        mazeconstants.h
        mazedata.h
        mazepathfinder.h
        mazeprinter.h
        mazesearcher.h
        priorityqueue.h
        mazeconstants.h
        mazefiler.h

        floodinfo.h

        )

set (SOURCE_FILES
        maze.cpp
        mazedata.cpp
        mazepathfinder.cpp
        mazeprinter.cpp
        mazesearcher.cpp
        mazefiler.cpp

        )

add_library(maze
        STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )