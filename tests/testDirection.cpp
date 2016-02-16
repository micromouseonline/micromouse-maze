#include "gtest/gtest.h"
#include "maze.h"

TEST (Direction, ClearDirectionData_AllNorth)
{
  location_t loc = {5, 6};
  SetDirection (loc, SOUTH);
  MazeClearDirectionData();
  for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
    for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
      EXPECT_EQ (INVALID, MazeGetDirection (loc));
    }
  }
}

TEST (Direction, MazeGetDirection_defaultValue_getNORTH)
{
  location_t loc = Home();
  EXPECT_EQ (INVALID, MazeGetDirection (loc));
}

TEST (Direction, MazeSetDirection_ReturnSetValue)
{
  location_t loc = {3, 4};
  direction_t dir = EAST;
  EXPECT_EQ (INVALID, MazeGetDirection (loc));
  SetDirection (loc, dir);
  EXPECT_EQ (dir, MazeGetDirection (loc));
}

TEST (Direction, DirectionGetLeftFrom)
{
  EXPECT_EQ (WEST, LeftFrom (NORTH));
  EXPECT_EQ (SOUTH, LeftFrom (WEST));
  EXPECT_EQ (EAST, LeftFrom (SOUTH));
  EXPECT_EQ (NORTH, LeftFrom (EAST));
}


TEST (Direction, DirectionGetRightFrom)
{
  EXPECT_EQ (EAST, RightFrom (NORTH));
  EXPECT_EQ (SOUTH, RightFrom (EAST));
  EXPECT_EQ (WEST, RightFrom (SOUTH));
  EXPECT_EQ (NORTH, RightFrom (WEST));
}

TEST (Direction, Behind)
{
  EXPECT_EQ (SOUTH, Behind (NORTH));
  EXPECT_EQ (WEST, Behind (EAST));
  EXPECT_EQ (NORTH, Behind (SOUTH));
  EXPECT_EQ (EAST, Behind (WEST));
}



