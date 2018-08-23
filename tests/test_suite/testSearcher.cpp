/************************************************************************
*
* Copyright (C) 2017 by Peter Harrison. www.micromouseonline.com
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without l> imitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
************************************************************************/



#include "gtest/gtest.h"

#include "mazeprinter.h"
#include "mazesearcher.h"
#include "mazedata.h"
#include "maze.h"

class SearcherTest : public ::testing::Test {

  /* This gets run before each test */
  virtual void SetUp() {
    maze = new Maze(16);
    maze->copyMazeFromFileData(japan2007ef, 256);
    searcher = new MazeSearcher;
    searcher->setRealMaze(maze);
    searcher->setVerbose(false);
  }

  virtual void TearDown() {
    delete searcher;
    delete maze;
  }

protected:
  MazeSearcher *searcher;
  Maze *maze;
};

TEST_F(SearcherTest, Constructor) {
  EXPECT_EQ(0, searcher->location());
  EXPECT_EQ(NORTH, searcher->heading());
  EXPECT_NE(nullptr, searcher->realMaze());
  searcher->map()->flood(0x77);
  EXPECT_EQ(14, searcher->map()->cost(0x00));
}

TEST_F(SearcherTest, MouseSetPosition_PositionAsSet) {
  searcher->setLocation(0x99);
  EXPECT_EQ(0x99, searcher->location());
}

TEST_F(SearcherTest, MouseSetHeading_HeadingAsSet) {
  searcher->setHeading(EAST);
  EXPECT_EQ(EAST, searcher->heading());
}

TEST_F(SearcherTest, moveWithMaze_ChangeLocationOnly) {
  searcher->move();
  EXPECT_EQ(0x01, searcher->location());
  EXPECT_EQ(NORTH, searcher->heading());
}

TEST_F(SearcherTest, Turning_ChangeHeadingOnly) {
  searcher->setLocation(0x44);
  EXPECT_EQ(NORTH, searcher->heading());
  searcher->turnRight();
  EXPECT_EQ(EAST, searcher->heading());
  searcher->turnRight();
  EXPECT_EQ(SOUTH, searcher->heading());
  searcher->turnRight();
  EXPECT_EQ(WEST, searcher->heading());
  searcher->turnRight();
  EXPECT_EQ(NORTH, searcher->heading());

  searcher->turnLeft();
  EXPECT_EQ(WEST, searcher->heading());
  searcher->turnLeft();
  EXPECT_EQ(SOUTH, searcher->heading());
  searcher->turnLeft();
  EXPECT_EQ(EAST, searcher->heading());
  searcher->turnLeft();
  EXPECT_EQ(NORTH, searcher->heading());

  searcher->turnAround();
  EXPECT_EQ(SOUTH, searcher->heading());

  EXPECT_EQ(0x44, searcher->location());
}

TEST_F(SearcherTest, followLeftWall) {
  searcher->setMapFromFileData(emptyMaze, 256);
  searcher->setHeading(NORTH);
  searcher->setLocation(0x00);
  EXPECT_EQ(NORTH, searcher->followLeftWall());
  searcher->setLocation(0x01);
  EXPECT_EQ(NORTH, searcher->followLeftWall());
  searcher->setLocation(0x11);
  EXPECT_EQ(WEST, searcher->followLeftWall());

  searcher->setLocation(0x10);
  searcher->setHeading(EAST);
  EXPECT_EQ(NORTH, searcher->followLeftWall());
  searcher->setHeading(SOUTH);
  EXPECT_EQ(EAST, searcher->followLeftWall());
  searcher->setHeading(WEST);
  EXPECT_EQ(NORTH, searcher->followLeftWall());

}

TEST_F(SearcherTest, followRightWall) {
  searcher->setMapFromFileData(emptyMaze, 256);
  searcher->setHeading(NORTH);
  searcher->setLocation(0x00);
  EXPECT_EQ(NORTH, searcher->followRightWall());
  searcher->setLocation(0x01);
  EXPECT_EQ(EAST, searcher->followRightWall());
  searcher->setLocation(0x11);
  EXPECT_EQ(EAST, searcher->followRightWall());

  searcher->setLocation(0x11);
  searcher->setHeading(EAST);
  EXPECT_EQ(SOUTH, searcher->followRightWall());
  searcher->setHeading(SOUTH);
  EXPECT_EQ(WEST, searcher->followRightWall());
  searcher->setHeading(WEST);
  EXPECT_EQ(NORTH, searcher->followRightWall());
}

TEST_F(SearcherTest, chooseRanndomExit) {
  searcher->setMapFromFileData(emptyMaze, 256);
  searcher->setHeading(NORTH);
  searcher->setLocation(0x11);
  EXPECT_EQ(WEST, searcher->followAlternateWall());
  EXPECT_EQ(EAST, searcher->followAlternateWall());
  EXPECT_EQ(WEST, searcher->followAlternateWall());

  searcher->setHeading(NORTH);
  searcher->setLocation(0x00);
  EXPECT_EQ(NORTH, searcher->followAlternateWall());
  EXPECT_EQ(NORTH, searcher->followAlternateWall());
}

TEST_F(SearcherTest, moveWithMaze_smallCircuitReturnToStart) {
  searcher->setLocation(0x39);
  searcher->move();
  searcher->setHeading(EAST);
  searcher->move();
  searcher->setHeading(SOUTH);
  searcher->move();
  searcher->setHeading(WEST);
  searcher->move();
  searcher->setHeading(NORTH);
  EXPECT_EQ(0x39, searcher->location());
  EXPECT_EQ(NORTH, searcher->heading());
}

/*
 * Tests whether the mouse can successfully follow a correctly setup
 * direction array and stop at the appropriate mLocation
 */
TEST_F(SearcherTest, MouseRunTo_EmptyMaze_StartToGoal_MouseAtGoal) {
  searcher->setMapFromFileData(emptyMaze, 256);
  int steps = searcher->runTo(0x77);
  EXPECT_EQ(14, steps);
  EXPECT_EQ(0x77, searcher->location()) << "{" << searcher->location() << ", " << +searcher->heading() << "}";
}

/*
 * Tests whether the mouse can successfully follow a correctly setup
 * direction array and stop at the appropriate mLocation
 */
TEST_F(SearcherTest, MouseRunTo_EmptyMaze_ToGoalFromAnywhere) {
  searcher->setMapFromFileData(japan2007ef, 256);
  maze->copyMazeFromFileData(japan2007ef, 256);
  maze->flood(0x77);
  int steps = searcher->runTo(0x77);
  EXPECT_EQ(72, steps);
  for (uint16_t loc = 0; loc < maze->numCells(); loc++) {
    searcher->setLocation(loc);
    searcher->setHeading(WEST);
    searcher->runTo(0x77);
    EXPECT_EQ(0x77, searcher->location()) << "{" << searcher->location() << ", " << +searcher->heading() << "}";
  }
}

/*
 * Tests whether the mouse can successfully follow a correctly setup
 * direction array and stop at the appropriate mLocation
 */
TEST_F(SearcherTest, MouseRunTo_EmptyMaze_ToStartFromAnywhere) {
  searcher->setMapFromFileData(japan2007ef, 256);
  maze->copyMazeFromFileData(japan2007ef, 256);
  maze->flood(maze->home());
  searcher->setLocation(0x01);
  int steps = searcher->runTo(maze->home());
  EXPECT_EQ(1, steps);
  for (uint16_t loc = 1; loc < maze->numCells(); loc++) {
    searcher->setLocation(loc);
    searcher->setHeading(WEST);
    int steps = searcher->runTo(maze->home());
    EXPECT_EQ(maze->home(), searcher->location()) << "{" << searcher->location() << ", " << +searcher->heading() << "}";
    EXPECT_GT(steps, 0);
  }
}

/*
 * Tests mouse getting lost in a cell with invalid direction
 * Taiwan2015 libMaze has closed in cells at 0x5C and 0x5D
 */
TEST_F(SearcherTest, MouseRunTo_RunToGoal_StartClosedIn_Error) {
  searcher->setMapFromFileData(taiwan2015, 256);
  searcher->setLocation(0x5D);
  int steps = searcher->runTo(maze->goal());
  EXPECT_EQ(int(MazeSearcher::E_NO_ROUTE), steps);
}

/*
 * Tests mouse getting lost in a cell with invalid direction
 * Taiwan2015 libMaze has closed in cells at 0x5C and 0x5D
 */
TEST_F(SearcherTest, MouseRunTo_RunToGoal_TargetClosedIn_Error) {
  searcher->setMapFromFileData(taiwan2015, 256);
  int steps = searcher->runTo(0x5C);
  EXPECT_EQ(int(MazeSearcher::E_NO_ROUTE), steps);
}



/*
 * Tests mouse getting lost because path is too long
 * Simulate by setting target outside libMaze
 */
//TEST_F (SearcherTest, MouseRunTo_RunToGoal_TargetTooFar_Error) {
//  barney->setMazeWalls(taiwan2015, 256);
//  int steps = barney->runTo(0x200);
//  EXPECT_EQ(int(MazeSearcher::E_ROUTE_TOO_LONG),steps);
//}

/*
 * Tests mouse search
 */
TEST_F(SearcherTest, MouseSearchTo_EmptyMaze_Success) {
  Maze *testMaze = new Maze(16);
  testMaze->setWall(0x07, EAST);
  testMaze->setFloodType(Maze::MANHATTAN_FLOOD);
  searcher->setRealMaze(testMaze);

  int steps = searcher->searchTo(0x77);
  EXPECT_EQ(16, steps);
}


/*
 * verbose mode prints out the libMaze after each step.
 */
TEST_F(SearcherTest, MouseRunTo_SearchToTarget_VerboseMode) {
  Maze *testMaze = new Maze(16);
  searcher->setRealMaze(testMaze);
  searcher->map()->setFloodType(Maze::MANHATTAN_FLOOD);
  int steps = searcher->searchTo(0x7);
  EXPECT_EQ(7, steps);
}


/*
 *
 */
TEST_F(SearcherTest, MouseRunTo_SearchToTarget_ManhattanFlood) {
  maze->copyMazeFromFileData(japan2007ef, 256);
  searcher->setRealMaze(maze);
  searcher->map()->setFloodType(Maze::MANHATTAN_FLOOD);
  int steps = searcher->searchTo(0x77);
  EXPECT_EQ(130, steps);
  //  MazePrinter::printVisitedDirs(barney->libMaze());
}


/*
 *
 */
TEST_F(SearcherTest, MouseSearchToTarget_RunLengthFlood) {
  maze->copyMazeFromFileData(japan2007ef, 256);
  searcher->setRealMaze(maze);
  searcher->setSearchMethod(MazeSearcher::SEARCH_NORMAL);
  searcher->map()->setFloodType(Maze::RUNLENGTH_FLOOD);
  int steps = searcher->searchTo(0x77);
  EXPECT_EQ(142, steps);

}


/*
 *
 */
TEST_F(SearcherTest, MouseSearchToTarget_LeftWall_Fail) {
  maze->copyMazeFromFileData(emptyMaze, 256);
  searcher->setRealMaze(maze);
  searcher->setSearchMethod(MazeSearcher::SEARCH_LEFT_WALL);
  int steps = searcher->searchTo(0x77);
  EXPECT_EQ(MazeSearcher::E_ROUTE_TOO_LONG, steps);
}

TEST_F(SearcherTest, MouseSearchToTarget_RightWall_Fail) {
  maze->copyMazeFromFileData(emptyMaze, 256);
  searcher->setRealMaze(maze);
  searcher->setSearchMethod(MazeSearcher::SEARCH_RIGHT_WALL);
  int steps = searcher->searchTo(0x77);
  EXPECT_EQ(MazeSearcher::E_ROUTE_TOO_LONG, steps);
}

/*
 *
 */
TEST_F(SearcherTest, MouseSearchToTarget_LeftWall_Succeed) {
  maze->copyMazeFromFileData(japan2007ef, 256);
  searcher->setRealMaze(maze);
  searcher->setSearchMethod(MazeSearcher::SEARCH_LEFT_WALL);
  int steps = searcher->searchTo(0x77);
  EXPECT_EQ(84, steps);
}

TEST_F(SearcherTest, MouseSearchToTarget_RightWall_Succeed) {
  maze->copyMazeFromFileData(japan2007ef, 256);
  searcher->setRealMaze(maze);
  searcher->setSearchMethod(MazeSearcher::SEARCH_RIGHT_WALL);
  int steps = searcher->searchTo(0x77);
  EXPECT_EQ(92, steps);
}

TEST_F(SearcherTest, MouseSearchToTarget_AlternateWall_Fail) {
  maze->copyMazeFromFileData(japan2007ef, 256);
  searcher->setRealMaze(maze);
  searcher->setSearchMethod(MazeSearcher::SEARCH_ALTERNATE);
  int steps = searcher->searchTo(0x77);
  EXPECT_EQ(MazeSearcher::E_ROUTE_TOO_LONG, steps);
}

TEST_F(SearcherTest, MouseSearchToTarget_AlternateWall_Succeed) {
  maze->copyMazeFromFileData(japan2007ef, 256);
  searcher->setRealMaze(maze);
  searcher->setSearchMethod(MazeSearcher::SEARCH_ALTERNATE);
  int steps = searcher->searchTo(0x08);
  EXPECT_EQ(14, steps);
}

/*
 *
 */
TEST_F(SearcherTest, MouseRunTo_SearchOutAndIn_RunLengthFlood) {
  searcher->map()->setFloodType(Maze::RUNLENGTH_FLOOD);
  int steps = 0;
  steps += searcher->searchTo(0x77);
  steps += searcher->searchTo(0x00);
  EXPECT_EQ(228, steps) << "The solution is not always correct. This is not right";
  steps = 0;
  steps += searcher->searchTo(0x77);
  steps += searcher->searchTo(0x00);
  EXPECT_EQ(150, steps) << "The solution is not always correct. This is not right";
  steps = searcher->searchTo(0x77);
  EXPECT_EQ(72, steps) << "The solution is not always correct. This is not right";
  steps = searcher->searchTo(0x00);
  EXPECT_EQ(72, steps) << "The solution is not always correct. This is not right";
}


/*
 *
 */
TEST_F(SearcherTest, MouseRunTo_SearchOutAndIn_ManhattanFlood) {
  searcher->map()->setFloodType(Maze::MANHATTAN_FLOOD);
  int steps = 0;
  steps += searcher->searchTo(0x77);
  steps += searcher->searchTo(0x00);
  EXPECT_EQ(208, steps) << "The solution is not always correct. This is not right";
  steps = 0;
  steps += searcher->searchTo(0x77);
  steps += searcher->searchTo(0x00);
  EXPECT_EQ(164, steps) << "The solution is not always correct. This is not right";
  steps = searcher->searchTo(0x77);
  EXPECT_EQ(72, steps) << "The solution is not always correct. This is not right";
  steps = searcher->searchTo(0x00);
  EXPECT_EQ(72, steps) << "The solution is not always correct. This is not right";
}




