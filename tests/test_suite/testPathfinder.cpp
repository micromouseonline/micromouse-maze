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



#include <iostream>
#include <mazedata.h>
#include "gtest/gtest.h"
#include "mazeprinter.h"
#include "mazepathfinder.h"
#include "maze.h"
#include "mazedata.h"
#include "commandnames.h"
#include "compiler.h"
#include "path_test_data.h"


class PathFinderTest : public ::testing::Test {

  /* This gets run before each test */
  virtual void SetUp() {
    maze = new Maze(16);
    maze->copyMazeFromFileData(japan2007ef, 256);
    maze->flood(0x77);
    path = new PathFinder();
  }

  virtual void TearDown() {
    delete path;
    delete maze;
  }

protected:
  PathFinder *path;
  Maze *maze;
};

TEST_F(PathFinderTest, constructor) {
  EXPECT_EQ(0, strlen(path->path()));
  EXPECT_EQ(0, path->cellCount());
  EXPECT_EQ(INVALID_DIRECTION, path->startHeading());
  EXPECT_EQ(INVALID_DIRECTION, path->endHeading());
  EXPECT_EQ(0, path->startCell());
  EXPECT_EQ(0, path->endCell());
  EXPECT_FALSE(path->reachesTarget());
}

TEST_F(PathFinderTest, generate_EmptyMaze_ManhattanFlood) {
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(emptyMaze, 256);
  maze->flood(0x77);
  path->generateSafePath(0, 0x77, maze);
  EXPECT_EQ(16, strlen(path->path()));
  EXPECT_STREQ("BFFFFFFFRFFFFFFS", path->path());
  EXPECT_EQ(15, path->cellCount());
  EXPECT_EQ(EAST, path->endHeading());
  EXPECT_EQ(0x77, path->endCell());
  EXPECT_TRUE(path->reachesTarget());
}

TEST_F(PathFinderTest, generate_EmptyMaze_RunLengthFlood) {
  maze->setFloodType(Maze::RUNLENGTH_FLOOD);
  maze->copyMazeFromFileData(emptyMaze, 256);
  maze->flood(0x77);
  path->generateSafePath(0, 0x77, maze);
  EXPECT_EQ(16, strlen(path->path()));
  EXPECT_STREQ("BFRFLRLRLRLRFLFS", path->path());
  EXPECT_EQ(15, path->cellCount());
  EXPECT_EQ(NORTH, path->endHeading());
  EXPECT_EQ(0x77, path->endCell());
  EXPECT_TRUE(path->reachesTarget());
}

TEST_F(PathFinderTest, generate_EmptyMaze_AtDestination) {
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(emptyMaze, 256);
  maze->flood(0x77);
  path->generateSafePath(0x77, 0x77, maze);
  EXPECT_EQ(2, strlen(path->path()));
  EXPECT_STREQ("BS", path->path());
  EXPECT_EQ(NORTH, path->endHeading());
  EXPECT_EQ(0x77, path->endCell());
  EXPECT_TRUE(path->reachesTarget());
}

TEST_F(PathFinderTest, generate_EmptyMaze_TargetOneCellAhead) {
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(emptyMaze, 256);
  maze->flood(0x77);
  path->generateSafePath(0x76, 0x77, maze);
  EXPECT_EQ(3, strlen(path->path()));
  EXPECT_STREQ("BFS", path->path());
  EXPECT_EQ(NORTH, path->endHeading());
  EXPECT_EQ(0x77, path->endCell());
  EXPECT_TRUE(path->reachesTarget());
}

TEST_F(PathFinderTest, generate_EmptyMaze_TargetOneCellBehind) {
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(emptyMaze, 256);
  maze->flood(0x77);
  path->generateSafePath(0x78, 0x77, maze);
  EXPECT_EQ(3, strlen(path->path()));
  EXPECT_STREQ("BFS", path->path());
  EXPECT_EQ(SOUTH, path->endHeading());
  EXPECT_EQ(0x77, path->endCell());
  EXPECT_TRUE(path->reachesTarget());
}

TEST_F(PathFinderTest, generate_NoExitCurrentCell) {
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(emptyMaze, 256);
  maze->setWall(0x00, NORTH);
  maze->flood(0x77);
  path->generateSafePath(0, 0x77, maze);
  EXPECT_EQ(2, strlen(path->path()));
  EXPECT_STREQ("BS", path->path());
  EXPECT_EQ(INVALID_DIRECTION, path->endHeading());
  EXPECT_EQ(0x77, path->endCell());
  EXPECT_FALSE(path->reachesTarget());
}

TEST_F(PathFinderTest, generate_NoRoute) {
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(emptyMaze, 256);
  maze->setWall(0x01, NORTH);
  maze->setWall(0x01, EAST);
  maze->flood(0x77);
  path->generateSafePath(0, 0x77, maze);
  EXPECT_EQ(2, strlen(path->path()));
  EXPECT_STREQ("BS", path->path());
  EXPECT_EQ(INVALID_DIRECTION, path->endHeading());
  EXPECT_EQ(0x77, path->endCell());
  EXPECT_FALSE(path->reachesTarget());
}

TEST_F(PathFinderTest, generate_Japan2007_ManHattan_CorrectPAth) {
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(japan2007ef, 256);
  maze->flood(0x77);
  path->generateSafePath(0, 0x77, maze);
  EXPECT_EQ(74, strlen(path->path()));
  char result[] = "BFFFRLLRRLLRRLLRFFRRFLLFFLRLRFRFFFFFFFFFFFFFFRFFFFFFRLRLLRRLLRRFFRFFFLFFFS";
  EXPECT_STREQ(result, path->path());
  EXPECT_EQ(WEST, path->endHeading());
  EXPECT_EQ(0x77, path->endCell());
  EXPECT_TRUE(path->reachesTarget());
}

TEST_F(PathFinderTest, generate_Japan2007_RunLength_Path) {
  maze->setFloodType(Maze::RUNLENGTH_FLOOD);
  maze->copyMazeFromFileData(japan2007ef, 256);
  maze->flood(0x77);
  path->generateSafePath(0, 0x87, maze);
  EXPECT_EQ(73, strlen(path->path()));
  char result[] = "BFRLRLRLFLRFFLFRFFRRFLLFFLRLRFRFFFFFFFFFFFFFFRFFFFFFRLRLLRRLLRRFFRFFFLFFS";
  EXPECT_STREQ(result, path->path());
  EXPECT_EQ(NORTH, path->startHeading());
  EXPECT_EQ(WEST, path->endHeading());
  EXPECT_EQ(0x00, path->startCell());
  EXPECT_EQ(0x87, path->endCell());
  EXPECT_EQ(72, path->cellCount());
  EXPECT_TRUE(path->reachesTarget());
}


TEST_F(PathFinderTest, generate_EmptyMaze_UnexploredOnPath) {
  maze->setFloodType(Maze::RUNLENGTH_FLOOD);
  maze->resetToEmptyMaze();
  maze->flood(0x77);
  path->generateSafePath(0, 0x77, maze);
  EXPECT_EQ(3, strlen(path->path())) << path->path();
  char result[] = "BFX";
  EXPECT_STREQ(result, path->path());
  EXPECT_FALSE(path->reachesTarget());
  EXPECT_EQ(0x01, path->endCell());
  maze->setVisited(0x01);
  maze->flood(0x77);
  path->generateSafePath(0, 0x77, maze);
  EXPECT_EQ(4, strlen(path->path())) << path->path();
  EXPECT_STREQ("BFRX", path->path());
  EXPECT_FALSE(path->reachesTarget());
  EXPECT_EQ(0x11, path->endCell());
}

TEST_F(PathFinderTest, generate_Japan2007_SimulateSearch) {
  // do a simulated search
  maze->copyMazeFromFileData(japan2007ef, 256);
  for (int i = 1; i < maze->numCells(); i++) {
    maze->clearVisited(i);
  }
  char japanPath[] = "BFRLRLRLFLRFFLFRFFRRFLLFFLRLRFRFFFFFFFFFFFFFFRFFFFFFRLRLLRRLLRRFFRFFFLFFFS";
  int steps = 0;
  while (!path->reachesTarget()) {
    maze->setVisited(path->endCell());
    steps++;
    maze->flood(0x77);
    maze->updateDirections();
    path->generateSafePath(0, 0x77, maze);
  }
  EXPECT_EQ(72, steps);
  EXPECT_EQ(74, strlen(path->path())) << path->path();
  EXPECT_STREQ(japanPath, path->path());
  EXPECT_TRUE(path->reachesTarget());
  EXPECT_EQ(0x77, path->endCell());
  //  MazePrinter::printVisitedDirs(libMaze);
}



// the distances are only meant to be accurate in relation to each other
// rather than as absolutes since they cannot take into account the actual
// turns. Thus, they should only be used to compare paths.
TEST_F(PathFinderTest, SimplePath_Distance) {
  maze->copyMazeFromFileData(emptyMaze, 256);
  maze->flood(0x01);
  path->generateSafePath(0x00, 0x01, maze);
  EXPECT_EQ(180, path->distance());
  maze->flood(0x0A);
  path->generateSafePath(0x00, 0x0A, maze);
  EXPECT_EQ(1800, path->distance());
  maze->flood(0x22);
  path->generateSafePath(0x00, 0x22, maze);
  EXPECT_EQ(667, path->distance());
}

/// Now start to convert some simple strings


TEST_F(PathFinderTest, MakeSmoothCommands_NullString) {
  uint8_t  testCommands[20] = {CMD_ERROR, CMD_END};
  uint8_t  commands[20] = {0};
  char src[] = "";
  makeInPlaceCommands(src, 20, commands);
  EXPECT_STREQ((char *) testCommands, (char *) commands);
  //  path->listCommands(commands); // only included for test coverage

}

TEST_F(PathFinderTest, MakeDiagonalCommands_NullString) {
  uint8_t  testCommands[20] = {CMD_ERROR, CMD_END};
  uint8_t  commands[20] = {0};
  char src[] = "";
  makeInPlaceCommands(src, 20, commands);
  EXPECT_STREQ((char *) testCommands, (char *) commands);
  //  path->listCommands(commands);

}



TEST_F(PathFinderTest, MakeInPlaceCommands_NullString) {
  /*
   *
   */
  uint8_t  testCommands[20] = {CMD_ERROR, CMD_END};
  uint8_t  commands[20] = {0};
  char src[] = "";
  makeInPlaceCommands(src, 20, commands);
  EXPECT_STREQ((char *) testCommands, (char *) commands);
  //  path->listCommands(commands);

}


TEST_F(PathFinderTest, CompareOldvsNewWithExplore) {
  /*
   *
   */
  uint8_t  testCommands[20] = {CMD_BEGIN, FWD4, CMD_EXPLORE, CMD_END};
  uint8_t  commands[20] = {0};
  char src[] = "BFFFFX";
  makeInPlaceCommands(src, 20, commands);
  EXPECT_STREQ((char *) testCommands, (char *) commands);

}


TEST_F(PathFinderTest, MakeInPlaceCommands_StraightTooLong) {
  /*
   *
   */
  uint8_t  testCommands[20] = {CMD_BEGIN, FWD2, IP90R, CMD_ERROR, CMD_END};
  uint8_t  commands[20] = {0};
  char src[] = "BFFRFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFX";
  makeInPlaceCommands(src, 10, commands);
  EXPECT_STREQ((char *) testCommands, (char *) commands);
  //  path->listCommands(commands);

}


TEST_F(PathFinderTest, TestPathCommands_FIG1_AB) {
  uint8_t  commands[20] = {0};
  char src[] = "BFFFFS";
  uint8_t  testCommands[20] = {CMD_BEGIN, FWD4, CMD_END};
  makeInPlaceCommands(src, 20, commands);
  EXPECT_STREQ((char *) testCommands, (char *) commands);
}


// Diagonals paths: Note that the number of diagonals cells traversed is
// even if the turns at the end are opposite directions


TEST_F(PathFinderTest, DiagonalPath_NullSrc_ERROR) {
  uint8_t  commands[20] = {0};
  char src[] = "";
  uint8_t  testCommands[20] = {CMD_ERR_BEGIN, CMD_END};
  makeDiagonalCommands(src, 20, commands);
  EXPECT_STREQ((char *) testCommands, (char *) commands);
  //  path->listCommands(commands);
}

TEST_F(PathFinderTest, DiagonalPath_LongStraight_ERROR) {
  uint8_t  commands[20] = {0};
  char src[] = "BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
  uint8_t  testCommands[20] = {CMD_ERROR, CMD_END};
  makeDiagonalCommands(src, 20, commands);
  EXPECT_STREQ((char *) testCommands, (char *) commands);
}


TEST_F(PathFinderTest, DiagonalPath_LongDiagonal_ERROR) {
  uint8_t  commands[30] = {0};
  char src[] = "BFRLRLRLRLRLRLRLRLRLRLRLRLRLRLRLRS";
  uint8_t  testCommands[30] = {CMD_BEGIN, FWD1, SD45R, DIA31, DS45R, FWD1, CMD_END};
  makeDiagonalCommands(src, 30, commands);
  EXPECT_STREQ((char *) testCommands, (char *) commands);
  // this path is one cell too long
  char srcX[] = "BFRLRLRLRLRLRLRLRLRLRLRLRLRLRLRLRLS";
  uint8_t  testCommandsX[30] = {CMD_ERROR, CMD_END};
  makeDiagonalCommands(srcX, 30, commands);
  EXPECT_STREQ((char *) testCommandsX, (char *) commands);
}



TEST_F(PathFinderTest, TestPathCommands_PairList) {
  uint8_t commands[150] = {0};
  for (int i = 0; i < diagonalPairCount; i++) {
    //    printf("%d\n",i);
    EXPECT_GT(150, strlen(testPairs[i].input));
    makeDiagonalCommands(testPairs[i].input, 150, commands);
    EXPECT_STREQ((char *) testPairs[i].expected, (char *) commands) << testPairs[i].input;
    //    path->listCommands(testPairs[i].expected);
    //    path->listCommands(commands);
    //    printf("-------------\n");
  }
}


/// Some Smooth Paths
TEST_F(PathFinderTest, SmoothPath_SimpleStrings) {
  uint8_t  commands[20] = {0};
  char src[] = "BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
  uint8_t  testCommands[20] = {CMD_ERROR, CMD_END};
  makeDiagonalCommands(src, 20, commands);
  EXPECT_STREQ((char *) testCommands, (char *) commands);
}

TEST_F(PathFinderTest, SmoothTestPathCommands_PairList) {
  uint8_t  commands[150] = {0};

  for (int i = 0; i < smoothPairCount; i++) {
    //    printf("%d\n",i);
    EXPECT_GT(150, strlen(smoothTestPairs[i].input));
    makeSmoothCommands(smoothTestPairs[i].input, 150, commands);
    EXPECT_STREQ((char *)smoothTestPairs[i].expected, (char *)commands) << smoothTestPairs[i].input;
    //    path->listCommands(smoothTestPairs[i].expected);
    //    path->listCommands(commands);
    //    printf("-------------\n");
  }
}
