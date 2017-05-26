#include "gtest/gtest.h"
#include "maze.h"

#include "D5Maze.h"


TEST (Direction, MazeGetDirection_defaultValue_isNORTH)
{
  D5Maze maze;

  maze.clearMaze();
  for(int i = 0; i < NUMCELLS; i++){
    EXPECT_EQ(NORTH,maze.heading(i));
  }
}

TEST (Direction, MazeSetDirection_ReturnSetValue)
{
  D5Maze maze;
  maze.clearMaze();
}

TEST (Direction, DirectionGetLeftFrom)
{
  D5Maze maze;
  EXPECT_EQ (WEST, maze.leftOf(NORTH));
  EXPECT_EQ (SOUTH, maze.leftOf (WEST));
  EXPECT_EQ (EAST, maze.leftOf(SOUTH));
  EXPECT_EQ (NORTH, maze.leftOf(EAST));
}


TEST (Direction, DirectionGetRightFrom)
{
  D5Maze maze;
  EXPECT_EQ (EAST, maze.rightOf (NORTH));
  EXPECT_EQ (SOUTH, maze.rightOf  (EAST));
  EXPECT_EQ (WEST, maze.rightOf  (SOUTH));
  EXPECT_EQ (NORTH, maze.rightOf  (WEST));

}

TEST (Direction, Behind)
{
  D5Maze maze;
  EXPECT_EQ (SOUTH, maze.behind (NORTH));
  EXPECT_EQ (WEST, maze.behind (EAST));
  EXPECT_EQ (NORTH, maze.behind (SOUTH));
  EXPECT_EQ (EAST, maze.behind (WEST));
}



