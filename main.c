/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.c
 * Author: peterharrison
 *
 * Created on 07 February 2016, 23:47
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "maze.h"
#include "mazeprinter.h"
#include "mazereader.h"
#include "mazeflooder.h"
#include "mazepathfinder.h"

/*
 *
 */
int main (int argc, char** argv)
{
  char mazename[64];
  printf ("micromouse maze\n");
  MazeResetWalls();
  location_t target = DefaultGoal();

  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      ReadMAZFile (argv[i]);
      printf ("\n===============================================\n");
      FloodMazeClassic (target);
      printf (" : %s\n", argv[i]);
      IsolatePath(Home(),target);
      PrintMaze (DIRS);
      PrintMaze (COSTS);
    }
  } else {
    ReadMAZFile("mazefiles/minos03f.maz");
    printf ("\n===============================================\n");
    FloodMazeClassic (target);
    printf (" : %s\n", mazename);
    IsolatePath(Home(),target);
    PrintMaze (DIRS);
    PrintMaze (COSTS);

  }
  return (EXIT_SUCCESS);
}

