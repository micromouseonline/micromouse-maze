#include "gtest/gtest.h"
#include <iostream>

#include "maze.h"
#include "mazeflooder.h"
#include "mazeprinter.h"
#include "mazereader.h"
#include "newmaze.h"
#include "D5Maze.h"

class ModifiedFloodTest : public ::testing::Test
{

  virtual void SetUp()
  {
    char mazeFileName[] = "../mazefiles/minos03f.maz";
    MazeResetWalls();
    ReadRealWallsFromFile (mazeFileName);
    UpdateEntireMazeFromRealWalls ();
    FloodMazeClassic (DefaultGoal());
    MazeRemoveWall (Location (2, 0), NORTH);
    EXPECT_EQ (0, Cost (DefaultGoal()));
    EXPECT_EQ (46, Cost (Home()));
    EXPECT_EQ (EAST, Direction (Location (2, 0)));
  }

  virtual void TearDown() { }
};

TEST_F (ModifiedFloodTest, SetupTest)
{
  /* not sure what constitutes a good tests here */
  ModifiedFlood (Location (2, 0));
  EXPECT_EQ (NORTH, Direction (Location (2, 0)));
  EXPECT_EQ (0, Cost (DefaultGoal()));
  EXPECT_EQ (40, Cost (Home()));
}

TEST_F (ModifiedFloodTest, StartsAtGoal_ReturnsNoChanges)
{
  /* not sure what constitutes a good tests here */
  ModifiedFlood (DefaultGoal());
  EXPECT_EQ (INVALID, Direction (DefaultGoal()));
  EXPECT_EQ (0, Cost (DefaultGoal()));
}

