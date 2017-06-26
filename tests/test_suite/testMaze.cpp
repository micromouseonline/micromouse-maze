#include "gtest/gtest.h"
#include "mazeprinter.h"
#include "mazedata.h"
#include "maze.h"
/////////////////////

class MazeTest : public ::testing::Test {
protected:
  Maze *maze;

  virtual void SetUp() {
    maze = new Maze(16);
    maze->resetToEmptyMaze();
  }

  virtual void TearDown() {
    delete maze;
  }

};


TEST_F(MazeTest, CopyMaze) {
  maze->copyMazeFromFileData(emptyMaze, 256);
  for (uint16_t cell = 0; cell < maze->numCells(); cell++) {
    EXPECT_EQ(emptyMaze[cell], maze->walls(cell));
    EXPECT_TRUE(maze->isVisited(cell));
  }
}

TEST_F(MazeTest, SetClearUnknowns_TestoneCell) {
 maze->resetToEmptyMaze();
  maze->setUnknowns();
  EXPECT_EQ(0x0F,maze->walls(0x22));
  EXPECT_EQ(0x0E,maze->walls(0x00));
  EXPECT_EQ(0x0B,maze->walls(0x01));
  maze->clearUnknowns();
  EXPECT_EQ(0x00,maze->walls(0x22));
  EXPECT_EQ(0x0E,maze->walls(0x00));
  EXPECT_EQ(0x08,maze->walls(0x01));
}

TEST_F(MazeTest, SetClearUnknowns_NoChangeInExploredMaze) {
  maze->copyMazeFromFileData(emptyMaze, 256);
  Maze setMaze(16);
  Maze clearMaze(16);
  setMaze.copyMazeFromFileData(emptyMaze, 256);
  setMaze.setUnknowns();
  clearMaze.copyMazeFromFileData(emptyMaze, 256);
  clearMaze.clearUnknowns();
  for (uint16_t cell = 0; cell < maze->numCells(); cell++) {
    EXPECT_EQ(setMaze.walls(cell), clearMaze.walls(cell));
  }
}

TEST_F(MazeTest, SetClearUnknowns_AllDifferentInUnExploredMaze) {
  Maze setMaze(16);
  Maze clearMaze(16);
  setMaze.setUnknowns();
  clearMaze.clearUnknowns();
  EXPECT_EQ(setMaze.walls(0), clearMaze.walls(0));
  for (uint16_t cell = 1; cell < maze->numCells(); cell++) {
    EXPECT_NE(setMaze.walls(cell), clearMaze.walls(cell));
  }
}

TEST_F(MazeTest, SetAndGetGoal) {
  EXPECT_EQ(DEFAULT_GOAL, maze->goal());
  maze->setGoal(99);
  EXPECT_EQ(99, maze->goal());
}

TEST_F (MazeTest, ResetData_16x16_SetsEmptyMaze) {
  maze->resetToEmptyMaze();
  EXPECT_EQ(256, maze->numCells());
  for (int i = 0; i < maze->numCells(); i++) {
    EXPECT_EQ(emptyMaze[i], maze->walls(i));
  }
}

TEST_F (MazeTest, ResetData_OnlyHomeCellVisited) {
  maze->resetToEmptyMaze();
  for (int i = 0; i < maze->numCells(); i++) {
    if (i != maze->home()) {
      EXPECT_FALSE (maze->isVisited(i));
    }
  }
}


TEST_F(MazeTest, SetClearAndGetWalls) {
  maze->resetToEmptyMaze();
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



TEST_F(MazeTest, SetClearVisited_clearsVisitFlagsOnly) {
  maze->resetToEmptyMaze();
  uint16_t cell = 0x22;
  maze->updateMap(cell, 0x0F);
  EXPECT_TRUE(maze->isVisited(cell));
  EXPECT_EQ(0x0f, maze->walls(cell));
  maze->clearVisited(cell);
  EXPECT_FALSE(maze->isVisited(cell));
  EXPECT_EQ(0x0F, maze->walls(cell));
  maze->setVisited(cell);
  EXPECT_TRUE(maze->isVisited(cell));
  EXPECT_EQ(0x0F, maze->walls(cell));

}

/////////////////////
TEST_F(MazeTest, UpdateMap_OnlyAddsWalls) {
  maze->resetToEmptyMaze();
  uint16_t cell = 0x22;
  maze->updateMap(cell, 0x00);
  EXPECT_FALSE(maze->hasWall(cell, NORTH));
  EXPECT_FALSE(maze->hasWall(cell, EAST));
  EXPECT_FALSE(maze->hasWall(cell, SOUTH));
  EXPECT_FALSE(maze->hasWall(cell, WEST));

  maze->updateMap(cell, 1 << NORTH);
  EXPECT_TRUE(maze->hasWall(cell, NORTH));
  EXPECT_FALSE(maze->hasWall(cell, EAST));
  EXPECT_FALSE(maze->hasWall(cell, SOUTH));
  EXPECT_FALSE(maze->hasWall(cell, WEST));

  maze->updateMap(cell, 1 << EAST);
  EXPECT_TRUE(maze->hasWall(cell, NORTH));
  EXPECT_TRUE(maze->hasWall(cell, EAST));
  EXPECT_FALSE(maze->hasWall(cell, SOUTH));
  EXPECT_FALSE(maze->hasWall(cell, WEST));

  maze->updateMap(cell, 1 << SOUTH);
  EXPECT_TRUE(maze->hasWall(cell, NORTH));
  EXPECT_TRUE(maze->hasWall(cell, EAST));
  EXPECT_TRUE(maze->hasWall(cell, SOUTH));
  EXPECT_FALSE(maze->hasWall(cell, WEST));

  maze->updateMap(cell, 1 << WEST);
  EXPECT_TRUE(maze->hasWall(cell, NORTH));
  EXPECT_TRUE(maze->hasWall(cell, EAST));
  EXPECT_TRUE(maze->hasWall(cell, SOUTH));
  EXPECT_TRUE(maze->hasWall(cell, WEST));

}

/////////////////////
TEST_F(MazeTest, HasExit) {
  maze->resetToEmptyMaze();
  EXPECT_FALSE(maze->hasExit(0x0F, WEST));
  EXPECT_FALSE(maze->hasExit(0x0F, NORTH));
  EXPECT_FALSE(maze->hasExit(0xF0, EAST));
  EXPECT_FALSE(maze->hasExit(0xF0, SOUTH));
}

TEST_F (MazeTest, CopyCellFromFileData_GetExactCopy) {
  const uint8_t *src = japan2007;
  maze->resetToEmptyMaze();
  for (int i = 0; i < maze->numCells(); i++) {
    maze->copyCellFromFileData(i, src[i]);
  }
  for (int i = 0; i < maze->numCells(); i++) {
    EXPECT_EQ(src[i], maze->walls(i));
    EXPECT_TRUE(maze->isVisited(i));
  }
}

TEST_F(MazeTest, OpenClosedMaze_HasExitWhenOpen) {
  maze->resetToEmptyMaze();
  maze->clearUnknowns();
  EXPECT_TRUE(maze->hasExit(0x22, WEST));
  EXPECT_TRUE(maze->hasExit(0x22, NORTH));
  EXPECT_TRUE(maze->hasExit(0x22, EAST));
  EXPECT_TRUE(maze->hasExit(0x22, SOUTH));
  maze->setUnknowns();
  EXPECT_FALSE(maze->hasExit(0x22, WEST));
  EXPECT_FALSE(maze->hasExit(0x22, NORTH));
  EXPECT_FALSE(maze->hasExit(0x22, EAST));
  EXPECT_FALSE(maze->hasExit(0x22, SOUTH));
  maze->clearUnknowns();
  EXPECT_TRUE(maze->hasExit(0x22, WEST));
  EXPECT_TRUE(maze->hasExit(0x22, NORTH));
  EXPECT_TRUE(maze->hasExit(0x22, EAST));
  EXPECT_TRUE(maze->hasExit(0x22, SOUTH));
}

TEST_F(MazeTest, NeighbourCellAddresses) {
  for (uint16_t cell = 0; cell < maze->numCells(); cell++) {
    EXPECT_EQ((cell + 1) % maze->numCells(), maze->cellNorth(cell));
    EXPECT_EQ((cell + maze->width()) % maze->numCells(), maze->cellEast(cell));
    EXPECT_EQ((cell + maze->numCells() - 1) % maze->numCells(), maze->cellSouth(cell));
    EXPECT_EQ((cell + maze->numCells() - maze->width()) % maze->numCells(), maze->cellWest(cell));
    EXPECT_EQ(maze->cellNorth(cell), maze->neighbour(cell, NORTH));
    EXPECT_EQ(maze->cellEast(cell), maze->neighbour(cell, EAST));
    EXPECT_EQ(maze->cellSouth(cell), maze->neighbour(cell, SOUTH));
    EXPECT_EQ(maze->cellWest(cell), maze->neighbour(cell, WEST));
  }
}


TEST_F(MazeTest, NeighbourInvalidDirection_ReturnsUINT16_MAX) {
  EXPECT_EQ(MAX_COST, maze->neighbour(0, -1));
}


TEST_F(MazeTest, LoadAndSave_MazeKeptSafe) {
  uint8_t backupWalls[1024] = {};
  maze->copyMazeFromFileData(japan2007,256);
  maze->save(backupWalls);
  maze->resetToEmptyMaze();
  for (int i = 0; i < maze->numCells(); i++){
    EXPECT_EQ(maze->walls(i),emptyMaze[i]);
  }
  maze->load(backupWalls);
  for (int i = 0; i < maze->numCells(); i++){
    EXPECT_EQ(maze->walls(i),japan2007[i]);
  }


}

TEST_F(MazeTest, RecalculateGoalOneEntrance_SetToCellOppositeEntrance) {
  maze->resetToEmptyMaze();
  EXPECT_EQ(0x77, maze->goal());
  maze->setWall(0x77, WEST);
  maze->setWall(0x78, WEST);
  maze->setWall(0x78, NORTH);
  maze->setWall(0x88, NORTH);
  maze->setWall(0x88, EAST);
  maze->setWall(0x87, EAST);
  maze->setWall(0x87, SOUTH);
  maze->recalculateGoal();
  EXPECT_EQ(0x78, maze->goal());
  //
  maze->setWall(0x77, SOUTH);
  maze->clearWall(0x77, WEST);
  maze->recalculateGoal();
  EXPECT_EQ(0x87, maze->goal());
  //
  maze->setWall(0x77, WEST);
  maze->clearWall(0x78, WEST);
  maze->recalculateGoal();
  EXPECT_EQ(0x88, maze->goal());
  //
  maze->setWall(0x78, WEST);
  maze->clearWall(0x78, NORTH);
  maze->recalculateGoal();
  EXPECT_EQ(0x77, maze->goal());
  //
  maze->setWall(0x78, NORTH);
  maze->clearWall(0x88, NORTH);
  maze->recalculateGoal();
  EXPECT_EQ(0x87, maze->goal());
  //
  maze->setWall(0x88, NORTH);
  maze->clearWall(0x88, EAST);
  maze->recalculateGoal();
  EXPECT_EQ(0x78, maze->goal());
  //
  maze->setWall(0x88, EAST);
  maze->clearWall(0x87, EAST);
  maze->recalculateGoal();
  EXPECT_EQ(0x77, maze->goal());
  //
  maze->setWall(0x87, EAST);
  maze->clearWall(0x87, SOUTH);
  maze->recalculateGoal();
  EXPECT_EQ(0x88, maze->goal());
}