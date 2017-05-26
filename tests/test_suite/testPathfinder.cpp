#include <iostream>
#include "gtest/gtest.h"
#include "maze.h"
#include "mazereader.h"
#include "mazeflooder.h"
#include "mazepathfinder.h"
#include "mazeprinter.h"

#include "D5Maze.h"


class PathFinder : public ::testing::Test {

  /* This gets run before each test */
  virtual void SetUp() {
    char testMazeName[] = "../mazefiles/empty.maz";
    MazeInit();
    ReadRealWallsFromFile(testMazeName);
    UpdateEntireMazeFromRealWalls();
    SetGoal(DefaultGoal());

    FloodMazeClassic(DefaultGoal());
  }
  virtual void TearDown() { }
};


TEST (PathFinder, StartsAtGoal_ReturnsZeroPathLength) {
  location_t start = DefaultGoal();
  location_t end = DefaultGoal();
  int pathLength = IsolatePath(start, end);
  ASSERT_EQ (0, pathLength);
  ASSERT_EQ (INVALID, Direction(start));
}


TEST (PathFinder, StartsAtUnreachablel_ReturnsNegativePathLength) {
  MazeInit();
  MazeAddWall(Location(6, 12), NORTH);
  MazeAddWall(Location(6, 12), EAST);
  MazeAddWall(Location(6, 12), SOUTH);
  MazeAddWall(Location(6, 12), WEST);
  FloodMazeClassic(DefaultGoal());
  PrintMaze(COSTS);
  location_t start = Location(6, 12);
  location_t end = DefaultGoal();
  int pathLength = IsolatePath(start, end);
  ASSERT_EQ (-1, pathLength);
  ASSERT_EQ (INVALID, Direction(start));
}


TEST (PathFinder, test) {
  int pathLength = IsolatePath(Home(), DefaultGoal());
  ASSERT_GE (200, pathLength);
}

TEST (PathFinder, testTargetNotReachable_ExpectPathGT200) {
  location_t testGoal = Location(6,12);
  MazeInit();
  MazeAddWall(testGoal, NORTH);
  MazeAddWall(testGoal, EAST);
  MazeAddWall(testGoal, WEST);
  FloodMazeClassic(testGoal);
  int pathLength = IsolatePath(Home(), testGoal);
  ASSERT_LT (pathLength, 250);
  MazeAddWall(testGoal, SOUTH);
  pathLength = IsolatePath(Home(), testGoal);
  ASSERT_GE (pathLength, 250);
}

