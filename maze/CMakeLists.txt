cmake_minimum_required(VERSION 2.8)

set(CMAKE_LEGACY_CYGWIN_WIN32 0)
#set(CMAKE_CXX_FLAGS " -std=gnu++0x")
#add_definitions(-std=gnu++0x)


project(maze)

set(HEADER_FILES
        list.h
        maze.h
        mazeconstants.h
        oldmaze.h
        mazedata.h
        mazepathfinder.h
        mazeprinter.h
        mazesearcher.h
        priorityqueue.h
        mazeconstants.h
        queue.h
        floodinfo.h
        )

set (SOURCE_FILES
        list.cpp
        maze.cpp
        oldmaze.cpp
        mazedata.cpp
        mazepathfinder.cpp
        mazeprinter.cpp
        mazesearcher.cpp
        )

add_library(maze
        STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )