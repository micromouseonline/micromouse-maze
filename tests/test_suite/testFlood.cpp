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


class MazeFlood : public ::testing::Test {
protected:
  Maze *maze;

  virtual void SetUp() {
    maze = new Maze(16);
    maze->resetToEmptyMaze();
  }

  virtual void TearDown() {
    delete maze;
  }

  virtual void copyClassicMaze(const uint8_t *mazeData) const {
    for (int cell = 0; cell < this->maze->numCells(); ++cell) {
      maze->copyCellFromFileData(cell, mazeData[cell]);
    }
  }

};

TEST_F (MazeFlood, FloodMaze_TargetCostIsZero) {
  uint16_t target = 0x34;
  EXPECT_EQ(MAX_COST, maze->cost(0));
  maze->flood(target);
  EXPECT_EQ(0, maze->cost(target));
  EXPECT_NE(0, maze->cost(0));
}

TEST_F (MazeFlood, FloodMaze_BlockedMaze_HomeCostMax) {
  maze->setWall(0x00, NORTH);
  maze->flood(maze->goal());
  EXPECT_EQ(MAX_COST, maze->cost(0));
}

TEST_F (MazeFlood, FloodOpenUnexploredMaze_HomeCostNotMax) {
  maze->clearUnknowns();
  maze->flood(maze->goal());
  EXPECT_NE(MAX_COST, maze->cost(0));
  EXPECT_EQ(NORTH,maze->direction(0));
}


TEST_F (MazeFlood, FloodClosedMaze_HomeCostMax) {
  maze->setUnknowns();
  maze->flood(maze->goal());
  EXPECT_EQ(MAX_COST, maze->cost(0));
  EXPECT_EQ(INVALID_DIRECTION,maze->direction(0));
  maze->clearUnknowns();

}


TEST_F (MazeFlood, FloodKnownMaze_OpenClosedCostsSame) {
  copyClassicMaze(japan2007ef);
  maze->setUnknowns();
  uint16_t closedCost = maze->flood(maze->goal());
  maze->clearUnknowns();
  uint16_t openCost = maze->flood(maze->goal());
 EXPECT_EQ(closedCost,openCost);
  EXPECT_EQ(NORTH,maze->direction(0));
}



TEST_F (MazeFlood, UnExploredMazeSolution) {
  maze->resetToEmptyMaze();
  maze->testForSolution();
  EXPECT_GE(maze->closedMazeCost(), maze->openMazeCost());
  EXPECT_EQ(64601,maze->costDifference());
  EXPECT_FALSE(maze->isSolved());
}



TEST_F (MazeFlood, UnExploredMazeSolution_Manhattan) {
  maze->resetToEmptyMaze();
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->testForSolution();
  EXPECT_GE(maze->closedMazeCost(), maze->openMazeCost());
  EXPECT_EQ(65521,maze->costDifference());
  EXPECT_FALSE(maze->isSolved());
}



TEST_F (MazeFlood, ExploredMazeSolution) {
  maze->resetToEmptyMaze();
  copyClassicMaze(japan2007ef);
  maze->testForSolution();
  EXPECT_GE(maze->closedMazeCost(), maze->openMazeCost());
  EXPECT_EQ(0,maze->costDifference());
  EXPECT_TRUE(maze->isSolved());
}



TEST_F (MazeFlood, FloodPartialMaze_SolutionTestFails) {
  maze->resetToEmptyMaze();
  copyClassicMaze(japan2007ef);
  maze->testForSolution();

  EXPECT_TRUE(maze->isSolved());
  // Cell 0x07 lies on all best routes for Japan2007
  maze->clearVisited(0xA7);
  maze->testForSolution();
  EXPECT_FALSE(maze->isSolved());
  EXPECT_GT(maze->closedMazeCost(),maze->openMazeCost());
  maze->setVisited(0xA7);
  // cell 0x0F is critical for the runLengthFlood
  // but is not on the shortest manhatten path
  maze->clearVisited(0x0F);
  maze->testForSolution();
  EXPECT_FALSE(maze->isSolved());
  EXPECT_GT(maze->closedMazeCost(),maze->openMazeCost());
}

// full maze floods are not so easily tested.
// here we just look for the cost left in cell 0
TEST_F(MazeFlood, ManhattanFlood_EmptyMaze_cost_14){
  maze->resetToEmptyMaze();
  uint16_t cost = maze->manhattanFlood(0x77);
  EXPECT_EQ(14,cost);
  // top left cell
  EXPECT_EQ(15,maze->cost(maze->width()-1));
  EXPECT_EQ(NORTH,maze->direction(0));
}

TEST_F(MazeFlood, ManhattanFlood_Japan2007_costx){
  maze->copyMazeFromFileData(japan2007ef, 256);
  uint16_t cost = maze->manhattanFlood(0x77);
  EXPECT_EQ(72,cost);
  // top left cell
  EXPECT_EQ(43,maze->cost(maze->width()-1));
  EXPECT_EQ(NORTH,maze->direction(0));
}

TEST_F(MazeFlood, WeightedFlood_EmptyMaze_cost_31){
  maze->resetToEmptyMaze();
  uint16_t cost = maze->weightedFlood(0x77);
  EXPECT_EQ(31,cost);
  // top left cell
  EXPECT_EQ(31,maze->cost(maze->width()-1));
  EXPECT_EQ(NORTH,maze->direction(0));
}

TEST_F(MazeFlood, directionFlood_EmptyMaze_cost_31){
  maze->resetToEmptyMaze();
  uint16_t cost = maze->directionFlood(0x77);
  EXPECT_EQ(14,cost);
  // top left cell
  EXPECT_EQ(15,maze->cost(maze->width()-1));
  EXPECT_EQ(NORTH,maze->direction(0));
}
