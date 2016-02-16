
/*
 * File:   mazeprinter.c
 * Author: peterharrison
 *
 * Created on 13 February 2016, 19:53
 */
#include <stdio.h>
#include "maze.h"
#include "mazeprinter.h"


static char dirChars[] = "^>v< ";

void PrintMaze (print_options_t option)
{
  location_t loc;
  walls_t walls;
  for (loc.row = MazeHeight() - 1; loc.row >= 0; loc.row--) {
    for (loc.col = 0; loc.col < MazeWidth(); loc.col++) {
      walls = MazeGetWalls (loc);
      //Do the north walls
      printf ("o");
      if (HaveWall (walls, NORTH)) {
        printf ("---");
      } else {
        printf ("   ");
      }
    }
    printf ("o\n");
    for (loc.col = 0; loc.col < MazeWidth(); loc.col++) {
      walls = MazeGetWalls (loc);
      //Do the west walls
      if (HaveWall (walls, WEST)) {
        printf ("|");
      } else {
        printf (" ");
      }
      if (option & COSTS) {
        cost_t cost = Cost (loc);
        if (cost == MAX_COST) {
          printf (" x ");
        } else {
          printf ("%3d", Cost (loc));
        }
      } else if (option & DIRS) {
        printf (" %c ", dirChars[MazeGetDirection (loc)]);
      } else {
        printf ("   ");
      }
    }
    printf ("|\n");
  }
  for (loc.col = 0; loc.col < MazeWidth(); loc.col++) {
    //Do the last row of walls on the south edge
    printf ("o---");
  }
  printf ("o\n");
}
