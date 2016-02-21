#include <iostream>
#include "gtest/gtest.h"
#include "maze.h"
#include "mazereader.h"
#include "mazeflooder.h"
#include "mazepathfinder.h"
#include "mazeprinter.h"


class PathFinder : public ::testing::Test
{

  /* This gets run before each test */
  virtual void SetUp()
  {
    char testMazeName[] = "mazefiles/empty.maz";
    MazeResetWalls();
    MazeResetCosts();
    MazeResetDirections();
    ReadRealWallsFromFile (testMazeName);
    UpdateEntireMazeFromRealWalls ();
    SetGoal (DefaultGoal());
    FloodMazeClassic (DefaultGoal());
  }

  virtual void TearDown() { }
};


TEST (PathFinder, StartsAtGoal_ReturnsZeroPathLength)
{
  location_t start = DefaultGoal();
  location_t end = DefaultGoal();
  int pathLength = IsolatePath (start, end);
  ASSERT_EQ (0, pathLength);
  ASSERT_EQ (INVALID, Direction (start));
}


TEST (PathFinder, StartsAtUnreachablel_ReturnsNegativePathLength)
{
  location_t start = Location (6, 12);
  location_t end = DefaultGoal();
  int pathLength = IsolatePath (start, end);
  ASSERT_EQ (-1, pathLength);
  ASSERT_EQ (INVALID, Direction (start));
}


TEST (PathFinder, test)
{
  int pathLength = IsolatePath (Home(), DefaultGoal());
  ASSERT_GE (200, pathLength);
}

TEST (PathFinder, testTargetNotReachable_ExpectPathGT200)
{
  int pathLength = IsolatePath (Home(), Location (10, 10));
  ASSERT_LE (200, pathLength);
}

