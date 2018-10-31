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
#include "maze.h"


class CostTest : public ::testing::Test {
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

TEST_F(CostTest, MazeGetCosts_default_ValuesUINT16_MAX) {
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    EXPECT_EQ(MAX_COST, maze->cost(cell));
  }
}


TEST_F(CostTest, MazeSetCosts_SetCost_getCost) {
  maze->setCost(0x43, 123);
  EXPECT_EQ(123, maze->cost(0x43));
}

TEST_F(CostTest, GetNeighbourCosts_GetCostIgnoresWals) {
  maze->resetToEmptyMaze();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell, cell);
  }
  uint32_t neighbour;
  uint32_t cell;
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    uint32_t neighbour;
    EXPECT_EQ(cell, maze->cost(cell));
    neighbour = maze->cellNorth(cell);
    EXPECT_EQ(neighbour, maze->cost(neighbour));
    neighbour = maze->cellEast(cell);
    EXPECT_EQ(neighbour, maze->cost(neighbour));
    neighbour = maze->cellSouth(cell);
    EXPECT_EQ(neighbour, maze->cost(neighbour));
    neighbour = maze->cellWest(cell);
    EXPECT_EQ(neighbour, maze->cost(neighbour));
  }
}

TEST_F(CostTest, CostDirection_GivesNeighbourCostIfNoWall) {
  maze->resetToEmptyMaze();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell, cell);
  }
  uint32_t neighbour;
  uint32_t cell;
  cell = 0x22;
  neighbour = maze->cellNorth(cell);
  EXPECT_EQ(neighbour, maze->cost(cell, NORTH));
  neighbour = maze->cellEast(cell);
  EXPECT_EQ(neighbour, maze->cost(cell, EAST));
  neighbour = maze->cellSouth(cell);
  EXPECT_EQ(neighbour, maze->cost(cell, SOUTH));
  neighbour = maze->cellWest(cell);
  EXPECT_EQ(neighbour, maze->cost(cell, WEST));
}

TEST_F(CostTest, CostDirection_GivesUINT16_MAXIfWall) {
  maze->resetToEmptyMaze();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell, cell);
  }
  uint32_t cell;
  cell = 0x22;
  maze->setWall(cell, NORTH);
  maze->setWall(cell, EAST);
  maze->setWall(cell, SOUTH);
  maze->setWall(cell, WEST);
  EXPECT_EQ(MAX_COST, maze->cost(cell, NORTH));
  EXPECT_EQ(MAX_COST, maze->cost(cell, EAST));
  EXPECT_EQ(MAX_COST, maze->cost(cell, SOUTH));
  EXPECT_EQ(MAX_COST, maze->cost(cell, WEST));
}

TEST_F(CostTest, SmallestNeighbourDirection) {
  maze->resetToEmptyMaze();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell, (uint16_t)cell);
  }

  EXPECT_EQ(WEST, maze->directionToSmallest(0x22));
  maze->setWall(0x22, WEST);
  EXPECT_EQ(SOUTH, maze->directionToSmallest(0x22));
  maze->setWall(0x22, SOUTH);
  EXPECT_EQ(NORTH, maze->directionToSmallest(0x22));
  maze->setWall(0x22, NORTH);
  EXPECT_EQ(EAST, maze->directionToSmallest(0x22));
  maze->setWall(0x22, EAST);

  // no accessible neighbours now
  EXPECT_EQ(INVALID_DIRECTION, maze->directionToSmallest(0x22));


}

TEST_F(CostTest, UpdateDirections) {
  maze->resetToEmptyMaze();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell, cell);
  }

  maze->updateDirections();
  EXPECT_EQ(WEST, maze->direction(0x22));

  maze->setWall(0x22, WEST);
  maze->updateDirections();
  EXPECT_EQ(SOUTH, maze->direction(0x22));

  maze->setWall(0x22, SOUTH);
  maze->updateDirections();
  EXPECT_EQ(NORTH, maze->direction(0x22));

  maze->setWall(0x22, NORTH);
  maze->updateDirections();
  EXPECT_EQ(EAST, maze->direction(0x22));

  maze->setWall(0x22, EAST);
  maze->updateDirections();
  EXPECT_EQ(INVALID_DIRECTION, maze->direction(0x22));
}
