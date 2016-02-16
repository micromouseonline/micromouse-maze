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


/*
 * return the direction to neighbour with the smallest cost
 * There will always be one unless the cell has all walls.
 * That should not happen in normal maze and so no special care is taken
 * Only accessible neighbours are tested
 */

direction_t  SmallestNeighbourDirection (location_t loc)
{
  direction_t result = NORTH;
  location_t neighbour;
  cost_t smallestCost;
  cost_t cost;

  smallestCost = MAX_COST;
  if (HasExit (loc, NORTH)) {
    neighbour = Neighbour (loc, NORTH);
    cost = Cost (neighbour);
    if (cost < smallestCost) {
      smallestCost = cost;
      result = NORTH;
    }
  }
  if (HasExit (loc, EAST)) {
    neighbour = Neighbour (loc, EAST);
    cost = Cost (neighbour);
    if (cost < smallestCost) {
      smallestCost = cost;
      result = EAST;
    }
  }
  if (HasExit (loc, SOUTH)) {
    neighbour = Neighbour (loc, SOUTH);
    cost = Cost (neighbour);
    if (cost < smallestCost) {
      smallestCost = cost;
      result = SOUTH;
    }
  }
  if (HasExit (loc, WEST)) {
    neighbour = Neighbour (loc, WEST);
    cost = Cost (neighbour);
    if (cost < smallestCost) {
      smallestCost = cost;
      result = WEST;
    }
  }
  return result;
}


void FloodMazeClassic (location_t target)
{
  location_t here;
  location_t nextLoc;
  cost_t costHere;
  cost_t costNext;
  for (here.row = 0; here.row < MAZE_ROWS; here.row++) {
    for (here.col = 0; here.col < MAZE_COLS; here.col++) {
      SetCost (here, MAX_COST);
      SetDirection(here,INVALID);
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
    if (HasExit(here, NORTH)) {
      nextLoc = Neighbour (here, NORTH);
      if (Cost (nextLoc)  > costNext) {
        SetDirection (nextLoc, SOUTH);
        SetCost (nextLoc, costNext);
        ListAdd (nextLoc);
      }
    }

    if (HasExit(here,EAST)) {
      nextLoc = Neighbour (here, EAST);
      if (Cost (nextLoc)  > costNext) {
        SetDirection (nextLoc, WEST);
        SetCost (nextLoc, costNext);
        ListAdd (nextLoc);
      }
    }

    if (HasExit(here, SOUTH)) {
      nextLoc = Neighbour (here, SOUTH);
      if (Cost (nextLoc)  > costNext) {
        SetDirection (nextLoc, NORTH);
        SetCost (nextLoc, costNext);
        ListAdd (nextLoc);
      }
    }

    if (HasExit(here, WEST)) {
      nextLoc = Neighbour (here, WEST);
      if (Cost (nextLoc)  > costNext) {
        SetDirection (nextLoc, EAST);
        SetCost (nextLoc, costNext);
        ListAdd (nextLoc);
      }
    }

  }
  printf ("Max List Length = %d List additions = %d path cost = %d\n", ListMaxSize(), ListAdditions(), Cost (Home()));
}
