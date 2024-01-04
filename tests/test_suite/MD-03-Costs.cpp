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


class MD_03_Costs : public ::testing::Test {
protected:
  Maze *maze;

  virtual void SetUp() {
    maze = new Maze(16);
    maze->reset_to_empty();
  }

  virtual void TearDown() {
    delete maze;
  }

};

TEST_F(MD_03_Costs, MazeGetCosts_default_ValuesUINT16_MAX) {
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    EXPECT_EQ(MAX_COST, maze->cost(cell));
  }
}


TEST_F(MD_03_Costs, MazeSetCosts_SetCost_getCost) {
  maze->setCost(0x43, 123);
  EXPECT_EQ(123, maze->cost(0x43));
}

TEST_F(MD_03_Costs, GetNeighbourCosts_GetCostIgnoresWals) {
  maze->reset_to_empty();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell, cell);
  }
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    uint16_t neighbour;
    EXPECT_EQ(cell, maze->cost(cell));
    neighbour = maze->cell_north(cell);
    EXPECT_EQ(neighbour, maze->cost(neighbour));
    neighbour = maze->cell_east(cell);
    EXPECT_EQ(neighbour, maze->cost(neighbour));
    neighbour = maze->cell_south(cell);
    EXPECT_EQ(neighbour, maze->cost(neighbour));
    neighbour = maze->cell_west(cell);
    EXPECT_EQ(neighbour, maze->cost(neighbour));
  }
}

TEST_F(MD_03_Costs, CostDirection_GivesNeighbourCostIfNoWall) {
  maze->reset_to_empty();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell, cell);
  }
  uint32_t neighbour;
  uint32_t cell;
  cell = 0x22;
  neighbour = maze->cell_north(cell);
  EXPECT_EQ(neighbour, maze->cost(cell, DIR_N));
  neighbour = maze->cell_east(cell);
  EXPECT_EQ(neighbour, maze->cost(cell, DIR_E));
  neighbour = maze->cell_south(cell);
  EXPECT_EQ(neighbour, maze->cost(cell, DIR_S));
  neighbour = maze->cell_west(cell);
  EXPECT_EQ(neighbour, maze->cost(cell, DIR_W));
}

TEST_F(MD_03_Costs, CostDirection_GivesUINT16_MAXIfWall) {
  maze->reset_to_empty();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell, cell);
  }
  uint32_t cell;
  cell = 0x22;
  maze->set_wall_present(cell, DIR_N);
  maze->set_wall_present(cell, DIR_E);
  maze->set_wall_present(cell, DIR_S);
  maze->set_wall_present(cell, DIR_W);
  EXPECT_EQ(MAX_COST, maze->cost(cell, DIR_N));
  EXPECT_EQ(MAX_COST, maze->cost(cell, DIR_E));
  EXPECT_EQ(MAX_COST, maze->cost(cell, DIR_S));
  EXPECT_EQ(MAX_COST, maze->cost(cell, DIR_W));
}

TEST_F(MD_03_Costs, SmallestNeighbourDirection) {
  maze->reset_to_empty();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell, (uint16_t)cell);
  }

  EXPECT_EQ(DIR_W, maze->directionToSmallest(0x22));
  maze->set_wall_present(0x22, DIR_W);
  EXPECT_EQ(DIR_S, maze->directionToSmallest(0x22));
  maze->set_wall_present(0x22, DIR_S);
  EXPECT_EQ(DIR_N, maze->directionToSmallest(0x22));
  maze->set_wall_present(0x22, DIR_N);
  EXPECT_EQ(DIR_E, maze->directionToSmallest(0x22));
  maze->set_wall_present(0x22, DIR_E);

  // no accessible neighbours now
  EXPECT_EQ(DIR_BLOCKED, maze->directionToSmallest(0x22));


}

TEST_F(MD_03_Costs, UpdateDirections) {
  maze->reset_to_empty();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell, cell);
  }

  maze->updateDirections();
  EXPECT_EQ(DIR_W, maze->get_direction(0x22));

  maze->set_wall_present(0x22, DIR_W);
  maze->updateDirections();
  EXPECT_EQ(DIR_S, maze->get_direction(0x22));

  maze->set_wall_present(0x22, DIR_S);
  maze->updateDirections();
  EXPECT_EQ(DIR_N, maze->get_direction(0x22));

  maze->set_wall_present(0x22, DIR_N);
  maze->updateDirections();
  EXPECT_EQ(DIR_E, maze->get_direction(0x22));

  maze->set_wall_present(0x22, DIR_E);
  maze->updateDirections();
  EXPECT_EQ(DIR_BLOCKED, maze->get_direction(0x22));
}
