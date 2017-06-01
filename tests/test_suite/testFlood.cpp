#include "gtest/gtest.h"
#include "oldmaze.h"
#include "mazereader.h"
#include "mazeflooder.h"

#include "maze.h"
#include "mazeprinter.h"

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

  virtual void copyMaze(const uint8_t *mazeData) const {
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

TEST_F (MazeFlood, FloodOpenUnexploredMaze_HomeCost105) {
  maze->clearUnknowns();
  maze->flood(maze->goal());
  EXPECT_EQ(95, maze->cost(0));
  PrintMaze(maze,COSTS);
}


TEST_F (MazeFlood, FloodClosedMaze_HomeCostMax) {
  maze->setUnknowns();
  maze->flood(maze->goal());
  EXPECT_EQ(MAX_COST, maze->cost(0));
  maze->clearUnknowns();
}


TEST_F (MazeFlood, FloodKnownMaze_OpenClosedCostsSame) {
  copyMaze(japan2007);
  maze->setUnknowns();
  maze->flood(maze->goal());
  maze->clearUnknowns();
  maze->flood(maze->goal());
  EXPECT_EQ(maze->closedMazeCost(), maze->openMazeCost());
}



TEST_F (MazeFlood, ExploredMazeSolution) {
  maze->resetToEmptyMaze();
  copyMaze(japan2007);
  maze->testForSolution();
  EXPECT_GE(maze->closedMazeCost(), maze->openMazeCost());
  EXPECT_EQ(0,maze->costDifference());
  EXPECT_TRUE(maze->isSolved());
}



TEST_F (MazeFlood, FloodPartialMaze_SolutionTestFails) {
  maze->resetToEmptyMaze();
  copyMaze(japan2007);
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

