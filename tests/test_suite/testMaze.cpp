#include "gtest/gtest.h"
#include "oldmaze.h"
#include "mazeprinter.h"
#include "mazedata.h"
#include "maze.h"
/////////////////////

class MazeTest : public ::testing::Test {
protected:
  Maze *maze;

  virtual void SetUp() {
    maze = new Maze();
    maze->resetData();
  }

  virtual void TearDown() {
    delete maze;
  }

};

TEST_F(MazeTest, SetAndGetGoal) {
  EXPECT_EQ(DEFAULT_GOAL, maze->goal());
  maze->setGoal(99);
  EXPECT_EQ(99, maze->goal());
}

TEST_F (MazeTest, ClearMaze_AllWallsAbsent) {
  maze->clearMaze();
  for (int i = 0; i < maze->numCells(); i++) {
    EXPECT_EQ (0, maze->walls(i));
  }
}

TEST_F (MazeTest, ResetData_16x16_SetsEmptyMaze) {
  maze->resetData();
  EXPECT_EQ(256, maze->numCells());
  for (int i = 0; i < maze->numCells(); i++) {
    EXPECT_EQ(emptyMaze[i], maze->walls(i));
  }
}

TEST_F (MazeTest, ResetData_DefaultCostsAreUINT16_MAX) {
  maze->resetData();
  for (int i = 0; i < maze->numCells(); i++) {
    EXPECT_EQ (UINT16_MAX, maze->cost(i));
  }
}

TEST_F (MazeTest, ResetData_OnlyHomeCellVisited) {
  maze->resetData();
  for (int i = 0; i < maze->numCells(); i++) {
    if (i != maze->home()) {
      EXPECT_FALSE (maze->isVisited(i));
    }
  }
}


TEST_F(MazeTest, SetClearAndGetWalls) {
  maze->resetData();
  maze->setWall(0x22, NORTH);
  maze->setWall(0x22, EAST);
  maze->setWall(0x22, SOUTH);
  maze->setWall(0x22, WEST);
  EXPECT_FALSE(maze->hasExit(0x22, EAST));
  EXPECT_FALSE(maze->hasExit(0x32, WEST));
  EXPECT_FALSE(maze->hasExit(0x22, SOUTH));
  EXPECT_FALSE(maze->hasExit(0x21, NORTH));
  EXPECT_FALSE(maze->hasExit(0x22, WEST));
  EXPECT_FALSE(maze->hasExit(0x12, EAST));
  EXPECT_FALSE(maze->hasExit(0x22, NORTH));
  EXPECT_FALSE(maze->hasExit(0x23, SOUTH));
  EXPECT_TRUE(maze->hasWall(0x22, EAST));
  EXPECT_TRUE(maze->hasWall(0x32, WEST));
  EXPECT_TRUE(maze->hasWall(0x22, SOUTH));
  EXPECT_TRUE(maze->hasWall(0x21, NORTH));
  EXPECT_TRUE(maze->hasWall(0x22, WEST));
  EXPECT_TRUE(maze->hasWall(0x12, EAST));
  EXPECT_TRUE(maze->hasWall(0x22, NORTH));
  EXPECT_TRUE(maze->hasWall(0x23, SOUTH));
  maze->clearWall(0x22, NORTH);
  maze->clearWall(0x22, EAST);
  maze->clearWall(0x22, SOUTH);
  maze->clearWall(0x22, WEST);
  EXPECT_TRUE(maze->hasExit(0x22, EAST));
  EXPECT_TRUE(maze->hasExit(0x32, WEST));
  EXPECT_TRUE(maze->hasExit(0x22, SOUTH));
  EXPECT_TRUE(maze->hasExit(0x21, NORTH));
  EXPECT_TRUE(maze->hasExit(0x22, WEST));
  EXPECT_TRUE(maze->hasExit(0x12, EAST));
  EXPECT_TRUE(maze->hasExit(0x22, NORTH));
  EXPECT_TRUE(maze->hasExit(0x23, SOUTH));
  EXPECT_FALSE(maze->hasWall(0x22, EAST));
  EXPECT_FALSE(maze->hasWall(0x32, WEST));
  EXPECT_FALSE(maze->hasWall(0x22, SOUTH));
  EXPECT_FALSE(maze->hasWall(0x21, NORTH));
  EXPECT_FALSE(maze->hasWall(0x22, WEST));
  EXPECT_FALSE(maze->hasWall(0x12, EAST));
  EXPECT_FALSE(maze->hasWall(0x22, NORTH));
  EXPECT_FALSE(maze->hasWall(0x23, SOUTH));
}

/////////////////////
TEST_F(MazeTest, HasExit) {
  maze->resetData();
  EXPECT_FALSE(maze->hasExit(0x0F, WEST));
  EXPECT_FALSE(maze->hasExit(0x0F, NORTH));
  EXPECT_FALSE(maze->hasExit(0xF0, EAST));
  EXPECT_FALSE(maze->hasExit(0xF0, SOUTH));
}

TEST_F (MazeTest, CopyCellFromFileData_GetExactCopy) {
  const uint8_t *src = japan2007;
  maze->resetData();
  for (int i = 0; i < maze->numCells(); i++) {
    maze->copyCellFromFileData(i, src[i]);
  }
  for (int i = 0; i < maze->numCells(); i++) {
    EXPECT_EQ(src[i], maze->walls(i));
    EXPECT_TRUE(maze->isVisited(i));
  }
}



