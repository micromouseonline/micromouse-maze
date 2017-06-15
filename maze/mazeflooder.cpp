/*
 * File:   mazeflooder.c
 * Author: peterharrison
 *
 * Created on 13 February 2016, 21:48
 */
#include "oldmaze.h"
#include "list.h"
//#include "mazeflooder.h"
#if 0

void FloodMazeClassic (location_t target)
{
  location_t here;
  location_t nextLoc;
  for (here.row = 0; here.row < MAZE_ROWS; here.row++) {
    for (here.col = 0; here.col < MAZE_COLS; here.col++) {
      SetCost (here, MAX_COST);
      SetDirection (here, BAD_DIRECTION);
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
    cost_t costNext = Cost (here) + 1;
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
  //printf ("Max List Length = %d List additions = %d path cost = %d\n", ListMaxSize(), ListAdditions(), Cost (Home()));
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

void AddAllNeighboursToList (location_t here)
{
  ListAdd (Neighbour (here, NORTH));
  ListAdd (Neighbour (here, EAST));
  ListAdd (Neighbour (here, SOUTH));
  ListAdd (Neighbour (here, WEST));
}


#endif