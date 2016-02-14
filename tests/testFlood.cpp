#include "gtest/gtest.h"
#include "maze.h"
#include "mazereader.h"
#include "mazeflooder.h"

TEST (Flood, FloodMazeClassic_TargetCostZero)
{
  location_t target = {3, 4};
  MazeResetData();
  ReadEmptyMaze();
  FloodMazeClassic (target);
  EXPECT_EQ (0, Cost (target));
}

TEST (Flood, FloodMazeClassic_BlockedMaze_HomeCostMax)
{
  location_t target = {7, 7};
  MazeResetData();
  ReadEmptyMaze();
  MazeSetWall (target, NORTH);
  MazeSetWall (target, EAST);
  MazeSetWall (target, SOUTH);
  MazeSetWall (target, WEST);
  FloodMazeClassic (target);
  EXPECT_EQ (MAX_COST, Cost (Home()));
}


TEST (Flood, FloodMazeClassic_EmptyMaze_TargetNeighbours1)
{
  location_t target = {3, 4};
  MazeResetData();
  ReadEmptyMaze();
  FloodMazeClassic (target);
  EXPECT_EQ (1, Cost (Neighbour (target, NORTH)));
  EXPECT_EQ (1, Cost (Neighbour (target, EAST)));
  EXPECT_EQ (1, Cost (Neighbour (target, SOUTH)));
  EXPECT_EQ (1, Cost (Neighbour (target, WEST)));
}

