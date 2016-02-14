/*
 * File:   mazeflooder.c
 * Author: peterharrison
 *
 * Created on 13 February 2016, 21:48
 */
#include <stdio.h>
#include "maze.h"
#include "list.h"
#include "mazeflooder.h"

void binary (uint8_t i)
{
  uint8_t n = 128;
  while (n) {
    if (n & i) {
      printf ("1");
    } else {
      printf ("0");
    }

    n >>= 1;
  }
}
void FloodMazeClassic (location_t target)
{
  location_t here;
  location_t nextLoc;
  cost_t costHere;
  cost_t costNext;
  walls_t walls;
  for (here.row = 0; here.row < MAZE_ROWS; here.row++) {
    for (here.col = 0; here.col < MAZE_COLS; here.col++) {
      SetCost (here, MAX_COST);
    }
  }
  SetCost (target, 0);
  ListClear();
  ListAdd (target);
  while (!ListEmpty()) {
    /*
     * TODO: show costs and directions for all combinations
     * of testing against MAX_COST vs smaller than and stack vs queue
     */
    here = ListQueueHead();
    //here = ListStackPop();
    costNext = Cost (here) + 1;
    walls = MazeGetWalls (here);
    if (!HaveWall (walls, NORTH)) {
      nextLoc = Neighbour (here, NORTH);
      if (Cost (nextLoc)  > costNext) {
        SetDirection (nextLoc, SOUTH);
        SetCost (nextLoc, costNext);
        ListAdd (nextLoc);
      }
    }

    if (!HaveWall (walls, EAST)) {
      nextLoc = Neighbour (here, EAST);
      if (Cost (nextLoc)  > costNext) {
        SetDirection (nextLoc, WEST);
        SetCost (nextLoc, costNext);
        ListAdd (nextLoc);
      }
    }

    if (!HaveWall (walls, SOUTH)) {
      nextLoc = Neighbour (here, SOUTH);
      if (Cost (nextLoc)  > costNext) {
        SetDirection (nextLoc, NORTH);
        SetCost (nextLoc, costNext);
        ListAdd (nextLoc);
      }
    }

    if (!HaveWall (walls, WEST)) {
      nextLoc = Neighbour (here, WEST);
      if (Cost (nextLoc)  > costNext) {
        SetDirection (nextLoc, EAST);
        SetCost (nextLoc, costNext);
        ListAdd (nextLoc);
      }
    }

  }
  printf ("%d = List Size", ListMaxSize());
}
