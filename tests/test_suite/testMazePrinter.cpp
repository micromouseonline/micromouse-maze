#include "gtest/gtest.h"

#include <stdio.h>
#include "oldmaze.h"
#include "mazereader.h"
#include "mazedata.h"
#include "mazeflooder.h"
#include "mazeprinter.h"

#include "maze.h"

TEST (MazePrinter, DummyPrintingForCoverageTests)
{
  char mazeFileName[] = "mazefiles/minos03f.maz";
  MazeResetWalls();

  ReadRealWallsFromFile (mazeFileName);
  UpdateEntireMazeFromRealWalls ();
  UpdateEntireMazeFromData(testMaze5x5);
  FloodMazeClassic (DefaultGoal());
  PrintMaze (WALLS);
  PrintMaze (COSTS);
  PrintMaze (DIRS);
}

