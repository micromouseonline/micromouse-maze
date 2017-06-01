cmake_minimum_required(VERSION 2.8)

set(CMAKE_LEGACY_CYGWIN_WIN32 0)
#set(CMAKE_CXX_FLAGS " -std=gnu++0x")
#add_definitions(-std=gnu++0x)


project(maze)

set(HEADER_FILES
        list.h
        maze.h
        oldmaze.h
        mazedata.h
        mazeflooder.h
        mazepathfinder.h
        mazeprinter.h
        mazereader.h
        mazesearcher.h
        priorityqueue.h
        mazeconstants.h
        MazeFiler.h
        Queue.h)

set (SOURCE_FILES
        list.cpp
        maze.cpp
        oldmaze.cpp
        mazedata.cpp
        mazeflooder.cpp
        mazepathfinder.cpp
        mazeprinter.cpp
        mazereader.cpp
        mazesearcher.cpp
        priorityqueue.cpp
        MazeFiler.cpp
        )

add_library(maze
        STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        FloodInfo.cpp FloodInfo.h)