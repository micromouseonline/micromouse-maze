#include <iostream>
#include <mazedata.h>
#include "gtest/gtest.h"
#include "mazeprinter.h"
#include "mazepathfinder.h"
#include "maze.h"
#include "mazedata.h"
#include "commands.h"
#include "pathfinder.h"

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
  EXPECT_EQ(0, path->length());
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
  path->generatePath(0, 0x77, maze);
  EXPECT_EQ(16, strlen(path->path()));
  EXPECT_STREQ("BFFFFFFFRFFFFFFS", path->path());
  EXPECT_EQ(15, path->length());
  EXPECT_EQ(EAST, path->endHeading());
  EXPECT_EQ(0x77, path->endCell());
  EXPECT_TRUE(path->reachesTarget());
}

TEST_F(PathFinderTest, generate_EmptyMaze_AtDestination) {
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(emptyMaze, 256);
  maze->flood(0x77);
  path->generatePath(0x77, 0x77, maze);
  EXPECT_EQ(2, strlen(path->path()));
  EXPECT_STREQ("BS", path->path());
  EXPECT_EQ(NORTH, path->endHeading());
  EXPECT_EQ(0x77, path->endCell());
  EXPECT_TRUE(path->reachesTarget());
}

TEST_F(PathFinderTest, generate_EmptyMaze_OneCellAhead) {
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(emptyMaze, 256);
  maze->flood(0x77);
  path->generatePath(0x76, 0x77, maze);
  EXPECT_EQ(3, strlen(path->path()));
  EXPECT_STREQ("BFS", path->path());
  EXPECT_EQ(NORTH, path->endHeading());
  EXPECT_EQ(0x77, path->endCell());
  EXPECT_TRUE(path->reachesTarget());
}

TEST_F(PathFinderTest, generate_EmptyMaze_OneCellBehind) {
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(emptyMaze, 256);
  maze->flood(0x77);
  path->generatePath(0x78, 0x77, maze);
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
  path->generatePath(0, 0x77, maze);
  EXPECT_EQ(2, strlen(path->path()));
  EXPECT_STREQ("BS", path->path());
  EXPECT_EQ(INVALID_DIRECTION, path->endHeading());
  EXPECT_EQ(0, path->endCell());
  EXPECT_FALSE(path->reachesTarget());
}

TEST_F(PathFinderTest, generate_NoRoute) {
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(emptyMaze, 256);
  maze->setWall(0x01, NORTH);
  maze->setWall(0x01, EAST);
  maze->flood(0x77);
  path->generatePath(0, 0x77, maze);
  EXPECT_EQ(2, strlen(path->path()));
  EXPECT_STREQ("BS", path->path());
  EXPECT_EQ(INVALID_DIRECTION, path->endHeading());
  EXPECT_EQ(0, path->endCell());
  EXPECT_FALSE(path->reachesTarget());
}

TEST_F(PathFinderTest, generate_Japan2007_ManHattan_CorrectPAth) {
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(japan2007ef, 256);
  maze->flood(0x77);
  path->generatePath(0, 0x77, maze);
  EXPECT_EQ(74, strlen(path->path()));
  char result[] = "BFFFRLLRRLLRRLLRFFRRFLLFFLRFRRLLRRLLRFFFFFFFFFRFFFFFRLRLLRRLLRRFFRFFFLFFFS";
  EXPECT_STREQ(result, path->path());
  EXPECT_EQ(WEST, path->endHeading());
  EXPECT_EQ(0x77, path->endCell());
  EXPECT_TRUE(path->reachesTarget());
}

TEST_F(PathFinderTest, generate_Japan2007_RunLength_Path) {
  maze->setFloodType(Maze::RUNLENGTH_FLOOD);
  maze->copyMazeFromFileData(japan2007ef, 256);
  maze->flood(0x77);
  path->generatePath(0, 0x87, maze);
  EXPECT_EQ(73, strlen(path->path()));
  char result[] = "BFRLRLRLFLRFFLFRFFRRFLLFFLRLRFRFFFFFFFFFFFFFFRFFFFFFRLRLLRRLLRRFFRFFFLFFS";
  EXPECT_STREQ(result, path->path());
  EXPECT_EQ(NORTH, path->startHeading());
  EXPECT_EQ(WEST, path->endHeading());
  EXPECT_EQ(0x00, path->startCell());
  EXPECT_EQ(0x87, path->endCell());
  EXPECT_EQ(72, path->length());
  EXPECT_TRUE(path->reachesTarget());
}


/// Now start to convert some simple strings




TEST_F(PathFinderTest, CompareOldvsNewWithExplore) {
  /*
   *
   */
  uint8_t  testCommands[20] = {CMD_BEGIN, FWD4, CMD_EXPLORE};
  uint8_t  commands[20] = {0};
  char src[] = "BFFFFX";
  path->makeInPlaceCommands(src, commands);
  ASSERT_STREQ((char *) commands, (char *) testCommands);

}

#if 0

// these tests are not used once the code has been micrted. They are fro
// comparing old with new exhaustively
TEST_F(PathFinderTest, CompareOldvsNewIPCommands) {
  /*
   * exhastive test of path generation for simple smooth, orthogonal paths
   */
  uint8_t ipCommands[132] = {0};
  maze->copyMazeFromFileData(japan2007ef, 256);
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  for (uint16_t goal = 1; goal < maze->numCells(); goal++) {
    maze->flood(goal);
    path->generatePath(0, goal, maze);
    makeInPlaceCommands(commandList, path->path());
    path->makeInPlaceCommands(path->path(), ipCommands);
    ASSERT_STREQ((char *) commandList, (char *) ipCommands);
  }
  maze->setFloodType(Maze::RUNLENGTH_FLOOD);
  for (uint16_t goal = 1; goal < maze->numCells(); goal++) {
    maze->flood(goal);
    path->generatePath(0, goal, maze);
    makeInPlaceCommands(commandList, path->path());
    path->makeInPlaceCommands(path->path(), ipCommands);
    ASSERT_STREQ((char *) commandList, (char *) ipCommands);
  }
}



TEST_F(PathFinderTest, CompareOldvsNewSmoothCommands) {
  /*
   * exhastive test of path generation for simple smooth, orthogonal paths
   */
  uint8_t smoothCommands[132] = {0};
  maze->copyMazeFromFileData(japan2007ef, 256);
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  for (uint16_t goal = 1; goal < maze->numCells(); goal++) {
    maze->flood(goal);
    path->generatePath(0, goal, maze);
    path->makeSmoothCommands(path->path(),commandList);
    makeSmoothPath(path->path(), smoothCommands);
    ASSERT_STREQ((char *) commandList, (char *) smoothCommands);
  }
  maze->setFloodType(Maze::RUNLENGTH_FLOOD);
  for (uint16_t goal = 1; goal < maze->numCells(); goal++) {
    maze->flood(goal);
    path->generatePath(0, goal, maze);
    path->makeSmoothCommands(path->path(),commandList);
    makeSmoothPath(path->path(), smoothCommands);
    ASSERT_STREQ((char *) commandList, (char *) smoothCommands);
  }
}

TEST_F(PathFinderTest, CompareOldvsNewDiagonalCommands) {
  /*
   * exhaustive test of path generation for diagonal paths
   */
  printf("\n");
  uint8_t diagonalCommands[256] = {0};
  maze->copyMazeFromFileData(japan2007ef, 256);
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  for (uint16_t goal = 1; goal < maze->numCells(); goal++) {
    maze->flood(goal);
    path->generatePath(0, goal, maze);
    makeInPlaceCommands(commandList, path->path());
    diagonals();
    smoothTurns();
    fastTurns();
    makeDiagonalPath(path->path(), diagonalCommands);
    EXPECT_STREQ((char *) commandList, (char *) diagonalCommands) << "goal: " << goal << " pathstr: " << path->path();
  }

  maze->setFloodType(Maze::RUNLENGTH_FLOOD);
  for (uint16_t goal = 1; goal < maze->numCells(); goal++) {
    maze->flood(goal);
    path->generatePath(0, goal, maze);
    makeInPlaceCommands(commandList, path->path());
    diagonals();
    smoothTurns();
    fastTurns();
    makeDiagonalPath(path->path(), diagonalCommands);
    EXPECT_STREQ((char *) commandList, (char *) diagonalCommands) << "goal: " << goal << " pathstr: " << path->path();;
  }
}


TEST_F(PathFinderTest, CompareClassvsNewDiagonalCommands) {
  /*
   * exhaustive test of path generation for diagonal paths
   */
  printf("\n");
  uint8_t diagonalCommands[256] = {0};
  maze->copyMazeFromFileData(japan2007ef, 256);
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  for (uint16_t goal = 1; goal < maze->numCells(); goal++) {
    maze->flood(goal);
    path->generatePath(0, goal, maze);
    path->makeDiagonalCommands(path->path(), commandList);
    makeDiagonalPath(path->path(), diagonalCommands);
    EXPECT_STREQ((char *) commandList, (char *) diagonalCommands) << "goal: " << goal << " pathstr: " << path->path();
  }

  maze->setFloodType(Maze::RUNLENGTH_FLOOD);
  for (uint16_t goal = 1; goal < maze->numCells(); goal++) {
    maze->flood(goal);
    path->generatePath(0, goal, maze);
    path->makeDiagonalCommands(path->path(), commandList);
    makeDiagonalPath(path->path(), diagonalCommands);
    EXPECT_STREQ((char *) commandList, (char *) diagonalCommands) << "goal: " << goal << " pathstr: " << path->path();;
  }
}

#endif