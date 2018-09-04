cmake_minimum_required(VERSION 2.8)


project(maze)

set(HEADER_FILES
        maze.h
        mazeconstants.h
        mazedata.h
        mazepathfinder.h
        mazeprinter.h
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
        mazefiler.cpp

        compiler.cpp compiler.h)

add_library(maze
        STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )