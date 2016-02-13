#include "gtest/gtest.h"
#include "maze.h"

TEST (Costs, MazeGetCosts_default_ValuesZero)
{
  location_t loc = {0, 0};
  EXPECT_EQ (0, MazeGetCost (loc));
}


TEST (Costs, MazeSetCosts_SetCost_getCost)
{
  location_t loc = {0, 0};
  MazeSetCost (loc, 123);
  EXPECT_EQ (123, MazeGetCost (loc));
}
