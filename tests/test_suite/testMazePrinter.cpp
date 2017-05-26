#include "gtest/gtest.h"

#include <stdio.h>
#include "maze.h"
#include "mazereader.h"
#include "mazeflooder.h"
#include "mazeprinter.h"
#include "newmaze.h"
#include "D5Maze.h"

TEST (MazePrinter, DummyPrintingForCoverageTests)
{
  char mazeFileName[] = "mazefiles/minos03f.maz";
  MazeResetWalls();
  ReadRealWallsFromFile (mazeFileName);
  UpdateEntireMazeFromRealWalls ();
  FloodMazeClassic (DefaultGoal());
  PrintMaze (WALLS);
  PrintMaze (COSTS);
  PrintMaze (DIRS);
}

