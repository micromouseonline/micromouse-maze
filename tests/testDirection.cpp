#include "gtest/gtest.h"
#include "maze.h"

TEST (Direction, ClearDirectionData_AllNorth)
{
  location_t loc = {5, 6};
  MazeSetDirection (loc, SOUTH);
  MazeClearDirectionData();
  for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
    for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
      EXPECT_EQ (NORTH, MazeGetDirection (loc));
    }
  }
}

TEST (Direction, MazeGetDirection_defaultValue_getNORTH)
{
  location_t loc = Home();
  EXPECT_EQ (NORTH, MazeGetDirection (loc));
}

TEST (Direction, MazeSetDirection_ReturnSetValue)
{
  location_t loc = {3, 4};
  direction_t dir = EAST;
  EXPECT_EQ (NORTH, MazeGetDirection (loc));
  MazeSetDirection (loc, dir);
  EXPECT_EQ (dir, MazeGetDirection (loc));
}

TEST (Direction, DirectionGetLeftFrom)
{
  EXPECT_EQ (WEST, DirectionGetLeftFrom (NORTH));
  EXPECT_EQ (SOUTH, DirectionGetLeftFrom (WEST));
  EXPECT_EQ (EAST, DirectionGetLeftFrom (SOUTH));
  EXPECT_EQ (NORTH, DirectionGetLeftFrom (EAST));
}


TEST (Direction, DirectionGetRightFrom)
{
  EXPECT_EQ (EAST, DirectionGetRightFrom (NORTH));
  EXPECT_EQ (SOUTH, DirectionGetRightFrom (EAST));
  EXPECT_EQ (WEST, DirectionGetRightFrom (SOUTH));
  EXPECT_EQ (NORTH, DirectionGetRightFrom (WEST));
}

TEST (Direction, DirectionGetBehindFrom)
{
  EXPECT_EQ (SOUTH, DirectionGetBehindFrom (NORTH));
  EXPECT_EQ (WEST, DirectionGetBehindFrom (EAST));
  EXPECT_EQ (NORTH, DirectionGetBehindFrom (SOUTH));
  EXPECT_EQ (EAST, DirectionGetBehindFrom (WEST));
}



