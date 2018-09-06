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
#include "mazedata.h"
#include "maze.h"
/////////////////////

class MazeTest : public ::testing::Test {
protected:
  Maze *maze;
  Maze * maze32;

  virtual void SetUp() {
    maze32 = new Maze(32);
    maze = new Maze(16);
  }

  virtual void TearDown() {
    delete maze;
    delete maze32;
  }

  virtual void copyMaze(Maze *maze, const uint8_t *mazeData) const {
    if (!maze || !mazeData) {
      return;
    }
    maze->loadFromFileData(mazeData);

  }


};

TEST_F(MazeTest, RowAndColCalculations) {
  EXPECT_EQ(0, maze->col(0x00));
  EXPECT_EQ(0, maze->row(0x00));
  EXPECT_EQ(5, maze->col(0x57));
  EXPECT_EQ(7, maze->row(0x57));
  EXPECT_EQ(15, maze->col(0xf2));
  EXPECT_EQ(2, maze->row(0xf2));
}


TEST_F(MazeTest, SetXWalls) {
  EXPECT_EQ(WALL, maze32->xwalls(0).wall.south);
  EXPECT_EQ(WALL, maze32->xwalls(0).wall.east);
  EXPECT_EQ(WALL, maze32->xwalls(0).wall.west);
  EXPECT_EQ(UNKNOWN, maze32->xwalls(132).wall.north);
  EXPECT_EQ(UNKNOWN, maze32->xwalls(132).wall.east);
  EXPECT_EQ(UNKNOWN, maze32->xwalls(132).wall.south);
  EXPECT_EQ(UNKNOWN, maze32->xwalls(132).wall.west);
  maze32->setWall(132, NORTH);
  EXPECT_EQ(WALL, maze32->xwalls(132).wall.north);
  EXPECT_EQ(WALL, maze32->xwalls(133).wall.south);
  EXPECT_EQ(UNKNOWN, maze32->xwalls(132).wall.east);
  EXPECT_EQ(UNKNOWN, maze32->xwalls(132).wall.south);
  EXPECT_EQ(UNKNOWN, maze32->xwalls(132).wall.west);
  maze32->setWall(132, EAST);
  EXPECT_EQ(WALL, maze32->xwalls(132).wall.east);
  EXPECT_EQ(WALL, maze32->xwalls(164).wall.west);
  EXPECT_EQ(UNKNOWN, maze32->xwalls(132).wall.south);
  EXPECT_EQ(UNKNOWN, maze32->xwalls(132).wall.west);
  maze32->setWall(132, SOUTH);
  EXPECT_EQ(WALL, maze32->xwalls(132).wall.south);
  EXPECT_EQ(WALL, maze32->xwalls(131).wall.north);
  EXPECT_EQ(UNKNOWN, maze32->xwalls(132).wall.west);
  maze32->setWall(132, WEST);
  EXPECT_EQ(WALL, maze32->xwalls(132).wall.west);
  EXPECT_EQ(WALL, maze32->xwalls(100).wall.east);
}

TEST_F(MazeTest, ClearXWalls) {
  EXPECT_EQ(WALL, maze32->xwalls(0).wall.south);
  EXPECT_EQ(WALL, maze32->xwalls(0).wall.east);
  EXPECT_EQ(WALL, maze32->xwalls(0).wall.west);
  EXPECT_EQ(UNKNOWN, maze32->xwalls(132).wall.north);
  EXPECT_EQ(UNKNOWN, maze32->xwalls(132).wall.east);
  EXPECT_EQ(UNKNOWN, maze32->xwalls(132).wall.south);
  EXPECT_EQ(UNKNOWN, maze32->xwalls(132).wall.west);
  maze32->setWall(132, NORTH);
  maze32->setWall(132, EAST);
  maze32->setWall(132, SOUTH);
  maze32->setWall(132, WEST);

  maze32->clearWall(132, NORTH);
  EXPECT_EQ(EXIT, maze32->xwalls(132).wall.north);
  EXPECT_EQ(EXIT, maze32->xwalls(133).wall.south);
  EXPECT_EQ(WALL, maze32->xwalls(132).wall.east);
  EXPECT_EQ(WALL, maze32->xwalls(132).wall.south);
  EXPECT_EQ(WALL, maze32->xwalls(132).wall.west);
  maze32->clearWall(132, EAST);
  EXPECT_EQ(EXIT, maze32->xwalls(132).wall.east);
  EXPECT_EQ(EXIT, maze32->xwalls(164).wall.west);
  EXPECT_EQ(WALL, maze32->xwalls(132).wall.south);
  EXPECT_EQ(WALL, maze32->xwalls(132).wall.west);
  maze32->clearWall(132, SOUTH);
  EXPECT_EQ(EXIT, maze32->xwalls(132).wall.south);
  EXPECT_EQ(EXIT, maze32->xwalls(131).wall.north);
  EXPECT_EQ(WALL, maze32->xwalls(132).wall.west);
  maze32->clearWall(132, WEST);
  EXPECT_EQ(EXIT, maze32->xwalls(132).wall.west);
  EXPECT_EQ(EXIT, maze32->xwalls(100).wall.east);
}

TEST_F(MazeTest, HasUnknowns) {
  EXPECT_TRUE(maze32->isVisited(0));
  EXPECT_FALSE(maze32->isVisited(1));
}


TEST_F(MazeTest, HasKnownExit) {

  EXPECT_TRUE(maze32->hasExit(0, NORTH, CLOSED_MASK));
  EXPECT_FALSE(maze32->hasExit(0, EAST, CLOSED_MASK));
  EXPECT_FALSE(maze32->hasExit(0, SOUTH, CLOSED_MASK));
  EXPECT_FALSE(maze32->hasExit(0, WEST, CLOSED_MASK));

  EXPECT_FALSE(maze32->hasExit(1, NORTH, CLOSED_MASK));
  EXPECT_FALSE(maze32->hasExit(1, EAST, CLOSED_MASK));
  EXPECT_TRUE(maze32->hasExit(1, SOUTH, CLOSED_MASK));
  EXPECT_FALSE(maze32->hasExit(1, WEST, CLOSED_MASK));
}


TEST_F(MazeTest, HasKnownWall) {

  EXPECT_FALSE(maze32->hasWall(0, NORTH, CLOSED_MASK));
  EXPECT_TRUE(maze32->hasWall(0, EAST, CLOSED_MASK));
  EXPECT_TRUE(maze32->hasWall(0, SOUTH, CLOSED_MASK));
  EXPECT_TRUE(maze32->hasWall(0, WEST, CLOSED_MASK));
  // all the unknowns are walls unless we 'see' them
  EXPECT_TRUE(maze32->hasWall(1, NORTH, CLOSED_MASK));
  EXPECT_TRUE(maze32->hasWall(1, EAST, CLOSED_MASK));
  EXPECT_FALSE(maze32->hasWall(1, SOUTH, CLOSED_MASK));
  EXPECT_TRUE(maze32->hasWall(1, WEST, CLOSED_MASK));
  // all the unknowns are walls unless we 'see' them
  maze32->setVisited(1);
  EXPECT_FALSE(maze32->hasWall(1, NORTH, CLOSED_MASK));
  EXPECT_FALSE(maze32->hasWall(1, EAST, CLOSED_MASK));
  EXPECT_FALSE(maze32->hasWall(1, SOUTH, CLOSED_MASK));
  EXPECT_TRUE(maze32->hasWall(1, WEST, CLOSED_MASK));
}





TEST_F(MazeTest, SetTrainingGoal) {
  maze->setGoal(TRAINING_GOAL);
  EXPECT_EQ(TRAINING_GOAL, maze->goal());
}

TEST_F(MazeTest, CopyClassicMaze) {
  Maze testMaze(16);
  copyMaze(&testMaze, emptyMaze);
  for (uint16_t cell = 0; cell < testMaze.numCells(); cell++) {
    EXPECT_EQ(emptyMaze[cell], testMaze.fwalls(cell));
    EXPECT_TRUE(testMaze.isVisited(cell));
  }
}

TEST_F(MazeTest, CopyHalfSizeMaze) {
  Maze testMaze(32);
  copyMaze(&testMaze, emptyHalfSize);
  for (uint16_t cell = 0; cell < testMaze.numCells(); cell++) {
    EXPECT_EQ(emptyHalfSize[cell], testMaze.fwalls(cell));
    EXPECT_TRUE(testMaze.isVisited(cell));
  }
}



TEST_F(MazeTest, SetClearUnknowns_NoChangeInExploredMaze) {
  maze->loadFromFileData(emptyMaze);
  Maze setMaze(16);
  Maze clearMaze(16);
  setMaze.loadFromFileData(emptyMaze);
  setMaze.setUnknowns();
  clearMaze.loadFromFileData(emptyMaze);
  clearMaze.clearUnknowns();
  for (uint16_t cell = 0; cell < maze->numCells(); cell++) {
    EXPECT_EQ(setMaze.fwalls(cell), clearMaze.fwalls(cell));
  }
}



TEST_F(MazeTest, SetAndGetGoal) {
  EXPECT_EQ(DEFAULT_GOAL, maze->goal());
  maze->setGoal(99);
  EXPECT_EQ(99, maze->goal());
}

TEST_F(MazeTest, ResetData_16x16_SetsEmptyMaze) {
  maze->resetToEmptyMaze();
  EXPECT_EQ(256, maze->numCells());
  for (int i = 0; i < maze->numCells(); i++) {
    EXPECT_EQ(emptyMaze[i], maze->fwalls(i));
  }
}

TEST_F(MazeTest, ResetData_OnlyHomeCellVisited) {
  maze->resetToEmptyMaze();
  for (int i = 0; i < maze->numCells(); i++) {
    if (i != maze->home()) {
      EXPECT_FALSE(maze->isVisited(i));
    }
  }
}



TEST_F(MazeTest, SetClearVisited_clearsVisitFlagsOnly) {
  maze->resetToEmptyMaze();
  uint16_t cell = 0x22;
  printf("%02x\n", maze->xwalls(cell).byte);
  maze->updateMap(cell, 0x0F);
  printf("%02x\n", maze->xwalls(cell).byte);
  EXPECT_TRUE(maze->isVisited(cell));
  EXPECT_EQ(0x0f, maze->fwalls(cell));
  printf("%02x\n", maze->xwalls(cell).byte);
  maze->clearVisited(cell);
  printf("%02x\n", maze->xwalls(cell).byte);
  EXPECT_FALSE(maze->isVisited(cell));
  // unseen walls are virtual but present
  // to 'unsee' a wall, it should be marked as UNKNOWN
  EXPECT_EQ(0x0F, maze->fwalls(cell));
  maze->setVisited(cell);
  EXPECT_TRUE(maze->isVisited(cell));
  EXPECT_EQ(0x0F, maze->fwalls(cell));

}



/////////////////////
TEST_F(MazeTest, HasExit) {

  EXPECT_FALSE(maze->hasExit(0, EAST, OPEN_MASK));
  EXPECT_FALSE(maze->hasExit(0, EAST, CLOSED_MASK));

  EXPECT_TRUE(maze->hasExit(0, NORTH, CLOSED_MASK));
  EXPECT_TRUE(maze->hasExit(0, NORTH, OPEN_MASK));
  EXPECT_TRUE(maze->hasExit(1, SOUTH, OPEN_MASK));
  EXPECT_TRUE(maze->hasExit(1, SOUTH, CLOSED_MASK));
  EXPECT_TRUE(maze->hasExit(1, EAST, OPEN_MASK));
  EXPECT_FALSE(maze->hasExit(1, EAST, CLOSED_MASK));

}

TEST_F(MazeTest, CopyCellFromFileData_GetExactCopy) {
  const uint8_t *src = japan2007ef;
  maze->resetToEmptyMaze();
  maze->loadFromFileData(src);

  for (int i = 0; i < maze->numCells(); i++) {
    EXPECT_EQ(src[i], maze->fwalls(i));
    EXPECT_TRUE(maze->isVisited(i));
  }
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
  maze->loadFromFileData(japan2007ef);
  maze->save(backupWalls);
  maze->resetToEmptyMaze();
  for (int i = 0; i < maze->numCells(); i++) {
    EXPECT_EQ(maze->fwalls(i), emptyMaze[i]);
  }
  maze->load(backupWalls);
  for (int i = 0; i < maze->numCells(); i++) {
    EXPECT_EQ(maze->fwalls(i), japan2007ef[i]);
  }
}


TEST_F(MazeTest, RecalculateGoal) {
  maze->loadFromFileData(japan2007ef);
  EXPECT_EQ(0x77, maze->goal());
  maze->setGoal(0x87);
  maze->recalculateGoal();
  EXPECT_EQ(0x77, maze->goal());
  maze->setGoal(0x11);
  maze->recalculateGoal();
  EXPECT_EQ(0x77, maze->goal());
  maze->clearWall(0x87, SOUTH);
  maze->setGoal(0x11);
  maze->recalculateGoal();
  EXPECT_EQ(0x88, maze->goal());
  MazePrinter::printPlain(maze);
  maze32->setGoal(0x11);
  maze32->recalculateGoal();
  EXPECT_EQ(0x11, maze32->goal());
}



