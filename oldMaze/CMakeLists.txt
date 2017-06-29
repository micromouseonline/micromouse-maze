cmake_minimum_required(VERSION 2.8)

set(CMAKE_LEGACY_CYGWIN_WIN32 0)
#set(CMAKE_CXX_FLAGS " -std=gnu++0x")
#add_definitions(-std=gnu++0x)


project(oldmaze)

set(HEADER_FILES
        pathfinder.h
        commands.h
        )

set(SOURCE_FILES
        pathfinder.cpp
        )

add_library(oldmaze
        STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )