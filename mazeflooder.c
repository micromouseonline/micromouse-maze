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
  for (here.row = 0; here.row < MAZE_ROWS; here.row++) {
    for (here.col = 0; here.col < MAZE_COLS; here.col++) {
      SetCost (here, MAX_COST);
      SetDirection (here, INVALID);
    }
  }
  SetCost (target, 0);
  ListReset();
  ListAdd (target);
  while (!ListIsEmpty()) {
    /*
     * TODO: show costs and directions for all combinations
     * of testing against MAX_COST vs smaller than and stack vs queue
     */
    here = ListQueueHead();
    //here = ListStackPop();
    costNext = Cost (here) + 1;
    if (HasExit (here, NORTH)) {
      nextLoc = Neighbour (here, NORTH);
      if (Cost (nextLoc) > costNext) {
        SetDirection (nextLoc, SOUTH);
        SetCost (nextLoc, costNext);
        ListAdd (nextLoc);
      }
    }

    if (HasExit (here, EAST)) {
      nextLoc = Neighbour (here, EAST);
      if (Cost (nextLoc) > costNext) {
        SetDirection (nextLoc, WEST);
        SetCost (nextLoc, costNext);
        ListAdd (nextLoc);
      }
    }

    if (HasExit (here, SOUTH)) {
      nextLoc = Neighbour (here, SOUTH);
      if (Cost (nextLoc) > costNext) {
        SetDirection (nextLoc, NORTH);
        SetCost (nextLoc, costNext);
        ListAdd (nextLoc);
      }
    }

    if (HasExit (here, WEST)) {
      nextLoc = Neighbour (here, WEST);
      if (Cost (nextLoc) > costNext) {
        SetDirection (nextLoc, EAST);
        SetCost (nextLoc, costNext);
        ListAdd (nextLoc);
      }
    }

  }
  printf ("Max List Length = %d List additions = %d path cost = %d\n", ListMaxSize(), ListAdditions(), Cost (Home()));
}

void AddOpenNeighboursToList (location_t here)
{
  if (HasExit (here, NORTH)) {
    ListAdd (Neighbour (here, NORTH));
  }
  if (HasExit (here, EAST)) {
    ListAdd (Neighbour (here, EAST));
  }
  if (HasExit (here, SOUTH)) {
    ListAdd (Neighbour (here, SOUTH));
  }
  if (HasExit (here, WEST)) {
    ListAdd (Neighbour (here, WEST));
  }
}

void ModifiedFlood (location_t here)
{
  direction_t direction;
  cost_t smallestCost;
  ListReset();
  ListAdd (here);
  while (!ListIsEmpty()) {
    here = ListStackPop();
    if (Cost (here) == 0) {
      continue;
    }
    direction = SmallestNeighbourDirection (here);
    smallestCost = Cost (Neighbour (here, direction));
    SetDirection (here, direction);
    if (Cost (here) != smallestCost + 1) {
      SetCost (here, smallestCost + 1);
      AddOpenNeighboursToList (here);
    }
  }
}


