#include "gtest/gtest.h"
#include "maze.h"
#include "newmaze.h"
#include "D5Maze.h"


TEST (Costs, MazeGetCosts_default_ValuesZero)
{
  location_t loc = {0, 0};
  EXPECT_EQ (0, Cost (loc));
  NewMaze newMaze;
}


TEST (Costs, MazeSetCosts_SetCost_getCost)
{
  location_t loc = {0, 0};
  SetCost (loc, 123);
  EXPECT_EQ (123, Cost (loc));
}
