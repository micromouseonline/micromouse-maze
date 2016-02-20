#include "gtest/gtest.h"

#include <stdio.h>
#include "maze.h"
#include "mazereader.h"
#include "mazeflooder.h"
#include "mazeprinter.h"

TEST (MazePrinter, DummyPrintingForCoverageTests)
{
  char mazeFileName[] = "mazefiles/minos03f.maz";
  MazeResetWalls();
  LoadMAZFile (mazeFileName);
  FloodMazeClassic (DefaultGoal());
  PrintMaze (WALLS);
  PrintMaze (COSTS);
  PrintMaze (DIRS);
}
