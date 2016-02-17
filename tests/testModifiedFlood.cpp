#include "gtest/gtest.h"
#include <iostream>

#include "maze.h"
#include "mazeflooder.h"
#include "mazeprinter.h"
#include "mazereader.h"

class ModifiedFloodTest : public ::testing::Test
{

  virtual void SetUp()
  {
    MazeResetWalls();
    FloodMazeClassic (DefaultGoal());
    ReadMAZFile ("mazefiles/minos03f.maz");
    FloodMazeClassic (DefaultGoal());
    MazeClearWall (Location (2, 0), NORTH);
    EXPECT_EQ (0, Cost (DefaultGoal()));
    EXPECT_EQ (46, Cost (Home()));
    EXPECT_EQ (EAST, MazeGetDirection (Location (2, 0)));
  }

  virtual void TearDown() { }
};

TEST_F (ModifiedFloodTest, SetupTest)
{
  /* not sure what constitutes a good tests here */
  PrintMaze (DIRS);
  PrintMaze (COSTS);
  ModifiedFlood (Location (2, 0));
  EXPECT_EQ (NORTH, MazeGetDirection (Location (2, 0)));
  EXPECT_EQ (0, Cost (DefaultGoal()));
  EXPECT_EQ (40, Cost (Home()));
  PrintMaze (DIRS);
  PrintMaze (COSTS);
}
