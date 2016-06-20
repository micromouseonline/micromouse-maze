
/*
 * File:   mazeprinter.c
 * Author: peterharrison
 *
 * Created on 13 February 2016, 19:53
 */
#include <stdio.h>
#include "maze.h"
#include "mazeprinter.h"
#include "mazesearcher.h"


static char dirChars[] = "^>v< ";

void PrintMaze (print_options_t option)
{
  location_t loc;
  walls_t walls;
  for (loc.row = MazeHeight() - 1; loc.row >= 0; loc.row--) {
    for (loc.col = 0; loc.col < MazeWidth(); loc.col++) {
      walls = Walls (loc);
      //Do the north walls
      printf ("o");
      if (WallExists (walls, NORTH)) {
        printf ("---");
      } else {
        printf ("   ");
      }
    }
    printf ("o\n");
    /* TODO:  this is all rather messy */
    for (loc.col = 0; loc.col < MazeWidth(); loc.col++) {
      walls = Walls (loc);
      //Do the west walls
      if (WallExists (walls, WEST)) {
        printf ("|");
      } else {
        printf (" ");
      }
      if (MousePosition().row == loc.row && MousePosition().col == loc.col) {
        printf ("[M]");
      } else if (option & COSTS) {
        cost_t cost = Cost (loc);
        if (cost == MAX_COST) {
          printf (" x ");
        } else {
          printf ("%3d", Cost (loc));
        }
      } else if (option & DIRS) {
        printf (" %c ", dirChars[Direction (loc)]);
      } else {
        printf ("   ");
      }
    }
    printf ("|\n");
  }
  for (loc.col = 0; loc.col < MazeWidth(); loc.col++) {
    /* Do the last row of walls on the south edge. They must all be there */
    printf ("o---");
  }
  printf ("o\n");
}
