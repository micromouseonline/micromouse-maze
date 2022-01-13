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

#include <vector>
#include <mazedata.h>
#include "gtest/gtest.h"
#include "mazeprinter.h"
#include "mazedata.h"
#include "maze.h"
#include "mazefiler.h"

/////////////////////

class MazeTest : public ::testing::Test {
protected:
  Maze *maze;
  uint16_t top_left;
  uint16_t top_right;
  uint16_t bottom_left;
  uint16_t bottom_right;

  virtual void SetUp() {
    maze = new Maze(16);
    top_left = maze->width() * (0) + (maze->width() - 1);
    top_right = maze->width() * (maze->width() - 1) + (maze->width() - 1);
    bottom_left = 0;
    bottom_right = maze->width() * (maze->width() - 1) + 0;
  }

  virtual void TearDown() {
    delete maze;
  }

};

TEST_F(MazeTest, initial_size_is_correct) {
  EXPECT_EQ(16, maze->width());
  Maze big_maze(32);
  EXPECT_EQ(32, big_maze.width());
}

// Ensure that the wall data is being updated in the way we expect
TEST_F(MazeTest, stored_wall_data_correct) {
  EXPECT_EQ(0x00, maze->openWalls(0x11));
  EXPECT_EQ(0x0f, maze->closedWalls(0x11));
  maze->setWallPresent(0x11, NORTH);
  EXPECT_EQ(0x01, maze->openWalls(0x11));
  EXPECT_EQ(0x0F, maze->closedWalls(0x11));
  maze->setWallAbsent(0x11, SOUTH);
  EXPECT_EQ(0x01, maze->openWalls(0x11));
  EXPECT_EQ(0b1011, maze->closedWalls(0x11));
}


TEST_F(MazeTest, has_open_exit) {
  maze->resetToEmptyMaze();
  EXPECT_TRUE(maze->hasOpenExit(0x01, NORTH));
  EXPECT_TRUE(maze->hasOpenExit(0x01, SOUTH));
  EXPECT_TRUE(maze->hasOpenExit(0x01, EAST));
  EXPECT_FALSE(maze->hasOpenExit(0x01, WEST));
}

TEST_F(MazeTest, has_closed_exit) {
  maze->resetToEmptyMaze();
  EXPECT_FALSE(maze->hasClosedExit(0x01, NORTH));
  EXPECT_TRUE(maze->hasClosedExit(0x01, SOUTH));
  EXPECT_FALSE(maze->hasClosedExit(0x01, EAST));
  EXPECT_FALSE(maze->hasClosedExit(0x01, WEST));
}


TEST_F(MazeTest, initialisation_has_boundary_walls) {
  EXPECT_FALSE(maze->hasExit(bottom_left, WEST, OPEN_MAZE));
  EXPECT_FALSE(maze->hasExit(bottom_left, SOUTH, OPEN_MAZE));
  EXPECT_FALSE(maze->hasExit(top_left, WEST, OPEN_MAZE));
  EXPECT_FALSE(maze->hasExit(top_left, NORTH, OPEN_MAZE));
  EXPECT_FALSE(maze->hasExit(top_right, NORTH, OPEN_MAZE));
  EXPECT_FALSE(maze->hasExit(top_right, EAST, OPEN_MAZE));
  EXPECT_FALSE(maze->hasExit(bottom_right, EAST, OPEN_MAZE));
  EXPECT_FALSE(maze->hasExit(bottom_right, SOUTH, OPEN_MAZE));
}

TEST_F(MazeTest, classic_maze_initialises_open_walls) {
  Maze classic_maze(16);
  // this is a lazy test against known data rather than an exhaustive test
  // of wall states
  for (uint16_t cell = 0; cell < classic_maze.numCells(); cell++) {
    EXPECT_EQ(emptyMaze[cell] & 0x0f, classic_maze.openWalls(cell));
  }
}

TEST_F(MazeTest, classic_maze_initialises_closed_walls) {
  Maze classic_maze(16);
  for (uint16_t cell = 0; cell < classic_maze.numCells(); cell++) {
    if (cell == 0) {
      EXPECT_EQ(0x0E, classic_maze.closedWalls(cell));
    } else if (cell == maze->neighbour(0, NORTH)) {
      EXPECT_EQ(0x0B, classic_maze.closedWalls(cell));
    } else {
      EXPECT_EQ(0x0f, classic_maze.closedWalls(cell));
    }
  }
}



TEST_F(MazeTest, CopyMaze) {
  maze->copyMazeFromFileData(emptyMaze, 256);
  for (uint16_t cell = 0; cell < maze->numCells(); cell++) {
    EXPECT_EQ(emptyMaze[cell] & 0x0f, maze->openWalls(cell));
    EXPECT_TRUE(maze->isVisited(cell));
  }
}

TEST_F(MazeTest, SetClearUnknowns_TestoneCell) {
  maze->resetToEmptyMaze();
  EXPECT_EQ(0x00, maze->walls(0x22));
  EXPECT_EQ(0x0E, maze->walls(0x00));
  EXPECT_EQ(0x08, maze->walls(0x01));
}

TEST_F(MazeTest, SetClearUnknowns_NoChangeInExploredMaze) {
  maze->copyMazeFromFileData(emptyMaze, 256);
  Maze setMaze(16);
  Maze clearMaze(16);
  setMaze.copyMazeFromFileData(emptyMaze, 256);

  clearMaze.copyMazeFromFileData(emptyMaze, 256);

  for (uint16_t cell = 0; cell < maze->numCells(); cell++) {
    EXPECT_EQ(setMaze.walls(cell), clearMaze.walls(cell));
  }
}

TEST_F(MazeTest, SetClearUnknowns_AllDifferentInUnExploredMaze) {
  maze->resetToEmptyMaze();
  EXPECT_EQ(maze->openWalls(0), maze->closedWalls(0));
  for (uint16_t cell = 1; cell < maze->numCells(); cell++) {
    uint8_t openWalls = maze->openWalls(cell);
    uint8_t closedWalls = maze->closedWalls(cell);
    EXPECT_NE(openWalls, closedWalls);
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


/////////////////////
TEST_F(MazeTest, HasExit) {
  maze->resetToEmptyMaze();
  EXPECT_FALSE(maze->hasOpenExit(0x0F, WEST));
  EXPECT_FALSE(maze->hasOpenExit(0x0F, NORTH));
  EXPECT_FALSE(maze->hasOpenExit(0xF0, EAST));
  EXPECT_FALSE(maze->hasOpenExit(0xF0, SOUTH));
}

TEST_F(MazeTest, CopyCellFromFileData_GetExactCopy) {
  const uint8_t *src = japan2007ef;
  maze->resetToEmptyMaze();
  maze->copyMazeFromFileData(src, maze->numCells());
  for (int i = 0; i < maze->numCells(); i++) {
    EXPECT_EQ(src[i] & 0x0f, maze->walls(i));
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
  maze->copyMazeFromFileData(japan2007ef, 256);
  maze->save(backupWalls);
  maze->resetToEmptyMaze();
  for (int i = 0; i < maze->numCells(); i++) {
    EXPECT_EQ(maze->walls(i), emptyMaze[i] & 0x0f);
  }
  maze->load(backupWalls);
  for (int i = 0; i < maze->numCells(); i++) {
    EXPECT_EQ(maze->walls(i), japan2007ef[i] & 0x0f);
  }


}
