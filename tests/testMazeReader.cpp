#include "gtest/gtest.h"

#include "maze.h"
#include "mazeReader.h"

TEST (MazeReader, LoadMazeFromFile)
{
  char fileName[] = "mazefiles/empty.maz";
  LoadMAZFile (fileName);
  EXPECT_EQ (ALL_SEEN + WEST_WALL + SOUTH_WALL + EAST_WALL, Walls (Home()));
}


TEST (MazeReader, LoadMazeFromInvalidFile)
{
  char fileName[] = "mazefiles/aaaaaa.maz";
  LoadMAZFile (fileName);
  EXPECT_EQ (ALL_SEEN + NO_WALLS, Walls (Home()));
}
