#include "gtest/gtest.h"
#include "oldmaze.h"
#include "mazereader.h"
#include "mazeflooder.h"

#include "maze.h"


class Flood : public ::testing::Test {
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

TEST_F (Flood, FloodMaze_TargetCostIsZero) {
  uint16_t goalCell = 0x34;
  maze->setGoal(goalCell);
  EXPECT_EQ(UINT16_MAX, maze->cost(0));
  maze->setGoal(goalCell);
  maze->flood(goalCell);
  EXPECT_EQ(0, maze->cost(goalCell));
  EXPECT_NE(0, maze->cost(0));
}

TEST_F (Flood, FloodMaze_BlockedMaze_HomeCostMax) {
  maze->setWall(0x00, NORTH);
  maze->flood(maze->goal());
//  EXPECT_EQ(UINT16_MAX, maze->cost(0));
}


TEST_F (Flood, FloodMaze_EmptyOpenMaze_NeighboursPointToGoal) {
//  uint16_t goal = 0x55;
//  maze->flood(goal, Maze::unknownsAreClear);
//  uint16_t neighbour = maze->cellNorth(goal);
//  EXPECT_EQ(SOUTH, maze->heading(neighbour));
//  EXPECT_EQ(SOUTH, maze->smallestNeighbourDirection(neighbour));
//  neighbour = maze->cellWest(goal);
//  EXPECT_EQ(EAST, maze->heading(neighbour));
//  EXPECT_EQ(EAST, maze->smallestNeighbourDirection(neighbour));
//  neighbour = maze->cellSouth(goal);
//  EXPECT_EQ(NORTH, maze->heading(neighbour));
//  EXPECT_EQ(NORTH, maze->smallestNeighbourDirection(neighbour));
//  neighbour = maze->cellEast(goal);
//  EXPECT_EQ(WEST, maze->heading(neighbour));
//  EXPECT_EQ(WEST, maze->smallestNeighbourDirection(neighbour));
}


TEST_F (Flood, FloodMaze_EmptyClosedMaze) {
  uint16_t goal = 0x55;
//  maze->flood(goal);
//  EXPECT_EQ(UINT16_MAX,maze->cost(0));
//  EXPECT_EQ(0,maze->cost(goal));
}
