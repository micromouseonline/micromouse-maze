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
#include "mazesearcher.h"

/*
 *
 */
int main (int argc, char** argv)
{
  char mazename[64];
  MazeResetWalls();
  MouseInit();
  location_t target = DefaultGoal();

  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      ReadRealWallsFromFile (argv[i]);
      MouseInit();
      MazeInit();
      int steps =  MouseSearchToFullFlood (target);
      MouseInit();
      MazeInit();
      int stepsMod =  MouseSearchToModifiedFlood (target);
      printf ("%4d : %3d %c %3d steps for %s\n", steps - stepsMod, steps, (steps > stepsMod) ? '>' : '<', stepsMod,  argv[i]);
    }
  } else {
    char fileName[] = "mazefiles/minos03f.maz" ;
    ReadRealWallsFromFile (fileName);
    MouseInit();
    MazeInit();
    printf (" : %s\n", mazename);
    int steps =  MouseSearchToFullFlood (target);
    PrintMaze (DIRS);
    PrintMaze (COSTS);
    printf ("searched in %d steps\n", steps);
  }
  return (EXIT_SUCCESS);
}

