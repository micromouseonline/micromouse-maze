cmake_minimum_required(VERSION 2.8)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_CXX_FLAGS " -std=gnu++0x")

# where to look for includes
include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR})

add_executable(runTestSuite
        MD-50-Maze-Tests.cpp
        testPriorityQueue.cpp
        MD-03-Costs.cpp
        MD-04-Directions.cpp
        MF-20-Manhattan.cpp
        testWeightedFlood.cpp
        MF-50-Runlength.cpp
        testDirectionFlood.cpp
        testMazePrinter.cpp
        testMazeFiler.cpp
        PF-10-Pathfinder.cpp
        testSearcher.cpp
        MF-00-FloodInfo.cpp
        path_test_data.cpp
        path_test_data.h
        testPathReverse.cpp
        MazeTestHalfSize.cpp
        MD-10-Maze-Goal.cpp
        MD-02-Walls.cpp
        )

target_link_libraries(
        runTestSuite
        gtest
        gtest_main
        maze
        )

# before building, run astyle over all the sources to be sure
# the formatting is always consistent
add_custom_command(TARGET runTestSuite PRE_BUILD
        COMMENT "Pre build: reformat with astyle\n"
        COMMAND astyle -nQv --project=.astylerc  \"${PROJECT_SOURCE_DIR}/../libMaze/*.cpp\"
        COMMAND astyle -nQv --project=.astylerc  \"${PROJECT_SOURCE_DIR}/../libMaze/*.h\"
        COMMAND astyle -nQv --project=.astylerc  \"${PROJECT_SOURCE_DIR}/test_suite/*.cpp\"
        COMMAND astyle -nQv --project=.astylerc  \"${PROJECT_SOURCE_DIR}/test_suite/*.h\"
        )