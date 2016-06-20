cmake_minimum_required(VERSION 2.8)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_CXX_FLAGS " -std=gnu++0x")

# where to look for includes
include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR})

add_executable(runTestSuite
        testMaze.cpp
        testList.cpp
        testLocation.cpp
        testCosts.cpp
        testDirection.cpp
        testFlood.cpp
        testMazePrinter.cpp
        testMazeReader.cpp
        testModifiedFlood.cpp
        testPathFinder.cpp
        testSearcher.cpp
        testWalls.cpp
        )

target_link_libraries(
        runTestSuite
        gtest
        gtest_main)
target_link_libraries(
        runTestSuite
        libmaze)
