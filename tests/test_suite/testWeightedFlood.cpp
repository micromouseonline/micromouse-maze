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
#include "mazedata.h"
#include <mazeprinter.h>


class WeightedMazeFlood : public ::testing::Test {
protected:
  Maze *maze;

  virtual void SetUp() {
    maze = new Maze(16);
    maze->reset_to_empty();
    maze->setFloodType(Maze::WEIGHTED_FLOOD);
  }

  virtual void TearDown() {
    delete maze;
  }

};

TEST_F(WeightedMazeFlood, FloodOpenFreshMaze_costIs14) {
  maze->flood(maze->goal(), MASK_OPEN);
  EXPECT_EQ(31, maze->cost(0));
}

TEST_F(WeightedMazeFlood, FloodClosedFreshMaze_costIsMax) {
  maze->flood(maze->goal(), MASK_CLOSED);
  EXPECT_EQ(MAX_COST, maze->cost(0));
}


TEST_F(WeightedMazeFlood, FloodMaze_BlockedMaze_HomeCostMax) {
  maze->set_wall_present(0x00, DIR_N);
  maze->flood(maze->goal(), MASK_OPEN);
  EXPECT_EQ(MAX_COST, maze->cost(0));
}

TEST_F(WeightedMazeFlood, FloodOpenUnexploredMaze_HomeCostNotMax) {

  maze->flood(maze->goal(), MASK_OPEN);
  EXPECT_NE(MAX_COST, maze->cost(0));
  maze->updateDirections();
  EXPECT_EQ(DIR_N, maze->get_direction(0));
}


TEST_F(WeightedMazeFlood, FloodMaze_TargetCostIsZero) {
  uint16_t target = 0x34;
  EXPECT_EQ(MAX_COST, maze->cost(0));
  maze->flood(target, MASK_OPEN);
  EXPECT_EQ(0, maze->cost(target));
  EXPECT_NE(0, maze->cost(0));
}


TEST_F(WeightedMazeFlood, FloodClosedMaze_HomeCostMax) {

  maze->flood(maze->goal(), MASK_CLOSED);
  EXPECT_EQ(MAX_COST, maze->cost(0));
  EXPECT_EQ(DIR_BLOCKED, maze->get_direction(0));


}


TEST_F(WeightedMazeFlood, FloodKnownMaze_OpenClosedCostsSame) {
  maze->set_from_file_data(japan2007ef, 256);

  uint16_t closedCost = maze->flood(maze->goal(), MASK_CLOSED);

  uint16_t openCost = maze->flood(maze->goal(), MASK_OPEN);
  EXPECT_EQ(closedCost, openCost);
  maze->updateDirections();
  EXPECT_EQ(DIR_N, maze->get_direction(0));
}


TEST_F(WeightedMazeFlood, UnExploredMazeSolution) {
  maze->reset_to_empty();
  maze->testForSolution();
  EXPECT_GE(maze->closedMazeCost(), maze->openMazeCost());
  EXPECT_EQ(MAX_COST - 31, maze->costDifference());
  EXPECT_FALSE(maze->isSolved());
}


TEST_F(WeightedMazeFlood, UnExploredMazeSolution_Manhattan) {
  maze->reset_to_empty();
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->testForSolution();
  EXPECT_GE(maze->closedMazeCost(), maze->openMazeCost());
  EXPECT_EQ(65521, maze->costDifference());
  EXPECT_FALSE(maze->isSolved());
}


TEST_F(WeightedMazeFlood, ExploredMazeSolution) {
  maze->set_from_file_data(japan2007ef, 256);
  maze->testForSolution();
  EXPECT_GE(maze->closedMazeCost(), maze->openMazeCost());
  EXPECT_EQ(0, maze->costDifference());
  EXPECT_TRUE(maze->isSolved());
}


TEST_F(WeightedMazeFlood, FloodPartialMaze_SolutionTestFails) {
  //  maze->copyMazeFromFileData(japan2007ef, 256);
  //  maze->testForSolution();
  //
  //  EXPECT_TRUE(maze->isSolved());
  //  // Cell 0x07 lies on all best routes for Japan2007
  //  maze->clearVisited(0x07);
  //  maze->testForSolution();
  //  EXPECT_TRUE(maze->isSolved());
  //  EXPECT_GE(maze->closedMazeCost(), maze->openMazeCost());
  //  maze->setVisited(0xA7);
  //  // cell 0x0F is critical for the runLengthFlood
  //  // but is not on the shortest manhatten path
  //  maze->clearVisited(0x0F);
  //  maze->testForSolution();
  //  EXPECT_FALSE(maze->isSolved());
  //  EXPECT_GT(maze->closedMazeCost(), maze->openMazeCost());
}

// full maze floods are not so easily tested.
// here we just look for the cost left in cell 0
TEST_F(WeightedMazeFlood, ManhattanFlood_EmptyMaze_cost_14) {
  maze->reset_to_empty();

  uint16_t cost = maze->manhattanFlood(0x77, MASK_OPEN);
  EXPECT_EQ(14, cost);
  // top left cell
  EXPECT_EQ(15, maze->cost(maze->width() - 1));
  EXPECT_EQ(DIR_N, maze->directionToSmallest(0));
}

TEST_F(WeightedMazeFlood, ManhattanFlood_Japan2007_costx) {
  maze->set_from_file_data(japan2007ef, 256);
  uint16_t cost = maze->manhattanFlood(0x77, MASK_OPEN);
  EXPECT_EQ(72, cost);
  // top left cell
  EXPECT_EQ(43, maze->cost(maze->width() - 1));
  EXPECT_EQ(DIR_N, maze->directionToSmallest(0));
}

TEST_F(WeightedMazeFlood, WeightedFlood_EmptyMaze_cost_31) {
  maze->reset_to_empty();
  uint16_t cost = maze->weightedFlood(0x77, MASK_OPEN);
  EXPECT_EQ(31, cost);
  // top left cell
  EXPECT_EQ(31, maze->cost(maze->width() - 1));
  EXPECT_EQ(DIR_N, maze->directionToSmallest(0));
}

TEST_F(WeightedMazeFlood, directionFlood_EmptyMaze_cost_31) {
  maze->reset_to_empty();
  uint16_t cost = maze->directionFlood(0x77, MASK_OPEN);
  EXPECT_EQ(14, cost);
  // top left cell
  EXPECT_EQ(15, maze->cost(maze->width() - 1));
  EXPECT_EQ(DIR_N, maze->directionToSmallest(0));
}
