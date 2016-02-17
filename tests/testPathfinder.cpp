#include "gtest/gtest.h"
#include "maze.h"
#include "mazereader.h"
#include "mazeflooder.h"
#include "mazepathfinder.h"
#include "mazeprinter.h"

TEST (PathFinder, test)
{
  MazeResetWalls();
  ReadMAZFile ("mazefiles/empty.maz");
  FloodMazeClassic (DefaultGoal());
  ASSERT_EQ (0xFE, Walls (Home()));
//    int pathLength = IsolatePath(Home(),Goal());
//    PrintMaze(DIRS);
//    ASSERT_EQ(12,pathLength);
}