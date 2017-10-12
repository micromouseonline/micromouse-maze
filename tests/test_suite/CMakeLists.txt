cmake_minimum_required(VERSION 2.8)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_CXX_FLAGS " -std=gnu++0x")

# where to look for includes
include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR})

add_executable(runTestSuite
        testMaze.cpp
        testPriorityQueue.cpp
        testCosts.cpp
        testDirection.cpp
        testFlood.cpp
        testMazePrinter.cpp
        testMazeReader.cpp
        testPathFinder.cpp
        testSearcher.cpp
        testFloodInfo.cpp
        path_test_data.cpp
        path_test_data.h
        )

target_link_libraries(
        runTestSuite
        gtest
        gtest_main
        maze
        )
#target_link_libraries(
#        runTestSuite
#        maze)


# before building, run astyle over all the sources to be sure
# the formatting is always consistent
add_custom_command(TARGET runTestSuite PRE_BUILD
        COMMENT "Pre build: reformat with astyle\n"
        COMMAND astyle -nrQ \"${PROJECT_SOURCE_DIR}/../maze/*.cpp\"
        COMMAND astyle -nrQ \"${PROJECT_SOURCE_DIR}/../maze/*.h\"
        )