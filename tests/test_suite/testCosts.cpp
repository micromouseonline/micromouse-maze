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

TEST_F (CostTest, MazeGetCosts_default_ValuesUINT16_MAX) {
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    EXPECT_EQ (UINT16_MAX, maze->cost(cell));
  }
}


TEST_F (CostTest, MazeSetCosts_SetCost_getCost) {
  maze->setCost(0x43, 123);
  EXPECT_EQ(123, maze->cost(0x43));
}

TEST_F (CostTest, GetNeighbourCosts_GetCostIgnoresWals) {
  maze->resetToEmptyMaze();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell,cell);
  }
  uint32_t neighbour;
  uint32_t cell;
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    uint32_t neighbour;
    EXPECT_EQ(cell,maze->cost(cell));
    neighbour = maze->cellNorth(cell);
    EXPECT_EQ(neighbour,maze->cost(neighbour));
    neighbour = maze->cellEast(cell);
    EXPECT_EQ(neighbour,maze->cost(neighbour));
    neighbour = maze->cellSouth(cell);
    EXPECT_EQ(neighbour,maze->cost(neighbour));
    neighbour = maze->cellWest(cell);
    EXPECT_EQ(neighbour,maze->cost(neighbour));
  }
}

TEST_F (CostTest, CostDirection_GivesNeighbourCostIfNoWall) {
  maze->resetToEmptyMaze();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell,cell);
  }
  uint32_t neighbour;
  uint32_t cell;
  cell = 0x22;
  neighbour = maze->cellNorth(cell);
  EXPECT_EQ(neighbour,maze->costNorth(cell));
  neighbour = maze->cellEast(cell);
  EXPECT_EQ(neighbour,maze->costEast(cell));
  neighbour = maze->cellSouth(cell);
  EXPECT_EQ(neighbour,maze->costSouth(cell));
  neighbour = maze->cellWest(cell);
  EXPECT_EQ(neighbour,maze->costWest(cell));
}

TEST_F (CostTest, CostDirection_GivesUINT16_MAXIfWall) {
  maze->resetToEmptyMaze();
  for (int cell = 0; cell < maze->numCells(); ++cell) {
    maze->setCost(cell,cell);
  }
  uint32_t cell;
  cell = 0x22;
  maze->setWall(cell,NORTH);
  maze->setWall(cell,EAST);
  maze->setWall(cell,SOUTH);
  maze->setWall(cell,WEST);
  EXPECT_EQ(UINT16_MAX,maze->costNorth(cell));
  EXPECT_EQ(UINT16_MAX,maze->costEast(cell));
  EXPECT_EQ(UINT16_MAX,maze->costSouth(cell));
  EXPECT_EQ(UINT16_MAX,maze->costWest(cell));
}
