#include "gtest/gtest.h"
#include "maze.h"
#include "mazereader.h"
#include "mazeflooder.h"

TEST (Flood, FloodMazeClassic_TargetCostZero)
{
  location_t target = {3, 4};
  MazeResetWalls();
  LoadEmptyMaze();
  FloodMazeClassic (target);
  EXPECT_EQ (0, Cost (target));
}

TEST (Flood, FloodMazeClassic_BlockedMaze_HomeCostMax)
{
  location_t target = {7, 7};
  MazeResetWalls();
  LoadEmptyMaze();
  MazeAddWall (target, NORTH);
  MazeAddWall (target, EAST);
  MazeAddWall (target, SOUTH);
  MazeAddWall (target, WEST);
  FloodMazeClassic (target);
  EXPECT_EQ (MAX_COST, Cost (Home()));
}


TEST (Flood, FloodMazeClassic_EmptyMaze_TargetNeighbours1)
{
  location_t target = {3, 4};
  MazeResetWalls();
  LoadEmptyMaze();
  FloodMazeClassic (target);
  EXPECT_EQ (1, Cost (Neighbour (target, NORTH)));
  EXPECT_EQ (1, Cost (Neighbour (target, EAST)));
  EXPECT_EQ (1, Cost (Neighbour (target, SOUTH)));
  EXPECT_EQ (1, Cost (Neighbour (target, WEST)));
}

TEST (Flood, SmallestNeighbour_SetCostsWithClearMinimum_GetCorrectNeighbour)
{

  location_t target = {8, 8};
  direction_t direction;
  MazeResetWalls();
  LoadEmptyMaze();
  SetCost (target, 99);
  SetCost (Neighbour (target, NORTH), 22);
  SetCost (Neighbour (target, EAST), 1);
  SetCost (Neighbour (target, SOUTH), 22);
  SetCost (Neighbour (target, WEST), 22);
  direction = SmallestNeighbourDirection (target);
  EXPECT_EQ (EAST, direction);
}

TEST (Flood, SmallestNeighbour_SetCostsWithWalls_GetCorrectNeighbour)
{
  location_t target = {8, 8};
  direction_t direction;
  MazeResetWalls();
  LoadEmptyMaze();
  SetCost (target, 99);
  MazeAddWall (target, EAST);
  MazeAddWall (target, SOUTH);
  SetCost (Neighbour (target, NORTH), 22);
  SetCost (Neighbour (target, EAST), 1);
  SetCost (Neighbour (target, SOUTH), 2);
  SetCost (Neighbour (target, WEST), 3);
  direction = SmallestNeighbourDirection (target);
  EXPECT_EQ (WEST, direction);
}

