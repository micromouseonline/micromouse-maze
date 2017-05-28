#include "gtest/gtest.h"
#include "maze.h"


TEST (Costs, MazeGetCosts_default_ValuesZero)
{
  Maze maze;
  EXPECT_EQ (UINT16_MAX, maze.cost(0));
}


TEST (Costs, MazeSetCosts_SetCost_getCost)
{
  Maze maze;
  maze.setCost(0x43,123);
  EXPECT_EQ(123,maze.cost(0x43));
}
