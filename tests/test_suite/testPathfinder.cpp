#include <iostream>
#include <mazedata.h>
#include "gtest/gtest.h"
#include "mazeprinter.h"
#include "mazepathfinder.h"
#include "maze.h"
#include "mazedata.h"
#include "commands.h"


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
