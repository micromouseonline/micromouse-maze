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

class MD_50_Maze_Tests : public ::testing::Test {
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

TEST_F(MD_50_Maze_Tests, initial_size_is_correct) {
  EXPECT_EQ(16, maze->width());
  Maze big_maze(32);
  EXPECT_EQ(32, big_maze.width());
}

TEST_F(MD_50_Maze_Tests, initial_change_flag) {
  Maze big_maze(32);
  EXPECT_TRUE(big_maze.has_changed());
  big_maze.set_change_flag(false);
  EXPECT_FALSE(big_maze.has_changed());
}

TEST_F(MD_50_Maze_Tests, flood_updates_change_flag) {
  maze->set_change_flag(true);
  EXPECT_TRUE(maze->has_changed());
  maze->flood(0x77, MASK_OPEN);
  EXPECT_FALSE(maze->has_changed());
}

TEST_F(MD_50_Maze_Tests, wall_change_updates_change_flag) {
  maze->set_change_flag(false);
  EXPECT_FALSE(maze->has_changed());
  maze->set_wall_present(0x33, DIR_N);
  EXPECT_TRUE(maze->has_changed());
}


TEST_F(MD_50_Maze_Tests, has_open_exit) {
  maze->reset_to_empty();
  EXPECT_TRUE(maze->hasExit(0x01, DIR_N));
  EXPECT_TRUE(maze->hasExit(0x01, DIR_S));
  EXPECT_TRUE(maze->hasExit(0x01, DIR_E));
  EXPECT_FALSE(maze->hasExit(0x01, DIR_W));
}

TEST_F(MD_50_Maze_Tests, has_closed_exit) {
  maze->reset_to_empty();
  maze->set_wall_mask(MASK_CLOSED);
  EXPECT_FALSE(maze->hasExit(0x01, DIR_N));
  EXPECT_TRUE(maze->hasExit(0x01, DIR_S));
  EXPECT_FALSE(maze->hasExit(0x01, DIR_E));
  EXPECT_FALSE(maze->hasExit(0x01, DIR_W));
}


TEST_F(MD_50_Maze_Tests, initialisation_has_boundary_walls) {
  EXPECT_FALSE(maze->hasExit(bottom_left, DIR_W));
  EXPECT_FALSE(maze->hasExit(bottom_left, DIR_S));
  EXPECT_FALSE(maze->hasExit(top_left, DIR_W));
  EXPECT_FALSE(maze->hasExit(top_left, DIR_N));
  EXPECT_FALSE(maze->hasExit(top_right, DIR_N));
  EXPECT_FALSE(maze->hasExit(top_right, DIR_E));
  EXPECT_FALSE(maze->hasExit(bottom_right, DIR_E));
  EXPECT_FALSE(maze->hasExit(bottom_right, DIR_S));
}

TEST_F(MD_50_Maze_Tests, classic_maze_initialises_open_walls) {
  Maze classic_maze(16);
  // this is a lazy test against known data rather than an exhaustive test
  // of wall states
  for (uint16_t cell = 0; cell < classic_maze.numCells(); cell++) {
    EXPECT_EQ(emptyMaze[cell] & 0x0f, classic_maze.get_cell_walls_byte(cell));
  }
}


TEST_F(MD_50_Maze_Tests, CopyMaze) {
  maze->set_from_file_data(emptyMaze, 256);
  for (uint16_t cell = 0; cell < maze->numCells(); cell++) {
    EXPECT_EQ(emptyMaze[cell] & 0x0f, maze->get_cell_walls_byte(cell));
    EXPECT_TRUE(maze->isVisited(cell));
  }
}

TEST_F(MD_50_Maze_Tests, SetClearUnknowns_TestoneCell) {
  maze->reset_to_empty();
  EXPECT_EQ(0x00, maze->get_cell_walls_byte(0x22));
  EXPECT_EQ(0x0E, maze->get_cell_walls_byte(0x00));
  EXPECT_EQ(0x08, maze->get_cell_walls_byte(0x01));
}

TEST_F(MD_50_Maze_Tests, SetClearUnknowns_NoChangeInExploredMaze) {
  maze->set_from_file_data(emptyMaze, 256);
  Maze setMaze(16);
  Maze clearMaze(16);

  setMaze.set_from_file_data(emptyMaze, 256);

  clearMaze.set_from_file_data(emptyMaze, 256);

  for (uint16_t cell = 0; cell < maze->numCells(); cell++) {
    EXPECT_EQ(setMaze.get_cell_walls_byte(cell), clearMaze.get_cell_walls_byte(cell));
  }
}


TEST_F(MD_50_Maze_Tests, ResetData_OnlyHomeCellVisited) {
  maze->reset_to_empty();
  for (int i = 0; i < maze->numCells(); i++) {
    if (i != maze->home()) {
      EXPECT_FALSE(maze->isVisited(i));
    }
  }
}


/////////////////////
TEST_F(MD_50_Maze_Tests, HasExit) {
  maze->reset_to_empty();
  EXPECT_FALSE(maze->hasExit(0x0F, DIR_W));
  EXPECT_FALSE(maze->hasExit(0x0F, DIR_N));
  EXPECT_FALSE(maze->hasExit(0xF0, DIR_E));
  EXPECT_FALSE(maze->hasExit(0xF0, DIR_S));
}

TEST_F(MD_50_Maze_Tests, CopyCellFromFileData_GetExactCopy) {
  const uint8_t *src = japan2007ef;
  maze->reset_to_empty();
  maze->set_from_file_data(src, maze->numCells());
  for (int i = 0; i < maze->numCells(); i++) {
    EXPECT_EQ(src[i] & 0x0f, maze->get_cell_walls_byte(i));
    EXPECT_TRUE(maze->isVisited(i));
  }
}


TEST_F(MD_50_Maze_Tests, NeighbourCellAddresses) {
  for (uint16_t cell = 0; cell < maze->numCells(); cell++) {
    EXPECT_EQ((cell + 1) % maze->numCells(), maze->cell_north(cell));
    EXPECT_EQ((cell + maze->width()) % maze->numCells(), maze->cell_east(cell));
    EXPECT_EQ((cell + maze->numCells() - 1) % maze->numCells(), maze->cell_south(cell));
    EXPECT_EQ((cell + maze->numCells() - maze->width()) % maze->numCells(), maze->cell_west(cell));
    EXPECT_EQ(maze->cell_north(cell), maze->neighbour(cell, DIR_N));
    EXPECT_EQ(maze->cell_east(cell), maze->neighbour(cell, DIR_E));
    EXPECT_EQ(maze->cell_south(cell), maze->neighbour(cell, DIR_S));
    EXPECT_EQ(maze->cell_west(cell), maze->neighbour(cell, DIR_W));
  }
}


TEST_F(MD_50_Maze_Tests, NeighbourInvalidDirection_ReturnsUINT16_MAX) {
  EXPECT_EQ(MAX_COST, maze->neighbour(0, -1));
}
